#ifndef _HLREADER_H_
#define _HLREADER_H_

#include "headers.h"

/* A buffered tokenizer for .ir files for parsing core datatype specs.*/
class HLReader
{
private:
    /* Buffer for storing parsed tokens. A queue is better for 
     * performance, though it only contains 1-3 tokens max at any time.
     */
    std::vector<std::string> tokenBuffer;

    /* Read the next token from the buffer. If the buffer is empty, read
     * from the input source, tokenize it, add to the buffer and return
     * the first one.
     */
    std::string getNextToken();

    // Underlying input source.
    std::ifstream& source;

    // Split the word into valid HLIR tokens.
    static std::vector<std::string> tokenize(const std::string& word);

public:
    HLReader(std::ifstream& source);

    /* Returns true if the input source is complete and no more tokens to
     * be read or false if there are still more tokens.
     */
    bool eof();

    /* Either parse the given token successfully or throw an exception
     * otherwise.
     */
    void parseOrThrow(const std::string& strToken);

    /* Push the token back into buffer in case of parse failure and must be
     * retried.
     */
    void read_back(const std::string& strToken);

    /* Read a token of the template type. BEWARE, >> can throw an
     * exception.
     */
    template<class T>
    T read()
    {
        std::string next = getNextToken();
        std::istringstream istr(next);
        T ret;
        istr >> ret;
        return ret;
    }
};
#endif
