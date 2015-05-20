#ifndef _STATEMENT_H_
#define _STATEMENT_H_

#include "headers.h"
#include "Expression.h"

/**
 * Statements of the Avaj programming language.
 */
class Statement
{
public:
    virtual ~Statement() = 0;
};

/* Several subtypes of statements follow. */

/* Variable declaration.*/
class VarDecl: public Statement
{
public:
    const std::vector<std::string> varNames;
    const std::vector<Expression> exprs;
    const bool finality;
    const std::string typeName;

    VarDecl(const std::vector<std::string>& _varNames,
            const std::vector<Expression>& _exprs,
            const std::string& _typeName
            const bool _finality): varNames(_varNames), exprs(_exprs),
        finality(_finality), typeName(_typeName) {}
};

/* A Statement block, enclosed in curly braces. */
class StatementBlock: public Statement
{
public:
    StatementBlock(const std::vector<Statement*>& _stmts):
        stmts(_stmts) {}

    const std::vector<Statement*> stmts;
};

class IfStatement: public Statement
{
public:
    IfStatement(const std::vector<Expression*>& _exprs,
                const std::vector<Statement*>& _stmts):
        exprs(_exprs), stmts(_stmts) {}

    const std::vector<Expression*> exprs;
    const std::vector<Statement*> stmts;
};

class ForStatement: public Statement
{
public:
};
#endif
