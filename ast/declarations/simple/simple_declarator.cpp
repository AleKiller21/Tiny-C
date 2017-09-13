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
        bool is_initialized = init != NULL ? true : false;
        sym_table.add_symbol(id, new symbol { type, get_position(), is_initialized , pointer, get_kind(), this } );
        if(!is_initialized) redund_manager.push_declaration(id, { declaration_pos, declarator_pos, false, this });
    }

    else if(init != NULL)
    {
        sym_table.replace_symbol(id, new symbol { type, get_position(), true, pointer, get_kind(), this });
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

bool simple_declarator::validate_init_expression(id_attributes decl_type, expression* expr, int decl_position)
{
    if(sym_table.get_scope_level() == 0 && expr->get_lvalue())
    {
        comp_utils::show_message("error", "initializer element is not constant", decl_position);
        return false;
    }

    id_attributes expr_type = expr->get_type();
    if(expr_type.semantic_fail) return false;

    assignment_expression *assign_expr = new assignment_expression(NULL, NULL, 0);
    map<string, id_attributes> rules = assign_expr->get_rules();
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