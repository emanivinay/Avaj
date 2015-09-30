## Semantic analysis
This is the phase in which the compiler checks for logical errors in code. Such
errors include type errors, contextual errors(e.g., break statement not in any
loop), incorrect accesses(e.g., accessing private member of a different class)
etc..

1.  We start with a few core datatypes(Int, Float etc..) fully implemented in
the compiler/runtime itself. These are the primitive types. Their
representation, complete implementation is inbuilt into the language core. These
types don't hold references, they are just data blobs. Thus can be created
directly on stack and embedded into other objects. Of course, they can be insta-
ntiated on the heap as well.

2.  Every other datatype is what is known as a reference type. Objects of such
types are created on the heap and are manipulated via references. Automatic
memory management system will control their life cycle.

3.  Given a type definition(e.g. as a `Class` structure from parsing), compiler
must be able to extract certain information about the type - size occupied by
its objects in memory, information about its members etc.. TypeInfo class
defined in [Types.h](Types.h) holds that information. More information is at
[TypeCheckingAlgorithm.md](TypeCheckingAlgorithm.md).
