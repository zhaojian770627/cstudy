%{
#include <stdio.h>
#include "crowbar.h"
#define YYDEBUG 1
  %}
%union{
  char *identifier;
  ParameterList *parameter_list;
  ArgumentList *argument_list;
  Expression *expression;
  Statement *statement;
  StatementList *statement_list;
  Block *block;
  Elsif *elsif;
  IdentifierList *identifier_list;
 }

%token <expression> INT_LITERAL
%token <expression> DOUBLE_LITERAL
%token <expression> STRING_LITERAL;
%token <identifier> IDENTIFIER
%token FUNCTION IF ELSE ELSEIF WHILE FOR RETURN_T BREAK CONTINUE NULL_T
 LP RP LC RC SEMICONLON COMMA ASSIGN LOGICAL_ADN LOGICAL_OR
 EQ NE GT GE LT LE ADD SUB MUL DIV MOD TRUE_T FALSE_T GLOBAL_T

%type <parameter_list> parameter_list
%type <argument_list> argument_list
%type <expression> expression expression_opt
 logical_and_expression logical_or_expression
 equality_expression relational_expression
 additive_expression multiplicative_expression
 unary_expression primary_expression
%type <statement> statement global_statement
 if_statement while_statement for_statement
 return_statement break_statement continue_statement
%type <statement_list> statement_list
%type <block> block
%type <elsif> elsif elsif_list
%type <identifier_list> identifier_list
%%

translation_unit
:definition_or_statement
|translation_unit definition_or_statement
;

function_or_definition
:function_definition
|statement
{
  CRB_Interpreter *inter=crb_get_current_interpreter();
  inter->statement_list(inter->statement_list,$1);
}
;
function_definition
:FUNCTION IDENTIFIER LP parameter_list RP block
{
  crb_function_define($2,$4,$6);
}
|FUCNTION IDENTIFIER LP RP block
{
  crb_function_define($2,NULL,$5);
}
;
parameter_list
:IDENTIFIER
{
  $$=crb_create_parameter($1);
}
|parameter_list COMMA IDENTIFIER
{
  $$=crb=crb_chain_parameter($1,$3);
}
;
argument_list
:expression
{
  $$=crb_create_argument_list($1);
}
|argument_list COMMA expression
{
  $$=crb_chain_argument_list($1,$3);
}
;


