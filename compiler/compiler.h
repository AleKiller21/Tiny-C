#ifndef COMPILER
#define COMPILER

#include <list>
#include <iostream>
#include <string>
#include <map>
#include "../ast/declarations/external_declaration.h"
#include "../ast/declarations/declarator.h"
#include "../redundancy_manager/redundancy_manager.h"
#include "../label_manager/label_manager.h"

using namespace std;

extern int declaration_pos;
extern int declarator_pos;
extern string data_section_str;
extern redundancy_manager redund_manager;
extern map<string, string> data_section;
extern map<string, string> str_literals;
extern label_manager lbl_manager;

class compiler
{
private:
    list<external_declaration*> source_code;

public:
    compiler(list<external_declaration*> source_code);
    void validate_semantic();
    void mark_unnecessary_nodes();
    static void add_data_section(string label, string type, string value);
    static string add_string_literal(string literal);
    void generate_code();
};

#endif // COMPILER