#include "BuiltinType.h"

BuiltinType::BuiltinType(const std::string& _name, const int _size,
                         const std::vector<Method>& _methods):
    name(_name), size(_size), methods(_methods)
{
}

BuiltinType *BuiltinType::readType(std::ifstream& source)
{
    // TODO(vinay) - Implement BuiltinType::readType()
    return nullptr;
}

std::vector<Method> BuiltinType::getMethods() const
{
    return methods;
}
