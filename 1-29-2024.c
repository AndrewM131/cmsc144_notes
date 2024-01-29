/* Lecture 11
Exam 1 Review

First, Cache:
Cache Miss Analysis
    Assume:
        Cache block = 8 doubles
        Cache size S << n * sizeof(double) (cache can’t even hold one row/column)
        Two blocks fit into cache, 2B^2 < S, B is a multiple of 8
        No allocate on write (no data in matrix c will be in cache)
    First (block) iteration:
        2n/B * B2/8 = nB/4
        B2/8 misses for each block
        1 out of 8 elements miss
        B2 total elements
        2n/B total blocks
        Red highlights data that
            are last added to the cache
            in this block iteration (in slides)
    Every (block) iteration:
        Same as first iteration
        2n/B * B2/8 = nB/4
    Total misses:
        nB/4 * (n/B)2 = n3/(4B)
        nB/4 misses per iteration
        (n/B)2 iterations
Blocking Summary
    No blocking: (9/8) * n3
    Blocking: 1/(4B) * n3
    Suggest largest possible block size B s.t. sizeof(double)*2*B2 < S
        If S=64KBytes = 64*1024Bytes, then setting 16B^2 = S will give B=64
        1/(4B) * n^3 ~=0.004 n^3, much smaller than 9/8 * n^3 ~=1.1 n^3
    Reason for dramatic difference:
        Matrix multiplication has inherent temporal locality:
            Total num. data: 3n^2, total num. multiplication computation: 2n^3
            Every array element is used O(n) times!
        But program has to be written properly
Summary
    Cache memories can have significant performance impact
    You can write your programs to exploit this!
        Focus on the inner loops, where bulk of computations and memory
            accesses occur.
        Try to maximize spatial locality by reading data objects that are
            consecutive in memory.
        Try to maximize temporal locality by using a data object as often as
            possible once it’s read from memory
        Optimize read over write
*/
/*
Exam I Topics:
    Basic x86-64 Architecture
    Control Flow
    Funcions
    Arrays, Structs, Unions
    Memory Hierarchy and Locality
    Caches
    Architecture vs. microarchitecture

*/