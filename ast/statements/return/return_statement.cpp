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