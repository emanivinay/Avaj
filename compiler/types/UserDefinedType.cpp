#include "UserDefinedType.h"

UserDefinedType::UserDefinedType(const std::string& typeName,
                                 const int size,
                                 const bool _isPublic,
                                 const std::vector<TypeDataField>& fields,
                                 const std::vector<TypeMethod>& mthds):
    Type(typeName, size, mthds), dataFields(fields), isPublic(_isPublic) 
{
}

/* Construct a user defined type from a class syntax element.*/
UserDefinedType *UserDefinedType::readType(const Class *cls)
{
    std::string name = cls->name;
    bool isPublic = cls->publicness;
    int size = 0;
    std::vector<TypeDataField> dataFields;
    for (auto& fld: cls->dataFields) {
        dataFields.push_back(
                TypeDataField(TypeMemberInfo(fld->publicness,
                                             fld->staticness,
                                             fld->finality),
                              fld->typeName, fld->name));
    }

    std::vector<TypeMethod> methods;
    for (auto& meth: cls->methods) {
        methods.push_back(
                TypeMethod(TypeMemberInfo(meth->publicness,
                                          meth->staticness,
                                          meth->finality),
                           Method(meth->name, meth->returnTypeName,
                                  meth->methodParams->paramTypes)));
    }

    return new UserDefinedType(name, size, isPublic,
                               dataFields, methods);
}
