#include "function_expression.h"

string function_expression::to_string()
{
    if(arguments != NULL) return id->to_string() + "(" + arguments->to_string() + ")" + " ";
    return id->to_string() + "(" + ")" + " ";
}

int function_expression::get_kind()
{
    return FUNCTION_EXPR;
}

type_attributes function_expression::get_type()
{
    type_attributes id_type = id->get_type();
    type_attributes arg_types;

    if(id_type.semantic_fail) return id_type;
    if(id_type.kind != FUNCTION)
    {
        string id_lexeme = id->get_kind() == ID_EXPR ? id->to_string() : "";
        comp_utils::show_message("error", "called object '" + id_lexeme + "' is not a function or function pointer", position);
        return { 0, 0, 0, true };
    }

    string *id_operand = id->get_operand_id();
    symbol *id_sym = sym_table.get_symbol(*id_operand);
    vector<type_attributes> attrs = ((function_declarator*)id_sym->decl_ptr)->get_param_types();

    delete id_operand;

    if(arguments == NULL && attrs.size() != 0)
    {
        string id_lexeme = id->get_kind() == ID_EXPR ? id->to_string() : "";
        comp_utils::show_message("error", "too few arguments to function '" + id_lexeme + "'", position);
        return { 0, 0, 0, true };
    }

    if(arguments != NULL)
    {
        arg_types = arguments->get_type();
        if(arg_types.semantic_fail) return arg_types;

        list<expression*> arg_exprs = ((expression_list*)arguments)->get_list();
        if(arg_exprs.size() < attrs.size() && attrs.size() != 0)
        {
            string id_lexeme = id->get_kind() == ID_EXPR ? id->to_string() : "";
            comp_utils::show_message("error", "too few arguments to function '" + id_lexeme + "'", position);
            return { 0, 0, 0, true };
        }

        if(arg_exprs.size() > attrs.size() && attrs.size() != 0)
        {
            string id_lexeme = id->get_kind() == ID_EXPR ? id->to_string() : "";
            comp_utils::show_message("error", "too many arguments to function '" + id_lexeme + "'", position);
            return { 0, 0, 0, true };
        }
    }

    return { id_type.type, id_type.pointer, SIMPLE, false };
}

asm_code *function_expression::generate_code(stack_manager *manager)
{
    string code;
    map<int, string> sregs;
    int counter = 0;

    if(arguments == NULL)
    {
        string *routine_id = id->get_operand_id();
        code += "\tjal " + *routine_id + "\n";

        delete routine_id;
        return new asm_code { code, "$v0", -1 };
    }

    list<expression*> args = ((expression_list*)arguments)->get_list();

    for(list<expression*>::iterator it = args.begin(); it != args.end(); it++)
    {
        expression *expr = *it;

        if(expr->get_kind() != FUNCTION_EXPR && expr->get_kind() != PRINTF_EXPR && expr->get_kind() != MULT_EXPR 
            && expr->get_kind() != DIV_EXPR && expr->get_kind() != MOD_EXPR) { counter++; continue; }

        asm_code *arg_code = expr->generate_code(manager);
        string reg = reg_manager.get_register(true);
        code += arg_code->code;
        code += manager->save_sregister(reg);
        code += "\tmove " + reg + ", " + arg_code->place + "\n";
        reg_manager.free_register(arg_code->place);
        sregs[counter++] = reg;

        delete arg_code;
    }

    counter = 0;
    for(list<expression*>::iterator it = args.begin(); it != args.end(); it++)
    {
        try
        {
            string reg = sregs.at(counter);
            code += "\tmove $a" + std::to_string(counter++) + ", " + reg + "\n";
            reg_manager.free_register(reg);
        }

        catch(out_of_range)
        {
            expression *expr = *it;
            asm_code *arg_code = expr->generate_code(manager);
    
            if(!expr->is_code)
                code += "\tli $a" + std::to_string(counter++) + ", " + std::to_string(arg_code->constant) + "\n";
            
            else
            {
                code += arg_code->code;
                reg_manager.free_register(arg_code->place);
                code += "\tmove $a" + std::to_string(counter++) + ", " + arg_code->place + "\n";
            }
    
            delete arg_code;
        }
    }

    string * routine_id = id->get_operand_id();
    code += "\tjal " + *routine_id + "\n";

    delete routine_id;
    return new asm_code { code, "$v0", -1 };
}

string *function_expression::get_operand_id()
{
    return id->get_operand_id();
}