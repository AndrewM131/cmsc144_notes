/* Lecture 8

Caches (Book Sections 6.1-6.5)

General Cache Concepts: Hit & Miss
    -hit rate = #hits / #accesses
    -miss rate = #misses / #accesses

General Cache Design and Organization (S, E, B)
S = 2^s sets        (s bits)
E = lines per set
Cache size:
    C = S x E x B data bytes


|    v    |  tag   | 0 | 1 | ..... | B-1 |
valid bit    tag     B = 2^b butes per cache clock (the data)

-Locate set
-Check if any line in set has maychinh tag
-Yes + line valid: hit

Categorizing Misses: The Three C's
-Compulsory (or cold) - first-reference to a block, occur even with infinite
    cache
-Capacity-cache is too small to hold all data needed by program at a given time
    (refer to as the working set)
-Conflict-misses that occur because of collisions, even when the cache is large
    enough

-Cache examples in slides.

*/