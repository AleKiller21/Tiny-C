#include "div_expression.h"

string div_expression::to_string()
{
    return expr1->to_string() + "/ " + expr2->to_string();
}

int div_expression::get_kind()
{
    return DIV_EXPR;
}

asm_code *div_expression::generate_code(stack_manager *manager)
{
    // is_code = !(!expr1->is_code && !expr2->is_code);
    // asm_code *expr1_code = expr1->generate_code(manager);
    // asm_code *expr2_code = expr2->generate_code(manager);
    // asm_code *expr_code;
    // string code;

    // if(!expr1->is_code && !expr2->is_code)
    //     expr_code = new asm_code { "", "", expr1_code->constant / expr2_code->constant };

    // else if(expr1->is_code && expr2->is_code)
    // {
    //     code = expr1_code->code + expr2_code->code;
    // }
}