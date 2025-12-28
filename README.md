# Assembly to C++ Conversion Toolchain

A comprehensive semi-automated toolchain for converting x86 assembly (YASM format) to C++ code.

## Overview

This toolchain consists of several Python modules that work together to parse assembly code, analyze control flow, and generate readable C++ code.

## Components

### 1. `asm_parser.py` - Assembly Parser
- Parses YASM-format x86 assembly files
- Identifies functions, basic blocks, and labels
- Creates an intermediate representation (IR) of the code
- Extracts instruction information (operands, types, addresses)

**Features:**
- Supports standard x86 instruction set
- Handles memory operands with complex addressing modes
- Identifies function boundaries
- Tracks labels and control flow targets

### 2. `instruction_converter.py` - Instruction Converter
- Converts individual x86 instructions to C++ expressions
- Handles arithmetic, logical, movement, and control flow instructions
- Supports FPU and SSE instructions
- Manages register-to-variable mapping

**Supported Instructions:**
- Data movement: `mov`, `lea`, `movss`, `movaps`
- Arithmetic: `add`, `sub`, `mul`, `imul`, `inc`, `dec`
- Logical: `and`, `or`, `xor`, `not`, `shl`, `shr`
- Stack: `push`, `pop`
- Control flow: `jmp`, `je`, `jne`, `jg`, `jl`, `call`, `ret`
- Comparison: `cmp`, `test`, `ucomiss`
- FPU: `fld`, `fstp`, `fadd`, `fsub`, `fmul`, `fdiv`, `fsqrt`
- SSE: `addss`, `subss`, `mulss`, `divss`, `minss`, `maxss`, `cvttss2si`, `cvtsi2ss`

### 3. `control_flow_analyzer.py` - Control Flow Analyzer
- Builds control flow graphs (CFG)
- Identifies loops (while, do-while, for)
- Detects conditional structures (if-then-else)
- Analyzes dominance relationships
- Reconstructs high-level control structures

**Analysis Features:**
- Back-edge detection for loop identification
- Conditional branch analysis
- Loop type classification
- Control structure tree generation

### 4. `cpp_generator.py` - C++ Code Generator
- Orchestrates the conversion process
- Generates complete C++ source files
- Creates helper functions for stack/FPU simulation
- Produces header files for data structures
- Generates Windows API wrapper headers

**Output Features:**
- Well-commented C++ code
- Original assembly as inline comments
- Register declarations
- Flag simulation
- Stack and FPU emulation helpers

### 5. `main_converter.py` - Main Conversion Script
- Entry point for the entire conversion pipeline
- Batch processes multiple assembly files
- Generates project structure
- Creates build system files (CMake)
- Produces comprehensive documentation

## Usage

### Convert Entire Project

```bash
cd /path/to/Disassembly2
python asm_to_cpp/main_converter.py .
```

This will:
1. Parse all assembly files (hp_text_yasm.asm, hp_hatred_yasm.asm)
2. Convert them to C++ (hp_text.cpp, hp_hatred.cpp)
3. Generate headers (hp.h, windows_api.h, data_structures.h)
4. Create build files (CMakeLists.txt)
5. Output everything to `cpp_output/` directory

### Convert Single File

```bash
python asm_to_cpp/cpp_generator.py hp_text_yasm.asm output.cpp
```

### Test Parser Only

```bash
python asm_to_cpp/asm_parser.py hp_text_yasm.asm
```

## Directory Structure

```
asm_to_cpp/
├── README.md                    # This file
├── asm_parser.py               # Assembly parser module
├── instruction_converter.py    # Instruction converter module
├── control_flow_analyzer.py    # Control flow analyzer module
├── cpp_generator.py            # C++ generator module
└── main_converter.py           # Main conversion script

cpp_output/                     # Generated output (created by converter)
├── hp_text.cpp                 # Converted .text section
├── hp_hatred.cpp               # Converted HATRED section
├── hp.h                        # Main header
├── windows_api.h               # Windows API declarations
├── data_structures.h           # Data structures
├── CMakeLists.txt              # Build configuration
└── README.md                   # Build instructions
```

## Conversion Process

The conversion follows these steps:

1. **Parse Assembly**
   - Read assembly file
   - Tokenize instructions
   - Build instruction list
   - Identify labels and function boundaries

2. **Analyze Control Flow**
   - Build control flow graph
   - Identify basic blocks
   - Detect loops and conditionals
   - Create structure tree

3. **Convert Instructions**
   - Map registers to variables
   - Convert each instruction to C++
   - Handle memory addressing
   - Preserve semantics

4. **Generate C++ Code**
   - Write function declarations
   - Add register/flag declarations
   - Emit converted instructions
   - Add comments and annotations

5. **Create Project Structure**
   - Generate headers
   - Create build files
   - Write documentation

## Limitations and Considerations

### Current Limitations

1. **Function Signatures** - All functions generated as `void func()`. Manual analysis needed for:
   - Parameter types and count
   - Return values
   - Calling conventions (cdecl, stdcall, fastcall, thiscall)

2. **Type Inference** - Generic types used (uint32_t). Needs refinement for:
   - Custom game structures
   - Pointer types
   - Class hierarchies

3. **Memory Access** - Simplified as pointer dereferences. May need:
   - Proper struct member access
   - Array indexing
   - Object-oriented patterns

4. **Control Flow** - Some goto statements could be:
   - Converted to while/for loops
   - Simplified to if-else
   - Restructured for readability

5. **Windows API** - Calls need:
   - Proper function signatures
   - Parameter marshaling
   - Dynamic linking setup

### Manual Cleanup Required

After conversion, you should:

1. **Review Generated Code**
   - Check for logical errors
   - Verify instruction semantics
   - Test edge cases

2. **Refine Function Signatures**
   - Identify parameters (look at stack access patterns)
   - Determine return types (look at eax usage)
   - Add appropriate type declarations

3. **Extract Data Structures**
   - Identify struct member access patterns
   - Define classes and structs
   - Replace pointer arithmetic with member access

4. **Simplify Control Flow**
   - Replace goto with structured constructs where possible
   - Identify loop invariants
   - Extract repeated patterns into functions

5. **Add High-Level Context**
   - Name variables meaningfully
   - Add descriptive comments
   - Document function purposes
   - Explain complex algorithms

## Advanced Usage

### Customizing the Converter

You can modify the conversion behavior by editing:

- `instruction_converter.py` - Add support for new instructions or change conversion patterns
- `control_flow_analyzer.py` - Improve loop/conditional detection
- `cpp_generator.py` - Modify output format, add optimizations

### Batch Processing

To process multiple files in parallel:

```python
from main_converter import MasterConverter

converter = MasterConverter('/path/to/project')
converter.convert_hp_executable()
```

### Extending Instruction Support

Add new instruction patterns in `instruction_converter.py`:

```python
elif mnemonic == 'new_instruction':
    if len(ops) == 2:
        dest = self.operand_to_cpp(ops[0])
        src = self.operand_to_cpp(ops[1])
        return [f"{dest} = custom_operation({src});"]
```

## Performance

Conversion performance (approximate):

- **Parsing**: ~50,000 instructions/second
- **Analysis**: ~30,000 instructions/second
- **Generation**: ~100,000 lines/second

Expected times for HP.EXE:
- .text section (3.8M instructions): ~2-3 minutes
- HATRED section (330K instructions): ~15-30 seconds
- Total: ~3-5 minutes

## Requirements

- Python 3.7 or higher
- No external dependencies (uses only standard library)

## Examples

### Example 1: Simple Function

Assembly:
```asm
loc_00401010:
    push ebp
    mov ebp,esp
    mov eax,[ebp+0x8]
    add eax,0x5
    pop ebp
    ret
```

Generated C++:
```cpp
void sub_00401010() {
    uint32_t eax = 0, ebp = 0, esp = 0;

    push(ebp);              // push ebp
    ebp = esp;              // mov ebp,esp
    eax = *(uint32_t*)(ebp + 0x8);  // mov eax,[ebp+0x8]
    eax += 0x5;             // add eax,0x5
    ebp = pop();            // pop ebp
    return;                 // ret
}
```

### Example 2: Conditional Branch

Assembly:
```asm
    cmp eax,0x10
    jl loc_00401020
    mov ebx,0x1
    jmp loc_00401030
loc_00401020:
    mov ebx,0x0
loc_00401030:
    ret
```

Generated C++:
```cpp
/* cmp */ flags_update(eax - 0x10);
if (sign_flag != overflow_flag) goto loc_00401020;
ebx = 0x1;
goto loc_00401030;

loc_00401020:
ebx = 0x0;

loc_00401030:
return;
```

## Troubleshooting

### Common Issues

1. **"File not found" errors**
   - Ensure you're in the correct directory
   - Check that assembly files exist
   - Verify file paths in commands

2. **Parse errors**
   - Some custom assembly syntax may not be supported
   - Check for malformed instructions
   - Verify assembly format is YASM-compatible

3. **Large output files**
   - Generated C++ can be very large (100MB+)
   - Ensure sufficient disk space
   - Consider splitting into smaller files

## Future Improvements

Potential enhancements:

- [ ] Better type inference using dataflow analysis
- [ ] Automatic function signature detection
- [ ] Structure recovery from memory access patterns
- [ ] Dead code elimination
- [ ] Constant propagation
- [ ] Expression simplification
- [ ] Better control flow structuring
- [ ] Direct compilation to executable
- [ ] Interactive mode for manual annotations
- [ ] Integration with decompilers (Ghidra, IDA)

## Contributing

To improve the converter:

1. Add test cases in `tests/` directory
2. Document new features
3. Update this README
4. Follow Python PEP 8 style guidelines

## License

This toolchain is provided as-is for educational and reverse engineering purposes.

## Author

Created for the HP.EXE decompilation project.
