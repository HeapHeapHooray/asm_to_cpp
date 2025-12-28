#!/usr/bin/env python3
"""
Main Conversion Script
Orchestrates the full assembly to C++ conversion process
"""

import os
import sys
import argparse
from pathlib import Path
from cpp_generator import CppGenerator, HeaderGenerator


class MasterConverter:
    """Master converter that handles the entire conversion pipeline"""

    def __init__(self, project_dir: str):
        self.project_dir = Path(project_dir)
        self.output_dir = self.project_dir / "cpp_output"
        self.output_dir.mkdir(exist_ok=True)

    def convert_hp_executable(self):
        """Convert the entire HP executable"""
        print("=" * 70)
        print("HP.EXE Assembly to C++ Converter")
        print("=" * 70)
        print()

        # Define input files
        sections = [
            {
                'name': '.text',
                'asm_file': self.project_dir / 'hp_text_yasm.asm',
                'output_file': self.output_dir / 'hp_text.cpp',
                'description': 'Main code section'
            },
            {
                'name': 'HATRED',
                'asm_file': self.project_dir / 'hp_hatred_yasm.asm',
                'output_file': self.output_dir / 'hp_hatred.cpp',
                'description': 'HATRED code section'
            },
        ]

        # Convert each section
        for section in sections:
            self._convert_section(section)

        # Generate headers
        self._generate_headers()

        # Generate build files
        self._generate_build_files()

        print("\n" + "=" * 70)
        print("Conversion complete!")
        print(f"Output directory: {self.output_dir}")
        print("=" * 70)

    def _convert_section(self, section: dict):
        """Convert a single section"""
        print(f"\n[*] Converting {section['name']} section")
        print(f"    Description: {section['description']}")
        print(f"    Input: {section['asm_file'].name}")
        print(f"    Output: {section['output_file'].name}")

        if not section['asm_file'].exists():
            print(f"    [!] Warning: Input file not found, skipping...")
            return

        # Create generator
        generator = CppGenerator()

        # Parse assembly
        print(f"    [1/2] Parsing assembly...")
        try:
            num_functions = generator.parse_assembly(str(section['asm_file']))
            num_instructions = len(generator.parser.instructions)
            print(f"          Found {num_functions} functions, {num_instructions} instructions")
        except Exception as e:
            print(f"    [!] Error parsing: {e}")
            return

        # Generate C++
        print(f"    [2/2] Generating C++ code...")
        try:
            num_lines = generator.write_cpp_file(str(section['output_file']))
            print(f"          Generated {num_lines} lines of C++ code")
        except Exception as e:
            print(f"    [!] Error generating: {e}")
            return

        print(f"    [✓] Complete!")

    def _generate_headers(self):
        """Generate header files"""
        print(f"\n[*] Generating header files")

        header_gen = HeaderGenerator()

        # Windows API headers
        api_header = self.output_dir / "windows_api.h"
        print(f"    [1/3] Generating {api_header.name}...")
        with open(api_header, 'w') as f:
            f.write('\n'.join(header_gen.generate_windows_api_headers()))

        # Data structures
        data_header = self.output_dir / "data_structures.h"
        print(f"    [2/3] Generating {data_header.name}...")

        # Load binary sections
        rdata = self._load_binary_section('hp_rdata.bin')
        data = self._load_binary_section('hp_data.bin')

        with open(data_header, 'w') as f:
            f.write('\n'.join(header_gen.generate_data_structures(rdata, data)))

        # Main header
        main_header = self.output_dir / "hp.h"
        print(f"    [3/3] Generating {main_header.name}...")
        with open(main_header, 'w') as f:
            f.write(self._generate_main_header())

        print(f"    [✓] Headers generated!")

    def _load_binary_section(self, filename: str) -> bytes:
        """Load binary section data"""
        filepath = self.project_dir / filename
        if filepath.exists():
            with open(filepath, 'rb') as f:
                return f.read()
        return b''

    def _generate_main_header(self) -> str:
        """Generate main header file"""
        return """#ifndef HP_H
#define HP_H

#include <cstdint>
#include <cmath>
#include <algorithm>
#include <windows.h>

#include "windows_api.h"
#include "data_structures.h"

// Game engine typedefs
using byte = uint8_t;
using word = uint16_t;
using dword = uint32_t;

// Forward declarations of all functions
// (These will be filled in by analyzing the assembly)

#endif // HP_H
"""

    def _generate_build_files(self):
        """Generate build system files"""
        print(f"\n[*] Generating build files")

        # CMakeLists.txt
        cmake_file = self.output_dir / "CMakeLists.txt"
        print(f"    [1/2] Generating {cmake_file.name}...")
        with open(cmake_file, 'w') as f:
            f.write(self._generate_cmake())

        # README
        readme_file = self.output_dir / "README.md"
        print(f"    [2/2] Generating {readme_file.name}...")
        with open(readme_file, 'w') as f:
            f.write(self._generate_readme())

        print(f"    [✓] Build files generated!")

    def _generate_cmake(self) -> str:
        """Generate CMakeLists.txt"""
        return """cmake_minimum_required(VERSION 3.15)
project(HarryPotterOOTP CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    hp_text.cpp
    hp_hatred.cpp
)

# Headers
set(HEADERS
    hp.h
    windows_api.h
    data_structures.h
)

# Executable
add_executable(hp ${SOURCES} ${HEADERS})

# Link Windows libraries
if(WIN32)
    target_link_libraries(hp
        kernel32
        user32
        gdi32
        opengl32
    )
endif()

# Compiler warnings
if(MSVC)
    target_compile_options(hp PRIVATE /W3)
else()
    target_compile_options(hp PRIVATE -Wall -Wextra)
endif()
"""

    def _generate_readme(self) -> str:
        """Generate README"""
        return """# Harry Potter and the Order of the Phoenix - Decompiled

This is a semi-automated decompilation of HP.EXE to C++.

## Structure

- `hp_text.cpp` - Main code section (.text)
- `hp_hatred.cpp` - HATRED code section
- `hp.h` - Main header file
- `windows_api.h` - Windows API declarations
- `data_structures.h` - Data structure definitions

## Building

### Requirements
- CMake 3.15 or higher
- C++17 compatible compiler (MSVC, GCC, or Clang)
- Windows SDK (if building on Windows)

### Compilation

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Notes

This code is generated through semi-automated conversion and requires:

1. **Manual review and cleanup** - The converter does its best, but assembly-to-C++
   translation is not perfect.

2. **Function signature refinement** - Most functions are declared as `void func()`.
   You'll need to identify actual parameters and return types.

3. **Type inference** - Register and memory operations use generic types (uint32_t).
   Actual game structures need to be reverse-engineered.

4. **Windows API integration** - API calls need to be properly resolved and linked.

5. **Control flow simplification** - Some goto statements could be converted to
   higher-level constructs (if/while/for).

## Conversion Process

The code was generated using:
1. YASM-format assembly parser
2. x86 instruction to C++ converter
3. Control flow analyzer
4. C++ code generator

## License

This is a reverse-engineered educational project. Original game © EA Games.
"""


def main():
    """Main entry point"""
    parser = argparse.ArgumentParser(
        description='Convert HP.EXE assembly to C++',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Convert entire project
  python main_converter.py /path/to/Disassembly2

  # Convert single file
  python cpp_generator.py hp_text_yasm.asm output.cpp
        """
    )

    parser.add_argument(
        'project_dir',
        nargs='?',
        default='.',
        help='Project directory containing assembly files (default: current directory)'
    )

    args = parser.parse_args()

    # Verify directory exists
    project_path = Path(args.project_dir).resolve()
    if not project_path.exists():
        print(f"Error: Directory '{project_path}' does not exist")
        sys.exit(1)

    # Create converter and run
    converter = MasterConverter(str(project_path))
    converter.convert_hp_executable()


if __name__ == "__main__":
    main()
