#ifndef _PASCAL_H_
#define _PASCAL_H_

using namespace std;

#include <vector>

#define TRUE 1
#define FALSE 0
#define SYS_CON_TRUE 0
#define SYS_CON_FALSE 1
#define SYS_CON_MAXINT 2

#define SYS_TYPE_INTEGER 0
#define SYS_TYPE_REAL 1
#define SYS_TYPE_CHAR 2
#define SYS_TYPE_BOOL 3

#define SYS_FUNCT_ABS 0
#define SYS_FUNCT_CHR 1
#define SYS_FUNCT_ODD 2
#define SYS_FUNCT_ORD 3
#define SYS_FUNCT_PRED 4
#define SYS_FUNCT_SQR 5
#define SYS_FUNCT_SQRT 6
#define SYS_FUNCT_SUCC 7

#define SYS_PROC_WRITE 0
#define SYS_PROC_WRITELN 1

typedef enum { typeCon, typeId, typeOpr, typeType, typeSysProc, typeSysFunc, typeLink } nodeEnum;
//typedef enum {INT_D, CHAR_D, STRING_D, ARRAY_D, ARR}

struct typeNodeStruct{
	int type;
	int array_size;
	struct typeNodeStruct* child;
};
typedef struct typeNodeStruct typeNode;

typedef struct{
	int name;
} sysProcNodeType;

typedef struct{
	int name;
} sysFuncNodeType;

typedef struct{
	int type;
} typeNodeType;

/* constants */
typedef struct {
	int type;		//INTEGER,STRING,CHAR,REAL,BOOL
	union{
		double real;
		int integer;
		char* str;
		char character;
		int boolean;
	};                  
} conNodeType;/* value of constant */

/* identifiers */
typedef struct {
	//int sIndex;                      /* subscript to sym array */
	char *sValue;
} idNodeType;

struct nodeTypeTag ;

/* operators */
typedef struct {
	int oper;                   /* operator */
	int nops;                   /* number of operands */
	struct nodeTypeTag *op[10];  /* operands, extended at runtime */
	//vector<struct nodeTypeTag *> op;
} oprNodeType;

///* link list node */ //for name_list
//typedef enum { NAME_LIST } linkEum;
//
//typedef struct {
//	linkEum tag;
//	struct linkNodeType *next;  
//} linkNodeType;


typedef struct nodeTypeTag {
	nodeEnum type;              /* type of node */
	struct nodeTypeTag* exp;			/* use for type derivation */

	union {
		conNodeType con;        /* constants */
		idNodeType id;          /* identifiers */
		oprNodeType opr;        /* operators */ //records//arrays//enum
		typeNodeType tp;       /*types*/ 
		sysProcNodeType sysProc;
		sysProcNodeType sysFunc;
	};


} nodeType;


#endif