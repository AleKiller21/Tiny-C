#include "mult_expression.h"

string mult_expression::to_string()
{
    return expr1->to_string() + "* " + expr2->to_string();
}

int mult_expression::get_kind()
{
    return MULT_EXPR;
}

asm_code *mult_expression::generate_code(stack_manager *manager)
{
    asm_code *expr1_code;
    asm_code *expr2_code;
    string code;
    bool right_operand_first = false;

    generate_operands_code(manager, &expr1_code, &expr2_code, &right_operand_first);
    asm_code *expr_code = evaluate_function_expressions(manager, expr1_code, expr2_code, right_operand_first);

    if(expr_code != NULL) {}

    else if(!expr1->is_code && !expr2->is_code)
        expr_code = new asm_code { "", "", expr1_code->constant * expr2_code->constant };

    else if(expr1->is_code && expr2->is_code)
    {
        if(right_operand_first) code = expr2_code->code + expr1_code->code;
        else code = expr1_code->code + expr2_code->code;
        
        reg_manager.free_register(expr1_code->place);
        reg_manager.free_register(expr2_code->place);
        code += "\tmove $a0, " + expr1_code->place + "\n";
        code += "\tmove $a1, " + expr2_code->place + "\n";
        code += "\tjal mult\n";
        expr_code = new asm_code { code, "$v0", -1 };
    }

    else if(expr1->is_code)
    {
        code = expr1_code->code;
        code += "\tmove $a0, " + expr1_code->place + "\n";
        code += "\tli $a1, " + std::to_string(expr2_code->constant) + "\n";
        reg_manager.free_register(expr1_code->place);
        code += "\tjal mult\n";
        expr_code = new asm_code { code, "$v0", -1 };
    }

    else
    {
        code = expr2_code->code;
        code += "\tli $a0, " + std::to_string(expr1_code->constant) + "\n";
        code += "\tmove $a1, " + expr2_code->place + "\n";
        reg_manager.free_register(expr2_code->place);
        code += "\tjal mult\n";
        expr_code = new asm_code { code, "$v0", -1 };
    }

    delete expr1_code;
    delete expr2_code;
    return expr_code;
}