#include "expression_statement.h"

string expression_statement::to_string()
{
    if(expr == NULL) return ";\n";

    return expr->to_string() + ";\n";
}

int expression_statement::get_kind()
{
    return EXPRESSION_STMT;
}

void expression_statement::validate_semantic(bool is_loop_statement, bool *has_return)
{
    if(expr != NULL) expr->get_type();
}