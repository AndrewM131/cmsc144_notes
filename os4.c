/*
Files
Chapter 10

Files and File Descriptors

Unix Files and I/Os
     OS provides abstraction
         Processes abstracts the processors
             You: simply run processes
             OS: set up all the details (last three lectures)
         Files abstracts the storage (disk/ssd/cloud storage/etc.)
             You: simply open/read/write/close files
             OS: map files to bits on storage
Basic Unix I/O operations (system calls):
     Opening and closing files
         open()and close()
     Reading and writing a file
         read() and write()
     Changing the current file position (seek)
         indicates next offset into file to read or write
         lseek(offset, ...)
             Ex: skip DVD chapters / fast forward
Opening files
     Open in read/write modes, examples:
         Firefox open .html pages in read only mode
         Microsoft word open .docx pages in write mode         */
int fd; /* file descriptor */

fd = open("/myweb/somefile.html", O_RDONLY);

if (fd < 0) {
    printf("oops");
    exit(1);
}
/*
    -Returns a small identifying positive integer file descriptor
         Fd < 0 means error
         What does integer fd represent? (later)
             For now: one fd per open call
Closing files       */
int fd = open(...);
...
int retval = close(fd)
if (retval < 0) ... /* check */
/*
     Use “fd” to close the file
     Good practice: Always check return codes (“retval”)

FYI
2^10 1K 1024
2^20 1M 1024*1024
2^30 1G
K = 1024
k = 1000
B = byte
b = bit

Reading files
     read()  OS copies bytes from the last file position to your buffer
     Read a 500-KB file?
     Call read (..., 1024) 500 times
*/
char buf[1024]; -> 1 KB
int nbytes;
read(fd, buf, 1024);
/*
Writing files
     Writing a file copies bytes from memory to the current file
    position, and then updates current file position
     Downloading 1MB file with 1KB buffer
         Call write() 1024 times
*/
char buf[1024] = "random data";
int nbytes;
write(fd, buf, 1024);
/*
FD Table
     The OS maintains a file descriptor table for every process
         (part of the process’ PCB – invisible to you)
     The first 3 file descriptors
         Each process begins life with 3 open file descriptors:
         0: standard input (default: keyboard)
         1: standard output (default: screen)
         2: standard error (default: screen)
     Open a new file
         Starts from fd = 3
        ---------------------
        fd  File information
        0   stdin
        1   stdout
        2   stderr
        3   (unused)
        ...
        ---------------------

File descriptors (Sharing and redirection)
Metadata, sharing, and redirection

File descriptor
     User: “fd” is just a number
         Ex: FD table of a microsoft word process
     OS: “fd” represents a pointer to file descriptor structure
         Describe file access information
         Current position, read/write mode, etc.
     FDs = represent open files
How the Unix kernel represents open files
     User:
         “fd” is a number (a “handler”)
     OS:
         “fd” is actually a file descriptor structure
         fd describes file access information
             Current position, open in read/write
        mode, etc.
         However, “fd” is not file metadata
             Fd does not describe the file
File sharing
     Two distinct FDs sharing the same disk file
         E.g., Calling open twice with the same filename argument
             fd3=open(“file.txt”),
             fd4=open(“file.txt”),
             read(fd4, buf, 1000)
I/O redirection (Project 4)
     Question: How does a shell implement I/O redirection?
        ls > foo.txt
         “>” is a shell feature
         How do you build implement this feature?
     Answer: By calling the dup2(fdsrc, fddst) syscall
         Copies (per-process) descriptor table entry fdsrc to entry fddst
    -Every process has its own fd table
        -exact same content as its parent
    -After reading a file, based on how many bytes, it advances the position
    -lseek changes the offser of the position manually
How processes share files: Fork()
     A child process inherits its parent’s open files
         Note: situation unchanged by exec functions (use fcntl to change)
    -sleep(1) means it sleeps for 1 second
O_APPEND
     Position is always updated to the end of the file
     Lseek on O_APPEND fd will be ignored

    int fda, fdb;
    char buf[100];

    fda = open("outfile", O_CREAT|O_TRUNC|O_RDWR, S_IRUSR|S_IWUSR);
    fdb = open("outfile", O_APPEND|O_WRONLY, 0);

    write(fda, "aa", 2); // file is "aa"
    write(fdb, "bb", 2); // file is "aabb"

    write(fda, "cc", 2); // file is "aacc"
    write(fdb, "dd", 2); // file is "aaccdd"

    lseek (fdb, 0, SEEK_SET); // ignored by the OS, fdb always append
    write(fdb, "ff", 2); // file is "aaccddff"

Shortcounts

Reading files
    -read() returns number of bytes read from file fd into buf
         nbytes < 0 indicates that an error occurred
         nbytes == 1000  great!
         nbytes == 500??
             Short counts (nbytes < readSize)
             Not errors!! E.g. file is only 500 bytes long
Dealing with short counts
     Put simply
         You want to read N bytes
         OS returns less than N bytes
     Short counts can occur in these situations:
         Encountering (end-of-file) EOF on reads
         Reading text lines from a terminal
         Reading and writing network sockets or Unix pipes
     Short counts never occur in these situations:
         Reading from disk files (except for EOF)
         Writing to disk files
     One way to deal with short counts in your code:
         Use the RIO (Robust I/O) package from your textbook’s csapp.c
        file (Appendix B)

Buffering

read() vs. rio_read()
     Simple example:
         A big file contains a list of 16-digit (16-char/byte) numbers
         Boss: “compute the total!!!”
     My read()
         One read system call for every 16-byte read!
         If file is big? 16 MB -> 1+ million system calls. bad
     rio_read()
         Buffering!
         Read 8 KB (8192 bytes) per read system call, but return to caller 16
        bytes at a time
    -if your buffer size is small, the reduction is less and vice versa
    -Library calls have optimization compared to system calls
Buffered I/O: Implementation
     For reading from file
     File has associated buffer to hold bytes that have been read
    from file but not yet read by user code
Buffering Summary
     Prevalent topic!
         High-performance computing, storage systems, networking, ...
     Reduce overhead cost
         At what other cost?
         (Nothing is perfect; all about tradeoffs)
     Principle: trade X for Y
         Trade space for performance
         Space = memory is big (big buffer is fine)
         Syscall = expensive
     Real-life analogy?
         If grocery near, buy small fridge (buffer)
         If grocery far (expensive syscall), buy very large fridge (buffer)


*/
