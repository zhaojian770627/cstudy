#ifndef PUBLIC_CRB_H_INCLUDED
#define PUBLIC_CRB_H_INCLUDED
#include <stdio.h>

typedef struct CRB_Interpreter_tag CRB_interperter;

CRG_Interpreter *CRB_create_interpreter(void);
void CRB_compile(CRB_Interperter *interpreter,FILE *fp);
void CRB_interpret(CRB_Interperter *interpreter);
void CRB_dispose_interpreter(CRB_Interpreter *interpreter);

#endif	/* PUBLIC_CRB_H_INCLUDED */
