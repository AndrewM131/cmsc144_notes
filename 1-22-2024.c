/* Lecture 8
The Memory Hierarchy

The CPU-Memory GAP
-gap widens between DRAM, disk, and CPU speeds
-Many instructions access memory:
    >34% of instructions access data memory!
    100% of insyructions are stored in instruction memory!

Synthesize This
-Many instructions access memory:
    • > 34% of instructions access data memory
    • 100% of instructions access instruction memory
-Memory is many orders of magnitude slower than the processor
    For example: Four-issue 2 GHz superscalar accessing 100 ns DRAM could
        execute 800 instructions during the time for one memory access!

These numbers don’t make sense

Must be a way to speed up memory access

Are all memories slow?
No.

Key Idea: Memory Hierarchy
L0: Regs
L1: L1 cache (SRAM)
L2 cache (SRAM)
L3: L3 cache (SRAM)
L4: Main memory (DRAM)
L5: Local secondary storage (local disks)
L6: Remote secondary storage (e.g., Web servers)

Capacity: Register << Cache << DRAM
Speed: Register >> Cache >> DRAM

On a data access:
    if data is in fast memroy -> low-latency access (to cache or register)
    if data is not in fast memory -> long-latency access to DRAM

Memory hirarchies only work if the small, fast memory (cache) actually stores
    data that is used/re-used by the proecessor at a given time

Locality!
-The key to bridging this CPI-Memory gap is a fundamental property of computer
    programs known as locality

Principle of Locality: Programs tend to use data and instructions with addresses
    near or equal to those they have used recently
Temporal locality: Recently referenced items are likely to be referenced again
    in the near future
Spatial locality: Items with nearby addresses tend to be referenced close
    together in time

*Locality example in the slides

Back to Memory hierarchy
-Memory hierarchies work because of
    -Caches: A smaller, faster memory that acts as a staging area for a subset
        of the data in a larger, slower memory (Fundamental idea of a memory
        hierarchy).
-For each k, the faster, smaller device at level k serves as a cache for the
    larger, slower device at level k+1
-Designed to take advantage of program locality: programs tend to access the
    data at level k more often than they access the data at level k+1
-Thus, the storage at level k+1 can be slower, and thus larger and cheaper per
    bit
-The memory hierarchy creates a large pool of storage that costs as much as
    the cheap storage near the bottom, but that serves data to programs at the
    rate of the fast storage near the top

General Cache Concepts:
Hit
Miss
hit rate and miss rate
*/