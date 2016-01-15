#pragma once

#include "headers.h"
#include "Type.h"
#include "Method.h"
#include "Class.h"

/* A user defined type in an Avaj program. User defined types have
 * members - data fields & functions. Each member can be public/private, 
 * can be static or instance members.
 */
class UserDefinedType: public Type
{
private:
    const std::vector<TypeDataField> dataFields;
    const std::vector<TypeMethod> methods;
    const bool isPublic;

    /* Constructs an UserDefinedType object. `size' field is unused at
     * the moment.
     */
    UserDefinedType(const std::string& typeName,
                    const int size,
                    const bool _isPublic,
                    const std::vector<TypeDataField>& fields,
                    const std::vector<TypeMethod>& methods);
public:
    /* Read type info of a user defined type from an Avaj class 
     * definition.
     */
    static UserDefinedType *readType(const Class *cls);
};
