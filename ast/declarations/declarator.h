#ifndef DECLARATOR
#define DECLARATOR

#include <stdexcept>
#include "../types.h"
#include "initializer/initializer.h"
#include "../expressions/primary/id/id_expression.h"
#include "../../symbol_table/symbol_table.h"
#include "../../redundancy_manager/redundancy_manager.h"
#include "../../comp_utils/comp_utils.h"
#include "../id_kind.h"

using namespace std;

extern symbol_table sym_table;
extern redundancy_manager redund_manager;
extern int declaration_pos;
extern int declarator_pos;

class declarator
{
private:
    int position;
    int kind;
    string id;

public:
    initializer* init;
    bool pointer;
    bool redund_declaration;
    int type;

    //virtual string generate_mips() = 0;
    virtual void validate_semantic() = 0;

    virtual string to_string() 
    {
        if(init != NULL) return " = " + init->to_string();
        return "";
    }    

    string get_id() { return id; }
    int get_position() { return position; }
    int get_default_value() { return 0; }
    int get_kind() { return kind; }

protected:
    declarator(string* id, int position, int kind)
    {
        this->position = position;
        this->id = *id;
        this->kind = kind;
        pointer = false;
        redund_declaration = false;
        init = NULL;

        delete id;
    }

    virtual bool validate_existance(string id, symbol* sym, int category)
    {
        if(sym == NULL) return true;
    
        if(sym->is_initialized && init != NULL)
        {
            comp_utils::show_message("error", "Redefinition of '" + id + "'\nprevious definition was found at line " + 
                std::to_string(sym->lineno), get_position());
            return false;
        }

        if(sym->category != category)
        {
            comp_utils::show_message("error", "'" + id + "' redeclared as different kind of symbol", get_position());
            return false;
        }

        if(sym->type != type || sym->pointer != pointer)
        {
            comp_utils::show_message("error", "conflicting types for '" + id + "'\nprevious declaration was found at line " +
                std::to_string(sym->lineno), get_position());
            return false;
        }
    
        if(sym_table.get_scope_level() > 0)
        {
            comp_utils::show_message("error", "Redeclaration of '" + id + "'\nprevious declaration was found at line " +
                std::to_string(sym->lineno), get_position());
            return false;
        }
    
        if(sym_table.get_scope_level() == 0 && init == NULL) return true;
        return true;
    }
};

#endif // DECLARATOR