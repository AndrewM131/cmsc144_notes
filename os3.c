/*
OS3: Fork, execve, and signals
Chapter 8.4-8.5

fork() and execve()

fork() and execve() system calls
    See “man fork” and “man execve” for details
     int fork(void)
         creates a new process (child process) that is identical to the calling
        process (parent process)
     int execve(char *filename, char *argv[], char *envp[])
         Runs a new program (filename) in the current process
         Ex: execve(“somewhere/p0/hello”, ...)
How to create a new process?
     Basically all processes are rooted
    from a shell
         Desktop GUI is a “shell”
         A running shell is a process
         Many choices:
            – E.g. /bin/sh, bash, csh, tcsh, ...
            – echo $SHELL (to know)
     From a shell, you can start new
    processes (childrens)
         E.g. shell within a shell
         Childrens can create childrens
fork()
     Fork()
         Creates a child
         Child inherits parent’s context
     Last lecture: inherit CWD
         Shell’s CWD is “/data”
         Run myprog and CWD is passed from the shell process to myprog
Non-determinism/concurrency/race condition
*/
void fork_ex9() {
    int ret = fork();
    if (ret == 0) {
        printf("Child");
    }
    else {
        printf("Parent");
    }
    exit();
}
/* They are not connected, they print based on OS Scheduling
if statements are concurrent
Wait
*/
void fork_ex9() {
    int status;
    int ret = fork();
    if (ret == 0) {
        printf("Child");
    }
    else {
        wait(&status);
        printf("Parent");
    }
    exit();
}
/* In this way, the child gets printed first, and then the parent goes
So the parent will never print before child
wait() and waitpid()
     wait(..)
         Wait for one (any) of
        the childrens
     Please see the book
    for more examples
     waitpid(pid, ..)
         Wait for specific child
        with pid

Signals

Signals
     A signal is a small “message” that notifies a process that
    an event of some type has occurred in the system
         Signal type is identified by small integer IDs (1-30)
         Signals can come directly from the OS
         Signals can come from other processes (mediated by the OS)
     How does this work?
         A program P provides a SIGFPE signal handler
             Note: Signal handler (in program) != exception handler (in OS)
         OS lets P have its own way to deal with the error
Some Signals
    SIGINT
    SIGKILL
    SIGSEGV
    SIGALARM
    ...


Signal summary
     Create signal handlers
         void some_function_name(int sig)
     Register them -- signal()
         signal(SIG???, some_function_name);
     Send signals -- kill ()
         Specify destination pid
         kill(pid, SIG???);
     Your program may ignore signals (i.e. no handlers)

Sending signals – kill()

*/