#include "SourceBuffer.h"
#include "SyntaxError.h"

/**
 * Return the next character in the buffer. 
 */
CharUnit SourceBuffer::getCharUnit()
{
    while (curReadPos >= numChars && !inputStream.eof()) {
        readIntoBuffer();
    }

    if (curReadPos >= numChars && inputStream.eof())
        return CharUnit(EOF, 0, 0);

    curReadPos++;
    return CharUnit(buffer[curReadPos - 1], lineNo, columns[curReadPos - 1]);
}

void SourceBuffer::readIntoBuffer()
{
    // Reset the read position and buffer size.
    curReadPos = 0;
    numChars = 0;

    if (inputStream.eof()) {
        // End of input.
        return;
    }

    // Read to the end of the current line. Strip the comment part. If an open
    // string literal exists, throw an exception.
    std::string buf;
    getline(inputStream, buf);
    lineNo++;

    numChars = (int)buf.size();
    for (int i = 0;i <= numChars; ++i) {
        buffer[i] = i < numChars ? buf[i] : '\n';
        columns[i] = i + 1;
    }

    int trailingSlashes = 0, stringLiteral = 0;
    for (int i = 0;i <= numChars; ++i) {
        char c = buffer[i];
        trailingSlashes = c == '/' ? (trailingSlashes + 1) : 0;

        if (c == '"')
            stringLiteral = !stringLiteral;
        
        if (!stringLiteral && trailingSlashes == 2) {
            // Comment start.
            numChars = i - 1;
            break;
        }
    }
    numChars++;

    if (stringLiteral) {
        throw SyntaxError(lineNo, "Incomplete string literal");
    }
}

bool SourceBuffer::pushCharBack(CharUnit c)
{
    if (curReadPos > 0) {
        curReadPos--;
        buffer[curReadPos] = c.chr;
        columns[curReadPos] = c.columnNo;
        lineNo = c.lineNo;
        return true;
    }

    // Freshly read buffer.
    for (int i = numChars - 1;i >= 0; i--) {
        buffer[i + 1] = buffer[i];
        columns[i + 1] = columns[i];
    }

    lineNo = c.lineNo;
    curReadPos = 0;
    numChars++;
    return true;
}
