#include "Parser.h"

Parser::Parser(const std::string& sourceFile)
{
    Lexer lexer(sourceFile);
    tokenList.clear();
    tokenIndex = 0;

    while (true) {
        Token tok = lexer.getNextToken();
        tokenList.push_back(tok);
        if (tok.type == TokenType::END_OF_FILE)
            break;
    }
}

AST Parser::constructAST()
{
    std::vector<Import> imports;
    std::vector<Class> classes;

    // Read all import statements and class definitions.
    
    if (getCurrentToken().type != TokenType::END_OF_FILE) {
        throw std::runtime_error(
                "Extraneous code at the end of the source file.");
    }

    return AST(imports, classes);
}
