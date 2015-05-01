int main(int argc, char **argv)
{
    Lexer lexer(argv[1]);
    while (true) {
        Token tok = lexer.getNextToken();
        if (tok.type == TokenType::END_OF_FILE)
            break;

        std::cout << tok.lexeme << std::endl;
    }

    return 0;
}
