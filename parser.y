%code requires
{
    #include "ast.h"
}

%{
    extern int yylineno;

    int yylex();
    void yyerror(const char* msg);

    #define YYDEBUG 1
    #define YYERROR_VERBOSE 1
%}

%union {
    string* str_t;
    expression* expr_t;
    int int_t;
    char char_t;
}

%type <expr_t> expression primary_expression expression_list argument_list postfix_expression unary_expression cast_expression multiplicative_expression

%token RW_INT RW_CHAR RW_VOID RW_PRINTF RW_SCANF RW_IF RW_ELSE RW_WHILE RW_FOR RW_RETURN RW_BREAK RW_CONTINUE
%token <str_t> TK_ID TK_STRING 
%token <int_t> TK_DEC TK_OCT TK_HEX
%token <char_t> TK_CHAR
%token OP_LE "<="
%token OP_GE ">="
%token OP_EQ "=="
%token OP_NE "!="
%token OP_LA "&&"
%token OP_LO "||"
%token OP_INC "++"
%token OP_DEC "--"
%token OP_SL "<<"
%token OP_SR ">>"
%token OP_MULT_EQUAL "*="
%token OP_DIV_EQUAL "/="
%token OP_MOD_EQUAL "%="
%token OP_SUM_EQUAL "+="
%token OP_SUB_EQUAL "-="
%token OP_SHIFT_LEFT_EQUAL "<<="
%token OP_SHIFT_RIGHT_EQUAL ">>="
%token OP_AND_EQUAL "&="
%token OP_EX_OR_EQUAL "^="
%token OP_IN_OR_EQUAL "|="

%expect 1

%%

translation_unit: external_declaration
                | translation_unit external_declaration
;

external_declaration: declaration
                    | function_definition
;

function_definition: type declarator block_statement
;

statement_list: statement
              | statement_list statement
;

statement: expression_statement
         | block_statement
         | selection_statement
         | loop_statement
         | jump_statement
;

expression_statement: expression ';'
                    | ';'
;

block_statement: '{' declaration_list '}'
               | '{' statement_list '}'
               | '{' declaration_list statement_list '}'
               | '{' '}'
;

selection_statement: RW_IF '(' expression ')' statement else_statement
;

else_statement: RW_ELSE statement
              | %empty
;

loop_statement: while_statement
              | for_statement
;

while_statement: RW_WHILE '(' expression ')' statement
;

for_statement: RW_FOR '(' expression_statement expression_statement optional_expression ')' statement
;

jump_statement: RW_CONTINUE ';'
              | RW_BREAK ';'
              | RW_RETURN optional_expression ';'
;

type_name: type
         | type abstract_declarator
;

abstract_declarator: pointer
                   | pointer direct_abstract_declarator
                   | direct_abstract_declarator
;

direct_abstract_declarator: '(' abstract_declarator ')'
                          | direct_abstract_declarator '[' conditional_expression ']'
                          | direct_abstract_declarator '[' ']'
                          | '[' conditional_expression ']'
                          | '[' ']'
                          | direct_abstract_declarator '(' parameter_type_list ')'
                          | direct_abstract_declarator '(' ')'
                          | '(' parameter_type_list ')'
                          | '(' ')'
;

declaration_list: declaration
                | declaration_list declaration
;

declaration: type declarators_list ';'
;

declarators_list: declarator_init
                | declarators_list ',' declarator_init
;

declarator_init: declarator
               | declarator '=' initializer
;

initializer: expression
           | '{' initializer_list '}'
;

initializer_list: initializer
                | initializer_list ',' initializer
;

declarator: pointer direct_declarator
          | direct_declarator
;

pointer: '*'
;

direct_declarator: TK_ID
                 | '(' declarator ')'
                 | direct_declarator '[' optional_expression ']'
                 | direct_declarator '(' parameter_type_list ')'
                 | direct_declarator '(' ')'
;

parameter_type_list: parameter_list
;

parameter_list: parameter_declaration
              | parameter_list ',' parameter_declaration
;

parameter_declaration: type declarator
                     | type abstract_declarator
                     | type
;

type: RW_INT
    | RW_CHAR
    | RW_VOID
;

optional_expression: expression
                   | %empty
;

expression: conditional_expression
          | assign_expression
;

assign_expression: unary_expression assign_operators expression
;

assign_operators: '='
                | "*="
                | "/="
                | "%="
                | "+="
                | "-="
                | "<<="
                | ">>="
                | "&="
                | "^="
                | "|="
;

conditional_expression: logical_or_expression '?' expression ':' conditional_expression
                      | logical_or_expression
;

logical_or_expression: logical_or_expression "||" logical_and_expression
                     | logical_and_expression
;

logical_and_expression: logical_and_expression "&&" inclusive_or_expression
                      | inclusive_or_expression
;

inclusive_or_expression: inclusive_or_expression '|' exclusive_or_expression
                       | exclusive_or_expression
;

exclusive_or_expression: exclusive_or_expression '^' and_expression
                       | and_expression
;

and_expression: and_expression '&' equality_expression
              | equality_expression
;

equality_expression: equality_expression "==" relational_expression
                   | equality_expression "!=" relational_expression
                   | relational_expression
;

relational_expression: relational_expression '<' shift_expression
                     | relational_expression '>' shift_expression
                     | relational_expression "<=" shift_expression
                     | relational_expression ">=" shift_expression
                     | shift_expression
;

shift_expression: shift_expression "<<" additive_expression
                | shift_expression ">>" additive_expression
                | additive_expression
;

additive_expression: additive_expression '+' multiplicative_expression
                   | additive_expression '-' multiplicative_expression
                   | multiplicative_expression
;

multiplicative_expression: multiplicative_expression '*' cast_expression { $$ = new mult_expression($1, $3, yylineno); }
                         | multiplicative_expression '/' cast_expression { $$ = new div_expression($1, $3, yylineno); }
                         | multiplicative_expression '%' cast_expression { $$ = new mod_expression($1, $3, yylineno); }
                         | cast_expression { $$ = $1; }
;

cast_expression: '(' type_name ')' cast_expression { $$ = NULL; /* TODO: Implementar despues de haber terminado type_name production*/ }
               | unary_expression { $$ = $1; }
;

unary_expression: "++" unary_expression { $$ = new pre_increment_expression($2, yylineno); }
                | "--" unary_expression { $$ = new pre_decrement_expression($2, yylineno); }
                | pointer cast_expression { $$ = new pointer_expression($2, yylineno); }
                | '&' cast_expression { $$ = new address_expression($2, yylineno); }
                | '+' cast_expression { $$ = new positive_expression($2, yylineno); }
                | '-' cast_expression { $$ = new negative_expression($2, yylineno); }
                | '~' cast_expression { $$ = new two_complement_expression($2, yylineno); }
                | '!' cast_expression { $$ = new negation_expression($2, yylineno); }
                | postfix_expression { $$ = $1; }
;

postfix_expression: postfix_expression '[' expression ']' { $$ = new array_expression($1, $3, yylineno); }
                  | postfix_expression '(' argument_list ')' { $$ = new function_expression($1, $3, yylineno); }
                  | postfix_expression "++" { $$ = new post_increment_expression($1, yylineno); }
                  | postfix_expression "--" { $$ = new post_decrement_expression($1, yylineno); }
                  | primary_expression { $$ = $1; }
;

argument_list: expression_list { $$ = $1; }
             | %empty { $$ = NULL; }
;

expression_list: expression { $$ = new expression_list(yylineno); ((expression_list*)$$)->add_expression($1); }
               | expression_list ',' expression { $$ = $1; ((expression_list*)$$)->add_expression($3); }
;

primary_expression: TK_ID { $$ = new id_expression($1, yylineno); }
                  | TK_CHAR { $$ = new char_expression($1, yylineno); }
                  | TK_DEC { $$ = new int_expression($1, 'd', yylineno); }
                  | TK_HEX { $$ = new int_expression($1, 'h', yylineno); }
                  | TK_OCT { $$ = new int_expression($1, 'o', yylineno); }
                  | TK_STRING { $$ = new string_expression($1, yylineno); }
                  | '(' expression ')' { $$ = $2; }
;

%%

void yyerror(const char* msg)
{
    fprintf(stderr, "Line %d: error: %s\n", yylineno, msg);
}
