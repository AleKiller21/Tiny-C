
#include "compiler/compiler.h"
#include "symbol_table/symbol_table.h"

extern int yydebug;
extern int yyparse();

list<external_declaration*> source;
symbol_table sym_table;

int main()
{
    yydebug = 0;
    yyparse();
    compiler comp(source);
    comp.validate_semantic();
    //comp.generate_code();
}