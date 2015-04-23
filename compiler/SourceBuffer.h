#include "headers.h"

/**
 * A low level buffer used by the lexer. It provides a stream of syntactically
 * significant characters(i.e. ignores whitespace and comments), can push
 * characters back in case of parse failures, can consider whitespace when
 * needed etc..
 */
class SourceBuffer
{
public:
    SourceBuffer(const std::string& sourceFile): inputStream(sourceFile),
        buffer()
    {
        curReadPos = 0;
    }

    ~SourceBuffer()
    {
        // Close the input stream.
        inputStream.close();
    }

    /* Return the next character in the buffer. */
    char getChar();

    /* Push a character back into the buffer, in case of a parse failure.*/
    bool pushCharBack(char c);

private:
    std::ifstream inputStream;

    /* Internal buffer used. */
    std::string buffer;

    /* Current read position in the buffer.*/
    int curReadPos;

    /* Current line number in the source file. */
    int lineNo;

    /* Read fresh data from the file into the buffer.*/
    void readIntoBuffer();
};
