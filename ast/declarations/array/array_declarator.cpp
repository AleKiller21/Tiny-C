#include "array_declarator.h"

string array_declarator::to_string()
{
    if(has_range())
        return get_id() + "[" + index_expr->to_string() + "]" + declarator::to_string();

        return get_id() + "[" + "]" + declarator::to_string();
}

bool array_declarator::has_range()
{
    return index_expr != NULL;
}

int array_declarator::get_size()
{
    return size;
}

void array_declarator::validate_semantic()
{
    string id = get_id();
    symbol* sym = sym_table.exist_symbol_in_current_scope(id);
    is_global = sym_table.get_scope_level() == 0;

    if(!validate_type(id) || !validate_pointer(id) || !validate_range(id)) return;
    if(!validate_existance(id, sym, get_kind())) return;
    if(!validate_initialization()) return;
    if(!set_size()) return;
    
    if(sym == NULL)
    {
        set_stack_displacement();
        bool is_initialized = init != NULL ? true : false;
        sym_table.add_symbol(id, new symbol { type, get_position(), is_initialized , pointer, get_kind(), this, is_global } );
        if(!is_initialized && is_global) redund_manager.push_declaration(id, { declaration_pos, declarator_pos, false, this });
    }

    else if(init != NULL)
    {
        sym_table.replace_symbol(id, new symbol { type, get_position(), true, pointer, get_kind(), this, is_global });
        redund_manager.make_all_removable(id);
        use_default_value = false;
    }

    else if((has_range() && !((array_declarator*)sym->decl_ptr)->has_range()) && !sym->is_initialized)
    {
        sym_table.replace_symbol(id, new symbol { type, get_position(), false, pointer, get_kind(), this, is_global });
        redund_manager.make_all_removable(id);
        redund_manager.push_declaration(id, { declaration_pos, declarator_pos, false, this });
    }

    else redund_manager.push_declaration(id, { declaration_pos, declarator_pos, true, this });
}

bool array_declarator::validate_initialization()
{
    if(init == NULL) return true;

    if(init->list_expr == NULL)
    {
        comp_utils::show_message("error", "invalid initializer", get_position());
        return false;
    }

    list<expression*> init_exprs = init->list_expr->get_list();
    type_attributes decl_type = { type, false, SIMPLE, false };
    
    for(list<expression*>::iterator it = init_exprs.begin(); it != init_exprs.end(); it++)
    {
        if(!simple_declarator::validate_init_expression(decl_type, *it, get_position())) return false;
    }

    return true;
}

bool array_declarator::validate_type(string id)
{
    if(type == VOID)
    {
        comp_utils::show_message("error", "declaration of '" + id + "' as array of voids", get_position());
        return false;
    }

    return true;
}

bool array_declarator::validate_pointer(string id)
{
    if(pointer)
    {
        comp_utils::show_message("error", "declaration of array of pointers is not allowed in TinyC", get_position());
        return false;
    }

    return true;
}

bool array_declarator::validate_range(string id)
{
    if(!validate_block_scope_range(id) || !validate_range_type(id)) return false;   
    return true;
}

bool array_declarator::validate_block_scope_range(string id)
{
    if(!is_global && !has_range() && init == NULL)
    {
        comp_utils::show_message("error", "array size missing in '" + id + "'", get_position());
        return false;
    }

    return true;
}

bool array_declarator::validate_range_type(string id)
{
    if(!has_range()) return true;
    
    type_attributes index_type = index_expr->get_type();
    if(index_type.semantic_fail) return false;
    if(index_expr->get_lvalue() && is_global)
    {
        comp_utils::show_message("error", "variably modified '" + get_id() + "' at file scope", get_position());
        return false;
    }
//index_type.type != INT && index_type.type != CHAR
    if((index_expr->get_kind() != INT_EXPR && index_expr->get_kind() != CHAR_EXPR) || index_type.pointer)
    {
        comp_utils::show_message("error", "size of '" + id + "' has non-integer type", get_position());
        return false;
    }

    return true;
}

string* array_declarator::generate_code(stack_manager *manager)
{
    string code;

    if(redund_declaration) return new string();
    if(is_global)
    {
        generate_global_code(manager);
        return new string();
    }
    
    return generate_local_code(manager);
}

void array_declarator::generate_global_code(stack_manager *manager)
{
    string asm_type = comp_utils::determine_asm_type(type, pointer);

    if(!has_range() && init == NULL) compiler::add_data_section(get_id(), asm_type, "0");

    else if(has_range() && init == NULL)
    {
        string value = "0";
        for(int i = 0; i < size - 1; i++) value += ", 0";

        compiler::add_data_section(get_id(), asm_type, value);
    }

    else if(!has_range() && init != NULL)
    {
        string str_value;
        list<expression*> init_exprs = init->list_expr->get_list();
        
        generate_code_global_initialization(manager, &init_exprs, &str_value);
        compiler::add_data_section(get_id(), asm_type, str_value);
    }

    else if(has_range() && init != NULL)
    {
        string str_value;
        list<expression*> init_exprs = init->list_expr->get_list();

        generate_code_global_initialization(manager, &init_exprs, &str_value);
        if(size > init_exprs.size())
        {
            for(int i = 0; i < size - init_exprs.size(); i++) str_value += ", 0";
        }

        compiler::add_data_section(get_id(), asm_type, str_value);
    }
}

string *array_declarator::generate_local_code(stack_manager *manager)
{
    return new string();
}

stack_entry *array_declarator::create_stack_entry()
{
    string asm_type;
    int displacement;
    
    if(type == INT) { asm_type = WORD; displacement = 4 * size; }
    if(type == CHAR) { asm_type = BYTE; displacement = size; }

    return new stack_entry { asm_type, get_id(), -1, displacement };
}

void array_declarator::generate_code_global_initialization(stack_manager *manager, list<expression*> *init_exprs, string *str_value)
{
    for(list<expression*>::iterator it = init_exprs->begin(); it != init_exprs->end(); it++)
    {
        if((*it)->is_code)
        {
            comp_utils::show_message("error", "Global arrays can not be initialized with modifiable values. Don't run the file", get_position());
            return;
        }

        asm_code *value = (*it)->generate_code(manager);
        *str_value += std::to_string(value->constant) + ", ";
        delete value;
    }

    str_value->erase(str_value->size() - 2);
}

bool array_declarator::set_size()
{
    if(!has_range() && init == NULL) { size = 1; }

    else if(has_range() && init == NULL)
        size = index_expr->get_kind() == INT_EXPR ? ((int_expression*)index_expr)->get_value() : ((char_expression*)index_expr)->get_value();

    else if(!has_range() && init != NULL) size = init->list_expr->get_list().size();

    else if(has_range() && init != NULL)
    {
        string str_value;
        list<expression*> init_exprs = init->list_expr->get_list();
        size = index_expr->get_kind() == INT_EXPR ? ((int_expression*)index_expr)->get_value() : ((char_expression*)index_expr)->get_value();

        if(size < init_exprs.size())
        {
            comp_utils::show_message("error", "the number of elements in initializer is greater than the established size of the array", get_position());
            return false;
        }
    }

    return true;
}

void array_declarator::set_stack_displacement()
{
    if(is_global) return;
    
    if (type == INT) compiler::increase_stack_displacement(size * 4);
    else compiler::increase_stack_displacement(size);
}