#ifndef _USER_DEFINED_TYPE_H_
#define _USER_DEFINED_TYPE_H_

#include "headers.h"
#include "Type.h"

/* A user defined type in an Avaj program.*/
class UserDefinedType: public Type
{
public:
    /* Name of the type. */
    const std::string name;

    /* Total size of all the data fields in this type.*/
    const int size;

    /* All the methods for this type.*/
    const std::vector<Method> methods;

    /* Read type info of a user defined type from an Avaj class 
     * definition.
     */
    static UserDefinedType *readType(Class *cls)
    {
        // TODO(vinay) - Implement UserDefinedType::readType().
        return nullptr;
    }
};
#endif
