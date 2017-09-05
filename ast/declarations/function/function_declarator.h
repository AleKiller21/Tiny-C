#ifndef FUNCTION_DECLARATOR
#define FUNCTION_DECLARATOR

#include "../declarator.h"
#include "../parameter_list/parameter_list.h"
#include "../../parameter_details.h"
#include "../../../comp_utils/comp_utils.h"
#include <vector>
#include <iostream>

using namespace std;

class function_declarator : public declarator
{
private:
    parameter_list* params;

public:
    function_declarator(int position, string* id, parameter_list* params) : declarator(id, position, FUNCTION)
    {
        this->params = params;
    }

    string to_string();
    vector<parameter_details> get_param_types();
    bool compare_existing_symbol(string id, symbol* sym);
    bool compare_param_types(vector<parameter_details> prev_decl, vector<parameter_details> curr_decl);
    bool validate_params();
    // string generate_mips();
    void validate_semantic();
};

#endif // FUNCTION_DECLARATOR