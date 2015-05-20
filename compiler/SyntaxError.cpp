#include "SyntaxError.h"

const char* SyntaxError::what() const noexcept
{
    std::ostringstream out;
    out << desc << std::endl;
    out << "Occurring at " << lineNo;
    return out.str().c_str();
}
