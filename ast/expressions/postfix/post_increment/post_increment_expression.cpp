#include "post_increment_expression.h"

string post_increment_expression::to_string()
{
    return expr->to_string() + "++ ";
}

int post_increment_expression::get_kind()
{
    return POST_INC_EXPR;
}

type_attributes post_increment_expression::get_type()
{
    type_attributes expr_type = expr->get_type();

    if(expr_type.semantic_fail) return expr_type;
    if(!expr->get_lvalue() || expr_type.kind == ARRAY)
    {
        comp_utils::show_message("error", "lvalue required as increment operand", position);
        return { 0, 0, 0, true };
    }

    return { expr_type.type, expr_type.pointer, expr_type.kind, false };
}

asm_code *post_increment_expression::generate_code(stack_manager *manager)
{
    asm_code *expr_code = expr->generate_code(manager);
    string *operand_id = expr->get_operand_id();
    string code = expr_code->code;
    string treg = reg_manager.get_register(false);

    //TODO: Tomar en cuenta como seria la suma con apuntadores. Ej: si es un int* se sumaria 4, no 1
    code += "\taddi " + treg + ", " + expr_code->place + ", 1\n";
    code += manager->store_into_var(treg, *operand_id);
    reg_manager.free_register(treg);

    delete expr_code;
    delete operand_id;
    return new asm_code { code, expr_code->place, -1 };
}

string *post_increment_expression::get_operand_id()
{
    return expr->get_operand_id();
}