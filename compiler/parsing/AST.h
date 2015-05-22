#ifndef _AST_H_
#define _AST_H_

#include "headers.h"
#include "Class.h"

/* Import statements at the beginning of the file. */
class Import
{
public:
    Import(const std::string& _importStr):
        importString(_importStr) {}

    std::string importString;
};

/**
 * Abstract Syntax Tree of a source file.
 */
class AST
{
public:
    const std::vector<Import> imports;
    const std::vector<Class> classes;

    AST(const std::vector<Import>& _imports,
        const std::vector<Class>& _classes):
        imports(_imports), classes(_classes) {}
};
#endif
