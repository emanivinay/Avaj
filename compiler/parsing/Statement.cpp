#include "Statement.h"

ParseResult<StatementBlock> *StatementBlock::tryParse(TokenBuffer& tokenBuffer)
{
    int startTokenBufferState = tokenBuffer.getState();

    if (!tokenBuffer.readLexemes({"{"})) {
        return new ParseFail<StatementBlock>(
                "Left brace not found");
    }

    std::vector<Statement*> stmts;
    while (true) {
        if (tokenBuffer.readLexemes({"}"})) {
            // Block ended.
            break;
        }

        ParseResult<Statement*> stmt = parseStmt(tokenBuffer);
        if (!stmt->isParseSuccessful()) {
            // syntax error.
            tokenBuffer.setState(startTokenBufferState);
            throw SyntaxError(tokenBuffer.line(), 
                    "Failed reading a statement.");
        }

        stmts.push_back(stmt->result());
    }

    return new ParseSuccess<StatementBlock>(
            StatementBlock(stmts));
}

ParseResult<Statement*> *parseStmt(TokenBuffer& tokenBuffer)
{
    return new ParseFail<Statement*>(
            "parseStmt not implemented yet");
}
