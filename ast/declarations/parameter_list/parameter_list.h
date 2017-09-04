#ifndef PARAMETER_LIST
#define PARAMETER_LIST

#include "../declarator.h"
#include "../../parameter_details.h"
#include <vector>
#include <iostream>

using namespace std;

class parameter_list
{
private:
    list<declarator*> params;

public:
    string to_string();
    vector<parameter_details> get_types();
    void add_param(declarator* param);
    // string generate_mips();
    // void validate_semantic();
};

#endif // PARAMETER_LIST