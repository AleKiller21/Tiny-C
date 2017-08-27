#include "if_statement.h"

string if_statement::to_string()
{
    if(false_block == NULL)
        return "if( " + condition->to_string() + ")\n" + true_block->to_string();

    return "if( " + condition->to_string() + ")\n" + true_block->to_string() + "else\n" +
        false_block->to_string();
}