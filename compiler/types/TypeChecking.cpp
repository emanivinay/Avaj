#include "headers.h"
#include "BuiltinType.h"
#include "UserDefinedType.h"
#include "TypeChecking.h"

// Hard coded builtin type spec file path.
// TODO(vinay) - In future, refactor this to use a value specified in 
// a configuration file.
static const std::string BUILTIN_TYPE_REL_LOC = 
                            "compiler/types/builtins/new.ir";

/* Type checking algorithm. 
 */
TypeCheckResult checkTypes(const AST *ast)
{
    std::ifstream fin(BUILTIN_TYPE_REL_LOC);
    std::vector<BuiltinType*> builtins = BuiltinType::readBuiltins(fin);

    std::vector<UserDefinedType*> userTypes;
    for (auto cls: ast->classes)
        userTypes.push_back(UserDefinedType::readType(cls));

    // Now, we have the list of builtins and user defined types.
    // TODO(vinay) - Complete checkTypes();
    return TypeCheckResult::FAILURE;
}
