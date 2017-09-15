#include "stack_manager.h"

int stack_manager::get_var_offset(string id)
{
    return vars[id].byte_offset;
}

string stack_manager::load_from_var(string reg, string id)
{
    stack_entry entry = vars[id];    
    if(entry.asm_type == WORD) return "lw " + reg + ", " + to_string(entry.byte_offset) + "($sp)\n";

    return "lb " + reg + ", " + to_string(entry.byte_offset) + "($sp)\n";
}

string stack_manager::store_into_var(string reg, string id)
{
    stack_entry entry = vars[id];    
    if(entry.asm_type == WORD) return "sw " + reg + ", " + to_string(entry.byte_offset) + "($sp)\n";

    return "sb " + reg + ", " + to_string(entry.byte_offset) + "($sp)\n";
}