#ifndef DECLARATION
#define DECLARATION

#include "../declarator_list/declarator_list.h"
#include "../external_declaration.h"
#include "../../../stack_manager/stack_manager.h"

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
    string *generate_code(stack_manager *manager);
    list<stack_entry> *create_stack_entries();
    void validate_semantic();
};

#endif // DECLARATION