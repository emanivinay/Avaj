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
ParseResult<std::vector<T > >* tryParseMultiple(TokenBuffer& tokenBuffer);
#endif
