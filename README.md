## Avaj
Avaj project is a programming language with a compiler and a runtime. The
language is a statically typed, class based OO language. The compiler and the
runtime for Avaj are written in C++. This is a fun personal project for me to
learn about writing compilers & language runtimes, one I hope will be
meaningfully executed.

### Avaj language 
1.	Static language - The compiler will parse the source code, check for
syntax, type and other logical errors and will emit code for a target machine
(a vm in this case). Thus at runtime, we simply have an executable code that can
be run.

2.	Class based OOP - Each Avaj program is a set of class definitions, with
exactly one of them containing the entry point. Each running program has a set
of live objects interacting with each other according to their specified
interfaces. Object state and its logic are encapsulated in class definitions.

### Avaj runtime
Avaj runtime is a small VM built to execute Avaj programs. It comes with an
instruction set which is the target of our compiler. Details will be decided in
future.

### Versioning
1.  Avaj language versions are named {MAJOR-VERSION}.{MINOR-VERSION}. Current
version is 0.1

2.  At important milestones, the existing version is frozen and is made
available as a separate branch on the repo. Development moves on to the next
version number.

### TODO
1.  Type checking
2.  Other kinds of error checking
3.  VM design & implementation
4.  Primitive types
5.  Code generation

### Future goals

0.  Array access syntax must be implemented. e.g., if nameList is an array,
expressions like nameList[2], nameList[2][3] must be supported. As of v0.1,
this is not a priority.

1.  Algebraic datatypes - I'd like to support algebraic datatypes with simple
syntax. 

2. Protocols - A protocol is like a Java interface - it specifies the methods
and some state that supporting classes must implement. 
