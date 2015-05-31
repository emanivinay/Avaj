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

/**
 * Parse a statement. Used when we know there's a statement coming up, but
 * don't know which kind.
 */
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
    // List of statements in this block.
    std::vector<Statement*> statements;

    static ParseResult<StatementBlock> *tryParse(TokenBuffer& tokenBuffer);

    // Once this object is constructed, takes over the management of its child
    // statements.
    StatementBlock(const std::vector<Statement*>& stmts):
        statements(stmts) {}

    // Statement block owns its child statement objects. Delete them and clear
    // the vector.
    ~StatementBlock()
    {
        for (auto stmtPtr: statements) {
            delete stmtPtr;
        }

        statements.clear();
    }
};
#endif
