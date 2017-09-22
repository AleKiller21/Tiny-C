#ifndef FUNCTION_DECLARATOR
#define FUNCTION_DECLARATOR

#include "../declarator.h"
#include "../parameter_list/parameter_list.h"
#include "../../type_attributes.h"
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

    vector<type_attributes> get_param_types();
    list<declarator*> get_params();
    string to_string();
    string *generate_code(stack_manager *manager);
    bool compare_existing_symbol(string id, symbol* sym);
    bool compare_param_types(vector<type_attributes> prev_decl, vector<type_attributes> curr_decl);
    bool validate_params(bool calculate_stack_displacement);
    void validate_semantic();
};

#endif // FUNCTION_DECLARATOR