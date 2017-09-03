#ifndef REDUNDANCY_MANAGER
#define REDUNDANCY_MANAGER

#include <list>
#include <stdexcept>
#include <map>
#include <string>

using namespace std;

class declarator;

struct redundant_declaration
{
    int declaration_pos;
    int declarator_pos;
    bool removable;
    declarator* decl_ptr;
};

class redundancy_manager
{

public:
    map<string, list<redundant_declaration>* > redundant_declarations;
    
    void push_declaration(string key, redundant_declaration decl);
    void make_all_removable(string key);
};

#endif // REDUNDANCY_MANAGER