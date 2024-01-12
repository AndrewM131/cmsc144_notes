/* Lecture Notes

Conditional Branch Example (jX)
*/
long diff
(long x, long y)
{
long result;
if (x >= y)
    result = x-y;
else
    result = y-x;
return result;
}
/*
Assembly:
diff:
    cmpq %rsi, %rdi     # Set SF,OF,ZF,CF by x-y
    jl .L4              # jmp if x<y
    movq %rdi, %rax
    subq %rsi, %rax     # x-y
    jmp .Done
.L4:                    # x < y
    movq %rsi, %rax
    subq %rdi, %rax     # y-x
.Done
    ret

Register    Use(s)
%rdi        Argument x
%rsi        Argument y
%rax        Return value

jX  Condition           Description
mp  1                   Unconditional
je  ZF                  Equal / Zero
jne ~ZF                 Not Equal / Not Zero
js  SF                  Negative
jns ~SF                 Nonnegative
jg  ~(SF^OF)&~ZF        Greater (Signed)
jge ~(SF^OF)            Greater or Equal (Signed)
jl  (SF^OF)             Less (Signed)
jle (SF^OF)|ZF          Less or Equal (Signed)
ja  ~CF&~ZF             Above (unsigned)
jb  CF                  Below (unsigned)

-"Do-while" Loop Compilation
*/
long pcount_goto
(unsigned long x) {
long result = 0;
loop:
result += x & 0x1;
x >>= 1;
if(x) goto loop;
return result;
}
/*
    movq $0, %rax       # result = 0
.L2: # loop:
    movq %rdi, %rdx
    andq $1, %rdx       # t = x & 0x1
    addq %rdx, %rax     # result += t
    shrq %rdi           # x >>= 1
    jne .L2             # if (x) goto loop
    ret

Register    Use(s)
%rdi        Argument x
%rax        result

"For" Loop Example Assembly
*/
long pcount_for (unsigned long x)
{
size_t i;
long result = 0;
for (i = 0; i < 64; i++)
{
unsigned bit = (x >> i) & 0x1;
result += bit;
}
return result;
}
/* In Assmbly:
    movq $0, %rax       # result = 0
    movq $0, %rcx       # i = 0
.L2: # loop:
    movq %rdi, %rdx     # tmp = x
    shrq %rcx, %rdx     # tmp = tmp >> i
    andq $1, %rdx       # bit = tmp & 0x1
    addq %rdx, %rax     # result += bit
    incq %rcx           # i++
    cmpq $64, %rcx
    jl .L2              # if(i<64)goto loop
    ret

How CPI jumps to the specified line?
    -Each line in assembly has a memory address
    -Program counter (PC) reads insructions ine by line, unless told otherwise
        (by jump, etc)
    -Program counter is a register
    -Check slides for visual


Topic Today:
Machine-Level Programming III: Funcions and the call stack

What we have learned so far:
    -Register & memory (asm1)
    -Arithmetic operations (asm2)
    -Control (asm3)
    Today: Procedures (functions)

Goals of a procedure:
    -passing control
        -to beginning of prodedure code
        -back to return point
    -passing data
        -procedure arguments
        -return value
    -memory management
        -allocate during procedure execuion
        -deallocate upon return

How to pass control:
*/
long mult2(long a, long b){
    long s = a * b;
    return s;
}
void multstore(long x, long y, long *p){
    long t = mult2(x, y);
    *p = t;
    return;
}
/*
Assembly:
...
0000000000001129 <mult2>:
        112d: mov   %rdi,%rax
        1130: imul  %rsi,%rax
        1134: retq
0000000000001135 <multstore>:
        1139: push  %rbx
        113a: mov   %rdx,%rbx
        113d: callq 1129 <mult2>
        1142: mov   %rax,(%rbx)
        1145: pop   %rbx
        1146: retq
...

How does it know 1142?
    -Return address (1142) is saved on stack before callee starts!!

Stack in memory
Stack
    -runtime stack (8MB limit)
    -Eg local variables
Heap
    -Dynamically allocated as needed
    -When call malloc(), calloc(), etc

Code (or "Text")
    -Executable machine instructions
    -Read-Only

x86-64/Linux Stack Frame
    -Caller Stack Frame
        -Return address
            -Pushed by call instruction
            -Popped by ret instruction
        -Arguments for this call (optional)
Callee Stack Frame
        -Saved register context
        -Local variables
    -If can’t keep in registers
        -Arguments for function about to call
    -(optional)  
-Grows toward lower addresses

For following, look at slides for visual
x86-64 Stack: Push
-pushq Src
     Fetch operand at Src
     Decrement %rsp by 8
     Write operand at address given by %rsp
     Example: pushq %rbx
-popq Dest
     Read value at address given by %rsp
     Increment %rsp by 8
     Store value at Dest (must be register)
     Example: pushq %rbx

Procedure Control Flow
-Procedure call: call label
    • Push return address on stack
    • Address of the next instruction right after call
    • Jump to label
-Procedure return: ret
    • Pop address from stack
    • Jump to address

Control Flow example in slides
*/
