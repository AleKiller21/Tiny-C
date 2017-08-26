#include "pointer_expression.h"

string pointer_expression::to_string()
{
    return "*" + expr->to_string();
}