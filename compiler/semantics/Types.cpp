#include "Primitives.h"
#include "Types.h"

/* Extract type information from the class definition.*/
TypeInfo extractTypeInfo(Class *classTree)
{
    int objSize = 0;
    for (auto& fld: classTree->dataFields) {
        const std::string& fieldType = fld.typeName;
        if (getPrimitiveType(fieldType) != PrimitiveType::INVALID) {
            objSize += getPrimitiveTypeSize(fieldType);
        }
        else objSize += getPrimitiveTypeSize("Ref");
    }

    std::map<std::string, TypeFieldInfo> fieldMap;
    for (auto& fld: classTree->dataFields) {
        if (fieldMap.count(fld.typeName))
            throw std::runtime_error(
                "Field name clash in the class " + classTree->name);

        AccessInfo accInfo = fld.publicness ?
                             AccessInfo::PUBLIC :
                             AccessInfo::PRIVATE;

        fieldMap.insert(fld.typeName,
                TypeFieldInfo(fld.typeName,
                              accInfo,
                              fld.staticness,
                              false));
    }

    std::map<std::string, TypeFieldInfo> methodMap;
    for (auto& mthd: classTree->methods) {
    }

    std::map<std::string, TypeFieldInfo> fullMap;
    return TypeInfo(objSize, fullMap);
}
