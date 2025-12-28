"""
x86 Instruction to C++ Converter
Translates x86 assembly instructions to C++ expressions
"""

from typing import List, Dict, Optional, Tuple
from asm_parser import Instruction, Operand, InstructionType


class RegisterState:
    """Tracks register usage and mapping to C++ variables"""
    def __init__(self):
        # Map registers to C++ variable names
        self.reg_to_var: Dict[str, str] = {}
        self.var_counter = 0

    def get_var(self, reg: str) -> str:
        """Get or create C++ variable for register"""
        reg = reg.lower()
        if reg not in self.reg_to_var:
            self.var_counter += 1
            self.reg_to_var[reg] = f"r_{reg}"
        return self.reg_to_var[reg]

    def reset(self):
        """Reset state"""
        self.reg_to_var.clear()
        self.var_counter = 0


class InstructionConverter:
    """Converts x86 instructions to C++"""

    def __init__(self):
        self.reg_state = RegisterState()
        self.stack_offset = 0
        self.local_vars: Dict[int, str] = {}  # offset -> variable name
        self.var_counter = 0

    def operand_to_cpp(self, op: Operand, size_hint: int = 4) -> str:
        """Convert operand to C++ expression"""
        if op.is_register:
            return self._register_to_cpp(op.raw)

        elif op.is_immediate:
            # Handle hex immediates
            if op.raw.startswith('0x'):
                return op.raw
            # Handle labels/function calls
            elif op.raw.startswith('loc_') or op.raw.startswith('sub_'):
                return f"/* {op.raw} */ 0x{op.raw.split('_')[1]}"
            elif op.raw.startswith('byte'):
                # Handle 'byte +0x8' format
                return op.raw.replace('byte ', '')
            else:
                return op.raw

        elif op.is_memory:
            return self._memory_to_cpp(op)

        return f"/* {op.raw} */"

    def _register_to_cpp(self, reg: str) -> str:
        """Convert register name to C++ variable"""
        reg = reg.lower()

        # Handle sub-registers (al, ah, ax, etc.)
        reg_map = {
            # 32-bit
            'eax': 'eax', 'ebx': 'ebx', 'ecx': 'ecx', 'edx': 'edx',
            'esi': 'esi', 'edi': 'edi', 'ebp': 'ebp', 'esp': 'esp',
            # 16-bit
            'ax': 'eax', 'bx': 'ebx', 'cx': 'ecx', 'dx': 'edx',
            'si': 'esi', 'di': 'edi', 'bp': 'ebp', 'sp': 'esp',
            # 8-bit
            'al': 'eax', 'ah': 'eax', 'bl': 'ebx', 'bh': 'ebx',
            'cl': 'ecx', 'ch': 'ecx', 'dl': 'edx', 'dh': 'edx',
            # SSE
            'xmm0': 'xmm0', 'xmm1': 'xmm1', 'xmm2': 'xmm2', 'xmm3': 'xmm3',
            'xmm4': 'xmm4', 'xmm5': 'xmm5', 'xmm6': 'xmm6', 'xmm7': 'xmm7',
        }

        base_reg = reg_map.get(reg, reg)

        # Handle sub-register access with casting
        if reg.endswith('l') and reg[:-1] in ['a', 'b', 'c', 'd']:
            return f"(uint8_t){base_reg}"
        elif reg.endswith('h') and reg[:-1] in ['a', 'b', 'c', 'd']:
            return f"(uint8_t)({base_reg} >> 8)"
        elif reg in ['ax', 'bx', 'cx', 'dx', 'si', 'di', 'bp', 'sp']:
            return f"(uint16_t){base_reg}"

        return base_reg

    def _memory_to_cpp(self, op: Operand) -> str:
        """Convert memory operand to C++ expression"""
        # Build the address expression
        parts = []

        if op.base_reg:
            parts.append(self._register_to_cpp(op.base_reg))

        if op.index_reg:
            if op.scale > 1:
                parts.append(f"{self._register_to_cpp(op.index_reg)} * {op.scale}")
            else:
                parts.append(self._register_to_cpp(op.index_reg))

        if op.displacement:
            if op.displacement >= 0:
                parts.append(f"0x{op.displacement:x}")
            else:
                parts.append(f"-0x{-op.displacement:x}")

        addr_expr = " + ".join(parts) if parts else "0"

        # Determine the type for dereferencing
        # This is a simplification - we'd need type analysis for accuracy
        return f"*(uint32_t*)({addr_expr})"

    def instruction_to_cpp(self, inst: Instruction) -> List[str]:
        """Convert instruction to C++ statements"""
        mnemonic = inst.mnemonic.lower()
        ops = inst.operands

        # Movement instructions
        if mnemonic == 'mov':
            if len(ops) == 2:
                dest = self.operand_to_cpp(ops[0])
                src = self.operand_to_cpp(ops[1])
                return [f"{dest} = {src};"]

        elif mnemonic == 'movss':
            if len(ops) == 2:
                dest = self.operand_to_cpp(ops[0])
                src = self.operand_to_cpp(ops[1])
                return [f"{dest} = {src}; // movss"]

        elif mnemonic == 'movaps':
            if len(ops) == 2:
                dest = self.operand_to_cpp(ops[0])
                src = self.operand_to_cpp(ops[1])
                return [f"{dest} = {src}; // movaps"]

        elif mnemonic == 'lea':
            if len(ops) == 2:
                dest = self.operand_to_cpp(ops[0])
                # For LEA, we want the address, not the value
                if ops[1].is_memory:
                    addr_parts = []
                    if ops[1].base_reg:
                        addr_parts.append(self._register_to_cpp(ops[1].base_reg))
                    if ops[1].index_reg:
                        if ops[1].scale > 1:
                            addr_parts.append(f"{self._register_to_cpp(ops[1].index_reg)} * {ops[1].scale}")
                        else:
                            addr_parts.append(self._register_to_cpp(ops[1].index_reg))
                    if ops[1].displacement:
                        if ops[1].displacement >= 0:
                            addr_parts.append(f"0x{ops[1].displacement:x}")
                        else:
                            addr_parts.append(f"-0x{-ops[1].displacement:x}")
                    addr_expr = " + ".join(addr_parts)
                    return [f"{dest} = {addr_expr};"]

        # Arithmetic instructions
        elif mnemonic == 'add':
            if len(ops) == 2:
                dest = self.operand_to_cpp(ops[0])
                src = self.operand_to_cpp(ops[1])
                return [f"{dest} += {src};"]

        elif mnemonic == 'sub':
            if len(ops) == 2:
                dest = self.operand_to_cpp(ops[0])
                src = self.operand_to_cpp(ops[1])
                return [f"{dest} -= {src};"]

        elif mnemonic in ['imul', 'mul']:
            if len(ops) == 2:
                dest = self.operand_to_cpp(ops[0])
                src = self.operand_to_cpp(ops[1])
                return [f"{dest} *= {src};"]
            elif len(ops) == 3:
                dest = self.operand_to_cpp(ops[0])
                src1 = self.operand_to_cpp(ops[1])
                src2 = self.operand_to_cpp(ops[2])
                return [f"{dest} = {src1} * {src2};"]

        elif mnemonic == 'inc':
            if len(ops) == 1:
                dest = self.operand_to_cpp(ops[0])
                return [f"{dest}++;"]

        elif mnemonic == 'dec':
            if len(ops) == 1:
                dest = self.operand_to_cpp(ops[0])
                return [f"{dest}--;"]

        # Logical instructions
        elif mnemonic == 'and':
            if len(ops) == 2:
                dest = self.operand_to_cpp(ops[0])
                src = self.operand_to_cpp(ops[1])
                return [f"{dest} &= {src};"]

        elif mnemonic == 'or':
            if len(ops) == 2:
                dest = self.operand_to_cpp(ops[0])
                src = self.operand_to_cpp(ops[1])
                return [f"{dest} |= {src};"]

        elif mnemonic == 'xor':
            if len(ops) == 2:
                dest = self.operand_to_cpp(ops[0])
                src = self.operand_to_cpp(ops[1])
                # Common idiom: xor reg, reg = zero register
                if ops[0].raw == ops[1].raw:
                    return [f"{dest} = 0;"]
                return [f"{dest} ^= {src};"]

        elif mnemonic == 'not':
            if len(ops) == 1:
                dest = self.operand_to_cpp(ops[0])
                return [f"{dest} = ~{dest};"]

        elif mnemonic in ['shl', 'sal']:
            if len(ops) == 2:
                dest = self.operand_to_cpp(ops[0])
                src = self.operand_to_cpp(ops[1])
                return [f"{dest} <<= {src};"]

        elif mnemonic in ['shr', 'sar']:
            if len(ops) == 2:
                dest = self.operand_to_cpp(ops[0])
                src = self.operand_to_cpp(ops[1])
                return [f"{dest} >>= {src};"]

        # Stack instructions
        elif mnemonic == 'push':
            if len(ops) == 1:
                src = self.operand_to_cpp(ops[0])
                return [f"push({src});"]

        elif mnemonic == 'pop':
            if len(ops) == 1:
                dest = self.operand_to_cpp(ops[0])
                return [f"{dest} = pop();"]

        # Comparison instructions
        elif mnemonic == 'cmp':
            if len(ops) == 2:
                op1 = self.operand_to_cpp(ops[0])
                op2 = self.operand_to_cpp(ops[1])
                return [f"/* cmp */ flags_update({op1} - {op2});"]

        elif mnemonic == 'test':
            if len(ops) == 2:
                op1 = self.operand_to_cpp(ops[0])
                op2 = self.operand_to_cpp(ops[1])
                return [f"/* test */ flags_update({op1} & {op2});"]

        # Jump instructions
        elif mnemonic == 'jmp':
            if len(ops) == 1:
                target = ops[0].raw
                return [f"goto {target};"]

        elif mnemonic in ['je', 'jz']:
            if len(ops) == 1:
                target = ops[0].raw
                return [f"if (zero_flag) goto {target};"]

        elif mnemonic in ['jne', 'jnz']:
            if len(ops) == 1:
                target = ops[0].raw
                return [f"if (!zero_flag) goto {target};"]

        elif mnemonic == 'jg':
            if len(ops) == 1:
                target = ops[0].raw
                return [f"if (!zero_flag && sign_flag == overflow_flag) goto {target};"]

        elif mnemonic == 'jl':
            if len(ops) == 1:
                target = ops[0].raw
                return [f"if (sign_flag != overflow_flag) goto {target};"]

        elif mnemonic == 'jge':
            if len(ops) == 1:
                target = ops[0].raw
                return [f"if (sign_flag == overflow_flag) goto {target};"]

        elif mnemonic == 'jle':
            if len(ops) == 1:
                target = ops[0].raw
                return [f"if (zero_flag || sign_flag != overflow_flag) goto {target};"]

        elif mnemonic == 'ja':
            if len(ops) == 1:
                target = ops[0].raw
                return [f"if (!carry_flag && !zero_flag) goto {target};"]

        elif mnemonic == 'jb':
            if len(ops) == 1:
                target = ops[0].raw
                return [f"if (carry_flag) goto {target};"]

        elif mnemonic in ['js', 'jns']:
            if len(ops) == 1:
                target = ops[0].raw
                cond = "sign_flag" if mnemonic == 'js' else "!sign_flag"
                return [f"if ({cond}) goto {target};"]

        # Call/Return
        elif mnemonic == 'call':
            if len(ops) == 1:
                target = ops[0].raw
                if target.startswith('loc_') or target.startswith('sub_'):
                    return [f"/* call */ {target}();"]
                else:
                    target_cpp = self.operand_to_cpp(ops[0])
                    return [f"/* call */ ((void(*)()){target_cpp})();"]

        elif mnemonic == 'ret' or mnemonic == 'retn':
            return ["return;"]

        # FPU instructions
        elif mnemonic == 'fld':
            if len(ops) == 1:
                src = self.operand_to_cpp(ops[0])
                return [f"fpu_push({src});"]

        elif mnemonic == 'fstp':
            if len(ops) == 1:
                dest = self.operand_to_cpp(ops[0])
                return [f"{dest} = fpu_pop();"]

        elif mnemonic == 'fadd':
            return ["fpu_st0 += fpu_st1;"]

        elif mnemonic == 'fsub':
            return ["fpu_st0 -= fpu_st1;"]

        elif mnemonic == 'fmul':
            return ["fpu_st0 *= fpu_st1;"]

        elif mnemonic == 'fdiv':
            return ["fpu_st0 /= fpu_st1;"]

        elif mnemonic == 'fsqrt':
            return ["fpu_st0 = sqrt(fpu_st0);"]

        # SSE instructions
        elif mnemonic == 'addss':
            if len(ops) == 2:
                dest = self.operand_to_cpp(ops[0])
                src = self.operand_to_cpp(ops[1])
                return [f"{dest} += {src}; // addss"]

        elif mnemonic == 'subss':
            if len(ops) == 2:
                dest = self.operand_to_cpp(ops[0])
                src = self.operand_to_cpp(ops[1])
                return [f"{dest} -= {src}; // subss"]

        elif mnemonic == 'mulss':
            if len(ops) == 2:
                dest = self.operand_to_cpp(ops[0])
                src = self.operand_to_cpp(ops[1])
                return [f"{dest} *= {src}; // mulss"]

        elif mnemonic == 'divss':
            if len(ops) == 2:
                dest = self.operand_to_cpp(ops[0])
                src = self.operand_to_cpp(ops[1])
                return [f"{dest} /= {src}; // divss"]

        elif mnemonic == 'xorps':
            if len(ops) == 2:
                dest = self.operand_to_cpp(ops[0])
                src = self.operand_to_cpp(ops[1])
                if ops[0].raw == ops[1].raw:
                    return [f"{dest} = 0.0f; // xorps (zero)"]
                return [f"/* xorps */ {dest} ^= {src};"]

        elif mnemonic == 'cvttss2si':
            if len(ops) == 2:
                dest = self.operand_to_cpp(ops[0])
                src = self.operand_to_cpp(ops[1])
                return [f"{dest} = (int32_t){src}; // cvttss2si"]

        elif mnemonic == 'cvtsi2ss':
            if len(ops) == 2:
                dest = self.operand_to_cpp(ops[0])
                src = self.operand_to_cpp(ops[1])
                return [f"{dest} = (float){src}; // cvtsi2ss"]

        elif mnemonic == 'ucomiss':
            if len(ops) == 2:
                op1 = self.operand_to_cpp(ops[0])
                op2 = self.operand_to_cpp(ops[1])
                return [f"/* ucomiss */ flags_update_float({op1} - {op2});"]

        elif mnemonic == 'minss':
            if len(ops) == 2:
                dest = self.operand_to_cpp(ops[0])
                src = self.operand_to_cpp(ops[1])
                return [f"{dest} = min({dest}, {src}); // minss"]

        elif mnemonic == 'maxss':
            if len(ops) == 2:
                dest = self.operand_to_cpp(ops[0])
                src = self.operand_to_cpp(ops[1])
                return [f"{dest} = max({dest}, {src}); // maxss"]

        # Special/other instructions
        elif mnemonic == 'nop' or mnemonic == 'int3':
            return [f"/* {mnemonic} */"]

        elif mnemonic == 'lahf':
            return ["ah = (uint8_t)flags;"]

        # Default: emit as comment
        return [f"/* {inst.raw_line} */"]


if __name__ == "__main__":
    # Test
    from asm_parser import AssemblyParser

    test_asm = """
    loc_00000010:
        push ebp
        mov ebp,esp
        sub esp,byte +0x10
        mov eax,[ebp+0x8]
        add eax,0x5
        ret
    """

    parser = AssemblyParser()
    functions = parser.parse_lines(test_asm.split('\n'))

    converter = InstructionConverter()
    if functions and functions[0].basic_blocks:
        for inst in functions[0].basic_blocks[0].instructions:
            cpp_lines = converter.instruction_to_cpp(inst)
            for line in cpp_lines:
                print(f"  {line}")
