#ifndef _SYNTAX_ERROR_H_
#define _SYNTAX_ERROR_H_

#include "headers.h"

/**
 * Syntax error in the source code.
 */
class SyntaxError: public std::exception
{
public:
    SyntaxError(int _lineNo, std::string _desc):
        lineNo(_lineNo), desc(_desc)
    {
    }

    const char* what() const noexcept;

private:
    // Line in source file where this error happens.
    int lineNo;

    // A description of the error.
    std::string desc;
};
#endif
