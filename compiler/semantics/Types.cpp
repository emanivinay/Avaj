#include "Types.h"

/* Extract type information from the class definition.*/
TypeInfo extractTypeInfo(Class *classTree)
{
    std::map<std::string, TypeFieldInfo> fields;

    int objSize = 0;
    for (auto& fld : classTree->dataFields) {
        const std::string &fieldTypeName = fld.typeName;
        if (getPrimitiveType(fieldTypeName) != INVALID) {
            objSize += getPrimitiveTypeSize(fieldTypeName);
        } else {
            // Holds a reference to this field.
            objSize += getPrimitiveTypeSize("Ref");
        }
    }
}
