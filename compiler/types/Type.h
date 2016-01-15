#pragma once

#include "headers.h"
#include "Expression.h"
#include "Method.h"

class SymbolTable;

/* TypeMemberInfo holds information like access - public/private,
 * whether the member is static or instance, whether it is final or
 * changing.
 */
class TypeMemberInfo
{
public:
    const bool isPublic;
    const bool isStatic;
    const bool isFinal;

    TypeMemberInfo(const bool _isPublic, const bool _isStatic,
                   const bool _isFinal);
};

/* TypeDataField holds information about a single data field.*/
class TypeDataField
{
public:
    const TypeMemberInfo memberInfo;
    const std::string fieldType;
    const std::string fieldName;

    TypeDataField(const TypeMemberInfo& tMemInfo,
                  const std::string& type,
                  const std::string& name);
};

/* A method in a user defined type. */
class TypeMethod
{
public:
    const Method method;
    const TypeMemberInfo memberInfo;

    TypeMethod(const TypeMemberInfo& tMemInfo, const Method& method);

    /* Assumes defaults for tMemInfo.*/
    TypeMethod(const Method& method);
};

/* An abstract class to represent Avaj types. Builtin types and user defined
 * types are instances of its subclasses. In future, this class will include
 * the method code as well.
 */
class Type
{
public:
    /* Name of the type.*/
    const std::string name;

    /* Total size of all data fields in this type.*/
    const int size;

    /* List of the methods supported by this type.*/
    const std::vector<TypeMethod> methods;
public:
    Type(const std::string _name, const int _size,
         const std::vector<TypeMethod>& methods);
    /* Get the total size of the data fields in this type. This may be less
     * than the actual size occupied by the objects of this type in RAM because
     * of, say, alignment restrictions.
     */
    virtual int getSize() const;

    /* Return the list of all methods supported by this type.*/
    virtual std::vector<TypeMethod> getMethods()
    {
        return methods;
    }

    /* Compute the type of an Avaj expression, within the context of the given
     * symbol table.
     */
    static Type *getExpressionType(const Expression *expr,
                                   const SymbolTable& symTab);
};
