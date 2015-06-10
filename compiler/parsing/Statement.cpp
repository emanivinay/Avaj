#include "Statement.h"

// Define the destructor.
Statement::~Statement() {}

ParseResult<Statement*>* Statement::tryParse(TokenBuffer& tokenBuffer)
{
    return parseStmt(tokenBuffer);
}

ParseResult<StatementBlock*> *StatementBlock::tryParse(TokenBuffer& tokenBuffer)
{
    return new ParseFail<StatementBlock*>(
            "StatementBlock::tryParse not implemented yet.");
}

ParseResult<IfStmt*> *IfStmt::tryParse(TokenBuffer& tokenBuffer)
{
    return new ParseFail<IfStmt*>(
            "IfStmt::tryParse not implemented yet.");
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

/**
 * If, for and while statements can be parsed by looking one token ahead.
 * Statement blocks are enclosed in curly braces and thus only need one token
 * lookahead.
 * Assignments can be parsed by looking two tokens ahead. Likewise variable
 * declarations need three token lookahead.
 */
ParseResult<Statement*> *parseStmt(TokenBuffer& tokenBuffer)
{
    ParseResult<StatementBlock*> *blockStmt = StatementBlock::tryParse(
                                                    tokenBuffer);

    if (blockStmt->isParseSuccessful()) {
        auto ret = new ParseSuccess<Statement*>(blockStmt->result());
        delete blockStmt;
        return ret;
    }
    delete blockStmt;

    ParseResult<IfStmt*> *ifStmt = IfStmt::tryParse(tokenBuffer);

    if (ifStmt->isParseSuccessful()) {
        auto ret = new ParseSuccess<Statement*>(ifStmt->result());
        delete ifStmt;
        return ret;
    }
    delete ifStmt;

    ParseResult<ForStmt*> *forStmt = ForStmt::tryParse(tokenBuffer);

    if (forStmt->isParseSuccessful()) {
        auto ret = new ParseSuccess<Statement*>(forStmt->result());
        delete forStmt;
        return ret;
    }
    delete forStmt;

    ParseResult<VarDecl*> *declStmt = VarDecl::tryParse(tokenBuffer);

    if (declStmt->isParseSuccessful()) {
        auto ret = new ParseSuccess<Statement*>(declStmt->result());
        delete declStmt;
        return ret;
    }
    delete declStmt;

    ParseResult<Assignment*> *assignStmt = Assignment::tryParse(tokenBuffer);

    if (assignStmt->isParseSuccessful()) {
        auto ret = new ParseSuccess<Statement*>(assignStmt->result());
        delete assignStmt;
        return ret;
    }
    delete assignStmt;

    return new ParseFail<Statement*>(
            "No statement found here.");
}
