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
bool endsExpr(const Token& tok)
{
    return tok.type == TokenType::COMMA || tok.type == TokenType::RIGHT_BRACKET
        || tok.type == TokenType::SEMI_COLON;
}

/**
 * Find the matching closing paren to that of the one at tokens[s]. This must 
 * occur on or before tokens[e].
 */
int getClosingToken(const std::vector<Token>& tokens, int s, int e)
{
    if (tokens[s].type != TokenType::LEFT_BRACKET) {
        // Invalid token set passed
        throw std::logic_error("Invalid token set passed to getClosingToken");
    }

    for (int i = s, depth = 0;i <= e; ++i) {
        if (tokens[i].type == TokenType::LEFT_BRACKET)
            depth++;
        else if (tokens[i].type == TokenType::RIGHT_BRACKET)
            depth--;
        if (depth == 0)
            return i;
    }

    return -1;
}

/* Read a list of comma separated expressions enclosed in parens. */
ParseResult<std::vector<Expression*> > *parseCommaSeparatedExprs(
                                        const std::vector<Token>& tokens,
                                        int a, int b)
{
    if (a >= b) {
        throw std::logic_error(
                "Not enough tokens to parse comma separated exprs");
    }

    if (tokens[a].type != TokenType::LEFT_BRACKET) {
        throw SyntaxError(tokens[a].lineNo,
                "Left paren not present when expected");
    }

    if (tokens[b].type != TokenType::RIGHT_BRACKET) {
        throw SyntaxError(tokens[b].lineNo,
                "Right paren not present when expected");
    }

    std::vector<Expression*> exprs;
    for (int i = a + 1;i <= b;) {

        if (tokens[i].type == TokenType::RIGHT_BRACKET)
            break;

        // TODO(Vinay) - Read an expression, followed by either a `,` or `)`
        int endingToken = -1, depth = 0;
        for (int j = i;j <= b; ++j) {
            if (depth == 0 and endsExpr(tokens[j])) {
                endingToken = j;
                break;
            }
            else if (tokens[j].type == TokenType::LEFT_BRACKET)
                depth++;
            else if (tokens[j].type == TokenType::RIGHT_BRACKET)
                depth--;
            if (depth < 0) {
                throw SyntaxError(tokens[j].lineNo,
                        "Unbalanced parens");
            }
        }

        if (endingToken < 0) {
            throw SyntaxError(tokens[i].lineNo,
                    "Ill formed sub-expression");
        }

        ParseResult<Expression*> *subExpr = parseExpr(tokens, i,
                                                      endingToken - 1);
        exprs.push_back(subExpr->result());
        i = endingToken;

        if (tokens[i].type != TokenType::COMMA && tokens[i].type !=
                TokenType::RIGHT_BRACKET) {
            throw SyntaxError(tokens[i].lineNo,
                    "No comma or right paren following a sub-expression.");
        }

        if (tokens[i].type == TokenType::COMMA)
            i++;
    }

    if (exprs.empty()) {
        throw SyntaxError(tokens[a].lineNo,
                "Empty pair of parentheses.");
    }

    return new ParseSuccess<std::vector<Expression*> >(exprs);
}

/* Read a member reference expression.*/
ParseResult<Expression*> *parseMemberRef(const std::vector<Token>& tokens,
                                         int s, int& endingToken)
{
    return new ParseFail<Expression*>(
            "parseMemberRef not implemented yet.");
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
                                    int a, int b)
{
    if (b < 0)
        b = (int)tokens.size() - 1;

    if (b < a) {
        throw SyntaxError(tokens[a].lineNo, 
                "Empty expression.");
    }

    std::vector<std::vector<Token> > operators;
    operators.push_back(std::vector<Token>());

    std::vector<Expression*> topLevelExprs;

    for (int i = a, last = 1;i <= b; ++i) {
        const Token& tok = tokens[i];
        if (getUnaryOpType(tok) != UnaryOp::INVALID ||
                getBinaryOpType(tok) != BinaryOp::INVALID) {
            if (!last) {
                operators.push_back(std::vector<Token>());
            }
            last = 1;
            operators.back().push_back(tok);
            continue;
        }
        else if (last == 0) {
            // Two top level expressions without an operator separating them.
            throw SyntaxError(tok.lineNo,
                    "Ill formed expression, two sub-expressions with no\
                    operator separating them.");
        }
        else if (tok.type == TokenType::IDENTIFIER) {
            // Read a member ref.
            int endingToken = i;
            ParseResult<Expression*> *memberRef = 
                            parseMemberRef(tokens, i, endingToken);
            topLevelExprs.push_back(memberRef->result());
            i = endingToken;
        }
        else if (tok.type == TokenType::LEFT_BRACKET) {
            // Read a nested expression.
            int closingToken = getClosingToken(tokens, i, b);

            if (closingToken < 0) {
                throw SyntaxError(tok.lineNo, 
                        "Unbalanced parenthesis in expression.");
            }

            ParseResult<Expression*> *pE = parseExpr(tokens,
                    i + 1, closingToken - 1);
            topLevelExprs.push_back(pE->result());
            i = closingToken;
        }
        else if (getLiteralType(tok) != LiteralType::INVALID) {
            // Literal expression.
            topLevelExprs.push_back(new Literal(tok));
        }

        last = 0;
    }

    if (topLevelExprs.size() != operators.size()) {
        // Ill formed expression.
        throw SyntaxError(tokens[a].lineNo, 
                "Ill formed expression");
    }

    // TODO(Vinay) -> Check the unary/binary validity of operators and 
    // form the final expression.
    return new ParseFail<Expression*>(
            "Final expression building not implemented yet.");
}

// Isolate the expression tokens and pass them to the fnction above.
ParseResult<Expression*>* parseExpr(TokenBuffer& tokenBuffer)
{
    std::vector<Token> exprTokens;
    int depth = 0;

    while (true) {
        Token& tok = tokenBuffer.getCurrentToken();
        if (tok.type == TokenType::END_OF_FILE) {
            throw SyntaxError(tok.lineNo,
                    "Incomplete expression, premature end of file.");
        }
        if (depth == 0 and endsExpr(tok)) {
            tokenBuffer.putTokenBack(tok);
            break;
        }
        exprTokens.push_back(tok);
        if (tok.type == TokenType::LEFT_BRACKET)
            depth++;
        else if (tok.type == TokenType::RIGHT_BRACKET)
            depth--;
        if (depth < 0) {
            throw SyntaxError(tok.lineNo,
                    "Unbalanced parens in an expression.");
        }
    }

    return parseExpr(exprTokens);
}
