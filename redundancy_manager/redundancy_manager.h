#ifndef REDUNDANCY_MANAGER
#define REDUNDANCY_MANAGER

#include "../ast/declarations/declarator.h"
#include <list>
#include <stdexcept>

struct redundant_declaration
{
    int declaration_pos;
    int declarator_pos;
    bool removable;
    declarator* decl_ptr;
};

class redundancy_manager
{
private:
    map<string, list<redundant_declaration>* > redundant_declarations;

public:
    void push_declaration(string key, redundant_declaration decl);
    void make_all_removable(string key);
};

#endif // REDUNDANCY_MANAGER