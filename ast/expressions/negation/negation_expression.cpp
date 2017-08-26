#include "negation_expression.h"

string negation_expression::to_string()
{
    return "!" + expr->to_string();
}