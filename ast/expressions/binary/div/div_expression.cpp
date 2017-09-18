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
    asm_code *expr1_code;
    asm_code *expr2_code;
    bool right_operand_first = false;

    generate_operands_code(manager, &expr1_code, &expr2_code, &right_operand_first);
    string code = evaluate_function_expressions(manager, expr1_code, expr2_code, right_operand_first);

    if(!code.empty())
    {
        code += "\tmove $a0, " + expr1_code->place + "\n";
        code += "\tmove $a1, " + expr2_code->place + "\n";
    }

    else if(!expr1->is_code && !expr2->is_code)
    {
        delete expr1_code;
        delete expr2_code;
        return new asm_code { "", "", expr1_code->constant / expr2_code->constant };
    }

    else if(expr1->is_code && expr2->is_code)
    {
        if(right_operand_first) code = expr2_code->code + expr1_code->code;
        else code = expr1_code->code + expr2_code->code;

        reg_manager.free_register(expr1_code->place);
        reg_manager.free_register(expr2_code->place);
        code += "\tmove $a0, " + expr1_code->place + "\n";
        code += "\tmove $a1, " + expr2_code->place + "\n";
    }

    else if(expr1->is_code)
    {
        code = expr1_code->code;
        reg_manager.free_register(expr1_code->place);
        code += "\tmove $a0, " + expr1_code->place + "\n";
        code += "\tli $a1, " + std::to_string(expr2_code->constant) + "\n";
    }

    else
    {
        code = expr2_code->code;
        reg_manager.free_register(expr2_code->place);
        code += "\tli $a0, " + std::to_string(expr1_code->constant) + "\n";
        code += "\tmove $a1, " + expr2_code->place + "\n";
    }

    code += "\taddi $sp, $sp, -8\n";
    code += "\tmove $a2, $sp\n";
    code += "\taddi $a3, $sp, 4\n";
    code += "\tjal divide\n";
    code += "\tlw $v0, ($sp)\n";
    code += "\taddi $sp, $sp, 8\n";

    delete expr1_code;
    delete expr2_code;
    return new asm_code { code, "$v0", -1 };
}