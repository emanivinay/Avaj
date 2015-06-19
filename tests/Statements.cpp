#include "headers.h"
#include "TokenBuffer.h"
#include "Statement.h"

using namespace std;

/**
 * Test consists of a series of statements terminated by semi-colons. Both 
 * legal and illegal statements must be reported correctly.
 */
int main(int argc, char **argv)
{
    TokenBuffer tokenBuffer(argv[1]);

    while (true) {
        try {
            ParseResult<Statement*> *stmt = parseStmt(tokenBuffer);
            stmt->result();
        } catch (SyntaxError& err) {
            cout << "Error reading a statement" << endl;
            cout << err.what() << endl;
            break;
        }
    }

    return 0;
}
