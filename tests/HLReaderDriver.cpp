#include "headers.h"
#include "HLReader.h"

int main(int argc, char **argv)
{
    std::ifstream file(argv[1]);
    HLReader reader(file);

    while (true) {
        std::string token = reader.read<std::string>();
        if (token.empty())
            break;
        std::cout << "Token read is " << token << std::endl;
    }
    return 0;
}
