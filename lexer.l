%option noyywrap
%option yylineno
%x string_lit
%x char_lit
%x line_comment
%x block_comment

%{
    #include <stdio.h>
    #include <string>

    using namespace std;

    string string_lexeme;
    char char_lexeme;

    int extract_lexeme(char delimiter);
    char get_escape_secuence();

    #define RW_INT 1
    #define RW_CHAR 2
    #define RW_PRINTF 3
    #define RW_SCANF 4
    #define RW_IF 5
    #define RW_ELSE 6
    #define RW_WHILE 7
    #define RW_FOR 8
    #define TK_ID 9
    #define TK_NUMBER 10
    #define TK_STRING 11
    #define TK_CHAR 12
    #define OP_LE 13
    #define OP_GE 14
    #define OP_EQ 15
    #define OP_NE 16
    #define TK_EOF 17
    #define RW_RETURN 18
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
"printf"                    { return RW_PRINTF; }
"scanf"                     { return RW_SCANF; }
"if"                        { return RW_IF; }
"else"                      { return RW_ELSE; }
"while"                     { return RW_WHILE; }
"for"                       { return RW_FOR; }
"return"                    { return RW_RETURN; }
{ID}                        { return TK_ID; }
{NUMBER}                    { return TK_NUMBER; }
"="                         { return '='; }
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
"{"                         { return '{'; /*}*/ }
"}"                         { /*{*/ return '}'; }
"("                         { return '('; /*)*/ }
")"                         { return ')'; }
","                         { return ','; }
";"                         { return ';'; }
"["                         { return '['; }
"]"                         { return ']'; }
<INITIAL><<EOF>>            { return TK_EOF; }
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
        default:
            printf("Line %d: warning: Unknown escape secuence: '\\%c'.\n", yylineno, symbol);
            return symbol;
    }
}

int main()
{
    int token;
    while((token = yylex()) != TK_EOF)
    {
        if(token == TK_STRING) printf("Token: %d, Value: %s\n", token, string_lexeme.c_str());
        else if(token == TK_CHAR) printf("Token: %d, Value: %c\n", token, char_lexeme);
        else printf("Token: %d, Value: %s\n", token, yytext);
    }

    printf("End of file\n");
}