#ifndef __MID_CODE__
#define __MID_CODE__
#include "node.h"
#include <vector>
#include "Parser.h"
#include "symbol.h"
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
/*
%token PARAM CALL CALLEE CMP CMP_NOT CMP_ID CMP_EQUA CMP_UNEQUA CMP_GT CMP_GE CMP_LT CMP_LE	
*/

#define PARAM		113
#define CALL		114
#define RET			115
#define CMP			1
#define CMP_NOT		117
#define CMP_ID		118
#define CMP_EQUAL	119
#define CMP_UNEQUAL 120
#define CMP_GT		121
#define CMP_GE		122
#define CMP_LT		123
#define CMP_LE		124

///The 3-address-code arg structure
struct Arg{
    int type;
    bool temporary;
	bool ifinsubroutine;
	int addr;
    int ci;
    double cr;
    string cs;
    char cc;
    int cb;
    Symbol id;
	int proc;
	int func;

	Arg(){
		type = INTEGER;
		temporary = false;
		ifinsubroutine = false;
		addr = 0;
		ci = 0;
		cr = 0;
		cs = "";
		cc = 0;
		cb = 0;
		proc = 0;
		func = 0;
	}
};

///3-address-code structure
typedef struct midcode{
    int op;
    Arg arg1;
    Arg arg2;
    Arg result;
}midcode;

extern map<string, Scope>  gen_symbol_table;
extern vector<Arg> Arg_list; //Master list of all Arg data
extern vector<midcode> midcode_list;
extern int labels;
extern int tmps;
extern int mains;

void init_Midcode();

/// The Drive function to work with head and tail
int Gen_Drive(nodeType*  root, const char * outputfile);
void GenControl(nodeType* pnode, Arg label1, Arg label2);
Arg GenCode(nodeType* pnode);
Arg GenCon(nodeType* pnode);
Arg GenId(nodeType* pnode);
Arg GenOpr(nodeType* pnode);
int GenType(nodeType* pnode);
Arg GenSysProc(nodeType* pnode);
Arg GenSysFunc(nodeType* pnode);
void GenLink(nodeType* pnode);
string printArg(Arg in);

#endif
