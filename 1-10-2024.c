/* Lecture Notes 4th Lecture
To look at assembly code, use command: ggc -0g -s <file>

Machine-Level Programming III: Condition Code and Conditional Branch

-All examples so far execuite linearly line by line
-Assembly Language doesn't natively support conditional statement: 
    if(), while(), or for()
-How to implement conditional statements in assembly code?
-ISA provides  cmp, set and jmp instructions
*/
long max (long x, long y)
{
if (x > y) return x;
else return y;
}
/* in assembly:
# x in %rdi, y in %rsi
    movq %rsi, %rax         # y -> %rax
    cmpq %rsi, %rdi
    jle .L2
    movq %rdi, %rax         # x -> %rax
.L2:
    ret                     # return value in %rax

jle = jump if less or equal
cmpq = compare x(rdi) and y (rsi)
-We want to commpute x(rdi) - y(rsi), and then use the result to determine
    whether to jump to L2
Can we use "subq %rsi, %rdi"?
    -No, subq changes %rdi (destination)!
    -We need to keep track of the "side effect" of an arithmetic operation

Control Flow in x86
-Condition Codes record different types of side effects: CF, Zf, SF, OF

Consider x<y (signed)
-How to compare two signed integer on the bit level??
    -CPU can't understand natral numbers. It only operates on the bit level!
-Do a signed (two's complement) x-y and save the result in t
-And then check the sign of t. Will this work?
    -How to check the sign of t? Check the leading (leftmost) bit?
-Correct statement: x<y iff (t is negative) ^ (overflow)
                                            ^(XOR) means one and only one is true
                    x<y iff SF ^ OF
                    SF: Sign flag, OF: Overflow flag
                    CF: Carrby bit, ZF: t==0?

Condition codes are implicitly set after arithmetic instructions (not just subtraction)
-subq, addq, andq, salq, incq, ...
-exception: leaq (load effective address) doesn't set condition codes

Condition Codes (explicit setting: test)
-Explicit setting by test instruction
    -testq Src2, Src1
        -testq b, a like computing a&b without setting destination (unlike andq)
    
    -ZF set when a&b == 0
    -SF set when a&b < 0
    -OF and CF are set to 0

    -testq Src is equivalent to testq Src, Src
    -Test sign of a value (ZF set when Src is zero, and SF set when Src < 0)
    -Useful to have one of the operands be a mask

Look at slides for explicit setting: compare

How to use the condition codes?
-Two ways:
    -set: read some sematoic combinations of the codes
    -jmp: jump based on sematic combinations of the codes

Reading Condition Codes
-SetX Instructions
    -Does not alter remaining 7 bytes
    -Refer to textbook 2.4.2 on p184 for details on movzbq and similar instructions
    SetX Condition Description

    SetX    Condition       Description
    sete    ZF              Equal / Zero
    setne   ~ZF             Not Equal / Not Zero
    sets    SF              Negative
    setns   ~SF             Nonnegative
    setg    ~(SF^OF)&~ZF    Greater (Signed)
    setge   ~(SF^OF)        Greater or Equal (Signed)
    setl    (SF^OF)         Less (Signed)
    setle   (SF^OF)|ZF      Less or Equal (Signed)
    seta    ~CF&~ZF         Above (unsigned)
    setb    CF Below        (unsigned)

Check slides for Condition Branch Example (jX)
*/