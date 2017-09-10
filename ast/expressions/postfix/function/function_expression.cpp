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

id_attributes* function_expression::get_type()
{
    //TODO: No se puede mandar a llamar la funcion en la que nos encontramos recursivamente porque aun no ha sido agregado a la tabla de simbolos
    id_attributes *id_type = id->get_type();
    //id_attributes *arg_types = arguments->get_type();
    id_attributes *type;

    if(id_type == NULL)
    {
        return NULL;
    }

    if(id_type->kind != FUNCTION)
    {
        string id_lexeme = id->get_kind() == ID_EXPR ? id->to_string() : "";
        comp_utils::show_message("error", "called object '" + id_lexeme + "' is not a function or function pointer", position);
        return NULL;
    }

    type = new id_attributes { id_type->type, id_type->pointer, SIMPLE };
    return type;
}