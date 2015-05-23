#ifndef _PARSE_RESULT_H_
#define _PARSE_RESULT_H_

#include "headers.h"

/**
 * An abstract datatype to represent a parsing attempt for a syntax object.
 * Parsing can succeed with a valid result or fail, not producing anything.
 */
template<class T>
class ParseResult
{
public:
    /* Return true if the parsing attempt succeeded or false for failures. */
    virtual bool isParseSuccessful() const = 0;

    /* Return parsed value in successful case. Throw an exception in failure.*/
    virtual const T& result() = 0;
};

template<class T>
class ParseFail: public ParseResult<T>
{
public:
    bool isParseSuccessful() const 
    {
        return false;
    }

    const T& result()
    {
        throw std::logic_error("Parse attempt failed with reason - " + 
                                failMsg);
    }

    ParseFail(const std::string _failMsg):
        failMsg(_failMsg) {}

private:
    // Parse failure reason.
    const std::string failMsg;
};

template<class T>
class ParseSuccess: public ParseResult<T>
{
public:
    bool isParseSuccessful() const {return true;}

    // Constructs the `parseResult` member out of `t` argument. For syntax
    // objects, default copy constructor will work correctly.
    ParseSuccess(const T& t):
       parseResult(t)
    {
    }

    const T& result() {return parseResult;}

private:
    const T parseResult;
};
#endif
