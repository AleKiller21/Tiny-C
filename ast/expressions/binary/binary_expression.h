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

    void generate_operands_code(stack_manager *manager, asm_code **expr1_code, asm_code **expr2_code, bool *right_operand_first)
    {
        if(expr2->is_compound_expression())
        {
            *right_operand_first = true;
            *expr2_code = expr2->generate_code(manager);
            *expr1_code = expr1->generate_code(manager);
        }
    
        else
        {
            *expr1_code = expr1->generate_code(manager);
            *expr2_code = expr2->generate_code(manager);
        }
    
        is_code = !(!expr1->is_code && !expr2->is_code);
    }

    asm_code *evaluate_function_expressions(stack_manager *manager, asm_code *expr1_code, asm_code *expr2_code, bool right_operand_first)
    {
        asm_code *expr_code = NULL;
        string code;

        if(!expr1_code->place.compare("$v0") && !expr2_code->place.compare("$v0"))
        {
            string sreg = reg_manager.get_register(true);
            if(right_operand_first)
            {
                code = expr2_code->code;
                code += manager->save_sregister(sreg);
                code += "\tmove " + sreg + ", $v0\n";
                code += expr1_code->code;
                expr2_code->place = sreg;
            }
    
            else
            {
                code = expr1_code->code;
                code += manager->save_sregister(sreg);
                code += "\tmove " + sreg + ", $v0\n";
                code += expr2_code->code;
                expr1_code->place = sreg;
            }
    
            reg_manager.free_register(expr1_code->place);
            reg_manager.free_register(expr2_code->place);
            code += "\tmove $a0, " + expr1_code->place + "\n";
            code += "\tmove $a1, " + expr2_code->place + "\n";
            code += "\tjal mult\n";
            expr_code = new asm_code { code, "$v0", -1 };
        }

        return expr_code;
    }
};

#endif // BINARY_EXPRESSION