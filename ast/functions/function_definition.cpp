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

    return str + decl->to_string() + "\n" + block->to_string();
}

void function_definition::validate_semantic()
{
    string id = decl->get_id();
    symbol* sym = sym_table.exist_symbol_in_current_scope(id);

    if(decl->get_kind() != FUNCTION)
    {
        comp_utils::show_message("error", "Wrong definition of function '" + id + "'", decl->get_position());
        return;
    }

    if(decl->type == VOID && decl->pointer)
    {
        comp_utils::show_message("error", "TinyC does not allows the use of functions returning void*", decl->get_position());
        return;
    }

    if(sym == NULL)
    {
        if(!id.compare("main")) main_flag = true;
        
        sym_table.add_symbol(id, new symbol { type, decl->get_position(), true , decl->pointer, decl->get_kind(), decl } );
        validate_block_semantic();
        return;
    }

    if(!((function_declarator*)decl)->compare_existing_symbol(id, sym))
    {
        validate_block_semantic();
        return;
    }

    if(sym->is_initialized)
    {
        comp_utils::show_message("error", "redefinition of '" + id + "'", decl->get_position());
        return;
    }

    sym_table.replace_symbol(id, new symbol { type, decl->get_position(), true , decl->pointer, decl->get_kind(), decl });
    redund_manager.make_all_removable(id);
    validate_block_semantic();
}

void function_definition::validate_block_semantic()
{
    bool has_return_stmt = false;

    sym_table.push_scope();
    ((function_declarator*)decl)->validate_params();
    block->validate_semantic(false, &has_return_stmt);

    if(has_return_stmt) cout << decl->get_id() + " has return\n" << endl;
    if(!has_return_stmt)
    {
        block->push_statement(new return_statement(0, NULL));
        cout << "return statement added to function " + decl->get_id() + "\n" << endl;
    }
}