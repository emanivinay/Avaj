#ifndef _CLASS_H_
#define _CLASS_H_

#include "headers.h"
#include "Method.h"
#include "Field.h"

/**
 * A syntax unit for classes.
 */
class Class
{
public:
    Class(const std::vector<Field>& fields, 
          const std::vector<Method>& _methods,
          const std::string& _name,
          bool _public):
        dataFields(fields), methods(_methods), publicness(_public),
            name(_name){}

    const std::string name;
    const bool publicness;

    const std::vector<Field> dataFields;
    const std::vector<Method> methods;
};
#endif
