#ifndef DECLARATOR_LIST
#define DECLARATOR_LIST

#include "../declarator.h"
#include <list>

using namespace std;

class declarator_list
{
private:
    list<declarator*> declarators;

public:
    void add_declarator(declarator* decl);
    void validate_semantic();
    // string generate_mips();
    string to_string();
    void set_type(int type);
};

#endif // DECLARATOR_LIST