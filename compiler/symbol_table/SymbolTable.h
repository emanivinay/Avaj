#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

#include "headers.h"
#include "Scope.h"

/**
 * The symbol table data structure keeps track of the method local scopes, class
 * scope and the object scope. Singleton.
 */
class SymbolTable
{
private:
public:
    SymbolTable();

    std::string getVariableType(const std::string& name);
};
#endif
