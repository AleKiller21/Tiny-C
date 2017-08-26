#include "post_decrement_expression.h"

post_decrement_expression::post_decrement_expression(expression* expr)
{
    this->expr = expr;
}

string post_decrement_expression::to_string()
{
    return expr->to_string() + "-- ";
}