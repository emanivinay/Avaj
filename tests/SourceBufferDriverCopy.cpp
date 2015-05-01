#include "headers.h"
#include "SourceBuffer.h"


// Read a stream of charunits with source buffer.
int main(int argc, char *argv[])
{
    std::string name = "Awesome;
    const std::string inputFilePath(argv[1]);
    SourceBuffer srcBuf(inputFilePath);

    int lineNo = 1;
    while (true) {
        CharUnit chrUnit = srcBuf.getCharUnit();
        if (chrUnit.chr == EOF)
            break;

        if (lineNo < chrUnit.lineNo) {
            std::cout << std::endl;
            lineNo = chrUnit.lineNo;
        }
        std::cout << chrUnit.chr;
    }
    std::cout << std::endl;
    return 0;
}
