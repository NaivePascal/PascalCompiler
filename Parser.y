%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <iostream>
#include "pascal.h"
#include "Lexer.h"

int yylex(void);
void yyerror(char *s);
nodeType *con(void* value,int type);
//nodeType *id(int i);
nodeType *id(char *name);
nodeType *tp(int i);
nodeType *sysProc(int i);
//nodeType *sysProc(char *name);
nodeType *sysFunc(int i);
//nodeType *sysFunc(char *name);
nodeType *opr(int oper, int nops, ...);
void freeNode(nodeType *p) ;

//int count;

//hdj: symbol table
void insert(char *name, nodeType* type);
void print_info();
void enter_scope();
void exit_scope();
nodeType* lookup(string name);
bool type_equal(nodeType *n1, nodeType *n2);
string type_str(nodeType *node);
void type_error(const char *s) {
  printf("type error at line %d: %s\n", yylineno,s); //exit(42);
}

nodeType *lookup_field_in_record(char* name, nodeType *record);
bool name_list_equal(nodeType *n1, nodeType *n2);
bool const_value_equal(nodeType *n1, nodeType *n2);
nodeType *check_record_access(char *record, char *field);
nodeType *check_array_access(char *array, nodeType *index);
bool check_case_expression(nodeType *expression, nodeType *cases);
bool check_parameters(nodeType *function_head, nodeType* parameters);
vector<nodeType*> get_para_names(nodeType *function_head);
vector<nodeType*> get_para_types(nodeType *function_head);
vector<nodeType*> flatten(nodeType *root);
//symbol table end

%}

%output  "Parser.cpp"
%defines "Parser.h"

%union {
	int iValue;
	char* sValue;
	char cValue;
	double rValue;
	int sIndex;
	int sysType;
	int syscon;
	int sysProc;
	int sysFunc;
	struct nodeTypeTag* nodetype;
}
%token <iValue> INTEGER
%token <sValue> STRING
%token <cValue>  CHAR
%token <rValue> REAL
//%token <sIndex> ID
%token <sValue> ID

%token <syscon> SYS_CON
%token <sysType> SYS_TYPE
%token <sysProc> SYS_PROC
%token <sysFunc> SYS_FUNCT

%token  THEN CONST DO READ EQUAL GOTO WHILE PROGRAM MUL PLUS UNEQUAL DIV MINUS DOT 
%token  CASE PBEGIN LE LB SEMI TO UNTIL DOTDOT RECORD LT COLON RB ARRAY ASSIGN FUNCTION REPEAT END 
%token  LP FOR ELSE GE VAR RP PROCEDURE IF AND GT OF DOWNTO NOT COMMA TYPE OR MOD 

%token PROGRAM ROUTINE ROUTINE_HEAD CONST_PART CONST_EXPR_LIST CONST_EXPR
%token CONST_VALUE TYPE_PART TYPE_DECL_LIST TYPE_DEFINITION TYPE_DECL
%token SIMPLE_TYPE_DECL ARRAY_TYPE_DECL RECORD_TYPE_DECL FIELD_DECL_LIST
%token FIELD_DECL NAME_LIST VAR_PART VAR_DECL_LIST VAR_DECL ROUTINE_PART 
%token FUNCTION_DECL FUNCTION_HEAD PROCEDURE_DECL PROCEDURE_HEAD PARAMETERS
%token PARA_DECL_LIST PARA_TYPE_LIST VAR_PARA_LIST VAL_PARA_LIST ROUTINE_BODY
%token COMPOUND_STMT STMT_LIST STMT NON_LABEL_STMT ASSIGN_STMT PROC_STMT
%token IF_STMT ELSE_CLAUSE REPEAT_STMT WHILE_STMT FOR_STMT CASE_STMT CASE_EXPR_LIST
%token CASE_EXPR GOTO_STMT EXPRESSION_LIST EXPRESSION EXPR TERM FACTOR ARGS_LIST
%token SUB_ROUTINE BOOL CONST_POSITIVE_POSITIVE CONST_NEGATIVE_POSITIVE CONST_NEGATIVE_NEGATIVE
%token ENUM ID_ID

%type <nodetype> program routine routine_head  const_part const_expr_list const_expr
%type <nodetype> const_value type_part type_decl_list type_definition type_decl
%type <nodetype> simple_type_decl array_type_decl record_type_decl field_decl_list
%type <nodetype> field_decl name_list var_part var_decl_list var_decl routine_part 
%type <nodetype> function_decl function_head procedure_decl procedure_head parameters
%type <nodetype> para_decl_list para_type_list var_para_list val_para_list routine_body
%type <nodetype> compound_stmt stmt_list stmt non_label_stmt assign_stmt proc_stmt
%type <nodetype> if_stmt else_clause repeat_stmt while_stmt for_stmt case_stmt case_expr_list
%type <nodetype> case_expr goto_stmt expression_list expression expr term factor args_list
%type <nodetype> sub_routine

%left PLUS
%left OR
%%

program			: program_head  routine  DOT{
					$$ = $2;
					//hdj
					//program ends, exit scope
					exit_scope();
				}
				;	
						
program_head	: PROGRAM  ID  SEMI
				{
					//hdj
					//program starts, enter new scope
					enter_scope();
				}
				;			
						
routine			: routine_head  routine_body
				{$$ = opr(ROUTINE,2,$1,$2);}
				;	
						
sub_routine		: routine_head  routine_body
				{$$ = opr(ROUTINE,2,$1,$2);}
				;							

routine_head	: label_part const_part type_part var_part  routine_part
				{$$ = opr(ROUTINE_HEAD,3,$2,$3,$4);}
				;

label_part		: ;

const_part		: CONST const_expr_list{
					$$=$2;
}								  
				| 
				{$$ = NULL;}
				;											
					
const_expr_list : const_expr_list  const_expr  SEMI	{
					$$ = opr(SEMI,2,$1,$2);
}	
				|  const_expr  SEMI{
					$$ = $1;
				};

const_expr :  ID  EQUAL  const_value {
					$$ = opr(CONST_EXPR,2,id($1),$3);
					//example:
					//const
					//PI = 3.141592654;
					insert($1, $3);
};

const_value		: INTEGER  {$$ = con(&($1),INTEGER);}
				|  REAL  {$$ = con(&($1),REAL);}
				|  CHAR  {$$ = con(&($1),CHAR);}
				|  STRING  {$$ = con(($1),STRING);}
				|  SYS_CON {
					if($1==SYS_CON_TRUE){
						int value = TRUE;
						$$ = con(&value,BOOL);
					}else if($1==SYS_CON_FALSE){
						int value = FALSE;
						$$ = con(&value,BOOL);
					}else if($1==SYS_CON_MAXINT){
						int value = INT_MAX;
						$$ = con(&value, INTEGER);
					}
				}
				;

type_part		: TYPE type_decl_list{
					$$ = $2;
				}  
				|  
				{$$=NULL;}
				;

type_decl_list	: type_decl_list  type_definition{
					$$=opr(SEMI,2,$1,$2);
}
				|  type_definition{
					$$=$1;
				};

type_definition : ID  EQUAL  type_decl  SEMI{
					$$=opr(TYPE_DEFINITION,2,$1,$3);

					//example:
					//type
					//days, age = integer;
					insert($1, $3);

};

type_decl		: simple_type_decl  {$$=$1;}
				|  array_type_decl  {$$=$1;}
				|  record_type_decl {$$=$1;};

simple_type_decl: SYS_TYPE  {$$=tp($1);}
				|  ID  
				{$$=id($1);}
				|  LP  name_list  RP  
				{
					//$$=$2;
					$$=opr(ENUM, 1, $2);
				}
				|  const_value  DOTDOT  const_value 
				{
					//check error : Upper bound of range is less than lower bound
					$$=opr(CONST_POSITIVE_POSITIVE,2,$1,$3);
				}
				|  MINUS  const_value  DOTDOT  const_value
				{
					$$=opr(CONST_NEGATIVE_POSITIVE,2,$2,$4);
				}
				|  MINUS  const_value  DOTDOT  MINUS  const_value
				{
					$$=opr(CONST_NEGATIVE_NEGATIVE,2,$2,$5);
				}
				|  ID  DOTDOT  ID
				{
					$$=opr(ID_ID,2,$1,$3);
				}
				;

array_type_decl : ARRAY  LB  simple_type_decl  RB  OF  type_decl
				{
					$$=opr(ARRAY_TYPE_DECL,2,$3,$6);
					//type check
					//index-type can be any scalar data type except real
					if($3->type == typeType){
						if($3->tp.type == SYS_TYPE_REAL){
							type_error("Error in type definition");
						}
					}
					else if($3->type == typeOpr){
						if($3->opr.oper == ENUM||$3->opr.oper==CONST_POSITIVE_POSITIVE||$3->opr.oper==CONST_NEGATIVE_NEGATIVE){

						}
						else{
							type_error("Error in type definition");	
						}
					}
				}
				;

record_type_decl: RECORD  field_decl_list  END
				{
					//$$=$2;
					$$=opr(RECORD_TYPE_DECL, 1, $2);
				}
				;

field_decl_list : field_decl_list  field_decl
				{$$=opr(FIELD_DECL_LIST,2,$1,$2);}  
				|  field_decl{$$=$1;}
				;

field_decl		: name_list  COLON  type_decl  SEMI
				{$$=opr(FIELD_DECL,2,$1,$3);}
				;

name_list		: name_list  COMMA  ID 
				{
					$$=opr(NAME_LIST,2,$1,id($3));
				} 
				|  ID 
				{
					$$=id($1);
				}
				;

var_part		: VAR  var_decl_list  {$$=$2;}
				|
				{$$=NULL;}
				;

var_decl_list	: var_decl_list  var_decl  
				{$$=opr(VAR_DECL_LIST,2,$1,$2);}
				|  var_decl{$$=$1;};

var_decl		: name_list  COLON  type_decl  SEMI
				{
					$$=opr(VAR_DECL,2,$1,$3);
					//just one name
					if($1->type==typeId){
						insert($1->id.sValue, $3);
					}
					//more than one name
					else{
						nodeType *p = $1;
						while(1){
							insert(p->opr.op[1]->id.sValue, $3);
							p = p->opr.op[0];
							if(p->type==typeId)
								break;
						}
						insert(p->id.sValue, $3);
					}

				}
				;

routine_part	:  routine_part  function_decl  
				{$$=opr(ROUTINE_PART,2,$1,$2);}
				|  routine_part  procedure_decl
				{$$=opr(ROUTINE_PART,2,$1,$2);}
				|  function_decl
				{$$=opr(ROUTINE_PART,1,$1);}
				|  procedure_decl  
				{$$=opr(ROUTINE_PART,1,$1);}
				|
				{$$=NULL;}
				;

function_decl	: function_head  SEMI  sub_routine  SEMI
				{
				//hdj:function overloading is not supported yet
				//example:
				//function max(num1, num2: integer): integer;
					$$=opr(FUNCTION_DECL,2,$1,$3);
				
				// a function is finished, now exit its scope
				exit_scope();
				
				}
				;

function_head	:  FUNCTION  ID  parameters  COLON  simple_type_decl
				{
					nodeType* node = opr(FUNCTION_HEAD,3,id($2),$3,$5);
					$$= node;
					insert($2, node);

					//hdj
					//enter a new scope
					enter_scope();
					vector<nodeType*> parameters = get_para_names(node);
					vector<nodeType*> types = get_para_types(node);
					for(int i=0;i<types.size();i++){
						insert(parameters[i]->id.sValue, types[i]);
					}
				}
				;

procedure_decl	:  procedure_head  SEMI  sub_routine  SEMI
				{
					opr(PROCEDURE_DECL,2,$1,$3);
					// a procedure is finished, now exit its scope
					exit_scope();
				}
				;

procedure_head	:  PROCEDURE ID parameters
				{
					nodeType* node = opr(PROCEDURE_HEAD,2,id($2),$3);
					$$=node;
					insert($2, node);
					//enter a new scope
					enter_scope();
					vector<nodeType*> parameters = get_para_names(node);
					vector<nodeType*> types = get_para_types(node);
					for(int i=0;i<types.size();i++){
						insert(parameters[i]->id.sValue, types[i]);
					}
				}
				;

parameters		: LP  para_decl_list  RP  
				{$$=$2;}
				|
				{$$=NULL;}
				;

para_decl_list	: para_decl_list  SEMI  para_type_list 
				{$$=opr(PARA_DECL_LIST,2,$1,$3);}
				| para_type_list
				{$$=$1;}
				;

para_type_list	: var_para_list COLON  simple_type_decl
				{
					$$=opr(PARA_TYPE_LIST,2,$1,$3);
				}  
				| val_para_list COLON simple_type_decl
				{
					//$$=$1;
					$$=opr(PARA_TYPE_LIST,2,$1,$3);
				}
				;

var_para_list	: VAR  name_list
				{$$=opr(VAR_PARA_LIST,1,$2);}
				;

val_para_list	: name_list
				{$$=$1;}
				;

routine_body	: compound_stmt
				{$$=$1;}
				;

compound_stmt	: PBEGIN  stmt_list  END	
				{$$=$2;}
				;

stmt_list		: stmt_list  stmt  SEMI  
				{$$=opr(STMT_LIST,2,$1,$2);}
				|
				{$$=NULL;}  
				;

stmt			: INTEGER  COLON  non_label_stmt 
				{$$=opr(COLON,2,con(&($1),INTEGER),$3);} 
				|  non_label_stmt
				{$$=$1;} 
				;

non_label_stmt	: assign_stmt 
				{$$=$1;}
				| proc_stmt
				{$$=$1;} 
				| compound_stmt
				{$$=$1;} 
				| if_stmt
				{$$=$1;} 
				| repeat_stmt
				{$$=$1;} 
				| while_stmt
				{$$=$1;} 
				| for_stmt
				{$$=$1;} 
				| case_stmt
				{$$=$1;} 
				| goto_stmt
				{$$=$1;}
				;

assign_stmt		: ID  ASSIGN  expression
				{
					$$=opr(ASSIGN,2,id($1),$3);
					nodeType *check = $3;
					//type check
					//not consider array assignment yet
					char message[100];
					nodeType *node = lookup($1);
					if(node->type == typeType){
						// REAL := REAL or INT
						if(node->tp.type == SYS_TYPE_REAL){
							//if($3->exp->type != SYS_TYPE_REAL && $3->exp->type!=SYS_TYPE_INTEGER){
							if( !(type_equal(tp(SYS_TYPE_REAL),$3->exp)||type_equal(tp(SYS_TYPE_INTEGER),$3->exp)) ){
								sprintf(message, "\"%s\" expected but \"%s\" found", type_str(node).data(), type_str($3->exp).data());
								type_error(message);
							}
						}
						//others
						else if(!type_equal(node,$3->exp)){
							sprintf(message, "\"%s\" expected but \"%s\" found", type_str(node).data(), type_str($3->exp).data());
							type_error(message);
						}
					}
					//function return value
					else if(node->type == typeOpr && node->opr.oper == FUNCTION_HEAD){
						//check return value
						nodeType *returnType = node->opr.op[2];
						if(!type_equal(returnType, $3->exp)){
							sprintf(message, "\"%s\" expected but \"%s\" found", type_str(returnType).data(), type_str($3->exp).data());
							type_error(message);
						}
					}
					else{
						sprintf(message, "Variable identifier expected");
							type_error(message);
					}
				}
				| ID LB expression RB ASSIGN expression
				{
					$$=opr(ASSIGN,3,id($1),$3,$6);
					//type check
					nodeType *check1 = $3;
					nodeType *check2 = $6;
					
					char message[200];
					nodeType *node = lookup($1);
					if(node->type == typeOpr && node->opr.oper == ARRAY_TYPE_DECL){
						//incompatible index type 
						if(!type_equal(node->opr.op[0], $3->exp)){
							sprintf(message, "incompatible index type, \"%s\" expected but \"%s\" found", type_str(node->opr.op[0]).data(), type_str($3->exp).data());
							type_error(message);
						}
						//incompatible element type 
						if(!type_equal(node->opr.op[1],$6->exp)){
							string tinfo1 = type_str(node->opr.op[1]);
							string tinfo2 = type_str($6->exp);
							//sprintf("incompatible element type, \"%s\" expected but \"%s\" found", type_str(node->opr.op[1]).data(), type_str($6->exp).data());
							sprintf(message, "incompatible element type, \"%s\" expected but \"%s\" found", tinfo1.data(), tinfo2.data());
							
							type_error(message);
						}
					}
					else{
						sprintf(message, "%s is not an array", $1);
						type_error(message);
					}
				}
				| ID  DOT  ID  ASSIGN  expression 				
				{

					$$=opr(ASSIGN,3,id($1),id($3),$5);
					nodeType *field = check_record_access($1, $3);

					if(!type_equal(field, $5->exp)){
						char message[100];
						sprintf(message, "\"%s\" expected but \"%s\" found", type_str(field).data(), type_str($5->exp).data());
						type_error(message);
					}
					//type check
					/*char message[100];
					nodeType *node = lookup($1);
					if(node->type == typeOpr && node->opr.oper == RECORD_TYPE_DECL){
						//search given field in field_list
						nodeType *field = lookup_field_in_record($3, node);
						if(field == NULL){
							sprintf(message, "%s is not a member of %s", $3, $1);
							type_error(message);
						}
						else if(!type_equal(field, $5)){
							sprintf(message, "\"%s\" expected but \"%s\" found", type_str(field).data(), type_str($5).data());
							type_error(message);
						}
					}
					else{
						sprintf(message, "%s is not a record", $1);
						type_error(message);
					}*/

				}
				;


proc_stmt		: ID
				{$$=opr(PROC_STMT,1,id($1));}
				|  ID  LP  args_list  RP
				{$$=opr(PROC_STMT,2,id($1),$3);}
				|  SYS_PROC
				{$$=opr(PROC_STMT,1,sysProc($1));}
				|  SYS_PROC  LP  expression_list  RP
				{$$=opr(PROC_STMT,2,sysProc($1),$3);}
				|  READ  LP  factor  RP
				{$$=opr(READ,1,$3);}
				;

if_stmt			: IF  expression  THEN  stmt  else_clause
				{
					$$=opr(IF,3,$2,$4,$5);
					//check if condition(expression) is boolean
					if(!type_equal(tp(SYS_TYPE_BOOL),$2->exp)){
						char message[100];
						sprintf(message, "boolean expected but \"%s\" found", type_str($2->exp).data());
						type_error(message);
					}
				}
else_clause		: ELSE stmt 
				{$$=$2;}
				|  {$$=NULL;};

repeat_stmt		: REPEAT  stmt_list  UNTIL  expression
				{
					$$=opr(REPEAT,2,$2,$4);
					//type check: until expression should be boolean
					if(!type_equal(tp(SYS_TYPE_BOOL), $4->exp)){
						char message[100];
						sprintf(message, " \"boolean\" expression expected but found \"%s\"", type_str($4->exp).data());
						type_error(message);
					}
				}
				;

while_stmt		: WHILE  expression  DO stmt
				{
					$$=opr(WHILE,2,$2,$4);	
					//check while condition (expression) is boolean
					if(!type_equal(tp(SYS_TYPE_BOOL),$2->exp)){
						char message[100];
						sprintf(message, "boolean expected but \"%s\" found", type_str($2->exp).data());
						type_error(message);
					}
				}
				;

for_stmt		: FOR  ID  ASSIGN  expression  direction  expression  DO stmt
				{
					//type check:id-expression
					nodeType *node = lookup($2);

					if(!type_equal(tp(SYS_TYPE_INTEGER), node)){
						char message[100];
						sprintf(message, "\"integer\" expected but \"%s\" found", type_str(node).data());
						type_error(message);
					}

					if(!type_equal(tp(SYS_TYPE_INTEGER), $4->exp)){
						char message[100];
						sprintf(message, "\"integer\" expected but \"%s\" found", type_str($4->exp).data());
						type_error(message);
					}
					if(!type_equal(tp(SYS_TYPE_INTEGER), $6->exp)){
						char message[100];
						sprintf(message, "\"integer\" expected but \"%s\" found", type_str($6->exp).data());
						type_error(message);
					}

					$$=opr(FOR,5,id($2),$4,$6,$8);
				}
				;
direction		: TO 
				| DOWNTO;

case_stmt		: CASE expression OF case_expr_list  END
				{
					$$=opr(CASE,2,$2,$4);
					//type check:expression--case_expr
					if(!check_case_expression($2->exp, $4)){
						type_error("Constant and CASE types do not match");
					}
				}
				;

case_expr_list	: case_expr_list  case_expr 
				{$$=opr(CASE_EXPR_LIST,2,$1,$2);}
				|  case_expr
				{$$=$1;}
				;


case_expr		: const_value  COLON  stmt  SEMI
				{$$=opr(CASE_EXPR,2,$1,$3);}
				|  ID  COLON  stmt  SEMI
				{$$=opr(CASE_EXPR,2,id($1),$3);}
				;

goto_stmt		: GOTO  INTEGER
				{$$=con(&($2),INTEGER);}
				;

expression_list : expression_list  COMMA  expression
				{$$=opr(EXPRESSION_LIST,2,$1,$3);}  
				|  expression
				{$$=$1;}
				;

expression		: expression  GE  expr 
				{
					//$$=opr(GE,2,$1,$3);
					if(( type_equal(tp(SYS_TYPE_REAL),$1->exp)||type_equal(tp(SYS_TYPE_INTEGER),$1->exp) ) 
					&& ( type_equal(tp(SYS_TYPE_REAL),$3->exp)||type_equal(tp(SYS_TYPE_INTEGER),$3->exp) )){
						nodeType* node = opr(GE, 2, $1, $3);
						node->exp = tp(SYS_TYPE_BOOL);
						$$ = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \">=\" not supported for types \"%s\" and \"%s\"", type_str($1->exp).data(), type_str($3->exp).data());
						type_error(messgae);
					}
				}
				|  expression  GT  expr
				{
					//$$=opr(GT,2,$1,$3);
					if(( type_equal(tp(SYS_TYPE_REAL),$1->exp)||type_equal(tp(SYS_TYPE_INTEGER),$1->exp) ) 
					&& ( type_equal(tp(SYS_TYPE_REAL),$3->exp)||type_equal(tp(SYS_TYPE_INTEGER),$3->exp) )){
						nodeType* node = opr(GT, 2, $1, $3);
						node->exp = tp(SYS_TYPE_BOOL);
						$$ = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \">\" not supported for types \"%s\" and \"%s\"", type_str($1->exp).data(), type_str($3->exp).data());
						type_error(messgae);
					}
				}  
				|  expression  LE  expr
				{
					//$$=opr(LE,2,$1,$3);
					if(( type_equal(tp(SYS_TYPE_REAL),$1->exp)||type_equal(tp(SYS_TYPE_INTEGER),$1->exp) ) 
					&& ( type_equal(tp(SYS_TYPE_REAL),$3->exp)||type_equal(tp(SYS_TYPE_INTEGER),$3->exp) )){
						nodeType* node = opr(LE, 2, $1, $3);
						node->exp = tp(SYS_TYPE_BOOL);
						$$ = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \"<=\" not supported for types \"%s\" and \"%s\"", type_str($1->exp).data(), type_str($3->exp).data());
						type_error(messgae);
					}
				}
				|  expression  LT  expr  
				{
					//$$=opr(LT,2,$1,$3);
					if(( type_equal(tp(SYS_TYPE_REAL),$1->exp)||type_equal(tp(SYS_TYPE_INTEGER),$1->exp) ) 
					&& ( type_equal(tp(SYS_TYPE_REAL),$3->exp)||type_equal(tp(SYS_TYPE_INTEGER),$3->exp) )){
						nodeType* node = opr(LT, 2, $1, $3);
						node->exp = tp(SYS_TYPE_BOOL);
						$$ = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \"<\" not supported for types \"%s\" and \"%s\"", type_str($1->exp).data(), type_str($3->exp).data());
						type_error(messgae);
					}
				}
				|  expression  EQUAL  expr
				{
					//$$=opr(EQUAL,2,$1,$3);
					if(( type_equal(tp(SYS_TYPE_REAL),$1->exp)||type_equal(tp(SYS_TYPE_INTEGER),$1->exp) ) 
					&& ( type_equal(tp(SYS_TYPE_REAL),$3->exp)||type_equal(tp(SYS_TYPE_INTEGER),$3->exp) )){
						nodeType* node = opr(EQUAL, 2, $1, $3);
						node->exp = tp(SYS_TYPE_BOOL);
						$$ = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \"==\" not supported for types \"%s\" and \"%s\"", type_str($1->exp).data(), type_str($3->exp).data());
						type_error(messgae);
					}
				}  
				|  expression  UNEQUAL  expr
				{
					//$$=opr(UNEQUAL,2,$1,$3);
					if(( type_equal(tp(SYS_TYPE_REAL),$1->exp)||type_equal(tp(SYS_TYPE_INTEGER),$1->exp) ) 
					&& ( type_equal(tp(SYS_TYPE_REAL),$3->exp)||type_equal(tp(SYS_TYPE_INTEGER),$3->exp) )){
						nodeType* node = opr(UNEQUAL, 2, $1, $3);
						node->exp = tp(SYS_TYPE_BOOL);
						$$ = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \"!=\" not supported for types \"%s\" and \"%s\"", type_str($1->exp).data(), type_str($3->exp).data());
						type_error(messgae);
					}
				}  
				|  expr
				{$$=$1;}
				;

expr			: expr  PLUS  term
				{
					//$$=opr(PLUS,2,$1,$3);
					nodeType *check1 = $1;
					nodeType *check2 = $3;

					if(( type_equal(tp(SYS_TYPE_REAL),$1->exp)||type_equal(tp(SYS_TYPE_INTEGER),$1->exp) ) 
					&& ( type_equal(tp(SYS_TYPE_REAL),$3->exp)||type_equal(tp(SYS_TYPE_INTEGER),$3->exp) )){
						nodeType* node = opr(PLUS, 2, $1, $3);
						//both integer, result is integer
						if(type_equal(tp(SYS_TYPE_INTEGER),$1->exp) && type_equal(tp(SYS_TYPE_INTEGER),$3->exp))
							node->exp = tp(SYS_TYPE_INTEGER);
						//one of them is real, result should be real
						else
							node->exp = tp(SYS_TYPE_REAL);
						$$ = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \"plus\" not supported for types \"%s\" and \"%s\"", type_str($1->exp).data(), type_str($3->exp).data());
						type_error(messgae);
					}
				}
				|  expr  MINUS  term 
				{
					//$$=opr(MINUS,2,$1,$3);
					if(( type_equal(tp(SYS_TYPE_REAL),$1->exp)||type_equal(tp(SYS_TYPE_INTEGER),$1->exp) ) 
					&& ( type_equal(tp(SYS_TYPE_REAL),$3->exp)||type_equal(tp(SYS_TYPE_INTEGER),$3->exp) )){
						nodeType* node = opr(MINUS, 2, $1, $3);
						//both integer, result is integer
						if(type_equal(tp(SYS_TYPE_INTEGER),$1->exp) && type_equal(tp(SYS_TYPE_INTEGER),$3->exp))
							node->exp = tp(SYS_TYPE_INTEGER);
						//one of them is real, result should be real
						else
							node->exp = tp(SYS_TYPE_REAL);
						$$ = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \"minus\" not supported for types \"%s\" and \"%s\"", type_str($1->exp).data(), type_str($3->exp).data());
						type_error(messgae);
					}
				} 
				|  expr  OR  term
				{
					//$$=opr(OR,2,$1,$3);
					nodeType *check1 = $1;
					nodeType *check2 = $3;
					if(type_equal(tp(SYS_TYPE_BOOL),$1->exp) && type_equal(tp(SYS_TYPE_BOOL),$3->exp)){
						nodeType* node = opr(OR, 2, $1, $3);
						node->exp = tp(SYS_TYPE_BOOL);
						$$ = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \"or\" not supported for types \"%s\" and \"%s\"", type_str($1->exp).data(), type_str($3->exp).data());
						type_error(messgae);
					}
				}
				|  term
				{
					$$=$1;
				}
				;

term			: term  MUL  factor
				{
					//$$=opr(MUL,2,$1,$3);
					if(( type_equal(tp(SYS_TYPE_REAL),$1->exp)||type_equal(tp(SYS_TYPE_INTEGER),$1->exp) ) 
					&& ( type_equal(tp(SYS_TYPE_REAL),$3->exp)||type_equal(tp(SYS_TYPE_INTEGER),$3->exp) )){
						nodeType* node = opr(MUL, 2, $1, $3);
						//both integer, result is integer
						if(type_equal(tp(SYS_TYPE_INTEGER),$1->exp) && type_equal(tp(SYS_TYPE_INTEGER),$3->exp))
							node->exp = tp(SYS_TYPE_INTEGER);
						//one of them is real, result should be real
						else
							node->exp = tp(SYS_TYPE_REAL);
						$$ = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \"mul\" not supported for types \"%s\" and \"%s\"", type_str($1->exp).data(), type_str($3->exp).data());
						type_error(messgae);
					}
				}
				|  term  DIV  factor
				{
					//$$=opr(DIV,2,$1,$3);
					if(( type_equal(tp(SYS_TYPE_REAL),$1->exp)||type_equal(tp(SYS_TYPE_INTEGER),$1->exp) ) 
					&& ( type_equal(tp(SYS_TYPE_REAL),$3->exp)||type_equal(tp(SYS_TYPE_INTEGER),$3->exp) )){
						nodeType* node = opr(DIV, 2, $1, $3);
						//both integer, result is integer
						if(type_equal(tp(SYS_TYPE_INTEGER),$1->exp) && type_equal(tp(SYS_TYPE_INTEGER),$3->exp))
							node->exp = tp(SYS_TYPE_INTEGER);
						//one of them is real, result should be real
						else
							node->exp = tp(SYS_TYPE_REAL);
						$$ = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \"div\" not supported for types \"%s\" and \"%s\"", type_str($1->exp).data(), type_str($3->exp).data());
						type_error(messgae);
					}
				}  
				|  term  MOD  factor
				{
					//$$=opr(MOD,2,$1,$3);
					if(type_equal(tp(SYS_TYPE_INTEGER),$1->exp) && type_equal(tp(SYS_TYPE_INTEGER),$3->exp)){
						nodeType* node = opr(MOD, 2, $1, $3);
						node->exp = tp(SYS_TYPE_INTEGER);
						$$ = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \"mod\" not supported for types \"%s\" and \"%s\"", type_str($1->exp).data(), type_str($3->exp).data());
						type_error(messgae);
					}
				} 
				|  term  AND  factor
				{
					//$$=opr(AND,2,$1,$3);
					//if($1->exp->tp.type == SYS_TYPE_BOOL && $3->exp->tp.type == SYS_TYPE_BOOL){
					if(type_equal(tp(SYS_TYPE_BOOL),$1->exp) && type_equal(tp(SYS_TYPE_BOOL),$3->exp)){
						nodeType* node = opr(AND, 2, $1, $3);
						node->exp = tp(SYS_TYPE_BOOL);
						$$ = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \"and\" not supported for types \"%s\" and \"%s\"", type_str($1->exp).data(), type_str($3->exp).data());
						type_error(messgae);
					}
				}  
				|  factor
				{
					$$=$1;
				}
				;

factor			: ID  
				{
					//$$=id($1);
					nodeType *node = id($1);
					nodeType *refer = lookup($1);
					node->exp = refer;
					//if it is function
					if(refer->type==typeOpr && refer->opr.oper == FUNCTION_HEAD){
						//this function should not have any parameters
						nodeType* parameters = refer->opr.op[1];
						if(parameters!=NULL){
							char messgae[100];
							sprintf(messgae, "no parameters found for function %s", $1);
							type_error(messgae);
						}
						else{
							//return type
							node->exp = refer->opr.op[2];
						}
					}
					$$=node;
				}
				|  ID  LP  args_list  RP
				{
					//$$=opr(LP,2,$1,$3);
					nodeType *node = opr(LP, 2, $1, $3);
					nodeType *refer = lookup($1);
					if(refer->type==typeOpr && refer->opr.oper == FUNCTION_HEAD){
						//check parameters!!!
						check_parameters(refer, $3);
					}
					else{
						//not a function/procedure
						char message[100];
						sprintf(message, "\"function\" expected but \"%s\" found", type_str(node).data());
						type_error(message);
					}
					node->exp = refer->opr.op[2];//return type
					$$=node;
				}  
				|  SYS_FUNCT 
				{
					//$$=sysFunc($1);
					nodeType *node=sysFunc($1);
					node->exp = node;
					$$ = node;
				}
				|  SYS_FUNCT  LP  args_list  RP
				{
					//$$=opr(SYS_FUNCT,2,$1,$3);
					//..never check input type now
					nodeType *node=sysFunc($1);
					switch($1){
						case SYS_FUNCT_ABS:{
							node->exp=tp(SYS_TYPE_INTEGER);
							break;
						}
						case SYS_FUNCT_CHR:{
							node->exp=tp(SYS_TYPE_CHAR);
							break;
						}
						case SYS_FUNCT_ODD:{
							node->exp=tp(SYS_TYPE_BOOL);
							break;
						}
						case SYS_FUNCT_ORD:{
							//..need to be done
							node->exp=tp(SYS_TYPE_INTEGER);
							break;
						}
						case SYS_FUNCT_PRED:{
							node->exp=tp(SYS_TYPE_INTEGER);
							break;
						}
						case SYS_FUNCT_SQR:{
							node->exp=tp(SYS_TYPE_REAL);
							break;
						}
						case SYS_FUNCT_SQRT:{
							node->exp=tp(SYS_TYPE_REAL);
							break;
						}
						case SYS_FUNCT_SUCC:{
							node->exp=tp(SYS_TYPE_INTEGER);
							break;
						}
					}
					$$ = node;
				}  
				|  const_value
				{
					//$$=$1;
					nodeType *node = $1;
					node->exp = $1;
					$$ = node;
				}  
				|  LP  expression  RP
				{
					$$=$2;
				}
				|  NOT  factor
				{
					//$$=opr(NOT,1,$2);
					//check_not_exp($2->exp);
					if(type_equal(tp(SYS_TYPE_BOOL),$2->exp)){
						nodeType *node = opr(NOT, 1, $2);
						node->exp = $2->exp;
						$$ = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \"not\" not supported for type \"%s\" ", type_str($2->exp).data());
						type_error(messgae);
					}
				}  
				|  MINUS  factor  
				{
					//$$=opr(MINUS,1,$2);
					//check_minus_exp($2->exp);
					if(type_equal(tp(SYS_TYPE_REAL),$2->exp)||type_equal(tp(SYS_TYPE_INTEGER),$2->exp) ){
						nodeType* node = opr(MINUS, 1, $2);
						node->exp = $2->exp;
						$$ = node;
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \"minus\" not supported for type \"%s\" ", type_str($2->exp).data());
						type_error(messgae);
					}
				}
				|  ID  LB  expression  RB
				{
					//access array
					//$$=opr(LB,2,id($1),$3);
					nodeType* node = opr(LB,2,id($1), $3);
					nodeType*element = check_array_access($1,$3->exp);
					node->exp = element;
					$$ = node;
				}
				|  ID  DOT  ID
				{
					//$$=opr(DOT,2,id($1),id($3));
					//access record
					nodeType *node = opr(DOT,2,id($1),id($3));
					nodeType *field = check_record_access($1, $3);
					node->exp = field;
					$$ = node;
				}
				;

args_list		: args_list  COMMA  expression 
				{$$=opr(ARGS_LIST,2,$1,$3);} 
				|  expression
				{$$=$1;}
				;


%%



//hdj: symbol table
#include <map>
#include <string>
#include <vector>

using namespace std;

/*struct Symbol {
	nodeType *type;
	map<string, nodeType*> record;
};*/
bool lookup_in_name_list(char *name, nodeType *name_list);
bool isSubrange(nodeType *node){
	return node->type == typeOpr && (
		node->opr.oper == CONST_NEGATIVE_NEGATIVE||
		node->opr.oper == CONST_NEGATIVE_POSITIVE||
		node->opr.oper == CONST_POSITIVE_POSITIVE);
}

vector<map<string, nodeType*>> symbol_table_stack;
//vector<map<string, symbol>> Symbol_table_stack;

void insert(char *name, nodeType* type){
	/*Symbol symbol;
	symbol.type = type;
	symbol_table_stack.back()[name] = symbol;*/
	symbol_table_stack.back()[name] = type;
}

/*map<string, nodeType*> convert_node_to_record(nodeType *node){
	node->
}*/

/*void insert(char *name, const map<string, nodeType*> &record){
	Symbol symbol;
	symbol.record = record;
	symbol_table_stack.back()[name] = symbol;	
}*/

void enter_scope(){
	symbol_table_stack.push_back(map<string, nodeType*>());
}

void exit_scope(){
	symbol_table_stack.pop_back();
}

nodeType* _lookup(string name){
	//traverse the stack backwards to find symbol
	for(auto iter=symbol_table_stack.rbegin();iter!=symbol_table_stack.rend();iter++){
		auto item = iter->find(name);
		if(item!=iter->end()){
			return item->second; //return node information
		}
	}

	//nothing found, return NULL/type error
	char message[100];
	sprintf(message, "Identifier not found \"%s\"", name.data());
	type_error(message);
	return NULL;
}

nodeType* lookup(string name){
	nodeType *result = _lookup(name);
	if(result->type == typeId) //if the id points to another id( type xx:yy var a:xx)
		return lookup(result->id.sValue);
	else
		return result;
}

bool type_equal(nodeType *n1, nodeType *n2){
	if(n1->type != n2->type)
	{
		if(n1->type == typeType && n2->type == typeCon){
			if(n1->tp.type==SYS_TYPE_INTEGER && n2->con.type==INTEGER)
				return true;
			if(n1->tp.type==SYS_TYPE_REAL && n2->con.type==REAL)
				return true;
			if(n1->tp.type==SYS_TYPE_CHAR && n2->con.type==CHAR)
				return true;
			if(n1->tp.type==SYS_TYPE_BOOL && n2->con.type==BOOL)
				return true;
				
			//otherwise
			return false;
		}
		//array of char and string are equal
		else if(n1->type==typeOpr && n1->opr.op[1]->tp.type==SYS_TYPE_CHAR && n2->type==typeCon &&n2->con.type==STRING)
			return true;
		//subrange <- integer 
		else if(isSubrange(n1)){
			//
			return type_equal(tp(SYS_TYPE_INTEGER), n2);
		}
		//enumeration <- element
		else if(n1->type == typeOpr && n1->opr.oper == ENUM && n2->type == typeId){
			return lookup_in_name_list(n2->id.sValue, n1->opr.op[0]);
		}
	}

	if(n1->type == typeType){
		if(n1->tp.type == SYS_TYPE_REAL){
			if(n2->tp.type != SYS_TYPE_REAL && n2->tp.type != SYS_TYPE_INTEGER)
				return false;
			else
				return true;
		}
		else{
		 	if(n1->tp.type != n2->tp.type)
				return false;
			else
				return true;
		}
	}
	else if(n1->type == typeOpr){
		if(n1->opr.oper != n2->opr.oper)
			return false;
		else{
			// enumeration
			if(n1->opr.oper == ENUM){
				return name_list_equal(n1->opr.op[0], n2->opr.op[0]);
			}
			// subrange
			else if(n1->opr.oper == CONST_NEGATIVE_NEGATIVE || n1->opr.oper == CONST_NEGATIVE_POSITIVE || n1->opr.oper == CONST_POSITIVE_POSITIVE){
				return const_value_equal(n1->opr.op[0], n2->opr.op[1]) && const_value_equal(n1->opr.op[1], n2->opr.op[1]);
			}
			//array
			else if(n1->opr.oper==ARRAY_TYPE_DECL){
				//index type and element type should both be the same
				return type_equal(n1->opr.op[0], n2->opr.op[0]) && type_equal(n1->opr.op[1], n2->opr.op[1]);
			}

		}
	}
	else if(n1->type == typeId){
		//array // record
		// simply decide by name now
		//nodeType *type1 = lookup(n1->id.name);
		//nodeType *type2 = lookup(n2->id.name);
		return  strcmp(n1->id.sValue, n2->id.sValue)==0;
	}
}

string type_str(nodeType *node){
	if(node->type==typeType){
		switch(node->tp.type){
			case SYS_TYPE_INTEGER:return "integer";
			case SYS_TYPE_REAL:return "real";
			case SYS_TYPE_CHAR:return "char";
			case SYS_TYPE_BOOL:return "boolean";
		}
	}
	else if(node->type==typeId){
		return node->id.sValue;
	}
	else if(node->type == typeOpr){
		if(node->opr.oper == ENUM){
			return "<enumeration type>";
		}
		else if(node->opr.oper == CONST_POSITIVE_POSITIVE ||node->opr.oper ==CONST_NEGATIVE_NEGATIVE || node->opr.oper ==CONST_NEGATIVE_POSITIVE){
			return "<subrange type>";
		}
		else if(node->opr.oper == ARRAY_TYPE_DECL){
			return "array ["+type_str(node->opr.op[0])+"] of " + type_str(node->opr.op[1]);
		}
		else if(node->opr.oper== FUNCTION_HEAD){
			return "<function>";
		}
		else if(node->opr.oper == PROCEDURE_HEAD){
			return "<procedure>";
		}
	}
	else if(node->type == typeCon){
		switch(node->con.type){
			case INTEGER:return "integer";
			case STRING:return "string";
			case CHAR:return "char";
			case REAL:return "real";
			case BOOL:return "boolean";
		}
	}
	else if(node->type == typeSysProc){
		return "<system procedure>";
	}
	else if(node->type == typeSysFunc){
		return "<system function>";
	}
	return "unknown";
}

bool lookup_in_name_list(char *name, nodeType *name_list){
	if(name_list->opr.oper==NAME_LIST)
		return (strcmp(name, name_list->opr.op[1]->id.sValue)==0) || lookup_in_name_list(name, name_list->opr.op[0]);
	else//a single id
		return strcmp(name, name_list->id.sValue)==0;
}

nodeType* lookup_field_in_field(char *name, nodeType *node){
	nodeType *name_list = node->opr.op[0];
	nodeType *type_decl = node->opr.op[1];
	if(lookup_in_name_list(name, name_list)){
		return type_decl;
	}
	else{
		return NULL;
	}
}

nodeType* lookup_field_in_field_list(char *name, nodeType *node){
	if(node->opr.oper==FIELD_DECL_LIST){
		nodeType* result = lookup_field_in_field(name, node->opr.op[1]);
		if(result)
			return result;

		result = lookup_field_in_field_list(name, node->opr.op[0]);
		if(result)
			return result;
	}
	else{//FIELD_DECL
		return lookup_field_in_field(name, node);
	}
	//Not found
	return NULL;
}

nodeType *lookup_field_in_record(char* name, nodeType *record){
	nodeType *field_list = record->opr.op[0];
	return lookup_field_in_field_list(name, field_list);
}

bool name_list_equal(nodeType *n1, nodeType *n2){
	if(n1->type != n2->type)
		return false;

	if(n1->opr.oper != n2->opr.oper)
		return false;

	if(n1->opr.oper == NAME_LIST)
		return name_list_equal(n1->opr.op[0], n2->opr.op[0]) && strcmp(n1->opr.op[1]->id.sValue, n2->opr.op[1]->id.sValue)==0;
	else
		return strcmp(n1->id.sValue, n2->id.sValue)==0;
}


bool const_value_equal(nodeType *n1, nodeType *n2){
	if(n1->con.type != n2->con.type)
		return false;
	else{
		switch(n1->con.type){
			case INTEGER:return n1->con.integer==n2->con.integer;
			case REAL:return n1->con.real==n2->con.real;
			case CHAR:return n1->con.character==n2->con.character;
			case STRING:return strcmp(n1->con.str, n2->con.str)==0;
			case BOOL:return n1->con.boolean==n2->con.boolean;
		}
	}
}

nodeType* check_record_access(char *record, char *field){
	char message[100];
	nodeType *node = lookup(record);
	if(node->type == typeOpr && node->opr.oper == RECORD_TYPE_DECL){
		//search given field in field_list
		nodeType *fieldnode = lookup_field_in_record(field, node);
		if(fieldnode == NULL){
			sprintf(message, "%s is not a member of %s", field, record);
			type_error(message);
		}
		else 
			return fieldnode;
	}
	else{
		sprintf(message, "%s is not a record", record);
		type_error(message);
	}
}

nodeType *check_array_access(char *array, nodeType *index){
	char message[100];
	nodeType *node = lookup(array);
	if(node->type == typeOpr && node->opr.oper == ARRAY_TYPE_DECL){
		//incompatible index type 
		if(!type_equal(node->opr.op[0], index)){
			sprintf(message,"incompatible index type, \"%s\" expected but \"%s\" found", type_str(node->opr.op[0]).data(), type_str(index).data());
			type_error(message);
		}
		else
			return node->opr.op[1];
	}
	else{
		sprintf(message, "%s is not an array", array);
		type_error(message);
	}
}

bool check_case_expression(nodeType *expression, nodeType *cases){
	// more than one
	if(cases->opr.oper == CASE_EXPR_LIST) {
		nodeType *case_list = cases->opr.op[0];
		nodeType *case_expr = cases->opr.op[1];								//get const_value
		return check_case_expression(expression, case_list) && type_equal(expression, case_expr->opr.op[0]);
	}
	else{//just one case
		return type_equal(expression, cases->opr.op[0]);
	}
}

void push_back_from_para_type_list(vector<nodeType*> &v, nodeType *p, bool name_or_type){
	//if(p->opr.oper == PARA_TYPE_LIST){//para_type_list	: var_para_list COLON  simple_type_decl
			nodeType *var_para_list = p->opr.op[0];
			nodeType *simple_type_decl = p->opr.op[1];
			nodeType *name_list;
			if(var_para_list->opr.oper==VAR_PARA_LIST) //para_type_list: var_para_list COLON simple_type_decl
				name_list = var_para_list->opr.op[0];
			else //para_type_list: val_para_list COLON simple_type_decl
				name_list = var_para_list;

		if(name_or_type){ // name
			nodeType *node = name_list;
			vector<nodeType*> names = flatten(name_list);
			v.insert(v.end(), names.begin(), names.end());
		}
		else{//type
			int cnt = 0; //count number of name
			nodeType *node = name_list;
			while(true){
				if(node->type == typeOpr){
					cnt++;
					node = node->opr.op[0];
				}
				//single ID
				else{
					cnt++;
					break;
				}
			}
			for(int i=0;i<cnt;i++)
				v.push_back(simple_type_decl);
		}
	//}
	//else{// para_type_list: val_para_list COLON simple_type_decl // what is this!?
		
	//	type_error("unknown behavior");
	//	nodeType *simple_type_decl = p;
	//}
}

void push_back_from_para_decl_list(vector<nodeType*> &v, nodeType *p, bool name_or_type){
	//para_type_list node
	if(p->opr.oper == PARA_TYPE_LIST){
		push_back_from_para_type_list(v, p, name_or_type);
	}
	//para_decl_list node
	else{
		push_back_from_para_decl_list(v, p->opr.op[0], name_or_type);
		push_back_from_para_type_list(v, p->opr.op[1], name_or_type);
	}
}

vector<nodeType *> get_para_types(nodeType *function_head){
	vector<nodeType *> result;
	nodeType *para = function_head->opr.op[1];
	if(para==NULL){//no parameters
		return result;
	}
	else{//para is para_decl_list
		push_back_from_para_decl_list(result, para, false);
		return result;
	}
}

vector<nodeType*> get_para_names(nodeType *function_head){
	vector<nodeType *> result;
	nodeType *para = function_head->opr.op[1];
	if(para==NULL){//no parameters
		return result;
	}
	else{//para is para_decl_list
		push_back_from_para_decl_list(result, para, true);
		return result;
	}
}

void push_back_from_root(vector<nodeType*>&v, nodeType *node){
	if(node->type==typeOpr){
		push_back_from_root(v, node->opr.op[0]);
		v.push_back(node->opr.op[1]);
	}
	else{
		v.push_back(node);
	}
}

//return a vector contains all leaves of the tree with given root
vector<nodeType*> flatten(nodeType *root){
	vector<nodeType*> result;
	push_back_from_root(result, root);
	return result;
}

bool check_parameters(nodeType *function_head, nodeType* args_list){
	vector<nodeType*> args;
	vector<nodeType*> para_types = get_para_types(function_head);
	if(args_list->type==typeOpr&&args_list->opr.oper == ARGS_LIST)
		args = flatten(args_list);
	else
		args.push_back(args_list);
	if(para_types.size()!=args.size()){
		type_error("parameter number mismatch");
	}
	else{
		for(int i=0;i<para_types.size();i++){
			nodeType *tocheck = args[i]->exp;
			if(!type_equal(para_types[i], args[i]->exp)){
				char message[100];
				sprintf(message, "Incompatible type for arg no. %d: expected \"%s\" but \"%s\" found", i+1, type_str(para_types[i]).data(), type_str(args[i]->exp).data());
				type_error(message);
			}
		}
	}
	return true;

}
//symbol table end

nodeType *con(void* value,int type) {
	nodeType *p;

	/* allocate node */
	if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
		yyerror("out of memory");

	/* copy information */
	p->type = typeCon;
	p->con.type = type;
	if(type == REAL){
		p->con.real=*((double*)value);
	}else if(type == INTEGER){
		p->con.integer=*((int*)value);
	}else if(type == STRING){
		p->con.str = (char*)value;
	}else if(type == CHAR){
		p->con.character = *((char*)value);
	}else if(type == BOOL){
		p->con.boolean = *((int*)value);
	}

	return p;
}

nodeType *id(char * name) {
	nodeType *p;

	if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
		yyerror("out of memory");

	p->type = typeId;
	p->id.sValue = (char *)malloc(strlen(name)+1);
	strcpy(p->id.sValue, name);

	return p;
}

nodeType *tp(int i) {
	nodeType *p;

	/* allocate node */
	if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
		yyerror("out of memory");

	/* copy information */
	p->type = typeType;
	p->tp.type = i;

	return p;
}

nodeType *sysProc(int i) {
	nodeType *p;

	
	if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
		yyerror("out of memory");


	p->type = typeSysProc;
	p->sysProc.name = i;

	return p;
}


nodeType *sysFunc(int i) {
	nodeType *p;


	if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
		yyerror("out of memory");


	p->type = typeSysFunc;
	p->sysFunc.name = i;

	return p;
}

nodeType *opr(int oper, int nops, ...) {
	va_list ap;
	nodeType *p;
	int i;

	/* allocate node, extending op array */
	if ((p = (nodeType*)malloc(sizeof(nodeType) + (nops-1) * sizeof(nodeType* ))) == NULL)
		yyerror("out of memory");

	/* copy information */
	p->type = typeOpr;
	p->opr.oper = oper;
	p->opr.nops = nops;
	va_start(ap, nops);
	for (i = 0; i < nops; i++)
		p->opr.op[i] = va_arg(ap, nodeType*);
	va_end(ap);
	return p;
}

void freeNode(nodeType *p) {
	int i;

	if (!p) return;
	if (p->type == typeOpr) {
		for (i = 0; i < p->opr.nops; i++)
			freeNode(p->opr.op[i]);
	}
	free (p);
}
void yyerror(char *s) {
	fprintf(stdout, "%s\n", s);
}

int main(int argc, char *argv[]) {

	yyparse();
	//printf("Number of  pairs of BEGIN and END: %d\n", count);

	return 0;
}
