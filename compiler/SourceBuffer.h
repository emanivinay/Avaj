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
    SourceBuffer(const std::string& sourceFile): inputStream(sourceFile)
    {
    }

    ~SourceBuffer()
    {
        // Close the input stream.
        inputStream.close();
    }

    /* Return the next character in the buffer. */
    char getChar();

private:
    std::ifstream inputStream;

    /* Size of the internal buffer.*/
    static const int BUFFER_SIZE = 8192;

    char buffer[BUFFER_SIZE + 1];
    int curPosInBuffer;

    /* Read fresh data from the file into the buffer.*/
    void readIntoBuffer();
};
