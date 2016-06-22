#include "TargetCode.h"
#include "Parser.h"
#include <vector>
#include <string>
#include <sstream>
#include "symbol.h"
#include <assert.h>
Section dataSection;
Section codeSection;

string spaceStr[4] = { "BYTE" ,"SDWORD", "REAL4", "DWORD"};

Space typeSpace(int simpleType)
{
	switch (simpleType) {
		case SYS_TYPE_INTEGER:return Space::SDWORD;
		case SYS_TYPE_REAL:return Space::REAL4;
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
			space = Space::REAL4;
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

void GenTargetCode(const vector<midcode>&)
{

}