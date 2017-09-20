#include "register_manager.h"

register_manager::register_manager()
{
    temp_regs = { {"$t0", true}, {"$t1", true}, {"$t2", true}, {"$t3", true}, 
    {"$t4", true}, {"$t5", true}, {"$t6", true}, {"$t7", true},
    {"$t8", true}, {"$t9", true} };

    saved_regs = { {"$s0", true}, {"$s1", true}, {"$s2", true}, {"$s3", true}, 
    {"$s4", true}, {"$s5", true}, {"$s6", true}, {"$s7", true} };

    sregs_used = 0;
}

int register_manager::get_sregs_used()
{
    return sregs_used;
}

string register_manager::get_register(bool preserved)
{
    map<string, bool>::iterator it = preserved ? saved_regs.begin() : temp_regs.begin();
    map<string, bool>::iterator end = preserved ? saved_regs.end() : temp_regs.end();

    for(; it != end; it++)
    {
        if(it->second)
        {
            it->second = false;
            if(!preserved) return it->first;

            try { sregs_asked.at(it->first); }

            catch(out_of_range)
            {
                sregs_used++;
                sregs_asked[it->first] = it->first;
            }       
            
            return it->first;
        }
    }

    return "";
}

void register_manager::free_register(string reg)
{
    try 
    {
        if(reg[1] == 't') temp_regs.at(reg) = true;
        else saved_regs.at(reg) = true;
    }

    catch(out_of_range) {}
}

void register_manager::reset_sregisters()
{
    sregs_used = 0;

    sregs_asked.clear();
    for(map<string, bool>::iterator it = saved_regs.begin(); it != saved_regs.end(); it++)
        it->second = true;
}