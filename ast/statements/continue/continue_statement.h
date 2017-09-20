#ifndef CONTINUE_STATEMENT
#define CONTINUE_STATEMENT

#include "../statement.h"

class continue_statement : public statement
{
public:
    continue_statement(int position) : statement(position) {}
    
    string to_string();
    int get_kind();
    string *generate_code(stack_manager *manager, string nearest_loop, string nearest_loop_end);
    void validate_semantic(bool is_loop_statement, bool *has_return);
};

#endif // CONTINUE_STATEMENT