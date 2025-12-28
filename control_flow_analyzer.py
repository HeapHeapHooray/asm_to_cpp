"""
Control Flow Analyzer
Analyzes control flow to reconstruct higher-level structures (loops, if-else, etc.)
"""

from typing import List, Dict, Set, Optional
from dataclasses import dataclass, field
from enum import Enum
from asm_parser import Function, BasicBlock, Instruction, InstructionType


class ControlStructureType(Enum):
    IF_THEN = "if_then"
    IF_THEN_ELSE = "if_then_else"
    WHILE_LOOP = "while"
    DO_WHILE_LOOP = "do_while"
    FOR_LOOP = "for"
    SWITCH = "switch"
    SEQUENTIAL = "sequential"


@dataclass
class ControlStructure:
    """Represents a high-level control structure"""
    type: ControlStructureType
    start_address: int
    end_address: int
    condition: Optional[str] = None
    true_branch: Optional['ControlStructure'] = None
    false_branch: Optional['ControlStructure'] = None
    body: Optional['ControlStructure'] = None
    blocks: List[BasicBlock] = field(default_factory=list)
    children: List['ControlStructure'] = field(default_factory=list)


class ControlFlowAnalyzer:
    """Analyzes control flow and reconstructs high-level structures"""

    def __init__(self):
        self.blocks_by_address: Dict[int, BasicBlock] = {}

    def analyze_function(self, func: Function) -> ControlStructure:
        """Analyze control flow of a function"""
        if not func.basic_blocks:
            return ControlStructure(
                type=ControlStructureType.SEQUENTIAL,
                start_address=func.start_address,
                end_address=func.end_address or func.start_address
            )

        # Build CFG
        self._build_cfg(func)

        # Identify loops
        loops = self._identify_loops(func)

        # Identify if-then-else structures
        conditionals = self._identify_conditionals(func, loops)

        # Build control structure tree
        return self._build_control_tree(func, loops, conditionals)

    def _build_cfg(self, func: Function):
        """Build control flow graph"""
        # First pass: index blocks by address
        self.blocks_by_address.clear()
        for bb in func.basic_blocks:
            self.blocks_by_address[bb.start_address] = bb

        # Second pass: build edges
        for bb in func.basic_blocks:
            if not bb.instructions:
                continue

            last_inst = bb.instructions[-1]

            # Handle jumps
            if last_inst.inst_type == InstructionType.JUMP:
                if last_inst.operands:
                    target_label = last_inst.operands[0].raw
                    if target_label.startswith('loc_'):
                        target_addr = int(target_label.split('_')[1], 16)
                        bb.successors.append(target_addr)

                        if target_addr in self.blocks_by_address:
                            self.blocks_by_address[target_addr].predecessors.append(bb.start_address)

                # Conditional jumps also fall through
                if last_inst.mnemonic.lower() != 'jmp':
                    # Find next block
                    next_addr = bb.end_address
                    if next_addr in self.blocks_by_address:
                        bb.successors.append(next_addr)
                        self.blocks_by_address[next_addr].predecessors.append(bb.start_address)

            # Handle returns
            elif last_inst.inst_type == InstructionType.RETURN:
                pass  # No successors

            # Fall through to next block
            else:
                next_addr = bb.end_address
                if next_addr in self.blocks_by_address:
                    bb.successors.append(next_addr)
                    self.blocks_by_address[next_addr].predecessors.append(bb.start_address)

    def _identify_loops(self, func: Function) -> List[Dict]:
        """Identify loop structures (natural loops)"""
        loops = []

        # Find back edges (edges that go to a dominator)
        # Simplified: look for jumps backwards
        for bb in func.basic_blocks:
            if not bb.instructions:
                continue

            last_inst = bb.instructions[-1]
            if last_inst.inst_type == InstructionType.JUMP:
                if last_inst.operands:
                    target_label = last_inst.operands[0].raw
                    if target_label.startswith('loc_'):
                        target_addr = int(target_label.split('_')[1], 16)

                        # Back edge if target is before current block
                        if target_addr <= bb.start_address:
                            loops.append({
                                'header': target_addr,
                                'latch': bb.start_address,
                                'type': self._classify_loop(bb, target_addr, last_inst)
                            })

        return loops

    def _classify_loop(self, latch_bb: BasicBlock, header_addr: int, jump_inst: Instruction) -> str:
        """Classify loop type (while, do-while, for)"""
        # Heuristics:
        # - do-while: conditional jump at end that jumps back
        # - while: conditional at start
        # - for: counter pattern

        if jump_inst.mnemonic.lower() == 'jmp':
            return 'infinite'

        # Check if there's a counter variable being decremented/incremented
        counter_pattern = False
        for inst in latch_bb.instructions:
            if inst.mnemonic.lower() in ['inc', 'dec', 'add', 'sub']:
                counter_pattern = True
                break

        if counter_pattern:
            return 'for'

        # do-while: conditional at end
        return 'do_while'

    def _identify_conditionals(self, func: Function, loops: List[Dict]) -> List[Dict]:
        """Identify if-then-else structures"""
        conditionals = []
        loop_headers = set(loop['header'] for loop in loops)

        for bb in func.basic_blocks:
            if not bb.instructions:
                continue

            # Skip loop headers
            if bb.start_address in loop_headers:
                continue

            last_inst = bb.instructions[-1]

            # Look for conditional jumps
            if last_inst.inst_type == InstructionType.JUMP and last_inst.mnemonic.lower() != 'jmp':
                if len(bb.successors) >= 2:
                    # We have a conditional branch
                    true_target = bb.successors[0]  # Jump target
                    false_target = bb.successors[1]  # Fall through

                    conditionals.append({
                        'condition_block': bb.start_address,
                        'true_branch': true_target,
                        'false_branch': false_target,
                        'condition': self._extract_condition(bb)
                    })

        return conditionals

    def _extract_condition(self, bb: BasicBlock) -> str:
        """Extract condition from basic block"""
        if len(bb.instructions) < 2:
            return "/* unknown condition */"

        # Look for cmp/test followed by conditional jump
        compare_inst = None
        for inst in reversed(bb.instructions[:-1]):
            if inst.inst_type == InstructionType.COMPARE:
                compare_inst = inst
                break

        if not compare_inst:
            return "/* unknown condition */"

        last_inst = bb.instructions[-1]
        mnemonic = last_inst.mnemonic.lower()

        # Build condition based on jump type and comparison
        if compare_inst.mnemonic.lower() == 'cmp' and len(compare_inst.operands) == 2:
            left = compare_inst.operands[0].raw
            right = compare_inst.operands[1].raw

            condition_map = {
                'je': f"{left} == {right}",
                'jz': f"{left} == {right}",
                'jne': f"{left} != {right}",
                'jnz': f"{left} != {right}",
                'jg': f"{left} > {right}",
                'jl': f"{left} < {right}",
                'jge': f"{left} >= {right}",
                'jle': f"{left} <= {right}",
                'ja': f"(unsigned){left} > (unsigned){right}",
                'jb': f"(unsigned){left} < (unsigned){right}",
                'jae': f"(unsigned){left} >= (unsigned){right}",
                'jbe': f"(unsigned){left} <= (unsigned){right}",
            }

            return condition_map.get(mnemonic, f"/* {mnemonic} {left}, {right} */")

        elif compare_inst.mnemonic.lower() == 'test' and len(compare_inst.operands) == 2:
            left = compare_inst.operands[0].raw
            right = compare_inst.operands[1].raw

            if left == right:
                # test reg, reg checks if zero
                if mnemonic in ['jz', 'je']:
                    return f"{left} == 0"
                elif mnemonic in ['jnz', 'jne']:
                    return f"{left} != 0"

            return f"({left} & {right}) != 0"

        return f"/* {last_inst.raw_line} */"

    def _build_control_tree(self, func: Function, loops: List[Dict],
                           conditionals: List[Dict]) -> ControlStructure:
        """Build hierarchical control structure tree"""
        # For now, create a simple sequential structure
        # A full implementation would build a proper AST

        root = ControlStructure(
            type=ControlStructureType.SEQUENTIAL,
            start_address=func.start_address,
            end_address=func.end_address or func.start_address,
            blocks=func.basic_blocks
        )

        return root


class StructuredCodeGenerator:
    """Generates structured code from control flow analysis"""

    def __init__(self):
        self.indent_level = 0

    def generate(self, structure: ControlStructure) -> List[str]:
        """Generate structured code"""
        lines = []

        if structure.type == ControlStructureType.IF_THEN:
            lines.append(self._indent(f"if ({structure.condition}) {{"))
            self.indent_level += 1
            if structure.true_branch:
                lines.extend(self.generate(structure.true_branch))
            self.indent_level -= 1
            lines.append(self._indent("}"))

        elif structure.type == ControlStructureType.IF_THEN_ELSE:
            lines.append(self._indent(f"if ({structure.condition}) {{"))
            self.indent_level += 1
            if structure.true_branch:
                lines.extend(self.generate(structure.true_branch))
            self.indent_level -= 1
            lines.append(self._indent("} else {"))
            self.indent_level += 1
            if structure.false_branch:
                lines.extend(self.generate(structure.false_branch))
            self.indent_level -= 1
            lines.append(self._indent("}"))

        elif structure.type == ControlStructureType.WHILE_LOOP:
            lines.append(self._indent(f"while ({structure.condition}) {{"))
            self.indent_level += 1
            if structure.body:
                lines.extend(self.generate(structure.body))
            self.indent_level -= 1
            lines.append(self._indent("}"))

        elif structure.type == ControlStructureType.DO_WHILE_LOOP:
            lines.append(self._indent("do {"))
            self.indent_level += 1
            if structure.body:
                lines.extend(self.generate(structure.body))
            self.indent_level -= 1
            lines.append(self._indent(f"}} while ({structure.condition});"))

        elif structure.type == ControlStructureType.SEQUENTIAL:
            for child in structure.children:
                lines.extend(self.generate(child))

        return lines

    def _indent(self, line: str) -> str:
        """Add indentation to line"""
        return "    " * self.indent_level + line


if __name__ == "__main__":
    # Test
    print("Control Flow Analyzer module loaded")
