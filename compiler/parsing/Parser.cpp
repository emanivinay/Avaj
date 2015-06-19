#include "Parser.h"

Parser::Parser(const std::string& sourceFile):
    tokenBuffer(sourceFile)
{
}

ParseResult<AST*>* Parser::constructAST()
{
    return AST::tryParse(tokenBuffer);
}
