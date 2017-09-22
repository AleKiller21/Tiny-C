#include "simple_declarator.h"

string simple_declarator::to_string()
{
    if(pointer) return "*" + get_id() + declarator::to_string();
    return get_id() + declarator::to_string();
}

void simple_declarator::validate_semantic()
{
    string id = get_id();
    symbol* sym = sym_table.exist_symbol_in_current_scope(id);
    is_global = sym_table.get_scope_level() == 0;

    if(type == VOID)
    {
        comp_utils::show_message("error", "variable or field '" + id + "' declared void", get_position());
        return;
    }
    
    if(!validate_existance(id, sym, get_kind())) return;
    if(!validate_initialization()) return;

    if(sym == NULL)
    {
        if(!is_global) compiler::increase_stack_displacement(4);
        
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

    else if(init == NULL)
        redund_manager.push_declaration(id, { declaration_pos, declarator_pos, true, this });
}

bool simple_declarator::validate_initialization()
{
    if(init == NULL) return true;
    if(init->list_expr != NULL)
    {
        list<expression*> expressions = init->list_expr->get_list();
        if(expressions.size() > 1)
        {
            comp_utils::show_message("warning", "excess elements in scalar initializer", get_position());
            init->single_expr = expressions.front();
            for(list<expression*>::iterator it = ++expressions.begin(); it != expressions.end(); it++) delete *it;
            delete init->list_expr;
            init->list_expr = NULL;
        }

        else
        {
            init->single_expr = expressions.front();
            delete init->list_expr;
            init->list_expr = NULL;
        }
    }
    
    return simple_declarator::validate_init_expression({ type, pointer, SIMPLE, false }, init->single_expr, get_position());
}

bool simple_declarator::validate_init_expression(type_attributes decl_type, expression* expr, int decl_position)
{
    //TODO: validar que no acepte esto en el contexto global: int num1; int num2 = num2 = 5;
    if(sym_table.get_scope_level() == 0 && expr->get_lvalue())
    {
        comp_utils::show_message("error", "initializer element is not constant", decl_position);
        return false;
    }

    type_attributes expr_type = expr->get_type();
    if(expr_type.semantic_fail) return false;

    assignment_expression *assign_expr = new assignment_expression(NULL, NULL, 0);
    map<string, type_attributes> rules = assign_expr->get_rules();
    bool success = false;

    string op1 = comp_utils::id_attrs_to_string(decl_type);
    string op2 = comp_utils::id_attrs_to_string(expr_type);
    
    try
    {
        string entry = op1 + "," + op2;
        rules.at(entry);
        success = true;
    }

    catch(out_of_range)
    {
        string entries = " (have '" + op1 + "' and '" + op2 + "')"; 
        comp_utils::show_message("error", "invalid operands to binary =" + entries, decl_position);
    }
    
    delete assign_expr;
    return success;    
}

string* simple_declarator::generate_code(stack_manager *manager)
{
    //TODO: averiguar como almacenar apuntadores en el data section
    string code;

    if(redund_declaration) return new string();
    if(is_global)
    {
        generate_global_code();
        return new string();
    }
    
    return generate_local_code(manager);
}

string* simple_declarator::generate_local_code(stack_manager *manager)
{
    if(init == NULL) return new string();
    
    asm_code *expr_init_code = init->single_expr->generate_code(manager);
    string code;

    if(!init->single_expr->is_code)
    {
        string treg = reg_manager.get_register(false);
        code = "\tli " + treg + ", " + std::to_string(expr_init_code->constant) + "\n";
        code += manager->store_into_var(treg, get_id());
        reg_manager.free_register(treg);

        delete expr_init_code;
        return new string(code);
    }

    code = expr_init_code->code;
    code += manager->store_into_var(expr_init_code->place, get_id());
    reg_manager.free_register(expr_init_code->place);

    delete expr_init_code;
    return new string(code);
}

void simple_declarator::generate_global_code()
{
    string asm_type = comp_utils::determine_asm_type(type, pointer);

    if(use_default_value) compiler::add_data_section(get_id(), asm_type, "0");

    else
    {
        asm_code *expr_init_code = init->single_expr->generate_code(NULL);
        compiler::add_data_section(get_id(), asm_type, std::to_string(expr_init_code->constant));

        delete expr_init_code;
    }
}

stack_entry* simple_declarator::create_stack_entry()
{
    string asm_type;
    int size;
    
    if(pointer || type == INT) { asm_type = WORD; size = 4; }
    if(type == CHAR) { asm_type = BYTE; size = 1; }

    return new stack_entry { asm_type, get_id(), -1, size, false, false };
}