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
        
        stack_displacements.push_back(0);
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

    sym_table.replace_symbol(id, new symbol { type, decl->get_position(), true , decl->pointer, decl->get_kind(), decl, true });
    stack_displacements.push_back(0);
    validate_block_semantic();
}

void function_definition::validate_block_semantic()
{
    bool has_return_stmt = false;

    sym_table.push_scope();
    ((function_declarator*)decl)->validate_params();
    block->validate_semantic(false, &has_return_stmt);

    if(!has_return_stmt) block->push_statement(new return_statement(0, NULL));
}

string* function_definition::generate_code()
{
    string code;
    string stack_setup = setup_stack() + map_arguments_to_stack();
    string main_prologue = "\tli $a0, BRIGHT_WHITE\n\tli $a1, BLACK\n\tjal set_color\n\tjal clear_screen\n\n";
    string *func_header = decl->generate_code(stck_manager);
    string *block_code = block->generate_code(stck_manager, "", "");

    if(!decl->get_id().compare("main")) code = *func_header + stack_setup + main_prologue + *block_code;
    else code = *func_header + stack_setup + *block_code;

    delete func_header;
    delete block_code;
    delete stck_manager;

    stack_displacements_iterator++;
    return new string(code);
}

string function_definition::setup_stack()
{
    stck_manager->displacement = stack_displacements[stack_displacements_iterator];

    if(stck_manager->displacement % 4 != 0) stck_manager->displacement = (stck_manager->displacement / 4 + 1) * 4;
    stck_manager->displacement += 8;

    string code = "\taddi $sp, $sp, -" + std::to_string(stck_manager->displacement) + "\n";
    code += "\tsw $fp, " + std::to_string(stck_manager->displacement - 4) + "($sp)\n";
    code += "\tsw $ra, " + std::to_string(stck_manager->displacement - 8) + "($sp)\n";
    code += "\tmove $fp, $sp\n\n";

    return code;
}

string function_definition::map_arguments_to_stack()
{
    list<declarator*> params = ((function_declarator*)decl)->get_params();
    string code;
    bool is_word;
    int size;
    int counter = 0;
    
    for(list<declarator*>::iterator it = params.begin(); it != params.end(); it++)
    {
        stack_entry *arg_entry = (*it)->create_stack_entry();
        arg_entry->is_argument = true;
        string id = arg_entry->var_id;
        stck_manager->vars[id] = *arg_entry;

        is_word = stck_manager->vars[id].asm_type == WORD || stck_manager->vars[id].is_array;
        size = is_word ? 4 : 1;

        if(is_word)
            while(stck_manager->current_byte_offset % 4 != 0) stck_manager->current_byte_offset++;

        stck_manager->vars[id].byte_offset = stck_manager->current_byte_offset;

        if(stck_manager->vars[id].is_array) code += stck_manager->store_array_base_address_from_arguments("$a" + std::to_string(counter++), id);
        else code += stck_manager->store_into_var("$a" + std::to_string(counter++), id);
        
        stck_manager->current_byte_offset += size;

        delete arg_entry;
    }

    return code;
}