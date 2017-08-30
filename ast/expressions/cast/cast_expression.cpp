#include "cast_expression.h"

string cast_expression::to_string()
{
    return "(" + type->to_string() + ")" + expr->to_string();
}