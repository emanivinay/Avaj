#include "AST.h"

ParseResult<Import>* Import::tryParse(TokenBuffer& tokenBuffer)
{
    return new ParseFail<Import>("Import::tryParse NotImplementedYet");
}

ParseResult<AST>* AST::tryParse(TokenBuffer& tokenBuffer)
{
    return new ParseFail<AST>("AST::tryParse NotImplementedYet");
}
