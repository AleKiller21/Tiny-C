#include "block_statement.h"

string block_statement::to_string()
{
    if(decl_list != NULL && stmt_list != NULL)
        return "{\n" + decl_list->to_string() + "\n" + stmt_list->to_string() + "}\n\n";

    if(stmt_list == NULL && decl_list != NULL) return "{\n" + decl_list->to_string() + "\n" + "}\n\n";
    if(stmt_list != NULL && decl_list == NULL) return "{\n" + stmt_list->to_string() + "\n" + "}\n\n";
    return "{\n }\n\n";
}