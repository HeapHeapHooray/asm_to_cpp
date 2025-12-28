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
    goto loc_0039dbc8; // jmp loc_0039dbc8
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
}

// Function at 0x0040102a
void sub_0040102a() {
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

    ebx = *(uint32_t*)(esp + 0x18); // mov ebx,[esp+0x18]
    push(ebp); // push ebp
    ebp = *(uint32_t*)(esp + 0x18); // mov ebp,[esp+0x18]
    push(esi); // push esi
    esi = *(uint32_t*)(ebp); // mov esi,[ebp+0x0]
    /* test */ flags_update(esi & esi);
    if (zero_flag) goto loc_00000049; // jz loc_00000049
    /* cmp */ flags_update(esi - 0x7d3ddb);
    if (zero_flag) goto loc_00000049; // jz loc_00000049
    /* call */ loc_00213170();
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
    if (zero_flag) goto loc_0000009e; // jz loc_0000009e
    /* cmp */ flags_update(byte [ebx] - 0x0);
    if (zero_flag) goto loc_0000009e; // jz loc_0000009e
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
    if (!zero_flag) goto loc_00000057; // jnz loc_00000057
    push(edi); // push edi
    eax -= edx; // sub eax,edx
    edi = eax + 0x1; // lea edi,[eax+0x1]
    push(dword 0x7d3ddc); // push dword 0x7d3ddc
    push(edi); // push edi
    esi = esp + 0x18; // lea esi,[esp+0x18]
    dword [esp+0x18] = 0x4; // mov dword [esp+0x18],0x4
    dword [esp+0x1c] = 0x1; // mov dword [esp+0x1c],0x1
    dword [esp+0x20] = 0x0; // mov dword [esp+0x20],0x0
    /* call */ loc_002131b0();
    push(edi); // push edi
    esi = eax; // mov esi,eax
    push(ebx); // push ebx
    push(esi); // push esi
    /* call */ loc_0039ac6a();
    esp += +0x14; // add esp,byte +0x14
    *(uint32_t*)(ebp) = esi; // mov [ebp+0x0],esi
    edi = pop(); // pop edi
}

// Function at 0x004010d1
void sub_004010d1() {
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
    return; // ret 0x8
    /* int3 */
    /* int3 */
}

// Function at 0x004010e7
void sub_004010e7() {
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

    /* int3 */
    /* int3 */
}

// Function at 0x004010eb
void sub_004010eb() {
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

    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
}

// Function at 0x004010f5
void sub_004010f5() {
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

    eax = ecx; // mov eax,ecx
    return; // ret
    /* int3 */
    /* int3 */
}

// Function at 0x004010fd
void sub_004010fd() {
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

    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
}

// Function at 0x00401107
void sub_00401107() {
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

    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* test */ flags_update([esp+0x4] & 0x1);
}

// Function at 0x0040111d
void sub_0040111d() {
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

    push(esi); // push esi
    esi = ecx; // mov esi,ecx
    dword [esi] = 0x8475e0; // mov dword [esi],0x8475e0
    dword [dword 0xe6b298] = 0x0; // mov dword [dword 0xe6b298],0x0
    if (zero_flag) goto loc_000000e3; // jz loc_000000e3
    push(esi); // push esi
    /* call */ loc_00213120();
    esp += +0x4; // add esp,byte +0x4
}

// Function at 0x00401144
void sub_00401144() {
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

    eax = esi; // mov eax,esi
    esi = pop(); // pop esi
    return; // ret 0x4
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
}

// Function at 0x0040115c
void sub_0040115c() {
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

    push(edi); // push edi
    edi = *(uint32_t*)(esp + 0x10); // mov edi,[esp+0x10]
    edi -= +0x1; // sub edi,byte +0x1
    if (sign_flag) goto loc_0000011e; // js loc_0000011e
    push(ebx); // push ebx
    ebx = *(uint32_t*)(esp + 0x18); // mov ebx,[esp+0x18]
    push(ebp); // push ebp
    ebp = *(uint32_t*)(esp + 0x14); // mov ebp,[esp+0x14]
    push(esi); // push esi
    esi = *(uint32_t*)(esp + 0x14); // mov esi,[esp+0x14]
    esp = esp; // lea esp,[esp+0x0]
}

// Function at 0x00401184
void sub_00401184() {
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

    ecx = esi; // mov ecx,esi
    /* call */ ((void(*)())ebx)();
    esi += ebp; // add esi,ebp
    edi -= +0x1; // sub edi,byte +0x1
    if (!sign_flag) goto loc_00000110; // jns loc_00000110
    esi = pop(); // pop esi
    ebp = pop(); // pop ebp
    ebx = pop(); // pop ebx
}

// Function at 0x0040119f
void sub_0040119f() {
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

    edi = pop(); // pop edi
    return; // ret 0x10
}

// Function at 0x004011a7
void sub_004011a7() {
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

    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
}

// Function at 0x004011c3
void sub_004011c3() {
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

    push(ebx); // push ebx
    ebx = *(uint32_t*)(esp + 0xc); // mov ebx,[esp+0xc]
    push(esi); // push esi
    esi = *(uint32_t*)(esp + 0xc); // mov esi,[esp+0xc]
    push(edi); // push edi
    edi = *(uint32_t*)(esp + 0x18); // mov edi,[esp+0x18]
    eax = ebx; // mov eax,ebx
    eax *= edi; // imul eax,edi
    esi += eax; // add esi,eax
    edi -= +0x1; // sub edi,byte +0x1
    if (sign_flag) goto loc_0000015c; // js loc_0000015c
    push(ebp); // push ebp
    ebp = *(uint32_t*)(esp + 0x20); // mov ebp,[esp+0x20]
}

// Function at 0x004011ed
void sub_004011ed() {
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

    esi -= ebx; // sub esi,ebx
    ecx = esi; // mov ecx,esi
    /* call */ ((void(*)())ebp)();
    edi -= +0x1; // sub edi,byte +0x1
    if (!sign_flag) goto loc_00000150; // jns loc_00000150
    ebp = pop(); // pop ebp
}

// Function at 0x00401204
void sub_00401204() {
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

    edi = pop(); // pop edi
    esi = pop(); // pop esi
    ebx = pop(); // pop ebx
    return; // ret 0x10
    /* int3 */
    /* int3 */
}

// Function at 0x00401214
void sub_00401214() {
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

    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
}

// Function at 0x00401220
void sub_00401220() {
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

    /* int3 */
}

// Function at 0x00401222
void sub_00401222() {
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

    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
}

// Function at 0x0040122c
void sub_0040122c() {
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

    goto loc_00a77000; // jmp loc_00a77000
    *(uint32_t*)(edi + 0x74) += esp; // add [edi+0x74],esp
    if (zero_flag) goto loc_0000017b; // jz loc_0000017b
    *(uint32_t*)(eax) += (uint8_t)eax; // add [eax],al
    *(uint32_t*)(eax) += (uint8_t)eax; // add [eax],al
    *(uint32_t*)(eax) += (uint8_t)eax; // add [eax],al
    *(uint32_t*)(eax) += (uint8_t)eax; // add [eax],al
    *(uint32_t*)(eax) += (uint8_t)eax; // add [eax],al
    *(uint32_t*)(eax) += (uint8_t)eax; // add [eax],al
    /* scasd */
    if (zero_flag) goto loc_000001fd; // jz loc_000001fd
    *(uint32_t*)(eax) += eax; // add [eax],eax
    *(uint32_t*)(eax) += (uint8_t)eax; // add [eax],al
    *(uint32_t*)(eax) += (uint8_t)eax; // add [eax],al
    *(uint32_t*)(eax) += (uint8_t)eax; // add [eax],al
    *(uint32_t*)(eax) += (uint8_t)eax; // add [eax],al
}

// Function at 0x00401270
void sub_00401270() {
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

    *(uint32_t*)(eax) += (uint8_t)eax; // add [eax],al
    (uint8_t)(ebx >> 8) += (uint8_t)(edx >> 8); // add bh,dh
    if (zero_flag) goto loc_0000020d; // jz loc_0000020d
    *(uint32_t*)(eax) += eax; // add [eax],eax
    *(uint32_t*)(eax) += (uint8_t)eax; // add [eax],al
    *(uint32_t*)(eax) += (uint8_t)eax; // add [eax],al
    *(uint32_t*)(eax) += (uint8_t)eax; // add [eax],al
    *(uint32_t*)(eax) += (uint8_t)eax; // add [eax],al
    *(uint32_t*)(eax) += (uint8_t)eax; // add [eax],al
    *(uint32_t*)(ecx + 0x1754590) += (uint8_t)(eax >> 8); // add [ecx+0x1754590],ah
    goto loc_001b6e91; // jmp loc_001b6e91
}

// Function at 0x0040129e
void sub_0040129e() {
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
    esp -= +0x20; // sub esp,byte +0x20
    xmm0 = dword [ebp+0x8]; // movss // movss xmm0,dword [ebp+0x8]
    xmm1 = xmm0; // movaps // movaps xmm1,xmm0
    xmm1 *= dword [dword 0x8d10f0]; // mulss // mulss xmm1,dword [dword 0x8d10f0]
    eax = (int32_t)xmm1; // cvttss2si // cvttss2si eax,xmm1
    xmm1 = dword [dword 0x8d10f8]; // movss // movss xmm1,dword [dword 0x8d10f8]
    xmm2 = (float)eax; // cvtsi2ss // cvtsi2ss xmm2,eax
    xmm2 *= xmm1; // mulss // mulss xmm2,xmm1
}

// Function at 0x004012bc
void sub_004012bc() {
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

    xmm0 -= xmm2; // subss // subss xmm0,xmm2
    xmm1 -= xmm0; // subss // subss xmm1,xmm0
    xmm0 = min(xmm0, xmm1); // minss // minss xmm0,xmm1
    xmm1 = dword [dword 0x8d10f4]; // movss // movss xmm1,dword [dword 0x8d10f4]
    xmm1 -= xmm0; // subss // subss xmm1,xmm0
    xmm0 = min(xmm0, xmm1); // minss // minss xmm0,xmm1
    xmm2 = dword [dword 0x8d0ff0]; // movss // movss xmm2,dword [dword 0x8d0ff0]
    xmm3 = dword [dword 0x8d0ff4]; // movss // movss xmm3,dword [dword 0x8d0ff4]
    xmm1 -= xmm0; // subss // subss xmm1,xmm0
    dword [ebp-0x20] = xmm1; // movss // movss dword [ebp-0x20],xmm1
    xmm0 *= xmm0; // mulss // mulss xmm0,xmm0
    xmm2 *= xmm0; // mulss // mulss xmm2,xmm0
    xmm2 += dword [dword 0x8afa70]; // addss // addss xmm2,dword [dword 0x8afa70]
    xmm1 = xmm0; // movaps // movaps xmm1,xmm0
    xmm1 *= xmm0; // mulss // mulss xmm1,xmm0
    xmm3 *= xmm1; // mulss // mulss xmm3,xmm1
    xmm3 += xmm2; // addss // addss xmm3,xmm2
    xmm2 = dword [dword 0x8d0ff8]; // movss // movss xmm2,dword [dword 0x8d0ff8]
    xmm1 *= xmm0; // mulss // mulss xmm1,xmm0
    xmm2 *= xmm1; // mulss // mulss xmm2,xmm1
    xmm2 += xmm3; // addss // addss xmm2,xmm3
    xmm1 *= xmm0; // mulss // mulss xmm1,xmm0
    xmm3 = xmm1; // movaps // movaps xmm3,xmm1
    xmm1 = dword [dword 0x8d0ffc]; // movss // movss xmm1,dword [dword 0x8d0ffc]
    xmm1 *= xmm3; // mulss // mulss xmm1,xmm3
    xmm1 += xmm2; // addss // addss xmm1,xmm2
    xmm2 = dword [dword 0x8d1000]; // movss // movss xmm2,dword [dword 0x8d1000]
    xmm3 *= xmm0; // mulss // mulss xmm3,xmm0
    xmm2 *= xmm3; // mulss // mulss xmm2,xmm3
}

// Function at 0x00401308
void sub_00401308() {
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

    xmm2 += xmm1; // addss // addss xmm2,xmm1
    xmm3 *= xmm0; // mulss // mulss xmm3,xmm0
}

// Function at 0x0040130c
void sub_0040130c() {
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

    xmm1 = xmm3; // movaps // movaps xmm1,xmm3
    xmm3 = dword [dword 0x8d1004]; // movss // movss xmm3,dword [dword 0x8d1004]
    xmm3 *= xmm1; // mulss // mulss xmm3,xmm1
    xmm1 *= xmm0; // mulss // mulss xmm1,xmm0
    xmm3 += xmm2; // addss // addss xmm3,xmm2
    xmm2 = dword [dword 0x8d1008]; // movss // movss xmm2,dword [dword 0x8d1008]
    xmm2 *= xmm1; // mulss // mulss xmm2,xmm1
    xmm1 *= xmm0; // mulss // mulss xmm1,xmm0
    xmm0 = 0.0f; // xorps (zero) // xorps xmm0,xmm0
    xmm1 *= dword [dword 0x8d100c]; // mulss // mulss xmm1,dword [dword 0x8d100c]
    xmm2 += xmm3; // addss // addss xmm2,xmm3
    xmm1 += xmm2; // addss // addss xmm1,xmm2
    dword [ebp-0x10] = xmm1; // movss // movss dword [ebp-0x10],xmm1
    xmm0 = dword [ebp-0x20]; // movss // movss xmm0,dword [ebp-0x20]
    /* ucomiss */ flags_update_float(xmm0 - dword [dword 0x845314]);
}

// Function at 0x00401336
void sub_00401336() {
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

    ah = (uint8_t)flags; // lahf
    /* test */ flags_update((uint8_t)(eax >> 8) & 0x44);
    /* jpe 0x2d3 */
    xmm0 = dword [dword 0x88e808]; // movss // movss xmm0,dword [dword 0x88e808]
    xmm0 -= dword [ebp-0x10]; // subss // subss xmm0,dword [ebp-0x10]
    esp = ebp; // mov esp,ebp
    ebp = pop(); // pop ebp
    return; // ret
    xmm0 = dword [ebp-0x10]; // movss // movss xmm0,dword [ebp-0x10]
    esp = ebp; // mov esp,ebp
    ebp = pop(); // pop ebp
    return; // ret
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
}

// Function at 0x00401362
void sub_00401362() {
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

    fpu_push(dword [ecx]); // fld dword [ecx]
    xmm0 = 0.0f; // xorps (zero) // xorps xmm0,xmm0
    dword [eax+0x10] = fpu_pop(); // fstp dword [eax+0x10]
    fpu_push(dword [ecx+0x4]); // fld dword [ecx+0x4]
    dword [eax+0x14] = fpu_pop(); // fstp dword [eax+0x14]
}

// Function at 0x0040136c
void sub_0040136c() {
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

    fpu_push(dword [ecx+0x8]); // fld dword [ecx+0x8]
    dword [eax+0x18] = fpu_pop(); // fstp dword [eax+0x18]
    fpu_push(dword [ecx+0xc]); // fld dword [ecx+0xc]
    dword [eax+0x1c] = fpu_pop(); // fstp dword [eax+0x1c]
}

// Function at 0x00401374
void sub_00401374() {
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

    dword [eax+0x1c] = xmm0; // movss // movss dword [eax+0x1c],xmm0
    return; // ret
}

// Function at 0x0040137a
void sub_0040137a() {
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

    fpu_push(dword [ecx]); // fld dword [ecx]
    xmm0 = 0.0f; // xorps (zero) // xorps xmm0,xmm0
    dword [eax+0x20] = fpu_pop(); // fstp dword [eax+0x20]
}

// Function at 0x00401380
void sub_00401380() {
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

    fpu_push(dword [ecx+0x4]); // fld dword [ecx+0x4]
    dword [eax+0x24] = fpu_pop(); // fstp dword [eax+0x24]
    fpu_push(dword [ecx+0x8]); // fld dword [ecx+0x8]
    dword [eax+0x28] = fpu_pop(); // fstp dword [eax+0x28]
    fpu_push(dword [ecx+0xc]); // fld dword [ecx+0xc]
    dword [eax+0x2c] = fpu_pop(); // fstp dword [eax+0x2c]
    dword [eax+0x2c] = xmm0; // movss // movss dword [eax+0x2c],xmm0
    return; // ret
}

// Function at 0x00401392
void sub_00401392() {
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

    fpu_push(dword [ecx]); // fld dword [ecx]
    xmm0 = dword [dword 0x843488]; // movss // movss xmm0,dword [dword 0x843488]
    dword [eax+0x30] = fpu_pop(); // fstp dword [eax+0x30]
    fpu_push(dword [ecx+0x4]); // fld dword [ecx+0x4]
    dword [eax+0x34] = fpu_pop(); // fstp dword [eax+0x34]
    fpu_push(dword [ecx+0x8]); // fld dword [ecx+0x8]
    dword [eax+0x38] = fpu_pop(); // fstp dword [eax+0x38]
    fpu_push(dword [ecx+0xc]); // fld dword [ecx+0xc]
    dword [eax+0x3c] = fpu_pop(); // fstp dword [eax+0x3c]
    dword [eax+0x3c] = xmm0; // movss // movss dword [eax+0x3c],xmm0
    return; // ret
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
}

// Function at 0x004013b4
void sub_004013b4() {
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

    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
}

// Function at 0x004013c2
void sub_004013c2() {
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
    xmm2 = dword [esp+0x20]; // movss // movss xmm2,dword [esp+0x20]
    xmm6 = dword [esp+0x10]; // movss // movss xmm6,dword [esp+0x10]
    xmm0 = dword [esp+0x24]; // movss // movss xmm0,dword [esp+0x24]
}

// Function at 0x004013d4
void sub_004013d4() {
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

    xmm3 = dword [esp+0x14]; // movss // movss xmm3,dword [esp+0x14]
    xmm4 = dword [esp+0x18]; // movss // movss xmm4,dword [esp+0x18]
    xmm5 = dword [esp+0x1c]; // movss // movss xmm5,dword [esp+0x1c]
    xmm7 = 0.0f; // xorps (zero) // xorps xmm7,xmm7
    xmm0 *= xmm3; // mulss // mulss xmm0,xmm3
    xmm1 = xmm2; // movaps // movaps xmm1,xmm2
    xmm1 *= xmm6; // mulss // mulss xmm1,xmm6
    xmm1 += xmm0; // addss // addss xmm1,xmm0
    xmm0 = xmm4; // movaps // movaps xmm0,xmm4
    xmm0 *= dword [esp+0x28]; // mulss // mulss xmm0,dword [esp+0x28]
    xmm1 += xmm0; // addss // addss xmm1,xmm0
    xmm0 = dword [esp+0x2c]; // movss // movss xmm0,dword [esp+0x2c]
    xmm0 *= xmm5; // mulss // mulss xmm0,xmm5
    xmm1 += xmm0; // addss // addss xmm1,xmm0
    /* comiss xmm7,xmm1 */
    xmm0 = dword [esp+0x30]; // movss // movss xmm0,dword [esp+0x30]
    push(ebx); // push ebx
    dword [esp+0x4] = xmm1; // movss // movss dword [esp+0x4],xmm1
    /* jna loc_000003cf */
    xmm7 = dword [dword 0x88e808]; // movss // movss xmm7,dword [dword 0x88e808]
}

// Function at 0x00401412
void sub_00401412() {
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

    xmm7 -= xmm1; // subss // subss xmm7,xmm1
    xmm1 = xmm7; // movaps // movaps xmm1,xmm7
    dword [esp+0x4] = xmm1; // movss // movss dword [esp+0x4],xmm1
    (uint8_t)ebx = 0x1; // mov bl,0x1
    goto short loc_000003d1; // jmp short loc_000003d1
}

// Function at 0x00401424
void sub_00401424() {
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

    (uint8_t)ebx = 0; // xor bl,bl
}

// Function at 0x00401426
void sub_00401426() {
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

    /* comiss xmm1,dword [dword 0x88ea5c] */
    /* jna loc_000003ed */
    xmm1 = dword [dword 0x843488]; // movss // movss xmm1,dword [dword 0x843488]
    xmm1 -= dword [esp+0x34]; // subss // subss xmm1,dword [esp+0x34]
    goto loc_0000049f; // jmp loc_0000049f
}

// Function at 0x0040143a
void sub_0040143a() {
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
    push(ecx); // push ecx
    dword [esp] = fpu_pop(); // fstp dword [esp]
    /* call */ loc_001824c0();
    dword [esp+0x8] = xmm0; // movss // movss dword [esp+0x8],xmm0
}

// Function at 0x0040144d
void sub_0040144d() {
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

    xmm0 -= dword [dword 0x84386c]; // subss // subss xmm0,dword [dword 0x84386c]
    dword [esp] = xmm0; // movss // movss dword [esp],xmm0
    /* call */ loc_000001b0();
    xmm1 = dword [dword 0x843488]; // movss // movss xmm1,dword [dword 0x843488]
    xmm2 = xmm0; // movaps // movaps xmm2,xmm0
    xmm0 = xmm1; // movaps // movaps xmm0,xmm1
    xmm1 -= dword [esp+0x38]; // subss // subss xmm1,dword [esp+0x38]
    xmm1 *= dword [esp+0x8]; // mulss // mulss xmm1,dword [esp+0x8]
    xmm1 -= dword [dword 0x84386c]; // subss // subss xmm1,dword [dword 0x84386c]
    xmm0 /= xmm2; // divss // divss xmm0,xmm2
    dword [esp+0xc] = xmm0; // movss // movss dword [esp+0xc],xmm0
    dword [esp] = xmm1; // movss // movss dword [esp],xmm1
    /* call */ loc_000001b0();
    xmm0 *= dword [esp+0xc]; // mulss // mulss xmm0,dword [esp+0xc]
    dword [esp+0x10] = xmm0; // movss // movss dword [esp+0x10],xmm0
    xmm0 = dword [esp+0x8]; // movss // movss xmm0,dword [esp+0x8]
}

// Function at 0x0040148b
void sub_0040148b() {
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

    xmm0 *= dword [esp+0x38]; // mulss // mulss xmm0,dword [esp+0x38]
}

// Function at 0x0040148d
void sub_0040148d() {
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

    xmm0 -= dword [dword 0x84386c]; // subss // subss xmm0,dword [dword 0x84386c]
    dword [esp] = xmm0; // movss // movss dword [esp],xmm0
    /* call */ loc_000001b0();
    xmm0 *= dword [esp+0xc]; // mulss // mulss xmm0,dword [esp+0xc]
    xmm2 = dword [esp+0x28]; // movss // movss xmm2,dword [esp+0x28]
    xmm6 = dword [esp+0x18]; // movss // movss xmm6,dword [esp+0x18]
    xmm3 = dword [esp+0x1c]; // movss // movss xmm3,dword [esp+0x1c]
    xmm4 = dword [esp+0x20]; // movss // movss xmm4,dword [esp+0x20]
    xmm5 = dword [esp+0x24]; // movss // movss xmm5,dword [esp+0x24]
    xmm1 = dword [esp+0x10]; // movss // movss xmm1,dword [esp+0x10]
    esp += +0x4; // add esp,byte +0x4
}

// Function at 0x004014bc
void sub_004014bc() {
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

    xmm7 = dword [dword 0x88e808]; // movss // movss xmm7,dword [dword 0x88e808]
    /* test */ flags_update((uint8_t)ebx & (uint8_t)ebx);
    ebx = pop(); // pop ebx
    if (zero_flag) goto loc_000004b3; // jz loc_000004b3
    xmm7 -= xmm0; // subss // subss xmm7,xmm0
    xmm0 = xmm7; // movaps // movaps xmm0,xmm7
}

// Function at 0x004014d0
void sub_004014d0() {
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

    xmm2 *= xmm0; // mulss // mulss xmm2,xmm0
    xmm6 *= xmm1; // mulss // mulss xmm6,xmm1
    xmm2 += xmm6; // addss // addss xmm2,xmm6
    dword [esi] = xmm2; // movss // movss dword [esi],xmm2
    xmm2 = dword [esp+0x24]; // movss // movss xmm2,dword [esp+0x24]
    xmm3 *= xmm1; // mulss // mulss xmm3,xmm1
    xmm2 *= xmm0; // mulss // mulss xmm2,xmm0
    xmm3 += xmm2; // addss // addss xmm3,xmm2
}

// Function at 0x004014e4
void sub_004014e4() {
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

    xmm2 = dword [esp+0x28]; // movss // movss xmm2,dword [esp+0x28]
    xmm4 *= xmm1; // mulss // mulss xmm4,xmm1
    xmm5 *= xmm1; // mulss // mulss xmm5,xmm1
    xmm1 = dword [esp+0x2c]; // movss // movss xmm1,dword [esp+0x2c]
    xmm2 *= xmm0; // mulss // mulss xmm2,xmm0
    xmm1 *= xmm0; // mulss // mulss xmm1,xmm0
    xmm4 += xmm2; // addss // addss xmm4,xmm2
}

// Function at 0x004014f6
void sub_004014f6() {
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

    xmm5 += xmm1; // addss // addss xmm5,xmm1
    dword [esi+0x4] = xmm3; // movss // movss dword [esi+0x4],xmm3
    dword [esi+0x8] = xmm4; // movss // movss dword [esi+0x8],xmm4
    dword [esi+0xc] = xmm5; // movss // movss dword [esi+0xc],xmm5
    esp += +0xc; // add esp,byte +0xc
    return; // ret 0x24
    /* int3 */
    /* int3 */
}

// Function at 0x00401514
void sub_00401514() {
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
}

// Function at 0x00401518
void sub_00401518() {
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

    esp &= byte -0x8; // and esp,byte -0x8
    esp -= +0x10; // sub esp,byte +0x10
    xmm5 = dword [dword 0x843488]; // movss // movss xmm5,dword [dword 0x843488]
    xmm6 = dword [ecx]; // movss // movss xmm6,dword [ecx]
    xmm3 = dword [ecx+0x14]; // movss // movss xmm3,dword [ecx+0x14]
    xmm0 = dword [ecx+0x28]; // movss // movss xmm0,dword [ecx+0x28]
    xmm1 = xmm5; // movaps // movaps xmm1,xmm5
    xmm1 -= xmm6; // subss // subss xmm1,xmm6
    xmm4 = xmm1; // movaps // movaps xmm4,xmm1
    xmm2 = xmm6; // movaps // movaps xmm2,xmm6
    xmm2 += xmm5; // addss // addss xmm2,xmm5
    xmm2 -= xmm3; // subss // subss xmm2,xmm3
    xmm2 -= xmm0; // subss // subss xmm2,xmm0
    xmm4 += xmm3; // addss // addss xmm4,xmm3
    xmm4 -= xmm0; // subss // subss xmm4,xmm0
    /* comiss xmm4,xmm2 */
    xmm1 -= xmm3; // subss // subss xmm1,xmm3
    xmm1 += xmm0; // addss // addss xmm1,xmm0
    xmm0 += xmm3; // addss // addss xmm0,xmm3
    xmm0 += xmm6; // addss // addss xmm0,xmm6
    xmm0 += xmm5; // addss // addss xmm0,xmm5
    dword [esp+0x4] = xmm2; // movss // movss dword [esp+0x4],xmm2
    dword [esp+0x8] = xmm4; // movss // movss dword [esp+0x8],xmm4
    dword [esp+0xc] = xmm1; // movss // movss dword [esp+0xc],xmm1
    dword [esp] = xmm0; // movss // movss dword [esp],xmm0
    xmm3 = xmm2; // movaps // movaps xmm3,xmm2
    /* jna loc_00000586 */
    xmm3 = xmm4; // movaps // movaps xmm3,xmm4
}

// Function at 0x00401572
void sub_00401572() {
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

    /* comiss xmm1,xmm3 */
    /* jna loc_0000058e */
    xmm3 = xmm1; // movaps // movaps xmm3,xmm1
}

// Function at 0x0040157e
void sub_0040157e() {
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

    /* comiss xmm0,xmm3 */
    /* jna loc_00000596 */
    xmm3 = xmm0; // movaps // movaps xmm3,xmm0
}

// Function at 0x0040158a
void sub_0040158a() {
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

    /* ucomiss */ flags_update_float(xmm3 - xmm0);
    ah = (uint8_t)flags; // lahf
    /* test */ flags_update((uint8_t)(eax >> 8) & 0x44);
    /* jpe 0x5f7 */
    fpu_push(dword [esp]); // fld dword [esp]
    xmm0 = dword [ecx+0x24]; // movss // movss xmm0,dword [ecx+0x24]
}

// Function at 0x004015a2
void sub_004015a2() {
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

    fpu_st0 *= fpu_st1; // fmul dword [dword 0x7ba55c]
    xmm0 -= dword [ecx+0x18]; // subss // subss xmm0,dword [ecx+0x18]
    fpu_st0 = sqrt(fpu_st0); // fsqrt
    /* fst dword [esp] */
    fpu_st0 *= fpu_st1; // fmul dword [dword 0x7d542c]
    xmm5 /= dword [esp]; // divss // divss xmm5,dword [esp]
}

// Function at 0x004015ae
void sub_004015ae() {
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

    xmm0 *= xmm5; // mulss // mulss xmm0,xmm5
    dword [edx] = xmm0; // movss // movss dword [edx],xmm0
    xmm0 = dword [ecx+0x8]; // movss // movss xmm0,dword [ecx+0x8]
    xmm0 -= dword [ecx+0x20]; // subss // subss xmm0,dword [ecx+0x20]
    xmm0 *= xmm5; // mulss // mulss xmm0,xmm5
    dword [edx+0x4] = xmm0; // movss // movss dword [edx+0x4],xmm0
    xmm0 = dword [ecx+0x10]; // movss // movss xmm0,dword [ecx+0x10]
    xmm0 -= dword [ecx+0x4]; // subss // subss xmm0,dword [ecx+0x4]
    dword [edx+0xc] = fpu_pop(); // fstp dword [edx+0xc]
    xmm0 *= xmm5; // mulss // mulss xmm0,xmm5
}

// Function at 0x004015ca
void sub_004015ca() {
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

    dword [edx+0x8] = xmm0; // movss // movss dword [edx+0x8],xmm0
    esp = ebp; // mov esp,ebp
    ebp = pop(); // pop ebp
    return; // ret
    /* ucomiss */ flags_update_float(xmm3 - xmm2);
    ah = (uint8_t)flags; // lahf
    /* test */ flags_update((uint8_t)(eax >> 8) & 0x44);
    /* jpe 0x65b */
    fpu_push(dword [esp+0x4]); // fld dword [esp+0x4]
    fpu_st0 *= fpu_st1; // fmul dword [dword 0x7ba55c]
    fpu_st0 = sqrt(fpu_st0); // fsqrt
    /* fst dword [esp+0x4] */
    fpu_st0 *= fpu_st1; // fmul dword [dword 0x7d542c]
    xmm5 /= dword [esp+0x4]; // divss // divss xmm5,dword [esp+0x4]
}

// Function at 0x004015f2
void sub_004015f2() {
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

    dword [edx] = fpu_pop(); // fstp dword [edx]
    xmm0 = dword [ecx+0x10]; // movss // movss xmm0,dword [ecx+0x10]
    xmm0 += dword [ecx+0x4]; // addss // addss xmm0,dword [ecx+0x4]
    xmm0 *= xmm5; // mulss // mulss xmm0,xmm5
    dword [edx+0x4] = xmm0; // movss // movss dword [edx+0x4],xmm0
    xmm0 = dword [ecx+0x20]; // movss // movss xmm0,dword [ecx+0x20]
    xmm0 += dword [ecx+0x8]; // addss // addss xmm0,dword [ecx+0x8]
    xmm0 *= xmm5; // mulss // mulss xmm0,xmm5
    dword [edx+0x8] = xmm0; // movss // movss dword [edx+0x8],xmm0
    xmm0 = dword [ecx+0x24]; // movss // movss xmm0,dword [ecx+0x24]
    xmm0 -= dword [ecx+0x18]; // subss // subss xmm0,dword [ecx+0x18]
    xmm0 *= xmm5; // mulss // mulss xmm0,xmm5
    dword [edx+0xc] = xmm0; // movss // movss dword [edx+0xc],xmm0
    esp = ebp; // mov esp,ebp
    ebp = pop(); // pop ebp
    return; // ret
    /* ucomiss */ flags_update_float(xmm3 - xmm4);
    ah = (uint8_t)flags; // lahf
    /* test */ flags_update((uint8_t)(eax >> 8) & 0x44);
}

// Function at 0x0040162a
void sub_0040162a() {
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

    /* jpe 0x6bf */
    fpu_push(dword [esp+0x8]); // fld dword [esp+0x8]
    xmm0 = dword [ecx+0x10]; // movss // movss xmm0,dword [ecx+0x10]
    fpu_st0 *= fpu_st1; // fmul dword [dword 0x7ba55c]
    xmm0 += dword [ecx+0x4]; // addss // addss xmm0,dword [ecx+0x4]
    fpu_st0 = sqrt(fpu_st0); // fsqrt
    /* fst dword [esp+0x8] */
}

// Function at 0x0040163e
void sub_0040163e() {
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

    fpu_st0 *= fpu_st1; // fmul dword [dword 0x7d542c]
    xmm5 /= dword [esp+0x8]; // divss // divss xmm5,dword [esp+0x8]
    xmm0 *= xmm5; // mulss // mulss xmm0,xmm5
    dword [edx] = xmm0; // movss // movss dword [edx],xmm0
    dword [edx+0x4] = fpu_pop(); // fstp dword [edx+0x4]
    xmm0 = dword [ecx+0x24]; // movss // movss xmm0,dword [ecx+0x24]
    xmm0 += dword [ecx+0x18]; // addss // addss xmm0,dword [ecx+0x18]
    xmm0 *= xmm5; // mulss // mulss xmm0,xmm5
    dword [edx+0x8] = xmm0; // movss // movss dword [edx+0x8],xmm0
    xmm0 = dword [ecx+0x8]; // movss // movss xmm0,dword [ecx+0x8]
}

// Function at 0x0040165a
void sub_0040165a() {
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

    xmm0 -= dword [ecx+0x20]; // subss // subss xmm0,dword [ecx+0x20]
    xmm0 *= xmm5; // mulss // mulss xmm0,xmm5
    dword [edx+0xc] = xmm0; // movss // movss dword [edx+0xc],xmm0
    esp = ebp; // mov esp,ebp
    ebp = pop(); // pop ebp
    return; // ret
    fpu_push(dword [esp+0xc]); // fld dword [esp+0xc]
    xmm0 = dword [ecx+0x20]; // movss // movss xmm0,dword [ecx+0x20]
    fpu_st0 *= fpu_st1; // fmul dword [dword 0x7ba55c]
    xmm0 += dword [ecx+0x8]; // addss // addss xmm0,dword [ecx+0x8]
    fpu_st0 = sqrt(fpu_st0); // fsqrt
    /* fst dword [esp+0xc] */
    fpu_st0 *= fpu_st1; // fmul dword [dword 0x7d542c]
    xmm5 /= dword [esp+0xc]; // divss // divss xmm5,dword [esp+0xc]
    xmm0 *= xmm5; // mulss // mulss xmm0,xmm5
    dword [edx] = xmm0; // movss // movss dword [edx],xmm0
    xmm0 = dword [ecx+0x24]; // movss // movss xmm0,dword [ecx+0x24]
    xmm0 += dword [ecx+0x18]; // addss // addss xmm0,dword [ecx+0x18]
    dword [edx+0x8] = fpu_pop(); // fstp dword [edx+0x8]
    xmm0 *= xmm5; // mulss // mulss xmm0,xmm5
    dword [edx+0x4] = xmm0; // movss // movss dword [edx+0x4],xmm0
    xmm0 = dword [ecx+0x10]; // movss // movss xmm0,dword [ecx+0x10]
    xmm0 -= dword [ecx+0x4]; // subss // subss xmm0,dword [ecx+0x4]
    xmm0 *= xmm5; // mulss // mulss xmm0,xmm5
    dword [edx+0xc] = xmm0; // movss // movss dword [edx+0xc],xmm0
    esp = ebp; // mov esp,ebp
    ebp = pop(); // pop ebp
}

// Function at 0x0040169e
void sub_0040169e() {
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

    return; // ret
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
}

// Function at 0x004016ac
void sub_004016ac() {
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

    esp -= +0x10; // sub esp,byte +0x10
    xmm1 = dword [ecx+0x8]; // movss // movss xmm1,dword [ecx+0x8]
    xmm4 = dword [ecx+0x4]; // movss // movss xmm4,dword [ecx+0x4]
    xmm2 = dword [ecx]; // movss // movss xmm2,dword [ecx]
    xmm3 = dword [dword 0x8451a0]; // movss // movss xmm3,dword [dword 0x8451a0]
    xmm0 = xmm2; // movaps // movaps xmm0,xmm2
    xmm0 *= xmm3; // mulss // mulss xmm0,xmm3
    xmm5 = xmm4; // movaps // movaps xmm5,xmm4
    xmm5 *= xmm3; // mulss // mulss xmm5,xmm3
    xmm6 = xmm1; // movaps // movaps xmm6,xmm1
    xmm6 *= xmm3; // mulss // mulss xmm6,xmm3
    xmm2 *= xmm0; // mulss // mulss xmm2,xmm0
    dword [esp] = xmm6; // movss // movss dword [esp],xmm6
}

// Function at 0x004016da
void sub_004016da() {
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

    xmm3 = xmm1; // movaps // movaps xmm3,xmm1
    xmm3 *= xmm6; // mulss // mulss xmm3,xmm6
    xmm6 = dword [ecx+0xc]; // movss // movss xmm6,dword [ecx+0xc]
    xmm7 = xmm6; // movaps // movaps xmm7,xmm6
    xmm7 *= xmm0; // mulss // mulss xmm7,xmm0
    dword [esp+0xc] = xmm7; // movss // movss dword [esp+0xc],xmm7
    xmm7 = xmm6; // movaps // movaps xmm7,xmm6
    xmm6 *= dword [esp]; // mulss // mulss xmm6,dword [esp]
    xmm7 *= xmm5; // mulss // mulss xmm7,xmm5
    dword [esp+0x4] = xmm7; // movss // movss dword [esp+0x4],xmm7
    dword [esp+0x8] = xmm2; // movss // movss dword [esp+0x8],xmm2
    xmm2 = xmm4; // movaps // movaps xmm2,xmm4
    xmm4 *= xmm0; // mulss // mulss xmm4,xmm0
    xmm7 = xmm4; // movaps // movaps xmm7,xmm4
    xmm4 = xmm1; // movaps // movaps xmm4,xmm1
    xmm4 *= xmm0; // mulss // mulss xmm4,xmm0
    xmm1 *= xmm5; // mulss // mulss xmm1,xmm5
    dword [esp] = xmm6; // movss // movss dword [esp],xmm6
    xmm2 *= xmm5; // mulss // mulss xmm2,xmm5
    xmm5 = dword [dword 0x843488]; // movss // movss xmm5,dword [dword 0x843488]
    xmm0 = xmm3; // movaps // movaps xmm0,xmm3
    xmm0 += xmm2; // addss // addss xmm0,xmm2
}

// Function at 0x00401720
void sub_00401720() {
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

    xmm6 = xmm5; // movaps // movaps xmm6,xmm5
    xmm6 -= xmm0; // subss // subss xmm6,xmm0
    dword [eax] = xmm6; // movss // movss dword [eax],xmm6
    xmm6 = dword [esp+0x8]; // movss // movss xmm6,dword [esp+0x8]
    xmm0 = xmm7; // movaps // movaps xmm0,xmm7
    xmm0 -= dword [esp]; // subss // subss xmm0,dword [esp]
    xmm7 += dword [esp]; // addss // addss xmm7,dword [esp]
    dword [eax+0x4] = xmm0; // movss // movss dword [eax+0x4],xmm0
    xmm0 = xmm4; // movaps // movaps xmm0,xmm4
    xmm0 += dword [esp+0x4]; // addss // addss xmm0,dword [esp+0x4]
    xmm4 -= dword [esp+0x4]; // subss // subss xmm4,dword [esp+0x4]
    dword [eax+0x8] = xmm0; // movss // movss dword [eax+0x8],xmm0
    xmm0 = 0.0f; // xorps (zero) // xorps xmm0,xmm0
    dword [eax+0xc] = xmm0; // movss // movss dword [eax+0xc],xmm0
    dword [eax+0x10] = xmm7; // movss // movss dword [eax+0x10],xmm7
    dword [eax+0x1c] = xmm0; // movss // movss dword [eax+0x1c],xmm0
    xmm3 += xmm6; // addss // addss xmm3,xmm6
    xmm7 = xmm5; // movaps // movaps xmm7,xmm5
    xmm7 -= xmm3; // subss // subss xmm7,xmm3
    xmm3 = dword [esp+0xc]; // movss // movss xmm3,dword [esp+0xc]
    dword [eax+0x14] = xmm7; // movss // movss dword [eax+0x14],xmm7
}

// Function at 0x00401764
void sub_00401764() {
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

    xmm7 = xmm1; // movaps // movaps xmm7,xmm1
    xmm1 += xmm3; // addss // addss xmm1,xmm3
    xmm7 -= xmm3; // subss // subss xmm7,xmm3
}

// Function at 0x0040176c
void sub_0040176c() {
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

    dword [eax+0x18] = xmm7; // movss // movss dword [eax+0x18],xmm7
    dword [eax+0x24] = xmm1; // movss // movss dword [eax+0x24],xmm1
    dword [eax+0x20] = xmm4; // movss // movss dword [eax+0x20],xmm4
    dword [eax+0x2c] = xmm0; // movss // movss dword [eax+0x2c],xmm0
    xmm2 += xmm6; // addss // addss xmm2,xmm6
    xmm1 = xmm5; // movaps // movaps xmm1,xmm5
}

// Function at 0x00401782
void sub_00401782() {
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

    xmm1 -= xmm2; // subss // subss xmm1,xmm2
    dword [eax+0x28] = xmm1; // movss // movss dword [eax+0x28],xmm1
    dword [eax+0x30] = xmm0; // movss // movss dword [eax+0x30],xmm0
    dword [eax+0x34] = xmm0; // movss // movss dword [eax+0x34],xmm0
    dword [eax+0x38] = xmm0; // movss // movss dword [eax+0x38],xmm0
}

// Function at 0x00401794
void sub_00401794() {
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

    dword [eax+0x3c] = xmm5; // movss // movss dword [eax+0x3c],xmm5
}

// Function at 0x00401798
void sub_00401798() {
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

    esp += +0x10; // add esp,byte +0x10
    return; // ret
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
}

// Function at 0x004017aa
void sub_004017aa() {
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

    xmm1 -= dword [esp+0x4]; // subss // subss xmm1,dword [esp+0x4]
    xmm0 = 0.0f; // xorps (zero) // xorps xmm0,xmm0
    /* comiss xmm0,xmm1 */
    /* jna loc_0000087c */
    xmm0 = dword [dword 0x88e808]; // movss // movss xmm0,dword [dword 0x88e808]
    xmm0 -= xmm1; // subss // subss xmm0,xmm1
    goto short loc_0000087f; // jmp short loc_0000087f
}

// Function at 0x004017be
void sub_004017be() {
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

    xmm0 = xmm1; // movaps // movaps xmm0,xmm1
}

// Function at 0x004017c2
void sub_004017c2() {
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

    xmm1 = dword [esp+0x8]; // movss // movss xmm1,dword [esp+0x8]
    /* comiss xmm1,xmm0 */
}

// Function at 0x004017c8
void sub_004017c8() {
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

    /* jna loc_00000890 */
    eax = 0x1; // mov eax,0x1
    return; // ret
}

// Function at 0x004017d6
void sub_004017d6() {
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

    eax = 0; // xor eax,eax
    return; // ret
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
}

// Function at 0x004017e4
void sub_004017e4() {
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

    /* int3 */
    /* int3 */
    /* int3 */
}

// Function at 0x004017ea
void sub_004017ea() {
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

    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
    /* int3 */
}

// Function at 0x004017f4
void sub_004017f4() {
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
    esp &= byte -0x10; // and esp,byte -0x10
}

// Function at 0x004017fa
void sub_004017fa() {
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

    esp -= +0x20; // sub esp,byte +0x20
    xmm2 = dword [eax+0x8]; // movss // movss xmm2,dword [eax+0x8]
    xmm2 -= dword [esi+0x38]; // subss // subss xmm2,dword [esi+0x38]
    xmm1 = dword [eax+0x4]; // movss // movss xmm1,dword [eax+0x4]
    xmm1 -= dword [esi+0x34]; // subss // subss xmm1,dword [esi+0x34]
    xmm0 = dword [eax]; // movss // movss xmm0,dword [eax]
    xmm0 -= dword [esi+0x30]; // subss // subss xmm0,dword [esi+0x30]
    xmm3 = xmm2; // movaps // movaps xmm3,xmm2
    xmm3 *= xmm2; // mulss // mulss xmm3,xmm2
    dword [esp+0x18] = xmm2; // movss // movss dword [esp+0x18],xmm2
    xmm2 = xmm1; // movaps // movaps xmm2,xmm1
    xmm2 *= xmm1; // mulss // mulss xmm2,xmm1
    dword [esp+0x14] = xmm1; // movss // movss dword [esp+0x14],xmm1
    xmm1 = xmm0; // movaps // movaps xmm1,xmm0
    xmm3 += xmm2; // addss // addss xmm3,xmm2
    xmm1 *= xmm0; // mulss // mulss xmm1,xmm0
    push(ecx); // push ecx
    xmm3 += xmm1; // addss // addss xmm3,xmm1
    dword [esp+0x14] = xmm0; // movss // movss dword [esp+0x14],xmm0
    dword [esp] = xmm3; // movss // movss dword [esp],xmm3
    /* call */ loc_00000010();
    /* fst dword [esp+0x10] */
    /* fldz */
    xmm4 = dword [dword 0x843488]; // movss // movss xmm4,dword [dword 0x843488]
    /* fxch st1 */
}

// Function at 0x0040184d
void sub_0040184d() {
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

    esp += +0x4; // add esp,byte +0x4
    /* fucomip st1 */
    st0 = fpu_pop(); // fstp st0
    ah = (uint8_t)flags; // lahf
    /* test */ flags_update((uint8_t)(eax >> 8) & 0x44);
    /* jpo 0x928 */
    xmm0 = xmm4; // movaps // movaps xmm0,xmm4
    xmm0 /= dword [esp+0xc]; // divss // divss xmm0,dword [esp+0xc]
    goto short loc_0000092e; // jmp short loc_0000092e
    xmm0 = dword [esp+0xc]; // movss // movss xmm0,dword [esp+0xc]
}

// Function at 0x00401871
void sub_00401871() {
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

    xmm1 = dword [esp+0x10]; // movss // movss xmm1,dword [esp+0x10]
    xmm2 = dword [esp+0x14]; // movss // movss xmm2,dword [esp+0x14]
}

// Function at 0x00401879
void sub_00401879() {
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

    xmm3 = dword [esp+0x18]; // movss // movss xmm3,dword [esp+0x18]
    xmm1 *= xmm0; // mulss // mulss xmm1,xmm0
    xmm2 *= xmm0; // mulss // mulss xmm2,xmm0
    xmm3 *= xmm0; // mulss // mulss xmm3,xmm0
    xmm0 = 0.0f; // xorps (zero) // xorps xmm0,xmm0
    dword [esi+0x20] = xmm1; // movss // movss dword [esi+0x20],xmm1
    dword [esi+0x24] = xmm2; // movss // movss dword [esi+0x24],xmm2
    dword [esi+0x28] = xmm3; // movss // movss dword [esi+0x28],xmm3
    xmm1 = dword [esi+0x24]; // movss // movss xmm1,dword [esi+0x24]
    /* comiss xmm0,xmm1 */
    dword [esi+0x2c] = xmm0; // movss // movss dword [esi+0x2c],xmm0
    /* jna loc_0000097b */
    xmm2 = dword [dword 0x88e808]; // movss // movss xmm2,dword [dword 0x88e808]
    xmm2 -= xmm1; // subss // subss xmm2,xmm1
    goto short loc_0000097e; // jmp short loc_0000097e
}

// Function at 0x004018a9
void sub_004018a9() {
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

    xmm2 = xmm1; // movaps // movaps xmm2,xmm1
}

// Function at 0x004018ad
void sub_004018ad() {
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

    xmm1 = dword [dword 0x843688]; // movss // movss xmm1,dword [dword 0x843688]
    /* comiss xmm1,xmm2 */
    dword [esi+0x10] = xmm0; // movss // movss dword [esi+0x10],xmm0
    dword [esi+0x1c] = xmm0; // movss // movss dword [esi+0x1c],xmm0
    /* jna loc_000009a1 */
    dword [esi+0x14] = xmm4; // movss // movss dword [esi+0x14],xmm4
    dword [esi+0x18] = xmm0; // movss // movss dword [esi+0x18],xmm0
    goto short loc_000009bb; // jmp short loc_000009bb
}

// Function at 0x004018cb
void sub_004018cb() {
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

    xmm1 = dword [dword 0x8475dc]; // movss // movss xmm1,dword [dword 0x8475dc]
    dword [esi+0x14] = xmm1; // movss // movss dword [esi+0x14],xmm1
    xmm1 = dword [dword 0x88edc4]; // movss // movss xmm1,dword [dword 0x88edc4]
    dword [esi+0x18] = xmm1; // movss // movss dword [esi+0x18],xmm1
}

// Function at 0x004018db
void sub_004018db() {
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

    xmm7 = dword [esi+0x28]; // movss // movss xmm7,dword [esi+0x28]
    xmm5 = dword [esi+0x24]; // movss // movss xmm5,dword [esi+0x24]
    xmm4 = dword [esi+0x18]; // movss // movss xmm4,dword [esi+0x18]
    xmm6 = dword [esi+0x14]; // movss // movss xmm6,dword [esi+0x14]
    xmm3 = dword [esi+0x10]; // movss // movss xmm3,dword [esi+0x10]
}

// Function at 0x004018ef
void sub_004018ef() {
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

    xmm2 = xmm3; // movaps // movaps xmm2,xmm3
    xmm1 = xmm7; // movaps // movaps xmm1,xmm7
    xmm1 *= xmm6; // mulss // mulss xmm1,xmm6
    xmm0 = xmm5; // movaps // movaps xmm0,xmm5
    xmm0 *= xmm4; // mulss // mulss xmm0,xmm4
    xmm0 -= xmm1; // subss // subss xmm0,xmm1
    xmm1 = dword [esi+0x20]; // movss // movss xmm1,dword [esi+0x20]
    xmm2 *= xmm7; // mulss // mulss xmm2,xmm7
    xmm7 = xmm1; // movaps // movaps xmm7,xmm1
    xmm1 *= xmm6; // mulss // mulss xmm1,xmm6
    xmm3 *= xmm5; // mulss // mulss xmm3,xmm5
    xmm1 -= xmm3; // subss // subss xmm1,xmm3
    xmm3 = xmm1; // movaps // movaps xmm3,xmm1
    xmm3 *= xmm1; // mulss // mulss xmm3,xmm1
    dword [esp+0x18] = xmm1; // movss // movss dword [esp+0x18],xmm1
    xmm7 *= xmm4; // mulss // mulss xmm7,xmm4
    xmm2 -= xmm7; // subss // subss xmm2,xmm7
    xmm1 = xmm2; // movaps // movaps xmm1,xmm2
    xmm1 *= xmm2; // mulss // mulss xmm1,xmm2
    xmm3 += xmm1; // addss // addss xmm3,xmm1
    xmm1 = xmm0; // movaps // movaps xmm1,xmm0
    xmm1 *= xmm0; // mulss // mulss xmm1,xmm0
    push(ecx); // push ecx
    xmm3 += xmm1; // addss // addss xmm3,xmm1
    dword [esp+0x14] = xmm0; // movss // movss dword [esp+0x14],xmm0
    dword [esp+0x18] = xmm2; // movss // movss dword [esp+0x18],xmm2
    dword [esp] = xmm3; // movss // movss dword [esp],xmm3
    /* call */ loc_00000010();
    /* fst dword [esp+0x10] */
    /* fldz */
    esp += +0x4; // add esp,byte +0x4
    /* fxch st1 */
    /* fucomip st1 */
    st0 = fpu_pop(); // fstp st0
    ah = (uint8_t)flags; // lahf
    /* test */ flags_update((uint8_t)(eax >> 8) & 0x44);
    /* jpo 0xa68 */
    xmm1 = dword [dword 0x843488]; // movss // movss xmm1,dword [dword 0x843488]
    xmm1 /= dword [esp+0xc]; // divss // divss xmm1,dword [esp+0xc]
    goto short loc_00000a6e; // jmp short loc_00000a6e
    xmm1 = dword [esp+0xc]; // movss // movss xmm1,dword [esp+0xc]
}

// Function at 0x00401970
void sub_00401970() {
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

    xmm2 = dword [esp+0x14]; // movss // movss xmm2,dword [esp+0x14]
    xmm4 = dword [esp+0x18]; // movss // movss xmm4,dword [esp+0x18]
    xmm7 = 0.0f; // xorps (zero) // xorps xmm7,xmm7
    xmm4 *= xmm1; // mulss // mulss xmm4,xmm1
    dword [esi+0x8] = xmm4; // movss // movss dword [esi+0x8],xmm4
}

// Function at 0x00401980
void sub_00401980() {
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

    xmm2 *= xmm1; // mulss // mulss xmm2,xmm1
    dword [esi+0x4] = xmm2; // movss // movss dword [esi+0x4],xmm2
    xmm0 = xmm1; // movaps // movaps xmm0,xmm1
    xmm0 *= dword [esp+0x10]; // mulss // mulss xmm0,dword [esp+0x10]
    dword [esi] = xmm0; // movss // movss dword [esi],xmm0
    dword [esi+0xc] = xmm7; // movss // movss dword [esi+0xc],xmm7
    xmm5 = dword [esi+0x28]; // movss // movss xmm5,dword [esi+0x28]
    xmm6 = dword [esi+0x24]; // movss // movss xmm6,dword [esi+0x24]
    xmm1 = xmm5; // movaps // movaps xmm1,xmm5
    xmm1 *= xmm2; // mulss // mulss xmm1,xmm2
    xmm2 = dword [esi+0x20]; // movss // movss xmm2,dword [esi+0x20]
    xmm0 = xmm6; // movaps // movaps xmm0,xmm6
    xmm0 *= xmm4; // mulss // mulss xmm0,xmm4
    xmm1 -= xmm0; // subss // subss xmm1,xmm0
    xmm0 = dword [esi]; // movss // movss xmm0,dword [esi]
    xmm3 = xmm2; // movaps // movaps xmm3,xmm2
    xmm2 *= dword [esi+0x4]; // mulss // mulss xmm2,dword [esi+0x4]
    xmm3 *= xmm4; // mulss // mulss xmm3,xmm4
    xmm4 = xmm0; // movaps // movaps xmm4,xmm0
    xmm4 *= xmm5; // mulss // mulss xmm4,xmm5
}

// Function at 0x004019c0
void sub_004019c0() {
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

    xmm0 *= xmm6; // mulss // mulss xmm0,xmm6
    xmm3 -= xmm4; // subss // subss xmm3,xmm4
}

// Function at 0x004019c4
void sub_004019c4() {
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

    xmm0 -= xmm2; // subss // subss xmm0,xmm2
    dword [esi+0x10] = xmm1; // movss // movss dword [esi+0x10],xmm1
    dword [esi+0x14] = xmm3; // movss // movss dword [esi+0x14],xmm3
    dword [esi+0x18] = xmm0; // movss // movss dword [esi+0x18],xmm0
    dword [esi+0x1c] = xmm7; // movss // movss dword [esi+0x1c],xmm7
    esp = ebp; // mov esp,ebp
    ebp = pop(); // pop ebp
    return; // ret
    /* int3 */
    /* int3 */
    /* int3 */
}

// Function at 0x004019e2
void sub_004019e2() {
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
    esp &= byte -0x10; // and esp,byte -0x10
    esp -= +0x38; // sub esp,byte +0x38
    xmm1 = dword [eax+0x4]; // movss // movss xmm1,dword [eax+0x4]
    xmm1 -= dword [ecx+0x4]; // subss // subss xmm1,dword [ecx+0x4]
    xmm3 = 0.0f; // xorps (zero) // xorps xmm3,xmm3
    xmm2 = dword [eax+0x8]; // movss // movss xmm2,dword [eax+0x8]
    xmm2 -= dword [ecx+0x8]; // subss // subss xmm2,dword [ecx+0x8]
}

// Function at 0x004019fc
void sub_004019fc() {
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

    xmm0 = dword [eax]; // movss // movss xmm0,dword [eax]
    xmm0 -= dword [ecx]; // subss // subss xmm0,dword [ecx]
    dword [esp+0x14] = xmm3; // movss // movss dword [esp+0x14],xmm3
    xmm3 = xmm1; // movaps // movaps xmm3,xmm1
    xmm3 *= xmm1; // mulss // mulss xmm3,xmm1
    dword [esp+0xc] = xmm1; // movss // movss dword [esp+0xc],xmm1
    ecx = *(uint32_t*)(esp + 0xc); // mov ecx,[esp+0xc]
    push(ebx); // push ebx
    ebx = *(uint32_t*)(ebp + 0x8); // mov ebx,[ebp+0x8]
    xmm1 = xmm2; // movaps // movaps xmm1,xmm2
    xmm1 *= xmm2; // mulss // mulss xmm1,xmm2
    xmm3 += xmm1; // addss // addss xmm3,xmm1
    push(edi); // push edi
    edi = *(uint32_t*)(esp + 0x1c); // mov edi,[esp+0x1c]
    dword [esp+0x10] = xmm0; // movss // movss dword [esp+0x10],xmm0
}

// Function at 0x00401a2c
void sub_00401a2c() {
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

    eax = *(uint32_t*)(esp + 0x10); // mov eax,[esp+0x10]
    dword [esp+0x18] = xmm2; // movss // movss dword [esp+0x18],xmm2
    edx = *(uint32_t*)(esp + 0x18); // mov edx,[esp+0x18]
    xmm1 = xmm0; // movaps // movaps xmm1,xmm0
    xmm1 *= xmm0; // mulss // mulss xmm1,xmm0
    push(ecx); // push ecx
    xmm3 += xmm1; // addss // addss xmm3,xmm1
    *(uint32_t*)(esp + 0x24) = eax; // mov [esp+0x24],eax
    *(uint32_t*)(esp + 0x28) = ecx; // mov [esp+0x28],ecx
    *(uint32_t*)(esp + 0x2c) = edx; // mov [esp+0x2c],edx
    *(uint32_t*)(esp + 0x30) = edi; // mov [esp+0x30],edi
    dword [esp] = xmm3; // movss // movss dword [esp],xmm3
}

// Function at 0x00401a56
void sub_00401a56() {
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

    /* call */ loc_00000010();
}

// Function at 0x00401a5f
void sub_00401a5f() {
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

    /* fst dword [esp+0x10] */
    /* fldz */
    esp += +0x4; // add esp,byte +0x4
}

// Function at 0x00401a69
void sub_00401a69() {
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

    /* fxch st1 */
    /* fucomip st1 */
    st0 = fpu_pop(); // fstp st0
    ah = (uint8_t)flags; // lahf
    /* test */ flags_update((uint8_t)(eax >> 8) & 0x44);
    /* jpo 0xbb2 */
    xmm0 = dword [dword 0x843488]; // movss // movss xmm0,dword [dword 0x843488]
    xmm0 /= dword [esp+0xc]; // divss // divss xmm0,dword [esp+0xc]
    goto short loc_00000bb8; // jmp short loc_00000bb8
    xmm0 = dword [esp+0xc]; // movss // movss xmm0,dword [esp+0xc]
}

// Function at 0x00401a89
void sub_00401a89() {
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

    xmm6 = dword [esp+0x10]; // movss // movss xmm6,dword [esp+0x10]
    xmm3 = dword [esp+0x24]; // movss // movss xmm3,dword [esp+0x24]
    xmm4 = dword [esp+0x28]; // movss // movss xmm4,dword [esp+0x28]
    xmm5 = dword [ebx+0x4]; // movss // movss xmm5,dword [ebx+0x4]
    xmm3 *= xmm0; // mulss // mulss xmm3,xmm0
    xmm4 *= xmm0; // mulss // mulss xmm4,xmm0
    xmm6 *= xmm0; // mulss // mulss xmm6,xmm0
    xmm0 = dword [ebx+0x8]; // movss // movss xmm0,dword [ebx+0x8]
    xmm2 = xmm0; // movaps // movaps xmm2,xmm0
    xmm2 *= xmm3; // mulss // mulss xmm2,xmm3
    xmm1 = xmm5; // movaps // movaps xmm1,xmm5
    xmm1 *= xmm4; // mulss // mulss xmm1,xmm4
    xmm1 -= xmm2; // subss // subss xmm1,xmm2
    xmm2 = dword [ebx]; // movss // movss xmm2,dword [ebx]
    xmm0 *= xmm6; // mulss // mulss xmm0,xmm6
    xmm7 = xmm2; // movaps // movaps xmm7,xmm2
    xmm2 *= xmm3; // mulss // mulss xmm2,xmm3
    dword [esp+0x24] = xmm3; // movss // movss dword [esp+0x24],xmm3
    xmm7 *= xmm4; // mulss // mulss xmm7,xmm4
    xmm0 -= xmm7; // subss // subss xmm0,xmm7
    xmm3 = xmm0; // movaps // movaps xmm3,xmm0
    xmm3 *= xmm0; // mulss // mulss xmm3,xmm0
    dword [esp+0x14] = xmm0; // movss // movss dword [esp+0x14],xmm0
}

// Function at 0x00401acf
void sub_00401acf() {
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

    ecx = *(uint32_t*)(esp + 0x14); // mov ecx,[esp+0x14]
    xmm5 *= xmm6; // mulss // mulss xmm5,xmm6
    xmm2 -= xmm5; // subss // subss xmm2,xmm5
    xmm0 = xmm2; // movaps // movaps xmm0,xmm2
    xmm0 *= xmm2; // mulss // mulss xmm0,xmm2
}

