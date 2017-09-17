#include "stack_manager.h"

stack_manager::stack_manager()
{
    displacement = 0;
    current_byte_offset = 0;
}

int stack_manager::get_var_offset(string id)
{
    return vars[id].byte_offset;
}

string stack_manager::load_from_var(string reg, string id)
{
    stack_entry entry = vars[id];    
    if(entry.asm_type == WORD) return "\tlw " + reg + ", " + to_string(entry.byte_offset) + "($fp)\n";

    return "\tlb " + reg + ", " + to_string(entry.byte_offset) + "($fp)\n";
}

string stack_manager::store_into_var(string reg, string id)
{
    stack_entry entry = vars[id];    
    if(entry.asm_type == WORD) return "\tsw " + reg + ", " + to_string(entry.byte_offset) + "($fp)\n";

    return "\tsb " + reg + ", " + to_string(entry.byte_offset) + "($fp)\n";
}

string stack_manager::save_sregister(string sreg)
{
    try
    {
        sregs_asked.at(sreg);
        return "";
    }

    catch(out_of_range)
    {
        sregs_asked[sreg] = sreg;
        string code = "\taddi $sp, $sp, -4\n";
        return code + "\tsw " + sreg + ", ($sp)\n";
    }
}