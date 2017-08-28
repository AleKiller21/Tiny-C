#ifndef FUNCTION_DECLARATOR
#define FUNCTION_DECLARATOR

#include "../declarator.h"
#include "../parameter_list/parameter_list.h"

class function_declarator : public declarator
{
private:
    declarator* decl;
    parameter_list* params;

public:
    function_declarator(int position, declarator* decl, parameter_list* params) : declarator(position)
    {
        this->decl = decl;
        this->params = params;
    }

    string to_string();
    // string generate_mips();
    // void validate_semantic();
};

#endif // FUNCTION_DECLARATOR