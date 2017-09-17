#include "printf_expression.h"

string printf_expression::to_string()
{
    return "printf(" + expr->to_string() + ") ";
}

int printf_expression::get_kind()
{
    return PRINTF_EXPR;
}

id_attributes printf_expression::get_type()
{
    id_attributes expr_type = expr->get_type();
    list<expression*> expressions = ((expression_list*)expr)->get_list();

    if(expr_type.semantic_fail) return expr_type;
    if(expressions.size() > 4)
    {
        comp_utils::show_message("error", "printf max number of arguments is 4", position);
        return { 0, 0, 0, true };
    }
    if(expressions.front()->get_kind() != STRING_EXPR)
    {
        comp_utils::show_message("error", "the first argument of printf must be a string", position);
        return { 0, 0, 0, true };
    }

    vector<string> strs = parse_string();
    if(strs.size() == 1) return { INT, false, SIMPLE, false };
    if(expressions.size() - 1 < strs.size() - 1)
    {
        comp_utils::show_message("error", "the number of arguments for printf is less than the number of formats in the string expression", position);
        return { 0, 0, 0, true };
    }
}

asm_code *printf_expression::generate_code(stack_manager *manager)
{
    vector<string> strs = parse_string();
    list<expression*> expressions = ((expression_list*)expr)->get_list();
    int counter = 0;
    string code;

    for(list<expression*>::iterator it = ++expressions.begin(); it != expressions.end(); it++)
    {
        if(counter >= strs.size() - 1) break;

        string str = strs[counter];
        expression *arg = *it;
        string label = compiler::add_string_literal(str);
        code += "\tla $a0, " + label + "\n";
        code += "\tjal puts\n";
        
        asm_code *expr_code = arg->generate_code(manager);

        //TODO: Considerar aceptar %s
        if(!arg->is_code) code += "\tli $a0, " + std::to_string(expr_code->constant) + "\n";
        else
        {
            code += expr_code->code;
            code += "\tmove $a0, " + expr_code->place + "\n";
            reg_manager.free_register(expr_code->place);
        }

        if(formats[counter++] == CHAR) code += "\tjal put_char\n";
        else code += "\tjal put_udecimal\n";

        delete expr_code;
    }

    string end = strs.back();
    if(end.empty()) {}

    else if(end.size() == 1)
    {
        code += "\tli $a0, " + std::to_string(end[0]) + "\n";
        code += "\tjal put_char\n";
    }

    else
    {
        string label = compiler::add_string_literal(end);
        code += "\tla $a0, " + label + "\n";
        code += "\tjal puts\n";
    }

    code += "\tli $v0, " + std::to_string(expressions.size()) + "\n";

    return new asm_code { code, "$v0", -1 };
}

vector<string> printf_expression::parse_string()
{
    list<expression*> expressions = ((expression_list*)expr)->get_list();
    string str_expr = ((string_expression*)expressions.front())->get_lexeme();
    vector<string> subs;
    int begin = 0, i = 0;

    for(; i < str_expr.size(); i++)
    {
        if(str_expr[i] != '%') continue;
        subs.push_back(str_expr.substr(begin, i - begin));
        begin = i + 2;

        if(str_expr[i + 1] == 'd') formats.push_back(INT);
        else formats.push_back(CHAR);
    }

    subs.push_back(str_expr.substr(begin, i - begin));
    return subs;
}