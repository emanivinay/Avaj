AVAJ PROGRAMMING LANGUAGE.

My goal in this project to to understand PL concepts and techniques through
implementation. I'd like to start with a minimal feature set and extend it
further.

1.  A class based simplified OO language. Objects and methods are the key units
    in this programming model. Every program is a collection of objects calling
    each others' methods to compute desired values and achieve desired effects.

2.  Curly brace syntax, quite similar to that of Java's.

3.  Compiles to an IR, which can either be converted to native code or run on a
    VM.

4.  Static type system with generics and interfaces. In later versions,
    automatic type inferencing shall be supported.

5.  Memory model - Every value can either be heap allocated or stack allocated.
    Heap allocated objects are long living and are the main building blocks of
    the program. These are automatically managed with GC. Stack allocated ones
    are usually function local variables like ints, references to other objects.
    These are deleted when their scope is exited. Simplified version of Java
    memory model.
