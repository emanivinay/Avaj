### COMPILER FOR A JAVA LIKE LANGUAGE

My goal in this project is to implement a compiler from scratch. The language
is a simplified version of Java. 

#### LANGUAGE OVERVIEW

1.  C-style curly brace syntax. Statements, expressions, blocks etc.. are the
syntactic elements.

2.  Class based OO language. Every program is a set of objects messaging each
other to achieve desired effects and to compute desired results. Objects are
created on the heap and automatically GCed when no longer in use. Certain types
like numerics, reference types are directly allocated on stack and are deleted
when they go out of scope. 

3.  Source files are first parsed into an AST and then into an IR.
