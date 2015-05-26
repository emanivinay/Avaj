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

    int getCurrentState() const {return tokenIndex;}
    void setState(int index) 
    {
        if (index > tokenIndex || index < 0)
            throw std::logic_error(
                    "Invalid index to set the token buffer state");

        tokenIndex = index;
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

    /* Push a token back. */
    void putTokensBack(const std::vector<Token>& tokens)
    {
        for (auto& tok: tokens)
            putTokenBack(tok);
    }

    bool readOneOfTheKeywords(const std::vector<std::string>& keywords)
    {
        Token& tok = getCurrentToken();
        if (tok.type != TokenType::KEYWORD ||
                std::find(keywords.begin(), keywords.end(), tok.lexeme) 
                    == keywords.end()) {
            putTokenBack(tok);
            return false;
        }

        return true;
    }

    /**
     * Read a list of tokens matching the given list of lexemes. A helper
     * routine to read simple tokens like keywords, braces, etc..
     */
    bool readLexemes(const std::vector<std::string>& lexemes)
    {
        int tokensRead = 0;
        for (auto& lex: lexemes) {
            Token& tok = getCurrentToken();
            tokensRead++;
            if (tok.lexeme != lex) {
                tokenIndex -= tokensRead;
                return false;
            }
        }

        return true;
    }

private:
    std::vector<Token> tokenList;
    int tokenIndex;
};
#endif
