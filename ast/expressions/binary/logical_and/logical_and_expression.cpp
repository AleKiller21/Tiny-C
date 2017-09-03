#include "logical_and_expression.h"

string logical_and_expression::to_string()
{
    return expr1->to_string() + "&& " + expr2->to_string();
}

int logical_and_expression::get_kind()
{
    return LA_EXPR;
}