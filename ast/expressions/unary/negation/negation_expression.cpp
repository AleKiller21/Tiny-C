#include "negation_expression.h"

string negation_expression::to_string()
{
    return "!" + expr->to_string();
}

int negation_expression::get_kind()
{
    return NEGATION_EXPR;
}

id_attributes negation_expression::get_type()
{
    id_attributes expr_type = expr->get_type();
    
    if(expr_type.semantic_fail) return expr_type;
    return { INT, false, SIMPLE, false };
}