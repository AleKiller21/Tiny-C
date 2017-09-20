#ifndef STATEMENT_LIST
#define STATEMENT_LIST

#include <list>
#include "../statement.h"

class statement_list : public statement
{
private:
    list<statement*> statements;

public:
    statement_list(int position) : statement(position) {}

    string to_string();
    int get_kind();
    void add_statement(statement* stmt);
    string *generate_code(stack_manager *manager, string nearest_loop, string nearest_loop_end);
    void validate_semantic(bool is_loop_statement, bool *has_return);
};

#endif // STATEMENT_LIST