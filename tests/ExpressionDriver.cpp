#include "headers.h"
#include "TokenBuffer.h"
#include "Expression.h"

using namespace std;

/**
 * Test consists of an input file with a bunch of expressions each followed by
 * a semi-colon. Expressions may be correct or ill-formed and this test shall
 * correctly identify both the cases and report accordingly.
 */
int main(int argc, char **argv)
{
    TokenBuffer tokenBuffer(argv[1]);

    for (;;) {
        try {
            ParseResult<Expression*> *parsedExpr = parseExpr(tokenBuffer);
            cout << "After parseExpr call" << endl;
            if (parsedExpr->isParseSuccessful()) {
                cout << "Parse successful" << endl;
                cout << "Parsed expression is " << endl;
                cout << parsedExpr->result()->repr() << endl;
                tokenBuffer.getCurrentToken();
            }
            else {
                cout << "Parse failed" << endl;
                break;
            }
        } catch (SyntaxError& err) {
            cout << "Bad expression syntax" << endl;
            cout << err.what() << endl;
            break;
        } catch (std::logic_error& logic_err) {
            cout << "Error in Expression code" << endl;
            cout << logic_err.what() << endl;
            break;
        }
    }

    return 0;
}
