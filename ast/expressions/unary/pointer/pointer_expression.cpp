#include "pointer_expression.h"

string pointer_expression::to_string()
{
    return "*" + expr->to_string();
}

int pointer_expression::get_kind()
{
    return POINTER_EXPR;
}

id_attributes pointer_expression::get_type()
{
    id_attributes expr_type = expr->get_type();

    if(expr_type.semantic_fail) return expr_type;
    if(!expr_type.pointer && expr_type.kind != ARRAY)
    {
        comp_utils::show_message("error", "invalid type argument of unary '*'", position);
        return {0, 0, 0, true };
    }

    return { expr_type.type, false, SIMPLE, false };
}