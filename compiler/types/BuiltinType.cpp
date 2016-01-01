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
    std::vector<TypeMethod> methods;
    
    // Read the list of method declarations.
    while (true) {
        // read <METHOD_NAME> ":"
        std::string methodName = reader.read<std::string>();
        if (methodName == "}") {
            // End of type spec.
            break;
        } else if (methodName == ";") {
            // End of all methods. Just read "}"
            reader.parseOrThrow("}");
            break;
        }
        else if (methodName.empty()) {
            throw MalformedFileInput(
                    "Unexpected end of file");
        }
        reader.parseOrThrow(":");

        while (true) {
            // read <RETURN_TYPE> <ARG_TYPE> ";"
            std::string retType = reader.read<std::string>();
            if (retType == "}") {
                reader.read_back("}");
                break;
            }
            else if (retType.empty()) {
                throw MalformedFileInput(
                        "Unexpected end of file reading return type.");
            }

            std::string argType = reader.read<std::string>();
            if (argType == ":") {
                // This is a new method, break out of the inner loop.
                reader.read_back(":");
                reader.read_back(retType);
                break;
            }
            else if (argType.empty()) {
                throw MalformedFileInput(
                        "Unexpected end of file reading argument type.");
            }

            reader.parseOrThrow(";");
            methods.push_back(Method(methodName, retType, {argType}));
        }
    }

    return new BuiltinType(name, size, methods);
}
