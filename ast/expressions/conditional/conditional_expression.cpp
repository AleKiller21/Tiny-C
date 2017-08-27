#include "conditional_expression.h"

string conditional_expression::to_string()
{
    return evaluate_expression->to_string() + "? " + true_expression->to_string() + ": " + false_expression->to_string();
}