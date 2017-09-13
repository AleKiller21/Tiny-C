#include "compiler/compiler.h"
#include "symbol_table/symbol_table.h"
#include "redundancy_manager/redundancy_manager.h"
#include "comp_utils/comp_utils.h"
#include <iostream>

extern int yydebug;
extern int yyparse();

list<external_declaration*> source;
symbol_table sym_table;
redundancy_manager redund_manager;
int declaration_pos = 0;
int declarator_pos = 0;
int semantic_errors = 0;
bool main_flag = false;

int main()
{
    yydebug = 0;
    yyparse();
    compiler comp(source);
    comp.validate_semantic();
    if(!main_flag) comp_utils::show_message("error", "undefined reference to main", 0);
    else if(semantic_errors == 0)
    {
        comp.mark_unnecessary_nodes();
        //comp.generate_code();
    }
}