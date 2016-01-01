#include "UserDefinedType.h"

UserDefinedType::UserDefinedType(const std::string& typeName,
                                 const int size,
                                 const std::vector<TypeDataField>& fields,
                                 const std::vector<TypeMethod>& mthds):
    Type(typeName, size, mthds), dataFields(fields)
{
}

UserDefinedType *UserDefinedType::readType(const Class *cls)
{
    // TODO(vinay) - Implement UserDefinedType::readType().
    return nullptr;
}
