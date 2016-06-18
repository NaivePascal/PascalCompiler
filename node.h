#ifndef _PASCAL_H_
#define _PASCAL_H_

using namespace std;

#include <vector>
#include <map>
#include <vector>

string intToString(int i);
//string doubleToString(double i);



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
		sysFuncNodeType sysFunc;
	};


} nodeType;


class SymbolTag{
	public:
		map<int,string> table;
		SymbolTag();
};
void printTree(nodeType* tree);
#endif