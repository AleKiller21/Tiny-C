#ifndef ID
#define ID

#include "../../expression.h"
#include "../../../../comp_utils/comp_utils.h"
#include "../../../../symbol_table/symbol_table.h"

extern symbol_table sym_table;

class id_expression : public expression
{
private:
    string lexeme;

public:
    id_expression(string* lexeme, int position) : expression(position)
    {
        this->lexeme = *lexeme;
        lvalue = true;
        delete lexeme;
    }
    
    string to_string();
    string get_lexeme();
    string get_type();
    int get_kind();
    // string generate_mips();
};

#endif // ID