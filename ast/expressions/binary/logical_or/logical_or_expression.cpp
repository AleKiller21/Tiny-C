#include "logical_or_expression.h"

string logical_or_expression::to_string()
{
    return expr1->to_string() + "|| " + expr2->to_string();
}

int logical_or_expression::get_kind()
{
    return LO_EXPR;
}

asm_code *logical_or_expression::generate_code(stack_manager *manager)
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
        code += "\tsne " + expr1_code->place + ", " + expr1_code->place + ", $zero\n";
        code += "\tsne " + expr2_code->place + ", " + expr2_code->place + ", $zero\n";
        code += "\tor " + treg + ", " + expr1_code->place + ", " + expr2_code->place + "\n";
    }

    else if(!expr1->is_code && !expr2->is_code)
    {
        expr_code = new asm_code { "", "", expr1_code->constant || expr2_code->constant };
        delete expr1_code;
        delete expr2_code;
        return expr_code;
    }

    else if(expr1->is_code && expr2->is_code)
    {
        if(right_operand_first) code = expr2_code->code + expr1_code->code;
        else code = expr1_code->code + expr2_code->code;

        reg_manager.free_register(expr1_code->place);
        reg_manager.free_register(expr2_code->place);
        treg = reg_manager.get_register(false);
        code += "\tsne " + expr1_code->place + ", " + expr1_code->place + ", $zero\n";
        code += "\tsne " + expr2_code->place + ", " + expr2_code->place + ", $zero\n";
        code += "\tor " + treg + ", " + expr1_code->place + ", " + expr2_code->place + "\n";
    }

    else if(expr1->is_code)
    {
        code = expr1_code->code;
        treg = reg_manager.get_register(false);
        code += "\tli " + treg + ", " + std::to_string(expr2_code->constant) + "\n";
        code += "\tsne " + expr1_code->place + ", " + expr1_code->place + ", $zero\n";
        code += "\tsne " + treg + ", " + treg + ", $zero\n";
        code += "\tor " + treg + ", " + expr1_code->place + ", " + treg + "\n";
        reg_manager.free_register(expr1_code->place);
    }

    else
    {
        code = expr2_code->code;
        treg = reg_manager.get_register(false);
        code += "\tli " + treg + ", " + std::to_string(expr1_code->constant) + "\n";
        code += "\tsne " + treg + ", " + treg + ", $zero\n";
        code += "\tsne " + expr2_code->place + ", " + expr2_code->place + ", $zero\n";
        code += "\tor " + treg + ", " + treg  + ", " +expr2_code->place + "\n";
        reg_manager.free_register(expr2_code->place);
    }

    expr_code = new asm_code { code, treg, -1 };
    delete expr1_code;
    delete expr2_code;
    return expr_code;
}