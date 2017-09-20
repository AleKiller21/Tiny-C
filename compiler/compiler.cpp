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
    data_section[label] = type;
    data_section_str += "\t" + label + ": " + type + " " + value + "\n";
}

void compiler::increase_stack_displacement(int type)
{
    switch(type)
    {
        case INT:
            stack_displacements[stack_displacements.size() - 1] = stack_displacements.back() + 4;
            break;
        case CHAR:
            stack_displacements[stack_displacements.size() - 1] = stack_displacements.back() + 1;
            break;
    }
}

string compiler::add_string_literal(string literal)
{
    try
    {
        return str_literals.at(literal);
    }

    catch(out_of_range)
    {
        string label = lbl_manager.get_free_label("literal");
        str_literals[literal] = label;
        add_data_section(label, ".asciiz", "\"" + literal + "\"");

        return label;
    }
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
    string prologue = ".text\n";
    string code;

    for(list<external_declaration*>::iterator it = source_code.begin(); it != source_code.end(); it++)
    {
        string *fragment = (*it)->generate_code();
        code += *fragment;
        
        delete fragment;
    }

	code = header + data_section_str + "\n" + prologue + "\n" + code;
	cout << code << endl;
}