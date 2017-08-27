#include "while_statement.h"

string while_statement::to_string()
{
    return "while( " + condition->to_string() + ")\n" + stmt->to_string();
}