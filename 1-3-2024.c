/* First Lecture 1/3/2024


What is a Computer system? --Single Program
What are computer applications?
    Apps are just C programs, but what do programs run on?
What really is segmentation fault?
    Something wrong beneath the programs
Computer sysrems provide an environment for computer hardware

What is a Computer system? --Multi-program
How many apps run simultaneously? Multicores?
    No, apps >> cores
Efficient hsaring of hardware is one of the functoinalities provided by
    computer systems

What is a Computer system? --Device evolution
With a growing number of digital devices, although these systems may look
    completely different, they share many design principles

What is a Computer System? --Hardware Evolution
Moore's Law
    Hardware performance doubles every two years
We don't need to re-design computers or applications with every new hardware
    technology. Why?
        Computer systems provide an abstraction of different hardware

What is a Computer System?
Application
    /\
    |
    |
    |  gap too large to bridge in one step
    |
    |
    \/
Physics

Actual:
Applications
Algorithm
Programming Language
Operating System/Virtal Machines                        |
    Interfaces for controlling and coordinating the     |
    use of hardware among various apps and users        |
Instruction Set Architecture                            |
    Interfaces for controlling hardware "Architecture"  | Focus on these three
Microarchitecture                                       | in the class
    Implementation of the instruction set architecture  |
    Key to Performance & Efficiency                     |
    Effects seen in performance                         |
Register-Transfer Level
Gates
Circuits
Devices
Physics

More and more layers and abstractions in each layer

We focus on key ideas behind computer systems rather than their latest
    implementation

Goal of the Class
    -Give you the basis to understand how the OS, Architecture, and
        Microarchitecture affect the programmer
    -Transition from porgrammer to computer scientist
    -Textbook: "Computer Systems: A Programmers' Perspective" 3rd Edition.
        Randal E. Bryant, David R. O'Hallaron
            -Great technical reference (not great for big picture)

Logistics:
Lecture0

Projects:
4 projects
    -Defusing bombs (asm), cache, your shell, your malloc
    -No project partnership
    -Great way to enhance your understanding of computer systems
    -Makes you a better programmer
    -First project posted

Labs:
    -Option, but helpful for projects
        svn, gdb, ...

Homeworks:
8 homeworks
    -Remove worst HW score (top 7 out of 8)
    -Due 11:59pm, Chicago time
    -Read instructoins carefully!! Word by word.
        -How to hand in, format file name, always run "svn status"

Exams
2 Exams
    Exam I: Covers first half of the course
    Exam II: covers second half of the course
    Not cumulative
    Taking exam in-person: location TBD

Final grade: Homework, projects, exams

Getting Help:
Where to get help with hw, projects, etc.
    -ED
        guarantee a fast response (within 24hours)
        TAG post properly
    -DO NOT send emails to individuak faculty/TAs
        unless necessary
    -Vertical division of TA duties
        2 per project, and homework
    -START EARLY
    -Use details when asking for help
    -if projects, homeowrks, tech problems
        -ED or TA's office hours
    -else if lectures, exams
        -ED or instructor's office hours
    -else
        -life, insiration, issues with class

Academic misconduct
    -don't cheat
    -Run a very smart code comparator tool
    -NO ChatGPT or online code generation software

How to work on projects.labs
Preferred Method
    -Work on your programming tasks on uchicago CS machines through ssh or
        remote desktop connection
    -Detailed tutorials can be found on canvas
Alternative Methods
    -Write your ode on your local machine, push to SVN, and compile/debug on
        uchicago CS machines


*/