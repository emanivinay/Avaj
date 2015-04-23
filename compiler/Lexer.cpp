#include "SyntaxError.h"
#include "SourceBuffer.h"
#include "Lexer.h"

Lexer::Lexer(const std::string& sourceFile):
    sourceBuffer(sourceFile)
{
}

static bool isBraceOrBracket(const CharUnit& c)
{
    static const std::string bString = "{}[]()";
    return bString.find(c.chr) != std::string::npos;
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
                              c == ')' ? TokenType::RIGHT_BRACKET :
                              TokenType::FAILURE;

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
    else {
        return Token(TokenType::FAILURE, "");
    }
}
