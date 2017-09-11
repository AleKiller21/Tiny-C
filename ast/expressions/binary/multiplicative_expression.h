#ifndef MULTIPLICATIVE_EXPRESSION
#define MULTIPLICATIVE_EXPRESSION

#include "binary_expression.h"

class multiplicative_expression : public binary_expression
{
protected:
    string op;

    multiplicative_expression(expression *expr1, expression *expr2, int position, string op) : binary_expression(expr1, expr2, position)
    {
        rules["int,int"] = "int";
        rules["int,char"] = "int";
        rules["char,int"] = "int";
        rules["char,char"] = "int";
        this->op = op;
    }

public:
    id_attributes get_type()
    {
        id_attributes expr1_type = expr1->get_type();
        id_attributes expr2_type = expr2->get_type();

        if(expr1_type.semantic_fail || expr2_type.semantic_fail) return expr1_type;
        string op1 = comp_utils::id_attrs_to_string(expr1_type);
        string op2 = comp_utils::id_attrs_to_string(expr2_type);
        try
        {
            string entry = op1 + "," + op2;
            rules.at(entry);
            return { INT, false, SIMPLE, false };
        }

        catch(out_of_range)
        {
            string entries = " (have '" + op1 + "' and '" + op2 + "')"; 
            comp_utils::show_message("error", "invalid operands to binary " + op + entries, position);
            return { 0, 0, 0, true };
        }
    }
};

#endif // MULTIPLICATIVE_EXPRESSION