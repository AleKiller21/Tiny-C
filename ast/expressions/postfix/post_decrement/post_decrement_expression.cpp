#include "post_decrement_expression.h"

string post_decrement_expression::to_string()
{
    return expr->to_string() + "-- ";
}

int post_decrement_expression::get_kind()
{
    return POST_DEC_EXPR;
}