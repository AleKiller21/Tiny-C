#include "srand_expression.h"

string srand_expression::to_string()
{
    return "srand(" + expr->to_string() + ") ";
}

int srand_expression::get_kind()
{
    return SRAND_EXPR;
}

type_attributes srand_expression::get_type()
{
    type_attributes expr_type = expr->get_type();

    if(expr_type.semantic_fail) return expr_type;
    return { VOID, false, SIMPLE, false };
}

asm_code *srand_expression::generate_code(stack_manager *manager)
{
    asm_code *expr_code = expr->generate_code(manager);
    string code;

    if(!expr->is_code)
    {
        code = "\tli $a0, " + std::to_string(expr_code->constant) + "\n";
        code += "\tjal rand_seed\n";
        delete expr_code;
        return new asm_code { code, "$v0", -1 };
    }

    code = expr_code->code;
    code += "\tmove $a0, " + expr_code->place + "\n";
    reg_manager.free_register(expr_code->place);
    code += "\tjal rand_seed\n";

    delete expr_code;
    return new asm_code { code, "$v0", -1 };
}