#include "statement_list.h"

string statement_list::to_string()
{
    string str;

    for(list<statement*>::iterator it = statements.begin(); it != statements.end(); it++)
    {
        str += "\t" + (*it)->to_string();
    }

    return str;
}

int statement_list::get_kind()
{
    return LIST_STMT;
}

void statement_list::add_statement(statement* stmt)
{
    statements.push_back(stmt);
}

void statement_list::validate_semantic(bool is_loop_statement, bool *has_return)
{
    for(list<statement*>::iterator it = statements.begin(); it != statements.end(); it++)
    {
        (*it)->validate_semantic(is_loop_statement, has_return);
    }
}