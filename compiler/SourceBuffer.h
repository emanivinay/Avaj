#pragma once

#include "headers.h"

/**
 * CharUnit consists of a single source character, its line number in source
 * text, column no. within the line. It is a single unit of data returned to
 * the Lexer.
 */
class CharUnit
{
public:
    const char chr;
    const int lineNo;
    const int columnNo;

    CharUnit(char c, int line, int col):
        chr(c), lineNo(line), columnNo(col)
    {}
};

/**
 * A low level buffer used by the lexer. It strips comments from the code and
 * can push characters back in case of parse failures, can consider whitespace
 * when needed etc..
 */
class SourceBuffer
{
public:
    SourceBuffer(const std::string& sourceFile): inputStream(sourceFile),
        buffer()
    {
        numChars = 0;
        curReadPos = 0;
    }

    ~SourceBuffer()
    {
        // Close the input stream.
        inputStream.close();
    }

    /* Return the next character in the buffer. */
    CharUnit getCharUnit();

    /* Push a character back into the buffer, in case of a parse failure.*/
    bool pushCharBack(CharUnit c);

    /* Return the line no. in the source file being currently read.*/
    int line() const {return lineNo;};

    /* Return the column of the current character being read. */
    int column() const 
    {
        if (curReadPos >= numChars)
            return 0;
        return columns[curReadPos];
    };

private:
    std::ifstream inputStream;

    /* Current read position in the buffer.*/
    int curReadPos;

    /* Current line number in the source file. */
    int lineNo;

    static const int MAX_LINE_SIZE = 8192;

    /**
     * Column numbers of each char currently in the buffer. A negative value in
     * the array denotes the end of the buffer.
     */
    int columns[MAX_LINE_SIZE + 1];

    /* Buffer. */
    char buffer[MAX_LINE_SIZE + 1];

    /* Number of characters in the buffer. */
    int numChars;

    /* Read fresh data from input file and strip the comments. */
    void readIntoBuffer();
};
