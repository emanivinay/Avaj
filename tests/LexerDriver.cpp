#include "SyntaxError.h"
#include "SourceBuffer.h"
#include "Lexer.h"

/* Read and print all the tokens. */
int main(int argc, char **argv)
{
    Lexer lexer(argv[1]);
    while (true) {
        try {
        Token tok = lexer.getNextToken();
        if (tok.type == TokenType::END_OF_FILE)
            break;

        if (tok.type == TokenType::FAILURE) {
            std::cout << "Failed in the line " << tok.lineNo << " at the column"
                << " " << tok.columnNo << " with the string "
                << tok.lexeme << std::endl;
            break;
        }

        std::cout << (int)tok.type << " " << tok.lexeme << std::endl;
        } catch (SyntaxError err) {
            std::cout << "syntax error thrown" << std::endl;
        }
    }
    std::cout << std::endl;

    return 0;
}
