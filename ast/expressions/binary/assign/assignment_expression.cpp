#include "assignment_expression.h"

string assignment_expression::to_string()
{
    return expr1->to_string() + "= " + expr2->to_string();
}

int assignment_expression::get_kind()
{
    return ASSIGN_EXPR;
}

id_attributes assignment_expression::get_type()
{
    id_attributes expr1_type = expr1->get_type();
    id_attributes expr2_type = expr2->get_type();

    if(expr1_type.semantic_fail || expr2_type.semantic_fail) return expr1_type;
    if(!expr1->get_lvalue() || expr1_type.kind == FUNCTION)
    {
        comp_utils::show_message("error", "lvalue required as left operand of assignment", position);
        return { 0, 0, 0, true };
    }

    if(expr1_type.kind == ARRAY)
    {
        comp_utils::show_message("error", "assignment to expression with array type", position);
        return { 0, 0, 0, true };
    }

    string op1 = comp_utils::id_attrs_to_string(expr1_type);
    string op2 = comp_utils::id_attrs_to_string(expr2_type);
    
    try
    {
        string entry = op1 + "," + op2;
        return rules.at(entry);
    }

    catch(out_of_range)
    {
        string entries = " (have '" + op1 + "' and '" + op2 + "')"; 
        comp_utils::show_message("error", "invalid operands to binary " + op + entries, position);
        return { 0, 0, 0, true };
    }
}