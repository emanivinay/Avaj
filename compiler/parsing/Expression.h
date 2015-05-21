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
   /* Parse an isolated token list into an Expression object. */
   virtual Expression& read(std::vector<Token>& tokenList) = 0;
};
#endif
