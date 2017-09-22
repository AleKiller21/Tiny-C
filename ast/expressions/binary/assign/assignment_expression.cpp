#include "assignment_expression.h"

string assignment_expression::to_string()
{
    return expr1->to_string() + "= " + expr2->to_string();
}

string assignment_expression::choose_store_format(string type)
{
    if(type == WORD) return "\tsw ";
    return "\tsb ";
}

int assignment_expression::get_kind()
{
    return ASSIGN_EXPR;
}

map<string, type_attributes> assignment_expression::get_rules()
{
    return rules;
}

type_attributes assignment_expression::get_type()
{
    type_attributes expr1_type = expr1->get_type();
    type_attributes expr2_type = expr2->get_type();

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

asm_code *assignment_expression::generate_code(stack_manager *manager)
{
    asm_code *expr2_code = expr2->generate_code(manager);
    string code;
    string sreg;

    if(!expr2->is_code)
    {
        sreg = reg_manager.get_register(true);
        code += manager->save_sregister(sreg);
        code += "\tli " + sreg + ", " + std::to_string(expr2_code->constant) + "\n";
    }

    else
    {
        code += expr2_code->code;
        reg_manager.free_register(expr2_code->place);
        sreg = reg_manager.get_register(true);
        code += manager->save_sregister(sreg);
        code += "\tmove " + sreg + ", " + expr2_code->place + "\n";
    }

    if(expr1->get_kind() == ID_EXPR)
    {
        id_expression *id_expr = (id_expression*)expr1;
        string *id = id_expr->get_operand_id();
        if(id_expr->is_global)
            code += choose_store_format(data_section[*id]) + sreg + ", " + *id + "\n";
        
        else code += manager->store_into_var(sreg, *id);
        delete id;
    }

    else if(expr1->get_kind() == ARRAY_EXPR)
    {
        asm_code *array_store = ((array_expression*)expr1)->generate_array_expression_code(manager, sreg, "store");
        code += array_store->code;
        delete array_store;
    }

    delete expr2_code;
    return new asm_code { code, sreg, -1 };
}