#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

#include <map>
#include <string>
#include <stdexcept>
#include "../ast/types.h"

using namespace std;

struct symbol
{
    int type;
    bool lvalue;
};

struct scope
{
    map<string, symbol*> symbols;
    scope* outer_scope;
};

class symbol_table
{
private:
    scope* scope_ptr;
    int scope_level;

public:
    symbol_table();
    symbol* get_symbol(string id);
    int get_scope_level();
    int exist_symbol_in_current_scope(string id);
    int add_symbol(string id, symbol* sym);
    void push_scope();
    void pop_scope();
};

#endif // SYMBOL_TABLE