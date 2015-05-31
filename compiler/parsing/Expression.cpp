#include "Expression.h"


Expression::~Expression() {}

/**
 * Read enough tokens from the token buffer and construct an expression object.
 * In Avaj language, expressions are always followed by either a semicolon,
 * comma or a right paren.
 *
 * Algorithm to parse Avaj expressions.
 *
 * 1. Isolate the tokens which'll make up the expression.
 * 2. For method calls(and member accesses), expressions can be nested within
 * this whole expression. Parse those nested expressions first and construct
 * member access/method call objects. This must be done recursively.
 * 3. Now, at the top most level, we have a bunch of expressions(literals,
 * parsed member accesses etc..) separated by arith/relational/logical
 * operators etc.. Construct a parse tree for this top level expression.
 */
ParseResult<Expression*>* parseExpr(TokenBuffer& tokenBuffer)
{
    return new ParseFail<Expression*>(
            "parseExpr not implemented yet.");
}
