#include "Class.h"

/**
 * Fields common to both data fields and methods in a class body. Common to
 * their syntactic forms as well.
 */
class ClassMemberCommonData
{
public:
    const bool publicness;
    const bool staticness;
    const bool finalness;

    const std::string type;
    const std::string name;

    ClassMemberCommonData(bool _p, bool _s, bool _f,
            std::string _typ, std::string _na):
        publicness(_p), staticness(_s), finalness(_f),
        type(_typ), name(_na) {}
};

/* MethodDefn and DataField syntactic forms have qualifiers at the beginning
 * followed by type and name tokens. Try to parse this common part. */
ParseResult<ClassMemberCommonData*> *parseClassMemberCommon(
                                        TokenBuffer& tokenBuffer)
{
    // (`public`|`private`)? `static`? `final`? TYPENAME ID
    bool publicness = false;
    if (parseKeywordOptional("public", tokenBuffer)) {
        publicness = true;
    }
    else if (parseKeywordOptional("private", tokenBuffer)) {}

    bool staticness = parseKeywordOptional("static", tokenBuffer);
    bool finalness = parseKeywordOptional("final", tokenBuffer);

    Token typeNameToken = tokenBuffer.getCurrentToken();
    if (typeNameToken.type != TokenType::IDENTIFIER) {
        throw SyntaxError(tokenBuffer.line(), 
                "Typename not found in a class member/method declaration.");
    }

    Token varNameToken = tokenBuffer.getCurrentToken();
    if (varNameToken.type != TokenType::IDENTIFIER) {
        throw SyntaxError(tokenBuffer.line(), 
                "Variable name not found in a class member/method declaration.");
    }

    return new ParseSuccess<ClassMemberCommonData*>(
            new ClassMemberCommonData(publicness, staticness, finalness,
                                      typeNameToken.lexeme,
                                      varNameToken.lexeme));
}

ParseResult<MethodParams*> *MethodParams::tryParse(TokenBuffer& tokenBuffer)
{
    return new ParseFail<MethodParams*>(
            "MethodParams::tryParse yet to be implemented.");
}

/* Try to read a data field declaration in a class body.*/
ParseResult<DataField*>* DataField::tryParse(TokenBuffer& tokenBuffer)
{
    // Field declarations are of the form -
    // public/private? static? final? typename id ;

    int startTokenBufferState = tokenBuffer.getCurrentState();
    ParseResult<ClassMemberCommonData*> *commonData = 
                                        parseClassMemberCommon(tokenBuffer);

    Token& token = tokenBuffer.getCurrentToken();
    if (token.type != TokenType::SEMI_COLON) {
        // This is not a field declaration. Possibly a method defn, so reset
        // the token buffer state and return parse failure.
        tokenBuffer.setState(startTokenBufferState);
        return new ParseFail<DataField*>("Not a data field declaration.");
    }

    ClassMemberCommonData *cData = commonData->result();
    return new ParseSuccess<DataField*>(
            new DataField(cData->name, cData->type, cData->publicness,
                          cData->staticness, cData->finalness));
}

/* Try to read a method definition. */
ParseResult<MethodDefn*>* MethodDefn::tryParse(TokenBuffer& tokenBuffer)
{
    // COMMON_DATA `(` METHOD_PARAMS `)` STMT_BLOCK
    int tokenBufferStartState = tokenBuffer.getCurrentState();
    ParseResult<ClassMemberCommonData*> *commonData = 
                                        parseClassMemberCommon(tokenBuffer);

    if (!tokenBuffer.readLexemes({"("})) {
        // Not a method definition. Reset the token buffer state and return
        // failure.
        tokenBuffer.setState(tokenBufferStartState);
        return new ParseFail<MethodDefn*>(
                "Method definition not found");
    }

    // Read Method params.
    ParseResult<MethodParams*> *params = MethodParams::tryParse(tokenBuffer);
    if (!tokenBuffer.readLexemes({")"})) {
        throw SyntaxError(tokenBuffer.line(),
                "Closing paren not found after method params.");
    }

    ParseResult<StatementBlock*> *stmtBlock = StatementBlock::tryParse(
                                                tokenBuffer);

    ClassMemberCommonData *cData = commonData->result();
    return new ParseSuccess<MethodDefn*>(
            new MethodDefn(cData->name, cData->type,
                           cData->publicness, cData->staticness,
                           cData->finalness,
                           params->result(), stmtBlock->result()));
}

/* Try to read a class definition. */
ParseResult<Class*>* Class::tryParse(TokenBuffer& tokenBuffer)
{
    bool publicness = true;

    if (tokenBuffer.readLexemes({"private", "class"})) {
        publicness = false;
    } else if (tokenBuffer.readLexemes({"public", "class"})) {
    } else if (tokenBuffer.readLexemes({"class"})) {
    } else {
        return new ParseFail<Class*>("Not a class definition.");
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

    std::vector<MethodDefn*> methodDefns;
    std::vector<DataField*> dataFields;

    while (true) {
        if (tokenBuffer.readLexemes({"}"})) {
            // Class definition ends here.
            break;
        }
    }

    return new ParseSuccess<Class*>(
            new Class(dataFields, methodDefns, publicness,
                      classNameToken.lexeme));
}
