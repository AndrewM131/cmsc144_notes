/* Second Lecture
Object = state + methods
An object is: state + method
    state is data
    Methods are operations on data
These methods are the interface of an object
For example:

Methods: add_name()     get_name()    count()

state: student_roster      linked_list


Programming interface
Software programming interface: C, C++, Python, ...

What's the hardware interface:
              |
              \/
hardware (Processor + Memory)

Software programming vs. Machine-level programming
Swap function:*/
void swap (long *xp, long *yp){
    long t0 = *xp;
    long t1 = *yp;
    *xp = t1;
    *yp = t0;
}
/* gcc -0g -S swap.c
swap:
    info about what hardware sees (see slides)

Instruction Set Arhitecture (ISA)
The architecture is the interface between software and hardware


An ISA defines (among others):
States in hardware - eg, memory
(Note: There are different kinds of memory)

Methods: instructions used to change states (eg, memory)


Why is ISA needed?
There is faster innovation with ISA from early days of computer systems

Designing an ISA
    Arhitecture (interface) design is a tradeoff
    On the one hand
        Want a compatible line of processors
        Don't want to reqrite all software when new architecture available
    On the other hand
        Need to maintain interface limits innovation


Architectural States
CPU:
    PC, Registers, ALU, Condition Codes

Memory:
    Object Code, Prgram Data, OS Data, STACK

CPU --addresses--> Memory
CPU <--Data--> Memory
CPU <--Instructions-- memory

    -Programmer-Visibile 

Memory Basics
    -Byte (8 bits) is (usually) the smalled addressable unit in memory
        -Every byte has a memory Address
    -Word is the nominal size of integer-valued data in a machine
        -Word is also size of each memory address
        -Word is alos the size of a CPU register

Bytes, Words, and Memory Size
    -Word size limits the memory size. Why?
    -If a machine uses 8-bit words, what's the max memory size
        -2^8 = 256 unique memory addresses -> max memory size = 256 B (bytes)
    -On 32-bit machines (32-bit words), what's the max memory size?
        -2^32 = 4GB (1G=1024M, 1M=1024k, 1k=1024)
        -Too small for memory-intensive jobs
    -These days: most machines are 64-bit, i.e., 64-bit words
        -Potential address sace = 1.8x10^19 bytes
        -x86-64 machines support 48-bit addresses: 256 Terabytes

Multi-Byte Variable & Byte Ordering
    -Multi-byte variables
        -ex. short (2 bytes), int (4 bytes), long (8 bytes)
    -How are the bytes within a multi-byte word ordered in memory?
    -Two conventions
        -Big Endian: Least significant byte has highest address
        -Little Endian: Least significant byte has owest address
            -x86, ARM processors running Android, iOS, Linux, and Windows
        -X endian: Least significant byt has X-est address
4-byte variable: x = 0x1234567
Address: &x = 0x100
                     0x100 0x101 0x102 0x103
Big Endian: |   |   | 01  | 23  | 45  | 67  |   |   |
Small Endian: |   |   | 67 | 45 | 23 | 01 |   |   |


Array memory layout
    -Element address in an array are not affected by byte ordering
short a[2] = {1, 2};
                     0x100 0x101 0x102 0x103
Big Endian: |   |   | 00  | 01  | 00  | 02  |   |   |
Sma Endian      |   | 01  | 00  | 02  | 00  |   |   |

0x100 is addr of a[0] and addr of a[1] is 0x102

char s[4] = "123"
                     0x100 0x101 0x102 0x103
Big Endian: |   |   | 31  | 32  | 33  | 00  |   |   |
Sma Endian: |   |   | 31  | 32  | 33  | 00  |   |   |

addr of s[0] is 0x100 and addr of s[1] is 0x101

x86-64 Integer Registers
    -64-bit long (word size)
        Can reference low-order 4 bytes (also low-order 1 & 2 bytes)
    -General-purpose registers (except %rsp)
%rax    %eax
%rbx    %ebx
%rcx    %ecx
%rdx    %edx
%rsi    %esi
%rdi    %edi
%rsp    .
%rbp    .
%r8     .
%r9
%r10
%r11
%r12
%r13
%r14
%r15

Moving Data 101
    -Moving a constant value to a register
        movq $0x100, %rax
    -movq: instruction opcode
        -last character indicates the # of bytes to change/access
            -eg, movq moves 8 bytes, movl moves 4 bytes, etc
    -%rax: destination
    -$0x100: the vaue to be moved
        -prefix $ indicates its a constant value

Moving Data, in general
    -Moving data
        -movqSource, Dest
    -Operand Types
        -Register: One of 16 integer registers
            -Ex. movq %rax, %r13
            -Copy the value in %rax to %r13
        -Immediate: Ex., movq $0x100, %rax
            -Constant integer data (explained in last slide)
        -Absoulte: Ex., movq 0x100, %rax
            -Use 0x100 as a memory address and copy the value from memory to %rax
        -Memory: Ex. movq (%rax), %r13
            -use the value in %rax.. (look at slides0)

!!registery with parantheses means it's a memory address!!
*/