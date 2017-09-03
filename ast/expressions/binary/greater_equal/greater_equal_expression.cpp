#include "greater_equal_expression.h"

string greater_equal_expression::to_string()
{
    return expr1->to_string() + ">= " + expr2->to_string();
}

int greater_equal_expression::get_kind()
{
    return GE_EXPR;
}