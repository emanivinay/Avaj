#pragma once

/** This module implements the type checking algorithm.
 */
#include "AST.h"
#include "Type.h"

/* Result of the type checking.*/
enum class TypeCheckResult
{
    SUCCESS = 0,
    FAILURE, // Various failure types can be added further.
    UNKNOWN,
};

/* Perform type checking on a single module.*/
TypeCheckResult checkTypes(const AST *ast);
