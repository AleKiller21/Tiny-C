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