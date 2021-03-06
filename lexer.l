%option noyywrap
%option yylineno
%x string_lit
%x char_lit
%x line_comment
%x block_comment
%x hex

%{
    #include <string>
    #include <cstdlib>
    #include "tokens.h"

    using namespace std;

    string string_lexeme;
    char char_lexeme;

    int extract_lexeme(char delimiter);
    char get_escape_secuence();
    void consume_invalid_number_literal(const char* number_format);
%}

ID          [a-zA-Z_][a-zA-Z0-9_]*
DECIMAL     [1-9][0-9]*
HEXADECIMAL 0[xX]
OCTAL       0[0-7]*

%%

[ \t\n]                     { /* Nothing */ }
\"                          { BEGIN(string_lit); string_lexeme.clear(); }
\'                          { BEGIN(char_lit); }
"//"                        { BEGIN(line_comment); }
"/*"                        { BEGIN(block_comment); }
"int"                       { yylval.int_t = INT; return RW_INT; }
"char"                      { yylval.int_t = CHAR; return RW_CHAR; }
"void"                      { yylval.int_t = VOID; return RW_VOID; }
"printf"                    { return RW_PRINTF; }
"time"                      { return RW_TIME; }
"srand"                     { return RW_SRAND; }
"rand"                      { return RW_RAND; }
"if"                        { return RW_IF; }
"else"                      { return RW_ELSE; }
"while"                     { return RW_WHILE; }
"for"                       { return RW_FOR; }
"return"                    { return RW_RETURN; }
"continue"                  { return RW_CONTINUE; }
"break"                     { return RW_BREAK; }
"sizeof"                    { return RW_SIZEOF; }
{ID}                        { yylval.str_t = new string(yytext); return TK_ID; }
{HEXADECIMAL}               { BEGIN(hex); }
{OCTAL}                     { yylval.int_t = atoi(yytext); return TK_OCT; }
{DECIMAL}                   { yylval.int_t = atoi(yytext); return TK_DEC; }
"?"                         { return '?'; }
":"                         { return ':'; }
"="                         { return '='; }
"*="                        { return OP_MULT_EQUAL; }
"/="                        { return OP_DIV_EQUAL; }
"%="                        { return OP_MOD_EQUAL; }
"+="                        { return OP_SUM_EQUAL; }
"-="                        { return OP_SUB_EQUAL; }
"<<="                       { return OP_SHIFT_LEFT_EQUAL; }
">>="                       { return OP_SHIFT_RIGHT_EQUAL; }
"&="                        { return OP_AND_EQUAL; }
"^="                        { return OP_EX_OR_EQUAL; }
"|="                        { return OP_IN_OR_EQUAL; }
"++"                        { return OP_INC; }
"--"                        { return OP_DEC; }
"<<"                        { return OP_SL; }
">>"                        { return OP_SR; }
"^"                         { return '^'; }
"|"                         { return '|'; }
"~"                         { return '~'; }
"&"                         { return '&'; }
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
<INITIAL><<EOF>>                        { return 0; }
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
<string_lit>\"              { yylval.str_t = new string(string_lexeme); BEGIN(INITIAL); return TK_STRING; }
<string_lit>\\              { string_lexeme += get_escape_secuence(); }
<string_lit>\n|\'           { BEGIN(INITIAL); fprintf(stderr, "Line %d: error: Missing terminating \" character.\n", yylineno); }

<char_lit>\"|\n             { BEGIN(INITIAL); fprintf(stderr, "Line %d: error: Missing terminating \' character.\n", yylineno); }
<char_lit>\'                { BEGIN(INITIAL); fprintf(stderr, "Line %d: error: empty character constant.\n", yylineno); }
<char_lit>\\                {
                                char_lexeme = get_escape_secuence();
                                BEGIN(INITIAL);
                                yylval.char_t = char_lexeme;
                                if(extract_lexeme('\'') == 0) return TK_CHAR;

                            }
<char_lit>.\'               { yylval.char_t = *yytext; BEGIN(INITIAL); return TK_CHAR; }
<char_lit>[^\n\'\\]{2,}       { BEGIN(INITIAL); yyinput(); fprintf(stderr, "Line %d: error: character constant too long for its type.\n", yylineno); }


<line_comment>\n            { BEGIN(INITIAL); }
<line_comment>.             { /* Nothing */ }

<block_comment>"*/"         { BEGIN(INITIAL); }
<block_comment>.|\n         { /* Nothing */ }

<hex>[a-fA-F0-9]+           { yylval.int_t = atoi(yytext); BEGIN(INITIAL); return TK_HEX;}
<hex>.|\n                   { consume_invalid_number_literal("hexadecimal"); }


%%

int extract_lexeme(char delimiter)
{
    char symbol = yyinput();
    if(symbol != delimiter)
    {
        fprintf(stderr, "Line %d: error: Missing terminating %c character.\n", yylineno, delimiter);
        return 1;
    }

    if(delimiter == '\"') yylval.str_t = new string(string_lexeme);

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

void consume_invalid_number_literal(const char* number_format)
{
    int c;
    BEGIN(INITIAL);
    fprintf(stderr, "Line %d: error: Invalid %s literal %s.\n", yylineno, number_format, yytext);
    if(*yytext != '\n')
        while((c = yyinput()) != '\n');
}
