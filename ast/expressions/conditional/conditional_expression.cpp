#include "conditional_expression.h"

string conditional_expression::to_string()
{
    return evaluate_expression->to_string() + "? " + true_expression->to_string() + ": " + false_expression->to_string();
}

int conditional_expression::get_kind()
{
    return COND_EXPR;
}

id_attributes conditional_expression::get_type()
{
    id_attributes cond_type = evaluate_expression->get_type();
    id_attributes true_expr_type = true_expression->get_type();
    id_attributes false_expr_type = false_expression->get_type();

    if(cond_type.semantic_fail || true_expr_type.semantic_fail || false_expr_type.semantic_fail) return cond_type;
    string op1 = comp_utils::id_attrs_to_string(true_expr_type);
    string op2 = comp_utils::id_attrs_to_string(false_expr_type);
    try
    {
        string entry = op1 + "," + op2;
        return rules.at(entry);
    }

    catch(out_of_range)
    {
        string entries = " (have '" + op1 + "' and '" + op2 + "')"; 
        comp_utils::show_message("error", "invalid operands to conditional operator " + entries, position);
        return { 0, 0, 0, true };
    }
}