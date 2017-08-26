#ifndef CAST_EXPRESSION
#define CAST_EXPRESSION

#include "../expression.h"

class cast_expression : public expression
{
private:
    expression* expr;
    string type;
    //TODO: Terminar despues de haber creado nodo para type_name produdction
};

#endif // CAST_EXPRESSION