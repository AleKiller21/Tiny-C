#ifndef EXPRESSION_LIST
#define EXPRESSION_LIST

#include "../expression.h"
#include <list>

using namespace std;

class expression_list : public expression
{
private:
    list<expression*> expressions;

public:
    expression_list(int position) : expression(position) {}
    
    void add_expression(expression* expr);
    string to_string();
    int get_kind();
    list<expression*> get_list();
    type_attributes get_type();
    asm_code *generate_code(stack_manager *manager);
};

#endif // EXPRESSION_LIST