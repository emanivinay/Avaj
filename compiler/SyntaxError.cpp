#include "SyntaxError.h"

std::string SyntaxError::what() const
{
    std::ostringstream errorDesc;
    errorDesc << desc << " in the line " << lineNo;
    return errorDesc.str();
}
