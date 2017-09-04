#ifndef PARAMETER_LIST
#define PARAMETER_LIST

#include "../declarator.h"
#include <vector>
#include <iostream>

using namespace std;

class parameter_list
{
private:
    list<declarator*> params;

public:
    string to_string();
    vector<string> get_types();
    void add_param(declarator* param);
    // string generate_mips();
    // void validate_semantic();
};

#endif // PARAMETER_LIST