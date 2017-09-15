#ifndef STACK_MANAGER
#define STACK_MANAGER

#include <map>
#include <string>
#include "../asm_code/asm_code.h"

using namespace std;

class stack_manager
{
public:
    map<string, stack_entry> vars;
    int displacement;

    stack_manager();
    
    int get_var_offset(string id);
    string store_into_var(string reg, string id);
    string load_from_var(string reg, string id);
};

#endif // STACK_MANAGER