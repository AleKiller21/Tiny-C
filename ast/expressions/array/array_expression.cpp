#include "array_expression.h"

array_expression::array_expression(expression* expr, expression* index)
{
    this->expr = expr;
    this->index = index;
}

string array_expression::to_string()
{
    return expr->to_string() + "[" + index->to_string() + "]" + " ";
}