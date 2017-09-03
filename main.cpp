
#include "compiler/compiler.h"
#include "symbol_table/symbol_table.h"
#include "redundancy_manager/redundancy_manager.h"

extern int yydebug;
extern int yyparse();

list<external_declaration*> source;
symbol_table sym_table;
redundancy_manager redund_manager;

int main()
{
    yydebug = 0;
    yyparse();
    compiler comp(source);
    comp.validate_semantic();
    //comp.generate_code();
}