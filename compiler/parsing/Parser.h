#ifndef _PARSER_H_
#define _PARSER_H_

#include "headers.h"
#include "SourceBuffer.h"
#include "Lexer.h"
#include "ParseResult.h"
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
    ParseResult<AST>* constructAST();

private:
    TokenBuffer tokenBuffer;
};
#endif
