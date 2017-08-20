%{
    extern int yylineno;

    int yylex();
    void yyerror(const char* msg);

    #define YYDEBUG 1
    #define YYERROR_VERBOSE 1
%}

%token RW_INT RW_CHAR RW_PRINTF RW_SCANF RW_IF RW_ELSE RW_WHILE RW_FOR RW_RETURN RW_BREAK RW_CONTINUE
%token TK_ID TK_NUMBER TK_STRING TK_CHAR 
%token OP_LE "<="
%token OP_GE ">="
%token OP_EQ "=="
%token OP_NE "!="

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

expression_statement: optional_expression ';'
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
;

declarator: pointer direct_declarator
;

pointer: '*'
       | %empty
;

direct_declarator: TK_ID
                 | '(' declarator ')'
                 | direct_declarator '[' optional_expression ']'
                 | direct_declarator '(' parameter_type_list ')'
;

parameter_type_list: parameter_list
                   | %empty
;

parameter_list: parameter_declaration
              | parameter_list ',' parameter_declaration
;

parameter_declaration: type declarator
;

type: RW_INT
    | RW_CHAR
;

optional_expression: expression
                   | %empty
;

expression: equality_expression
          | assign_expression
;

assign_expression: unary_expression '=' expression
;


equality_expression: equality_expression "==" relational_expression
                   | equality_expression "!=" relational_expression
                   | relational_expression
;

relational_expression: relational_expression '<' additive_expression
                     | relational_expression '>' additive_expression
                     | relational_expression "<=" additive_expression
                     | relational_expression ">=" additive_expression
                     | additive_expression
;

additive_expression: additive_expression '+' multiplicative_expression
                   | additive_expression '-' multiplicative_expression
                   | multiplicative_expression
;

multiplicative_expression: multiplicative_expression '*' cast_expression
                         | multiplicative_expression '/' cast_expression
                         | multiplicative_expression '%' cast_expression
                         | cast_expression
;

cast_expression: '(' type ')' cast_expression
               | unary_expression
;

unary_expression: unary_operator cast_expression
                | postfix_expression
;

unary_operator: '&'
              | '*'
              | '+'
              | '-'
;

postfix_expression: postfix_expression '[' expression ']'
                  | postfix_expression '(' argument_list ')'
                  | primary_expression
;

argument_list: expression_list
             | %empty
;

expression_list: expression
               | expression_list ',' expression
;

primary_expression: TK_ID
                  | TK_CHAR
                  | TK_NUMBER
                  | TK_STRING
                  | '(' expression ')'
;

%%

void yyerror(const char* msg)
{
    fprintf(stderr, "Line %d: error: %s\n", yylineno, msg);
}
