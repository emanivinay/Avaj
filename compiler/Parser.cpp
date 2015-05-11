#include "Parser.h"

Parser::Parser(const std::string& sourceFile):
    Lexer(sourceFile)
{
}

AST Parser::constructAST()
{
    // TODO(Vinay Emani) - Implement this.
    throw NotImplementedException();
}
