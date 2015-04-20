#include "Lexer.h"

Lexer::Lexer(const std::string& sourceFile): sourceBuffer(sourceFile)
{
}

Token Lexer::getNextToken()
{
    // TODO(Vinay) -> Implement this function.
    return Token(TokenType.FAILURE, "");
}
