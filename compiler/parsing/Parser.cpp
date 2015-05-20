#include "Parser.h"

Parser::Parser(const std::string& sourceFile):
    lexer(sourceFile)
{
}

AST Parser::constructAST()
{
    std::vector<Import> imports;
    std::vector<Class> classes;

    // Read all import statements and class definitions.
    return AST(imports, classes);
}
