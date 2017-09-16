#include "pre_increment_expression.h"

string pre_increment_expression::to_string()
{
    return "++" + expr->to_string();
}

int pre_increment_expression::get_kind()
{
    return PRE_INC_EXPR;
}

id_attributes pre_increment_expression::get_type()
{
    id_attributes expr_type = expr->get_type();
    
    if(expr_type.semantic_fail) return expr_type;
    if(!expr->get_lvalue() || expr_type.kind == ARRAY)
    {
        comp_utils::show_message("error", "lvalue required as increment operand", position);
        return { 0, 0, 0, true };
    }

    return { expr_type.type, expr_type.pointer, expr_type.kind, false };
}

string *pre_increment_expression::get_operand_id()
{
    return expr->get_operand_id();
}