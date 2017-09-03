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