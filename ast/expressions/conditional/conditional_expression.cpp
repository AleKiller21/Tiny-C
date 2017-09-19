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

asm_code *conditional_expression::generate_code(stack_manager *manager)
{
    asm_code *eval_expr_code = evaluate_expression->generate_code(manager);
    asm_code *true_expr_code;
    asm_code *false_expr_code;
    asm_code *expr_code;
    string code;
    string treg;

    if(!evaluate_expression->is_code)
    {
        if(eval_expr_code->constant > 0)
        {
            delete eval_expr_code;
            is_code = true_expression->is_code;
            return true_expression->generate_code(manager);
        }

        delete eval_expr_code;
        is_code = false_expression->is_code;
        return false_expression->generate_code(manager);
    }

    is_code = true;
    true_expr_code = true_expression->generate_code(manager);
    false_expr_code = false_expression->generate_code(manager);
    string false_label = lbl_manager.get_free_label("ternary_false");
    string end_label = lbl_manager.get_free_label("ternary_end");

    reg_manager.free_register(eval_expr_code->place);
    code = eval_expr_code->code;
    treg = reg_manager.get_register(false);

    code += "\tbeqz " + eval_expr_code->place + ", " + false_label + "\n";
    if(!true_expression->is_code)
    {
        code += "\tli " + treg + ", " + std::to_string(true_expr_code->constant) + "\n";
        reg_manager.free_register(true_expr_code->place);
        code += "\tj " + end_label + "\n";
    }

    else
    {
        code += true_expr_code->code;
        code += "\tmove " + treg + ", " + true_expr_code->place + "\n";
        reg_manager.free_register(true_expr_code->place);
        code += "\tj " + end_label + "\n";
    }

    code += false_label + ":\n";
    if(!false_expression->is_code)
    {
        code += "\tli " + treg + ", " + std::to_string(false_expr_code->constant) + "\n";
        reg_manager.free_register(false_expr_code->place);
    }

    else
    {
        code += false_expr_code->code;
        code += "\tmove " + treg + ", " + false_expr_code->place + "\n";
        reg_manager.free_register(false_expr_code->place);
    }

    code += end_label + ":\n";
    expr_code = new asm_code { code, treg, -1 };
    delete eval_expr_code, true_expr_code, false_expr_code;
    return expr_code;
}