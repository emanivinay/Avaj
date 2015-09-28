#ifndef _PRIMITIVES_H_
#define _PRIMITIVES_H_

#include "headers.h"

/* Primitive datatypes of the language.*/
enum class PrimitiveType
{
    SHORT = 0, // 2-byte signed integer.
    INT, // 4-byte signed integer.
    LONG, // 8-byte signed integer.
    FLOAT, // Single precision floating point value.
    DOUBLE, // Double precision floating point.
    CHAR, // Unicode character.
    REF, // A reference variable, used to hold references to other objects.
    INVALID,
};

/**
 * Get the PrimitiveType enum value from the type name. If the input type
 * is not a primitive, return INVALID.
 */
PrimitiveType getPrimitiveType(const std::string& typeName);

/**
 * Return the size of a value of the given type, or -1 if the type is not 
 * one.
 */
int getPrimitiveTypeSize(const std::string& typeName);
#endif
