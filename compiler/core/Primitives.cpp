#include "Primitives.h"

/* `PrimitiveTypeInfo` structures hold data about primitive types.*/
class PrimitiveTypeInfo
{
public:
    PrimitiveType pType;

    // Size in memory of an object of this type.
    int valueSize;

    PrimitiveTypeInfo(PrimitiveType _pType = PrimitiveType::INVALID,
                      int vSize = -1):
        pType(_pType), valueSize(vSize) {}

};

/* A global map holding primitive type info structures.*/
static std::map<std::string, PrimitiveTypeInfo> primitiveTypeInfoMap
    {{"Short", {.pType = PrimitiveType::SHORT, .valueSize = 2}},
     {"Int", {.pType = PrimitiveType::INT, .valueSize = 4}},
     {"Long", {.pType = PrimitiveType::LONG, .valueSize = 8}},
     {"Float", {.pType = PrimitiveType::FLOAT, .valueSize = 4}},
     {"Double", {.pType = PrimitiveType::DOUBLE, .valueSize = 8}},
     {"Ref", {.pType = PrimitiveType::REF, .valueSize = 8}},
     {"Char", {.pType = PrimitiveType::CHAR, .valueSize = 4}}};

PrimitiveType getPrimitiveType(const std::string& typeName)
{
    if (primitiveTypeInfoMap.count(typeName))
        return primitiveTypeInfoMap[typeName].pType;
    else
        return PrimitiveType::INVALID;
}

int getPrimitiveTypeSize(const std::string& typeName)
{
    if (primitiveTypeInfoMap.count(typeName)) {
        const PrimitiveTypeInfo &typeInfo = primitiveTypeInfoMap[typeName];
        return typeInfo.valueSize;
    }

    // Not a primitive type. 
    return -1;
}
