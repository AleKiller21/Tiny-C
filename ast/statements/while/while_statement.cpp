#include "while_statement.h"

string while_statement::to_string()
{
    return "while( " + condition->to_string() + ")\n" + block->to_string();
}

int while_statement::get_kind()
{
    return WHILE_STMT;
}

void while_statement::validate_semantic(bool is_loop_statement, bool *has_return)
{
    condition->get_type();
    block->validate_semantic(true, NULL);
}

string *while_statement::generate_code(stack_manager *manager)
{
    string loop_label = lbl_manager.get_free_label("while");
    string end_label = lbl_manager.get_free_label("endwhile");
    asm_code *cond_code = condition->generate_code(manager);
    string *block_code;
    string treg, code;

    code = loop_label + ":\n";

    if(!condition->is_code)
    {
        treg = reg_manager.get_register(false);
        code += "\tli " + treg + ", " + std::to_string(cond_code->constant) + "\n";
    }

    else
    {        
        code += cond_code->code;
        treg = cond_code->place;
    }

    code += "\tbeqz " + treg + ", " + end_label + "\n";
    reg_manager.free_register(treg);
    block_code = block->generate_code(manager);
    code += *block_code;
    code += "\tj " + loop_label + "\n";
    code += end_label + ":\n";

    delete cond_code;
    delete block_code;
    return new string(code);
}