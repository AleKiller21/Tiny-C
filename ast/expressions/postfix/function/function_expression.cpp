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

id_attributes function_expression::get_type()
{
    //TODO: No se puede mandar a llamar la funcion en la que nos encontramos recursivamente porque aun no ha sido agregado a la tabla de simbolos
    id_attributes id_type = id->get_type();
    id_attributes arg_types;
    id_attributes type;

    if(id_type.semantic_fail) return id_type;
    if(id_type.kind != FUNCTION)
    {
        string id_lexeme = id->get_kind() == ID_EXPR ? id->to_string() : "";
        comp_utils::show_message("error", "called object '" + id_lexeme + "' is not a function or function pointer", position);
        return { 0, 0, 0, true };
    }

    symbol *id_sym = sym_table.get_symbol(((id_expression*)id)->get_lexeme());
    vector<id_attributes> attrs = ((function_declarator*)id_sym->decl_ptr)->get_param_types();

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