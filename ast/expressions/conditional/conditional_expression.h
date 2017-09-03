#ifndef CONDITIONAL_EXPRESSION
#define CONDITIONAL_EXPRESSION

#include "../expression.h"

class conditional_expression : public expression
{
private:
    expression *evaluate_expression, *true_expression, *false_expression;

public:
    conditional_expression(expression* evaluate, expression* true_expr, expression* false_expr, int position) :
    expression(position)
    {
        evaluate_expression = evaluate;
        true_expression = true_expr;
        false_expression = false_expr;
    }

    string to_string();
    int get_kind();
    // string get_type();
    // string generate_mips();
};

#endif // CONDITIONAL_EXPRESSION