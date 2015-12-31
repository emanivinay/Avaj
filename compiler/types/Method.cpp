#include "Method.h"

Method::Method(const std::string& _name, const std::string retType,
               const std::vector<std::string>& args):
        name(_name), returnType(retType), argTypes(args)
{
}
