#ifndef _CLASS_H_
#define _CLASS_H_

#include "headers.h"
#include "SyntaxError.h"
#include "ParseResult.h"
#include "ParserUtils.h"
#include "TokenBuffer.h"

/* A data field of a class.*/
class DataField
{
public:

    DataField(const std::string& _name, const std::string& _typeName,
              bool _publicness, bool _staticness, bool _finality):
        name(_name), typeName(_typeName), publicness(_publicness),
        staticness(_staticness), finality(_finality) {}

    const std::string name;
    const std::string typeName;
    const bool publicness;
    const bool staticness;
    const bool finality;

    std::string repr() const
    {
        std::ostringstream out;
        if (publicness)
            out << "public ";
        if (staticness)
            out << "static ";
        if (finality)
            out << "final ";
        out << typeName << " ";
        out << name;
        return out.str();
    }

    static ParseResult<DataField>* tryParse(TokenBuffer& tokenBuffer);
};

/* A method definition for a class. */
class MethodDefn
{
public:

    MethodDefn(const std::string& _name, const std::string& _returnTypeName,
              bool _publicness, bool _staticness, bool _finality):
        name(_name), returnTypeName(_returnTypeName), publicness(_publicness),
        staticness(_staticness), finality(_finality) {}

    const std::string name;
    const std::string returnTypeName;
    const bool publicness;
    const bool staticness;
    const bool finality;

    static ParseResult<MethodDefn>* tryParse(TokenBuffer& tokenBuffer);
};

/**
 * A syntax unit for classes.
 */
class Class
{
public:
    Class(const std::vector<DataField>& fields, 
          const std::vector<MethodDefn>& _methods,
          bool _public,
          const std::string& _name):
        dataFields(fields), methods(_methods), publicness(_public),
            name(_name){}

    const std::vector<DataField> dataFields;
    const std::vector<MethodDefn> methods;
    const bool publicness;
    const std::string name;

    static ParseResult<Class>* tryParse(TokenBuffer& tokenBuffer);
};
#endif
