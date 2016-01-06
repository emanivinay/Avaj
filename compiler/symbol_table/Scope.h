#ifndef _SCOPE_H_
#define _SCOPE_H_

#include "headers.h"
#include "Expression.h"

/**
 * A scope is a program region where a name gets bound to a memory location.
 * The same name may be bound to different locations in different scopes. A new
 * variable declaration in a scope allocates space(on stack or heap). A
 * reassignment modifies the value in the bound location.
 */
class Scope
{
public:
    /* A new variable declaration in the current scope.*/
    bool addNewVar(const std::string& varName,
                   const std::string& typeName = "",
                   const Expression *binding = nullptr);

    /* An assignment statement in the current scope.*/
    bool changeBinding(const std::string& varName,
                       const Expression *newBinding = nullptr);

    /* Check if the given name is in the current scope. */
    bool isNameInScope(const std::string& varName);

    /**
     * Return the type of the variable if it's present in this scope. Throw a
     * logic_error if it's not. Caller is expected to call isNameInScope before
     * this function.
     */
    std::string& getTypeName(const std::string& varName);

    /* Construtor creates an empty scope. */
    Scope();
private:
    /* All the variable bindings in the current scope. */
    std::map<std::string, std::pair<std::string, const Expression*> > bindings;
};
#endif
