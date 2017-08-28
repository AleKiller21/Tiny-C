#ifndef INITIALIZER
#define INITIALIZER

#include "../../expressions/expression_list/expression_list.h"

class initializer
{
public:
    expression* single_expr;
    expression_list* list_expr;

    initializer(expression* single_expr, expression_list* list_expr);
    string to_string();
};

#endif // INITIALIZER