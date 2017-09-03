#include "less_equal_expression.h"

string less_equal_expression::to_string()
{
    return expr1->to_string() + "<= " + expr2->to_string();
}

int less_equal_expression::get_kind()
{
    return LE_EXPR;
}