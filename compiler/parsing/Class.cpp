#include "Class.h"

/**
 * Fields common to both data fields and methods in a class body. Common to
 * their syntactic forms as well.
 */
class ClassMemberCommonData
{
public:
    bool publicness;
    bool staticness;
    bool finalness;

    std::string type;
    std::string name;

    ClassMemberCommonData(bool _p, bool _s, bool _f,
            std::string _typ, std::string _na):
        publicness(_p), staticness(_s), finalness(_f),
        type(_typ), name(_na) {}
};

/* MethodDefn and DataField syntactic forms have qualifiers at the beginning
 * followed by type and name tokens. Try to parse this common part. */
static ClassMemberCommonData parseClassMemberCommon(TokenBuffer& tokenBuffer)
{
    int startTokenBufferState = tokenBuffer.getCurrentState();

    bool publicness = false;
    if (parseKeywordOptional("public", tokenBuffer)) {
        publicness = true;
    } else if (parseKeywordOptional("private", tokenBuffer)) {
    }

    bool staticness = parseKeywordOptional("static", tokenBuffer);
    bool finalness = parseKeywordOptional("final", tokenBuffer);

    // If either the typename or variable name token isn't found,
    // it's a syntax error.
    Token& typeNameToken = tokenBuffer.getCurrentToken();
    if (typeNameToken.type != TokenType::IDENTIFIER) {
        tokenBuffer.setState(startTokenBufferState);
        throw SyntaxError(typeNameToken.lineNo,
                "Typename not found in this class member declaration.");
    }

    Token& fieldNameToken = tokenBuffer.getCurrentToken();
    if (fieldNameToken.type != TokenType::IDENTIFIER) {
        tokenBuffer.setState(startTokenBufferState);
        throw SyntaxError(fieldNameToken.lineNo,
                "Field name identifier not found");
    }

    return ClassMemberCommonData {publicness, staticness, finalness,
                    typeNameToken.lexeme, fieldNameToken.lexeme};
}

/* Try to read a data field declaration in a class body.*/
ParseResult<DataField>* DataField::tryParse(TokenBuffer& tokenBuffer)
{
    // Field declarations are of the form -
    // public/private? static? final? typename id ;

    int startTokenBufferState = tokenBuffer.getCurrentState();
    ClassMemberCommonData commonData = parseClassMemberCommon(tokenBuffer);
    Token& token = tokenBuffer.getCurrentToken();
    if (token.type != TokenType::SEMI_COLON) {
        // This is not a field declaration. Possibly a method defn, so reset
        // the token buffer state and return parse failure.
        tokenBuffer.setState(startTokenBufferState);
        return new ParseFail<DataField>("Not a data field declaration.");
    }

    return new ParseSuccess<DataField>(
            DataField(commonData.name, commonData.type,
                      commonData.publicness, commonData.staticness,
                      commonData.finalness));
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
