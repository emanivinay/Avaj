#include "Expression.h"

#define LOG_MSG(fmtString, ...)

Expression::~Expression() {}

/* Binary operator precedence table. */
std::map<std::string, int> binaryOpPrecTable {
        {"||", 0}, {"|", 0}, {"&&", 0}, {"&", 0}, {"^", 0},
        {">", 1}, {">=", 1}, {"<", 1}, {"<=", 1}, {"!=", 1}, {"==", 1},
        {"+", 2}, {"-", 2}, 
        {"*", 3}, {"/", 3}, {"%", 3},
};

/* Return the binary operator type of the token. */
BinaryOp getBinaryOpType(const Token& tok)
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

/* Get the unary operator type of the token. */
UnaryOp getUnaryOpType(const Token& tok)
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

/* Return the precedence of a binary operator.*/
int getBinaryOpPrec(const std::string& op)
{
    return binaryOpPrecTable[op];
}

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

/* Combine an unary operator and an expression into an UnaryExpr object. */
Expression *combine(const std::vector<Token>& opers, Expression *e,
                    bool isFirst)
{
    if (isFirst) {
        if (opers.empty())
            return e;

        if (opers.size() > 1) {
            throw SyntaxError(opers[0].lineNo,
                    "Too many unary operators precede an expression.");
        }
        else {
            if (getUnaryOpType(opers[0]) == UnaryOp::INVALID) {
                throw SyntaxError(opers[0].lineNo,
                        "Invalid unary operator before an expression.");
            }

            return new UnaryOpExpr(getUnaryOpType(opers[0]), e);
        }
    }

    if (opers.size() > 2) {
        throw SyntaxError(opers[0].lineNo,
                "Too many unary operators precede an expression.");
    }

    if (getBinaryOpType(opers[0]) == BinaryOp::INVALID) {
        throw SyntaxError(opers[0].lineNo,
                "Expected binary operator not found.");
    }

    if (opers.size() == 2) {
        if (getUnaryOpType(opers[1]) == UnaryOp::INVALID) {
            throw SyntaxError(opers[1].lineNo,
                "Invalid unary operator before an expression.");
        }

        e = new UnaryOpExpr(getUnaryOpType(opers[1]), e);
    }

    return e;
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

    return new ParseSuccess<std::vector<Expression*> >(exprs);
}

/* Parse an IDOrMethodcall or a single level member access. */
ParseResult<IDOrMethodCall*> *parseIDOrMethodCall(const std::vector<Token>& ts,
                                                 bool id,
                                                 int s, int& endingToken)
{
    TokenType neededType = id ? TokenType::IDENTIFIER : TokenType::FIELD_REF;
    if (ts[s].type != neededType) {
        return new ParseFail<IDOrMethodCall*>(
                "Unexpected token found.");
    }

    // Strip away the period.
    const std::string idName = ts[s].lexeme.substr(id ? 0 : 1);

    if (s + 1 < (int)ts.size() and ts[s + 1].type == TokenType::LEFT_BRACKET) {
        LOG_MSG("%s\n", "left paren found, method call");
        int end = getClosingToken(ts, s + 1, (int)ts.size() - 1);
        if (end < 0) {
            throw SyntaxError(ts[s + 1].lineNo,
                    "Unbalanced parenthesis in an expression.");
        }
        
        ParseResult<std::vector<Expression*> >* exprs = 
                        parseCommaSeparatedExprs(ts, s + 1, end);

        endingToken = end;
        return new ParseSuccess<IDOrMethodCall*>(
                new IDOrMethodCall(idName, exprs->result()));
    } else {
       endingToken = s; 
       return new ParseSuccess<IDOrMethodCall*>(new IDOrMethodCall(idName));
    }
}

/* Read a member reference expression.*/
ParseResult<Expression*> *parseMemberRef(const std::vector<Token>& tokens,
                                         int s, int& endingToken)
{
    std::vector<IDOrMethodCall*> refs;
    endingToken = s;
    ParseResult<IDOrMethodCall*>* t = parseIDOrMethodCall(tokens,
                                                         true, s,
                                                         endingToken);
    refs.push_back(t->result());
    while (true) {
        ParseResult<IDOrMethodCall*> *acc = parseIDOrMethodCall(tokens, false,
                                                endingToken + 1, endingToken);
        if (!acc->isParseSuccessful()) {
            break;
        }

        refs.push_back(acc->result());
    }

    return new ParseSuccess<Expression*>(new MemberAccess(refs));
}

/* Top down recursive algorithm for operator precedence parsing.*/
ParseResult<Expression*> *topDownPrecedence(const std::vector<Expression*>& exprs,
                                            const std::vector<Token>& bOps,
                                            int start, int end)
{
    if (start > end) {
        throw std::logic_error("Empty range for topDownPrecedence");
    }
    else if (start == end) {
        return new ParseSuccess<Expression*>(exprs[start]);
    }

    int minPrec = 100;
    std::vector<int> minPrecIndices;

    for (int i = start;i < end; ++i) {
        int curPrec = getBinaryOpPrec(bOps[i].lexeme);
        if (curPrec < minPrec) {
            minPrec = curPrec;
            minPrecIndices.clear();
        }

        if (curPrec == minPrec)
            minPrecIndices.push_back(i);
    }

    if (minPrec == 100) {
        throw std::logic_error("Illogical code in Expression.cpp");
    }

    std::vector<Expression*> topLevelSubExprs;
    for (int i = 0;i < (int)minPrecIndices.size(); ++i) {
        int curStart = i == 0 ? start : (1 + minPrecIndices[i - 1]);
        int curEnd = minPrecIndices[i];

        ParseResult<Expression*> *subExpr = topDownPrecedence(exprs, bOps,
                                                              curStart,
                                                              curEnd);
        topLevelSubExprs.push_back(subExpr->result());
    }

    ParseResult<Expression*> *lastSubExpr = topDownPrecedence(exprs, bOps,
                                                    1 + minPrecIndices.back(),
                                                    end);
    topLevelSubExprs.push_back(lastSubExpr->result());

    Expression* finalResult = topLevelSubExprs[0];
    for (int i = 1;i < (int)topLevelSubExprs.size();i++) {
        int operIndex = minPrecIndices[i - 1];
        finalResult = new BinaryExpression(finalResult, topLevelSubExprs[i],
                                           getBinaryOpType(bOps[operIndex]));
    }

    return new ParseSuccess<Expression*>(finalResult);
}

/**
 * Read enough tokens from the token buffer and construct an expression object.
 * In Avaj language, expressions are always followed by either a semicolon or a
 * comma or a right paren, plus considering that expressions can be nested, the
 * range of tokens that form the expression can be isolated.
 *
 * ALGORITHM to parse Avaj expressions.
 *
 * 1. Isolate the tokens that'll form the expression.
 * 2. Recursively construct the nested expressions(member refs and
 * parenthesised sub expressions).
 * 3. Top level expressions and operators will be present at the top level.
 * 4. Use operator precedence to form BinaryOp and UnaryOp objects.
 */
ParseResult<Expression*> *parseExpr(const std::vector<Token>& tokens,
                                    int a, int b)
{
    LOG_MSG("%s %d %d\n", "Entering parseExpr(tokens)", a, b);
    if (b < 0) {
        LOG_MSG("%s\n", "First parseExpr(tokens) call");
        for (auto& t : tokens) {
            LOG_MSG("Token is %s\n", t.lexeme.c_str());
        }
        b = (int)tokens.size() - 1;
    }

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
            LOG_MSG("%s\n", "before parseMemberRef call");
            ParseResult<Expression*> *memberRef = 
                            parseMemberRef(tokens, i, endingToken);
            LOG_MSG("Address of returned memberRef is %p\n", memberRef);
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

    std::vector<Token> middleOps;
    for (int i = 0;i < (int)operators.size(); ++i) {
        topLevelExprs[i] = combine(operators[i], topLevelExprs[i], i == 0);
        if (i >= 1)
            middleOps.push_back(operators[i][0]);
    }

    LOG_MSG("%s %d %d\n", "Leaving parseExpr(tokens)", a, b);
    return topDownPrecedence(topLevelExprs, middleOps, 0,
                             (int)topLevelExprs.size() - 1);
}

// Isolate the expression tokens and pass them to the fnction above.
ParseResult<Expression*>* parseExpr(TokenBuffer& tokenBuffer)
{
    LOG_MSG("%s\n", "Entering parseExpr(tokenBuffer)");
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
        else if (tok.type == TokenType::SEMI_COLON) {
            // Semi colon is never part of an expression. This is an ill-formed
            // expression.
            throw SyntaxError(tok.lineNo,
                    "Unexpected semi-colon before ending the expression.");
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

    LOG_MSG("%s\n", "Leaving parseExpr(tokenBuffer)");
    return parseExpr(exprTokens);
}
