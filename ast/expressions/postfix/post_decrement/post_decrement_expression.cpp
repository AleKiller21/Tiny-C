#include "post_decrement_expression.h"

string post_decrement_expression::to_string()
{
    return expr->to_string() + "-- ";
}

int post_decrement_expression::get_kind()
{
    return POST_DEC_EXPR;
}

id_attributes post_decrement_expression::get_type()
{
    id_attributes expr_type = expr->get_type();
    
    if(expr_type.semantic_fail) return expr_type;
    if(!expr->get_lvalue() || expr_type.kind == ARRAY)
    {
        comp_utils::show_message("error", "lvalue required as decrement operand", position);
        return { 0, 0, 0, true };
    }

    return { expr_type.type, expr_type.pointer, expr_type.kind, false };
}