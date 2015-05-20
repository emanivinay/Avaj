#ifndef _PARSER_H_
#define _PARSER_H_

#include "headers.h"
#include "Lexer.h"
#include "Units.h"
#include "AST.h"


/**
 * An intermediate token buffer b/w Parser and Lexer objects.
 */
class TokenBuffer
{
public:
    TokenBuffer(Lexer& lexer):
        sourceLexer(lexer), tokenBuffer()
    {
    }

    Lexer& sourceLexer;

    Token getNextToken()
    {
        if (tokenBuffer.size()) {
            Token ret = tokenBuffer[0];
            tokenBuffer.erase(tokenBuffer.begin());
            return ret;
        }

        return lexer.getNextToken();
    }

    void putTokenBack(const Token& tok)
    {
        tokenBuffer.insert(tokenBuffer.begin(), tok);
    }

private:
    std::vector<Token> tokenBuffer;
};

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
#endif
