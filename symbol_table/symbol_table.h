#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

#include <map>
#include <string>
#include <stdexcept>
#include "../ast/types.h"
#include "../ast/id_kind.h"

using namespace std;

class declarator;

struct symbol
{
    int type;
    int lineno;
    bool is_initialized;
    bool pointer;
    int category;
    declarator* decl_ptr;
    bool is_global;
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
    symbol* exist_symbol_in_current_scope(string id);
    int get_scope_level();
    int add_symbol(string id, symbol* sym);
    void replace_symbol(string id, symbol* sym);
    void push_scope();
    void pop_scope();
};

#endif // SYMBOL_TABLE