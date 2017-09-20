#include "for_statement.h"

string for_statement::to_string()
{
    if(expr3 != NULL) 
        return "for(" + expr1->to_string() + " " + expr2->to_string() + " " + expr3->to_string() + ")\n" + block->to_string();

    return "for(" + expr1->to_string() + " " + expr2->to_string() + ")\n" + block->to_string();
}

int for_statement::get_kind()
{
    return FOR_STMT;
}

void for_statement::validate_semantic(bool is_loop_statement, bool *has_return)
{
    expr1->validate_semantic(true, has_return);
    if(expr2 != NULL) expr2->get_type();
    block->validate_semantic(true, NULL);
    if(expr3 != NULL) expr3->get_type();
}

string* for_statement::generate_code(stack_manager *manager)
{
    string code, treg;
    string loop_label = lbl_manager.get_free_label("forloop");
    string end_label = lbl_manager.get_free_label("endfor");
    string expr3_label = lbl_manager.get_free_label("forinc");
    string *expr1_code = expr1->generate_code(manager);

    code = *expr1_code;
    code += loop_label + ":\n";
    
    if(expr2 != NULL)
    {
        asm_code *expr2_code = expr2->generate_code(manager);
        
        if(!expr2->is_code)
        {
            treg = reg_manager.get_register(false);
            code += "\tli " + treg + ", " + std::to_string(expr2_code->constant) + "\n";
        }
    
        else
        {
            code += expr2_code->code;
            treg = expr2_code->place;
        }

        code += "\tbeqz " + treg + ", " + end_label + "\n";
        reg_manager.free_register(treg);
        delete expr2_code;
    }

    string *block_code = block->generate_code(manager);
    code += *block_code;
    code += expr3_label + ":\n";

    if(expr3 != NULL)
    {
        asm_code *expr3_code = expr3->generate_code(manager);

        if(!expr3->is_code) {}
        else
        {
            code += expr3_code->code;
            reg_manager.free_register(expr3_code->place);
        }

        delete expr3_code;
    }

    code += "\tj " + loop_label + "\n";
    code += end_label + ":\n";
    delete expr1_code;
    return new string(code);
}