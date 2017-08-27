#include "expression_statement.h"

string expression_statement::to_string()
{
    if(expr == NULL) return ";\n";

    return expr->to_string() + ";\n";
}