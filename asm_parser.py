"""
Assembly Parser for YASM x86 format
Parses assembly files and creates an intermediate representation
"""

import re
from dataclasses import dataclass, field
from typing import List, Dict, Optional, Set
from enum import Enum


class InstructionType(Enum):
    ARITHMETIC = "arithmetic"
    LOGIC = "logic"
    MOVE = "move"
    JUMP = "jump"
    CALL = "call"
    RETURN = "return"
    STACK = "stack"
    COMPARE = "compare"
    FPU = "fpu"
    SSE = "sse"
    OTHER = "other"


@dataclass
class Operand:
    """Represents an assembly operand"""
    raw: str
    is_memory: bool = False
    is_immediate: bool = False
    is_register: bool = False
    base_reg: Optional[str] = None
    index_reg: Optional[str] = None
    displacement: Optional[int] = None
    scale: int = 1

    def __post_init__(self):
        self._parse()

    def _parse(self):
        """Parse operand string"""
        s = self.raw.strip()

        # Check for memory operands [...]
        if s.startswith('[') and s.endswith(']'):
            self.is_memory = True
            self._parse_memory(s[1:-1])
        # Check for immediate values (hex or decimal)
        elif s.startswith('0x') or s.startswith('-0x') or (s.startswith('byte') and '+' in s):
            self.is_immediate = True
        # Check if it's a label/function call
        elif s.startswith('loc_') or s.startswith('sub_'):
            self.is_immediate = True
        # Otherwise it's a register
        else:
            self.is_register = True

    def _parse_memory(self, content: str):
        """Parse memory operand like 'esp+0x4' or 'eax*4+ebx+0x10'"""
        # Handle dword/byte/word prefixes
        for prefix in ['dword ', 'byte ', 'word ', 'qword ']:
            if content.startswith(prefix):
                content = content[len(prefix):]
                break

        # Simple patterns
        if '+' not in content and '*' not in content and '-' not in content:
            self.base_reg = content
            return

        # Parse complex addressing
        parts = re.split(r'([+\-])', content)
        for i, part in enumerate(parts):
            part = part.strip()
            if not part or part in ['+', '-']:
                continue

            if '*' in part:
                # Index with scale
                reg, scale = part.split('*')
                self.index_reg = reg.strip()
                self.scale = int(scale.strip())
            elif part.startswith('0x') or part.lstrip('-').isdigit():
                # Displacement
                sign = -1 if i > 0 and parts[i-1] == '-' else 1
                self.displacement = sign * int(part, 16 if part.startswith('0x') else 10)
            else:
                # Register
                if self.base_reg is None:
                    self.base_reg = part
                elif self.index_reg is None:
                    self.index_reg = part


@dataclass
class Instruction:
    """Represents a single assembly instruction"""
    address: int
    mnemonic: str
    operands: List[Operand]
    raw_line: str
    comment: str = ""
    inst_type: InstructionType = InstructionType.OTHER

    def __post_init__(self):
        self._classify()

    def _classify(self):
        """Classify instruction type"""
        m = self.mnemonic.lower()

        if m in ['add', 'sub', 'mul', 'imul', 'div', 'idiv', 'inc', 'dec', 'neg']:
            self.inst_type = InstructionType.ARITHMETIC
        elif m in ['and', 'or', 'xor', 'not', 'shl', 'shr', 'sal', 'sar', 'rol', 'ror']:
            self.inst_type = InstructionType.LOGIC
        elif m in ['mov', 'movss', 'movaps', 'movzx', 'movsx', 'lea']:
            self.inst_type = InstructionType.MOVE
        elif m in ['jmp', 'je', 'jz', 'jne', 'jnz', 'jg', 'jl', 'jge', 'jle', 'ja', 'jb', 'jae', 'jbe', 'js', 'jns', 'jpe', 'jpo']:
            self.inst_type = InstructionType.JUMP
        elif m in ['call']:
            self.inst_type = InstructionType.CALL
        elif m in ['ret', 'retn']:
            self.inst_type = InstructionType.RETURN
        elif m in ['push', 'pop']:
            self.inst_type = InstructionType.STACK
        elif m in ['cmp', 'test', 'ucomiss']:
            self.inst_type = InstructionType.COMPARE
        elif m.startswith('f') and m not in ['fld', 'fstp', 'fst']:
            self.inst_type = InstructionType.FPU
        elif m.startswith('xmm') or 'ss' in m or 'ps' in m:
            self.inst_type = InstructionType.SSE


@dataclass
class BasicBlock:
    """Represents a basic block of instructions"""
    start_address: int
    end_address: int
    label: Optional[str] = None
    instructions: List[Instruction] = field(default_factory=list)
    successors: List[int] = field(default_factory=list)
    predecessors: List[int] = field(default_factory=list)


@dataclass
class Function:
    """Represents a function"""
    start_address: int
    end_address: Optional[int] = None
    name: str = ""
    calling_conv: str = "cdecl"  # cdecl, stdcall, fastcall, thiscall
    basic_blocks: List[BasicBlock] = field(default_factory=list)
    local_vars: Dict[str, str] = field(default_factory=dict)
    returns: bool = True


class AssemblyParser:
    """Main parser for assembly files"""

    def __init__(self):
        self.functions: Dict[int, Function] = {}
        self.labels: Dict[str, int] = {}
        self.instructions: List[Instruction] = []
        self.current_address = 0

    def parse_file(self, filepath: str) -> List[Function]:
        """Parse an assembly file"""
        with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
            lines = f.readlines()

        return self.parse_lines(lines)

    def parse_lines(self, lines: List[str]) -> List[Function]:
        """Parse assembly lines"""
        current_address = 0x00401000  # Default .text base

        for line in lines:
            line = line.strip()

            # Skip empty lines and section directives
            if not line or line.startswith(';') or line.startswith('SECTION') or line.startswith('ORG'):
                if line.startswith('ORG'):
                    # Extract base address
                    match = re.search(r'ORG\s+(0x[0-9a-fA-F]+)', line)
                    if match:
                        current_address = int(match.group(1), 16)
                continue

            # Check for labels
            if line.endswith(':'):
                label = line[:-1]
                self.labels[label] = current_address
                continue

            # Parse instruction
            inst = self._parse_instruction(line, current_address)
            if inst:
                self.instructions.append(inst)
                # Estimate instruction size (rough approximation)
                current_address += self._estimate_instruction_size(inst)

        # Build functions from instructions
        self._identify_functions()

        return list(self.functions.values())

    def _parse_instruction(self, line: str, address: int) -> Optional[Instruction]:
        """Parse a single instruction line"""
        # Remove comments
        if ';' in line:
            line, comment = line.split(';', 1)
            comment = comment.strip()
        else:
            comment = ""

        line = line.strip()
        if not line:
            return None

        # Split mnemonic and operands
        parts = line.split(None, 1)
        if not parts:
            return None

        mnemonic = parts[0]
        operands_str = parts[1] if len(parts) > 1 else ""

        # Parse operands
        operands = []
        if operands_str:
            # Split by comma, but respect brackets
            op_parts = []
            current = ""
            depth = 0
            for char in operands_str:
                if char == '[':
                    depth += 1
                elif char == ']':
                    depth -= 1
                elif char == ',' and depth == 0:
                    op_parts.append(current.strip())
                    current = ""
                    continue
                current += char
            if current:
                op_parts.append(current.strip())

            operands = [Operand(op) for op in op_parts if op]

        return Instruction(
            address=address,
            mnemonic=mnemonic,
            operands=operands,
            raw_line=line,
            comment=comment
        )

    def _estimate_instruction_size(self, inst: Instruction) -> int:
        """Rough estimate of instruction size in bytes"""
        # This is a simplification
        base_size = 1

        # Mnemonic size
        if inst.mnemonic in ['movss', 'movaps', 'ucomiss']:
            base_size = 4
        elif inst.mnemonic.startswith('j'):
            base_size = 2
        elif inst.mnemonic in ['call']:
            base_size = 5
        else:
            base_size = 2

        # Add for operands
        for op in inst.operands:
            if op.is_memory:
                base_size += 2
            elif op.is_immediate:
                base_size += 4

        return base_size

    def _identify_functions(self):
        """Identify function boundaries"""
        if not self.instructions:
            return

        # Simple heuristic: functions start at labels and end at ret/jmp
        function_starts = set()

        # Add all call targets as function starts
        for inst in self.instructions:
            if inst.inst_type == InstructionType.CALL:
                if inst.operands and inst.operands[0].raw.startswith('loc_'):
                    label = inst.operands[0].raw
                    if label in self.labels:
                        function_starts.add(self.labels[label])

        # Add all labels as potential function starts
        for label, addr in self.labels.items():
            if label.startswith('loc_'):
                function_starts.add(addr)

        # Sort and create functions
        function_starts = sorted(function_starts)

        for i, start in enumerate(function_starts):
            # Find end (next function or end of code)
            end = function_starts[i + 1] if i + 1 < len(function_starts) else self.instructions[-1].address

            func = Function(
                start_address=start,
                end_address=end,
                name=f"sub_{start:08x}"
            )

            # Add instructions to function
            func_insts = [inst for inst in self.instructions
                         if start <= inst.address < end]

            if func_insts:
                bb = BasicBlock(start_address=start, end_address=end)
                bb.instructions = func_insts
                func.basic_blocks.append(bb)

            self.functions[start] = func


if __name__ == "__main__":
    import sys
    if len(sys.argv) > 1:
        parser = AssemblyParser()
        functions = parser.parse_file(sys.argv[1])
        print(f"Parsed {len(functions)} functions")
        print(f"Total instructions: {len(parser.instructions)}")
        if functions:
            print(f"\nFirst few functions:")
            for func in functions[:5]:
                print(f"  {func.name} @ 0x{func.start_address:08x} ({len(func.basic_blocks[0].instructions) if func.basic_blocks else 0} instructions)")
