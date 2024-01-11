/* 3rd Lecture 1/8/2024s
This course uses x86-64 ISA
-x86-64 is the 64-bit ISA designed by Intel
    -64-bit word -> 64-bit memory addresses and 64-bit registers
    -Many principles shared by other ISAs

movq Operand Combinations
-mem-to-mem transfer is two instructions:
    -example: *p = *q
        movq (%rax) %r13
        movq %r13 (%rdx)

How mov works, byte by byte
    -rax has 0x123456789abcdef,
    rdi has 0x120
    Assume little-endian
        movq %rax, (%rdi)
        movq (%rdi), %rdx
        movl (%rdi), %ecx (4 byte version)
            q indicates 8 bytes, and l indicates 4 bytes

%rax | 0x0123456789abcdef |
%rdi | 0x0000000000000120 |
%rdx | 0x0123456789abcdef |
%rcx | 0x0000000089abcdef |

Assume big-endian
        movq %rax, (%rdi)
        movq (%rdi), %rdx
        movl (%rdi), %ecx (4 byte version)

%rax | 0x0123456789abcdef |
%rdi | 0x0000000000000120 |
%rdx | 0x0123456789abcdef |
%rcx | 0x0000000001234567 |


Simple Memory Addressing Modes
-Normal         (R)         Mem[Reg[R]]
    -Register R specifies memory address
    -Aha! Pointer dereferencing in C

    movq (%rcx), %rax #copy Mem[Reg[rcx]] to rax

-Displacement       D(R)        Mem[Reg[R]+D]
    -Register R specified start of memory region
    -Constant displacement D specifies offset

    movq 8(%rbp)..... look at slides


Complete memory Addressing Modes
-D(Rb) is a special case of the General Form
    D(Rb, Ri, S)    Mem[Reg[Rb]+S*Reg[Ri]+D]
    -D: Constant "displacement" 1, 2, or 4 bytes (default 0, if ommitted)
    -Rb: Base register: Any of 16 integer regsters (default 0, if ommitted)
    -Ri: Index register: Any, except for %rsp (default 0, if ommitted)
    -S: Scale, 1, 2, 4, or 8 (to align with typical element size in an array)
    (default 1, if ommitted)

    Ex: 1(%rax, %rdi, 4) -> %rax + 4*%rdi + 1 = 0x129
    %rax 0x120
    %rdi 0x2

-Special Cases
    -D(Rb)
    (Rb, Ri)
    D(Rb, Ri)
    (Rb, Ri, S)
    ...

What's the uses of memory addressing modes
-Referencing memory location
    -Refer to an element in an array
    -Refer to a variable in a stack ( in a few lectures )
    C code:
        int arr[5] = {1, 2, 3, 4, 5};
        return *p = &arr[i];
    Converted to ASM by compiler:
        leaq (%rdi, %rsi, 4), %rax
*/