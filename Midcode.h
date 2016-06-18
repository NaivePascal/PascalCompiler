#ifndef __MID_CODE__
#define __MID_CODE__
#include "node.h"
#include <vector>
/* Macro that checks for a malloc error */
#define CHECK_MEM_ERROR(name) {if (name == NULL) { \
				 printf("Memory allocation error\n"); \
				 exit(1); \
				} \
			}

/* Macro that iterates to the end of a linked list whose next
* element pointer is named "next"
*/
#define GOTO_END_OF_LIST(name) {while (name->next != NULL) \
                                  name = name->next; \
							}
typedef enum{
    CODE, CON_INT,CON_REAL,CON_STRING,CON_CHAR,CON_BOOL,SYSPRO,SYSFUNC
}arg_type;

typedef enum{
	TAC_PROC, TAC_GOTO, TAC_ASSIGN,
	TAC_LABEL, TAC_GE, TAC_GT, TAC_LE, TAC_LT,
	TAC_PARAM, TAC_CALL,
}tac_opt;

///The 3-address-code arg structure
typedef struct{
    int type;
    bool temporary = false;
    int ci = 0;
    double cr = 0 ;
    string cs;
    char cc;
    int cb = 0;
    string id;
	string proc;
	string func;
}Arg;

///3-address-code structure
typedef struct midcode{
    int op;
    Arg arg1;
    Arg arg2;
    Arg result;
}midcode;



void init_Midcode();

/// The Drive function to work with head and tail
int Gen_Drive(nodeType*  root, const char * outputfile);

#endif
