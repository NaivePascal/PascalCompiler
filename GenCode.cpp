#include "node.h"
#include "Parser.h"
#include "symbol.h"
#include "Midcode.h"

/*------------------------
* State Variables
*------------------------
*/
vector<midcode> midcode_list; // 3-address-code head

vector<Arg> Arg_list; //Master list of all Arg data
Arg ARG_BOOL_TRUE;
Arg ARG_BOOL_FALSE;
Arg ARG_KEYWORD_IF;
FILE* codef = NULL;
FILE* dataf = NULL;
FILE* ff=NULL;

int labels = 0;
int tmps = 0;
map<string, Scope>  gen_symbol_table;

//midcode_list

/// Control flow function
/// if
void GenControl_if(nodeType* pnode, Arg label1, Arg label2){}
void GenControl_while(nodeType* pnode,Arg label1, Arg label2){}
void GenControl_repeat(nodeType* pnode, Arg label1, Arg label2){}
void GenControl_follow(nodeType* pnode, Arg label1, Arg label2){}
void GenControl_for(nodeType* pnode, Arg label1, Arg label2){}

Arg GenCode(nodeType* pnode);

/// Generate Constant
Arg GenCon(nodeType* pnode){
	Arg res;
    switch((pnode->con).type){
        case INTEGER:
			res.type = CON_INT;
			res.ci = (pnode->con).integer;
        break;
		case STRING:
			res.type = CON_STRING;
			res.cs = (pnode->con).str;
        break;
		case CHAR:
			res.type = CON_CHAR;
			res.cc = (pnode->con).character;
        break;
		case REAL:
			res.type = CON_REAL;
			res.cr = (pnode->con).real;
        break;
		case BOOL:
			res.type = CON_BOOL;
			res.cb = (pnode->con).boolean;
        break;
    }
	return res;
}

/// Generate Id
Arg GenId(nodeType* pnode){
	Arg res;
	res.type = ID;
	res.id = (pnode->id).sValue;
	return res;
}

/// Generate Composite type node
Arg GenOpr(nodeType* pnode){
	Arg arg1;
	Arg arg2;
	Arg arg3;
	Arg res;
	if (pnode == NULL) return res;
	nodeType** child = pnode->opr.op;
	midcode tmp;
	switch ((pnode->opr).oper){
		//Declaration
		case ROUTINE:
		case CONST_EXPR_LIST:
		case TYPE_DECL_LIST:
			GenOpr(child[0]);
			GenOpr(child[1]);
		break;
        case ROUTINE_HEAD:
			GenOpr(child[1]);
			GenOpr(child[2]);
        break;
        case CONST_EXPR:
			arg1 = GenId(child[0]);
			arg2 = GenId(child[1]);
			//#####################
			//Const declaration
			//Insert to the Symbol table
			insert(child[0]->id.sValue, child[1]);
			//#####################
        break;
        case TYPE_DEFINITION:
			arg1 = GenId(child[0]);
			//There may be a simple, array, record
			arg2 = GenOpr(child[1]);
			//#####################
			//Type declaration
			//Insert to the Symbol table
			insert(child[0]->id.sValue, child[1]);
			//#####################
        break;
        case ENUM:

        break;
        case CONST_POSITIVE_POSITIVE:
			arg1 = GenCon(child[0]);
			arg2 = GenCon(child[1]);
        break;
		case CONST_NEGATIVE_POSITIVE:
			arg1 = GenCon(child[0]);
			arg2 = GenCon(child[1]);
        break;
        case CONST_NEGATIVE_NEGATIVE:
			arg1 = GenCon(child[0]);
			arg2 = GenCon(child[1]);
        break;
		case ID_ID:
			arg1 = GenId(child[0]);
			arg2 = GenId(child[1]);
        break;
        case ARRAY_TYPE_DECL:
        break;
        case RECORD_TYPE_DECL:
        break;
        case FIELD_DECL_LIST:
        break;
        case FIELD_DECL:
        break;
        case NAME_LIST:
        break;
        case VAR_DECL_LIST:
        break;
		case VAR_DECL:{
			//hdj
			//just one name
			if (child[0]->type == typeId) {
				insert(child[0]->id.sValue, child[1]);
			}
			//more than one name
			else {
				nodeType *p = child[0];
				while (1) {
					insert(p->opr.op[1]->id.sValue, child[1]);
					p = p->opr.op[0];
					if (p->type == typeId)
						break;
				}
				insert(p->id.sValue, child[1]);
			}
		}
        break;
		//Code
        case ROUTINE_PART:
			GenOpr(child[0]);
			if (pnode->opr.nops == 2)
				GenOpr(child[1]);
        break;
		case FUNCTION_DECL:{
			GenOpr(child[0]);
			GenOpr(child[1]);
			string key = child[0]->opr.op[0]->id.sValue;
			gen_symbol_table.insert({ key, exit_scope() });
		}break;
		case FUNCTION_HEAD:{
			//hdj: insert function
			insert(child[0]->id.sValue, pnode);
			enter_scope();
			tmps = 0;
			tmp.op = TAC_PROC;
			tmp.arg1 = GenId(child[0]);
			midcode_list.push_back(tmp);
			//hdj:insert function parameters
			vector<nodeType*> parameters = get_para_names(pnode);
			vector<nodeType*> types = get_para_types(pnode);
			for (int i = 0; i < types.size(); i++) {
				insert(parameters[i]->id.sValue, types[i]);
			}
		}break;
		case PROCEDURE_DECL:{
			GenOpr(child[0]);
			GenOpr(child[1]);
			string key = child[0]->opr.op[0]->id.sValue;
			gen_symbol_table.insert({ key, exit_scope() });
		}break;
		case PROCEDURE_HEAD:{
			//hdj: insert function
			insert(child[0]->id.sValue, pnode);
			enter_scope();
			tmps = 0;
			tmp.op = TAC_PROC;
			tmp.arg1 = GenId(child[0]);
			midcode_list.push_back(tmp);
			//hdj:insert function parameters
			vector<nodeType*> parameters = get_para_names(pnode);
			vector<nodeType*> types = get_para_types(pnode);
			for (int i = 0; i < types.size(); i++) {
				insert(parameters[i]->id.sValue, types[i]);
			}
		}break;
        case PARA_DECL_LIST:
        break;
        case PARA_TYPE_LIST:
        break;
        case VAR_PARA_LIST:
        break;
        case STMT_LIST:
			GenOpr(child[0]);
			GenOpr(child[1]);//stmt
        break;
        case COLON:
			tmp.op = TAC_LABEL;
			tmp.arg1 = GenCon(child[0]);
			midcode_list.push_back(tmp);
			GenOpr(child[1]);
        break;
		case GOTO:
			tmp.op = TAC_GOTO;
			tmp.arg1 = GenCon(child[0]);
			midcode_list.push_back(tmp);
        case ASSIGN:
			tmp.op = TAC_ASSIGN;
			tmp.result = GenId(child[0]);
			if (pnode->opr.nops == 2){
				tmp.arg1 = GenCode(child[1]);
				tmp.arg2.type = CON_INT;
				tmp.arg2.ci = 0;
			}else if (pnode->opr.nops == 3){
				tmp.arg1 = GenCode(child[2]);
				tmp.arg2 = GenCode(child[1]);
			}
			midcode_list.push_back(tmp);
        break;
		case PROC_STMT:
			//No parameter
			if (pnode->opr.nops == 1){
				tmp.op = TAC_PROC;
				tmp.arg1 = GenCode(child[0]);
			}
			//Parameter require
			else if (pnode->opr.nops == 2){
				GenCode(child[1]);//args_list | sysproc
				tmp.op = TAC_PROC;
				tmp.arg1 = GenCode(child[0]);
			}
			midcode_list.push_back(tmp);
        break;
		case IF:
			arg1.type = CON_STRING;
			arg1.cs = "L" + intToString(labels);
			labels++;
			arg2.type = CON_STRING;
			arg2.cs = "L" + intToString(labels);
			labels++;
			//0 expression
			GenControl_if(child[0], arg1, arg2);
			//1 stmt
			GenCode(child[1]);
			//   jump
			tmp.op = TAC_GOTO;
			tmp.arg1 = arg2;
			midcode_list.push_back(tmp);
			//2 else stmt
			// Label else
			tmp.op = TAC_LABEL;
			tmp.arg1 = arg1;
			midcode_list.push_back(tmp);
			GenCode(child[2]);
			// Label follow
			tmp.op = TAC_LABEL;
			tmp.arg1 = arg2;
			midcode_list.push_back(tmp);
        break;
		case REPEAT:
			arg1.type = CON_STRING;
			arg1.cs = "L" + intToString(labels);
			labels++;
			arg2.type = CON_STRING;
			arg2.cs = "L" + intToString(labels);
			labels++;
			// Label loop
			tmp.op = TAC_LABEL;
			tmp.arg1 = arg1;
			midcode_list.push_back(tmp);
			//0 stmt
			GenCode(child[0]);
			//1 expression
			GenControl_repeat(child[1], arg1, arg2);
			//   jump
			tmp.op = TAC_GOTO;
			tmp.arg1 = arg1;
			midcode_list.push_back(tmp);
			// Label follow
			tmp.op = TAC_LABEL;
			tmp.arg1 = arg2;
			midcode_list.push_back(tmp);
        break;
		case WHILE:
			arg1.type = CON_STRING;
			arg1.cs = "L" + intToString(labels);
			labels++;
			arg2.type = CON_STRING;
			arg2.cs = "L" + intToString(labels);
			labels++;
			// Label loop
			tmp.op = TAC_LABEL;
			tmp.arg1 = arg1;
			midcode_list.push_back(tmp);
			//0 expression
			GenControl_while(child[0], arg1, arg2);
			//1 stmt
			GenCode(child[1]);
			//   jump
			tmp.op = TAC_GOTO;
			tmp.arg1 = arg1;
			midcode_list.push_back(tmp);
			// Label follow
			tmp.op = TAC_LABEL;
			tmp.arg1 = arg2;
			midcode_list.push_back(tmp);
        break;
		case FOR:
			arg1.type = CON_STRING;
			arg1.cs = "L" + intToString(labels);
			labels++;
			arg2.type = CON_STRING;
			arg2.cs = "L" + intToString(labels);
			labels++;
			// Initialize the id
			tmp.op = TAC_ASSIGN;
			tmp.arg1 = GenId(child[0]);
			tmp.arg2.type = CON_INT;
			tmp.arg2.ci = 0;
			tmp.result = GenId(child[1]);
			midcode_list.push_back(tmp);
			// Label loop
			tmp.op = TAC_LABEL;
			tmp.arg1 = arg1;
			midcode_list.push_back(tmp);
			// stmt
			GenCode(child[3]);
			// Add
			tmp.op = (pnode->opr).oper;
			tmp.result = GenCode(child[0]);
			tmp.arg1 = GenCode(child[0]);
			tmp.arg2.type = CON_INT;
			tmp.arg2.ci = 1;
			midcode_list.push_back(tmp);
			// Expr control
			GenControl_for(child[2], arg1, arg2);
			// jump
			tmp.op = TAC_GOTO;
			tmp.arg1 = arg1;
			midcode_list.push_back(tmp);
			// Label follow
			tmp.op = TAC_LABEL;
			tmp.arg1 = arg2;
			midcode_list.push_back(tmp);
        break;
        case CASE:

        break;
        case CASE_EXPR_LIST:

        break;
        case CASE_EXPR:

        break;
        case EXPRESSION_LIST:

        break;
        case GE:
		case GT:
		case LE:
		case LT:
		case EQUAL:
		case UNEQUAL:
		case OR:
		case AND:
		case NOT:
			tmp.op = (pnode->opr).oper;
			tmp.result.id = "tmp" + intToString(tmps);
			tmps++;
			tmp.result.type = CON_BOOL;
			tmp.result.temporary = true;
			tmp.arg1 = GenCode(child[0]);
			tmp.arg2 = GenCode(child[1]);
			midcode_list.push_back(tmp);
			res = tmp.result;
        break;
        case PLUS:
        case MINUS:
        case MUL:
        case DIV:
		case MOD:
			tmp.op = (pnode->opr).oper;
			tmp.result.id = "tmp" + intToString(tmps); 
			tmps++;

			tmp.result.type = (type_equal(tp(SYS_TYPE_REAL),pnode->exp))?CON_REAL:CON_INT;
			tmp.result.temporary = true;
			tmp.arg1 = GenCode(child[0]);
			tmp.arg2 = GenCode(child[1]);
			midcode_list.push_back(tmp);
			res = tmp.result;
		break;
        case LP:
			tmp.op = TAC_CALL;
			GenCode(child[1]);
			tmp.arg1 = GenId(child[0]);
			midcode_list.push_back(tmp);
        break;
        /// Array Index
		case LB:
			tmp.op = TAC_ASSIGN;
			tmp.result.id = "tmp" + intToString(tmps);
			tmps++;

			tmp.result.type = (type_equal(tp(SYS_TYPE_INTEGER), pnode->exp)) ? CON_REAL : CON_INT;
			tmp.result.temporary = true;
			tmp.arg1 = GenId(child[0]);
			tmp.arg2 = GenCode(child[1]);
			midcode_list.push_back(tmp);
			res = tmp.result;
        break;
		case DOT:
			tmp.op = TAC_ASSIGN;
			tmp.result.id = "tmp" + intToString(tmps);
			tmps++;

			tmp.result.type = (type_equal(tp(SYS_TYPE_INTEGER), pnode->exp)) ? CON_REAL : CON_INT;
			tmp.result.temporary = true;
			tmp.arg1 = GenId(child[0]);
			tmp.arg2.type = CON_INT;
			tmp.arg2.ci = 0;
			midcode_list.push_back(tmp);
			res = tmp.result;
        break;
        case ARGS_LIST:
			tmp.op = TAC_PARAM;
			GenCode(child[0]);
			tmp.arg1 = GenCode(child[1]);
			midcode_list.push_back(tmp);
        break;
    }
	return res;
}

/// Generate Type declaration
int GenType(nodeType* pnode){
	return (pnode->tp).type;
}

/// Generate System procedure
Arg GenSysProc(nodeType* pnode){
	Arg res;
	res.proc = (pnode->sysProc).name;
	return res;
}

/// Generate System function
Arg GenSysFunc(nodeType* pnode){
	Arg res;
	res.func = (pnode->sysFunc).name;
	return res;
}

/// Generate Link
void GenLink(nodeType* pnode){}

/// The top parse for the node and switch to new Function
Arg GenCode(nodeType* pnode){
	int size_param;
	Arg res;
    switch(pnode->type){
        case typeCon:
            res = GenCon(pnode);
            break;
        case typeId:
			res = GenId(pnode);
            break;
        case typeOpr:
			res = GenOpr(pnode);
            break;
        case typeType:
			GenType(pnode);
            break;
        case typeSysProc:
			res = GenSysProc(pnode);
            break;
        case typeSysFunc:
			res = GenSysFunc(pnode);
            break;
        case typeLink:
			GenLink(pnode);
            break;
    }
	return res;
}

string printArg(Arg in){
	string res;
	if (in.temporary == true)
		return in.id;
	switch (in.type){
	case CON_INT:
		res = intToString(in.ci);
		break;
	case CON_REAL:
		res = intToString(in.cr);
		break;
	case CON_STRING:
		res = in.cs;
		break;
	case CON_CHAR:
		res = in.cc;
		break;
	case CON_BOOL:
		res = intToString(in.cb);
		break;
	case ID:
		res = in.id;
		break;
	case SYSPRO:
		res = in.id;
		break;
	case SYSFUNC:
		res = in.id;
		break;
	}
	return res;
}

void printTAC(){
	int i;
	midcode tmp;
	puts("-----Three Address Code-----");
	printf("opr\tArg1\tArg2\tResult\n");
	for (i = 0; i < midcode_list.size(); i++){
		tmp = midcode_list[i];
		printf("%d\t%s\t%s\t%s\n", tmp.op, printArg(tmp.arg1).data(), printArg(tmp.arg2).data(), printArg(tmp.result).data());
	}
}

/// The Drive function to work with head and tail
int Gen_Drive(nodeType*  root,const char * outputfile){
    int size_param;
    char buf[100000];

    codef = fopen("code.asm","w");
    dataf = fopen("data.asm","w");

	enter_scope();
    GenCode(root);
	exit_scope();

	printTAC();
    //size_param = leaveScope();

    fclose(codef);
    fclose(dataf);

    ff = fopen(outputfile, "w");
    codef = fopen("code.asm","r");
    dataf = fopen("data.asm","r");
    while(fgets(buf, BUFSIZ,dataf)!=NULL){
        fputs(buf,ff);
    }
    while(fgets(buf, BUFSIZ,codef)!=NULL){
        fputs(buf,ff);
    }
	fclose(codef);
	fclose(dataf);
	fclose(ff);
	return 0;
}
