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

void statement_list::add_statement(statement* stmt)
{
    statements.push_back(stmt);
}