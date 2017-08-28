#include "initializer.h"

initializer::initializer(expression* single_expr, expression_list* list_expr)
{
    this->single_expr = single_expr;
    this->list_expr = list_expr;
}

string initializer::to_string()
{
    if(single_expr != NULL) return single_expr->to_string();

    return "{" + list_expr->to_string() + "}";
}