#ifndef CONDITIONAL_EXPRESSION
#define CONDITIONAL_EXPRESSION

#include "../expression.h"
#include <map>

using namespace std;

class conditional_expression : public expression
{
private:
    expression *evaluate_expression, *true_expression, *false_expression;
    map<string, id_attributes> rules;

public:
    conditional_expression(expression* evaluate, expression* true_expr, expression* false_expr, int position) :
    expression(position)
    {
        evaluate_expression = evaluate;
        true_expression = true_expr;
        false_expression = false_expr;
        rules["int,int"]        = { INT, false, SIMPLE, false };
        rules["int,char"]       = { INT, false, SIMPLE, false };
        rules["char,int"]       = { INT, false, SIMPLE, false };
        rules["char,char"]      = { INT, false, SIMPLE, false };
        
        rules["int*,int*"]      = { INT, true, SIMPLE, false };
        rules["char*,char*"]    = { INT, true, SIMPLE, false };
        
        // Lo restringi a que solo soportara apuntadores al mismo tipo
    }

    string to_string();
    int get_kind();
    id_attributes get_type();
    // string generate_mips();
};

#endif // CONDITIONAL_EXPRESSION