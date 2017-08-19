%{
    extern int yylineno;

    int yylex();
    void yyerror(const char* msg);

    #define YYDEBUG 1
    #define YYERROR_VERBOSE 1
%}

%token RW_INT RW_CHAR RW_PRINTF RW_SCANF RW_IF RW_ELSE RW_WHILE RW_FOR RW_RETURN
%token TK_ID TK_NUMBER TK_STRING TK_CHAR 
%token OP_LE "<="
%token OP_GE ">="
%token OP_EQ "=="
%token OP_NE "!="

%%



expression: equality_expression
          | assign_expression
;

type: RW_INT
    | RW_CHAR
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
