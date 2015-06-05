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
    EXPONENT,
    INVALID,
};

/* Return the type of a literal token. */
static LiteralType getLiteralType(const Token& tok)
{
    switch (tok.type)
    {
        case TokenType::STRING_LITERAL:
            return LiteralType::STRING;
        case TokenType::CHAR_LITERAL:
            return LiteralType::CHAR;
        case TokenType::INTEGER:
            return LiteralType::INTEGER;
        case TokenType::FLOATING:
            return LiteralType::FLOATING;
        case TokenType::EXPONENT:
            return LiteralType::EXPONENT;
        default:
            return LiteralType::INVALID;
    }
}

/* Literal expression. */
class Literal: public Expression
{
public:
    const LiteralType type;
    const std::string lexeme;

    Literal(const Token& tok):
        type(getLiteralType(tok)), lexeme(tok.lexeme)
    {
    }

private:
    Literal(const LiteralType typ, const std::string& lex):
        type(typ), lexeme(lex) {}
};

/**
 * Either an identifier or a simple method call.
 * e.g., bilbosAge in the statement `int bilbosAge = 111;` or
 * countVariations(1200) in the statement `return countVariations(1200);`
 */
class IDOrMethodCall
{
public:
    const bool isAMethodCall;
    const std::string varName;
    const std::vector<Expression*> argExprs;

    IDOrMethodCall(bool isMethodCall, const std::string& name,
                   const std::vector<Expression*>& exprs):
        isAMethodCall(isMethodCall), varName(name), argExprs(exprs) {}

    ~IDOrMethodCall()
    {
        for (auto expr: argExprs) {
            delete expr;
        }
    }
};

/**
 * MemberAccess is any expression for accessing a class member(field or
 * method). Such an access can be arbitrarily deep, e.g., `a.b(1, 2).c.d(3)`
 * Such an expression is represented here as the vector {a, b(1, 2), c, d(3)}
 */
class MemberAccess: public Expression
{
public:
    const std::vector<IDOrMethodCall> members;

    MemberAccess(const std::vector<IDOrMethodCall>& mbrs):
        members(mbrs) {}

    ~MemberAccess() {}
};

/* Binary operators in the Avaj language. */
enum class BinaryOp
{
    // ARITHMETIC OPERATORS
    PLUS = 0,
    MINUS,
    MULTIPLY,
    DIVIDE,
    MODULO,

    // RELATIONAL
    GT,
    LT,
    EQ,
    GE,
    LE,
    NE,

    // LOGICAL AND BITWISE
    AND,
    OR,
    BITWISE_AND,
    BITWISE_OR,
    BITWISE_XOR,

    INVALID,
};

/* Return the binary operator type of the token. */
static BinaryOp getBinaryOpType(const Token& tok)
{
    switch (tok.type) {
        case TokenType::PLUS:
            return BinaryOp::PLUS;
        case TokenType::MINUS:
            return BinaryOp::MINUS;
        case TokenType::MULTIPLY:
            return BinaryOp::MULTIPLY;
        case TokenType::DIVIDE:
            return BinaryOp::DIVIDE;
        case TokenType::MODULO:
            return BinaryOp::MODULO;
        case TokenType::GT:
            return BinaryOp::GT;
        case TokenType::LT:
            return BinaryOp::LT;
        case TokenType::EQ:
            return BinaryOp::EQ;
        case TokenType::GE:
            return BinaryOp::GE;
        case TokenType::LE:
            return BinaryOp::LE;
        case TokenType::NE:
            return BinaryOp::NE;
        case TokenType::AND:
            return BinaryOp::AND;
        case TokenType::OR:
            return BinaryOp::OR;
        case TokenType::BITWISE_AND:
            return BinaryOp::BITWISE_AND;
        case TokenType::BITWISE_OR:
            return BinaryOp::BITWISE_OR;
        case TokenType::BITWISE_XOR:
            return BinaryOp::BITWISE_XOR;
        default:
            return BinaryOp::INVALID;
    }
}

/* Expressions of type E1 op E2, where op is a binary operator. */
class BinaryExpression: public Expression
{
public:
    Expression* const leftExpr;
    Expression* const rightExpr;
    const BinaryOp op;

    BinaryExpression(Expression* const lft, Expression* const rgt,
            const BinaryOp _op): leftExpr(lft), rightExpr(rgt), op(_op) {}

    ~BinaryExpression()
    {
        delete leftExpr;
        delete rightExpr;
    }
};

/* Unary operators. */
enum class UnaryOp
{
    PLUS,
    MINUS,
    NOT,
    BITWISE_NOT,
    INVALID,
};

static UnaryOp getUnaryOpType(const Token& tok)
{
    switch (tok.type) {
        case TokenType::PLUS:
            return UnaryOp::PLUS;
        case TokenType::MINUS:
            return UnaryOp::MINUS;
        case TokenType::NOT:
            return UnaryOp::NOT;
        case TokenType::BITWISE_NOT:
            return UnaryOp::BITWISE_NOT;
        default:
            return UnaryOp::INVALID;
    }
}

/**
 * Expressions of the form `uop E` where uop is a unary operator and E is an
 * arbitrary expression.
 */
class UnaryOpExpr: public Expression
{
public:
    const UnaryOp op;
    Expression* const expr;

    UnaryOpExpr(const UnaryOp _op, Expression* const _expr):
        op(_op), expr(_expr) {}

    ~UnaryOpExpr()
    {
        delete expr;
    }
};

/* Parse Avaj language expressions.*/
ParseResult<Expression*>* parseExpr(TokenBuffer& tokenBuffer);

ParseResult<Expression*>* parseExpr(const std::vector<Token>&,
                                    int a = 0, int b = -1);

bool endsExpr(const Token&);

int getClosingToken(const std::vector<Token>&, int, int);

ParseResult<std::vector<Expression*> > *parseCommaSeparatedExprs(
        const std::vector<Token>&, int, int);

ParseResult<Expression*> *parseMemberRef(const std::vector<Token>&, int, int&);
#endif
