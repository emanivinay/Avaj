## Avaj language & Runtime
This document serves as an informal spec for the Avaj language and its runtime.
It defines at a very high level several aspects of the language and the RT.

### Type system

1. Avaj is a statically typed language - types in the program are checked at
compile time. 

### Scoping

Avaj variables have lexical/static scoping. Class definitions, method bodies,
block statements create new scopes. Variable resolution order -> inner most to
outer most blocks within methods and finally the class body.

### Objects & Memory

Avaj objects can be created on the heap, which are managed by the memory
management system.

### Execution
