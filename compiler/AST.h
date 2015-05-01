#include "headers.h"

/**
 * This module defines the AST data structure and related types. 
 */

class Class;
class Method;
class Statement;
class Expression;


/**
 * An abstract syntax tree, or simply an AST, 
 */
class AST
{
private:
    std::vector<Class> classes;
};
