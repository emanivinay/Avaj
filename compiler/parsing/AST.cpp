#include "AST.h"

ParseResult<Import>* Import::tryParse(TokenBuffer& tokenBuffer)
{
    // Import statements are of the following form.
    // import "..." ;

    Token& kwToken = tokenBuffer.getCurrentToken();
    if (kwToken.type != TokenType::KEYWORD || kwToken.lexeme != "import") {
        tokenBuffer.putTokenBack(kwToken);
        return new ParseFail<Import>("import keyword not found");
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

    return new ParseSuccess<Import>(Import(strLiteralToken.lexeme));
}

ParseResult<AST>* AST::tryParse(TokenBuffer& tokenBuffer)
{
    return new ParseFail<AST>("AST::tryParse NotImplementedYet");
}
