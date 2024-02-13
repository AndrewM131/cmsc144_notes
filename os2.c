/*
OS2: System Calls and Processes
Chapter 8.2-8.3

System Calls
     Top-down description (wikipedia.org)
         In computing, a system call is how a program requests a service
        from an operating system's kernel.
         This may include hardware-related services (for example, accessing
        a hard disk drive), creation and execution of new processes, and
        communication with integral kernel services such as process
        scheduling.
         System calls provide an essential interface between a process and
        the operating system.
     My simple version:
         A program cannot do everything by itself
         Need OS to help (e.g. read/write to disk, or gettimeofday(), or
        receive data from the network card)
System calls vs. library calls
    System:
         write(stdout, buf, len)
         write(stdout, “a”, 100)
             Bug??
         write(stdout, “44.44”, 5)
             Print up to two decimal
        places
             Easy to setup?
    Library:
         printf(manyFormats)
         printf(“a”)
             Length is implicit
         printf(“%5.2f”, float)
             Nice formatting supports
         Other examples:
             Java OutputStream
         Libraries -> user friendly
             Eventually will make system calls! (for hardware access)
Library call vs. Systems call
    Library:
        Just put arguments in the stack
    Systems:
        Must pass arguments through CPU registers
System calls
    How many system calls?
        300+ system calls (and you can add your own system calls)
    The problem:
        Jumping from user program to OS/kernel functions can ONLY be done via
            interrupts
         But interrupt table is limited!
             Exception/interrupt table in HW (e.g., 256 entries, many for
            other purposes such as network, disk, timer interrupts)
             How to call them from user program?
             2-level indirection
Two-level indirection
     1st level:
         Use only 1 syscall handler
     int 0x80
         Trap to interrupt[128]
         Calls syscall_handler() in OS
Two-level indirection
     With only 1 handler, how to route many system calls?
         e.g. open, read, write, exit, ...
     2nd level: Use syscall number and syscall arguments
         Additional notes:
             Different OSes (Linux, Mac, etc.) will have a different syscall
            table and syscall arguments (the compilers will take care of this)
             x86-64 also has a different syscall table
Making write system call
     How does a program make a system call?
     Step 1: Set the arguments in registers (e.g. eax, ebx, ..)
         eax: the system call number (4 -> write)
         The rest (ebx, ecx, edx): used by the specific system calls
             write() accepts 3 arguments
     Step 2: Make the interrupt 0x80
         (The OS automatically copy eax-edx to “num” and “args”)
System calls
    Must pass arguments through CPU registers
Making exit() system call
     Explicit (call exit yourself) or implicit (end of main() function)
         The OS will clean up your process’ memory
     Step 1:
         eax: the system call number (1  exit)
         The rest (ebx): used by the specific system calls
             exit() accepts only 1 argument (the exit code: 0, -1, etc.)
     Step 2: Make the interrupt 0x80

User and Kernel Mode

User vs. System/Kernel Mode
     System calls
         CPU runs user code -> User mode (green)
         CPU runs OS kernel code -> Kernel/system mode (red)
     Examples:
         Watch youtube -> green or red?? Both, because green from web browser
            and red from network/server
         Infinite loop of i++ -> green or red?? Green
User and kernel mode
     How does the CPU know whether it’s in user or
    kernel mode?
         Whenever HW interrupt happens, user -> kernel
         When returning to user, change CPU to user mode
     Kernel mode (important!)
         “King/God mode” -> can access anything!!! All hardware,
        disk content, all process’ memory, etc.!!
         Hacker’s destination
Why should you care?
     Ideally reduce unnecessary user/kernel crossings
         User/kernel crossing is expensive
         Long jump, saving registers, saving return address, setup
        arguments via registers, etc. etc.
         Hence, the many C libraries are provided today!
System call vs. library call
     Library call does not involve user/kernel crossing
         Library (e.g. libc.so) is loaded into the user’s code segment
         So a call to the library will only make a
        local jump
             (eventually make a syscall if needed)
     Is a function “f” a syscall or library?
         Run “man 3 f” and see the description
         (or just google it)
         (Some libraries e.g. fwrite will eventually make system calls e.g. write)

Processes

Program vs. Process
     Program:
         A collection of static code and static data
         E.g. /code/myprog, /bin/ls
     Process
         Instance of a computer program that is being executed
         Has its own context
         Context: its code and data stored in memory (stack, registers,
        program counter, heap, etc.)
         Has private virtual address space (more later in VM)
     Process != program
         In previous example: the two processes of the same program have
        different current working directories (CWD)
         CWD is inherited from the parent process (i.e. the shell in this
        example) – more when we discuss fork()
Process State (PID, PC, ...)
     Process ID
         Run “top” or “ps –e”
         Firefox PIDs in previous slide
     Program counter (PC / %eip)
         Run 2 “increment” processes
         P56 might already reach k++
         P76 might only at i++

OS creates a Process Control Block (PCB) per process
*/