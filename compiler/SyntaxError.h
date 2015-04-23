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

    virtual std::string what()
    {
        std::ostringstream errorDesc;
        errorDesc << desc << " in the line " << lineNo;
        return errorDesc.str();
    }

private:
    // Line in source file where this error happens.
    int lineNo;

    // A description of the error.
    std::string desc;
};
