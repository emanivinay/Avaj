#include "headers.h"
#include "Lexer.h"
#include "AST.h"


/**
 * Parser receives a stream of tokens from the Lexer and constructs an abstract
 * syntax tree(AST). The AST can then be used to generate an intermediate
 * representation of the code.
 */
class Parser 
{
public:
    Parser(const std::string& souceFile);

    /* Construct AST from the given source file.*/
    AST constructAST();

private:
    Lexer lexer;
};
