#ifndef DECLARATOR_LIST
#define DECLARATOR_LIST

#include "../declarator.h"
#include <list>

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
    string *generate_code();
    string to_string();
    int calculate_stack_displacement();
};

#endif // DECLARATOR_LIST