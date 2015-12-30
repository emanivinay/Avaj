#ifndef _BUILTIN_TYPE_H_
#define _BUILTIN_TYPE_H_

#include "headers.h"
#include "Type.h"
#include "Method.h"

/* An Avaj builtin type.*/
class BuiltinType: public Type
{
public:
    /* Name of the type.*/
    const std::string name;

    /* Data occupied by an object of this type, in bytes.*/
    const int size;

    /* Methods supported for this type.*/
    const std::vector<Method> methods;

    BuiltinType(const std::string& _name, const int _size,
                const std::vector<Method>& _methods);

    /* Return the size occupied in memory by objects of this type.*/
    int getSize() const;

    /* Parse a builtin type from a source file.*/
    static BuiltinType *readType(std::ifstream& source);

    /* Return the list of all the methods supported by this type.*/
    std::vector<Method> getMethods() const;
};
#endif
