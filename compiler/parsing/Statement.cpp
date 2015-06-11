#include "Statement.h"

// Define the destructor.
Statement::~Statement() {}

// Initialize the empty statement singleton to null.
EmptyStatement *EmptyStatement::emptyStmt = nullptr;

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
    int startState = tokenBuffer.getCurrentState();

    // `if` `(` expression `)` stmt (`else` `if` `(` expr `)` stmt)* (`else`
    // stmt)?
    if (!tokenBuffer.readLexemes({"if", "("})) {
        return new ParseFail<IfStmt*>(
                "If keyword and left paren expected, missing.");
    }
    // If and ( found, if statement must follow.
    ParseResult<Expression*> *testExpr = parseExpr(tokenBuffer);
    if (!tokenBuffer.readLexemes({")"})) {
        throw SyntaxError(tokenBuffer.line(),
                "Closing paren not found after first condition expression.");
    }

    // Read a statement.
    ParseResult<Statement*> *consequent = parseStmt(tokenBuffer);

    // Read else if clauses.
    while (true) {
        if (tokenBuffer.readLexemes({"else", "if"})) {
            // else if block starts.
        } else {
            break;
        }
    }

    // Read the final else clause, if exists.
    return new ParseFail<IfStmt*>("IfStmt::tryParse not implemented yet.");
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
    
    tryAndReturn(StatementBlock, blockStmt);
    tryAndReturn(IfStmt, ifStmt);
    tryAndReturn(ForStmt, forStmt);
    tryAndReturn(VarDecl, varDecl);
    tryAndReturn(Assignment, assignStmt);
    throw SyntaxError(tokenBuffer.line(),
                      "Statement expected, not found");
}
