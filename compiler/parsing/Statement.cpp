#include "Statement.h"

/* Get the assignment operator type of a given token. */
AssignmentOp getAssignmentOpType(const Token& tok)
{
    switch (tok.type)
    {
        case TokenType::ASSIGNMENT:
            return AssignmentOp::EQ;
        case TokenType::PLUS_EQ:
            return AssignmentOp::PLUS_EQ;
        case TokenType::MINUS_EQ:
            return AssignmentOp::MINUS_EQ;
        case TokenType::MULT_EQ:
            return AssignmentOp::MULT_EQ;
        case TokenType::DIV_EQ:
            return AssignmentOp::DIV_EQ;
        case TokenType::MOD_EQ:
            return AssignmentOp::MOD_EQ;
        case TokenType::OR_EQ:
            return AssignmentOp::OR_EQ;
        case TokenType::BITWISE_OR_EQ:
            return AssignmentOp::BITWISE_OR_EQ;
        case TokenType::AND_EQ:
            return AssignmentOp::AND_EQ;
        case TokenType::BITWISE_AND_EQ:
            return AssignmentOp::BITWISE_AND_EQ;
        case TokenType::BITWISE_NOT_EQ:
            return AssignmentOp::BITWISE_NOT_EQ;
        case TokenType::BITWISE_XOR_EQ:
            return AssignmentOp::BITWISE_XOR_EQ;
        default:
            return AssignmentOp::INVALID;
    }
}

// Define the destructor.
Statement::~Statement() {}

ParseResult<EmptyStatement*> *EmptyStatement::tryParse(TokenBuffer& tokenBuffer)
{
    if (tokenBuffer.readLexemes({";"})) {
        return new ParseSuccess<EmptyStatement*>(new EmptyStatement());
    }

    return new ParseFail<EmptyStatement*>(
            "Semi colon expected, but not found");
}

ParseResult<StatementBlock*> *StatementBlock::tryParse(TokenBuffer& tokenBuffer)
{
    if (!tokenBuffer.readLexemes({"{"})) {
        // Not a statement block;
        return new ParseFail<StatementBlock*>(
                "Curly brace expected, but found");
    }

    std::vector<Statement*> blockStmts;
    while (true) {
        if (tokenBuffer.readLexemes({"}"})) {
            break;
        }
        auto stmt = parseStmt(tokenBuffer);
        blockStmts.push_back(stmt->result());
    }
    return new ParseSuccess<StatementBlock*>(new StatementBlock(blockStmts));
}

ParseResult<IfStmt*> *IfStmt::tryParse(TokenBuffer& tokenBuffer)
{
    // `if` `(` expr `)` (`else` stmt)?
    if (!tokenBuffer.readLexemes({"if", "("})) {
        return new ParseFail<IfStmt*>(
                "if keyword and left paren expected, not found.");
    }

    ParseResult<Expression*> *condition = parseExpr(tokenBuffer);
    if (!condition->isParseSuccessful()) {
        throw SyntaxError(tokenBuffer.line(),
                "Failed reading a condition expression.");
    }

    ParseResult<Statement*> *consequent = parseStmt(tokenBuffer);
    if (!consequent->isParseSuccessful()) {
        throw SyntaxError(tokenBuffer.line(),
                "Failed reading the statement.");
    }

    ParseResult<Statement*> *alt;
    if (tokenBuffer.readLexemes({"else"})) {
        alt = parseStmt(tokenBuffer);
    } else {
        alt = new ParseSuccess<Statement*>(new EmptyStatement());
    }

    return new ParseSuccess<IfStmt*>(new IfStmt(condition->result(),
                                                consequent->result(),
                                                alt->result()));
}

ParseResult<ForStmt*> *ForStmt::tryParse(TokenBuffer& tokenBuffer)
{
    // `for` `(` stmt expr `;` hanging_stmt `)` stmt
    return new ParseFail<ForStmt*>(
            "ForStmt::tryParse not implemented yet.");
}

#define tryAndReturn(STMT_TYPE, stmtObj) ParseResult<STMT_TYPE*> *stmtObj\
        = STMT_TYPE::tryParse(tokenBuffer);\
        if (stmtObj->isParseSuccessful()) {\
            auto ret = new ParseSuccess<Statement*>(stmtObj->result());\
            delete stmtObj;\
            return ret;\
        }\
        delete stmtObj;
    
/**
 * If, for and while statements can be parsed by looking one token ahead.
 * Statement blocks are enclosed in curly braces and thus only need one token
 * lookahead.
 * Assignments can be parsed by looking two tokens ahead. Likewise variable
 * declarations need three token lookahead.
 */
ParseResult<Statement*> *parseStmt(TokenBuffer& tokenBuffer)
{
    
    tryAndReturn(EmptyStatement, emptyStmt);
    tryAndReturn(ContinueStmt, contStmt);
    tryAndReturn(ReturnStmt, retStmt);
    tryAndReturn(BreakStmt, brkStmt);

    tryAndReturn(StatementBlock, blockStmt);
    tryAndReturn(IfStmt, ifStmt);
    tryAndReturn(ForStmt, forStmt);
    tryAndReturn(HangingStmt, hangingStmt);

    throw SyntaxError(tokenBuffer.line(),
                      "Statement expected, not found");
}

ParseResult<std::vector<Statement*> > *parseAssignments(
                                        TokenBuffer& tokenBuffer)
{
    // Try to read a statement of multiple assignments.
    // Reset the token buffer state and return failure in case parsing fails.
    // VARNAME `=` EXPRESSION (`,` VARNAME `=` EXPRESSION)* `;`

    int startingTokenBufferState = tokenBuffer.getCurrentState();

    std::vector<Statement*> ret;
    for (bool firstTime = true; ; firstTime = false) {
        if (!firstTime) {
            // Either a `;` or a `,` are expected.
            if (tokenBuffer.readLexemes({";"})) {
                break;
            }

            if (!tokenBuffer.readLexemes({","})) {
                tokenBuffer.setState(startingTokenBufferState);
                return new ParseFail<std::vector<Statement*> >(
                        "Either a comma or semi-colon expected, but not found");
            }
        }

        Token varToken = tokenBuffer.getCurrentToken();
        if (varToken.type != TokenType::IDENTIFIER) {
            tokenBuffer.setState(startingTokenBufferState);
            return new ParseFail<std::vector<Statement*> >(
                    "No variable found in assignment statement.");
        }

        Token assignOpToken = tokenBuffer.getCurrentToken();
        if (getAssignmentOpType(assignOpToken) == AssignmentOp::INVALID)
        {
            tokenBuffer.setState(startingTokenBufferState);
            return new ParseFail<std::vector<Statement*> >(
                    "Assignment operator not found after the variable");
        }

        // Assignment operator seen, so this is an assignment statement.
        // Failure after this point means a syntax error.
        ParseResult<Expression*> *expr = parseExpr(tokenBuffer);
        if (!expr->isParseSuccessful()) {
            throw SyntaxError(assignOpToken.lineNo,
                    "Expression not found after the assignment operator.");
        }

        ret.push_back(new Assignment(varToken.lexeme, expr->result(),
                                     getAssignmentOpType(assignOpToken)));
    }

    return new ParseSuccess<std::vector<Statement*> >(ret);
}

ParseResult<std::vector<Statement*> > *parseDeclarations(
                                        TokenBuffer& tokenBuffer)
{
    // TYPENAME VARNAME (`=` EXPR)? (`,` VARNAME (`=` EXPR)?)* `;`
    int tokenBufferStartState = tokenBuffer.getCurrentState();

    Token typeNameToken = tokenBuffer.getCurrentToken();
    if (typeNameToken.type != TokenType::IDENTIFIER) {
        tokenBuffer.setState(tokenBufferStartState);
        return new ParseFail<std::vector<Statement*> >(
                "Type name expected in a variable declaration.");
    }

    std::vector<Statement*> ret;
    for (bool firstTime = true; ; firstTime = false) {
        if (tokenBuffer.readLexemes({";"}))
            break;

        if (!firstTime) {
            if (!tokenBuffer.readLexemes({","})) {
                throw SyntaxError(tokenBuffer.line(),
                        "Comma expected but not found");
            }
        }

        Token varNameToken = tokenBuffer.getCurrentToken();
        if (varNameToken.type != TokenType::IDENTIFIER) {
            throw SyntaxError(tokenBuffer.line(),
                    "Variable name expected, not found");
        }

        if (tokenBuffer.readLexemes({"="})) {
            ParseResult<Expression*> *expr = parseExpr(tokenBuffer);
            if (!expr->isParseSuccessful()) {
                throw SyntaxError(tokenBuffer.line(),
                    "Illegal expression in the assignment statement.");
            }
            ret.push_back(new DeclareAndInit(
                                typeNameToken.lexeme,
                                varNameToken.lexeme,
                                expr->result()));
        } else {
            ret.push_back(new VarDecl(typeNameToken.lexeme,
                                      varNameToken.lexeme));
        }
    }

    if (ret.empty()) {
        // TYPENAME `;`
        throw SyntaxError(tokenBuffer.line(),
                "Invalid statement");
    }

    return new ParseSuccess<std::vector<Statement*> >(ret);
}

ParseResult<HangingStmt*> *HangingStmt::tryParse(TokenBuffer& tokenBuffer)
{
    auto ret = parseAssignments(tokenBuffer);
    if (ret->isParseSuccessful()) {
        HangingStmt *hangingStmt = new HangingStmt(ret->result());
        delete ret;
        return new ParseSuccess<HangingStmt*>(hangingStmt);
    }

    ret = parseDeclarations(tokenBuffer);
    if (ret->isParseSuccessful()) {
        HangingStmt *hangingStmt = new HangingStmt(ret->result());
        delete ret;
        return new ParseSuccess<HangingStmt*>(hangingStmt);
    }

    return new ParseFail<HangingStmt*>(
            "Not a variable declaration nor an assignment statement.");
}
