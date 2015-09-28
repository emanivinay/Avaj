#ifndef _TYPES_H_
#define _TYPES_H_

#include "headers.h"
#include "Class.h"

/* Access level of a class member.*/
enum class AccessInfo
{
    PUBLIC = 0,
    PRIVATE,
    UNDEFINED,
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

    TypeInfo(const int objSize,
             const std::map<std::string, TypeFieldInfo>& _fieldMap):
        objectSizeInMemory(objSize), fieldMap(_fieldMap)
    {
        if (objSize <= 0) {
            throw std::logic_error("Object size can never be negative.");
        }
    }
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

    TypeFieldInfo(const std::string& _typename, const AccessInfo &accInfo,
                  const bool _isStatic): typeName(_typename),
                  accessInfo(accInfo), isStatic(_isStatic) {}
};

/* Extract type information from the class definition in the source code.*/
TypeInfo extractTypeInfo(Class *classTree);
#endif
