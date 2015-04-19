#include "common.h"


/**
 * Tokens are the syntactic units of a program. These can be variables,
 * keywords, string and numeric literals etc..
 */
enum class TokenType
{
    IDENTIFIER = 0,
    KEYWORD,
    NUMBER,
    STRING_LITERAL,
    UNARY_OPERATOR,
    BINARY_OPERATOR,
    SEMI_COLON,
};


/**
 * Token returned by the lexer to the parser.
 */
class Token
{
public:
    Token(TokenType type, std::string& lexeme);
};


/**
 * Lexer breaks the source code into a series of tokens to be processed by the
 * Parser. Parser reads these tokens and constructs an AST.
 */
class Lexer
{
public:
    Lexer(const std::string& source_file);

    /**
     * Read and return the next lexical token.
     */
    Token nextToken();
};
