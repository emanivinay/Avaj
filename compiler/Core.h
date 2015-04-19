#include <vector>

class Code;
class Statement;
class Method;
class DataField;

// C
class Type
{
private:
    std::vector<Method> methods;
    std::vector<DataField> dataFields;

public:
    Code genCode()
    {
        throw;
    }
};


class Method
{
private:
    std::vector<const Type&> argTypes;
    Code methodBody;
};
