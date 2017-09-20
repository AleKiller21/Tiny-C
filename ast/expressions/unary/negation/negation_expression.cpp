#include "negation_expression.h"

string negation_expression::to_string()
{
    return "!" + expr->to_string();
}

int negation_expression::get_kind()
{
    return NEGATION_EXPR;
}

type_attributes negation_expression::get_type()
{
    type_attributes expr_type = expr->get_type();
    
    if(expr_type.semantic_fail) return expr_type;
    return { INT, false, SIMPLE, false };
}

asm_code *negation_expression::generate_code(stack_manager *manager)
{
    is_code = expr->is_code;
    asm_code *expr_code = expr->generate_code(manager);

    if(!expr->is_code)
    {
        expr_code->constant = expr_code->constant >= 1 ? 0 : 1;
        return expr_code;
    }

    expr_code->code += "\tslt " + expr_code->place + ", " + expr_code->place + ", 1\n";
    return expr_code;
}