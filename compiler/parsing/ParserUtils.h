#ifndef _PARSER_UTILS_H_
#define _PARSER_UTILS_H_

#include "headers.h"
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
#endif
