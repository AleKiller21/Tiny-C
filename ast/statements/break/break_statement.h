#ifndef BREAK_STATEMENT
#define BREAK_STATEMENT

#include "../statement.h"

class break_statement : public statement
{
public:
    break_statement(int position) : statement(position) {}

    string to_string();
    int get_kind();
    // string generate_mips();
    void validate_semantic(bool is_loop_statement, bool *has_return);
};

#endif // BREAK_STATEMENT