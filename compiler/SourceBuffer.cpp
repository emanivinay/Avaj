#include "SourceBuffer.h"

/**
 * Return the next character in the buffer. 
 */
char SourceBuffer::getChar()
{
    if (curPosInBuffer >= BUFFER_SIZE) {
        readIntoBuffer();
        curPosInBuffer = 0;
    }

    char ret = buffer[curPosInBuffer];
    if (EOF == ret) {
        return EOF;
    }

    curPosInBuffer++;
    return ret;
}

void SourceBuffer::readIntoBuffer()
{
    //TODO(Vinay) :- Implement this.
    std::string line;
    inputStream.getline(line);
}
