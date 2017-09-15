#include "break_statement.h"

string break_statement::to_string()
{
    return "break;\n";
}

int break_statement::get_kind()
{
    return BREAK_STMT;
}

void break_statement::validate_semantic(bool is_loop_statement, bool *has_return)
{
    if(is_loop_statement) return;
    comp_utils::show_message("error", "break statement not within a loop", position);
}

string* break_statement::generate_code(stack_manager *manager)
{
    throw "break_Statement generate_code not implemented";
}