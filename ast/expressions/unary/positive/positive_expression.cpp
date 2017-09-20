#include "positive_expression.h"

string positive_expression::to_string()
{
    return "+" + expr->to_string();
}

int positive_expression::get_kind()
{
    return POSITIVE_EXPR;
}

type_attributes positive_expression::get_type()
{
    type_attributes expr_type = expr->get_type();

    if(expr_type.semantic_fail) return expr_type;
    if(expr_type.pointer || expr_type.kind == ARRAY)
    {
        comp_utils::show_message("error", "wrong type argument to unary plus", position);
        return { 0, 0, 0, true };
    }

    return { expr_type.type, false, SIMPLE, false };
}

asm_code *positive_expression::generate_code(stack_manager *manager)
{
    is_code = expr->is_code;
    return expr->generate_code(manager);
}