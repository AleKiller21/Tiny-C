#include <iostream>
#include <list>
#include "ast.h"

using namespace std;

extern int yydebug;
extern int yyparse();

list<external_declaration*> source;

int main()
{
    yydebug = 0;
    yyparse();
    string code;
    for(list<external_declaration*>::iterator it = source.begin(); it != source.end(); it++)
        code += (*it)->to_string();

    cout << code << endl;
    cout << "\n\nSUCCESS\n" << endl;
}