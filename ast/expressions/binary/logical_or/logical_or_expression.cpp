#include "logical_or_expression.h"

string logical_or_expression::to_string()
{
    return expr1->to_string() + "|| " + expr2->to_string();
}

int logical_or_expression::get_kind()
{
    return LO_EXPR;
}