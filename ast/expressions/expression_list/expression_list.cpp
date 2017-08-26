#include "expression_list.h"

void expression_list::add_expression(expression* expr)
{
    expressions.push_back(expr);
}

string expression_list::to_string()
{
    string source;

    for(list<expression*>::iterator it = expressions.begin(); it != expressions.end(); it++)
    {
        source += (*it)->to_string() + ", ";
    }

    return source;
}