#include "HLReader.h"

HLReader::HLReader(std::ifstream& _source):
    tokenBuffer(), source(_source)
{
}

std::string HLReader::getNextToken()
{
    if (tokenBuffer.empty()) {
        // Read more input from the source.
        std::string str;
        if (!(source >> str)) {
            return ""; // Empty string marks end of input.
        }

        // Tokenize the word and append them to the buffer.
        std::vector<std::string> tokens = tokenize(str);
        tokenBuffer.insert(tokenBuffer.end(),
                           tokens.begin(), tokens.end());
    }

    std::string ret = tokenBuffer[0];
    tokenBuffer.erase(tokenBuffer.begin());
    return ret;
}

std::vector<std::string> HLReader::tokenize(const std::string& word)
{
    std::vector<std::string> ret;
    // Valid hlir tokens are class, {, }, size, :, ;, <int>, method,
    // <string>, (, )
    const int n = (int)word.size();
    const std::vector<std::string> keywords {"class", "{", "}", "size",
            ":", ";", "method", "(", ")"};
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
        while (word[i] != '{' && word[i] != ':' && word[i] != ';') {
            i++;
        }

        ret.push_back(word.substr(start, i - start));
    }

    if (i != n)
        throw std::exception();
    return ret;
}

void HLReader::expectOrThrow(const std::string& strToken)
{
    std::string next = read<std::string>();
    if (next.empty() || next != strToken)
        throw std::exception();
}
