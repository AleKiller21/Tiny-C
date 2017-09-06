#ifndef STATEMENT
#define STATEMENT

#include <cstdio>
#include <stdexcept>
#include <string>
#include "../../symbol_table/symbol_table.h"

extern symbol_table sym_table;

#define BLOCK_STMT      1
#define BREAK_STMT      2
#define CONTINUE_STMT   3
#define EXPRESSION_STMT 4
#define FOR_STMT        5
#define IF_STMT         6
#define LIST_STMT       7
#define RETURN_STMT     8
#define WHILE_STMT      9

using namespace std;

class statement
{
private:
    int position;

public:
    statement(int position) { this->position = position; }

    virtual void validate_semantic() = 0;
    virtual string generate_mips() { throw "function not yet implemented. "; }
    virtual string to_string() = 0;
    virtual int get_kind() = 0;

    void show_error(const char* msg)
    {
        fprintf(stderr, "Line %d: error: %s", position, msg);
    }
};

#endif // STATEMENT