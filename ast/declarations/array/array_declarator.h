#ifndef ARRAY_DECLARATOR
#define ARRAY_DECLARATOR

#include "../declarator.h"
#include "../../expressions/expression.h"
#include "../../expressions/primary/int/int_expression.h"
#include "../../expressions/primary/char/char_expression.h"
#include "../simple/simple_declarator.h"
#include <list>

class array_declarator : public declarator
{
private:
    expression* index_expr;
    int size;
    
    bool validate_initialization();
    bool set_size();
    void set_stack_displacement();
    void generate_global_code(stack_manager *manager);
    void generate_code_global_initialization(stack_manager *manager, list<expression*> *init_exprs, string *str_value);
    void generate_code_local_initialization(stack_manager *manager, list<expression*> *init_exprs, string *code, int *offset);
    string *generate_local_code(stack_manager *manager);

public:
    array_declarator(int position, string* id, expression* index) : declarator(id, position, ARRAY)
    {
        index_expr = index;
    }

    string to_string();
    string *generate_code(stack_manager *manager);
    stack_entry *create_stack_entry();
    void validate_semantic();
    bool has_range();
    bool validate_type(string id);
    bool validate_pointer(string id);
    bool validate_range(string id);
    bool validate_block_scope_range(string id);
    bool validate_range_type(string id);
    int get_size();
};

#endif // ARRAY_DECLARATOR