#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

/* Common exceptions used throughout the project are defined here.*/
#include "headers.h"

/* Badly formatted input file is encountered during compilation.*/
class MalformedFileInput: public std::runtime_error
{
public:
    MalformedFileInput(const std::string& what):
        std::runtime_error(what) {}
};
#endif
