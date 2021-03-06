#ifndef SIMPLE_DECLARATOR
#define SIMPLE_DECLARATOR

#include "../declarator.h"
#include "../../expressions/primary/id/id_expression.h"
#include "../../expressions/binary/assign/assignment_expression.h"
#include <iostream>
#include <list>
#include <map>

using namespace std;

class simple_declarator : public declarator
{
private:
    bool validate_initialization();
    void generate_global_code();
    string *generate_local_code(stack_manager *manager);

public:
    simple_declarator(string* id, int position) : declarator(id, position, SIMPLE) {}

    string to_string();
    string *generate_code(stack_manager *manager);
    stack_entry *create_stack_entry();
    void validate_semantic();
    static bool validate_init_expression(type_attributes decl_type, expression* expr, int decl_position);
};

#endif // SIMPLE_DECLARATOR