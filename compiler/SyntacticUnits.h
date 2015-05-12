#ifndef _SYNTACTIC_UNITS_H_
#define _SYNTACTIC_UNITS_H_

/**
 * Syntactic units are components of the source code. Expressions, statements,
 * literals and their sub varieties etc.. make up the code. If tokens are like
 * the words of a programming language, these units are the sentences, phrases
 * and paragraphs. The job of the parser then is to process a stream of tokens
 * and group them into these syntactic units.
 */

/**
 * Expressions are those units that evaluate to a value. e.g., an expression
 * 1 + 2 evaluates to 3, while the expr. "asd" evaluates to itself. Expressions
 * may also be used to refer to existing values. e.g. myObj.a refers to a field
 * named a within the value myObj.
 */
class Expression
{
public:
    virtual ~Expression() = 0;
};

/* Definitions for sub varieties of expressions follow.*/

/**
 * A statement in an imperative programming language denotes an action to be
 * performed. Statements can and frequently do affect the program state.
 * Typically, statements are used to modify the program state, interact with
 * outside world etc.. Statements can be assignments, variable declarations,
 * method calls etc..
 */
class Statement
{
public:
    virtual ~Statement() = 0;
};

#endif
