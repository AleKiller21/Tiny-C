#include "time_expression.h"

string time_expression::to_string()
{
    return "time(" + expr->to_string() + ") ";
}

int time_expression::get_kind()
{
    return TIME_EXPR;
}

id_attributes time_expression::get_type()
{
    id_attributes expr_type = expr->get_type();

    if(expr_type.semantic_fail) return expr_type;
    return { INT, false, SIMPLE, false };
}

asm_code *time_expression::generate_code(stack_manager *manager)
{
    string code = "\tlw $v0, MS_COUNTER_REG_ADDR\n";
    return new asm_code { code, "$v0", -1 };
}