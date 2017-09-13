#include "register_manager.h"

register_manager::register_manager()
{
    temp_regs = { {"$t0", true}, {"$t1", true}, {"$t2", true}, {"$t3", true}, 
    {"$t4", true}, {"$t5", true}, {"$t6", true}, {"$t7", true},
    {"$t8", true}, {"$t9", true} };

    saved_regs = { 0 };
}

string register_manager::get_free_register(bool preserved)
{
    if(preserved) return "$s" + to_string(saved_regs[saved_regs.size() - 1]++);

    for(map<string, bool>::iterator it = temp_regs.begin(); it != temp_regs.end(); it++)
    {
        if(it->second)
        {
            it->second = false;
            return it->first;
        }
    }

    return "empty";
}

int register_manager::get_sregs_used()
{
    return saved_regs.back();
}

void register_manager::free_register(string reg)
{
    try { temp_regs.at(reg) = true; }
    catch(out_of_range) {}
}

void register_manager::push_sregs()
{
    saved_regs.push_back(0);
}

void register_manager::pop_sregs()
{
    saved_regs.pop_back();
}