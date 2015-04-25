#include "SyntaxError.h"
#include "SourceBuffer.h"
#include "Lexer.h"

Lexer::Lexer(const std::string& sourceFile):
    sourceBuffer(sourceFile)
{
}

Token Lexer::getNextToken()
{
    CharUnit chrUnit = sourceBuffer.getCharUnit();

    if (chrUnit.chr == EOF) {
        return Token(TokenType::END_OF_FILE, "");
    }
    else if (chrUnit.chr == ';') {
        return Token(TokenType::SEMI_COLON, ";");
    }
    else if (isBraceOrBracket(chrUnit)) {
        char c = chrUnit.chr;
        TokenType tokenType = c == '{' ? TokenType::LEFT_BRACE :
                              c == '}' ? TokenType::RIGHT_BRACE :
                              c == '[' ? TokenType::LEFT_SQUARE_BKT :
                              c == ']' ? TokenType::RIGHT_SQUARE_BKT :
                              c == '(' ? TokenType::LEFT_BRACKET :
                              TokenType::RIGHT_BRACKET;

        return Token(tokenType, std::string(1, c));
    }
    else if (isspace(chrUnit.chr)) {
        // Ignore the whitespace.
        return getNextToken();
    }
    else if ('"' == chrUnit.chr) {
        // Read the whole string literal and return it.
        std::ostringstream out;
        while (true) {
            CharUnit tmp = sourceBuffer.getCharUnit();
            if (tmp.chr == EOF) {
                throw SyntaxError(tmp.lineNo, "Incomplete string literal");
            }
            else if (tmp.chr == '"') {
                break;
            }
            out << tmp.chr;
        }

        return Token(TokenType::STRING_LITERAL, out.str());
    }
    else if (startsId(chrUnit)) {
        // Read an identifier.
        sourceBuffer.pushCharBack(chrUnit);
        return readIdentifier();
    }
    // All numerical tokens must start with a digit.
    else if (isdigit(chrUnit.chr)) {
        sourceBuffer.pushCharBack(chrUnit);
        return readNumber();
    }
    else {
        return Token(TokenType::FAILURE, std::string(1, chrUnit.chr));
    }
}

Token Lexer::readNumber()
{
    // Numbers are of the form -> [0-9]+(.[0-9]*)?(E[0-9]+)?)
    std::ostringstream out;
    out << readDigitString();

    CharUnit unit = sourceBuffer.getCharUnit();
    if (unit.chr == '.') {
        out << ".";
        out << readDigitString();
    }
    else if (unit.chr == 'E' || unit.chr == 'e') {
        out << unit.chr;
        out << readDigitString();
    } else {
        sourceBuffer.pushCharBack(unit);
    }

    return Token(TokenType::NUMBER, out.str());
}

Token Lexer::readIdentifier()
{
}
