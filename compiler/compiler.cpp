#include "compiler.h"

compiler::compiler(list<external_declaration*> source_code)
{
    this->source_code = source_code;
}

void compiler::validate_semantic()
{
    for(list<external_declaration*>::iterator it = source_code.begin(); it != source_code.end(); it++)
    {
        (*it)->validate_semantic();
        declaration_pos++;
        declarator_pos = 0;
    }
}

void compiler::mark_unnecessary_nodes()
{
    int counter = 0;
    for(map<string, list<redundant_declaration>* >::iterator it = redund_manager.redundant_declarations.begin(); it != redund_manager.redundant_declarations.end(); it++)
    {
        list<redundant_declaration>* decls = it->second;
        for(list<redundant_declaration>::iterator it2 = decls->begin(); it2 != decls->end(); it2++)
        {
            redundant_declaration entry = *it2;
            if(entry.removable)
            {
                ((declarator*)entry.decl_ptr)->redund_declaration = true;
                counter++;
            }
        }
    }

    cout << counter << endl;
}

string compiler::generate_code()
{
    string code;
    for(list<external_declaration*>::iterator it = source_code.begin(); it != source_code.end(); it++)
        code += (*it)->to_string();

    cout << code << endl;
    cout << "\n\nSUCCESS\n" << endl;
    return "SUCEES;";
}