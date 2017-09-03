#ifndef DECLARATOR
#define DECLARATOR

#include <stdexcept>
#include "../types.h"
#include "initializer/initializer.h"
#include "../expressions/primary/id/id_expression.h"
#include "../../symbol_table/symbol_table.h"
#include "../colors.h"

using namespace std;

extern symbol_table sym_table;

class declarator
{
private:
    int position;
    string id;

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
            fprintf(stderr, "Line %d: " RED "%s:" RESET " %s\n", position, type.c_str(), msg.c_str());
        else if(type == "warning")
            fprintf(stderr, "Line %d: " YELLOW "%s:" RESET " %s\n", position, type.c_str(), msg.c_str());
    }

protected:
    declarator(string* id, int position)
    {
        this->position = position;
        this->id = *id;
        pointer = false;
        init = NULL;

        delete id;
    }

    virtual bool validate_existance(string id, symbol* sym, int category)
    {
        if(sym == NULL) return true;
    
        if(sym->is_initialized && init != NULL)
        {
            show_message("error", "Redefinition of '" + id + "'\nprevious definition was found at line " + std::to_string(sym->lineno));
            return false;
        }

        if(sym->type != type || sym->pointer != pointer || sym->category != category)
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

    string get_id() { return id; }
    int get_position() { return position; }
};

#endif // DECLARATOR