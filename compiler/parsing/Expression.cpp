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
static bool endsExpr(Token& tok)
{
    return tok.type == TokenType.COMMA || tok.type == TokenType.RIGHT_PAREN 
        || tok.type == TokenType.SEMI_COLON;
}

/* Read a list of comma separated expressions enclosed in parens. */
ParseResult<std::vector<Expression*> > *parseCommaSeparatedExprs(
                                        std::vector<Token&> tokens,
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
ParseResult<Expression*> *parseExpr(std::vector<Token&> tokens,
                                    int a = 0, int b = -1)
{
    if (b < 0)
        b = (int)tokens.size() - 1;

    std::vector<Expression*> topLevelExprs;
    std::vector<Operator> operators;
    for (int i = a;i <= b; ++i) {
        Token& tok = tokens[i];
        if (isAnOperator(tok)) {
        }
        else if (isALiteral(tok)) {
            topLevelExprs.push_back();
        }
    }
}

// Isolate the expression tokens and pass them to the fnction above.
ParseResult<Expression*>* parseExpr(TokenBuffer& tokenBuffer)
{
    std::vector<Token&> exprTokens;
    for (int depth = 0; ;) {
        Token &tok = tokenBuffer.getCurrentToken();
        if (depth == 0 && endsExpr(tok)) {
            tokenBuffer.putTokenBack(tok);
            break;
        }
        else if (tok.type == TokenType::END_OF_FILE) {
            throw SyntaxError(tok.lineNo, 
                    "Incomplete expression, premature end of file.");
        }

        exprTokens.push_back(tok);
        if (tok.type == TokenType::LEFT_PAREN)
            depth++;
        else if (tok.type == TokenType::RIGHT_PAREN)
            depth--;
    }

    return parseExpr(exprTokens);
}
