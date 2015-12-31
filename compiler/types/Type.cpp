#include "Type.h"

Type::Type(const std::string _name, const int _size,
           const std::vector<Method>& _methods):
    name(_name), size(_size), methods(_methods)
{
}
