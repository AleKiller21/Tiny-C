#ifndef ID
#define ID

#include "../../expression.h"
#include <map>

extern map<string, string> data_section;

class id_expression : public expression
{
private:
    string lexeme;
    int kind;

    string choose_load_format(string type);

public:
    bool is_global;
    
    id_expression(string* lexeme, int position) : expression(position)
    {
        this->lexeme = *lexeme;
        delete lexeme;
        lvalue = true;
        is_code = true;
    }
    
    string to_string();
    string *get_operand_id();
    type_attributes get_type();
    int get_kind();
    asm_code *generate_code(stack_manager *manager);
};

#endif // ID