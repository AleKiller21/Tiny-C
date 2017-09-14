#ifndef DECLARATION_LIST
#define DECLARATION_LIST

#include "../declaration/declaration.h"
#include "../../../asm_code/asm_code.h"
#include <list>

using namespace std;

class declaration_list
{
private:
    list<declaration*> declarations;

public:
    void add_declaration(declaration* decl);
    void validate_semantic();
    string *generate_code();
    string to_string();
};

#endif // DECLARATION_LIST