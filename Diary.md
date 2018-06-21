##  Avaj project diary

*   My high level objective for this project is to write a compiler+runtime for
a statically typed language with java like syntax and semantics. Main goals are
to write a compiler frontend (parsing, semantic analysis, IR generation) and
design/develop a runtime(a mini VM) to run the code. Language itself is chosen
to be simple with well understood semantics and syntax. Goal is to learn
writing compilers and runtimes, not to design a new language. I'd have saved
myself a lot of pain by choosing a lispy S-expression based homoiconic syntax
and focused on novel language features in that case.

*   I've so far written a lexer to break the source into a stream of tokens to
be processed by the Parser. I'm currently in the process of designing a parser
to process these tokens and generate a AST(or report error(s) in case of
failure).

*   My first major choice was to either use standard tools like flex/bison or
to hand write the lexer and parser. I took the second path to have more control
over the process and also because I want to understand more about language
grammars and syntax.

*   I have written a mostly formal grammar for the language, present in the
compiler/Grammar file. This spec shall be cleaned up further and extended with
more constructs if needed.

### 05/06/15

*   One problem in Lexer is regarding the dot symbol. Dot can appear in a number
token, as well as in an object field reference. In the second case, it cannot
have an adjacent whitespace. While in C/C++/Java, floating point tokens can
start with a dot, I've forbidden such tokens, instead the programmar
must start the number literal with '0.' in such cases. 
 
*   Parsing has turned out be a harder problem. I'm going through the
Dragon book parsing chapter right now. I think that each language
construct(e.g., if statements, class/method defns etc..) shall be defined in
our code and objects of such kinds are combined to form the syntax tree. Such
an AST will be presented to the semantic analysis phase, which as of now, is
far ahead in the future for me.

Signing off for today.

### 05/11/15

*   It looks like top down parsing should work, with extra care taken to remove
disambiguities, eliminate left recustion and after left factoring. Parsing
statements and expressions is the hardest part of this problem. I hope to have
solved this in a couple days.

*   The big problem is really representing all these syntactic constructs in
C++ code. A number of abstract and derived classes must be written for
statements, expressions, method bodies, class bodies etc.. and this is proving
to be tedious. I find myself wishing for Haskell abstractions like Maybe and
List monads here.

*   I'm not well acquainted with C++ STL/Boost libraries. It's likely that I'll
be reimplementing certain data structures.

*   Real work only starts after the parsing is implemented. 

Signing off for today.

### 05/13/15

*   Expressions are the at the core of the language, syntactically and
semantically. Every othe syntactic unit is defined in terms of expressions, and
expressions are defined only in terms of themselves.

### 06/07/15

*   At this point, I'd like to start designing a VM for Avaj language.

### 06/09/15

*   I think the best course for me is to write the compiler for a good vm. VM design
and implementation, as it turns out is hard and time consuming. At this point, If I
started on VM design, Avaj compiler would stall indefinitely and eventually I'd lose
interest in it.

*   So, the next task is to finish the parser module and then start sketching out the
semantics of the language.

### 06/19/15

*   Finally, finished writing parser module. Hasn't been tested, though. But I
am reasonably confident what I have now is mostly correct. We'll see, now onto
language semantics.

    *   Semantics -> What constitutes the semantics of a language?
    *   Central paradigm - OOP model in Avaj's case. 
    *   Type system - Language type systems vary along a number of dimensions -
        Static/Dynamic/Hybrid, Strict/Permissive, expressivity etc..
    *   Concurrency support - Concurrency is not supported in the first version
    *   Runtime behavior - Evaluation model, Memory model, Concurrency etc..
    *   Any thing else?

*   I'll be try to think along these 3 axes and come up with a good programming
model

### 06/23/15

*   I think I'll benefit from learning assembly programming. Should be useful
for my Avaj project and OS kernel study project.

*   x64 assembly

### 09/20/15

*   After parse tree construction, then comes the semantic analysis phase. In
this phase, type checking and program, class and statement level semantic checks
are performed.

*   Code generation follows the semantic analysis phase. Here, we generate code
for a simple virtual machine.

### 09/24/15

*   I had a few good wins today. First, I learned to use ddd to debug c++
programs. I am close to finishing the parsing part.

### 10/02/15

*   I started working on type checking. Each statement must be checked for
proper typing. This means that code must be written for each statement type. In
addition, since statement blocks create new scopes, care must be taken when
dealing with variable assignments and declarations. All in all type checking
will require significant effort on my part.

### 10/07/15

*   So far, the representation consists of AST and its children node
classes(Expression, Statement etc..). A different(better?) representation is
needed for type checking and other kinds of analyses. Such an IR will include
information about symbols(e.g. a symbol table), loops in the code etc.. I'll
work on this new IR and write a AST to IR converter.

### 01/06/16 

*   Logging in after a long time. I'm implementing the type checking. Avaj type
system is relatively simple - You have types(user defined classes + builtins)
each with a well defined interface. Thus type checking now consists of simply
verifying that all statements are valid typewise. In the future, I want Avaj to
support interface based polymorphism and parametric types.

### 22/06/18

*   Picking this up after a long long time, from a different bitbucket account.
