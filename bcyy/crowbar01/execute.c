#include <math.h>
#include <string.h>
#include "MEM.h"
#include "DBG.h"
#include "crowbar.h"

static StatementResult
execute_statement(CRB_Interpreter *inter,LocalEnvironment *env,
		  Statement *statement);

static StatementResult
execute_expression_statement(CRB_Interpreter *inter,LocalEnvironment *env,
			     Statement *statement)
{
  StatementResult result;
  CRB_Value v;

  result.type=NORMAL_STATEMENT_RESULT;

  v=crb_eval_expression(inter,env,statement->u.expression_s);
  if(v.type==CRB_STRING_VALUE){
    crb_release_string(v.u.string_value);
  }
  return result;
}

static StatementResult
execute_global_statement(CRB_Interpreter *inter,LocalEnvironment *env,
			 Statement *statement)
{
  IdentifierList *pos;
  StatementResult result;

  IdentifierList *pos;
  StatementResult result;

  result.type=NORMAL_STATEMENT_RESULT;

  if(env==NULL){
    crb_runtime_error(statement->line_number,
		      GLOBAL_STATEMENT_IN_TOPLEVEL_ERR,
		      MESSAGE_ARGUMENT_END);
  }
  for(pos=statement->u.global_s.identifier_list;pos;pos=pos->next){
    GlobalVariableRef *ref_pos;
    GlobalVariableRef *new_ref;
    Variable *variable;

    for(ref_pos=env->global_variable;ref_pos;ref_pos=ref_pos->next){
      if(!strcmp(ref_pos->variable->name,pos->name))
	goto NEXT_IDENTIFIER;
    }
    variable=crb_search_global_variable(inter,pos->name);
    if(variable==NULL){
      crb_runtime_error(statement->line_number,
			GLOBAL_VARIABLE_NOT_FOUND_ERR,
			STRING_MESSAGE_ARGUMENT,"name",pos->name,
			MESSAGE_ARGUMENT_END);
    }
    new_ref=MEM_malloc(sizeof(GlobalVariableRef));
    new_ref->variable=variable;
    new_ref->next=env->global_variable;
    env->global_variable=new_ref;
    NEXT_IDENTIFIER;
    ;
  }
  return result;
}
