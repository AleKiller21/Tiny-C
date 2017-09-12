#include "if_statement.h"

string if_statement::to_string()
{
    if(false_block == NULL)
        return "if( " + condition->to_string() + ")\n" + true_block->to_string();

    return "if( " + condition->to_string() + ")\n" + true_block->to_string() + "else\n" +
        false_block->to_string();
}

int if_statement::get_kind()
{
    return IF_STMT;
}

void if_statement::validate_semantic(bool is_loop_statement)
{
    condition->get_type();
    true_block->validate_semantic(is_loop_statement);
    if(false_block != NULL) false_block->validate_semantic(is_loop_statement);
}