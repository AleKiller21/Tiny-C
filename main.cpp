#include <iostream>

using namespace std;

extern int yydebug;
extern int yyparse();

int main()
{
    yydebug = 0;
    yyparse();
    cout << "SUCCESS" << endl;
}