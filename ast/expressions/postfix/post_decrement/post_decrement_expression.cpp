#include "post_decrement_expression.h"

string post_decrement_expression::to_string()
{
    return expr->to_string() + "-- ";
}