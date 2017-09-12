#include "block_statement.h"

string block_statement::to_string()
{
    if(decl_list != NULL && stmt_list != NULL)
        return "{\n" + decl_list->to_string() + "\n" + stmt_list->to_string() + "}\n\n";

    if(stmt_list == NULL && decl_list != NULL) return "{\n" + decl_list->to_string() + "\n" + "}\n\n";
    if(stmt_list != NULL && decl_list == NULL) return "{\n" + stmt_list->to_string() + "\n" + "}\n\n";
    return "{\n }\n\n";
}

int block_statement::get_kind()
{
    return BLOCK_STMT;
}

void block_statement::validate_semantic(bool is_loop_statement)
{
    if(!first_class_block) sym_table.push_scope();

    if(decl_list != NULL) decl_list->validate_semantic();
    if(stmt_list != NULL) stmt_list->validate_semantic(is_loop_statement);

    sym_table.pop_scope();
}