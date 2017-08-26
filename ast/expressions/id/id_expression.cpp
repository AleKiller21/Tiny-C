#include "id_expression.h"

id_expression::id_expression(string* lexeme)
{
    this->lexeme = *lexeme;
    delete lexeme;
}

string id_expression::to_string()
{
   return string(lexeme) + " ";
}
