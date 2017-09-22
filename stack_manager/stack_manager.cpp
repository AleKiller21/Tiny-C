#include "stack_manager.h"

stack_manager::stack_manager()
{
    displacement = 0;
    current_byte_offset = 0;
}

bool stack_manager::is_argument(string id)
{
    return vars[id].is_argument;
}

int stack_manager::get_var_offset(string id)
{
    return vars[id].byte_offset;
}

string stack_manager::get_var_type(string id)
{
    return vars[id].asm_type;
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

string stack_manager::store_array_base_address_from_arguments(string reg, string id)
{
    stack_entry entry = vars[id];   
    return "\tsw " + reg + ", " + to_string(entry.byte_offset) + "($fp)\n";
}

string stack_manager::load_array_base_address_from_arguments(string reg, string id)
{
    stack_entry entry = vars[id];   
    return "\tlw " + reg + ", " + to_string(entry.byte_offset) + "($fp)\n";
}

string stack_manager::load_from_array(string reg, string id, int offset)
{
    stack_entry entry = vars[id];    

    if(entry.is_argument)
    {
        string code = "\tlw " + reg + ", " + to_string(entry.byte_offset) + "($fp)\n";
        if(entry.asm_type == WORD)
        {
            code += "\taddi " + reg + ", " + reg + ", " + std::to_string(offset * 4) + "\n";
            code += "\tlw " + reg + ", (" + reg + ")\n";
        }

        else
        {
            code += "\taddi " + reg + ", " + reg + ", " + std::to_string(offset) + "\n";
            code += "\tlb " + reg + ", (" + reg + ")\n";
        }

        return code;
    }

    else
    {
        if(entry.asm_type == WORD) return "\tlw " + reg + ", " + to_string(entry.byte_offset + offset * 4) + "($fp)\n";

        return "\tlb " + reg + ", " + to_string(entry.byte_offset + offset) + "($fp)\n";
    }
}

string stack_manager::store_into_array(string reg, string id, int offset)
{
    stack_entry entry = vars[id];    

    if(entry.is_argument)
    {
        string code = "\tlw " + reg + ", " + to_string(entry.byte_offset) + "($fp)\n";
        if(entry.asm_type == WORD)
        {
            code += "\taddi " + reg + ", " + reg + ", " + std::to_string(offset * 4) + "\n";
            code += "\tsw " + reg + ", (" + reg + ")\n";
        }

        else
        {
            code += "\taddi " + reg + ", " + reg + ", " + std::to_string(offset) + "\n";
            code += "\tsb " + reg + ", (" + reg + ")\n";
        }

        return code;
    }

    else
    {
        if(entry.asm_type == WORD) return "\tsw " + reg + ", " + to_string(entry.byte_offset + offset * 4) + "($fp)\n";
            
        return "\tsb " + reg + ", " + to_string(entry.byte_offset + offset) + "($fp)\n";
    }
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