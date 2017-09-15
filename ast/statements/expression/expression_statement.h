#ifndef EXPRESSION_STATEMENT
#define EXPRESSION_STATEMENT

#include "../statement.h"
#include "../../expressions/expression.h"

extern register_manager reg_manager;

class expression_statement : public statement
{
private:
    expression* expr;

public:
    expression_statement(int position, expression* expr) : statement(position)
    {
        this->expr = expr;
    }

    string to_string();
    int get_kind();
    string *generate_code(stack_manager *manager);
    void validate_semantic(bool is_loop_statement, bool *has_return);
};

#endif // EXPRESSION_STATEMENT