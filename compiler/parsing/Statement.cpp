#include "Statement.h"

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
    return new ParseFail<ForStmt*>(
            "ForStmt::tryParse not implemented yet.");
}

ParseResult<VarDecl*> *VarDecl::tryParse(TokenBuffer& tokenBuffer)
{
    return new ParseFail<VarDecl*>(
            "VarDecl::tryParse not implemented yet.");
}

ParseResult<Assignment*> *Assignment::tryParse(TokenBuffer& tokenBuffer)
{
    return new ParseFail<Assignment*>(
            "Assignment::tryParse not implemented yet.");
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
    tryAndReturn(ContinueStmt, continueStmt);
    tryAndReturn(BreakStmt, breakStmt);

    tryAndReturn(StatementBlock, blockStmt);
    tryAndReturn(IfStmt, ifStmt);
    tryAndReturn(ForStmt, forStmt);
    tryAndReturn(VarDecl, varDecl);
    tryAndReturn(Assignment, assignStmt);
    throw SyntaxError(tokenBuffer.line(),
                      "Statement expected, not found");
}
