#include "expression_statement.h"

string expression_statement::to_string()
{
    if(expr == NULL) return ";\n";

    return expr->to_string() + ";\n";
}

int expression_statement::get_kind()
{
    return EXPRESSION_STMT;
}

void expression_statement::validate_semantic(bool is_loop_statement, bool *has_return)
{
    if(expr != NULL) expr->get_type();
}

string* expression_statement::generate_code(stack_manager *manager, string nearest_loop, string nearest_loop_end)
{   
    if(expr == NULL || !expr->is_code) return new string();

    asm_code *expr_code = expr->generate_code(manager);
    string code = expr_code->code;
    reg_manager.free_register(expr_code->place);

    delete expr_code;
    return new string(code);
}