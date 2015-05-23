#ifndef _TOKEN_BUFFER_H_
#define _TOKEN_BUFFER_H_

#include "Lexer.h"

class TokenBuffer
{
public:
    TokenBuffer(const std::string& sourceFile)
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

    Token& getCurrentToken()
    {
        if (tokenIndex >= (int)tokenList.size())
            throw std::logic_error("Parser.tokenIndex out of range");

        return tokenList[tokenIndex++];
    }

    void putTokenBack(const Token& tok)
    {
        if (0 == tokenIndex)
            throw std::logic_error("No token has been read yet.");

        if (tokenList[tokenIndex - 1] != tok)
            throw std::logic_error("The new token doesn't match the old token.");

        --tokenIndex;
    }

private:
    std::vector<Token> tokenList;
    int tokenIndex;
};
#endif
