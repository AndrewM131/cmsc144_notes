/* Lecture 7
machine-Level Programming:
Advanced Datatypes: Arrays, Structs, and Unions

Back to Data
-Integers
    Unsigned and signed (two’s complement), of various sizes
What if you need some grouping of multiple values?
-Arrays
    Collection of values, all of same type, indexed by one or more indices
    E.g., A[i] (1D array), A[i][j] (2D array, or matrix)
-Structs and unions
    Collections of differently typed values

Array Allocation
-Basic Principle
    T A[L]; e.g., int val[5]
    -Array of data type T and length L
    -Contigously allocated region of L * sizeof(T) bytes
    -Identifer A can be used as a pointer to array element 0: Type T*

Mutidminensional (Nested) Arrays
-Declaration
    T A[R][C];
    -2D array of data type T
    -R rows, C columns
    -Type T element requires K bytes
-Array Size
    -R * C * K bytes

Nested Array Elemt Access
-Array Elements
    -A[i][j] is element of type T, which requires K bytes
    -Address A + i* (C * K) + j * K = A + (i * C + j) * 4

Structure Representation
-Structure represented as block of memory
    -big enough to hold all of the fields
-Fields ordered accoridng to declaration
    -Even if another ordering could yielf a more compact representation
        (more about this later)
-Compiler determines overall zie + positions of fieds
    -Machine-level program has no understanding of the structures in the source
        code

Generating Pointer to Structure Member
    -Generating Pointer to Array Element
        -Offset of each structure member determined at compile time
        -Compute as R + 4*index

Structures & Alignment
    -unaligned data
        p   p+1     p+5     p+9     p+17
    -aligned data
        -Primitive data type requires K bytes -> address must be multiple of K
        -Struct address must be multiple of the largest alignment of any element
        -Compiler follows the alignment rules
        -Align data to make memory access more efficient
        p+0     p+4     p+8     p+16       p+24
        -Multiple of 4 & 8
    
Specific Cases of Alignment (x86-64)
￿ 1 byte: char, ...
    ￿ no restrictions on address
￿ 2 bytes: short, ...
    ￿ lowest 1 bit of address must be 02
￿ 4 bytes: int, float, ...
    ￿ lowest 2 bits of address must be 002
￿ 8 bytes: double, long, char *, ...
    ￿ lowest 3 bits of address must be 0002
￿ 16 bytes: long double (GCC on Linux)
    ￿ lowest 4 bits of address must be 00002

Saving Space
-Put large data types first

Arrays of Structures
-Overall structure length multiple of K
-Satisfy alignment requirement for every element

Union Allocation
    -Allocate according to largest element
    -Can only use one field at a time

Summary
￿ Arrays in C
    ￿ Contiguous allocation of memory
    ￿ Aligned to satisfy every element’s alignment requirement
    ￿ Pointer to first element
    ￿ No bounds checking
￿ Structures
    ￿ Allocate bytes in order declared
    ￿ Alignment
￿ Unions
    ￿ Overlay declarations
    ￿ Way to circumvent type system
*/