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

void if_statement::validate_semantic(bool is_loop_statement, bool *has_return)
{
    bool true_return = false;
    bool false_return = false;

    condition->get_type();
    true_block->validate_semantic(is_loop_statement, &true_return);
    if(false_block != NULL) false_block->validate_semantic(is_loop_statement, &false_return);

    if(has_return != NULL && (true_return && false_return)) *has_return = true;
}