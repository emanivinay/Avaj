#include "Statement.h"

// Define the destructor.
Statement::~Statement() {}

ParseResult<Statement*>* Statement::tryParse(TokenBuffer& tokenBuffer)
{
    return parseStmt(tokenBuffer);
}

ParseResult<Statement*> *parseStmt(TokenBuffer& tokenBuffer)
{
    return new ParseFail<Statement*>(
            "parseStmt not implemented yet");
}
