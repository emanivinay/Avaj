#ifndef _LEXER_H_
#define _LEXER_H_

#include "headers.h"
#include "SourceBuffer.h"

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

    COMMA,
    PERIOD,
    WHITESPACE,

    // Braces, brackets, square brackets.
    LEFT_BRACE,
    RIGHT_BRACE,

    LEFT_BRACKET,
    RIGHT_BRACKET,

    LEFT_SQUARE_BKT,
    RIGHT_SQUARE_BKT,

    // Quotes
    SINGLE_QUOTE,
    DOUBLE_QUOTE,

    // Variable names, reserved keywords.
    IDENTIFIER,
    KEYWORD,

    // Field reference.
    FIELD_REF,

    // Literal tokens.
    INTEGER,
    FLOATING,
    EXPONENT, // Number in scientific notation.
    STRING_LITERAL,
    CHAR_LITERAL,

    // Arithmetic operators.
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    MODULO,

    // Boolean operators.
    AND,
    OR,
    NOT,

    // Bitwise operator
    BITWISE_AND,
    BITWISE_OR,
    BITWISE_XOR, // a ^ b
    BITWISE_NOT,

    // Comparison operators.
    EQ,
    NE,
    LT,
    LE,
    GE,
    GT,

    // Assignment and its variations.
    ASSIGNMENT, // a = b.
    PLUS_EQ, // a += b
    MINUS_EQ, // a -= b
    MULT_EQ, // a *= b
    DIV_EQ, // a /= b
    MOD_EQ, // a %= b
    OR_EQ, // a ||= b
    BITWISE_OR_EQ, // a |= b
    AND_EQ, // a &&= b
    BITWISE_AND_EQ, // a &= b
    BITWISE_XOR_EQ, // a ^= b 
    BITWISE_NOT_EQ, // a ~= b

    // Increment and decrement operators.
    INCREMENT,
    DECREMENT,

    END_OF_FILE,

    FAILURE,
};

/* List of keywords - Each of these tokens have special significance.*/
static const std::set<std::string> KEYWORDS = {
    "if", "else", "while", "for", "class", "break",
    "continue", "final", "private", "public", "static",
    "import", "new", "return", "this", "void"
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

    /* Starting line and column numbers. */
    const int lineNo;
    const int columnNo;

    Token(TokenType _type, const std::string& _lexeme, int _line, int _col):
        type(_type), lexeme(_lexeme), lineNo(_line), columnNo(_col)
    {
    }

    bool operator ==(const Token& tok)
    {
        return type == tok.type and lexeme == tok.lexeme
            and lineNo == tok.lineNo and columnNo == tok.columnNo;
    }

    bool operator !=(const Token& tok) {return ! (*this == tok);}
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

    Token _Token(TokenType type, std::string lexeme)
    {
        return Token(type, lexeme, sourceBuffer.line(), sourceBuffer.column());
    }

    /* Helper methods. */
    static bool isBraceOrBracket(const CharUnit& c)
    {
        static const std::string bString = "{}[]()";
        return bString.find(c.chr) != std::string::npos;
    }

    static bool alpha_(const CharUnit& c)
    {
        return isalpha(c.chr) || c.chr == '_';
    }

    /* Read a string of digits, not separated by whitespace. */
    std::string readDigitString()
    {
        std::ostringstream out;
        while (true) {
            CharUnit unit = sourceBuffer.getCharUnit();
            if (!isdigit(unit.chr)) {
                sourceBuffer.pushCharBack(unit);
                break;
            }

            out << unit.chr;
        }

        return out.str();
    }

    /* Read a string of digits, possibly prefixed with a +/- sign. */
    std::string readSignedDigitString()
    {
        std::ostringstream out;

        CharUnit unit = sourceBuffer.getCharUnit();
        if (unit.chr != '+' and unit.chr != '-' and !isdigit(unit.chr)) {
            sourceBuffer.pushCharBack(unit);
            return "";
        }
        out << unit.chr;
        out << readDigitString();
        return out.str();
    }

    bool readLiteral(const std::string& literal)
    {
        // Try to read the literal string as is.
        std::stack<CharUnit> cStack;
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

    std::string readStringLiteral(char endChar = '"')
    {
        std::ostringstream out;
        char prev = endChar;
        while (true) {
            CharUnit unit = sourceBuffer.getCharUnit();
            if (unit.chr == EOF) {
                throw SyntaxError(sourceBuffer.line(), 
                        "Incomplete string literal. Premature end of file.");
            }
            if (unit.chr == endChar and prev != '/') {
                // String literal ends.
                return out.str();
            }
            out << unit.chr;
            prev = unit.chr;
        }
    }
};
#endif
