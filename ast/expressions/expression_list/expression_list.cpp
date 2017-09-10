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

int expression_list::get_kind()
{
    return LIST_EXPR;
}

list<expression*> expression_list::get_list()
{
    return expressions;
}

id_attributes expression_list::get_type()
{
    for(list<expression*>::iterator it = expressions.begin(); it != expressions.end(); it++)
    {
        id_attributes expr_type = (*it)->get_type();
        if(expr_type.semantic_fail) return expr_type;
    }

    return { INT, false, SIMPLE, false }; //Dummy value
}