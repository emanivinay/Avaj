#include "ParserUtils.h"

/* Parse multiple Ts, as many as possible.*/
template<class T>
ParseResult<std::vector<T> >* tryParseMultiple(TokenBuffer& tokenBuffer)
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
