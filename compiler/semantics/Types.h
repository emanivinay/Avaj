#ifndef _TYPES_H_
#define _TYPES_H_

#include "headers.h"
#include "Class.h"
#include "Primitives.h"

/* Access level of a class member.*/
enum class AccessInfo
{
    PUBLIC = 0,
    PRIVATE,
    UNDEFINED,
};

/**
 * Kind of a value/variable - reference or primitive.
 */
enum class ValueKind
{
    PRIMITIVE = 0,
    REFERENCE,
    UNDEFINED,
};

/**
 * TypeFieldInfo holds information about members of a datatype - methods and
 * data fields. Information such as the type(return type for methods and types
 * of members), access info(private vs public), instance field vs class field
 * (static nature) etc..
 */
class TypeFieldInfo
{
public:
    const std::string typeName;
    const AccessInfo accessInfo;
    const bool isStatic;
    const bool isAMethod;

    TypeFieldInfo(const std::string& _typename, const AccessInfo &accInfo,
                  const bool _isStatic,
                  const bool _isAMethod): typeName(_typename),
                  accessInfo(accInfo), isStatic(_isStatic),
                  isAMethod(_isAMethod) {}

    TypeFieldInfo():
        typeName(""), accessInfo(AccessInfo::UNDEFINED),
        isStatic(false), isAMethod(false) {}

    // All fields must exactly be equal.
    bool operator==(const TypeFieldInfo& typeInfo)
    {
        return typeName == typeInfo.typeName &&
               accessInfo == typeInfo.accessInfo &&
               isStatic == typeInfo.isStatic &&
               isAMethod == typeInfo.isAMethod;
    }
};

/*
 * TypeMethodInfo is like TypeFieldInfo, but it stores the full method
 * signature including its parameter types as well.
 **/
class TypeMethodInfo
{
public:
    const TypeFieldInfo typeFieldInfo;
    const std::vector<std::string> paramTypes;

    TypeMethodInfo(const TypeFieldInfo& _tFInfo=TypeFieldInfo(),
                const std::vector<std::string>& 
                _paramTypes=std::vector<std::string>()):
        typeFieldInfo(_tFInfo), paramTypes(_paramTypes) {}

    bool operator==(const TypeMethodInfo& tMInfo)
    {
        // Two method signatures clash if their names, return typesd
        // parameter types match. Here, we assume that method names are
        // already matching.
        return typeFieldInfo.typeName == tMInfo.typeFieldInfo.typeName
                    && paramTypes == tMInfo.paramTypes;
    }
};

/**
 * TypeInfo holds certain basic information about the types - memory
 * size of the type's objects, info about its members etc.. - useful during
 * compilation phase.
 */
class TypeInfo
{
public:
    const int objectSizeInMemory;
    const std::map<std::string, TypeFieldInfo> fieldMap;
    const std::map<std::string, std::vector<TypeMethodInfo> > methodMap;

    TypeInfo(const int objSize,
             const std::map<std::string, TypeFieldInfo>& _fieldMap,
             const std::map<std::string, std::vector<TypeMethodInfo>>& 
                                                    _methodMap):
        objectSizeInMemory(objSize), fieldMap(_fieldMap),
        methodMap(_methodMap)
    {
        if (objSize <= 0) {
            throw std::logic_error("Object size can never be negative.");
        }
    }
};

/* Extract type information from the class definition in the source code.*/
TypeInfo extractTypeInfo(Class *classTree);
#endif
