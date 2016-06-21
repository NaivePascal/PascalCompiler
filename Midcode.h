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
/*
typedef enum{
	PROC, GOTO, ASSIGN,
	LABEL, GE, GT, LE, LT,
	PARAM, CALL,
}opt;*/

#define PARAM 256
#define CALL 257

///The 3-address-code arg structure
typedef struct{
    int type;
    bool temporary;
    int ci;
    double cr;
    string cs;
    char cc;
    int cb;
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
