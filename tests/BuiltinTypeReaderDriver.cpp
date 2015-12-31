#include "headers.h"
#include "exceptions.h"
#include "BuiltinType.h"

int main(int argc, char **argv)
{
    std::ifstream fin(argv[1]);
    try {
        while (true) {
            BuiltinType *type = BuiltinType::readType(fin);
            if (nullptr == type) {
                // Successfully read all the types in the file.
                break;
            }
            std::cout << "Type read with name " << type->name << std::endl;
        }
    } catch(MalformedFileInput& e) {
        std::cout << e.what() << std::endl;
    }

    fin.close();
    return 0;
}
