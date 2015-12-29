#include "BuiltinType.h"
#include "HLReader.h"

BuiltinType::BuiltinType(const std::string& _name, const int _size,
                         const std::vector<Method>& _methods):
    name(_name), size(_size), methods(_methods)
{
}

// Read BuiltinType definition from a high level representation.
BuiltinType *BuiltinType::readType(std::ifstream& source)
{
    HLReader reader(source);
    reader.expectOrThrow("class");
    std::string name = reader.read<std::string>();
    reader.expectOrThrow("{");
    reader.expectOrThrow("size");
    reader.expectOrThrow(":");
    int size = reader.read<int>();
    reader.expectOrThrow(";");
    reader.expectOrThrow("methods");
    reader.expectOrThrow(":");
    std::vector<Method> methods;
    while (true) {
        // TODO(vinay) - Finish BuiltinType::readType().
        break;
    }

    return new BuiltinType(name, size, methods);
}

std::vector<Method> BuiltinType::getMethods() const
{
    return methods;
}
