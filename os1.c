/*
os1: OS and Exceptions
Chapter 8.1

Os Lectures, we'll use 32-bit registers: "r" -> "e"
    Use mainly 4 registers, eax, ebx, ecx, edx

Control Flow
    A processor does only "one thing":
        From startup to shutdown
            Reads an instruction from memory, then executes the instruction
    This sequence is the CPU's control flow

Processor != Computer (Power, network, Memory, Disk/SSd, etc.)
    A processor is a "passive" component
    A computer does much more
        Run many programs
        Deal with eorros
        Receive nework packets
        Read/write data to disk/SSD
        Input/output: keyboard, mouse, screen
        But who manages all of these?
    The answer is the operating system
        Lots of mechanisms and policies
        We'll begin with exception

What is an OS?
    A top-down description
        Manages computer hardware and software resources...
    A botttom-up description
        See it! Feel it! Love it!

    OS manages program executions
        Hundreds of programs are running on your laptop!
        (including the execution of itself)
    OS itself is a program
    What does a program look like?
        Hello.c -> hello (a binary file)

        What does an OS program look like?
            A bunch of C files! (just like hello.c)
            Compiled into /boot/vmlinux.. (>200 MB binary file)
Objdump
    Objdump:
        objdump -t <binary> -> functions
        objdump -D <binary> -> all instructions
    Program (binary) files
    Where does a program live?
        In disk, and loaded to memory
Memory (DRAM) and Addresses
    Addressable high speed volatile storage
        int i=7;
        mov 7 Mem[Addr]
    Address range
        8 bytes of memory
            [0x0 - 0x8)
        16 bytes of memory
            [0x0 - 0x10) 0x10=16
        2 GB
            [0x0 - 0x8000 0000)
Programs and OS
    Where are they?
        On the disk:
            (yourPath) /p1/hello
            /boot/vmlinux-3.2.0
        Gets loaded to memory
But .. an infinite program?
    Ex:
         While(true) { i++ };
             0x800C040: mov Mem[i] %eax
             0x800C050: inc %eax
             0x800C060: mov %eax Mem[i]
             0x800C070: jmp 0x800C040
     A new program also runs
             Will you see print “A” after infinite program? Yes?
             But how come?
             time interrupt
Or, a network "interrupt"
    A long program is using the CPU
Or, a buggy program
    Ex: divide by zero
Or, make a system call
RECAP: The problem statement
     Computer is complex
         System calls, network interrupts, error handling, time sharing, ..
         But processor is “passive”
     We need a mechanism to deal with these scenarios
         That is, we need to break the control flow of a running program
     Solution: OS Exceptions
         In the book: “exceptional control flow”
         Alter the flow of a program
         (NOT the same as Java/C# exceptions)
     The mechanisms:
         Exception handlers (written by OS Developers)
         Exception table (provided in the HW)
         HW and SW (i.e. OS) developers work together to solve the problem

Exceptions

OS contains exception handlers
    TimerInterrupt()
    DivideByZeroError()
    Syscall_handler(int arg)
    networkInterrupt()
Exception handlers
     Compiled and get loaded to the memory
         They have “home” (physical) addresses
         (during boot time by the boot loader)
         Examples:
             divideByZero() is stored in address 0xC0003000
             timerInterrupt, 0xC0002000
             syscall_handler, 0xC0001000
             (Addresses are not static, known at boot time)
         These functions are waiting to be called (by who?)
Exception/Interrupt Table
     Built inside the CPU
         256 entries
     Initialization
         The boot loader boots the OS
         OS initialization code install addresses of exception handlers
            to exception table
Context Switching
     Control flow passes from one process to another via a
    context switch
         Ex: CPU context switches from Process A to Process B
     But what triggers context switch?
         Timer interrupt (the most common trigger)
Summary
     Computer is complex
         Need exceptional control flow
         Exceptional control flow (ECF) is important because its how we
        implement: Input/output, processes (and user-level control of process
        creation), virtual memory, interactions with OS, software exceptions
     Exception handlers – in SW
         Basically OS functions, compiled, then get loaded to certain memory
        addresses
     Exception table (or interrupt descriptor table) – in HW
         Built-in the CPU, initialized by the OS, contains addresses
     HW and SW developers work together
         HW provides the interrupt table
         SW (OS) decides how to handle each exception/interrupt

Exceptions (contd)
Exceptions
     An exception is a transfer of control to the OS in response to
    some event (i.e., change in processor state)
Asynchronous Exceptions (Interrupts)
     Caused by events external to the processor
     Indicated by setting the processor’s interrupt pin
     Handler returns to “next” instruction
Synchronous Exceptions
     Caused by events that occur as a result of executing an
    instruction:
         Traps (example in next slide)
             Intentional, returns control to “next” instruction
             Examples: system calls, breakpoint traps, special instructions
         Faults
             Unintentional but possibly recoverable
             Examples: page faults (recoverable), protection faults (unrecoverable),
            floating point exceptions
             Either re-executes faulting (“current”) instruction or aborts
         Aborts
             unintentional and unrecoverable
             Examples: parity error, machine check
             Aborts current program
Summary
     Exceptions
         Events that require nonstandard control flow
             “JUMPING” from user program to the OS code
         Generated externally/asynchronous (interrupts) or
        internally/synchronous (traps and faults)


*/