#include <cstdint>
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

// FPU stack simulation
float fpu_stack[8];
int fpu_sp = 0;

inline void fpu_push(float val) {
    fpu_stack[fpu_sp++] = val;
}

inline float fpu_pop() {
    return fpu_stack[--fpu_sp];
}

// Stack simulation
uint32_t stack[1024*1024];
int stack_pointer = 1024*1024 - 1;

inline void push(uint32_t val) {
    stack[stack_pointer--] = val;
}

inline uint32_t pop() {
    return stack[++stack_pointer];
}

// Flag update helpers
bool zero_flag, sign_flag, carry_flag, overflow_flag;

inline void flags_update(int32_t result) {
    zero_flag = (result == 0);
    sign_flag = (result < 0);
    // Carry and overflow simplified
}

inline void flags_update_float(float result) {
    zero_flag = (result == 0.0f);
    sign_flag = (result < 0.0f);
}

// Min/Max helpers for SSE
inline float min(float a, float b) { return (a < b) ? a : b; }
inline float max(float a, float b) { return (a > b) ? a : b; }

// Forward declarations
// Function at 0x00401000
void sub_00401000() {
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

    fpu_push(dword [esp+0x4]); // fld dword [esp+0x4]
    fpu_push(dword [esp+0x8]); // fld dword [esp+0x8]
    goto loc_0079ebc8; // jmp loc_0079ebc8
    /* int3 */
    /* int3 */
    /* int3 */
}

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

    push(ebp); // push ebp
    ebp = esp; // mov ebp,esp
    esp &= byte -0x8; // and esp,byte -0x8
    fpu_push(dword [ebp+0x8]); // fld dword [ebp+0x8]
    fpu_st0 = sqrt(fpu_st0); // fsqrt
    esp = ebp; // mov esp,ebp
    ebp = pop(); // pop ebp
    return; // ret
    /* int3 */
}

// Function at 0x00401022
void sub_00401022() {
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

    esp -= +0xc; // sub esp,byte +0xc
    push(ebx); // push ebx
    ebx = *(uint32_t*)(esp + 0x18); // mov ebx,[esp+0x18]
    push(ebp); // push ebp
    ebp = *(uint32_t*)(esp + 0x18); // mov ebp,[esp+0x18]
    push(esi); // push esi
    esi = *(uint32_t*)(ebp); // mov esi,[ebp+0x0]
    /* test */ flags_update(esi & esi);
    if (zero_flag) goto loc_00401049; // jz loc_00401049
    /* cmp */ flags_update(esi - 0x7d3ddb);
    if (zero_flag) goto loc_00401049; // jz loc_00401049
    /* call */ loc_00614170();
    dword [ebp+0x0] = 0x7d3ddb; // mov dword [ebp+0x0],0x7d3ddb
}

// Function at 0x0040105d
void sub_0040105d() {
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

    /* test */ flags_update(ebx & ebx);
    if (zero_flag) goto loc_0040109e; // jz loc_0040109e
    /* cmp */ flags_update(byte [ebx] - 0x0);
    if (zero_flag) goto loc_0040109e; // jz loc_0040109e
    eax = ebx; // mov eax,ebx
    edx = eax + 0x1; // lea edx,[eax+0x1]
}

// Function at 0x00401077
void sub_00401077() {
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

    (uint8_t)ecx = *(uint32_t*)(eax); // mov cl,[eax]
    eax += +0x1; // add eax,byte +0x1
    /* test */ flags_update((uint8_t)ecx & (uint8_t)ecx);
    if (!zero_flag) goto loc_00401057; // jnz loc_00401057
    push(edi); // push edi
    eax -= edx; // sub eax,edx
    edi = eax + 0x1; // lea edi,[eax+0x1]
    push(dword 0x7d3ddc); // push dword 0x7d3ddc
    push(edi); // push edi
    return; // ret
}

// Function at 0x00401097
void sub_00401097() {
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

    esi = pop(); // pop esi
    ebp = pop(); // pop ebp
    ebx = pop(); // pop ebx
    esp += +0xc; // add esp,byte +0xc
}

