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

    static ParseResult<Statement*> *tryParse(TokenBuffer& tokenBuffer);
};

/* Definitions for different types of statements follow. */

// Statement blocks, if/for/while statements, assignments, var declarations 

/**
 * A block of code, enclosed in curly braces. Introduces a new scope.
 */
class StatementBlock: public Statement
{
public:
    const std::vector<Statement*> statements;

    StatementBlock(const std::vector<Statement*>& stmts):
        statements(stmts) {}

    ~StatementBlock()
    {
        for (auto stmtPtr: statements) {
            delete stmtPtr;
        }
    }
};

/**
 * Variable assignment, in which a variable gets assigned a value(which is an
 * expression in source code.)
*/
class Assignment: public Statement
{
public:
    const std::string typeName;
    const std::string varName;
    Expression* const valueExpr;

    Assignment(const std::string& type, const std::string& name,
               Expression* valExpr):
        typeName(type), varName(name), valueExpr(valExpr) {}

    ~Assignment()
    {
        delete valueExpr;
    }
};

class VarDecl: public Statement
{
public:
    const std::string typeName;
    const std::string varName;

    VarDecl(const std::string& type, const std::string& name):
        typeName(type), varName(name) {}
};

/* If statement is a sequence of condition, statement_block pairs.*/
class IfStmt: public Statement
{
public:
    const std::vector<Expression*> conditions;
    const std::vector<Statement*> clauses;

    // General if statement.
    IfStmt(const std::vector<Expression*> conds,
           const std::vector<Statement*> _cls):
        conditions(conds), clauses(_cls) {}

    // Simple if statement, with no alternative clause.
    IfStmt(Expression* cond, Statement* consequent):
        conditions(std::vector<Expression*>{cond}),
        clauses(std::vector<Statement*>{consequent}) {}

    ~IfStmt()
    {
        for (auto cond: conditions) {
            delete cond;
        }

        for (auto clause: clauses) {
            delete clause;
        }
    }
};

/**
 * Classic for statement with an init statement, test expression, 
 * iteration statement and a statement block.
 */
class ForStmt: public Statement
{
public:
    Statement *const initStmt;
    Expression *const testExpr;
    Statement *const iterateStmt;
    Statement *const body;

    ForStmt(Statement* const init, Expression* const test,
            Statement* const iter, Statement* const _body):
        initStmt(init), testExpr(test), iterateStmt(iter), body(_body) {}

    ~ForStmt()
    {
        delete initStmt;
        delete testExpr;
        delete iterateStmt;
        delete body;
    }
};

/**
 * Parse a statement starting at the current position. A valid statement is
 * expected when calling this, so parseStmt either returns a valid statement
 * object or throws a SyntaxError exception.
 */
ParseResult<Statement*> *parseStmt(TokenBuffer& tokenBuffer);
#endif
