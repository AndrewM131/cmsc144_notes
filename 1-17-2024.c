/* Lecture 6
Summary: Stack
-Each "function" has its own space on stack, called a stack frame
-Stack frame management
    -Allocated when enter procedure "call" code)
    -Deallocated when returns ("ret" code)
-Last-in first-out (LIFO) stack discpline matches function call/ret patterns
    -If P calls Q, then Q returns before P
-%rsp must be put back to the end of Caller Frame when Callee returns

Procedure Data Flow
-Registers
    -First 6 Arguments
    %rdi    1st arg
    %rsi    2nd arg
    %rdx    ...
    %rcx    ..
    %r8     .
    %r9
    -Return value
    %rax
-Registers are much faster than memory
-Only allocate stack space when registers are not enough

Example of Passing arguments
*/
void multstore(long x, long y, long *dest)
{
long t = mult2(x, y);
*dest = t;
}

long mult2(long a, long b)
{
long s = a * b;
return s;
}
/* In Assembly:
0000000000001139 <multstore>:
# x in %rdi, y in %rsi, dest in %rdx
    1139: push %rbx             # Save %rbx
    113a: mov %rdx,%rbx         # Save dest
    113d: callq 1129 <mult2>    # mult2(x,y)
# t in %rax
    1142: mov %rax,(%rbx)       # Save at dest
    1145: pop %rbx              # Restore %rbx
    1146: ret

0000000000001129 <mult2>:
# a in %rdi, b in %rsi
    1129: mov %rdi,%rax         # a
    1130: imul %rsi,%rax        # a * b
# s in %rax
    1134: ret                   # Return


Register Saving Conventions
-When procedure foo calls bar
    -foo is the caller
    -bar is the callee
        -Example:
                foo:
                    • • •
                    movq $5000, %rdx
                    call bar
                    addq %rdx, %rax
                    • • •
                    ret
                bar:
                    • • •
                    subq $3000, %rdx
                    • • •
                    ret
    -contents of register %rdx overwritten by bar
    -This could be trouble -> something should be done!
        -Need some coordination

-Conventions:
    -"Caller Saved"
        -Caller saves temporary values in its frame before the call
    -"Callee Saved"
        -Callee saves temporary values in its frame before using
        -Callee restores them before returning to caller

***********Caller Saved and Callee Saved on Midterm**************

-Every function itself is a callee

Summary of Stack Discipline
Stack frames mean that each function call has private storage
 Saved registers & local variables
 Saved return pointer
 Register saving conventions prevent one function call from corrupting another’s data
 Unless the C code explicitly does so (e.g., buffer overflow)
 Stack discipline follows call / return pattern
 “If P calls Q, then Q returns before P” <==> “Stack: Last-In, First-Out”
 Also works for mutual recursion: P calls Q; Q calls P
*/