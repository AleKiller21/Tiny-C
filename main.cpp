#include "compiler/compiler.h"
#include "symbol_table/symbol_table.h"
#include "redundancy_manager/redundancy_manager.h"
#include "register_manager/register_manager.h"
#include "label_manager/label_manager.h"
#include "comp_utils/comp_utils.h"
#include "asm_code/asm_code.h"
#include <iostream>
#include <map>

using namespace std;

extern int yydebug;
extern int yyparse();

list<external_declaration*> source;
symbol_table sym_table;
map<string, string> data_section;

redundancy_manager redund_manager;
register_manager reg_manager;
label_manager lbl_manager;

string data_section_str = ".data\n";

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
        comp.generate_code();
    }
}
