#include "if_statement.h"

string if_statement::to_string()
{
    if(false_block == NULL)
        return "if( " + condition->to_string() + ")\n" + true_block->to_string();

    return "if( " + condition->to_string() + ")\n" + true_block->to_string() + "else\n" +
        false_block->to_string();
}

int if_statement::get_kind()
{
    return IF_STMT;
}

void if_statement::validate_semantic(bool is_loop_statement, bool *has_return)
{
    bool true_return = false;
    bool false_return = false;

    condition->get_type();
    true_block->validate_semantic(is_loop_statement, &true_return);
    if(false_block != NULL) false_block->validate_semantic(is_loop_statement, &false_return);

    if(has_return != NULL && (true_return && false_return)) *has_return = true;
}

string *if_statement::generate_code(stack_manager *manager)
{
    asm_code *cond_code = condition->generate_code(manager);
    string *true_code = true_block->generate_code(manager);
    string end_label = lbl_manager.get_free_label("endif");;
    string treg;
    string code;

    if(!condition->is_code)
    {
        treg = reg_manager.get_register(false);
        code = "\tli " + treg + ", " + std::to_string(cond_code->constant) + "\n";
    }

    else
    {
        code = cond_code->code;
        reg_manager.free_register(cond_code->place);
        treg = cond_code->place;
    }

    if(false_block == NULL)
    {
        code += "\tbeqz " + treg + ", " + end_label + "\n";
        code += *true_code;
        code += end_label + ":\n";
    
        delete cond_code;
        delete true_code;
        return new string(code);
    }

    string *false_code = false_block->generate_code(manager);
    string false_label = lbl_manager.get_free_label("if_false");

    code += "\tbeqz " + treg + ", " + false_label + "\n";
    code += *true_code;
    code += "\tj " + end_label + "\n";
    code += false_label + ":\n";
    code += *false_code;
    code += end_label + ":\n";

    delete cond_code;
    delete true_code;
    delete false_code;

    return new string(code);
}