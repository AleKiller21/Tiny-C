#include "printf_expression.h"

string printf_expression::to_string()
{
    return "printf(" + expr->to_string() + ") ";
}

int printf_expression::get_kind()
{
    return PRINTF_EXPR;
}