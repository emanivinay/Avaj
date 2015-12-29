#include "Method.h"

Method::Method(const std::string& _name, const Type *retType,
               const std::vector<Type*>& args):
        name(_name), returnType(retType), argTypes(args)
{
}

Method::~Method()
{
    for (Type *argType: argTypes) {
        delete argType;
    }
    delete returnType;
}
