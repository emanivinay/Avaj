#ifndef _STATEMENT_H_
#define _STATEMENT_H_

#include "headers.h"
#include "TokenBuffer.h"
#include "Expression.h"
#include "ParseResult.h"
#include "ParserUtils.h"

/**
 * Statements of the Avaj programming language.
 */
class Statement
{
public:
    virtual ~Statement() = 0;
};

ParseResult<Statement*> *parseStmt(TokenBuffer& tokenBuffer);

/**
 * Statements can be of several types. Variable declarations, assignments,
 * statement blocks, for/while statements, if conditionals etc..
 */

/**
 * A block of statements enclosed in braces. Such blocks execute in a new
 * scope.
 */
class StatementBlock: public Statement
{
public:
    // Once this object is constructed, takes over the management of its child
    // statements.
    StatementBlock(std::vector<Statement*> stmts):
        statements(stmts) {}

    std::vector<Statement*> statements;

    static ParseResult<StatementBlock> *tryParse(TokenBuffer& tokenBuffer);
};
#endif
