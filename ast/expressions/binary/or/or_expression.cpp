#include "or_expression.h"

string or_expression::to_string()
{
    return expr1->to_string() + "| " + expr2->to_string();
}

int or_expression::get_kind()
{
    return OR_EXPR;
}

asm_code *or_expression::generate_code(stack_manager *manager)
{
    asm_code *expr1_code;
    asm_code *expr2_code;
    asm_code *expr_code;
    string treg;
    bool right_operand_first = false;

    generate_operands_code(manager, &expr1_code, &expr2_code, &right_operand_first);
    string code = evaluate_function_expressions(manager, expr1_code, expr2_code, right_operand_first);

    if(!code.empty())
    {
        treg = reg_manager.get_register(false);
        code += "\tor " + treg + ", " + expr1_code->place + ", " + expr2_code->place + "\n";
    }

    else if(!expr1->is_code && !expr2->is_code)
    {
        expr_code = new asm_code { "", "", expr1_code->constant | expr2_code->constant };
        delete expr1_code, expr2_code;
        return expr_code;
    }

    else if(expr1->is_code && expr2->is_code)
    {
        if(right_operand_first) code = expr2_code->code + expr1_code->code;
        else code = expr1_code->code + expr2_code->code;

        reg_manager.free_register(expr1_code->place);
        reg_manager.free_register(expr2_code->place);
        treg = reg_manager.get_register(false);
        code += "\tor " + treg + ", " + expr1_code->place + ", " + expr2_code->place + "\n";
    }

    else if(expr1->is_code)
    {
        code = expr1_code->code;
        reg_manager.free_register(expr1_code->place);
        treg = reg_manager.get_register(false);
        code += "\tori " + treg + ", " + expr1_code->place + ", " + std::to_string(expr2_code->constant) + "\n";
    }

    else
    {
        code = expr2_code->code;
        treg = reg_manager.get_register(false);
        code += "\tli " + treg + ", " + std::to_string(expr1_code->constant) + "\n";
        code += "\tor " + treg + ", " + treg + ", " + expr2_code->place + "\n";
        reg_manager.free_register(expr2_code->place);
    }

    expr_code = new asm_code { code, treg, -1 };
    delete expr1_code, expr2_code;
    return expr_code;
}