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

void return_statement::validate_semantic(bool is_loop_statement)
{
    if(expr != NULL) expr->get_type();
}