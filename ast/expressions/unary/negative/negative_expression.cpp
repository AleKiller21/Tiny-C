#include "negative_expression.h"

string negative_expression::to_string()
{
    return "-" + expr->to_string();
}

int negative_expression::get_kind()
{
    return NEGATIVE_EXPR;
}