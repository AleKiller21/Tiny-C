#include "array_expression.h"

string array_expression::to_string()
{
    return expr->to_string() + "[" + index->to_string() + "]" + " ";
}