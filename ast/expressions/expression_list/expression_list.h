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
    void add_expression(expression* expr);
    string to_string();
    // string get_type();
    // string generate_mips();
};

#endif // EXPRESSION_LIST