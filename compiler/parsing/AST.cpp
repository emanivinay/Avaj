#include "AST.h"
#include "ParserUtils.h"

ParseResult<Import*>* Import::tryParse(TokenBuffer& tokenBuffer)
{
    // Import statements are of the following form.
    // import "..." ;

    Token& kwToken = tokenBuffer.getCurrentToken();
    if (kwToken.type != TokenType::KEYWORD || kwToken.lexeme != "import") {
        tokenBuffer.putTokenBack(kwToken);
        return new ParseFail<Import*>("import keyword not found");
    }

    Token& strLiteralToken = tokenBuffer.getCurrentToken();
    if (strLiteralToken.type != TokenType::STRING_LITERAL) {
        int lineNo = strLiteralToken.lineNo;
        throw SyntaxError(lineNo, "No import string found after import keyword");
    }

    Token& semiColonToken = tokenBuffer.getCurrentToken(); 
    if (semiColonToken.type != TokenType::SEMI_COLON) {
        throw SyntaxError(semiColonToken.lineNo, 
                "Semi colon not found in the import statement.");
    }

    return new ParseSuccess<Import*>(new Import(strLiteralToken.lexeme));
}

/* Parse a source file into an abstract syntax tree(AST).*/
ParseResult<AST*>* AST::tryParse(TokenBuffer& tokenBuffer)
{
    // Each source file has several imports followed by class definitions.
    ParseResult<std::vector<Import*> > *parsedImports = 
                    tryParseMultiple<Import>(tokenBuffer);
    std::vector<Import*> imports = parsedImports->result();
    delete parsedImports;

    ParseResult<std::vector<Class*> > *parsedClassDefns =
                    tryParseMultiple<Class>(tokenBuffer);
    std::vector<Class*> classes = parsedClassDefns->result();
    delete parsedClassDefns;

    Token eofToken = tokenBuffer.getCurrentToken();
    if (eofToken.type != TokenType::END_OF_FILE) {
        throw SyntaxError(eofToken.lineNo,
                "Extraneous input at the end.");
    }

    return new ParseSuccess<AST*>(new AST(imports, classes));
}
