#ifndef _PARSER_UTILS_H_
#define _PARSER_UTILS_H_

#include "headers.h"
#include "Lexer.h"
#include "ParseResult.h"
#include "TokenBuffer.h"

/**
 * A generic algorithm to read multiple syntax elements of the same type at
 * once. Tries to read as many elements as possible.
 */
template<class T>
ParseResult<std::vector<T> >* tryParseMultiple(TokenBuffer& tokenBuffer)
{
    // While, this function itself doesn't raise any exceptions, tryParse
    // calls might, which must be handled at higher levels in the call stack.
    std::vector<T> ret;
    while (true) {
        ParseResult<T> *one = T::tryParse(tokenBuffer);
        if (!one->isParseSuccessful()) {
            delete one;
            break;
        }
        ret.push_back(one->result());
        delete one;
    }

    return new ParseSuccess<std::vector<T> >(ret);
}

/**
 * Many grammar forms have optional keywords at the beginning. e.g.,
 * CLASS ::= `public`? ... class form has an optional public keyword at the
 * beginning. This function tries to read+consume such a keyword. Return true
 * and consume that keyword if its the current token. Return false without
 * consuming any token otherwise.
 *
 * parseKeywordOptional("public", {"public", ...}) -> True with {"..."}
 * remaining.
 *
 * parseKeywordOptional("public", {"static", ...}) -> False with {"static",
 * ...}
 */
inline bool parseKeywordOptional(const std::string& kwd, TokenBuffer& tokenBuffer)
{
    Token& token = tokenBuffer.getCurrentToken();
    if (token.type == TokenType::KEYWORD && token.lexeme == kwd) {
        return true;
    } else {
        tokenBuffer.putTokenBack(token);
        return false;
    }
}
#endif
