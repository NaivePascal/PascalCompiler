
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
extern int labels;

void intCmpSection(const string& ret, const string& j);
void realCmpSection(const string& ret, const string& constant);
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
	codeSection.append("mov","eax,"+arg);
	codeSection.append("mov", ret + ",al");
	// int to char
}

void sysFuncOdd(const string& arg, const string& ret) {
	codeSection.append("mov", ret+","+arg);
	codeSection.append("and", ret + "," + "1");
	// odd = true
}

void sysFuncOrd(const string& arg, const string& ret) {
	codeSection.append("mov", "eax, 0");
	codeSection.append("mov","al,"+arg);
	codeSection.append("mov", ret + ",eax");
	// char to int
}

void sysFuncPred(const string & arg, const string & ret)
{
	// the last number , char or enum
	codeSection.append("mov", ret + "," + arg);
	codeSection.append("sub", ret + ",1");
}

void sysFuncSucc(const string & arg, const string & ret)
{
	// the next number, char or enum
	codeSection.append("mov", ret + "," + arg);
	codeSection.append("add", ret + ",1");
}



void realCalculation(const string& arg1, const string& arg2, const string& ret, int type) {
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

void realCmpSection(const string& ret, const string& constant) {
	codeSection.append("and", "ax,"+constant);
	string label1 = "L"+intToString(labels++);
	string label2 = "L"+intToString(labels++);
	codeSection.append("JNE",label1);
	codeSection.append("mov", ret + ",1");
	codeSection.append("JMP",label2);
	codeSection.append(label1, ":");
	codeSection.append("mov", ret + ",0");
	codeSection.append(label2,":");
}

void realCompare(const string& ret, int type) {
	//codeSection.append("fld", arg1);
	//codeSection.append("fcom", arg2);
	codeSection.append("fstsw", ret);
	codeSection.append("fwait", "");
	switch (type) {
		case LT: {
			realCmpSection(ret,"0100H");
		}break;
		case GT: {
			realCmpSection(ret, "0100H");
		}break;
		case LE: {
			realCmpSection(ret, "0100H");
			codeSection.append("xor",ret+",1");
		}break;
		case GE: {
			realCmpSection(ret, "0100H");
			codeSection.append("xor", ret + ",1");
		}break;
		case EQUAL: {
			realCmpSection( ret, "4000H");
		}break;
		case UNEQUAL: {
			realCmpSection( ret, "4000H");
			codeSection.append("xor", ret + ",1");
		}break;
	}
}

void intCalculation(const string& arg1, const string& arg2, const string& ret, int type) {
	string opr;
	switch (type) {
		case PLUS: {
			codeSection.append("mov", ret + "," + arg1);
			codeSection.append("mov", ret + "," + arg1);
			codeSection.append("add",ret + "," + arg2);
		}break;
		case MINUS: {
			codeSection.append("mov", ret + "," + arg1);
			codeSection.append("mov", ret + "," + arg1);
			codeSection.append("sub", ret + "," + arg2);
		}break;
		case AND: {
			codeSection.append("mov", ret + "," + arg1);
			codeSection.append("mov", ret + "," + arg1);
			codeSection.append("and", ret + "," + arg2);
		}break;
		case OR: {
			codeSection.append("mov", ret + "," + arg1);
			codeSection.append("mov", ret + "," + arg1);
			codeSection.append("sub", ret + "," + arg2);
		}break;
		case MUL: {
			codeSection.append("mov","edx,0");
			codeSection.append("mov", "eax,"+arg1);
			codeSection.append("imul", arg2);
			codeSection.append("mov", ret + ",eax");
		}break;
		case DIV: {
			codeSection.append("mov", "edx,0");
			codeSection.append("mov", "eax," + arg1);
			codeSection.append("idiv", arg2);
			codeSection.append("mov", ret + ",eax");
		}break;
		case MOD: {
			codeSection.append("mov", "edx,0");
			codeSection.append("mov", "eax," + arg1);
			codeSection.append("idiv", arg2);
			codeSection.append("mov", ret + ",edx");
		}break;
	}
}

void intCmpSection(const string& ret, const string& j) {
	string label1 = "L" + intToString(labels++);
	string label2 = "L" + intToString(labels++);
	codeSection.append(j, label1);
	codeSection.append("MOV", ret, "0");
	codeSection.append("JMP", label2);
	codeSection.append(label1, ":");
	codeSection.append("MOV", ret+ ",1");
	codeSection.append(label2, ":");
}

void intCompare(const string& ret, int type) {
	switch (type)
	{
		case LT: {
			intCmpSection(ret, "JL");
		}break;
		case GT: {
			intCmpSection( ret, "JG");
		}break;
		case LE: {
			intCmpSection(ret, "JLE");
		}break;
		case GE: {
			intCmpSection(ret, "JGE");
		}break;
		case EQUAL: {
			intCmpSection(ret, "JE");
		}break;
		case UNEQUAL: {
			intCmpSection(ret, "JNE");
		}break;
	default:
		break;
	}
}



//vector<string> code_result;

string FindReg(Arg t,int i){
	return "";
}


/// zrz : different type
bool GenAss(midcode ptac, midcode tac, midcode ntac){
	char assemb[1000];
	switch (tac.op){
	case GOTO:
		codeSection.append("JMP", tac.arg1.cs);
		break;
	case LABEL:
		codeSection.append(tac.arg1.cs,":");
		break;
	case CMP:
		//###############################

		//lzt--int
		codeSection.append("CMP", FindReg(tac.arg1,1), FindReg(tac.arg2,2));
		//lzt--real
		//codeSection.append("fld", arg1);
		//codeSection.append("fcom", arg2);

		break;
	case ROUTINE_BODY:
		// Main process going
		codeSection.append(".STARTUP");
		break;
	case RET:
		// Call back
		//#########################################################
		//Have to judge that it is a function or procedure
		//so that we can know if we need to return value

		codeSection.append("RET");
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
		codeSection.append(tac.arg1.cs, "PROC", "NEAR");
		break;
	case ASSIGN:
		// assign an value to another simple value#####################################
		codeSection.append("MOV", FindReg(tac.result,1), FindReg(tac.arg1,2));
		break;
	case ASSIGN_STMT:

		break;
	case PARAM:
		codeSection.append("MOV", FindReg(tac.arg1, 1));
		codeSection.append("PUSH", FindReg(tac.arg1, 1));
		break;

	//lzt - compare
	case GE:
	case GT:
	case LE:
	case LT:
	case EQUAL:
	case UNEQUAL: {
		string  ret;
		//is int
		intCompare(ret, tac.op);
		//is real
		realCompare(ret, tac.op);
	}break;

	//lzt - calculate
	case OR:
	case AND:
	case PLUS:
	case MINUS:
	case MUL:
	case DIV:
	case MOD: {
		string arg1, arg2, ret;
		//is int
		intCalculation(arg1, arg2, ret, tac.op);
		//is real
		realCalculation( arg1, arg2, ret,tac.op);
	}break;
	case NOT: {
		string arg, ret;
		codeSection.append("mov", ret + "," + arg);
		codeSection.append("xor",ret+" ,1");
	}break;
	case CMP_NOT:{
		break;
	}
	case CMP_ID:{
		codeSection.append("CMP", FindReg(tac.arg2),);
		codeSection.append("JE", tac.arg1.cs);
		codeSection.append("JMP", tac.arg1.cs);
		break;
	}
	case CMP_EQUAL:{
		codeSection.append("JE", tac.arg1.cs);
		break;
	}
	case CMP_UNEQUAL:{
		codeSection.append("JNE", tac.arg1.cs);
		break;
	}
	case CMP_GT:{
		codeSection.append("JGT", tac.arg1.cs);
		break;
	}
	case CMP_GE:{
		codeSection.append("JGE", tac.arg1.cs);
		break;
	}
	case CMP_LT:{
		codeSection.append("JLT", tac.arg1.cs);
		break;
	}
	case CMP_LE:{
		codeSection.append("JLE", tac.arg1.cs);
		break;
	}
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
