#ifndef _BUILTIN_TYPE_H_
#define _BUILTIN_TYPE_H_

#include "headers.h"
#include "Type.h"
#include "Method.h"

/* An Avaj builtin type.*/
class BuiltinType: public Type
{
public:
    /* Inherit constructor from Type.*/
    using Type::Type;

    /* Parse a builtin type from a source file. Returns nullptr if theres 
     * no more type spec to be read(i.e. EOF is reached). Throws
     * MalformedFileInput exception when the spec format is incorrect.
     */
    static BuiltinType *readType(std::ifstream& source);

    /* Return the list of all the methods supported by this type.*/
    std::vector<Method> getMethods() const;
};
#endif
