#include "two_complement_expression.h"

string two_complement_expression::to_string()
{
    return "~" + expr->to_string();
}

int two_complement_expression::get_kind()
{
    return TWO_COMP_EXPR;
}

id_attributes two_complement_expression::get_type()
{
    id_attributes expr_type = expr->get_type();
    
    if(expr_type.semantic_fail) return expr_type;
    if(expr_type.pointer || expr_type.kind == ARRAY)
    {
        comp_utils::show_message("error", "wrong type argument to bit complement", position);
        return { 0, 0, 0, true };
    }

    return { expr_type.type, false, SIMPLE, false };
}