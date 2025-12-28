#!/usr/bin/env python3
"""
Quick Converter - Processes assembly with progress reporting
Optimized for large files
"""

import os
import sys
from pathlib import Path


def convert_with_progress(input_file, output_file):
    """Convert assembly to C++ with progress reporting"""
    print(f"Converting {input_file} to {output_file}")
    print("This may take 10-20 minutes for large files...")
    print()

    from cpp_generator import CppGenerator

    generator = CppGenerator()

    # Parse with progress
    print("[1/2] Parsing assembly...")
    with open(input_file, 'r', encoding='utf-8', errors='ignore') as f:
        lines = f.readlines()

    total_lines = len(lines)
    print(f"      Total lines: {total_lines:,}")

    functions = generator.parser.parse_lines(lines)
    num_instructions = len(generator.parser.instructions)

    print(f"      Found {len(functions):,} functions")
    print(f"      Total instructions: {num_instructions:,}")
    print()

    # Generate with progress
    print("[2/2] Generating C++ code...")

    with open(output_file, 'w', encoding='utf-8') as f:
        # Write header
        for line in generator._generate_header():
            f.write(line + '\n')

        # Process functions with progress
        func_count = min(len(functions), 1000)  # Limit for practical reasons
        if func_count < len(functions):
            print(f"      Processing first {func_count} functions (out of {len(functions)})")
        else:
            print(f"      Processing all {func_count} functions")

        for i, func in enumerate(functions[:func_count]):
            if i % 100 == 0:
                progress = (i / func_count) * 100
                print(f"      Progress: {i}/{func_count} ({progress:.1f}%)", end='\r')

            cpp_lines = generator.generate_function(func)
            for line in cpp_lines:
                f.write(line + '\n')

        print(f"      Progress: {func_count}/{func_count} (100.0%)")

        if func_count < len(functions):
            f.write(f"\n// NOTE: {len(functions) - func_count} more functions omitted\n")
            f.write(f"// To convert all functions, modify func_count limit in quick_converter.py\n")

    print()
    print(f"[✓] Complete! Output written to {output_file}")
    print()

    # Show file size
    size_mb = os.path.getsize(output_file) / (1024 * 1024)
    print(f"    Output file size: {size_mb:.1f} MB")


def main():
    if len(sys.argv) < 3:
        print("Usage: python quick_converter.py <input.asm> <output.cpp>")
        print()
        print("Examples:")
        print("  python quick_converter.py ../hp_text_yasm.asm hp_text.cpp")
        print("  python quick_converter.py ../hp_hatred_yasm.asm hp_hatred.cpp")
        return

    input_file = sys.argv[1]
    output_file = sys.argv[2]

    if not os.path.exists(input_file):
        print(f"Error: Input file '{input_file}' not found")
        return

    convert_with_progress(input_file, output_file)


if __name__ == "__main__":
    main()
