#ifndef ID
#define ID

#include "../../expression.h"
#include <map>

extern map<string, string> data_section;

class id_expression : public expression
{
private:
    string lexeme;

public:
    id_expression(string* lexeme, int position) : expression(position)
    {
        this->lexeme = *lexeme;
        delete lexeme;
        lvalue = true;
        is_code = true;
    }
    
    string to_string();
    string get_lexeme();
    id_attributes get_type();
    int get_kind();
    asm_code *generate_code(stack_manager *manager);
};

#endif // ID