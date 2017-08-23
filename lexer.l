%option noyywrap
%option yylineno
%x string_lit
%x char_lit
%x line_comment
%x block_comment

%{
    #include <string>
    #include "tokens.h"

    using namespace std;

    string string_lexeme;
    char char_lexeme;

    int extract_lexeme(char delimiter);
    char get_escape_secuence();
%}

ID          [a-zA-Z_][a-zA-Z0-9_]*
NUMBER      [0-9]+

%%

[ \t\n]                     { /* Nothing */ }
\"                          { BEGIN(string_lit); string_lexeme.clear(); }
\'                          { BEGIN(char_lit); }
"//"                        { BEGIN(line_comment); }
"/*"                        { BEGIN(block_comment); }
"int"                       { return RW_INT; }
"char"                      { return RW_CHAR; }
"void"                      { return RW_VOID; }
"printf"                    { return RW_PRINTF; }
"scanf"                     { return RW_SCANF; }
"if"                        { return RW_IF; }
"else"                      { return RW_ELSE; }
"while"                     { return RW_WHILE; }
"for"                       { return RW_FOR; }
"return"                    { return RW_RETURN; }
"continue"                  { return RW_CONTINUE; }
"break"                     { return RW_BREAK; }
{ID}                        { return TK_ID; }
{NUMBER}                    { return TK_NUMBER; }
"&"                         { return '&'; }
"?"                         { return '?'; }
":"                         { return ':'; }
"="                         { return '='; }
"++"                        { return OP_INC; }
"--"                        { return OP_DEC; }
"<<"                        { return OP_SL; }
">>"                        { return OP_SR; }
"^"                         { return '^'; }
"|"                         { return '|'; }
"~"                         { return '~'; }
"!"                         { return '!'; }
"+"                         { return '+'; }
"-"                         { return '-'; }
"*"                         { return '*'; }
"/"                         { return '/'; }
"%"                         { return '%'; }
"<"                         { return '<'; }
">"                         { return '>'; }
"<="                        { return OP_LE; }
">="                        { return OP_GE; }
"=="                        { return OP_EQ; }
"!="                        { return OP_NE; }
"&&"                        { return OP_LA; }
"||"                        { return OP_LO; }
"{"                         { return '{'; /*}*/ }
"}"                         { /*{*/ return '}'; }
"("                         { return '('; /*)*/ }
")"                         { return ')'; }
","                         { return ','; }
";"                         { return ';'; }
"["                         { return '['; }
"]"                         { return ']'; }
.                           { fprintf(stderr, "Line %d: error: Unrecognized token %s.\n", yylineno, yytext); }

<string_lit>[^\n\'\"\\]+    {
                                char symbol = yyinput();
                                string_lexeme += yytext;
                                if(symbol == '\\') string_lexeme += get_escape_secuence();
                                else
                                {
                                    unput(symbol);
                                    BEGIN(INITIAL); 
                                    if(extract_lexeme('\"') == 0) return TK_STRING;
                                }
                            }
<string_lit>\"              { /*TODO: save string_lexeme value into yylval */ BEGIN(INITIAL); return TK_STRING; }
<string_lit>\\              { string_lexeme += get_escape_secuence(); }
<string_lit>\n|\'           { BEGIN(INITIAL); fprintf(stderr, "Line %d: error: Missing terminating \" character.\n", yylineno); }

<char_lit>\"|\n             { BEGIN(INITIAL); fprintf(stderr, "Line %d: error: Missing terminating \' character.\n", yylineno); }
<char_lit>\'                { BEGIN(INITIAL); fprintf(stderr, "Line %d: error: empty character constant.\n", yylineno); }
<char_lit>\\                {
                                char_lexeme = get_escape_secuence();
                                BEGIN(INITIAL);
                                /*TODO: save yytext[0] value into yylval */
                                if(extract_lexeme('\'') == 0) return TK_CHAR;

                            }
<char_lit>.\'               { /*TODO: save yytext[0] value into yylval */ BEGIN(INITIAL); return TK_CHAR; }
<char_lit>[^\n\'\\]{2,}       { BEGIN(INITIAL); yyinput(); fprintf(stderr, "Line %d: error: character constant too long for its type.\n", yylineno); }


<line_comment>\n            { BEGIN(INITIAL); }
<line_comment>.             { /* Nothing */ }

<block_comment>"*/"         { BEGIN(INITIAL); }
<block_comment>.|\n         { /* Nothing */ }

%%

int extract_lexeme(char delimiter)
{
    char symbol = yyinput();
    if(symbol != delimiter)
    {
        fprintf(stderr, "Line %d: error: Missing terminating %c character.\n", yylineno, delimiter);
        return 1;
    }
    
    //TODO: save string_lexeme value into yylval
    return 0;
}

char get_escape_secuence()
{
    char symbol = yyinput();
    switch(symbol)
    {
        case 'n':
            return '\n';
        case 't':
            return '\t';
        case '\\':
            return '\\';
        case '\?':
            return '\?';
        case '\'':
            return '\'';
        case '\"':
            return '\"';
        case '0':
            return '\0';
        default:
            printf("Line %d: warning: Unknown escape secuence: '\\%c'.\n", yylineno, symbol);
            return symbol;
    }
}
