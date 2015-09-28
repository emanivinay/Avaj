## Avaj
    Avaj project is a programming language with a compiler and a runtime. The
language is a statically typed, class based OO language. The compiler and the
runtime for Avaj are written in C++.

	This is a fun personal project for me to learn about writing compilers &
language runtimes, one I hope will be meaningfully executed.

### Main features
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

### Future goals
1. Abstract datatypes - I'd like to support abstract datatypes with simple
syntax. 

2. Protocols - A protocol is like a Java interface - it specifies the methods
and some state that supporting classes must implement. 
