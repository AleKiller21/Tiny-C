#include "or_expression.h"

string or_expression::to_string()
{
    return expr1->to_string() + "| " + expr2->to_string();
}

int or_expression::get_kind()
{
    return OR_EXPR;
}