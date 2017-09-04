#include "function_definition.h"

string function_definition::to_string()
{
    string str;
    switch(type)
    {
        case INT:
            str = "int ";
            break;
        case CHAR:
            str = "char ";
            break;
        case VOID:
            str = "void ";
            break;
    }

    return str + decl->to_string() + "\n" + stmt->to_string();
}

void function_definition::validate_semantic()
{
    string id = decl->get_id();
    symbol* sym = sym_table.exist_symbol_in_current_scope(id);

    if(decl->get_kind() != FUNCTION)
    {
        decl->show_message("error", "Wrong definition of function '" + id + "'");
        return;
    }

    // if(sym == NULL)
    // {
    //     sym_table.add_symbol(id, new symbol { type, decl->get_position(), true , decl->pointer, decl->get_kind(), decl } );
    //     redund_manager.push_declaration(id, { declaration_pos, declarator_pos, false, decl });
    //     return;
    // }
}