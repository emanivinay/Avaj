#ifndef _METHOD_H_
#define _METHOD_H_

#include "headers.h"

/* Method signature has the method name, its return type and its argument
 * types.
 */
class Method
{
public:
    const std::string name;
    const std::string returnType;
    const std::vector<std::string> argTypes;

    Method(const std::string& name, const std::string retType,
           const std::vector<std::string>& args);
};
#endif
