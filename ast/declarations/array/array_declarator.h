#ifndef ARRAY_DECLARATOR
#define ARRAY_DECLARATOR

#include "../declarator.h"
#include "../../expressions/expression.h"
#include "../simple/simple_declarator.h"
#include <list>

class array_declarator : public declarator
{
private:
    expression* index_expr;
    bool validate_initialization();

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
};

#endif // ARRAY_DECLARATOR