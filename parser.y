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

%code
{
    #include <list>
    extern std::list<external_declaration*> source;
}

%union {
    string* str_t;
    expression* expr_t;
    expression_list* expr_lst;
    statement* stmt_t;
    declaration* declaration_t;
    external_declaration* external_decl_t;
    declarator* decl_t;
    abstract_declarator* abstract_decl_t;
    declarator_list* decl_lst;
    declaration_list* declaration_lst;
    parameter_list* params_t;
    initializer* initializer_t;
    function_definition* funct_t;
    int int_t;
    char char_t;
}

%type <expr_t> expression primary_expression expression_list argument_list postfix_expression unary_expression cast_expression
%type <expr_t> multiplicative_expression additive_expression shift_expression relational_expression equality_expression and_expression
%type <expr_t> exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression conditional_expression assign_expression
%type <expr_lst> initializer_list
%type <stmt_t> statement jump_statement expression_statement for_statement while_statement loop_statement else_statement selection_statement
%type <stmt_t> block_statement statement_list
%type <decl_t> direct_declarator declarator parameter_declaration declarator_init
%type <abstract_decl_t> type_name
%type <params_t> parameter_list parameter_type_list
%type <int_t> type
%type <initializer_t> initializer
%type <decl_lst> declarators_list
%type <declaration_lst> declaration_list
%type <declaration_t> declaration
%type <funct_t> function_definition
%type <external_decl_t> external_declaration

%token RW_PRINTF RW_SCANF RW_IF RW_ELSE RW_WHILE RW_FOR RW_RETURN RW_BREAK RW_CONTINUE RW_SIZEOF
%token <str_t> TK_ID TK_STRING 
%token <int_t> TK_DEC TK_OCT TK_HEX RW_INT RW_CHAR RW_VOID
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

translation_unit: external_declaration { source.push_back($1); }
                | translation_unit external_declaration { source.push_back($2); }
;

external_declaration: declaration { $$ = $1; }
                    | function_definition { $$ = $1; }
;

function_definition: type declarator block_statement { $$ = new function_definition($1, $2, $3); }
;

statement_list: statement { $$ = new statement_list(yylineno); ((statement_list*)$$)->add_statement($1); }
              | statement_list statement { $$ = $1; ((statement_list*)$$)->add_statement($2); }
;

statement: expression_statement { $$ = $1; }
         | block_statement { $$ = $1; }
         | selection_statement { $$ = $1; }
         | loop_statement { $$ = $1; }
         | jump_statement { $$ = $1; }
;

expression_statement: expression ';' { $$ = new expression_statement(yylineno, $1); }
                    | ';' { $$ = new expression_statement(yylineno, NULL); }
;

block_statement: '{' declaration_list '}' { $$ = new block_statement(NULL, $2); }
               | '{' statement_list '}' { $$ = new block_statement($2, NULL); }
               | '{' declaration_list statement_list '}' { $$ = new block_statement($3, $2); }
               | '{' '}' { $$ = new block_statement(NULL, NULL); }
;

selection_statement: RW_IF '(' expression ')' statement else_statement { $$ = new if_statement(yylineno, $3, $5, $6); }
                   | RW_IF '(' expression ')' statement { $$ = new if_statement(yylineno, $3, $5, NULL); }
;

else_statement: RW_ELSE statement { $$ = $2; }
;

loop_statement: while_statement { $$ = $1; }
              | for_statement { $$ = $1; }
;

while_statement: RW_WHILE '(' expression ')' statement { $$ = new while_statement($3, $5, yylineno); }
;

for_statement: RW_FOR '(' expression_statement expression_statement expression ')' statement { $$ = new for_statement(yylineno, $7, $3, $4, $5); }
             | RW_FOR '(' expression_statement expression_statement ')' statement { $$ = new for_statement(yylineno, $6, $3, $4, NULL); }
;

jump_statement: RW_CONTINUE ';' { $$ = new continue_statement(yylineno); }
              | RW_BREAK ';' { $$ = new break_statement(yylineno); }
              | RW_RETURN expression ';' { $$ = new return_statement(yylineno, $2); }
              | RW_RETURN ';' { $$ = new return_statement(yylineno, NULL); }
;

type_name: type { $$ = new abstract_declarator($1, false); }
         | type pointer { $$ = new abstract_declarator($1, true); }
;

declaration_list: declaration { $$ = new declaration_list(); $$->add_declaration($1); }
                | declaration_list declaration { $$ = $1; $$->add_declaration($2); }
;

declaration: type declarators_list ';' { $$ = new declaration($2, $1); }
;

declarators_list: declarator_init { $$ = new declarator_list(); $$->add_declarator($1); }
                | declarators_list ',' declarator_init { $$ = $1; $$->add_declarator($3); }
;

declarator_init: declarator { $$ = $1; }
               | declarator '=' initializer { $$ = $1; $$->init = $3; }
;

initializer: expression { $$ = new initializer($1, NULL); }
           | '{' initializer_list '}' { $$ = new initializer(NULL, $2); }
;

initializer_list: expression { $$ = new expression_list(yylineno); $$->add_expression($1); }
                | initializer_list ',' expression { $$ = $1; $$->add_expression($3); }
;

declarator: pointer direct_declarator { $$ = $2; $$->pointer = true; }
          | direct_declarator { $$ = $1; }
;

pointer: '*'
;

direct_declarator: TK_ID { $$ = new simple_declarator(new id_expression($1, yylineno), yylineno); }
                 | TK_ID '[' expression ']' { $$ = new array_declarator(yylineno, new id_expression($1, yylineno), $3); }
                 | TK_ID '[' ']' { $$ = new array_declarator(yylineno, new id_expression($1, yylineno), NULL); }
                 | TK_ID '(' parameter_type_list ')' { $$ = new function_declarator(yylineno, new id_expression($1, yylineno), $3); }
                 | TK_ID '(' ')' { $$ = new function_declarator(yylineno, new id_expression($1, yylineno), NULL); }
;

parameter_type_list: parameter_list { $$ = $1; }
;

parameter_list: parameter_declaration { $$ = new parameter_list(); $$->add_param($1); }
              | parameter_list ',' parameter_declaration { $$ = $1; $$->add_param($3); }
;

parameter_declaration: type declarator { $$ = $2; $$->type = $1; }
;

type: RW_INT { $$ = $1; }
    | RW_CHAR { $$ = $1; }
    | RW_VOID { $$ = $1; }
;

expression: conditional_expression { $$ = $1; }
          | assign_expression { $$ = $1; }
;

assign_expression: unary_expression '=' expression { $$ = new assign_equal_expression($1, $3, yylineno); }
                 | unary_expression "*=" expression { $$ = new mult_equal_expression($1, new mult_expression($1, $3, yylineno), yylineno); }
                 | unary_expression "/=" expression { $$ = new div_equal_expression($1, new div_expression($1, $3, yylineno), yylineno); }
                 | unary_expression "%=" expression { $$ = new mod_equal_expression($1, new mod_expression($1, $3, yylineno), yylineno); }
                 | unary_expression "+=" expression { $$ = new sum_equal_expression($1, new sum_expression($1, $3, yylineno), yylineno); }
                 | unary_expression "-=" expression { $$ = new sub_equal_expression($1, new sub_expression($1, $3, yylineno), yylineno); }
                 | unary_expression "<<=" expression { $$ = new lshift_equal_expression($1, new lshift_expression($1, $3, yylineno), yylineno); }
                 | unary_expression ">>=" expression { $$ = new rshift_equal_expression($1, new rshift_expression($1, $3, yylineno), yylineno); }
                 | unary_expression "&=" expression { $$ = new and_equal_expression($1, new and_expression($1, $3, yylineno), yylineno); }
                 | unary_expression "^=" expression { $$ = new xor_equal_expression($1, new xor_expression($1, $3, yylineno), yylineno); }
                 | unary_expression "|=" expression { $$ = new or_equal_expression($1, new or_expression($1, $3, yylineno), yylineno); }
;

conditional_expression: logical_or_expression '?' expression ':' conditional_expression { $$ = new conditional_expression($1, $3, $5, yylineno); }
                      | logical_or_expression { $$ = $1; }
;

logical_or_expression: logical_or_expression "||" logical_and_expression { $$ = new logical_or_expression($1, $3, yylineno); }
                     | logical_and_expression { $$ = $1; }
;

logical_and_expression: logical_and_expression "&&" inclusive_or_expression { $$ = new logical_and_expression($1, $3, yylineno); }
                      | inclusive_or_expression { $$ = $1; }
;

inclusive_or_expression: inclusive_or_expression '|' exclusive_or_expression { $$ = new or_expression($1, $3, yylineno); }
                       | exclusive_or_expression { $$ = $1; }
;

exclusive_or_expression: exclusive_or_expression '^' and_expression { $$ = new xor_expression($1, $3, yylineno); }
                       | and_expression { $$ = $1; }
;

and_expression: and_expression '&' equality_expression { $$ = new and_expression($1, $3, yylineno); }
              | equality_expression { $$ = $1; }
;

equality_expression: equality_expression "==" relational_expression { $$ = new equal_expression($1, $3, yylineno); }
                   | equality_expression "!=" relational_expression { $$ = new not_equal_expression($1, $3, yylineno); }
                   | relational_expression { $$ = $1; }
;

relational_expression: relational_expression '<' shift_expression { $$ = new less_expression($1, $3, yylineno); }
                     | relational_expression '>' shift_expression { $$ = new greater_expression($1, $3, yylineno); }
                     | relational_expression "<=" shift_expression { $$ = new less_equal_expression($1, $3, yylineno); }
                     | relational_expression ">=" shift_expression { $$ = new greater_equal_expression($1, $3, yylineno); }
                     | shift_expression
;

shift_expression: shift_expression "<<" additive_expression { $$ = new lshift_expression($1, $3, yylineno); }
                | shift_expression ">>" additive_expression { $$ = new rshift_expression($1, $3, yylineno); }
                | additive_expression { $$ = $1; }
;

additive_expression: additive_expression '+' multiplicative_expression { $$ = new sum_expression($1, $3, yylineno); }
                   | additive_expression '-' multiplicative_expression { $$ = new sub_expression($1, $3, yylineno); }
                   | multiplicative_expression { $$ = $1; }
;

multiplicative_expression: multiplicative_expression '*' cast_expression { $$ = new mult_expression($1, $3, yylineno); }
                         | multiplicative_expression '/' cast_expression { $$ = new div_expression($1, $3, yylineno); }
                         | multiplicative_expression '%' cast_expression { $$ = new mod_expression($1, $3, yylineno); }
                         | cast_expression { $$ = $1; }
;

cast_expression: '(' type_name ')' cast_expression { $$ = new cast_expression($2, $4, yylineno); }
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
                | RW_SIZEOF unary_expression { $$ = new sizeof_expression($2, NULL, yylineno); }
                | RW_SIZEOF '(' type_name ')' { $$ = new sizeof_expression(NULL, $3, yylineno); }
                | postfix_expression { $$ = $1; }
;

postfix_expression: postfix_expression '[' expression ']' { $$ = new array_expression($1, $3, yylineno); }
                  | postfix_expression '(' argument_list ')' { $$ = new function_expression($1, $3, yylineno); }
                  | postfix_expression '(' ')' { $$ = new function_expression($1, NULL, yylineno); }
                  | postfix_expression "++" { $$ = new post_increment_expression($1, yylineno); }
                  | postfix_expression "--" { $$ = new post_decrement_expression($1, yylineno); }
                  | primary_expression { $$ = $1; }
;

argument_list: expression_list { $$ = $1; }
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
