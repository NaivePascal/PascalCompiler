#ifndef _SYMBOL_H_
#define _SYMBOL_H_
#include "node.h"
#include "Parser.h"
#include <map>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

#define DEBUG

using namespace std;

extern nodeType *tp(int i);
extern int yylineno;
void insert(char *name, nodeType* type);
void enter_scope();

nodeType* lookup(string name);
bool type_equal(nodeType *n1, nodeType *n2);
string type_str(nodeType *node);
void type_error(const char *s);

nodeType* _lookup(string name);
nodeType *lookup_field_in_record(char* name, nodeType *record);
bool name_list_equal(nodeType *n1, nodeType *n2);
bool const_value_equal(nodeType *n1, nodeType *n2);
nodeType *check_record_access(char *record, char *field);
nodeType *check_array_access(char *array, nodeType *index);
bool check_case_expression(nodeType *expression, nodeType *cases);
bool check_parameters(nodeType *function_head, nodeType* parameters);
void range_check(nodeType *);
vector<nodeType*> get_para_names(nodeType *function_head);
vector<nodeType*> get_para_types(nodeType *function_head);
vector<nodeType*> flatten(nodeType *root);
bool isSubrange(const nodeType *node);
void get_from_field_decl_list(vector<string> &fields, vector<nodeType*> &types, nodeType*field_decl_list);

//for intermediate code generation
int lookup_address(string name);

void printSymbolTable();

enum SimpleType
{
	UNKNOWN,
	INT_T,
	CHAR_T,
	REAL_T,
	BOOL_T,
	ENUM_T,
	RANGE_T
};

struct Simple {
	SimpleType type;
	vector<string> names;//for enum
	pair<int, int> range; //for range

	Simple() {}

	Simple(const vector<string> &_names)
		:type(ENUM_T), names(_names) {}

	Simple(const pair<int, int> &_range)
		:type(RANGE_T), range(_range) {}

	Simple(SimpleType t)
		:type(t) {}

	string toString();
};

struct Type;

struct Base {
	bool is_array;
	Simple index;
	//if it is array
	Type* element;

	Base() {}

	Base(SimpleType t)
		:index(t), is_array(false) {}

	//simple type
	Base(const Simple& t)
		:index(t), element(NULL), is_array(false) {}
	//array
	Base(const Simple& _index, Type *_element)
		:index(_index), element(_element), is_array(true) {}
	//down cast to simple
	Simple toSimple() {
		return index;
	}

	string toString();
};

struct Type {
	bool is_record;
	//Base
	Base base;
	//record
	vector<string> fields;
	map<string, Type*> record;

	//down cast to simple
	Simple toSimple() {
		return base.toSimple();
	}

	Type():is_record(false) {}

	Type(SimpleType t)
		:base(t), is_record(false) {}

	//base type
	Type(const Base& _b)
		:base(_b), is_record(false) {}

	//record
	Type(const vector<string>& _fields, const vector<nodeType*> typenodes)
		:fields(_fields), is_record(true) {
		for (int i = 0; i < fields.size(); i++) {
			string name = fields[i];
			if (record.find(name) == record.end())
				record[name] = new Type(typenodes[i]);
			//duplicate names
			else {
				char message[100];
				sprintf(message, "duplicate name \"%s\"", name.data());
				type_error(message);
			}
		}
	}

	//convert nodeType to Type
	Type(const nodeType*node) {
		if (node->type == typeType) {
			switch (node->tp.type) {
			case SYS_TYPE_INTEGER:*this = Type(INT_T); break;
			case SYS_TYPE_REAL:*this = Type(REAL_T); break;
			case SYS_TYPE_CHAR:*this = Type(CHAR_T); break;
			case SYS_TYPE_BOOL:*this = Type(BOOL_T); break;
			}
		}
		else if (node->type == typeId) {
			//lookup this type in symbol table
			*this = Type(lookup(node->id.sValue));
		}
		else if (node->type == typeOpr) {
			if (node->opr.oper == ENUM) {
				// "<enumeration type>"
				vector<nodeType*> name_nodes = flatten(node->opr.op[0]);
				vector<string> names(name_nodes.size());
				for (int i = 0; i < names.size(); i++)
					names[i] = string(name_nodes[i]->id.sValue);
				*this = Base(names);
			}
			else if (isSubrange(node)) {
				//"<subrange type>"
				nodeType *left = node->opr.op[0];
				nodeType *right = node->opr.op[1];
				if (node->opr.oper == ID_ID) {
					left = lookup(left->id.sValue);
					right = lookup(right->id.sValue);
				}
				int begin = left->con.integer;
				int end = right->con.integer;
				pair<int, int> range(begin, end);
				*this = Base(range);
			}
			else if (node->opr.oper == ARRAY_TYPE_DECL) {
				//array
				Simple index = Type(node->opr.op[0]).toSimple();
				Type* element = new Type(node->opr.op[1]);
				*this = Base(index, element);
			}
			else if (node->opr.oper == RECORD_TYPE_DECL) {
				//record
				vector<string> names;
				vector<nodeType*> types;
				get_from_field_decl_list(names, types, node->opr.op[0]);
				*this = Type(names, types);
			}
			else if (node->opr.oper == FUNCTION_HEAD) {
				//"<function>";
			}
			else if (node->opr.oper == PROCEDURE_HEAD) {
				//"<procedure>";
			}
		}
		else if (node->type == typeCon) {
			switch (node->con.type) {
			case INTEGER:*this = Type(INT_T); break;
			case REAL:*this = Type(REAL_T); break;
			case CHAR:*this = Type(CHAR_T); break;
			case BOOL:*this = Type(BOOL_T); break;
			case STRING: {
				int size = strlen(node->con.str);
				pair<int, int> range(0, size - 1);
				Type *element = new Type(CHAR_T);
				*this = Base(range, element);
				break;
			}
			}
		}
		else if (node->type == typeSysProc) {
			//"<system procedure>";
		}
		else if (node->type == typeSysFunc) {
			//"<system function>";
		}
		//return "unknown";
	}

	string toString() {
		//if it is record
		if (is_record) {
			string info = "record";
			for (string field : fields) {
				info += "\n\t" + field + ":" + record[field]->toString();
			}
			return info;
		}
		else {
			//if it is an array
			return base.toString();
		}
	}

};



enum SymbolType {
	DATA,
	FUNC,
	PROC
};

struct Function {
	vector<string> parameters;
	map<string, Type> types;
	Type returnType;

	string toString() {
		string info = "<function ";
		for (string name : parameters) {
			info += name + ":" + types[name].toString()+" ";
		}
		info += ">";
		return info;
	}
};

struct Symbol
{
	SymbolType symbolType;
	nodeType *node;
	//for intermediate code generation
	Type type;//DATA
	Function func;//FUNC or PROC

	int addr;

	Symbol()
		:node(NULL) {}

	Symbol(nodeType *_node, int _addr)
		:node(_node), addr(_addr), type(node) {
		if (node->type == typeOpr && (node->opr.oper == FUNCTION_HEAD|| node->opr.oper == PROCEDURE_HEAD)) {
			nodeType* para = node;
			vector<nodeType*> nameNodes = get_para_names(para);
			vector<nodeType*> typeNodes = get_para_types(para);
			func.parameters.resize(nameNodes.size());
			for (int i = 0; i < nameNodes.size(); i++) {
				string name = string(nameNodes[i]->id.sValue);
				func.parameters[i] = name;
				func.types[name] = Type(typeNodes[i]);
			}
			if (node->opr.oper == FUNCTION_HEAD) {
				symbolType = SymbolType::FUNC;
				func.returnType = Type(node->opr.op[2]);
			}
			else
				symbolType = SymbolType::PROC;
		}
		else {
			symbolType = SymbolType::DATA;
		}
	}

	string information() {
		switch (symbolType)
		{
		case DATA:
			return type.toString();
		case PROC:
			return func.toString();
		case FUNC: {
			string info = func.toString();
			string retType = func.returnType.toString();
			return info + " return:" + retType;
		}
		default:
			return "unknown";
		}
	}
};

struct Scope
{
	int address;
	map<string, Symbol> symbol_table;

	Scope()
		:address(0) {}

	void print() {
		puts("-------Symbol Table of a Scope------");
		for (auto iter : symbol_table) {
			cout << iter.first << ":" << iter.second.type.toString() << endl;
		}
	}
};
Scope exit_scope();
extern vector<Scope> symbol_table_stack;
extern int level;
extern string message;

#endif // !_SYMBOL_H_
