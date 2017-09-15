#ifndef RETURN_STATEMENT
#define RETURN_STATEMENT

#include "../statement.h"
#include "../../expressions/expression.h"
#include "../../../register_manager/register_manager.h"

extern register_manager reg_manager;

class return_statement : public statement
{
private:
    expression* expr;

public:
    return_statement(int position, expression* expr) : statement(position) { this->expr = expr; }

    string to_string();
    int get_kind();
    string *generate_code(stack_manager *manager);
    void validate_semantic(bool is_loop_statement, bool *has_return);
};

#endif // RETURN_STATEMENT