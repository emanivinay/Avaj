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

/**
 * Either an identifier or a simple method call.
 * e.g., bilbosAge in the statement `int bilbosAge = 111;` or
 * countVariations(1200) in the statement `return countVariations(1200);`
 */
class IDOrMethodCall
{
public:
    IDOrMethodCall(bool isMethodCall, const std::string& name,
                   const std::vector<Expression*>& exprs):
        isAMethodCall(isMethodCall), varName(name), argExprs(exprs) {}

    const bool isAMethodCall;
    const std::string varName;
    const std::vector<Expression*> argExprs;
};

/**
 * MemberAccess is any expression for accessing a class member(field or
 * method). Such an access can be arbitrarily deep, e.g., `a.b(1, 2).c.d(3)`
 * Such an expression is represented here as the vector {a, b(1, 2), c, d(3)}
 */
class MemberAccess: public Expression
{
public:
    MemberAccess(const std::vector<IDOrMethodCall>& mbrs):
        members(mbrs) {}

    const std::vector<IDOrMethodCall> members;
};

/* Binary operator precedence table.*/
std::map<TokenType, int> binaryOpPrecTable = 
        {{}};

ParseResult<Expression*>* parseExpr(TokenBuffer& tokenBuffer);
#endif
