#ifndef DECLARATION
#define DECLARATION

#include "../declarator_list/declarator_list.h"
#include "../../types.h"

class declaration
{
private:
    declarator_list* declarators;
    int type;

public:
    declaration(declarator_list* decls, int type);
    string to_string();
    // string generate_mips();
    // void validate_semantic();
};

#endif // DECLARATION