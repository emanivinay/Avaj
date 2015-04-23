#include "SourceBuffer.h"
#include "SyntaxError.h"

/**
 * Return the next character in the buffer. 
 */
char SourceBuffer::getChar()
{
    if (curReadPos >= (int)buffer.size()) {
        readIntoBuffer();
    }

    if (buffer.empty())
        return EOF;
    return buffer[curReadPos++];
}

void SourceBuffer::readIntoBuffer()
{
    curReadPos = 0;
    if (inputStream.eof()) {
        // End of input.
        buffer = "";
        return;
    }

    // Read to the end of the current line. Strip the comments. If an open
    // string literal exists, throw an exception.
    getline(inputStream, buffer);

    bool inStringLiteral = false;
    for (auto c: buffer) {
        if (c == '"')
            inStringLiteral = !inStringLiteral;
    }

    if (inStringLiteral) {
        // TODO(Vinay) :- Define a good exception type for this case.
        throw 0;
    }
}

bool SourceBuffer::pushCharBack(char c)
{
    // TODO(Vinay) :- Implement this.
    return false;
}
