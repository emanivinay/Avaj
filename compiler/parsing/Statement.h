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
 * A return statement. Two possible variations.
 * `return` expr `;`
 * `return` `;`
 */
class ReturnStmt: public Statement
{
public:
    Expression *const returnedExpr;

    ReturnStmt(Expression* const retExpr = nullptr):
        returnedExpr(retExpr) {}

    ~ReturnStmt()
    {
        if (returnedExpr != nullptr)
        {
            delete returnedExpr;
        }
    }

    static ParseResult<ReturnStmt*> *tryParse(TokenBuffer& tokenBuffer)
    {
        if (tokenBuffer.readLexemes({"return", ";"})) {
            return new ParseSuccess<ReturnStmt*>(nullptr);
        }
        else if (tokenBuffer.readLexemes({"return"})) {
            ParseResult<Expression*> *expr = parseExpr(tokenBuffer);
            if (expr->isParseSuccessful()) {
                return new ParseSuccess<ReturnStmt*>(
                        new ReturnStmt(expr->result()));
            }
            // Expression expected.
            throw SyntaxError(tokenBuffer.line(),
                    "Expression expected after the return keyword.");
        }

        return new ParseFail<ReturnStmt*>(
                "return keyword expected, but not found");
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

/* Statements for assigning a new value to a variable.*/
class Assignment: public Statement
{
public:
    const std::string varName;
    Expression *const newValueExpr;

    Assignment(const std::string& var, Expression *const newValExpr):
        varName(var), newValueExpr(newValExpr) {}

    ~Assignment()
    {
        delete newValueExpr;
    }
};

/**
 * Declare and initialize a variable in a single statement
*/
class DeclareAndInit: public Statement
{
public:
    const std::string typeName;
    const std::string varName;
    Expression* const valueExpr;

    DeclareAndInit(const std::string& type, const std::string& name,
               Expression* valExpr):
        typeName(type), varName(name), valueExpr(valExpr) {}

    ~DeclareAndInit()
    {
        delete valueExpr;
    }

    static ParseResult<DeclareAndInit*> *tryParse(TokenBuffer& tokenBuffer);
};

/* Variable declarations.*/
class VarDecl: public Statement
{
public:
    const std::string typeName;
    const std::string varName;

    VarDecl(const std::string& type, const std::string& name):
        typeName(type), varName(name) {}

    static ParseResult<VarDecl*> *tryParse(TokenBuffer& tokenBuffer);
};

/* A compound statement to do multiple declarations or assignments.*/
class HangingStmt: public Statement
{
public:
    std::vector<Statement*> statements;

    HangingStmt(const std::vector<Statement*>& stmts):
        statements(stmts) {}

    static ParseResult<HangingStmt*> *tryParse(TokenBuffer& tokenBuffer);

    ~HangingStmt()
    {
        for (auto stmt: statements) {
            delete stmt;
        }

        statements.clear();
    }
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
