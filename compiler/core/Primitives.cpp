#include "Primitives.h"

/* `PrimitiveTypeInfo` structures hold data about primitive types.*/
struct PrimitiveTypeInfo
{
    PrimitiveType pType;
    int valueSize;

    PrimitiveTypeInfo(PrimitiveType _pType, int vSize):
        pType(_pType), valueSize(vSize) {}
};

/* A global map holding primitive type info structures.*/
static std::map<std::string, PrimitiveTypeInfo> primitiveTypeInfoMap
    {{"Short", {.pType = SHORT, .valueSize = 2}},
     {"Int", {.pType = INT, .valueSize = 4}},
     {"Long", {.pType = LONG, .valueSize = 8}},
     {"Float", {.pType = FLOAT, .valueSize = 4}},
     {"Double", {.pType = DOUBLE, .valueSize = 8}},
     {"Ref", {.pType = REF, .valueSize = 8}},
     {"Char", {.pType = CHAR, .valueSize = 4}}};

PrimitiveType getPrimitiveType(const std::string& typeName)
{
    if (primitiveTypeInfoMap.count(typeName)) {
        const PrimitiveTypeInfo &typeInfo = primitiveTypeInfoMap[typeName];
        return typeInfo.pType;
    }
    else return INVALID;
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
