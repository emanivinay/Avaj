#include "Class.h"

/* Try to read a data field declaration in a class body.*/
ParseResult<DataField>* DataField::tryParse(TokenBuffer& tokenBuffer)
{
    // TODO(Vinay Emani) -> Implement this.
    return new ParseFail<DataField>(
            "DataField::tryParse not implemented yet.");
}

/* Try to read a method definition. */
ParseResult<MethodDefn>* MethodDefn::tryParse(TokenBuffer& tokenBuffer)
{
    // TODO(Vinay) -> Implement this.
    return new ParseFail<MethodDefn>(
            "MethodDefn::tryParse not implemented yet.");
}

ParseResult<Class>* Class::tryParse(TokenBuffer& tokenBuffer)
{
    // TODO(Vinay) -> Implement this.
    return new ParseFail<Class>("Class::tryParse not implemented yet.");
}
