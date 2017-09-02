
#include "compiler/compiler.h"

extern int yydebug;
extern int yyparse();

list<external_declaration*> source;

int main()
{
    yydebug = 0;
    yyparse();
    compiler comp(source);
    comp.validate_semantic();
    //comp.generate_code();
}