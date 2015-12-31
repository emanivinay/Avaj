#include "exceptions.h"
#include "HLReader.h"

HLReader::HLReader(std::ifstream& _source):
    tokenBuffer(), source(_source)
{
}

bool HLReader::eof()
{
    if (!tokenBuffer.empty())
        return false;
    std::string str;
    if (!(source >> str)) {
        return true;
    }

    // Read more words from the source and tokenize them + queue them in
    // the buffer.
    std::vector<std::string> tokens = tokenize(str);
    tokenBuffer.insert(tokenBuffer.end(),
                       tokens.begin(), tokens.end());
    return false;
}

std::string HLReader::getNextToken()
{
    // No more tokens in the buffer nor any more words to be read from
    // the source.
    if (eof())
        return "";

    // Buffer is not empty. Pop the first token.
    std::string ret = tokenBuffer[0];
    tokenBuffer.erase(tokenBuffer.begin());
    return ret;
}

void HLReader::read_back(const std::string& strToken)
{
    tokenBuffer.insert(tokenBuffer.begin(), strToken);
}

std::vector<std::string> HLReader::tokenize(const std::string& word)
{
    std::vector<std::string> ret;
    // Valid hlir tokens are class, {, }, size, :, ;, <int>, method,
    // <string>, (, )
    const int n = (int)word.size();
    const std::vector<std::string> keywords {"class", "{", "}", "size",
            ":", ";", "methods", "(", ")"};
    int i;
    for (i = 0;i < n; ) {
        bool tokenFound = false;
        for (auto& kwd: keywords) {
            if (i + (int)kwd.size() <= n
                    && word.substr(i, (int)kwd.size()) == kwd) {
                i += (int)kwd.size();
                ret.push_back(kwd);
                tokenFound = true;
                break;
            }
        }

        if (tokenFound)
            continue;
        if (isdigit(word[i])) {
            tokenFound = true;
            int start = i;
            while (i < n && isdigit(word[i])) {
                i++;
            }
            ret.push_back(word.substr(start, i - start));
            continue;
        }

        int start = i;
        while (i < n && (word[i] != '{'
                && word[i] != ':' && word[i] != ';')) {
            i++;
        }

        ret.push_back(word.substr(start, i - start));
    }

    if (i != n)
        throw MalformedFileInput("Invalid word in the class spec.");
    return ret;
}

void HLReader::parseOrThrow(const std::string& strToken)
{
    std::string next = read<std::string>();
    if (next.empty() || next != strToken)
        throw MalformedFileInput("Read an unexpected token.");
}
