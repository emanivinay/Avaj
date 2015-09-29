## Type checking algorithm
Given the source code for a module, the compiler must identify the various
types defined and used in the module code. It must then verify that these types
are defined and used properly. As of v0.1, Avaj compiler only supports single
module - this means that excepting the primitive types which are in-built into
the compiler/runtime, entire program is in a single source file. Future Avaj
versions will support multiple modules, but not v0.1

Here, the steps used in checking the type definitions and usage are outlined.

0.  At the beginning, the compiler knows everything about the primitive types -
their sizes, operations supported and so on. As primitives are extensively used
throughout the user programs, this information becomes essential.

1.  After the parsing phase, compiler has the parse tree data structure. Parse
tree holds the list of types(classes) defined by the programmer. Compiler
collects type/static/access info about the type's data fields and methods from
the class nodes in the parse tree. At this stage, any conflicts within the
class definition(e.g., duplicate field names) are detected and errors reported.
Compiler will collect all such type level knowledge for each type into a table.
This table can be used to verify their proper usage.

3. All compiler needs to do now is to check every statement in the code and
verify according to the statement type. e.g., assignment statement must satisfy
that the var and RHS must have the same type, member access must be valid etc..

4.  Avaj language supports arithmetic, logical and other operators in its
expressions. The compiler parses such expressions and implicitly converts them
into relevant methods supported by the operand types. e.g., the expression 
"AS" + "EFG" is converted to "AS".append("EFG") and 1 + 23 to 1.add(23) etc..
If the operator and operands don't match, it's a type error and the compiler
must report it.

This phase only verifies that program is correct at the type level. Still other
kinds of errors are checked for in later phases.
