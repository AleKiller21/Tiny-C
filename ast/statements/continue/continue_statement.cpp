#include "continue_statement.h"

string continue_statement::to_string()
{
    return "continue;\n";
}

int continue_statement::get_kind()
{
    return CONTINUE_STMT;
}

void continue_statement::validate_semantic(bool is_loop_statement, bool *has_return)
{
    if(is_loop_statement) return;
    comp_utils::show_message("error", "continue statement not within a loop", position);
}

string* continue_statement::generate_code(stack_manager *manager)
{
    throw "continue_statement generate_code not implemented";
}