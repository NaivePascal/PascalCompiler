
#include "TargetCode.h"
#include "Parser.h"
#include <vector>
#include <string>
#include <sstream>
#include "symbol.h"
#include <assert.h>
Section dataSection;
Section codeSection;

string spaceStr[4] = { "BYTE" ,"SDWORD", "REAL8", "DWORD"};

Space typeSpace(int simpleType)
{
	switch (simpleType) {
		case SYS_TYPE_INTEGER:return Space::SDWORD;
		case SYS_TYPE_REAL:return Space::REAL8;
		case SYS_TYPE_CHAR:return Space::BYTE;
		case SYS_TYPE_BOOL:return Space::BYTE;
	}
}

void declare(string name, nodeType *node)
{
	Space space;
	string valuestr = "?";
	if (node->type == typeType) {
		space = typeSpace(node->tp.type);
	}
	else if (node->type == typeId) {
		//return node->id.sValue;
	}
	else if (node->type == typeOpr) {
		if (node->opr.oper == ENUM) {
			//return "<enumeration type>";
			space = Space::DWORD;
		}
		else if (node->opr.oper == CONST_POSITIVE_POSITIVE || node->opr.oper == CONST_NEGATIVE_NEGATIVE || node->opr.oper == CONST_NEGATIVE_POSITIVE) {
			//return "<subrange type>";
			space = Space::SDWORD;
		}
		else if (node->opr.oper == ARRAY_TYPE_DECL) {
			//return "array [" + type_str(node->opr.op[0]) + "] of " + type_str(node->opr.op[1]);
			nodeType *index_node = node->opr.op[0];
			int size = array_size(index_node);
			//support simple type temporarily
			assert(node->opr.op[1]->type == typeType);
			space = typeSpace(node->opr.op[1]->tp.type);
			valuestr = intToString(size);
			valuestr += " dup(?)";
		}
		else if (node->opr.oper == RECORD_TYPE_DECL) {
			vector<string> fields;
			vector<nodeType*> types;
			get_from_field_decl_list(fields, types, node->opr.op[0]);
			for (int i = 0; i < fields.size();i++) 
			{
				string varName = name + "." + fields[i];
				//support simple type temporarily
				assert(types[i]->type == typeType);
				declare(varName, types[i]);
			}
		}
		else if (node->opr.oper == FUNCTION_HEAD) {
			//return "<function>";
		}
		else if (node->opr.oper == PROCEDURE_HEAD) {
			//return "<procedure>";
		}
	}
	else if (node->type == typeCon) {
		stringstream ss;
		switch (node->con.type) {
		case INTEGER: {
			space = Space::SDWORD;
			ss << node->con.integer;
			ss >> valuestr;
			break;
		}
		case STRING: {
			space = Space::BYTE;
			valuestr = node->con.str;
			break;
		}
		case CHAR: {
			space = Space::BYTE;
			ss << node->con.character;
			ss >> valuestr;
			valuestr = "\'" + valuestr + "\'";
			break;
		}
		case REAL: {
			space = Space::REAL8;
			ss << node->con.real;
			ss >> valuestr;
			break;
		}
		case BOOL: {
			space = Space::BYTE;
			ss << node->con.boolean;
			ss >> valuestr;
			break;
		}
		}
	}
	else if (node->type == typeSysProc) {
		//return "<system procedure>";
	}
	else if (node->type == typeSysFunc) {
		//return "<system function>";
	}

	string spacestr = spaceStr[space];
	dataSection.append(name, spacestr, valuestr);
}

void printTargetCode(ostream & os)
{
	os << ".data" << endl;
	os << dataSection;
}

void insertIOFormatlist(){
	dataSection.append("zero", "BYTE", "0");
	dataSection.append("intFmt", "BYTE", "\"%d\", 0");
	dataSection.append("charFmt", "BYTE", "\"%c\", 0");
	dataSection.append("realFmt", "BYTE", "\"%lf\", 0");
	dataSection.append("stringFmt", "BYTE", "\"%s\", 0");
	dataSection.append("TrueSentence", "BYTE", "\"true\", 0");
	dataSection.append("FalseSentence", "BYTE", "\"false\", 0");
}

#include <utility>

void writeArg(const string& arg, int type) {
	//invoke crt_printf, addr fmtlist, area, area2
	switch (type) {
		case INTEGER: {
			codeSection.append("invoke","crt_printf,addr intFmt,"+arg);
		}break;
		case REAL: {
			codeSection.append("invoke", "crt_printf,addr realFmt," + arg);
		}break;
		case CHAR: {
			codeSection.append("invoke", "crt_printf,addr charFmt," + arg);
		}break;
		case STRING: {
			codeSection.append("invoke", "crt_printf,addr stringFmt,addr" + arg);
		}break;
		case BOOL: {
			codeSection.append("invoke", "crt_printf,addr intFmt," + arg);
		}break;
	}
}

void sysProcWrite(vector<pair<string, int>>& argPairs) {
	for (auto& arg : argPairs) {
		writeArg(arg.first, arg.second);
	}
}

void sysProcwriteln(vector<pair<string, int>>& argPairs) {
	sysProcWrite(argPairs);
	codeSection.append("invoke", "crt_puts,addr zero");
}

void procStmtRead(const string& arg, int type) {
	switch (type) {
	case INTEGER: {
		codeSection.append("invoke", "crt_scanf,addr intFmt, addr" + arg);
	}break;
	case REAL: {
		codeSection.append("invoke", "crt_scanf,addr realFmt,addr" + arg);
	}break;
	case CHAR: {
		codeSection.append("invoke", "crt_scanf,addr charFmt,addr" + arg);
	}break;
	case STRING: {
		codeSection.append("invoke", "crt_printf,addr stringFmt,addr" + arg);
	}break;
	case BOOL: {
		codeSection.append("invoke", "crt_printf,addr intFmt,addr" + arg);
	}break;
	}
}

void sysFuncSqrt(const string& arg, const string& ret) {
	codeSection.append("fld", arg);
	codeSection.append("fsqrt", "");
	codeSection.append("fstp", ret);
}

void sysFuncSqr(const string& arg, const string& ret) {
	codeSection.append("fld", arg);
	codeSection.append("fmul", arg);
	codeSection.append("fstp", ret);
}

void sysFuncAbs(int type,const string& arg, const string& ret) {
	switch (type) {
		case INTEGER: {
			codeSection.append("invoke", "crt_abs," + arg);
			codeSection.append("mov", ret + ",eax");
		}break;
		case REAL: {
			codeSection.append("fld", arg);
			codeSection.append("fabs", "");
			codeSection.append("fstp", ret);
		}break;
	}

}

void sysFuncChr(const string& arg, const string& ret) {
	// int to char
}

void sysFuncOdd(const string& arg, const string& ret) {
	// odd = true
}

void sysFuncOrd(const string& arg, const string& ret) {
	// char to int
}

void sysFuncPred(const string & arg, const string & ret)
{
	// the last number , char or enum
}

void sysFuncSucc(const string & arg, const string & ret)
{
	// the next number, char or enum
}


void realCalculate(int type, const string& arg1, const string& arg2, const string& ret) {
	codeSection.append("fld", arg1);
	string opr;
	switch (type)
	{
		case PLUS:
		{
			opr = "fadd";
		}break;
		case MINUS:
		{
			opr = "fsub";
		}break;
		case MUL:
		{
			opr = "fmul";
		}break;
		case DIV:
		{
			opr = "fdiv";
		}
		default:
			break;
	}
	codeSection.append(opr,arg2);
	codeSection.append("fstp",ret);
}

void realCompare(string arg1, string arg2, string ret) {
	codeSection.append("fld", arg1);
	codeSection.append("fcom", arg2);
	codeSection.append("fstsw", ret);
	codeSection.append("fwait", "");
	
}


//vector<string> code_result;

/// zrz : different type
bool GenAss(midcode ptac, midcode tac, midcode ntac){
	char assemb[1000];
	switch (tac.op){
	case GOTO:
		codeSection.append("JMP", tac.arg1.cs);
		break;
	case LABEL:
		codeSection.append(tac.arg1.cs, ":");
		break;
	case CMP:
		//###############################
		codeSection.append("CMP", tac.arg1.cs);
		break;
	case ROUTINE_BODY:
		// Main process going
		break;
	case RET:
		// Call back
		//Have to judge that it is a function or procedure
		//so that we can know if we need to return value

		break;
	case CALL:
		if (tac.arg1.type == SYS_PROC){

		}
		else if (tac.arg1.type == SYS_FUNCT){

		}
		else{
			codeSection.append("CALL", tac.arg1.cs);
		}
		break;
	case END:
		codeSection.append(tac.arg1.cs,"ENDP");
	case FUNCTION:
		// function declaration
		codeSection.append(tac.arg1.cs,"PROC","NEAR");
		break;
	case PROCEDURE:
		// procedure declaration
		break;
	case ASSIGN:
		// assign an value to another simple value
		break;
	case ASSIGN_STMT:

		break;
	case PARAM:
		
		break;
	case GE:{
		codeSection.append("MOV", "eax", "ebx");
		codeSection.append("CMP", "eax", "ebx");
		string l1 = "L" + intToString(labels++);
		string l2 = "L" + intToString(labels++);
		codeSection.append("JGE", l1);
		codeSection.append("MOV", "eax", "0");
		codeSection.append("JMP", l2);
		codeSection.append(l1, ":");
		codeSection.append("MOV", "eax", "1");
		codeSection.append(l2, ":");
		/*CMP arg1,arg2
		jge L1
		mov res, false
		jmp L2
		L1:
		mov res ,true
		L2:
		
		*/
		break;
	}
	case GT:

		break;
	case LE:

		break;
	case LT:

		break;
	case EQUAL:

		break;
	case UNEQUAL:

		break;
	case OR:

		break;
	case AND:

		break;
	case NOT:

		break;
	case PLUS:

		break;
	case MINUS:

		break;
	case MUL:

		break;
	case DIV:

		break;
	case MOD:

		break;
	}
	return false;
}

/// zrz : according TAC generate x86 asembly code:drive function
void GenTargetCode(const vector<midcode>&) {
	for (int i = 1; i < midcode_list.size()-1; i++) {
		if (GenAss(midcode_list[i-1], midcode_list[i], midcode_list[i+1])) {
			// pop sth to end a block
		}
	}
}
