#ifndef DECLARATOR
#define DECLARATOR

#include <stdexcept>
#include "../types.h"
#include "initializer/initializer.h"
#include "../expressions/primary/id/id_expression.h"
#include "../../symbol_table/symbol_table.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

using namespace std;

extern symbol_table sym_table;

class declarator
{
private:
    int position;
    id_expression* id_expr;

public:
    initializer* init;
    bool pointer;
    int type;

    //virtual string generate_mips() = 0;
    virtual void validate_semantic() = 0;

    virtual string to_string() 
    {
        if(init != NULL) return " = " + init->to_string();
        return "";
    }

    void show_message(string type, string msg)
    {
        if(type == "error")
            fprintf(stderr, "Line %d: " ANSI_COLOR_RED "%s:" ANSI_COLOR_RESET " %s\n", position, type.c_str(), msg.c_str());
        else if(type == "warning")
            fprintf(stderr, "Line %d: " ANSI_COLOR_YELLOW "%s:" ANSI_COLOR_RESET " %s\n", position, type.c_str(), msg.c_str());
    }

protected:
    declarator(id_expression* id, int position)
    {
        this->position = position;
        id_expr = id;
        pointer = false;
        init = NULL;
    }

    virtual bool validate_existance(string id, symbol* sym, int attribute)
    {
        if(sym == NULL) return true;
    
        if(sym->is_initialized && init != NULL)
        {
            show_message("error", "Redefinition of '" + id + "'\nprevious definition was found at line " + std::to_string(sym->lineno));
            return false;
        }

        if(sym->type != type || sym->pointer != pointer || sym->attribute != attribute)
        {
            show_message("error", "conflicting types for '" + id + "'\nprevious declaration was found at line " + std::to_string(sym->lineno));
            return false;
        }
    
        if(sym_table.get_scope_level() > 0)
        {
            show_message("error", "Redeclaration of '" + id + "'\nprevious declaration was found at line " + std::to_string(sym->lineno));
            return false;
        }
    
        if(sym_table.get_scope_level() == 0 && init == NULL) return true;
        return true;
    }

    string get_id() { return id_expr->get_lexeme(); }
    int get_position() { return position; }
};

#endif // DECLARATOR