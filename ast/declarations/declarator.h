#ifndef DECLARATOR
#define DECLARATOR

#include <stdexcept>
#include "../types.h"
#include "initializer/initializer.h"
#include "../expressions/primary/id/id_expression.h"
#include "../../symbol_table/symbol_table.h"

using namespace std;

extern symbol_table sym_table;

class declarator
{
private:
    int position;

public:
    initializer* init;
    id_expression* id_expr;
    bool pointer;
    int type;

    //virtual string generate_mips() = 0;
    virtual void validate_semantic() = 0;

    virtual string to_string() 
    {
        if(init != NULL) return " = " + init->to_string();
        return "";
    }

    void show_error(string msg)
    {
        fprintf(stderr, "Line %d: error: %s", position, msg.c_str());
    }

protected:
    declarator(id_expression* id, int position)
    {
        this->position = position;
        id_expr = id;
        pointer = false;
        init = NULL;
    }

    string get_id() { return id_expr->get_lexeme(); }
    int get_position() { return position; }
};

#endif // DECLARATOR