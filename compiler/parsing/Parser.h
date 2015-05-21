#ifndef _PARSER_H_
#define _PARSER_H_

#include "headers.h"
#include "SourceBuffer.h"
#include "Lexer.h"
#include "Class.h"
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
    // Parser runs the source file through the lexer once and stores all the
    // tokens into a list.
    std::vector<Token> tokenList;

    // Index in the token list at a given stage in parsing.
    int tokenIndex;
};
#endif
