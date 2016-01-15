#pragma once

#include "headers.h"

/**
 * Syntax errors in the source code.
 */
class SyntaxError : public std::runtime_error
{
public:
    SyntaxError(int _lineNo, const std::string& _desc):
        std::runtime_error(_desc), lineNo(_lineNo), desc(_desc) 
    {
    }

    const char* what() const noexcept;

private:
    // Line in source file where this error happens.
    int lineNo;

    // A description of the error.
    std::string desc;
};
