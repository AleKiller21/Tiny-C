#include "scanf_expression.h"

string scanf_expression::to_string()
{
    return "scanf(" + expr->to_string() + ") ";
}

int scanf_expression::get_kind()
{
    return SCANF_EXPR;
}