#include "compiler/compiler.h"
#include "symbol_table/symbol_table.h"
#include "redundancy_manager/redundancy_manager.h"
#include <iostream>

extern int yydebug;
extern int yyparse();

list<external_declaration*> source;
symbol_table sym_table;
redundancy_manager redund_manager;
int declaration_pos = 0;
int declarator_pos = 0;
int semantic_errors = 0;

int main()
{
    yydebug = 0;
    yyparse();
    compiler comp(source);
    comp.validate_semantic();
    //if(semantic_errors == 0) comp.generate_code();
}