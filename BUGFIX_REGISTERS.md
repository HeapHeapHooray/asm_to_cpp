# IMPORTANT BUG FIX: Global Register State

## The Problem (Fixed!)

**Original bug**: Registers were declared as local variables in each function and reset to 0.

```cpp
// WRONG (old version)
void function1() {
    uint32_t eax = 0;  // ❌ Reset to 0!
    uint32_t ebx = 0;  // ❌ Reset to 0!
    eax = 42;
    return;  // eax has value 42
}

void function2() {
    uint32_t eax = 0;  // ❌ Lost the value 42!
    // ...
}
```

This was **completely wrong** because:
- ❌ Registers don't persist between functions
- ❌ Parameter passing doesn't work
- ❌ Return values are lost
- ❌ Breaks all calling conventions
- ❌ Stack pointer resets incorrectly

## The Fix

**Registers are now GLOBAL variables** that persist across all function calls:

```cpp
// CORRECT (new version)
// Global CPU state
uint32_t eax = 0;
uint32_t ebx = 0;
uint32_t ecx = 0;
// ... all registers declared globally

void function1() {
    // No register declarations!
    eax = 42;
    return;  // eax = 42
}

void function2() {
    // Still eax = 42 from function1!
    int result = eax;  // Gets 42
}
```

## Why This is Correct

In real x86 assembly:
1. **Registers are CPU state** - they're global hardware resources
2. **Values persist** between function calls
3. **Parameters** are passed in registers (fastcall, thiscall) or stack
4. **Return values** go in eax/edx
5. **Callee-saved registers** (ebx, esi, edi, ebp) must be preserved

## Impact on Generated Code

### Parameter Passing

```asm
; Caller
mov eax, 10          ; Put parameter in eax
call my_function

; Callee
my_function:
    ; eax already has 10!
    add eax, 5       ; eax = 15
    ret
```

Becomes:

```cpp
// Caller
eax = 10;           // Global eax
my_function();

// Callee
void my_function() {
    // Uses global eax (already 10)
    eax += 5;       // eax = 15
}
```

### Return Values

```asm
calculate:
    mov eax, 42      ; Return value in eax
    ret

main:
    call calculate
    ; eax now has 42
    mov result, eax
```

Becomes:

```cpp
void calculate() {
    eax = 42;       // Global eax
    return;
}

void main() {
    calculate();
    // eax still has 42!
    result = eax;
}
```

### Stack Operations

```cpp
// Global stack pointer
uint32_t esp = 0x00100000;  // Starts at 1MB

void func1() {
    push(ebp);     // esp -= 4
    ebp = esp;
    // esp is now at 0x000FFFFC
}

void func2() {
    // esp still at 0x000FFFFC
    // Stack grows properly!
}
```

## What's Now Correct

✅ **Register values persist** across function calls
✅ **Parameter passing** works (registers carry values)
✅ **Return values** work (eax/edx maintained)
✅ **Stack pointer** maintains position
✅ **Calling conventions** work properly
✅ **Callee-saved registers** can be tracked
✅ **Global state** matches real CPU behavior

## Code Structure

```cpp
// ============================================================================
// GLOBAL CPU STATE
// ============================================================================
// IMPORTANT: Registers are GLOBAL and persist between function calls!
// This matches actual x86 behavior where registers maintain their values.

// General purpose registers (32-bit)
uint32_t eax = 0;
uint32_t ebx = 0;
uint32_t ecx = 0;
uint32_t edx = 0;
uint32_t esi = 0;
uint32_t edi = 0;
uint32_t ebp = 0;
uint32_t esp = 0x00100000;  // Stack starts at 1MB

// SSE registers
float xmm0 = 0.0f;
// ... xmm1-xmm7

// CPU flags
bool zero_flag = false;
bool sign_flag = false;
bool carry_flag = false;
bool overflow_flag = false;

// ============================================================================
// FUNCTIONS
// ============================================================================

void sub_00401000() {
    // Uses global registers - no local declarations!
    eax = 42;
}

void sub_00401010() {
    // eax still has 42 from previous function
    ebx = eax;  // ebx = 42
}
```

## Calling Convention Examples

### cdecl (stack parameters)
```asm
push 20         ; param2
push 10         ; param1
call function
add esp, 8      ; caller cleanup
```
```cpp
push(20);
push(10);
function();
esp += 8;
```

### fastcall (register parameters)
```asm
mov ecx, 10     ; param1 in ecx
mov edx, 20     ; param2 in edx
call function
```
```cpp
ecx = 10;
edx = 20;
function();
```

### thiscall (this pointer in ecx)
```asm
mov ecx, object_ptr  ; this pointer
call method
```
```cpp
ecx = object_ptr;
method();
```

## Testing the Fix

You can verify this works correctly:

```cpp
#include "generated_code.cpp"

int main() {
    // Set up initial state
    eax = 100;

    // Call function that uses eax
    sub_00401000();

    // Verify eax persisted
    printf("eax = %u\n", eax);  // Should NOT be 0!

    return 0;
}
```

## Files Updated

- ✅ `cpp_generator.py` - Removed local register declarations
- ✅ `cpp_generator.py` - Added global register declarations in header
- ✅ `quick_converter.py` - Automatically uses fixed generator

## Migration

If you have old generated code:

**OLD (broken)**:
```cpp
void func() {
    uint32_t eax = 0;  // Remove this
    uint32_t ebx = 0;  // Remove this
    // ...
}
```

**NEW (correct)**:
```cpp
// Add at top of file (once):
uint32_t eax = 0;
uint32_t ebx = 0;
// ... all registers

// Functions no longer declare registers:
void func() {
    // Just use global registers
    eax = value;
}
```

## Performance Note

Global variables might seem less efficient, but remember:
1. This is **emulation** - we're simulating x86 behavior
2. In real x86, registers **are** global CPU state
3. Modern compilers optimize globals well
4. For actual speed, you'd want to decompile to higher-level code anyway

## Summary

This fix makes the generated code **semantically correct** - it now properly emulates x86 register behavior where registers are global CPU state that persists across function calls. This is essential for:
- Correct parameter passing
- Working return values
- Proper stack management
- Accurate calling conventions
- Real-world behavior matching

**The converter now generates correct code!** ✅
