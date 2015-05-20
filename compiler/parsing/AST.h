#ifndef _AST_H_
#define _AST_H_

#include "headers.h"
#include "Units.h"

/**
 * Abstract Syntax Tree of a source file.
 */
class AST
{
public:
    const std::vector<Import> imports;
    const std::vector<Class> classes;

private:
    AST(const std::vector<Import>& _imports,
        const std::vector<Class>& _classes):
        imports(_imports), classes(_classes) {}
};
#endif
