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
