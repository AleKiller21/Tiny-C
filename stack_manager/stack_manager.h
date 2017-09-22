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
    map<string, string> sregs_asked;
    int current_byte_offset;
    int displacement;

    stack_manager();
    
    bool is_argument(string id);
    int get_var_offset(string id);
    string get_var_type(string id);
    string store_into_var(string reg, string id);
    string load_from_var(string reg, string id);
    string store_array_base_address_from_arguments(string reg, string id);
    string load_array_base_address_from_arguments(string reg, string id);
    string load_from_array(string reg, string id, int offset);
    string store_into_array(string reg, string id, int offset);
    string save_sregister(string sreg);
};

#endif // STACK_MANAGER