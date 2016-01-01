#include "Type.h"

TypeMemberInfo::TypeMemberInfo(const bool _isPublic,
                               const bool _isStatic,
                               const bool _isFinal):
    isPublic(_isPublic), isStatic(_isStatic), isFinal(_isFinal)
{
}

TypeMethod::TypeMethod(const TypeMemberInfo& tMemInfo,
                       const Method& _method):
    method(_method), memberInfo(tMemInfo)
{
}

TypeMethod::TypeMethod(const Method& method):
    TypeMethod(TypeMemberInfo(true, true, true), method)
{
}

TypeDataField::TypeDataField(const TypeMemberInfo& tMemInfo,
                             const std::string& type,
                             const std::string& name):
    memberInfo(tMemInfo), fieldType(type), fieldName(name)
{
}

Type::Type(const std::string _name, const int _size,
           const std::vector<TypeMethod>& _methods):
    name(_name), size(_size), methods(_methods)
{
}

Type *Type::getExpressionType(const Expression *expr,
                              const SymbolTable& symTab)
{
    // TODO(vinay) - Implement Type::getExpressionType().
    return nullptr;
}

int Type::getSize() const
{
    return size;
}
