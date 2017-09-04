#ifndef FUNCTION_DECLARATOR
#define FUNCTION_DECLARATOR

#include "../declarator.h"
#include "../parameter_list/parameter_list.h"
#include <vector>

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
    vector<string> get_param_types();
    bool compare_existing_symbol(string id, symbol* sym);
    bool compare_param_types(vector<string> prev_decl, vector<string> curr_decl);
    // string generate_mips();
    void validate_semantic();
};

#endif // FUNCTION_DECLARATOR