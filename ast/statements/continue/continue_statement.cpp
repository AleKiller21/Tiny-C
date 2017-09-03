#include "continue_statement.h"

string continue_statement::to_string()
{
    return "continue;\n";
}

int continue_statement::get_kind()
{
    return CONTINUE_STMT;
}