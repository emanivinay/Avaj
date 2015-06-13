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

/* Definitions for different types of statements follow. */

// Statement blocks, if/for/while statements, assignments, var declarations 
// Simple statements like expr `;` are also valid statements. Continue/break
// are also supported. Empty statements are also provided.

/* Empty statements are simply extraneous semi-colons.*/
class EmptyStatement: public Statement
{
public:
    static ParseResult<EmptyStatement*> *tryParse(TokenBuffer& tokenBuffer);
};

/* A continue statement. Is only valid inside a loop body.*/
class ContinueStmt: public Statement
{
public:
    static ParseResult<ContinueStmt*> *tryParse(TokenBuffer& tokenBuffer)
    {
        if (tokenBuffer.readLexemes({"continue", ";"})) {
            return new ParseSuccess<ContinueStmt*>(new ContinueStmt());
        }

        return new ParseFail<ContinueStmt*>(
                "continue and `;` expected");
    }
 
};

/* A break statement. Is only valid inside a loop body.*/
class BreakStmt: public Statement
{
public:
    static ParseResult<BreakStmt*> *tryParse(TokenBuffer& tokenBuffer)
    {
        if (tokenBuffer.readLexemes({"break", ";"})) {
            return new ParseSuccess<BreakStmt*>(new BreakStmt());
        }

        return new ParseFail<BreakStmt*>(
                "break and `;` expected");
    }
};

/**
 * Statements of the form expr `;` are valid and simply evaluate the
 * expression.
 */
class ExprStatement: public Statement
{
public:
    Expression* const expr;
    
    ExprStatement(Expression* e):
        expr(e) {}

    ~ExprStatement()
    {
        delete expr;
    }
};

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

    static ParseResult<StatementBlock*> *tryParse(TokenBuffer& tokenBuffer);
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

    static ParseResult<Assignment*> *tryParse(TokenBuffer& tokenBuffer);
};

class VarDecl: public Statement
{
public:
    const std::string typeName;
    const std::string varName;

    VarDecl(const std::string& type, const std::string& name):
        typeName(type), varName(name) {}

    static ParseResult<VarDecl*> *tryParse(TokenBuffer& tokenBuffer);
};

/* If statement is a sequence of condition, statement_block pairs.*/
class IfStmt: public Statement
{
public:
    Expression *const condition;
    Statement *const consequent;
    Statement *const alternate;

    IfStmt(Expression* const cond, Statement *const stmt, Statement *const alt):
        condition(cond), consequent(stmt) , alternate(alt){}

    ~IfStmt()
    {
        delete condition;
        delete consequent;
        delete alternate;
    }

    static ParseResult<IfStmt*> *tryParse(TokenBuffer& tokenBuffer);
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

    static ParseResult<ForStmt*> *tryParse(TokenBuffer& tokenBuffer);
};

/**
 * Parse a statement starting at the current position. A valid statement is
 * expected starting at the current position, so parseStmt either returns a
 * valid statement object or throws a SyntaxError exception.
 */
ParseResult<Statement*> *parseStmt(TokenBuffer& tokenBuffer);
#endif
