#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include "SourceBuffer.h"
#include "Lexer.h"
/**
 * Expressions are those units that evaluate to a value. e.g., an expression
 * 1 + 2 evaluates to 3, while the expr. "asd" evaluates to a string. Expressions
 * may also be used to refer to existing values. e.g. myObj.a refers to a field
 * named a within the value myObj.
 */
class Expression
{
public:
    virtual ~Expression() = 0;
};

/**
 * Parse an isolated list of tokens into an Expression object. In top down 
 * parsing, expression tokens cane be isolated and parsed separately. This
 * simplifies the rest of the parsing module.
 */
Expression *parse(std::vector<Token>& tokens)
{
    // TODO(Vinay) -> Implement this.
    return nullptr;
}
#endif
