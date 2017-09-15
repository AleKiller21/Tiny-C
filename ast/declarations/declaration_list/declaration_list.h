#ifndef DECLARATION_LIST
#define DECLARATION_LIST

#include "../declaration/declaration.h"
#include "../../../asm_code/asm_code.h"
#include "../../../stack_manager/stack_manager.h"
#include <list>
#include <vector>

using namespace std;

class declaration_list
{
private:
    list<declaration*> declarations;

public:
    void add_declaration(declaration* decl);
    void validate_semantic();
    string *generate_code(stack_manager *manager);
    string to_string();
};

#endif // DECLARATION_LIST