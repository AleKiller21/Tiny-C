#ifndef DECLARATION
#define DECLARATION

#include "../declarator_list/declarator_list.h"
#include "../external_declaration.h"

class declaration : public external_declaration
{
private:
    declarator_list* declarators;

public:
    declaration(declarator_list* decls, int type) : external_declaration(type, DECL)
    {
        declarators = decls;
        declarators->set_type(type);
    }

    string to_string();
    string *generate_code();
    int calculate_declarators_stack_displacement();
    void validate_semantic();
};

#endif // DECLARATION