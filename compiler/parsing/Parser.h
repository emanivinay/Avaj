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

    /**
     * A generic algorithm to read multiple syntax elements of the same type at
     * once. Tries to read as many elements as possible.
     */
    template<class T>
    ParseResult<std::vector<T> >* tryParseMultiple()
    {
        // tryParse calls might raise exceptions, which must be handled at
        // higher levels in the call stack.
        std::vector<T> ret;
        while (true) {
            ParseResult<T> *one = T::tryParse(tokenBuffer);
            if (!one->isParseSuccessful()) {
                break;
            }
            ret.push_back(one->result());
        }

        return new ParseResult<std::vector<T> >(ret);
    }

private:
    TokenBuffer tokenBuffer;
};
#endif
