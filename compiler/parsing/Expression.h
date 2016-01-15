#pragma once

#include "ParseResult.h"
#include "TokenBuffer.h"

/**
 * Expressions are those units that evaluate to a value. e.g., an expression
 * 1 + 2 evaluates to 3, while the expr. "asd" evaluates to a string. Expressions
 * may also be used to refer to existing values. e.g. myObj.a refers to a field
 * named a within the value myObj.
 *
 * Expression objects must never be created on stack or be a data member of
 * another object,  as that may lead to double deletion.
 */
class Expression
{
public:
    virtual ~Expression() = 0;

    /* String representation of this expression. */
    virtual std::string repr() const = 0;
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

    std::string repr() const
    {
        std::ostringstream out;
        out << "Literal(type=" << (int)type << ", lexeme=" << lexeme;
        out << ")";
        return out.str();
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
    std::vector<Expression*> argExprs;

    // For a simple identifier/field access.
    IDOrMethodCall(const std::string& name):
        isAMethodCall(false), varName(name), argExprs() {}
    
    // For a method call.
    IDOrMethodCall(const std::string& name,
                   const std::vector<Expression*>& exprs):
        isAMethodCall(true), varName(name), argExprs(exprs) {}

    /* String representation of this object.*/
    std::string repr() const
    {
        std::stringstream out;
        out << "IDOrMethodCall(varName=" << varName << ", isAMethodCall=";
        out << (isAMethodCall ? "true" : "false");
        out << ", argExprs=";
        out << "(";
        for (auto exprPtr: argExprs)
            out << exprPtr->repr() << ", ";
        out << "))";
        return out.str();
    }

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
    const std::vector<IDOrMethodCall*> members;

    MemberAccess(const std::vector<IDOrMethodCall*>& mbrs):
        members(mbrs) {}

    /* String representation of this object. */
    std::string repr() const
    {
        std::ostringstream out;
        out << "MemberAccess(";
        for (auto& m : members)
            out << m->repr() << ", ";
        out << ")";
        return out.str();
    }

    ~MemberAccess()
    {
        for (auto mPtr: members) {
            delete mPtr;
        }
    }
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

/* Return the binary operator type of this token. */
BinaryOp getBinaryOpType(const Token&);

/* Expressions of type E1 op E2, where op is a binary operator. */
class BinaryExpression: public Expression
{
public:
    Expression* const leftExpr;
    Expression* const rightExpr;
    const BinaryOp op;

    BinaryExpression(Expression* const lft, Expression* const rgt,
            const BinaryOp _op): leftExpr(lft), rightExpr(rgt), op(_op) {}

    /* String representation of this object. */
    std::string repr() const
    {
        std::ostringstream out;
        out << "BinaryExpression(op=" << (int)op << ", ";
        out << leftExpr->repr() << ", ";
        out << rightExpr->repr() << ")";
        return out.str();
    }

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

/* Return the unary operator type of this token. */
UnaryOp getUnaryOpType(const Token&);

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

    /* String representation of this object.*/
    std::string repr() const
    {
        std::ostringstream out;
        out << "UnaryOpExpr(op=" << (int)op << ", ";
        out << expr->repr() << ")";
        return out.str();
    }

    ~UnaryOpExpr()
    {
        delete expr;
    }
};

/* Parse Avaj language expressions.*/
ParseResult<Expression*>* parseExpr(TokenBuffer& tokenBuffer);

ParseResult<Expression*>* parseExpr(const std::vector<Token>&,
                                    int a = 0, int b = -1);

int getBinaryOpPrec(const std::string& op);

bool endsExpr(const Token&);

int getClosingToken(const std::vector<Token>&, int, int);

Expression *combine(const std::vector<Token>& opers, Expression *e,
                    bool isFirstExpr = false);

ParseResult<Expression*> *topDownPrecedence(const std::vector<Expression*>&,
                                            const std::vector<Token>&,
                                            int start, int end);

ParseResult<std::vector<Expression*> > *parseCommaSeparatedExprs(
        const std::vector<Token>&, int, int);

ParseResult<IDOrMethodCall*> *parseIDOrMethodCall(const std::vector<Token>&,
                                                 bool id, int, int&);

ParseResult<Expression*> *parseMemberRef(const std::vector<Token>&, int, int&);
