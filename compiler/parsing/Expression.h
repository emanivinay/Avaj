#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include "ParseResult.h"
#include "TokenBuffer.h"

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

/* Several varieties of expressions follow. */

/* Literals can be string, char or numeric literals. */
enum class LiteralType
{
    STRING = 0,
    CHAR,
    INTEGER,
    FLOATING,
};

/* Literal expression. */
class Literal: public Expression
{
public:
    Literal(const LiteralType typ, const std::string& lex):
        type(typ), lexeme(lex) {}

    const LiteralType type;
    const std::string lexeme;
};

class IDOrMethodCall
{
public:
    IDOrMethodCall(bool isMethodCall, std::vector<Expression*> exprs):
        isAMethodCall(isMethodCall), argExprs(exprs) {}

    const bool isAMethodCall;
    const std::vector<Expression*> argExprs;
};

class MemberAccess: public Expression
{
public:
    MemberAccess(const std::vector<IDOrMethodCall>& mbrs):
        members(mbrs) {}

    const std::vector<IDOrMethodCall> members;
};

class ArithmeticExpr: public Expr
{
};

class RelationalExpr: public Expr
{
};

class LogicalExpr: public Expr
{
};

ParseResult<Expression*>* parseExpr(TokenBuffer& tokenBuffer);
#endif
