#include "Parser.h"

Parser::Parser(const std::string& sourceFile)
{
    Lexer lexer(sourceFile);
    tokenList.clear();
    tokenIndex = 0;

    while (true) {
        Token tok = lexer.getNextToken();
        tokenList.push_back(tok);
        if (tok.type == TokenType::END_OF_FILE)
            break;
    }
}

ParseResult<AST>* Parser::constructAST()
{
    return AST::read(this);
}
