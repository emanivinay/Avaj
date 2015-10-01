#include "Primitives.h"
#include "Types.h"

/* Extract type information from the class definition.*/
TypeInfo extractTypeInfo(Class *classTree)
{
    // TypeInfo contains three pieces of data
    // 1. Size of the type's objects in bytes.
    // 2. Info. about its data field - type, access, static/instance.
    // 3. Info. about its methods - type, access, stat/inst, method param
    // types.
    
    // Object size.
    int objSize = 0;
    for (auto& fld: classTree->dataFields) {
        const std::string& fieldType = fld->typeName;
        if (getPrimitiveType(fieldType) != PrimitiveType::INVALID) {
            objSize += getPrimitiveTypeSize(fieldType);
        }
        else objSize += getPrimitiveTypeSize("Ref");
    }

    // Data fields.
    std::map<std::string, TypeFieldInfo> fieldMap;
    for (auto& fld: classTree->dataFields) {
        if (fieldMap.count(fld->typeName))
            throw std::runtime_error(
                "Field name clash in the class " + classTree->name);

        AccessInfo accInfo = fld->publicness ?
                             AccessInfo::PUBLIC :
                             AccessInfo::PRIVATE;

        fieldMap.insert(make_pair(
                    fld->typeName,
                    TypeFieldInfo(fld->typeName, accInfo,
                                  fld->staticness, false)));
    }

    // Methods.
    std::map<std::string, std::vector<TypeMethodInfo> > methodMap;
    for (auto& mthd: classTree->methods) {
        if (fieldMap.count(mthd->name)) {
            throw std::runtime_error(
                "Field name clashes with a method in the class "
                    + classTree->name);
        }

        AccessInfo accInfo = mthd->publicness ?
                             AccessInfo::PUBLIC :
                             AccessInfo::PRIVATE;

        TypeFieldInfo typeFieldInfo(mthd->returnTypeName,
                                    accInfo,
                                    mthd->staticness, true);

        TypeMethodInfo typeMethodInfo(typeFieldInfo,
                                      mthd->methodParams->paramTypes);

        if (methodMap.count(mthd->name)) {
            std::vector<TypeMethodInfo>& mthds = methodMap[mthd->name];
            if (std::find(mthds.begin(), mthds.end(), typeMethodInfo) !=
                    mthds.end()) {
                throw std::runtime_error("Method " + mthd->name + 
                    " signatures clash within the class " +
                    classTree->name);
            }
            mthds.push_back(typeMethodInfo);
        } else {
            methodMap[mthd->name] = std::vector<TypeMethodInfo>();
            methodMap[mthd->name].push_back(typeMethodInfo);
        }
    }

    return TypeInfo(objSize, fieldMap, methodMap);
}
