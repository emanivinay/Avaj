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

ParseResult<AST>* Parser::constructAST()
{
    std::vector<Import> imports;
    std::vector<Class> classes;

    // Read all import statements and class definitions.
    
    if (getCurrentToken().type != TokenType::END_OF_FILE) {
        // Extraneous input at the end of the file.
        return new ParseFail<AST>(
                "Extraneous input at the end.");
    }

    // Note := Implicit conversion to ParseResult<AST> happening here.
    return new ParseSuccess<AST>(AST(imports, classes));
}
