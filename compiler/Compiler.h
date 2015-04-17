#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <algorithm>

#include "Syntax.h"
#include "Core.h"

/**
 * Compilation succeeds on well formed source files and SUCCESS is returned.
 * Otherwise, FAILURE is returned.
 */
enum class FileParseStatus
{
    SUCCESS = 0,
    FAILURE,
};

/**
 * Avaj compiler reads the source code and compiles into an intermediate
 * representation.
 */
class Compiler 
{
private:
    /**
     * Parse a source file into a list of data types.
     */
    static std::pair<FileParseStatus, std::vector<Type> > parseCode(
            const std::string& filepath);

public:
    static void parseAndGenIR(const std::string& sourceFile,
                              const std::string& outFile);
};


class Code
{
private:
    std::vector<Statement> statements;
};
