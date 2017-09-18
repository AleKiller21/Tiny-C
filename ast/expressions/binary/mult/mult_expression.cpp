#include "mult_expression.h"

string mult_expression::to_string()
{
    return expr1->to_string() + "* " + expr2->to_string();
}

int mult_expression::get_kind()
{
    return MULT_EXPR;
}

// int c = x * (y * (a * (b * b)));
// x * y + i + m
asm_code *mult_expression::generate_code(stack_manager *manager)
{
    asm_code *expr1_code;
    asm_code *expr2_code;
    asm_code *expr_code;
    string code;
    bool right_operand_first = false;

    if(is_binary_or_function(expr2->get_kind()))
    {
        right_operand_first = true;
        expr2_code = expr2->generate_code(manager);
        expr1_code = expr1->generate_code(manager);
    }

    else
    {
        expr1_code = expr1->generate_code(manager);
        expr2_code = expr2->generate_code(manager);
    }

    is_code = !(!expr1->is_code && !expr2->is_code);
    if(!expr1->is_code && !expr2->is_code)
    {
        expr_code = new asm_code { "", "", expr1_code->constant * expr2_code->constant };
        delete expr1_code;
        delete expr2_code;
        return expr_code;
    }

    if(!expr1_code->place.compare("$v0") && !expr2_code->place.compare("$v0"))
    {
        string sreg = reg_manager.get_register(true);
        if(right_operand_first)
        {
            code = expr2_code->code;
            code += manager->save_sregister(sreg);
            code += "\tmove " + sreg + ", $v0\n";
            code += expr1_code->code;
            expr2_code->place = sreg;
        }

        else
        {
            code = expr1_code->code;
            code += manager->save_sregister(sreg);
            code += "\tmove " + sreg + ", $v0\n";
            code += expr2_code->code;
            expr1_code->place = sreg;
        }

        reg_manager.free_register(expr1_code->place);
        reg_manager.free_register(expr2_code->place);
        code += "\tmove $a0, " + expr1_code->place + "\n";
        code += "\tmove $a1, " + expr2_code->place + "\n";
        code += "\tjal mult\n";
        expr_code = new asm_code { code, "$v0", -1 };
    }

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