#include "while_statement.h"

string while_statement::to_string()
{
    return "while( " + condition->to_string() + ")\n" + stmt->to_string();
}

int while_statement::get_kind()
{
    return WHILE_STMT;
}

void while_statement::validate_semantic(bool is_loop_statement)
{
    condition->get_type();
    stmt->validate_semantic(true);
}