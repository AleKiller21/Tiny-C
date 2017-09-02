#include "id_expression.h"

string id_expression::to_string()
{
   return lexeme + " ";
}

string id_expression::get_lexeme()
{
    return lexeme;
}