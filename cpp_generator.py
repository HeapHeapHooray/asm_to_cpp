"""
C++ Code Generator
Main generator that orchestrates the conversion process
"""

from typing import List, Dict, Set
from asm_parser import AssemblyParser, Function, BasicBlock
from instruction_converter import InstructionConverter
from control_flow_analyzer import ControlFlowAnalyzer, StructuredCodeGenerator


class CppGenerator:
    """Main C++ code generator"""

    def __init__(self):
        self.parser = AssemblyParser()
        self.inst_converter = InstructionConverter()
        self.cf_analyzer = ControlFlowAnalyzer()
        self.functions: List[Function] = []

    def parse_assembly(self, filepath: str):
        """Parse assembly file"""
        self.functions = self.parser.parse_file(filepath)
        return len(self.functions)

    def generate_function(self, func: Function) -> List[str]:
        """Generate C++ code for a single function"""
        lines = []

        # Function signature
        lines.append(f"// Function at 0x{func.start_address:08x}")
        lines.append(f"void {func.name}() {{")

        # Note: Registers are now global variables, not reset per function!
        # This is correct - register values persist between function calls

        # Convert instructions
        if func.basic_blocks:
            for bb in func.basic_blocks:
                # Add label if needed
                if bb.label:
                    lines.append(f"{bb.label}:")
                elif bb.start_address != func.start_address:
                    lines.append(f"loc_{bb.start_address:08x}:")

                # Convert each instruction
                for inst in bb.instructions:
                    cpp_lines = self.inst_converter.instruction_to_cpp(inst)
                    for cpp_line in cpp_lines:
                        # Add comment with original instruction
                        if not cpp_line.startswith("/*"):
                            comment = f" // {inst.raw_line}"
                        else:
                            comment = ""
                        lines.append(f"    {cpp_line}{comment}")

        lines.append("}")
        lines.append("")

        return lines

    def generate_all_functions(self) -> List[str]:
        """Generate C++ code for all functions"""
        lines = []

        # Header
        lines.extend(self._generate_header())

        # Generate each function
        for i, func in enumerate(self.functions):
            if i >= 100:  # Limit for testing
                lines.append(f"// ... {len(self.functions) - 100} more functions ...")
                break
            lines.extend(self.generate_function(func))

        return lines

    def _generate_header(self) -> List[str]:
        """Generate C++ header includes and declarations"""
        return [
            "#include <cstdint>",
            "#include <cmath>",
            "#include <algorithm>",
            "#include <windows.h>",
            "",
            "// Type definitions",
            "using uint8_t = unsigned char;",
            "using uint16_t = unsigned short;",
            "using uint32_t = unsigned int;",
            "using int8_t = signed char;",
            "using int16_t = signed short;",
            "using int32_t = signed int;",
            "",
            "// ============================================================================",
            "// GLOBAL CPU STATE",
            "// ============================================================================",
            "// IMPORTANT: Registers are GLOBAL and persist between function calls!",
            "// This matches actual x86 behavior where registers maintain their values.",
            "",
            "// General purpose registers (32-bit)",
            "uint32_t eax = 0;",
            "uint32_t ebx = 0;",
            "uint32_t ecx = 0;",
            "uint32_t edx = 0;",
            "uint32_t esi = 0;",
            "uint32_t edi = 0;",
            "uint32_t ebp = 0;",
            "uint32_t esp = 0x00100000;  // Stack starts at 1MB",
            "",
            "// SSE registers (128-bit, but we use float for simplicity)",
            "float xmm0 = 0.0f;",
            "float xmm1 = 0.0f;",
            "float xmm2 = 0.0f;",
            "float xmm3 = 0.0f;",
            "float xmm4 = 0.0f;",
            "float xmm5 = 0.0f;",
            "float xmm6 = 0.0f;",
            "float xmm7 = 0.0f;",
            "",
            "// CPU flags",
            "bool zero_flag = false;",
            "bool sign_flag = false;",
            "bool carry_flag = false;",
            "bool overflow_flag = false;",
            "",
            "// ============================================================================",
            "// MEMORY AND STACK SIMULATION",
            "// ============================================================================",
            "",
            "// FPU stack simulation",
            "float fpu_stack[8] = {0};",
            "int fpu_sp = 0;",
            "",
            "inline void fpu_push(float val) {",
            "    fpu_stack[fpu_sp++] = val;",
            "}",
            "",
            "inline float fpu_pop() {",
            "    return fpu_stack[--fpu_sp];",
            "}",
            "",
            "// Stack simulation (1MB stack)",
            "uint32_t stack[1024*1024];",
            "int stack_pointer = 1024*1024 - 1;",
            "",
            "inline void push(uint32_t val) {",
            "    stack[stack_pointer--] = val;",
            "}",
            "",
            "inline uint32_t pop() {",
            "    return stack[++stack_pointer];",
            "}",
            "",
            "// ============================================================================",
            "// HELPER FUNCTIONS",
            "// ============================================================================",
            "",
            "// Flag update helpers",
            "inline void flags_update(int32_t result) {",
            "    zero_flag = (result == 0);",
            "    sign_flag = (result < 0);",
            "    // Carry and overflow simplified",
            "}",
            "",
            "inline void flags_update_float(float result) {",
            "    zero_flag = (result == 0.0f);",
            "    sign_flag = (result < 0.0f);",
            "}",
            "",
            "// Min/Max helpers for SSE",
            "inline float min(float a, float b) { return (a < b) ? a : b; }",
            "inline float max(float a, float b) { return (a > b) ? a : b; }",
            "",
            "// ============================================================================",
            "// FUNCTION DECLARATIONS",
            "// ============================================================================",
            "",
        ]

    def write_cpp_file(self, output_path: str):
        """Write generated C++ to file"""
        lines = self.generate_all_functions()

        with open(output_path, 'w', encoding='utf-8') as f:
            for line in lines:
                f.write(line + '\n')

        return len(lines)


class HeaderGenerator:
    """Generates C++ header files for data structures and APIs"""

    def __init__(self):
        pass

    def generate_windows_api_headers(self) -> List[str]:
        """Generate Windows API function declarations"""
        return [
            "#ifndef WINDOWS_API_H",
            "#define WINDOWS_API_H",
            "",
            "#include <windows.h>",
            "",
            "// Common Windows API functions used in the game",
            "// These will be dynamically resolved or linked",
            "",
            "#endif // WINDOWS_API_H",
        ]

    def generate_data_structures(self, rdata_section: bytes, data_section: bytes) -> List[str]:
        """Generate C++ structures for data sections"""
        lines = [
            "#ifndef DATA_STRUCTURES_H",
            "#define DATA_STRUCTURES_H",
            "",
            "#include <cstdint>",
            "",
            "// Global data section",
            "namespace GameData {",
            "",
        ]

        # Add data section as byte arrays
        lines.append(f"    // .data section ({len(data_section)} bytes)")
        lines.append(f"    extern uint8_t data_section[{len(data_section)}];")
        lines.append("")
        lines.append(f"    // .rdata section ({len(rdata_section)} bytes)")
        lines.append(f"    extern uint8_t rdata_section[{len(rdata_section)}];")
        lines.append("")

        lines.extend([
            "}",
            "",
            "#endif // DATA_STRUCTURES_H",
        ])

        return lines


def main():
    """Main conversion function"""
    import sys
    import os

    if len(sys.argv) < 2:
        print("Usage: python cpp_generator.py <input.asm> [output.cpp]")
        print("Example: python cpp_generator.py ../hp_text_yasm.asm hp_text.cpp")
        return

    input_file = sys.argv[1]
    output_file = sys.argv[2] if len(sys.argv) > 2 else "output.cpp"

    if not os.path.exists(input_file):
        print(f"Error: Input file '{input_file}' not found")
        return

    print(f"Parsing assembly from: {input_file}")
    generator = CppGenerator()

    print("Parsing assembly...")
    num_functions = generator.parse_assembly(input_file)
    print(f"Found {num_functions} functions")
    print(f"Total instructions: {len(generator.parser.instructions)}")

    print(f"\nGenerating C++ code...")
    generator.write_cpp_file(output_file)

    print(f"C++ code written to: {output_file}")
    print(f"\nNote: The generated code is a semi-automated conversion.")
    print(f"      Manual review and cleanup will be required.")
    print(f"      Pay special attention to:")
    print(f"      - Function signatures and parameters")
    print(f"      - Memory access patterns")
    print(f"      - Control flow structures")
    print(f"      - Windows API calls")


if __name__ == "__main__":
    main()
