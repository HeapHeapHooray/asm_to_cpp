# Assembly to C++ Conversion - Usage Guide

## Quick Start

### Option 1: Convert with Progress (Recommended for large files)

```bash
cd asm_to_cpp
python3 quick_converter.py ../hp_text_yasm.asm hp_text.cpp
python3 quick_converter.py ../hp_hatred_yasm.asm hp_hatred.cpp
```

### Option 2: Full Project Conversion

```bash
cd asm_to_cpp
python3 main_converter.py ..
```

This creates a complete C++ project in `cpp_output/` with:
- Converted source files
- Header files
- CMakeLists.txt for building
- Documentation

## Output Structure

```
cpp_output/
├── hp_text.cpp              # Main code section
├── hp_hatred.cpp            # HATRED section
├── hp.h                     # Main header
├── windows_api.h            # Windows API declarations
├── data_structures.h        # Data structures
├── CMakeLists.txt           # Build configuration
└── README.md                # Build instructions
```

## Example Generated Code

### Input Assembly:
```asm
loc_00401010:
    push ebp
    mov ebp,esp
    and esp,byte -0x8
    fld dword [ebp+0x8]
    fsqrt
    mov esp,ebp
    pop ebp
    ret
```

### Generated C++:
```cpp
// Function at 0x00401010
void sub_00401010() {
    // Registers
    uint32_t eax = 0;
    uint32_t ebx = 0;
    uint32_t ecx = 0;
    uint32_t edx = 0;
    uint32_t esi = 0;
    uint32_t edi = 0;
    uint32_t ebp = 0;
    uint32_t esp = 0;
    // SSE registers
    float xmm0 = 0.0f;
    float xmm1 = 0.0f;
    float xmm2 = 0.0f;
    float xmm3 = 0.0f;
    float xmm4 = 0.0f;
    float xmm5 = 0.0f;
    float xmm6 = 0.0f;
    float xmm7 = 0.0f;
    // Flags
    bool zero_flag = false, sign_flag = false, carry_flag = false, overflow_flag = false;

    push(ebp);           // push ebp
    ebp = esp;           // mov ebp,esp
    esp &= -0x8;         // and esp,byte -0x8
    fpu_push(*(uint32_t*)(ebp + 0x8));  // fld dword [ebp+0x8]
    fpu_st0 = sqrt(fpu_st0);  // fsqrt
    esp = ebp;           // mov esp,ebp
    ebp = pop();         // pop ebp
    return;              // ret
}
```

## Conversion Features

### ✅ Supported Features

1. **All x86 Instructions**
   - Arithmetic: add, sub, mul, div, inc, dec
   - Logical: and, or, xor, not, shl, shr
   - Data movement: mov, lea, movss, movaps
   - Control flow: jmp, je, jne, jg, jl, call, ret
   - Stack: push, pop
   - Comparison: cmp, test, ucomiss
   - FPU: fld, fstp, fadd, fsub, fmul, fdiv, fsqrt
   - SSE: addss, subss, mulss, divss, minss, maxss, cvttss2si, cvtsi2ss

2. **Register Mapping**
   - All 32-bit registers (eax, ebx, ecx, edx, esi, edi, ebp, esp)
   - 16-bit sub-registers (ax, bx, cx, dx)
   - 8-bit sub-registers (al, ah, bl, bh, cl, ch, dl, dh)
   - SSE registers (xmm0-xmm7)
   - FPU stack simulation

3. **Memory Addressing**
   - Base + displacement: [ebp+0x8]
   - Base + index: [eax+ebx]
   - Base + index*scale: [eax+ebx*4]
   - Complex: [eax+ebx*4+0x10]

4. **Control Flow**
   - Unconditional jumps
   - Conditional branches
   - Function calls
   - Returns
   - Label preservation

### ⚠️ Limitations

1. **Function Signatures**
   - All functions start as `void func()`
   - Parameters must be identified manually
   - Return types need manual analysis
   - Calling conventions not automatically detected

2. **Type Information**
   - Generic types used (uint32_t, float)
   - Structs/classes need manual reconstruction
   - Pointer types simplified

3. **Control Structures**
   - Some code uses goto statements
   - Manual restructuring to while/for loops recommended

4. **Windows API**
   - API calls need manual resolution
   - Function pointers need proper typing

## Post-Conversion Cleanup

### 1. Fix Compilation Errors

Some common issues to fix:

```cpp
// BEFORE (Won't compile)
fpu_push(dword [esp+0x4]);

// AFTER (Fixed)
fpu_push(*(float*)(esp + 0x4));
```

```cpp
// BEFORE
esp &= byte -0x8;

// AFTER
esp &= 0xFFFFFFF8;  // Align to 8-byte boundary
```

### 2. Identify Function Parameters

Look for stack accesses in the function prologue:

```cpp
void sub_00401020() {
    // ...
    mov ebx,[esp+0x18]  // Parameter 1
    mov ebp,[esp+0x18]  // Parameter 2
    // ...
}
```

Should become:

```cpp
void sub_00401020(uint32_t param1, uint32_t param2) {
    uint32_t ebx = param1;
    uint32_t ebp = param2;
    // ...
}
```

### 3. Identify Return Values

Look for eax assignments before return:

```cpp
void sub_00401030() {
    // ...
    eax = result;
    return;
}
```

Should become:

```cpp
uint32_t sub_00401030() {
    // ...
    return result;
}
```

### 4. Extract Data Structures

Look for patterns like:

```cpp
*(uint32_t*)(eax + 0x0) = value1;
*(uint32_t*)(eax + 0x4) = value2;
*(uint32_t*)(eax + 0x8) = value3;
```

Define a struct:

```cpp
struct MyStruct {
    uint32_t field0;  // offset 0x0
    uint32_t field4;  // offset 0x4
    uint32_t field8;  // offset 0x8
};

MyStruct* obj = (MyStruct*)eax;
obj->field0 = value1;
obj->field4 = value2;
obj->field8 = value3;
```

### 5. Replace Goto with Structured Loops

```cpp
// BEFORE
loc_00401057:
    mov cl,[eax]
    add eax,byte +0x1
    test cl,cl
    jnz loc_00401057
```

Becomes:

```cpp
// AFTER
while (*(uint8_t*)eax != 0) {
    uint8_t cl = *(uint8_t*)eax;
    eax++;
}
```

## Building the Generated Code

### Using CMake (Recommended)

```bash
cd cpp_output
mkdir build
cd build
cmake ..
cmake --build .
```

### Manual Compilation

```bash
g++ -std=c++17 -o hp hp_text.cpp hp_hatred.cpp -lm
```

On Windows with MSVC:

```bash
cl /std:c++17 /Fe:hp.exe hp_text.cpp hp_hatred.cpp
```

## Performance Tips

### For Large Files (3M+ lines):

1. **Use quick_converter.py** instead of main_converter.py
2. **Limit function count** in quick_converter.py if needed
3. **Process in chunks**: Split assembly file and convert separately
4. **Increase RAM**: Large files need 1-2GB+ memory

### Optimization:

```bash
# Edit quick_converter.py, line 47:
func_count = min(len(functions), 1000)  # Process 1000 functions

# To process more:
func_count = min(len(functions), 5000)  # Process 5000 functions

# To process all:
func_count = len(functions)  # Process all functions (may take 30+ min)
```

## Troubleshooting

### Issue: "Out of memory"
**Solution**: Process in smaller chunks or use the quick_converter with limited function count

### Issue: "Parse errors"
**Solution**: Check assembly syntax, ensure YASM format

### Issue: "Compilation errors in generated C++"
**Solution**: See "Post-Conversion Cleanup" section above

### Issue: "Conversion too slow"
**Solution**: Use quick_converter.py, it shows progress and is optimized for speed

## Advanced Usage

### Batch Processing Multiple Files

```python
from quick_converter import convert_with_progress

files = [
    ('hp_text_yasm.asm', 'hp_text.cpp'),
    ('hp_hatred_yasm.asm', 'hp_hatred.cpp'),
]

for input_file, output_file in files:
    convert_with_progress(input_file, output_file)
```

### Custom Instruction Patterns

Edit `instruction_converter.py` to add custom conversion patterns:

```python
# In instruction_to_cpp method:
elif mnemonic == 'my_custom_instruction':
    # Your custom conversion logic
    return [f"custom_func({operands});"]
```

### Extracting Specific Functions

```python
from asm_parser import AssemblyParser

parser = AssemblyParser()
functions = parser.parse_file('hp_text_yasm.asm')

# Find function at specific address
target_func = None
for func in functions:
    if func.start_address == 0x00401020:
        target_func = func
        break

# Convert just this function
from cpp_generator import CppGenerator
generator = CppGenerator()
cpp_code = generator.generate_function(target_func)
print('\n'.join(cpp_code))
```

## Next Steps

1. ✅ **Run the converter** on your assembly files
2. ✅ **Review generated code** for obvious errors
3. 🔧 **Fix compilation errors** (syntax issues)
4. 🔍 **Identify function signatures** (parameters, returns)
5. 🏗️ **Extract data structures** (classes, structs)
6. 🎨 **Refactor control flow** (replace gotos)
7. 📝 **Add documentation** (function names, comments)
8. 🧪 **Test functionality** (compare with original)

## Resources

- **Tool Documentation**: See `README.md` in asm_to_cpp/
- **Python Modules**:
  - `asm_parser.py` - Assembly parsing
  - `instruction_converter.py` - Instruction translation
  - `control_flow_analyzer.py` - Control flow analysis
  - `cpp_generator.py` - C++ generation
- **Examples**: Check `small_sample.cpp` for reference output

## Getting Help

If you encounter issues:

1. Check this guide's Troubleshooting section
2. Review the tool's README.md
3. Examine generated comments in C++ code
4. Look at working examples (small_sample.cpp)
5. Test on smaller file sections first

## Estimated Times

For HP.EXE disassembly:

- **hp_text section** (3.8M instructions): 15-25 minutes
- **hp_hatred section** (330K instructions): 2-5 minutes
- **Total project**: 20-30 minutes

Actual times vary based on CPU speed and RAM.

---

**Good luck with your decompilation project!** 🚀
