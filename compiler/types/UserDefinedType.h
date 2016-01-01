#ifndef _USER_DEFINED_TYPE_H_
#define _USER_DEFINED_TYPE_H_

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
    std::vector<TypeDataField> dataFields;
    std::vector<TypeMethod> methods;

    /* Constructs an UserDefinedType object. `size' field is unused at
     * the moment.
     */
    UserDefinedType(const std::string& typeName,
                    const int size,
                    const std::vector<TypeDataField>& fields,
                    const std::vector<TypeMethod>& methods);
public:
    /* Read type info of a user defined type from an Avaj class 
     * definition.
     */
    static UserDefinedType *readType(const Class *cls);
};
#endif
