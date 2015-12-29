#ifndef _TYPE_H_
#define _TYPE_H_

#include "headers.h"
#include "Expression.h"

class Method;
class SymbolTable;

/* An abstract class to represent Avaj types. Builtin types and user defined
 * types are instances of its subclasses. In future, this class will include
 * the method code as well.
 */
class Type
{
public:
    /* Get the total size of the data fields in this type. This may be less
     * than the actual size occupied by the objects of this type in RAM because
     * of, say, alignment restrictions.
     */
    virtual int getSize() const = 0;

    /* Return the list of all methods supported by this type.*/
    virtual std::vector<Method> getMethods() const = 0;

    /* Compute the type of an Avaj expression, within the context of the given
     * symbol table.
     */
    static Type *getExpressionType(const Expression *expr,
                                   const SymbolTable& symTab);

    virtual ~Type() = 0;
};
#endif
