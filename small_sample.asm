; .text section - Base address: 0x00401000
SECTION .text
ORG 0x00401000

loc_00000000:
    fld dword [esp+0x4]
    fld dword [esp+0x8]
    jmp loc_0039dbc8
    int3
    int3
    int3
loc_00000010:
    push ebp
    mov ebp,esp
    and esp,byte -0x8
    fld dword [ebp+0x8]
    fsqrt
    mov esp,ebp
    pop ebp
    ret
    int3
loc_00000020:
    sub esp,byte +0xc
    push ebx
loc_00000024:
    mov ebx,[esp+0x18]
    push ebp
    mov ebp,[esp+0x18]
    push esi
    mov esi,[ebp+0x0]
    test esi,esi
    jz loc_00000049
    cmp esi,0x7d3ddb
    jz loc_00000049
    call loc_00213170
    mov dword [ebp+0x0],0x7d3ddb
loc_00000049:
    test ebx,ebx
    jz loc_0000009e
    cmp byte [ebx],0x0
    jz loc_0000009e
    mov eax,ebx
    lea edx,[eax+0x1]
loc_00000057:
    mov cl,[eax]
    add eax,byte +0x1
    test cl,cl
    jnz loc_00000057
    push edi
    sub eax,edx
    lea edi,[eax+0x1]
    push dword 0x7d3ddc
    push edi
    lea esi,[esp+0x18]
    mov dword [esp+0x18],0x4
    mov dword [esp+0x1c],0x1
    mov dword [esp+0x20],0x0
    call loc_002131b0
    push edi
    mov esi,eax
    push ebx
    push esi
    call loc_0039ac6a
    add esp,byte +0x14
    mov [ebp+0x0],esi
    pop edi
loc_0000009e:
    pop esi
    pop ebp
    pop ebx
    add esp,byte +0xc
    ret 0x8
    int3
    int3
loc_000000a9:
    int3
    int3
loc_000000ab:
    int3
    int3
    int3
    int3
    int3
loc_000000b0:
    mov eax,ecx
    ret
    int3
    int3
loc_000000b5:
    int3
    int3
    int3
    int3
    int3
loc_000000ba:
    int3
    int3
    int3
    int3
    int3
    int3
    test byte [esp+0x4],0x1
loc_000000c5:
    push esi
    mov esi,ecx
    mov dword [esi],0x8475e0
    mov dword [dword 0xe6b298],0x0
    jz loc_000000e3
    push esi
    call loc_00213120
    add esp,byte +0x4
loc_000000e3:
    mov eax,esi
    pop esi
    ret 0x4
    int3
    int3
    int3
    int3
    int3
    int3
    int3
loc_000000f0:
    push edi
    mov edi,[esp+0x10]
    sub edi,byte +0x1
    js loc_0000011e
    push ebx
    mov ebx,[esp+0x18]
    push ebp
    mov ebp,[esp+0x14]
    push esi
    mov esi,[esp+0x14]
    lea esp,[esp+0x0]
loc_00000110:
    mov ecx,esi
    call ebx
    add esi,ebp
    sub edi,byte +0x1
    jns loc_00000110
    pop esi
    pop ebp
    pop ebx
loc_0000011e:
    pop edi
    ret 0x10
loc_00000122:
    int3
    int3
    int3
    int3
    int3
    int3
    int3
    int3
    int3
    int3
    int3
    int3
    int3
    int3
loc_00000130:
    push ebx
    mov ebx,[esp+0xc]
    push esi
    mov esi,[esp+0xc]
    push edi
    mov edi,[esp+0x18]
    mov eax,ebx
    imul eax,edi
    add esi,eax
    sub edi,byte +0x1
    js loc_0000015c
    push ebp
    mov ebp,[esp+0x20]
loc_00000150:
    sub esi,ebx
    mov ecx,esi
    call ebp
    sub edi,byte +0x1
    jns loc_00000150
    pop ebp
loc_0000015c:
    pop edi
    pop esi
    pop ebx
    ret 0x10
    int3
    int3
loc_00000164:
    int3
    int3
    int3
    int3
    int3
    int3
loc_0000016a:
    int3
loc_0000016b:
    int3
    int3
    int3
    int3
    int3
loc_00000170:
    jmp loc_00a77000
    add [edi+0x74],esp
    jz loc_0000017b
    add [eax],al
    add [eax],al
    add [eax],al
    add [eax],al
    add [eax],al
    add [eax],al
    scasd
    jz loc_000001fd
    add [eax],eax
    add [eax],al
    add [eax],al
    add [eax],al
    add [eax],al
loc_00000193:
    add [eax],al
    add bh,dh
    jz loc_0000020d
    add [eax],eax
    add [eax],al
    add [eax],al
    add [eax],al
    add [eax],al
    add [eax],al
    add [ecx+0x1754590],ah
    jmp loc_001b6e91
loc_000001b0:
    push ebp
    mov ebp,esp
    sub esp,byte +0x20
    movss xmm0,dword [ebp+0x8]
    movaps xmm1,xmm0
    mulss xmm1,dword [dword 0x8d10f0]
    cvttss2si eax,xmm1
    movss xmm1,dword [dword 0x8d10f8]
    cvtsi2ss xmm2,eax
    mulss xmm2,xmm1
loc_000001da:
    subss xmm0,xmm2
    subss xmm1,xmm0
    minss xmm0,xmm1
    movss xmm1,dword [dword 0x8d10f4]
    subss xmm1,xmm0
    minss xmm0,xmm1
    movss xmm2,dword [dword 0x8d0ff0]
    movss xmm3,dword [dword 0x8d0ff4]
    subss xmm1,xmm0
    movss dword [ebp-0x20],xmm1
    mulss xmm0,xmm0
    mulss xmm2,xmm0
    addss xmm2,dword [dword 0x8afa70]
    movaps xmm1,xmm0
    mulss xmm1,xmm0
    mulss xmm3,xmm1
    addss xmm3,xmm2
    movss xmm2,dword [dword 0x8d0ff8]
    mulss xmm1,xmm0
    mulss xmm2,xmm1
    addss xmm2,xmm3
    mulss xmm1,xmm0
    movaps xmm3,xmm1
    movss xmm1,dword [dword 0x8d0ffc]
    mulss xmm1,xmm3
    addss xmm1,xmm2
    movss xmm2,dword [dword 0x8d1000]
    mulss xmm3,xmm0
    mulss xmm2,xmm3
loc_00000269:
    addss xmm2,xmm1
    mulss xmm3,xmm0
loc_00000271:
    movaps xmm1,xmm3
    movss xmm3,dword [dword 0x8d1004]
    mulss xmm3,xmm1
    mulss xmm1,xmm0
    addss xmm3,xmm2
    movss xmm2,dword [dword 0x8d1008]
    mulss xmm2,xmm1
    mulss xmm1,xmm0
    xorps xmm0,xmm0
    mulss xmm1,dword [dword 0x8d100c]
    addss xmm2,xmm3
    addss xmm1,xmm2
    movss dword [ebp-0x10],xmm1
    movss xmm0,dword [ebp-0x20]
    ucomiss xmm0,dword [dword 0x845314]
loc_000002bc:
    lahf
    test ah,0x44
    jpe 0x2d3
    movss xmm0,dword [dword 0x88e808]
    subss xmm0,dword [ebp-0x10]
    mov esp,ebp
    pop ebp
    ret
    movss xmm0,dword [ebp-0x10]
    mov esp,ebp
    pop ebp
    ret
    int3
    int3
    int3
    int3
loc_000002e0:
    fld dword [ecx]
    xorps xmm0,xmm0
    fstp dword [eax+0x10]
    fld dword [ecx+0x4]
    fstp dword [eax+0x14]
loc_000002ee:
    fld dword [ecx+0x8]
    fstp dword [eax+0x18]
    fld dword [ecx+0xc]
    fstp dword [eax+0x1c]
loc_000002fa:
    movss dword [eax+0x1c],xmm0
    ret
loc_00000300:
    fld dword [ecx]
    xorps xmm0,xmm0
    fstp dword [eax+0x20]
loc_00000308:
    fld dword [ecx+0x4]
    fstp dword [eax+0x24]
    fld dword [ecx+0x8]
    fstp dword [eax+0x28]
    fld dword [ecx+0xc]
    fstp dword [eax+0x2c]
    movss dword [eax+0x2c],xmm0
    ret
loc_00000320:
    fld dword [ecx]
    movss xmm0,dword [dword 0x843488]
    fstp dword [eax+0x30]
    fld dword [ecx+0x4]
    fstp dword [eax+0x34]
    fld dword [ecx+0x8]
    fstp dword [eax+0x38]
    fld dword [ecx+0xc]
    fstp dword [eax+0x3c]
    movss dword [eax+0x3c],xmm0
    ret
    int3
    int3
    int3
    int3
loc_00000349:
    int3
    int3
    int3
    int3
    int3
    int3
    int3
loc_00000350:
    sub esp,byte +0xc
    movss xmm2,dword [esp+0x20]
    movss xmm6,dword [esp+0x10]
    movss xmm0,dword [esp+0x24]
loc_00000365:
    movss xmm3,dword [esp+0x14]
    movss xmm4,dword [esp+0x18]
    movss xmm5,dword [esp+0x1c]
    xorps xmm7,xmm7
    mulss xmm0,xmm3
    movaps xmm1,xmm2
    mulss xmm1,xmm6
    addss xmm1,xmm0
    movaps xmm0,xmm4
    mulss xmm0,dword [esp+0x28]
    addss xmm1,xmm0
    movss xmm0,dword [esp+0x2c]
    mulss xmm0,xmm5
    addss xmm1,xmm0
    comiss xmm7,xmm1
    movss xmm0,dword [esp+0x30]
    push ebx
    movss dword [esp+0x4],xmm1
    jna loc_000003cf
    movss xmm7,dword [dword 0x88e808]
loc_000003be:
    subss xmm7,xmm1
    movaps xmm1,xmm7
    movss dword [esp+0x4],xmm1
    mov bl,0x1
    jmp short loc_000003d1
loc_000003cf:
    xor bl,bl
loc_000003d1:
    comiss xmm1,dword [dword 0x88ea5c]
    jna loc_000003ed
    movss xmm1,dword [dword 0x843488]
    subss xmm1,dword [esp+0x34]
    jmp loc_0000049f
loc_000003ed:
    fld dword [esp+0x4]
    push ecx
    fstp dword [esp]
    call loc_001824c0
    movss dword [esp+0x8],xmm0
loc_00000400:
    subss xmm0,dword [dword 0x84386c]
    movss dword [esp],xmm0
    call loc_000001b0
    movss xmm1,dword [dword 0x843488]
    movaps xmm2,xmm0
    movaps xmm0,xmm1
    subss xmm1,dword [esp+0x38]
    mulss xmm1,dword [esp+0x8]
    subss xmm1,dword [dword 0x84386c]
    divss xmm0,xmm2
    movss dword [esp+0xc],xmm0
    movss dword [esp],xmm1
    call loc_000001b0
    mulss xmm0,dword [esp+0xc]
    movss dword [esp+0x10],xmm0
    movss xmm0,dword [esp+0x8]
loc_0000045a:
    mulss xmm0,dword [esp+0x38]
loc_00000460:
    subss xmm0,dword [dword 0x84386c]
    movss dword [esp],xmm0
    call loc_000001b0
    mulss xmm0,dword [esp+0xc]
    movss xmm2,dword [esp+0x28]
    movss xmm6,dword [esp+0x18]
    movss xmm3,dword [esp+0x1c]
    movss xmm4,dword [esp+0x20]
    movss xmm5,dword [esp+0x24]
    movss xmm1,dword [esp+0x10]
    add esp,byte +0x4
loc_0000049f:
    movss xmm7,dword [dword 0x88e808]
    test bl,bl
    pop ebx
    jz loc_000004b3
    subss xmm7,xmm0
    movaps xmm0,xmm7
loc_000004b3:
    mulss xmm2,xmm0
    mulss xmm6,xmm1
    addss xmm2,xmm6
    movss dword [esi],xmm2
    movss xmm2,dword [esp+0x24]
    mulss xmm3,xmm1
    mulss xmm2,xmm0
    addss xmm3,xmm2
loc_000004d5:
    movss xmm2,dword [esp+0x28]
    mulss xmm4,xmm1
    mulss xmm5,xmm1
    movss xmm1,dword [esp+0x2c]
    mulss xmm2,xmm0
    mulss xmm1,xmm0
    addss xmm4,xmm2
loc_000004f5:
    addss xmm5,xmm1
    movss dword [esi+0x4],xmm3
    movss dword [esi+0x8],xmm4
    movss dword [esi+0xc],xmm5
    add esp,byte +0xc
    ret 0x24
    int3
    int3
loc_00000510:
    push ebp
    mov ebp,esp
loc_00000513:
    and esp,byte -0x8
    sub esp,byte +0x10
    movss xmm5,dword [dword 0x843488]
    movss xmm6,dword [ecx]
    movss xmm3,dword [ecx+0x14]
    movss xmm0,dword [ecx+0x28]
    movaps xmm1,xmm5
    subss xmm1,xmm6
    movaps xmm4,xmm1
    movaps xmm2,xmm6
    addss xmm2,xmm5
    subss xmm2,xmm3
    subss xmm2,xmm0
    addss xmm4,xmm3
    subss xmm4,xmm0
    comiss xmm4,xmm2
    subss xmm1,xmm3
    addss xmm1,xmm0
    addss xmm0,xmm3
    addss xmm0,xmm6
    addss xmm0,xmm5
    movss dword [esp+0x4],xmm2
    movss dword [esp+0x8],xmm4
    movss dword [esp+0xc],xmm1
    movss dword [esp],xmm0
    movaps xmm3,xmm2
    jna loc_00000586
    movaps xmm3,xmm4
loc_00000586:
    comiss xmm1,xmm3
    jna loc_0000058e
    movaps xmm3,xmm1
loc_0000058e:
    comiss xmm0,xmm3
    jna loc_00000596
    movaps xmm3,xmm0
loc_00000596:
    ucomiss xmm3,xmm0
    lahf
    test ah,0x44
    jpe 0x5f7
    fld dword [esp]
    movss xmm0,dword [ecx+0x24]
loc_000005a7:
    fmul dword [dword 0x7ba55c]
    subss xmm0,dword [ecx+0x18]
    fsqrt
    fst dword [esp]
    fmul dword [dword 0x7d542c]
    divss xmm5,dword [esp]
loc_000005c2:
    mulss xmm0,xmm5
    movss dword [edx],xmm0
    movss xmm0,dword [ecx+0x8]
    subss xmm0,dword [ecx+0x20]
    mulss xmm0,xmm5
    movss dword [edx+0x4],xmm0
    movss xmm0,dword [ecx+0x10]
    subss xmm0,dword [ecx+0x4]
    fstp dword [edx+0xc]
    mulss xmm0,xmm5
loc_000005ee:
    movss dword [edx+0x8],xmm0
    mov esp,ebp
    pop ebp
    ret
    ucomiss xmm3,xmm2
    lahf
    test ah,0x44
    jpe 0x65b
    fld dword [esp+0x4]
    fmul dword [dword 0x7ba55c]
    fsqrt
    fst dword [esp+0x4]
    fmul dword [dword 0x7d542c]
    divss xmm5,dword [esp+0x4]
loc_0000061c:
    fstp dword [edx]
    movss xmm0,dword [ecx+0x10]
    addss xmm0,dword [ecx+0x4]
    mulss xmm0,xmm5
    movss dword [edx+0x4],xmm0
    movss xmm0,dword [ecx+0x20]
    addss xmm0,dword [ecx+0x8]
    mulss xmm0,xmm5
    movss dword [edx+0x8],xmm0
    movss xmm0,dword [ecx+0x24]
    subss xmm0,dword [ecx+0x18]
    mulss xmm0,xmm5
    movss dword [edx+0xc],xmm0
    mov esp,ebp
    pop ebp
    ret
    ucomiss xmm3,xmm4
    lahf
    test ah,0x44
loc_00000662:
    jpe 0x6bf
    fld dword [esp+0x8]
    movss xmm0,dword [ecx+0x10]
    fmul dword [dword 0x7ba55c]
    addss xmm0,dword [ecx+0x4]
    fsqrt
    fst dword [esp+0x8]
loc_0000067e:
    fmul dword [dword 0x7d542c]
    divss xmm5,dword [esp+0x8]
    mulss xmm0,xmm5
    movss dword [edx],xmm0
    fstp dword [edx+0x4]
    movss xmm0,dword [ecx+0x24]
    addss xmm0,dword [ecx+0x18]
    mulss xmm0,xmm5
    movss dword [edx+0x8],xmm0
    movss xmm0,dword [ecx+0x8]
loc_000006ad:
    subss xmm0,dword [ecx+0x20]
    mulss xmm0,xmm5
    movss dword [edx+0xc],xmm0
    mov esp,ebp
    pop ebp
    ret
    fld dword [esp+0xc]
    movss xmm0,dword [ecx+0x20]
    fmul dword [dword 0x7ba55c]
    addss xmm0,dword [ecx+0x8]
    fsqrt
    fst dword [esp+0xc]
    fmul dword [dword 0x7d542c]
    divss xmm5,dword [esp+0xc]
    mulss xmm0,xmm5
    movss dword [edx],xmm0
    movss xmm0,dword [ecx+0x24]
    addss xmm0,dword [ecx+0x18]
    fstp dword [edx+0x8]
    mulss xmm0,xmm5
    movss dword [edx+0x4],xmm0
    movss xmm0,dword [ecx+0x10]
    subss xmm0,dword [ecx+0x4]
    mulss xmm0,xmm5
    movss dword [edx+0xc],xmm0
    mov esp,ebp
    pop ebp
loc_00000719:
    ret
    int3
    int3
    int3
    int3
    int3
    int3
loc_00000720:
    sub esp,byte +0x10
    movss xmm1,dword [ecx+0x8]
    movss xmm4,dword [ecx+0x4]
    movss xmm2,dword [ecx]
    movss xmm3,dword [dword 0x8451a0]
    movaps xmm0,xmm2
    mulss xmm0,xmm3
    movaps xmm5,xmm4
    mulss xmm5,xmm3
    movaps xmm6,xmm1
    mulss xmm6,xmm3
    mulss xmm2,xmm0
    movss dword [esp],xmm6
loc_00000757:
    movaps xmm3,xmm1
    mulss xmm3,xmm6
    movss xmm6,dword [ecx+0xc]
    movaps xmm7,xmm6
    mulss xmm7,xmm0
    movss dword [esp+0xc],xmm7
    movaps xmm7,xmm6
    mulss xmm6,dword [esp]
    mulss xmm7,xmm5
    movss dword [esp+0x4],xmm7
    movss dword [esp+0x8],xmm2
    movaps xmm2,xmm4
    mulss xmm4,xmm0
    movaps xmm7,xmm4
    movaps xmm4,xmm1
    mulss xmm4,xmm0
    mulss xmm1,xmm5
    movss dword [esp],xmm6
    mulss xmm2,xmm5
    movss xmm5,dword [dword 0x843488]
    movaps xmm0,xmm3
    addss xmm0,xmm2
loc_000007b5:
    movaps xmm6,xmm5
    subss xmm6,xmm0
    movss dword [eax],xmm6
    movss xmm6,dword [esp+0x8]
    movaps xmm0,xmm7
    subss xmm0,dword [esp]
    addss xmm7,dword [esp]
    movss dword [eax+0x4],xmm0
    movaps xmm0,xmm4
    addss xmm0,dword [esp+0x4]
    subss xmm4,dword [esp+0x4]
    movss dword [eax+0x8],xmm0
    xorps xmm0,xmm0
    movss dword [eax+0xc],xmm0
    movss dword [eax+0x10],xmm7
    movss dword [eax+0x1c],xmm0
    addss xmm3,xmm6
    movaps xmm7,xmm5
    subss xmm7,xmm3
    movss xmm3,dword [esp+0xc]
    movss dword [eax+0x14],xmm7
loc_00000814:
    movaps xmm7,xmm1
    addss xmm1,xmm3
    subss xmm7,xmm3
loc_0000081f:
    movss dword [eax+0x18],xmm7
    movss dword [eax+0x24],xmm1
    movss dword [eax+0x20],xmm4
    movss dword [eax+0x2c],xmm0
    addss xmm2,xmm6
    movaps xmm1,xmm5
loc_0000083a:
    subss xmm1,xmm2
    movss dword [eax+0x28],xmm1
    movss dword [eax+0x30],xmm0
    movss dword [eax+0x34],xmm0
    movss dword [eax+0x38],xmm0
loc_00000852:
    movss dword [eax+0x3c],xmm5
loc_00000857:
    add esp,byte +0x10
    ret
    int3
    int3
    int3
    int3
    int3
loc_00000860:
    subss xmm1,dword [esp+0x4]
    xorps xmm0,xmm0
    comiss xmm0,xmm1
    jna loc_0000087c
    movss xmm0,dword [dword 0x88e808]
    subss xmm0,xmm1
    jmp short loc_0000087f
loc_0000087c:
    movaps xmm0,xmm1
loc_0000087f:
    movss xmm1,dword [esp+0x8]
    comiss xmm1,xmm0
loc_00000888:
    jna loc_00000890
    mov eax,0x1
    ret
loc_00000890:
    xor eax,eax
    ret
    int3
    int3
    int3
    int3
    int3
loc_00000898:
    int3
    int3
    int3
loc_0000089b:
    int3
    int3
    int3
    int3
    int3
loc_000008a0:
    push ebp
    mov ebp,esp
    and esp,byte -0x10
loc_000008a6:
    sub esp,byte +0x20
    movss xmm2,dword [eax+0x8]
    subss xmm2,dword [esi+0x38]
    movss xmm1,dword [eax+0x4]
    subss xmm1,dword [esi+0x34]
    movss xmm0,dword [eax]
    subss xmm0,dword [esi+0x30]
    movaps xmm3,xmm2
    mulss xmm3,xmm2
    movss dword [esp+0x18],xmm2
    movaps xmm2,xmm1
    mulss xmm2,xmm1
    movss dword [esp+0x14],xmm1
    movaps xmm1,xmm0
    addss xmm3,xmm2
    mulss xmm1,xmm0
    push ecx
    addss xmm3,xmm1
    movss dword [esp+0x14],xmm0
    movss dword [esp],xmm3
    call loc_00000010
    fst dword [esp+0x10]
    fldz
    movss xmm4,dword [dword 0x843488]
    fxch st1
loc_00000910:
    add esp,byte +0x4
    fucomip st1
    fstp st0
    lahf
    test ah,0x44
    jpo 0x928
    movaps xmm0,xmm4
    divss xmm0,dword [esp+0xc]
    jmp short loc_0000092e
    movss xmm0,dword [esp+0xc]
loc_0000092e:
    movss xmm1,dword [esp+0x10]
    movss xmm2,dword [esp+0x14]
loc_0000093a:
    movss xmm3,dword [esp+0x18]
    mulss xmm1,xmm0
    mulss xmm2,xmm0
    mulss xmm3,xmm0
    xorps xmm0,xmm0
    movss dword [esi+0x20],xmm1
    movss dword [esi+0x24],xmm2
    movss dword [esi+0x28],xmm3
    movss xmm1,dword [esi+0x24]
    comiss xmm0,xmm1
    movss dword [esi+0x2c],xmm0
    jna loc_0000097b
    movss xmm2,dword [dword 0x88e808]
    subss xmm2,xmm1
    jmp short loc_0000097e
loc_0000097b:
    movaps xmm2,xmm1
loc_0000097e:
    movss xmm1,dword [dword 0x843688]
    comiss xmm1,xmm2
    movss dword [esi+0x10],xmm0
    movss dword [esi+0x1c],xmm0
    jna loc_000009a1
    movss dword [esi+0x14],xmm4
    movss dword [esi+0x18],xmm0
    jmp short loc_000009bb
loc_000009a1:
    movss xmm1,dword [dword 0x8475dc]
    movss dword [esi+0x14],xmm1
    movss xmm1,dword [dword 0x88edc4]
    movss dword [esi+0x18],xmm1
loc_000009bb:
    movss xmm7,dword [esi+0x28]
    movss xmm5,dword [esi+0x24]
    movss xmm4,dword [esi+0x18]
    movss xmm6,dword [esi+0x14]
    movss xmm3,dword [esi+0x10]
loc_000009d4:
    movaps xmm2,xmm3
    movaps xmm1,xmm7
    mulss xmm1,xmm6
    movaps xmm0,xmm5
    mulss xmm0,xmm4
    subss xmm0,xmm1
    movss xmm1,dword [esi+0x20]
    mulss xmm2,xmm7
    movaps xmm7,xmm1
    mulss xmm1,xmm6
    mulss xmm3,xmm5
    subss xmm1,xmm3
    movaps xmm3,xmm1
    mulss xmm3,xmm1
    movss dword [esp+0x18],xmm1
    mulss xmm7,xmm4
    subss xmm2,xmm7
    movaps xmm1,xmm2
    mulss xmm1,xmm2
    addss xmm3,xmm1
    movaps xmm1,xmm0
    mulss xmm1,xmm0
    push ecx
    addss xmm3,xmm1
    movss dword [esp+0x14],xmm0
    movss dword [esp+0x18],xmm2
    movss dword [esp],xmm3
    call loc_00000010
    fst dword [esp+0x10]
    fldz
    add esp,byte +0x4
    fxch st1
    fucomip st1
    fstp st0
    lahf
    test ah,0x44
    jpo 0xa68
    movss xmm1,dword [dword 0x843488]
    divss xmm1,dword [esp+0xc]
    jmp short loc_00000a6e
    movss xmm1,dword [esp+0xc]
loc_00000a6e:
    movss xmm2,dword [esp+0x14]
    movss xmm4,dword [esp+0x18]
    xorps xmm7,xmm7
    mulss xmm4,xmm1
    movss dword [esi+0x8],xmm4
loc_00000a86:
    mulss xmm2,xmm1
    movss dword [esi+0x4],xmm2
    movaps xmm0,xmm1
    mulss xmm0,dword [esp+0x10]
    movss dword [esi],xmm0
    movss dword [esi+0xc],xmm7
    movss xmm5,dword [esi+0x28]
    movss xmm6,dword [esi+0x24]
    movaps xmm1,xmm5
    mulss xmm1,xmm2
    movss xmm2,dword [esi+0x20]
    movaps xmm0,xmm6
    mulss xmm0,xmm4
    subss xmm1,xmm0
    movss xmm0,dword [esi]
    movaps xmm3,xmm2
    mulss xmm2,dword [esi+0x4]
    mulss xmm3,xmm4
    movaps xmm4,xmm0
    mulss xmm4,xmm5
loc_00000ad9:
    mulss xmm0,xmm6
    subss xmm3,xmm4
loc_00000ae1:
    subss xmm0,xmm2
    movss dword [esi+0x10],xmm1
    movss dword [esi+0x14],xmm3
    movss dword [esi+0x18],xmm0
    movss dword [esi+0x1c],xmm7
    mov esp,ebp
    pop ebp
    ret
    int3
    int3
    int3
loc_00000b00:
    push ebp
    mov ebp,esp
    and esp,byte -0x10
    sub esp,byte +0x38
    movss xmm1,dword [eax+0x4]
    subss xmm1,dword [ecx+0x4]
    xorps xmm3,xmm3
    movss xmm2,dword [eax+0x8]
    subss xmm2,dword [ecx+0x8]
loc_00000b20:
    movss xmm0,dword [eax]
    subss xmm0,dword [ecx]
    movss dword [esp+0x14],xmm3
    movaps xmm3,xmm1
    mulss xmm3,xmm1
    movss dword [esp+0xc],xmm1
    mov ecx,[esp+0xc]
    push ebx
    mov ebx,[ebp+0x8]
    movaps xmm1,xmm2
    mulss xmm1,xmm2
    addss xmm3,xmm1
    push edi
    mov edi,[esp+0x1c]
    movss dword [esp+0x10],xmm0
loc_00000b59:
    mov eax,[esp+0x10]
    movss dword [esp+0x18],xmm2
    mov edx,[esp+0x18]
    movaps xmm1,xmm0
    mulss xmm1,xmm0
    push ecx
    addss xmm3,xmm1
    mov [esp+0x24],eax
    mov [esp+0x28],ecx
    mov [esp+0x2c],edx
    mov [esp+0x30],edi
    movss dword [esp],xmm3
loc_00000b88:
    call loc_00000010
loc_00000b8d:
    fst dword [esp+0x10]
    fldz
    add esp,byte +0x4
loc_00000b96:
    fxch st1
    fucomip st1
    fstp st0
    lahf
    test ah,0x44
    jpo 0xbb2
    movss xmm0,dword [dword 0x843488]
    divss xmm0,dword [esp+0xc]
    jmp short loc_00000bb8
    movss xmm0,dword [esp+0xc]
loc_00000bb8:
    movss xmm6,dword [esp+0x10]
    movss xmm3,dword [esp+0x24]
    movss xmm4,dword [esp+0x28]
    movss xmm5,dword [ebx+0x4]
    mulss xmm3,xmm0
    mulss xmm4,xmm0
    mulss xmm6,xmm0
    movss xmm0,dword [ebx+0x8]
    movaps xmm2,xmm0
    mulss xmm2,xmm3
    movaps xmm1,xmm5
    mulss xmm1,xmm4
    subss xmm1,xmm2
    movss xmm2,dword [ebx]
    mulss xmm0,xmm6
    movaps xmm7,xmm2
    mulss xmm2,xmm3
    movss dword [esp+0x24],xmm3
    mulss xmm7,xmm4
    subss xmm0,xmm7
    movaps xmm3,xmm0
    mulss xmm3,xmm0
    movss dword [esp+0x14],xmm0
loc_00000c1c:
    mov ecx,[esp+0x14]
    mulss xmm5,xmm6
    subss xmm2,xmm5
    movaps xmm0,xmm2
    mulss xmm0,xmm2
    addss xmm3,xmm0
