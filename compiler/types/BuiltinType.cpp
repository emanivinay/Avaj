#include "exceptions.h"
#include "BuiltinType.h"
#include "HLReader.h"

/* Read BuiltinType definition from a high level representation.
 */
BuiltinType *BuiltinType::readType(std::ifstream& source)
{
    HLReader reader(source);
    if (reader.eof()) {
        // No more type specs present in the ir file. Return nullptr.
        return nullptr;
    }
    reader.parseOrThrow("class");
    std::string name = reader.read<std::string>();
    reader.parseOrThrow("{");
    reader.parseOrThrow("size");
    reader.parseOrThrow(":");
    int size = reader.read<int>();
    reader.parseOrThrow(";");
    reader.parseOrThrow("methods");
    reader.parseOrThrow(":");
    std::vector<Method> methods;
    while (true) {
        std::string mthd_name = reader.read<std::string>();
        if (mthd_name.empty()) {
            throw MalformedFileInput(
                    "Unexpected end to builtin class spec.");
        } else if (mthd_name == "}") {
            // End of the class spec.
            break;
        } else {
            // Read ':'.
            reader.parseOrThrow(":");
            while (true) {
                std::string retType = reader.read<std::string>();
                if (retType.empty())
                    throw MalformedFileInput(
                        "Unexpected end to builtin class spec.");
                std::string argType = reader.read<std::string>();
                if (argType.empty())
                    throw MalformedFileInput(
                        "Unexpected end to builtin class spec.");
                else if (argType == ":") {
                    // New method starts.
                    reader.read_back(retType);
                    reader.read_back(":");
                    break;
                } else {
                    reader.parseOrThrow(";");
                    methods.push_back(Method(mthd_name, retType,
                                            {argType}));
                }
            }
        }
    }

    return new BuiltinType(name, size, methods);
}

std::vector<Method> BuiltinType::getMethods() const
{
    return methods;
}
