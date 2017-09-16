#ifndef DECLARATOR_LIST
#define DECLARATOR_LIST

#include "../declarator.h"
#include "../../../stack_manager/stack_manager.h"
#include <list>
#include <vector>

using namespace std;

extern int declarator_pos;

class declarator_list
{
private:
    list<declarator*> declarators;

public:
    void add_declarator(declarator* decl);
    void validate_semantic();
    void set_type(int type);
    string *generate_code(stack_manager *manager);
    string to_string();
    list<stack_entry> *create_stack_entries();
};

#endif // DECLARATOR_LIST