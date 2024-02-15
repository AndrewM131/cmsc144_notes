/*
Memory management
OSTEP Book, Chapter 12-16

Intro to Memory Management/Virtual memory
Uniprogramming

C Pointer Review
Process State: Process Address Space
    Stack grows down, heap grows up
    Stack goes high to low
    Heap gows low to high
Virtual memory
    In computing, virtual memory is a memory management
    technique that is implemented using both hardware and
    software. It maps memory addresses used by a program, called
    virtual (logical) addresses, into physical addresses in computer
    memory. Main storage as seen by a process or task appears as a
    contiguous address space or collection of contiguous segments.
    The operating system manages virtual address spaces and the
    assignment of real memory to virtual memory. Address
    translation hardware in the CPU, often referred to as a memory
    management unit or MMU, automatically translates virtual
    addresses to physical addresses.
Process AddresS Space
     Stack
         Runtime stack (8MB limit)
         E. g., local variables
     Heap
         Dynamically allocated storage
         When call malloc(), calloc(), new()
     Data
         Statically allocated data
         E.g., arrays & strings declared in code
     Text/Code
         Executable machine instructions
         Read-only
     This is enough ...
     Note:
         Each process address range starts at 0 to 2n-1
         This is virtual/logical address (not physical address
Compiler
     Compiler generates virtual addresses
     Objdump –d hello
Where are they in memory?
     Scattered
         They don’t have to be in contiguous location
     Thus, there must be an indirection (address translation)
     CPU: store R1 Mem[0xBFFDD00]
        -> store R1 Mem[0x28924500]
     CPU uses with virtual/logical addresses for user programs
Uniprogramming
     Uniprogramming: Only one process runs (or exists) at a time
         Process address space: Memory size – OS size
            - Ex: 2 GB – 1 GB = 1 GB
     Directly access physical memory
         Access memory using its actual address
         int *p = 0x05001000;
         *p = 7 -> mov $7 mem[0x05001000]

Dynamic Relocation (Base and Bound)
    -Today: OS Supports multiprogramming standard
        -One simple solution: dynamic relocation (base and bound)

Dynamic Relocation
(BB: Base and Bound)
     Goals:
         Multiple processes (multiprogramming) resident at the same time
            - (even with 1 CPU)
         Each address space may be placed anywhere in memory
         Protect processes from one another
         Transparent:
            - The OS hides the physical addresses so
            that the process doesn’t have to worry
            about what’s going on in the memory
     Process uses logical/virtual address space
     (“%08x”, pointer);
        - will print a virtual address
     jmp 0x0600
        - jump to a virtual address
BB: How it works
     The OS assigns to each process a base and a bound
     Stored in Process Control Block (PCB), maintained by the OS
     Base: start location for the process’ address space in physical memory
     Bound: size limit of address space
     Example (bound=1000): P1 (5000-6000), P2 (2000-3000), P3 (7000-8000)
Base and Bound (Disadvantages)
     Fixed-size address space for each process
         Must allocate relatively big stack and heap (e.g. 10 MB)
     Ex: give 10 MB for “Hello World” program?
         Can we predict memory usage?
         How much memory a process needs? Not known a priori
     Small processes get big memory (waste!)  internal fragmentation
         Address space must be allocated contiguously
            - Cannot break address space!!
     Processes can have different bounds
     Over time, as hundreds of processes come and go, we have ...
     Lots of unusable holes (external fragmentation)
         If lots of small holes, we may not be able to load new process
         Hard to relocate processes from one part of memory to other part of the
        memory (must reshuffle)
BB: How it works
     Need address translation
     P1:
        - var = 7
        - CPU: mov $7 mem[100]
     Mem[100]  physical memory [5100], who translates?
     Requires hardware support: Memory Management Unit (MMU)
        - An MMU for every CPU
Memory Management Unit (MMU)
     Translates virtual to physical addresses
         Done on every memory reference by the CPU
     For BB, MMU contains two registers: Base and Bound
         OS sets the base and bound registers of the currently running process
            - Example: CPU is running Process 1
            - P1’s base is 5000
         Must be done correctly during context switching
MMU (BB) Translation Algorithm
     Physical address = logical address + base
     If (logical address > bound) SEGFAULT exception
         CPU jumps to OS segfault_exception_handler();
BB Advantages [Read offline, if no time]
     Provides memory protection
         (via virtual address)
     Supports dynamic relocation
         Easy relocation / move address spaces
         Move P2? Simply change P2’s base and bound in P2’s PCB
     Simple, inexpensive implementation
         Two registers, little logic in MMU
         OS sets the two registers on kernel-to-user mode switching
BB Disadvantages
     What’s the “bound” of your process?
         Hard to know; must overestimate for safety -> Internal fragmentation
         Each process must be allocated contiguously in physical memory
     Processes come and go -> external fragmentation (memory holes)
         Yes, address space can be relocated dynamically, but ...
         Relocation -> memory reshuffling, processes must freeze!
     Small process needs to expand, but neighboring address is full
        - Inflexible to expand, must relocate processes

*/