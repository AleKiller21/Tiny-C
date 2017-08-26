#include "pre_decrement_expression.h"

string pre_decrement_expression::to_string()
{
    return "--" + expr->to_string();
}