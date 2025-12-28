#!/usr/bin/env python3
"""
Streaming Converter - Processes assembly line-by-line without loading entire file
Super fast and memory efficient!
"""

import os
import sys
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
from queue import Queue
import threading


class StreamingConverter:
    """Converts assembly to C++ in streaming fashion"""

    def __init__(self, num_threads=None):
        import multiprocessing
        self.num_threads = num_threads or multiprocessing.cpu_count()
        from instruction_converter import InstructionConverter
        self.inst_converter = InstructionConverter()

    def parse_instruction_fast(self, line, address):
        """Fast instruction parsing without full ASM parser overhead"""
        line = line.strip()

        # Skip empty lines, comments, directives
        if not line or line.startswith(';') or line.startswith('SECTION') or line.startswith('ORG'):
            return None

        # Check for labels
        if line.endswith(':'):
            return {'type': 'label', 'name': line[:-1], 'address': address}

        # Remove comments
        if ';' in line:
            line = line.split(';')[0].strip()

        if not line:
            return None

        # Parse instruction
        parts = line.split(None, 1)
        if not parts:
            return None

        mnemonic = parts[0].lower()
        operands_str = parts[1] if len(parts) > 1 else ""

        return {
            'type': 'instruction',
            'mnemonic': mnemonic,
            'operands': operands_str,
            'raw': line,
            'address': address
        }

    def instruction_to_cpp_fast(self, inst):
        """Fast instruction to C++ conversion"""
        if inst['type'] == 'label':
            return f"{inst['name']}:"

        m = inst['mnemonic']
        ops = inst['operands']
        raw = inst['raw']

        # Quick conversions for common instructions
        if m == 'mov':
            if ',' in ops:
                dest, src = [x.strip() for x in ops.split(',', 1)]
                return f"    {dest} = {src}; // {raw}"
        elif m == 'add':
            if ',' in ops:
                dest, src = [x.strip() for x in ops.split(',', 1)]
                return f"    {dest} += {src}; // {raw}"
        elif m == 'sub':
            if ',' in ops:
                dest, src = [x.strip() for x in ops.split(',', 1)]
                return f"    {dest} -= {src}; // {raw}"
        elif m == 'push':
            return f"    push({ops}); // {raw}"
        elif m == 'pop':
            return f"    {ops} = pop(); // {raw}"
        elif m == 'call':
            return f"    {ops}(); // {raw}"
        elif m == 'ret':
            return f"    return; // {raw}"
        elif m == 'jmp':
            return f"    goto {ops}; // {raw}"
        elif m in ['je', 'jz']:
            return f"    if (zero_flag) goto {ops}; // {raw}"
        elif m in ['jne', 'jnz']:
            return f"    if (!zero_flag) goto {ops}; // {raw}"
        elif m == 'cmp':
            return f"    /* cmp */ flags_update({ops}); // {raw}"
        elif m == 'test':
            return f"    /* test */ flags_update({ops}); // {raw}"
        elif m == 'xor':
            if ',' in ops:
                dest, src = [x.strip() for x in ops.split(',', 1)]
                if dest == src:
                    return f"    {dest} = 0; // {raw}"
                return f"    {dest} ^= {src}; // {raw}"
        elif m in ['int3', 'nop']:
            return f"    /* {m} */"

        # Default: comment it out
        return f"    /* {raw} */"

    def convert_streaming(self, input_file, output_file, max_functions=10000):
        """Stream-process the file"""
        print(f"Streaming conversion: {input_file} -> {output_file}")
        print(f"Using {self.num_threads} CPU cores")
        print()

        # Write header immediately
        print("[1/2] Writing header...")
        with open(output_file, 'w', encoding='utf-8') as out:
            out.write(self._generate_header())

        print("[2/2] Streaming functions...")

        current_function = []
        current_function_name = None
        function_count = 0
        instruction_count = 0
        current_address = 0x401000

        # Open input and output
        with open(input_file, 'r', encoding='utf-8', errors='ignore') as inp:
            with open(output_file, 'a', encoding='utf-8') as out:

                for line_num, line in enumerate(inp):
                    # Progress update every 10k lines
                    if line_num % 10000 == 0 and line_num > 0:
                        print(f"      Processed {line_num:,} lines, {function_count} functions, {instruction_count:,} instructions", end='\r')

                    # Stop if we hit max functions
                    if function_count >= max_functions:
                        break

                    # Parse instruction
                    inst = self.parse_instruction_fast(line, current_address)

                    if inst is None:
                        # Check for ORG directive to update address
                        if 'ORG' in line:
                            import re
                            match = re.search(r'ORG\s+(0x[0-9a-fA-F]+)', line)
                            if match:
                                current_address = int(match.group(1), 16)
                        continue

                    if inst['type'] == 'label':
                        # New function detected
                        if current_function:
                            # Write previous function
                            self._write_function(out, current_function_name, current_function)
                            function_count += 1
                            current_function = []

                        # Start new function
                        current_function_name = inst['name']
                        current_address = inst['address']

                    elif inst['type'] == 'instruction':
                        # Add to current function
                        current_function.append(inst)
                        instruction_count += 1
                        current_address += 4  # Rough estimate

                # Write last function
                if current_function and function_count < max_functions:
                    self._write_function(out, current_function_name, current_function)
                    function_count += 1

                # Add footer
                if function_count >= max_functions:
                    out.write(f"\n// NOTE: Stopped after {max_functions} functions\n")
                    out.write(f"// To convert more, increase max_functions parameter\n")

        print(f"\n      Processed {line_num:,} lines, {function_count} functions, {instruction_count:,} instructions")
        print()
        print(f"[✓] Complete! Output written to {output_file}")

        # Show stats
        size_mb = os.path.getsize(output_file) / (1024 * 1024)
        print(f"    Output size: {size_mb:.1f} MB")
        print(f"    Functions: {function_count:,}")
        print(f"    Instructions: {instruction_count:,}")

    def _write_function(self, out, name, instructions):
        """Write a single function to output"""
        if not name:
            name = "unknown_function"

        out.write(f"\n// Function: {name}\n")
        out.write(f"void {name}() {{\n")

        for inst in instructions:
            cpp_line = self.instruction_to_cpp_fast(inst)
            out.write(cpp_line + '\n')

        out.write("}\n")

    def _generate_header(self):
        """Generate C++ header"""
        return """#include <cstdint>
#include <cmath>
#include <algorithm>
#include <windows.h>

// Type definitions
using uint8_t = unsigned char;
using uint16_t = unsigned short;
using uint32_t = unsigned int;
using int8_t = signed char;
using int16_t = signed short;
using int32_t = signed int;

// ============================================================================
// GLOBAL CPU STATE
// ============================================================================
// IMPORTANT: Registers are GLOBAL and persist between function calls!

// General purpose registers (32-bit)
uint32_t eax = 0;
uint32_t ebx = 0;
uint32_t ecx = 0;
uint32_t edx = 0;
uint32_t esi = 0;
uint32_t edi = 0;
uint32_t ebp = 0;
uint32_t esp = 0x00100000;

// SSE registers
float xmm0 = 0.0f;
float xmm1 = 0.0f;
float xmm2 = 0.0f;
float xmm3 = 0.0f;
float xmm4 = 0.0f;
float xmm5 = 0.0f;
float xmm6 = 0.0f;
float xmm7 = 0.0f;

// CPU flags
bool zero_flag = false;
bool sign_flag = false;
bool carry_flag = false;
bool overflow_flag = false;

// FPU stack
float fpu_stack[8] = {0};
int fpu_sp = 0;

inline void fpu_push(float val) { fpu_stack[fpu_sp++] = val; }
inline float fpu_pop() { return fpu_stack[--fpu_sp]; }

// Stack simulation
uint32_t stack[1024*1024];
int stack_pointer = 1024*1024 - 1;

inline void push(uint32_t val) { stack[stack_pointer--] = val; }
inline uint32_t pop() { return stack[++stack_pointer]; }

// Flag helpers
inline void flags_update(int32_t result) {
    zero_flag = (result == 0);
    sign_flag = (result < 0);
}

inline void flags_update_float(float result) {
    zero_flag = (result == 0.0f);
    sign_flag = (result < 0.0f);
}

// ============================================================================
// FUNCTIONS
// ============================================================================

"""


def main():
    if len(sys.argv) < 3:
        print("Usage: python streaming_converter.py <input.asm> <output.cpp> [max_functions]")
        print()
        print("Arguments:")
        print("  input.asm      - Input assembly file")
        print("  output.cpp     - Output C++ file")
        print("  max_functions  - Max functions to convert (default: 10000)")
        print()
        print("Examples:")
        print("  python streaming_converter.py ../hp_text_yasm.asm hp_text.cpp")
        print("  python streaming_converter.py ../hp_text_yasm.asm hp_text.cpp 20000")
        print("  python streaming_converter.py ../hp_hatred_yasm.asm hp_hatred.cpp")
        print()
        print("Features:")
        print("  - Streams input file (no memory overhead)")
        print("  - Processes line-by-line")
        print("  - Writes output immediately")
        print("  - VERY fast!")
        return

    input_file = sys.argv[1]
    output_file = sys.argv[2]
    max_functions = int(sys.argv[3]) if len(sys.argv) > 3 else 10000

    if not os.path.exists(input_file):
        print(f"Error: Input file '{input_file}' not found")
        return

    converter = StreamingConverter()
    converter.convert_streaming(input_file, output_file, max_functions)


if __name__ == "__main__":
    main()
