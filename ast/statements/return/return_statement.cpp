#include "return_statement.h"

string return_statement::to_string()
{
    if(expr == NULL) return "return;\n";
    
    return "return " + expr->to_string() + ";\n";
}

int return_statement::get_kind()
{
    return RETURN_STMT;
}

void return_statement::validate_semantic(bool is_loop_statement, bool *has_return)
{
    if(expr != NULL) expr->get_type();
    if(has_return != NULL) *has_return = true;
}

string* return_statement::generate_code(stack_manager *manager, string nearest_loop, string nearest_loop_end)
{
    string code;
    bool reset_sregisters = reg_manager.get_sregs_used() > 0;

    if(expr != NULL)
    {
        asm_code *expr_code = expr->generate_code(manager);
        if(!expr->is_code) code = "\tli $v0, " + std::to_string(expr_code->constant) + "\n";
        else
        {
            code = expr_code->code;
            code += "\tmove $v0, " + expr_code->place + "\n";
            reg_manager.free_register(expr_code->place);
        }
    }
    
    // for(int sregs_used = reg_manager.get_sregs_used(); sregs_used > 0; sregs_used--)
    // {
    //     code += "\tlw $s" + std::to_string(sregs_used - 1) + ", " + "($sp)\n";
    //     code += "\taddi $sp, $sp, 4\n";
    // }
    int counter = manager->displacement - 12;
    for(int i = 0; i < 8; i++)
    {
        code += "\tlw $s" + std::to_string(i) + ", " + std::to_string(counter) + "($fp)\n";
        counter -= 4;
        //code += "\taddi $sp, $sp, 4\n";
    }

    if(reset_sregisters) reg_manager.reset_sregisters();

    code += "\tlw $fp, " + std::to_string(manager->displacement - 4) + "($sp)\n";
    code += "\tlw $ra, " + std::to_string(manager->displacement - 8) + "($sp)\n";
    code += "\taddi $sp, $sp, " + std::to_string(manager->displacement) + "\n";
    code += "\tjr $ra\n";

    return new string(code);
}