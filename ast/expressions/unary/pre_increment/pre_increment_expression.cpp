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

asm_code *pre_increment_expression::generate_code(stack_manager *manager)
{
    asm_code *expr_code = expr->generate_code(manager);
    string *operand_id = expr->get_operand_id();
    string code = expr_code->code;

    //TODO: Tomar en cuenta como seria la suma con apuntadores. Ej: si es un int* se sumaria 4, no 1
    code += "\taddi " + expr_code->place + ", " + expr_code->place + ", 1\n";
    code += manager->store_into_var(expr_code->place, *operand_id);

    delete expr_code;
    delete operand_id;
    return new asm_code { code, expr_code->place, -1 };
}