#ifndef PARAMETER_LIST
#define PARAMETER_LIST

#include "../parameter/parameter_declarator.h"
#include <list>

using namespace std;

class parameter_list
{
private:
    list<parameter_declarator*> params;

public:
    string to_string();
    void add_param(parameter_declarator* param);
    // string generate_mips();
    // void validate_semantic();
};

#endif // PARAMETER_LIST