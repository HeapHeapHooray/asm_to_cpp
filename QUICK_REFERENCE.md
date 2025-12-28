# Assembly to C++ - Quick Reference

## One-Liner Commands

```bash
# Convert single file with progress
python3 quick_converter.py ../hp_text_yasm.asm hp_text.cpp

# Convert entire project
python3 main_converter.py ..

# Test parser only
python3 asm_parser.py ../hp_text_yasm.asm

# Convert specific file
python3 cpp_generator.py input.asm output.cpp
```

## Common Instruction Conversions

| Assembly | C++ Translation |
|----------|-----------------|
| `mov eax, ebx` | `eax = ebx;` |
| `add eax, 5` | `eax += 5;` |
| `sub eax, ebx` | `eax -= ebx;` |
| `imul eax, ebx` | `eax *= ebx;` |
| `inc eax` | `eax++;` |
| `dec eax` | `eax--;` |
| `and eax, 0xff` | `eax &= 0xff;` |
| `or eax, ebx` | `eax \|= ebx;` |
| `xor eax, eax` | `eax = 0;` |
| `shl eax, 2` | `eax <<= 2;` |
| `shr eax, 1` | `eax >>= 1;` |
| `push eax` | `push(eax);` |
| `pop eax` | `eax = pop();` |
| `call func` | `func();` |
| `ret` | `return;` |
| `jmp label` | `goto label;` |
| `je label` | `if (zero_flag) goto label;` |
| `jne label` | `if (!zero_flag) goto label;` |
| `cmp eax, 5` | `flags_update(eax - 5);` |
| `test eax, eax` | `flags_update(eax & eax);` |
| `lea eax, [ebx+4]` | `eax = ebx + 4;` |
| `mov eax, [ebx]` | `eax = *(uint32_t*)ebx;` |
| `mov [ebx], eax` | `*(uint32_t*)ebx = eax;` |
| `fld dword [esp+4]` | `fpu_push(*(float*)(esp+4));` |
| `fstp dword [ebp-8]` | `*(float*)(ebp-8) = fpu_pop();` |
| `fsqrt` | `fpu_st0 = sqrt(fpu_st0);` |
| `movss xmm0, xmm1` | `xmm0 = xmm1;` |
| `addss xmm0, xmm1` | `xmm0 += xmm1;` |
| `mulss xmm0, [eax]` | `xmm0 *= *(float*)eax;` |

## Register Mapping

| Register | C++ Variable | Size |
|----------|--------------|------|
| eax, ebx, ecx, edx | `uint32_t eax` | 32-bit |
| esi, edi, ebp, esp | `uint32_t esi` | 32-bit |
| ax, bx, cx, dx | `(uint16_t)eax` | 16-bit |
| al, bl, cl, dl | `(uint8_t)eax` | 8-bit low |
| ah, bh, ch, dh | `(uint8_t)(eax>>8)` | 8-bit high |
| xmm0-xmm7 | `float xmm0` | SSE |

## Memory Addressing

| Assembly | C++ Translation |
|----------|-----------------|
| `[eax]` | `*(uint32_t*)eax` |
| `[eax+4]` | `*(uint32_t*)(eax + 4)` |
| `[eax+ebx]` | `*(uint32_t*)(eax + ebx)` |
| `[eax+ebx*4]` | `*(uint32_t*)(eax + ebx*4)` |
| `[eax+ebx*4+8]` | `*(uint32_t*)(eax + ebx*4 + 8)` |
| `byte [eax]` | `*(uint8_t*)eax` |
| `word [eax]` | `*(uint16_t*)eax` |
| `dword [eax]` | `*(uint32_t*)eax` |

## Control Flow Patterns

### Pattern 1: Loop
```asm
loc_loop:
    ; loop body
    dec ecx
    jnz loc_loop
```
→
```cpp
while (ecx != 0) {
    // loop body
    ecx--;
}
```

### Pattern 2: If-Then-Else
```asm
    cmp eax, 10
    jl loc_else
    ; then branch
    jmp loc_end
loc_else:
    ; else branch
loc_end:
```
→
```cpp
if (eax >= 10) {
    // then branch
} else {
    // else branch
}
```

### Pattern 3: Function Call
```asm
    push arg2
    push arg1
    call function
    add esp, 8
```
→
```cpp
function(arg1, arg2);
```

## Common Fixes

### Fix 1: Memory Access
```cpp
// BEFORE (Won't compile)
fpu_push(dword [esp+0x4]);

// AFTER
fpu_push(*(float*)(esp + 0x4));
```

### Fix 2: Byte Alignment
```cpp
// BEFORE
esp &= byte -0x8;

// AFTER
esp &= 0xFFFFFFF8;
```

### Fix 3: FPU References
```cpp
// BEFORE
fpu_st0 = sqrt(fpu_st0);

// AFTER
float st0 = fpu_stack[fpu_sp-1];
st0 = sqrt(st0);
fpu_stack[fpu_sp-1] = st0;
```

## File Sizes

| Input | Instructions | Output Size | Time |
|-------|-------------|-------------|------|
| Small (1K lines) | ~1,000 | ~100 KB | <1 sec |
| Medium (100K lines) | ~100,000 | ~10 MB | ~2 min |
| hp_text (24M lines) | ~3.8M | ~300 MB | ~20 min |
| hp_hatred (2M lines) | ~330K | ~30 MB | ~3 min |

## Troubleshooting

| Problem | Solution |
|---------|----------|
| Out of memory | Use quick_converter with limited functions |
| Parse error | Check YASM format |
| Slow conversion | Use quick_converter.py |
| Large output | Edit line 47 in quick_converter.py |
| Compilation error | See USAGE_GUIDE.md |

## Configuration

### Limit Output Size
Edit `quick_converter.py`, line 47:
```python
# Process first 1000 functions
func_count = min(len(functions), 1000)

# Process first 5000 functions
func_count = min(len(functions), 5000)

# Process ALL functions
func_count = len(functions)
```

### Add Custom Instruction
Edit `instruction_converter.py`:
```python
elif mnemonic == 'my_instruction':
    dest = self.operand_to_cpp(ops[0])
    src = self.operand_to_cpp(ops[1])
    return [f"{dest} = custom_operation({src});"]
```

## Performance Tips

1. Use **quick_converter.py** for large files
2. Start with **small samples** to verify
3. Monitor **memory usage** (1-2GB needed)
4. **Limit function count** if too slow
5. Process in **parallel** (split files)

## Quick Workflow

```bash
# 1. Navigate to tools
cd asm_to_cpp

# 2. Convert with progress
python3 quick_converter.py ../hp_text_yasm.asm hp_text.cpp

# 3. Check output
head -100 hp_text.cpp

# 4. Verify compilation
g++ -std=c++17 -c hp_text.cpp

# 5. Fix errors, iterate
```

## Helper Functions Available

```cpp
// Stack operations
void push(uint32_t val);
uint32_t pop();

// FPU operations
void fpu_push(float val);
float fpu_pop();

// Flag updates
void flags_update(int32_t result);
void flags_update_float(float result);

// Math helpers
float min(float a, float b);
float max(float a, float b);
```

## Useful Grep Patterns

```bash
# Find all function definitions
grep "^void sub_" output.cpp

# Find all calls to specific address
grep "loc_00401234" output.cpp

# Find all memory writes
grep "\*\(uint32_t\*\)" output.cpp

# Find all comparisons
grep "cmp" output.cpp
```

---

**For detailed info**: See USAGE_GUIDE.md
**For technical details**: See README.md
**For examples**: Check small_sample.cpp
