#include "break_statement.h"

string break_statement::to_string()
{
    return "break;\n";
}

int break_statement::get_kind()
{
    return BREAK_STMT;
}

void break_statement::validate_semantic()
{
    
}