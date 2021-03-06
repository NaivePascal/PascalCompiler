#include "Midcode.h"

/*------------------------
* State Variables
*------------------------
*/
vector<midcode> midcode_list; // 3-address-code head

map<string, Scope>  gen_symbol_table;
vector<Arg> Arg_list; //Master list of all Arg data
Arg ARG_BOOL_TRUE;
Arg ARG_BOOL_FALSE;
Arg ARG_KEYWORD_IF;
FILE* codef = NULL;
FILE* dataf = NULL;
FILE* ff=NULL;
string preScope = "!main";

int labels = 0;
int tmps = 0;
int mains = 0;

//midcode_list
void GenControl_case_exp(nodeType* pnode, Arg tv, Arg label){
	nodeType** child = pnode->opr.op;
	midcode tmp;
	switch ((pnode->opr).oper){
	case CASE_EXPR_LIST:
		GenControl_case_exp(child[0], tv, label);
		break;
	case CASE_EXPR:{
		Arg arg1;
		midcode tmp1, tmp2;
		tmp1.op = CMP;
		tmp1.arg1 = GenCode(child[0]);
		tmp1.arg2 = tv;
		midcode_list.push_back(tmp1);
		arg1.type = STRING;
		arg1.cs = "L" + intToString(labels);
		labels++;
		tmp2.op = CMP_UNEQUAL;
		tmp2.arg1 = arg1;
		midcode_list.push_back(tmp2);
		//stmt
		GenCode(child[1]);
		//insert label for new
		tmp.op = LABEL;
		tmp.arg1 = arg1;
		midcode_list.push_back(tmp);
		break;
	}
	}
}



/// Control flow function
/// if
void GenControl(nodeType* pnode, Arg label1, Arg label2){
	nodeType** child = pnode->opr.op;
	midcode falsego;
	falsego.op = GOTO;
	falsego.arg1 = label2;
	switch (pnode->opr.oper){
		case AND:{
			midcode tmp;
			Arg arg1;
			//First
			arg1.type = STRING;
			arg1.cs = "L" + intToString(labels);
			labels++;
			GenControl(child[0], arg1, label2);
			//insert label for new
			tmp.op = LABEL;
			tmp.arg1 = arg1;
			midcode_list.push_back(tmp);
			//Second
			GenControl(child[1], label1, label2);
			break;
		}
		case OR:{
			midcode tmp;
			Arg arg1;
			//First
			arg1.type = STRING;
			arg1.cs = "L" + intToString(labels);
			labels++;
			GenControl(child[0], label1, arg1);
			//insert label for new
			tmp.op = LABEL;
			tmp.arg1 = arg1;
			midcode_list.push_back(tmp);
			//Second
			GenControl(child[1], label1, label2);
			break;
		}
		case GE:{
			midcode tmp1, tmp2;
			tmp1.op = CMP;
			tmp1.arg1 = GenCode(child[0]);
			tmp1.arg2 = GenCode(child[1]);
			midcode_list.push_back(tmp1);
			tmp2.op = CMP_GE;
			tmp2.arg1 = label1;
			midcode_list.push_back(tmp2);
			break;
		}
		case GT:{
			midcode tmp1, tmp2;
			tmp1.op = CMP;
			tmp1.arg1 = GenCode(child[0]);
			tmp1.arg2 = GenCode(child[1]);
			midcode_list.push_back(tmp1);
			tmp2.op = CMP_GT;
			tmp2.arg1 = label1;
			midcode_list.push_back(tmp2);
			break;
		}
		case LE:{
			midcode tmp1, tmp2;
			tmp1.op = CMP;
			tmp1.arg1 = GenCode(child[0]);
			tmp1.arg2 = GenCode(child[1]);
			midcode_list.push_back(tmp1);
			tmp2.op = CMP_LE;
			tmp2.arg1 = label1;
			midcode_list.push_back(tmp2);
			break;
		}
		case LT:{
			midcode tmp1, tmp2;
			tmp1.op = CMP;
			tmp1.arg1 = GenCode(child[0]);
			tmp1.arg2 = GenCode(child[1]);
			midcode_list.push_back(tmp1);
			tmp2.op = CMP_LT;
			tmp2.arg1 = label1;
			midcode_list.push_back(tmp2);
			break;
		}
		case EQUAL:{
			midcode tmp1, tmp2;
			tmp1.op = CMP;
			tmp1.arg1 = GenCode(child[0]);
			tmp1.arg2 = GenCode(child[1]);
			midcode_list.push_back(tmp1);
			tmp2.op = CMP_EQUAL;
			tmp2.arg1 = label1;
			midcode_list.push_back(tmp2);
			break;
		}
		case UNEQUAL:{
			midcode tmp1, tmp2;
			tmp1.op = CMP;
			tmp1.arg1 = GenCode(child[0]);
			tmp1.arg2 = GenCode(child[1]);
			midcode_list.push_back(tmp1);
			tmp2.op = CMP_UNEQUAL;
			tmp2.arg1 = label1;
			midcode_list.push_back(tmp2);
			break;
		}
		case NOT:{
			midcode tmp;
			GenControl(child[0], label2, label1);
			break;
		}
		default:{
			midcode tmp1, tmp2, gt;
			tmp1.op = CMP;
			tmp1.arg1 = GenCode(child[0]);
			tmp1.arg2.type = BOOL;
			tmp1.arg2.cb = 1;
			midcode_list.push_back(tmp1);
			tmp2.op = CMP_EQUAL;
			tmp2.arg1 = label1;
			midcode_list.push_back(tmp2);
			tmp2.op = GOTO;
			tmp2.arg1 = label2;
			midcode_list.push_back(tmp2);
			break;
		}
	}
	midcode_list.push_back(falsego);
}
void GenControl_for(nodeType* i, nodeType* max, Arg label1, Arg label2){
	midcode tmp1, tmp2;
	tmp1.op = CMP;
	tmp1.arg1 = GenCode(i);
	tmp1.arg2 = GenCode(max);
	midcode_list.push_back(tmp1);
	tmp2.op = CMP_LE;
	tmp2.arg1 = label1;
	midcode_list.push_back(tmp2);
	midcode falsego;
	falsego.op = GOTO;
	falsego.arg1 = label2;
	midcode_list.push_back(falsego);
}

/// Generate Constant
Arg GenCon(nodeType* pnode){
	Arg res;
	res.ci = res.cc = res.cr = res.cb = 0;
	res.temporary = false;
    switch((pnode->con).type){
        case INTEGER:
			res.ci = (pnode->con).integer;
        break;
		case STRING:
			res.cs = (pnode->con).str;
        break;
		case CHAR:
			res.cc = (pnode->con).character;
        break;
		case REAL:
			res.cr = (pnode->con).real;
        break;
		case BOOL:
			res.cb = (pnode->con).boolean;
        break;
	}
	res.type = (pnode->con).type;
	return res;
}

/// Generate Id
Arg GenId(nodeType* pnode){
	Arg res;
	res.type = ID;
	res.id = lookupSymbol((pnode->id).sValue);
	res.cs = (pnode->id).sValue;
	res.subr = preScope;
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
		case CASE:{
			arg2 = GenCode(child[0]);
			arg1.type = STRING;
			arg1.cs = "L" + intToString(labels);
			labels++;
			GenControl_case_exp(child[1], arg2, arg1);
			//insert label for end
			tmp.op = LABEL;
			tmp.arg1 = arg1;
			midcode_list.push_back(tmp);
			break;
		}
		case ROUTINE_BODY:
			tmp.op = ROUTINE_BODY;
			tmp.arg1.type = STRING;
			tmp.arg1.cs = "MAIN";
			midcode_list.push_back(tmp);
			mains = midcode_list.size() - 1;
			GenCode(child[0]);
		break;
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
			GenOpr(child[3]);
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
		//*********Useless**********
        case CONST_POSITIVE_POSITIVE:
		case CONST_NEGATIVE_POSITIVE:
		case CONST_NEGATIVE_NEGATIVE:
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
			GenOpr(child[0]);
			GenOpr(child[1]);
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
			arg1 = GenOpr(child[0]);
			GenOpr(child[1]);
			tmp.arg1 = arg1;
			tmp.op = RET;
			midcode_list.push_back(tmp);
			tmp.op = END;
			tmp.arg1 = arg1;
			midcode_list.push_back(tmp);
			string key = child[0]->opr.op[0]->id.sValue;
			gen_symbol_table.insert({ key, exit_scope() });
			preScope = "!main";
		}break;
		case FUNCTION_HEAD:{
			//hdj: insert function
			insert(child[0]->id.sValue, pnode);
			preScope = child[0]->id.sValue;
			enter_scope();
			// zrz insert function label
			tmps = 0;
			tmp.op = FUNCTION;
			tmp.arg1 = GenId(child[0]);
			midcode_list.push_back(tmp);
			//hdj:insert function parameters
			vector<nodeType*> parameters = get_para_names(pnode);
			vector<nodeType*> types = get_para_types(pnode);
			for (int i = 0; i < types.size(); i++) {
				insert(parameters[i]->id.sValue, types[i]);
			}
			res = tmp.arg1;
		}break;
		case PROCEDURE_DECL:{
			arg1 = GenOpr(child[0]);
			GenOpr(child[1]);
			tmp.op = RET;
			midcode_list.push_back(tmp);
			tmp.op = END;
			tmp.arg1 = arg1;
			midcode_list.push_back(tmp);
			string key = child[0]->opr.op[0]->id.sValue;
			gen_symbol_table.insert({ key, exit_scope() });
			preScope = "!main";
		}break;
		case PROCEDURE_HEAD:{
			//hdj: insert function
			insert(child[0]->id.sValue, pnode);
			preScope = child[0]->id.sValue;
			enter_scope();
			tmps = 0;
			tmp.op = PROCEDURE;
			tmp.arg1 = GenId(child[0]);
			midcode_list.push_back(tmp);
			//hdj:insert function parameters
			vector<nodeType*> parameters = get_para_names(pnode);
			vector<nodeType*> types = get_para_types(pnode);
			for (int i = 0; i < types.size(); i++) {
				insert(parameters[i]->id.sValue, types[i]);
			}
			res = tmp.arg1;
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
			tmp.op = LABEL;
			tmp.arg1 = GenCon(child[0]);
			midcode_list.push_back(tmp);
			GenOpr(child[1]);
        break;
		case GOTO:
			tmp.op = GOTO;
			tmp.arg1 = GenCon(child[0]);
			midcode_list.push_back(tmp);
        case ASSIGN:
			tmp.op = ASSIGN;
			tmp.result = GenId(child[0]);
			if (pnode->opr.nops == 2){
				tmp.arg1 = GenCode(child[1]);
				tmp.arg2.type = INTEGER;
				tmp.arg2.ci = 0;
			}else if (pnode->opr.nops == 3){
				tmp.arg1 = GenCode(child[2]);
				tmp.arg2 = GenCode(child[1]);
			}
			midcode_list.push_back(tmp);
        break;
		case ASSIGN_STMT:
			tmp.op = ASSIGN_STMT;
			tmp.result = GenId(child[0]);
			tmp.arg1 = GenCode(child[2]);
			tmp.arg2 = GenCode(child[1]);
			midcode_list.push_back(tmp);
		break;
		case PROC_STMT:
			//No parameter
			if (pnode->opr.nops == 1){
				tmp.op = PROC_STMT;
				tmp.arg1 = GenCode(child[0]);
			}
			//Parameter require
			else if (pnode->opr.nops == 2){
				//args_list | sysproc
				if (child[1]->opr.oper == LP)
					GenCode(child[1]);
				else{
					if (child[1]->type == typeOpr && child[1]->opr.oper == ARGS_LIST){
						GenCode(child[1]);
					}
					else{
						tmp.op = PARAM;
						tmp.arg1 = GenCode(child[1]);
						midcode_list.push_back(tmp);
					}
				}
				tmp.op = CALL;
				tmp.arg1 = GenCode(child[0]);
			}
			midcode_list.push_back(tmp);
        break;
		case IF:
			arg1.type = STRING;
			arg1.cs = "L" + intToString(labels);
			labels++;
			arg2.type = STRING;
			arg2.cs = "L" + intToString(labels);
			labels++;
			arg3.type = STRING;
			arg3.cs = "L" + intToString(labels);
			labels++;
			//0 expression
			GenControl(child[0], arg1, arg2);
			//1 stmt
			// Label if
			tmp.op = LABEL;
			tmp.arg1 = arg1;
			midcode_list.push_back(tmp);
			GenCode(child[1]);
			//   jump
			tmp.op = GOTO;
			tmp.arg1 = arg3;
			midcode_list.push_back(tmp);
			//2 else stmt
			// Label else
			tmp.op = LABEL;
			tmp.arg1 = arg2;
			midcode_list.push_back(tmp);
			GenCode(child[2]);
			// Label follow
			tmp.op = LABEL;
			tmp.arg1 = arg3;
			midcode_list.push_back(tmp);
        break;
		case REPEAT:
			arg1.type = STRING;
			arg1.cs = "L" + intToString(labels);
			labels++;
			arg2.type = STRING;
			arg2.cs = "L" + intToString(labels);
			labels++;
			// Label loop
			tmp.op = LABEL;
			tmp.arg1 = arg1;
			midcode_list.push_back(tmp);
			//0 stmt
			GenCode(child[0]);
			//1 expression
			GenControl(child[1], arg2, arg1);
			//   jump
			tmp.op = GOTO;
			tmp.arg1 = arg1;
			midcode_list.push_back(tmp);
			// Label follow
			tmp.op = LABEL;
			tmp.arg1 = arg2;
			midcode_list.push_back(tmp);
        break;
		case WHILE:
			arg1.type = STRING;
			arg1.cs = "L" + intToString(labels);
			labels++;
			arg2.type = STRING;
			arg2.cs = "L" + intToString(labels);
			labels++;
			arg3.type = STRING;
			arg3.cs = "L" + intToString(labels);
			labels++;
			// Label loop
			tmp.op = LABEL;
			tmp.arg1 = arg1;
			midcode_list.push_back(tmp);
			//0 expression
			GenControl(child[0], arg2, arg3);
			//1 stmt
			// Label stmt
			tmp.op = LABEL;
			tmp.arg1 = arg2;
			midcode_list.push_back(tmp);
			GenCode(child[1]);
			//   jump
			tmp.op = GOTO;
			tmp.arg1 = arg1;
			midcode_list.push_back(tmp);
			// Label follow
			tmp.op = LABEL;
			tmp.arg1 = arg3;
			midcode_list.push_back(tmp);
        break;
		case FOR:
			arg1.type = STRING;
			arg1.cs = "L" + intToString(labels);
			labels++;
			arg2.type = STRING;
			arg2.cs = "L" + intToString(labels);
			labels++;
			arg3.type = STRING;
			arg3.cs = "L" + intToString(labels);
			labels++;
			// Initialize the id
			tmp.op = ASSIGN;
			tmp.arg1 = GenCode(child[1]);
			tmp.arg2.type = INTEGER;
			tmp.arg2.ci = 0;
			tmp.result = GenId(child[0]);
			midcode_list.push_back(tmp);
			// Label loop
			tmp.op = LABEL;
			tmp.arg1 = arg1;
			midcode_list.push_back(tmp);
			// Expr control
			GenControl_for(child[0],child[2], arg2, arg3);
			// stmt
			// Label stmt
			tmp.op = LABEL;
			tmp.arg1 = arg2;
			midcode_list.push_back(tmp);
			GenCode(child[3]);
			// Add 1
			tmp.op = (pnode->opr).oper;
			tmp.result = GenCode(child[0]);
			tmp.arg1 = GenCode(child[0]);
			tmp.arg2.type = INTEGER;
			tmp.arg2.ci = 1;
			midcode_list.push_back(tmp);
			// jump
			tmp.op = GOTO;
			tmp.arg1 = arg1;
			midcode_list.push_back(tmp);
			// Label follow
			tmp.op = LABEL;
			tmp.arg1 = arg3;
			midcode_list.push_back(tmp);
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
			tmp.op = (pnode->opr).oper;
			tmp.result.cs = "tmp" + intToString(tmps);
			tmps++;
			tmp.result.type = BOOL;
			tmp.result.temporary = true;
			tmp.result.subr = preScope;
			tmp.arg1 = GenCode(child[0]);
			tmp.arg2 = GenCode(child[1]);
			midcode_list.push_back(tmp);
			res = tmp.result;
			break;
		case NOT:
			tmp.op = (pnode->opr).oper;
			tmp.result.cs = "tmp" + intToString(tmps);
			tmps++;
			tmp.result.type = BOOL;
			tmp.result.temporary = true;
			tmp.result.subr = preScope;
			tmp.arg1 = GenCode(child[0]);
			midcode_list.push_back(tmp);
			res = tmp.result;
			break;
        break;
        case PLUS:
        case MINUS:
        case MUL:
        case DIV:
		case MOD:
			tmp.op = (pnode->opr).oper;
			tmp.result.cs = "tmp" + intToString(tmps); 
			tmps++;
			tmp.result.temporary = true;
			tmp.result.subr = preScope;
			if (pnode->opr.nops == 2){
				tmp.arg1 = GenCode(child[0]);
				tmp.arg2 = GenCode(child[1]);
				tmp.result.type = tmp.arg1.type;
			}
			else{
				tmp.arg2 = GenCode(child[0]);
				tmp.arg1.type = INTEGER;
				tmp.arg1.ci = 0;
				tmp.result.type = tmp.arg2.type;
			}
			midcode_list.push_back(tmp);
			res = tmp.result;
		break;
        case LP:
			if (child[1]->type == typeOpr && child[1]->opr.oper == ARGS_LIST){
				GenCode(child[1]);
			}
			else{
				tmp.op = PARAM;
				tmp.arg1 = GenCode(child[1]);
				midcode_list.push_back(tmp);
			}
			tmp.op = CALL;
			tmp.arg1 = GenId(child[0]);
			tmp.result.id = tmp.arg1.id;
			tmp.result.cs = "tmp" + intToString(tmps);
			tmp.result.temporary = true;
			tmp.result.subr = preScope;
			tmps++;
			midcode_list.push_back(tmp);
			res = tmp.result;
        break;
        /// Array Index
		case LB:
			tmp.op = ASSIGN;
			tmp.result.cs = "tmp" + intToString(tmps);
			tmps++;
			tmp.result.type = (type_equal(tp(SYS_TYPE_INTEGER), pnode->exp)) ? REAL : INTEGER;
			tmp.result.temporary = true;
			tmp.result.subr = preScope;
			tmp.arg1 = GenId(child[0]);
			tmp.arg2 = GenCode(child[1]);
			midcode_list.push_back(tmp);
			res = tmp.result;
        break;
		case DOT:
			res.type = ID;
			res.id = lookupSymbol(GenId(child[0]).cs + "." + GenId(child[1]).cs);
			/*tmp.op = ASSIGN;
			tmp.result.cs = "tmp" + intToString(tmps);
			tmps++;	
			tmp.result.id = pnode->exp;
			tmp.result.temporary = true;
			tmp.arg1 = GenId(child[0]);
			tmp.arg2 = GenId(child[1]);
			midcode_list.push_back(tmp);
			res = tmp.result;*/
        break;
        case ARGS_LIST:
			tmp.op = PARAM;
			tmp.arg1 = GenCode(child[1]);
			midcode_list.push_back(tmp);
			if (child[0]->opr.oper == ARGS_LIST)
				GenCode(child[0]);
			else{
				tmp.arg1 = GenCode(child[0]);
				midcode_list.push_back(tmp);
			}
        break;
		case SYS_FUNCT:
			tmp.op = CALL;
			tmp.arg1 = GenCode(child[0]);
			tmp.arg2 = GenCode(child[1]);
			tmp.result.cs = "tmp" + intToString(tmps);
			tmp.result.subr = preScope;
			tmps++;
			midcode_list.push_back(tmp);
		break;
		case READ:
			tmp.op = READ;
			tmp.arg1 = GenCode(child[0]);
			midcode_list.push_back(tmp);
		break;
    }
	if (tmp.arg1.type == 113)
		arg1 = arg2;
	return res;
}

/// Generate Type declaration
int GenType(nodeType* pnode){
	return (pnode->tp).type;
}

/// Generate System procedure
Arg GenSysProc(nodeType* pnode){
	Arg res;
	res.type = SYS_PROC;
	res.proc = (pnode->sysProc).name;
	return res;
}

/// Generate System function
Arg GenSysFunc(nodeType* pnode){
	Arg res;
	res.type = SYS_FUNCT;
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
	if (in.temporary)
		return in.cs;
	switch (in.type){
		case INTEGER:
			res = intToString(in.ci);
			break;
		case REAL:
			res = intToString(in.cr);
			break;
		case STRING:
			res = in.cs;
			break;
		case CHAR:
			res = in.cc;
			break;
		case BOOL:
			res = intToString(in.cb);
			break;
		case ID:
			res = in.cs;
			break;
		case SYS_PROC:
			res = intToString(in.proc);
			break;
		case SYS_FUNCT:
			res = intToString(in.func);
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
	
	GenCodePhrase = true; //hdj:start data section insertion

	enter_scope();
	GenCode(root);
	gen_symbol_table.insert({ "!main", exit_scope() });
	printTAC();

    //size_param = leaveScope();


	return 0;
}
