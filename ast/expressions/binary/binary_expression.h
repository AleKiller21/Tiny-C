#ifndef BINARY_EXPRESSION
#define BINARY_EXPRESSION

#include <map>
#include "../expression.h"

class binary_expression : public expression
{
protected:
    expression *expr1, *expr2;
    map<string, id_attributes> rules;
    string op;

    binary_expression(expression* expr1, expression* expr2, int position, string op) : expression(position)
    {
        this->expr1 = expr1;
        this->expr2 = expr2;
        this->op = op;
        lvalue = false;
    }

    virtual id_attributes get_type()
    {
        id_attributes expr1_type = expr1->get_type();
        id_attributes expr2_type = expr2->get_type();

        if(expr1_type.semantic_fail || expr2_type.semantic_fail) return expr1_type;
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
};

#endif // BINARY_EXPRESSION