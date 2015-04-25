#include "headers.h"

/**
 * Tokens are the syntactic units of a program. These can be identifiers,
 * keywords, string and numeric literals etc..
 */
enum class TokenType
{
    // Statement separator.
    SEMI_COLON = 0,

    // Ternary operator tokens.
    QUESTION_MARK,
    COLON,

    // Braces, brackets, square brackets.
    LEFT_BRACE,
    RIGHT_BRACE,

    LEFT_BRACKET,
    RIGHT_BRACKET,

    LEFT_SQUARE_BKT,
    RIGHT_SQUARE_BKT,

    // Variable names, reserved keywords.
    IDENTIFIER,
    KEYWORD,

    // Literal tokens.
    NUMBER,
    STRING_LITERAL,

    // Unary and binary operators.
    UNARY_OPERATOR,
    BINARY_OPERATOR,

    END_OF_FILE,

    FAILURE,
};


/**
 * Token returned by the lexer to the parser.
 */
class Token
{
public:
    /* Type of this token. */
    const TokenType type;

    /* The matched string. */
    const std::string lexeme;

    // TODO(Vinay) :- Add line and column numbers for better error reporting.

    Token(TokenType _type, const std::string& _lexeme):
        type(_type), lexeme(_lexeme)
    {
    }
};


/**
 * Lexer breaks the source code into a series of tokens to be processed by the
 * Parser. Parser reads these tokens and constructs an AST. This is a
 * handwritten lexer.
 */
class Lexer
{
public:
    Lexer(const std::string& sourceFile);

    /**
     * Read and return the next lexical token.
     */
    Token getNextToken();

private:
    SourceBuffer sourceBuffer;

    /* Helper methods to read specific tokens. */
    Token readIdentifier();
    Token readNumber();

    /* Helper methods. */
    static bool isBraceOrBracket(const CharUnit& c)
    {
        static const std::string bString = "{}[]()";
        return bString.find(c.chr) != std::string::npos;
    }

    static bool startsId(const CharUnit& c)
    {
        return isalpha(c.chr) || c.chr == '_';
    }

    std::string readDigitString()
    {
        return "2";
    }

    bool readLiteral(const std::string& literal)
    {
        // Try to read the literal string as is.
        stack<CharUnit> cStack;
        for (auto c : literal) {
            CharUnit unit = sourceBuffer.getCharUnit();
            if (unit.chr != c) {
                for (;!cStack.empty();cStack.pop()) {
                    sourceBuffer.pushCharBack(cStack.top());
                }
                return false;
            }

            cStack.push(unit);
        }

        return true;
    }
};
