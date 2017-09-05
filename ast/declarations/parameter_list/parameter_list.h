#ifndef PARAMETER_LIST
#define PARAMETER_LIST

#include "../array/array_declarator.h"
#include "../declarator.h"
#include "../../../comp_utils/comp_utils.h"
#include "../../parameter_details.h"
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
    vector<parameter_details> get_types();
    void add_param(declarator* param);
    // string generate_mips();
    bool validate_semantic();
};

#endif // PARAMETER_LIST