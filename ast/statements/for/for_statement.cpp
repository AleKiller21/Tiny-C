#include "for_statement.h"

string for_statement::to_string()
{
    if(expr3 != NULL) 
        return "for(" + expr1->to_string() + " " + expr2->to_string() + " " + expr3->to_string() + ")\n" + stmt->to_string();

    return "for(" + expr1->to_string() + " " + expr2->to_string() + ")\n" + stmt->to_string();
}

int for_statement::get_kind()
{
    return FOR_STMT;
}

void for_statement::validate_semantic(bool is_loop_statement, bool *has_return)
{
    expr1->validate_semantic(true, has_return);
    expr2->validate_semantic(true, has_return);
    stmt->validate_semantic(true, NULL);
    if(expr3 != NULL) expr3->get_type();
}

string* for_statement::generate_code(stack_manager *manager)
{
    throw "for_statement generate_code not implemented";
}