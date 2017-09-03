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

void compiler::remove_unnecessary_nodes()
{
    //TODO: Considerar la idea de borrar todos esos nodos de declaraciones redundantes
    // for(map<string, list<redundant_declaration>* >::iterator it = redundant_declarations.begin(); it != redundant_declarations.end(); it++)
    // {
    //     list<redundant_declaration>* decls = it->second;
    //     for(list<redundant_declaration>::iterator it2 = decls.begin(); it2 != decls.end(); it2++)
    //     {
    //         redundant_declaration entry = *it;
    //     }
    // }
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