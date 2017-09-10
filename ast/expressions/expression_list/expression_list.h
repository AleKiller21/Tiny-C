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
    id_attributes get_type();
    // string generate_mips();
};

#endif // EXPRESSION_LIST