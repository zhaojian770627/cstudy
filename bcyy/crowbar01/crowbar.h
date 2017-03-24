#ifndef PRIVATE_CROWBAR_HE_INCLUDED
#define PRIVATE_CROWBAR_HE_INCLUDED
#include <stdio.h>
#include "MEM.h>
#include "CRB.h"
#include "CRB_dev.h"

#define smaller(a,b) ((a)<(b)?(a):(b))
#define larger(a,b) ((a)>(b)?(a):(b))

#define MESSAGE_ARGUMENT_MAX (256)
#define LINE_BUF_SIZE (1024)

typedef enum{
  PARSE_ERR=1,
  CHARACTER_INVALID_ERR,
  FUNCTION_MULTIPLE_DEFINE_ERR,
  COMPILE_ERROR_COUNT_PLUS_1
}CompileError;

typedef enum{
  VARIABLE_NOT_FOUND_ERR=1,
  FUNCTION_NOT_FOUND_ERR,
  ARGUMENT_TOO_MANY_ERR,
  ARGUMENT_TOO_FEW_ERR,
  NOT_BOOLEAN_TYPE_ERR,
  MINUS_OPERAND_TYPE_ERR,
  BAD_OPERAND_TYPE_ERR,
  NOT_BOOLEAN_OPERATOR_ERR,
  FOPEN_ARGUMENT_TYPE_ERR,
  FCLOSE_ARGUMENT_TYPE_ERR,
  FGETS_ARGUMENT_TYPE_ERR,
  FPUTS_ARGUMENT_TYPE_ERR,
  NOT_NULL_OPERATOR_ERR,
  DIVISION_BY_ZERO_ERR,
  GLOBAL_VARIABLE_NOT_FOUND_ERR,
  GLOBAL_STATEMENT_IN_TOPLEVEL_ERR,
  BAD_OPERATOR_FOR_STRING_ERR,
  RUNTIME_ERROR_COUNT_PLUS_1
}RuntimeError;

typedef enum{
  INT_MESSAGE_ARGUMENT=1,
  DOUBLE_MESSAGE_ARGUMENT,
  STRING_MESSAGE_ARGUMENT,
  CHARACTER_MESSAGE_ARGUMENT,
  POINTER_MESSAGE_ARGUMENT,
  MESSAGE_ARGUMENT_END
}MessageArgumentType;

typedef struct{
  char *format;
}MessageFormat;

typedef struct Expression_tag Expression;

typedef enum{
  BOOLEAN_EXPRESSION=1,
  INT_EXPRESSION,
  DOUBLE_EXPRESSION,
  STRING_EXPRESSION,
  IDENTIFIER_EXPRESSION,
  ASSIGN_EXPRESSION,
  ADD_EXPRESSION,
  SUB_EXPRESSION,
  MUL_EXPRESSION,
  DIV_EXPRESSION,
  MOD_EXPRESSION,
  EQ_EXPRESSION,
  NE_EXPRESSION,
  GT_EXPRESSION,
  GE_EXPRESSION,
  LT_EXPRESSION,
  LE_EXPRESSION,
  LOGICAL_AND_EXPRESSION,
  LOGLCAL_OR_EXPRESSION,
  MINUS_EXPRESSION,
  FUNCTION_CALL_EXPRESSION,
  NULL_EXPRESSION,
  EXPRESSION_TYPE_EXPRESSION,
  EXPRESSION_TYPE_COUNT_PLUS_1
}Expression;

#define dkc_is_math_operator(operator)				\
  ((operator)==ADD_EXPRESSION||(operator)==SUB_EXPRESSION	\
   ||(operator)==MUL_EXPRESSION||(operator)==DIV_EXPRESSION	\
   ||(operator)==MOD_EXPRESSION)

#define dkc_is_compare_operator(operator)			\
  ((operator)==EQ_EXPRESSION||(operator)==NE_EXPRESSION		\
   ||(operator)==GT_EXPRESSION||(operator)==GE_EXPRESSION	\
   ||(operator)==LT_EXPRESSION||(operator)==LE_EXPRESSION)

#define dkc_is_logical_operator(operator) \
  ((operator)==LOGICAL_AND_EXPRESSION ||(operator)==LOGICAL_OR)

typedef struct ArgumentList_tag{
  Expression *expression;
  struct ArgumentList_tag *next;
}ArgumentList;

typedef struct{
  char *variable;
  Expression *operand;
}AssignExpression;

typedef struct {
  Expression *left;
  Expression *right;
}BinaruExpression;


typedef struct {
  char *identifier;
  ArgumentList *argument;
}FunctionCallExpression;

struct Expression_tag{
  ExpressionType type;
  int line_number;
  union{
    CRB_Boolean boolean_value;
    int int_value;
    double double_value;
    char *string_value;
    char *identifier;
    AssignExpression assign_expression;
    BinaruExpression binary_expression;
    Expression *minus_expression;
    FunctionCallExpression function_call_expression;
  }u;
};

typedef struct Statement_tag_Statement;

typedef struct StatementList_tag{
  Statement *statement;
  struct StatementList_tag *next;
}StatementList;

typedef struct IdentifierList_tag{
  char *name;
  struct IdentifierList_tag *next;
}IdentifierList;

typedef struct {
  IdentifierList *identifier_list;
}GlobalStatement;

typedef struct Elsif_tag{
  Expression *condition;
  Block *block;
  struct Elsif_tag *next;
}Elseif;

typedef struct{
  Expression *condition;
  Block *then_block;
  Elseif *elsif_list;
  Block *else_block;
}IfStatement;


