#include "declaration_list.h"

void declaration_list::add_declaration(declaration* decl)
{
    declarations.push_back(decl);
}

string declaration_list::to_string()
{
    string str;
    for(list<declaration*>::iterator it = declarations.begin(); it != declarations.end(); it++)
    {
        str += "\t" + (*it)->to_string();
    }

    return str;
}

void declaration_list::validate_semantic()
{
    for(list<declaration*>::iterator it = declarations.begin(); it != declarations.end(); it++)
    {
        (*it)->validate_semantic();
    }
}

string* declaration_list::generate_code()
{
    string code;
    bool is_word;
    int stack_displacement = 0;
    int entries_counter = 0;
    int word_size = 4;
    int byte_size = 1;
    int size;
    vector<stack_entry> entries;

    for(list<declaration*>::iterator it = declarations.begin(); it != declarations.end(); it++)
    {
        // string *decl_code = (*it)->generate_code();
        // code += *decl_code;
        // delete decl_code;

        list<stack_entry> *decls = (*it)->create_stack_entries();
        if(decls == NULL) continue;

        for(list<stack_entry>::iterator it = decls->begin(); it != decls->end(); it++)
        {
            entries.push_back(*it);

            is_word = entries[entries_counter].asm_type == WORD;
            size = is_word ? 4 : 1;

            if(entries[entries_counter].asm_type == WORD)
                while(stack_displacement % 4 != 0) stack_displacement++;

            entries[entries_counter].byte_offset = stack_displacement;
            stack_displacement += size;

            cout << entries[entries_counter].var_id + " Offset: " + std::to_string(entries[entries_counter].byte_offset) << endl;
            entries_counter++;
        }

        decls->clear();
        delete decls;
    }

    if(stack_displacement % 4 != 0) stack_displacement = (stack_displacement / 4 + 1) * 4;

    stack_displacement += 8;
    code = "\taddi $sp, $sp, -" + std::to_string(stack_displacement) + "\n" + code;
    code += "\tsw $fp, " + std::to_string(stack_displacement - 4) + "($sp)\n";
    code += "\tsw $ra, " + std::to_string(stack_displacement - 8) + "($sp)\n";
    return new string(code);
}

//0
//4
//8
//9
//12