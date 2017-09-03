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
    // string generate_mips();
    // void validate_semantic();
};

#endif // STATEMENT_LIST