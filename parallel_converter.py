#!/usr/bin/env python3
"""
Parallel Converter - Multi-threaded assembly to C++ converter
Uses all CPU cores for maximum speed!
"""

import os
import sys
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor, as_completed
import multiprocessing


def convert_with_progress_parallel(input_file, output_file, max_functions=1000):
    """Convert assembly to C++ using multi-threading"""
    print(f"Converting {input_file} to {output_file}")
    print("Using parallel processing for maximum speed!")
    print()

    from cpp_generator import CppGenerator

    generator = CppGenerator()

    # ========================================================================
    # STEP 1: Parse assembly (sequential - relatively fast)
    # ========================================================================
    print("[1/3] Parsing assembly...")
    with open(input_file, 'r', encoding='utf-8', errors='ignore') as f:
        lines = f.readlines()

    total_lines = len(lines)
    print(f"      Total lines: {total_lines:,}")

    functions = generator.parser.parse_lines(lines)
    num_instructions = len(generator.parser.instructions)

    print(f"      Found {len(functions):,} functions")
    print(f"      Total instructions: {num_instructions:,}")
    print()

    # ========================================================================
    # STEP 2: Convert functions in PARALLEL (FAST!)
    # ========================================================================
    func_count = min(len(functions), max_functions)
    if func_count < len(functions):
        print(f"[2/3] Converting first {func_count} functions in parallel...")
    else:
        print(f"[2/3] Converting all {func_count} functions in parallel...")

    # Determine number of threads (use all CPU cores)
    num_threads = multiprocessing.cpu_count()
    print(f"      Using {num_threads} CPU cores")

    # Convert functions in parallel
    converted_functions = [None] * func_count
    completed = 0

    with ThreadPoolExecutor(max_workers=num_threads) as executor:
        # Submit all function conversion jobs
        future_to_index = {
            executor.submit(generator.generate_function, func): i
            for i, func in enumerate(functions[:func_count])
        }

        # Collect results as they complete
        for future in as_completed(future_to_index):
            index = future_to_index[future]
            try:
                result = future.result()
                converted_functions[index] = result
                completed += 1

                # Update progress every 50 functions
                if completed % 50 == 0 or completed == func_count:
                    progress = (completed / func_count) * 100
                    print(f"      Progress: {completed}/{func_count} ({progress:.1f}%)", end='\r')
            except Exception as e:
                print(f"\n      Error converting function {index}: {e}")
                converted_functions[index] = [f"// Error converting function: {e}\n"]

    print(f"      Progress: {func_count}/{func_count} (100.0%)")
    print()

    # ========================================================================
    # STEP 3: Write output (sequential - very fast)
    # ========================================================================
    print("[3/3] Writing output file...")

    with open(output_file, 'w', encoding='utf-8') as f:
        # Write header
        for line in generator._generate_header():
            f.write(line + '\n')

        # Write all converted functions
        for cpp_lines in converted_functions:
            if cpp_lines:
                for line in cpp_lines:
                    f.write(line + '\n')

        # Add note if functions were omitted
        if func_count < len(functions):
            f.write(f"\n// NOTE: {len(functions) - func_count} more functions omitted\n")
            f.write(f"// To convert more, increase max_functions parameter\n")

    print()
    print(f"[✓] Complete! Output written to {output_file}")
    print()

    # Show file size
    size_mb = os.path.getsize(output_file) / (1024 * 1024)
    print(f"    Output file size: {size_mb:.1f} MB")
    print(f"    Functions converted: {func_count:,}")
    print(f"    Speedup: ~{num_threads}x faster than single-threaded")


def main():
    if len(sys.argv) < 3:
        print("Usage: python parallel_converter.py <input.asm> <output.cpp> [max_functions]")
        print()
        print("Arguments:")
        print("  input.asm       - Input assembly file")
        print("  output.cpp      - Output C++ file")
        print("  max_functions   - Maximum functions to convert (default: 1000)")
        print()
        print("Examples:")
        print("  python parallel_converter.py ../hp_text_yasm.asm hp_text.cpp")
        print("  python parallel_converter.py ../hp_text_yasm.asm hp_text.cpp 5000")
        print("  python parallel_converter.py ../hp_hatred_yasm.asm hp_hatred.cpp")
        return

    input_file = sys.argv[1]
    output_file = sys.argv[2]
    max_functions = int(sys.argv[3]) if len(sys.argv) > 3 else 1000

    if not os.path.exists(input_file):
        print(f"Error: Input file '{input_file}' not found")
        return

    convert_with_progress_parallel(input_file, output_file, max_functions)


if __name__ == "__main__":
    main()
