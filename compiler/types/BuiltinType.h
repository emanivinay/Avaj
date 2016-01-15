#pragma once

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

    /** Read a list of builtin specs until the input source is all consumed.
     */
    static std::vector<BuiltinType*> readBuiltins(std::ifstream& source);
};
