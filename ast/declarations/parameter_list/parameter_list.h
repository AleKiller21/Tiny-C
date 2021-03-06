#ifndef PARAMETER_LIST
#define PARAMETER_LIST

#include "../array/array_declarator.h"
#include "../declarator.h"
#include "../../../comp_utils/comp_utils.h"
#include "../../../compiler/compiler.h"
#include "../../type_attributes.h"
#include <vector>
#include <iostream>

using namespace std;

extern symbol_table sym_table;

class parameter_list
{
private:
    list<declarator*> params;

public:
    string to_string();
    vector<type_attributes> get_types();
    list<declarator*> get_params();
    void add_param(declarator* param);
    // string generate_mips();
    bool validate_semantic(bool calculate_stack_displacement);
    int get_params_amount();
};

#endif // PARAMETER_LIST