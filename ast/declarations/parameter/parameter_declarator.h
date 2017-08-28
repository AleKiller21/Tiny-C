#ifndef PARAMETER_DECLARATOR
#define PARAMETER_DECLARATOR

#include "../declarator.h"

class parameter_declarator : public declarator
{
private:
    declarator* decl;

public:
    parameter_declarator(declarator* decl, int type, int position) : declarator(position)
    {
        this->decl = decl;
        this->type = type;
    }

    string to_string();
    // string generate_mips();
    // void validate_semantic();
};

#endif // PARAMETER_DECLARATOR