/* Lecture 10
Optimizing Code for Better Cache Performance

Set Associativeity Affects Data Placement
    Assume:
    Each cache block is 8 bytes
    Total memory size = 256 bytes

    Memorize is divided into 256/8=32 cache blocks
    
    Direct mapped
        (Anywhere in set 2 (10 mod 8))
    Example: Block #10 contains 8 bytes. Addresses: 01010xxx
    01      010        xxx
    tag     Set index   Block offset
    Set index (010) = 2, therefore it is located in set 2

    Block #18 contains 8 bytes. Addresses: 10010xxx
    10      010         xxx
    tag     Set index   Block offset
    Set index (010) = 2, therefore it is located in set 2

    But there is CONFLICT because both are in set 2, so they'll be replacing
        each other in the cache block

    If we have a 2-way set associative, every set has two blocks
    *Look at slides for visualization

    Through a 2-way set associative, a set can hold both blocks 
        (Anywhere in set 2 (10 mod 4))
    Example: Block #10 contains 8 bytes. Addresses: 01010xxx
    010      10        xxx
    tag     Set index   Block offset
    Set index (010) = 2, therefore it is located in set 2

    Block #18 contains 8 bytes. Addresses: 10010xxx
    100    10         xxx
    tag     Set index   Block offset
    Set index (010) = 2, therefore it is located in set 2

    In fully associative, there is only one big set
        (Anywhere)

    Direct Mapped           2-way set associative           fully associative

    More cache misses                                       Less cache misses
    Simpler lookups             <------------->             More complex lookups

Block Replacement: Which block to vote off?
    No choice in a direct mapped cache
    In an associative cache, which block from set should be evicted when the set
        becomes full?
    
    Random

    Least Recently Used (LRU)
        LRU cache state must be updated on every access
    
    First In, First Out (FIFO) aka ound-Robin
        Used in highly associative caches

Write Strategy: How are writes handled?
    Cache Hit
        Write Through - write to memory immediately, generally higher traffic
            but simpler to design
        Write Back - write cache onlu, memory is written when evicted, dirty bit
            per block avoids unnecessary write backs, more complicated
    Cache Miss
        No Write Allocate - only write to main memory
        Write Allocate - fetch block into cache, then write
    Common Combinations
        Write Through & No Write Allocate (old)
        Write Back & Write Allocate (new)

Cache Performance Metrics
    Miss Rate
        Fraction of memory references not found in cache
            (misses / accesses) = 1 – hit rate
        Typical numbers (in percentages):
            3-10% for L1
            can be quite small (e.g., < 1%) for L2, depending on size, etc.
    Hit Time
        Time to deliver a line in the cache to the processor
            includes time to determine whether the line is in the cache
        Typical numbers:
            1-4 clock cycles for L1
            10 clock cycles for L2
    Miss Penalty
        Additional time required because of a miss
            typically 50-200 cycles for main memory (Trend: increasing!)

Let’s think about those numbers
    Huge difference between a hit and a miss
        Could be 100x, if just one level cache and main memory

    Would you believe 99% hits is twice as good as 97%?
        Consider:
            cache hit time of 1 cycle
            miss penalty of 100 cycles

    Average memory access time = hit time + miss rate * miss penalty (for one level cache)
        97% hits: 1 cycle + 0.03 * 100 cycles = 4 cycles
        99% hits: 1 cycle + 0.01 * 100 cycles = 2 cycles

    But.. Misses in caches are inevitable

Today
    How to write code that is cache friendly?
    Maximize spatial locality by accessing elements that are
        contiguous in memory as much as possible
            Use the same principle to access any data structure (e.g., any
                dimensional array of any type, structs, etc.)

Example: Matrix Multiplication
*/
c = (double *) calloc(sizeof(double), n*n);
/* Multiply n x n matrices a and b */
void mmm(double *a, double *b, double *c, int n) {
    int i, j, k;
        for (i = 0; i < n; i++){
            for (j = 0; j < n; j++){
                for (k = 0; k < n; k++){
                    c[i*n + j] += a[i*n + k] * b[k*n + j];
                }
            }
        }
}
/*
Cache Miss Analysis
    Assume:
        Matrix elements are doubles, n is a multiple of 8
        Cache block = 8 doubles
        Cache size S << n*sizeof(double) (cache can’t even hold one row/column)
        No allocate on write (no data in matrix c will be in cache)
    First iteration:
        n/8 + n = 9n/8 misses
    Total misses:
        9n/8 * n^2 = (9/8) * n^3
            Each inner loop: 9n/8 misses
            n2 outer loops
*/