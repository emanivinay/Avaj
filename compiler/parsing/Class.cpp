#include "Class.h"

/* Try to read a data field declaration in a class body.*/
ParseResult<DataField>* DataField::tryParse(TokenBuffer& tokenBuffer)
{
    // Field declarations are of the form -
    // public/private? static? typename? id? ;

    
}

/* Try to read a method definition. */
ParseResult<MethodDefn>* MethodDefn::tryParse(TokenBuffer& tokenBuffer)
{
    // TODO(Vinay) -> Implement this.
    return new ParseFail<MethodDefn>(
            "MethodDefn::tryParse not implemented yet.");
}

/* Try to read a class definition. */
ParseResult<Class>* Class::tryParse(TokenBuffer& tokenBuffer)
{
    bool publicness = true;

    if (tokenBuffer.readLexemes({"private", "class"})) {
        publicness = false;
    } else if (tokenBuffer.readLexemes({"public", "class"})) {
    } else if (tokenBuffer.readLexemes({"class"})) {
    } else {
        return new ParseFail<Class>("Not a class definition.");
    }

    // Read the class name identifier.
    Token& classNameToken = tokenBuffer.getCurrentToken();
    if (classNameToken.type != TokenType::IDENTIFIER) {
        // Syntax error.
        throw SyntaxError(classNameToken.lineNo,
                "Class name identifier not found.");
    }

    if (!tokenBuffer.readLexemes({"{"})) {
        throw SyntaxError(classNameToken.lineNo,
                "Left brace not found");
    }

    std::vector<MethodDefn> methods;

    auto parsedFields = tryParseMultiple<DataField>(tokenBuffer);
    std::vector<DataField> fields = parsedFields->result();
    delete parsedFields;

    if (!tokenBuffer.readLexemes({"}"})) {
        throw SyntaxError(0, "Right brace not found");
    }

    return new ParseSuccess<Class>(
            Class(fields, methods, publicness, classNameToken.lexeme));
}
