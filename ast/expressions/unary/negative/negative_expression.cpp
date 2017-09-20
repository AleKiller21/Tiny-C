#include "negative_expression.h"

string negative_expression::to_string()
{
    return "-" + expr->to_string();
}

int negative_expression::get_kind()
{
    return NEGATIVE_EXPR;
}

type_attributes negative_expression::get_type()
{
    type_attributes expr_type = expr->get_type();
    
    if(expr_type.semantic_fail) return expr_type;
    if(expr_type.pointer || expr_type.kind == ARRAY)
    {
        comp_utils::show_message("error", "wrong type argument to unary minus", position);
        return { 0, 0, 0, true };
    }

    return { expr_type.type, false, SIMPLE, false };
}

asm_code *negative_expression::generate_code(stack_manager *manager)
{
    is_code = expr->is_code;
    asm_code *expr_code = expr->generate_code(manager);

    if(!expr->is_code)
    {
        expr_code->constant = -expr_code->constant;
        return expr_code;
    }

    expr_code->code += "\tsubu " + expr_code->place + ", $zero, " + expr_code->place + "\n";
    return expr_code;
}