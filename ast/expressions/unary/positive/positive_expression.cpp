#include "positive_expression.h"

string positive_expression::to_string()
{
    return "+" + expr->to_string();
}

int positive_expression::get_kind()
{
    return POSITIVE_EXPR;
}