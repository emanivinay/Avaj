#include "Expression.h"

Expression::~Expression() {}

/* Binary operator precedence table. */
std::map<std::string, int> binaryOpPrecTable {
        {"||", 0}, {"|", 0}, {"&&", 0}, {"&", 0}, {"^", 0},
        {">", 1}, {">=", 1}, {"<", 1}, {"<=", 1}, {"!=", 1}, {"==", 1},
        {"+", 2}, {"-", 2}, 
        {"*", 3}, {"/", 3}, {"%", 3},
};

/* Does this token mark the end of an expression? */
static bool endsExpr(const Token& tok)
{
    return tok.type == TokenType::COMMA || tok.type == TokenType::RIGHT_BRACKET
        || tok.type == TokenType::SEMI_COLON;
}

/* Read a list of comma separated expressions enclosed in parens. */
ParseResult<std::vector<Expression*> > *parseCommaSeparatedExprs(
                                        const std::vector<Token>& tokens,
                                        int a, int b)
{
    return new ParseFail<std::vector<Expression*> >(
            "parseCommaSeparatedExprs not implemented yet.");
}

/**
 * Read enough tokens from the token buffer and construct an expression object.
 * In Avaj language, expressions are always followed by either a semicolon or a
 * comma.
 *
 * Algorithm to parse Avaj expressions.
 *
 * 1. Expressions can be nested. 
 */
ParseResult<Expression*> *parseExpr(const std::vector<Token>& tokens,
                                    int a = 0, int b = -1)
{
    return new ParseFail<Expression*>(
            "parseExpr(tokens) not implemented yet.");
}

// Isolate the expression tokens and pass them to the fnction above.
ParseResult<Expression*>* parseExpr(TokenBuffer& tokenBuffer)
{
    return new ParseFail<Expression*>(
            "parseExpr(tokenBuffer) not implemented yet.");
}
