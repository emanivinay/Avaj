#ifndef _METHOD_H_
#define _METHOD_H_

#include "headers.h"
#include "Type.h"


/* Method signature has the method name, its return type and its argument
 * types.
 */
class Method
{
public:
    const std::string name;
    const Type *returnType;
    const std::vector<Type*> argTypes;

    Method(const std::string& name, const Type *retType,
           const std::vector<Type*>& args);

    ~Method();
};
#endif
