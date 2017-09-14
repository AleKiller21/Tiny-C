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

void compiler::add_data_section(string label, string type, string value)
{
    data_section += "\t" + label + ": " + type + " " + value + "\n";
}

void compiler::mark_unnecessary_nodes()
{
    for(map<string, list<redundant_declaration>* >::iterator it = redund_manager.redundant_declarations.begin(); it != redund_manager.redundant_declarations.end(); it++)
    {
        list<redundant_declaration>* decls = it->second;
        for(list<redundant_declaration>::iterator it2 = decls->begin(); it2 != decls->end(); it2++)
        {
            redundant_declaration entry = *it2;
            if(entry.removable)
                ((declarator*)entry.decl_ptr)->redund_declaration = true;
        }
    }
}

void compiler::generate_code()
{
    string header = "#include \"screen.h\"\n#include \"system.h\"\n.global main\n\n";
    string prologue = ".text\nmain:\nli $a0, BRIGHT_WHITE\nli $a1, BLACK\njal set_color\njal clear_screen\n";
    string code;

    for(list<external_declaration*>::iterator it = source_code.begin(); it != source_code.end(); it++)
{
        string *fragment = (*it)->generate_code();
        code += *fragment;
        
        delete fragment;
    }

	code = header + data_section + "\n" + prologue + "\n" + code + "\n\njr $ra";
	cout << code << endl;
}