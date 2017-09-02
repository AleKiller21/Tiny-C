#include "compiler.h"

compiler::compiler(list<external_declaration*> source_code)
{
    this->source_code = source_code;
}

void compiler::validate_semantic()
{

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