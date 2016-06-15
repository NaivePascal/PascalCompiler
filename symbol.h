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
void exit_scope();
nodeType* lookup(string name);
bool type_equal(nodeType *n1, nodeType *n2);
string type_str(nodeType *node);
void type_error(const char *s) {
	printf("type error at line %d: %s\n", yylineno, s); //exit(42);
}

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

	string toString() {
		switch (type) {
		case INT_T:return "int";
		case CHAR_T:return "char";
		case REAL_T:return "real";
		case BOOL_T:return "bool";
		case ENUM_T: {
			string info = "enum[";
			for (string name : names) {
				info += name+" ";
			}
			info += "]";
			return info;
		}
		case RANGE_T: {
			char message[20];
			sprintf(message, "range(%d, %d)", range.first, range.second);
			string info(message);
			return info;
		}
		default:return "unknown";
		}
	}
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

string Base::toString() {
	if (is_array) {
		string info = "array";
		info += " [" + index.toString() + "] ";
		info += element->toString();
		return info;
	}
	else {
		return index.toString();
	}
}

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

vector<Scope> symbol_table_stack;

bool lookup_in_name_list(char *name, nodeType *name_list);
bool isSubrange(const nodeType *node) {
	return node->type == typeOpr && (
		node->opr.oper == CONST_NEGATIVE_NEGATIVE ||
		node->opr.oper == CONST_NEGATIVE_POSITIVE ||
		node->opr.oper == CONST_POSITIVE_POSITIVE ||
		node->opr.oper == ID_ID);
}

int array_size(nodeType* node) {
	int size = -1;
	if (node->type == typeType) {
		switch (node->tp.type) {
		case SYS_TYPE_INTEGER:size = 65536;
		case SYS_TYPE_CHAR:size = 256;
		}
	}
	else if (node->type == typeId) {
		size = array_size(lookup(node->id.sValue));
	}
	else if (node->type == typeOpr) {
		if (node->opr.oper == ENUM) {
			vector<nodeType*> name_nodes = flatten(node->opr.op[0]);
			return name_nodes.size();
		}
		else if (isSubrange(node)) {
			nodeType*left = node->opr.op[0];
			nodeType*right = node->opr.op[1];

			if (node->opr.oper == ID_ID) {
				left = lookup(left->id.sValue);
				right = lookup(right->id.sValue);
			}

			int begin = left->con.integer;
			int end = right->con.integer;
			size = end - begin + 1;
		}
	}

	if (size == -1)
		type_error("array size error");
	return size;
}

int type_space(nodeType *node) {
	if (node->type == typeType) {
		switch (node->tp.type) {
		case SYS_TYPE_INTEGER:return 4;
		case SYS_TYPE_REAL:return 8;
		case SYS_TYPE_CHAR:return 1;
		case SYS_TYPE_BOOL:return 1;
		}
	}
	else if (node->type == typeId) {
		//lookup this type in symbol table
		return type_space(lookup(node->id.sValue));
	}
	else if (node->type == typeOpr) {
		if (node->opr.oper == ENUM) {
			return 4;
		}
		else if (isSubrange(node)) {
			return 4;
		}
		else if (node->opr.oper == ARRAY_TYPE_DECL) {
			//array
			nodeType *index_node = node->opr.op[0];
			int size = array_size(index_node);
			int element_size = type_space(node->opr.op[1]);
			return size*element_size;
		}
		else if (node->opr.oper == RECORD_TYPE_DECL) {
			//record
			vector<string> names;
			vector<nodeType*> types;
			get_from_field_decl_list(names, types, node->opr.op[0]);
			int sum = 0;
			for (auto node : types) {
				sum += type_space(node);
			}
			return sum;
		}
		else if (node->opr.oper == FUNCTION_HEAD) {
			//"<function>";
			return 0;
		}
		else if (node->opr.oper == PROCEDURE_HEAD) {
			//"<procedure>";
			return 0;
		}
	}
	else if (node->type == typeCon) {
		switch (node->con.type) {
		case INTEGER:return 4;
		case REAL:return 8;
		case CHAR:return 1;
		case BOOL:return 1;
		case STRING: {
			int size = strlen(node->con.str);
			return size;
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
	return -1;
}

void insert(char *name, nodeType* node) {
	int addr = symbol_table_stack.back().address;
	map<string, Symbol> &table = symbol_table_stack.back().symbol_table;
	Symbol newSymbol(node, addr);
#ifdef DEBUG
	puts("----------------------------------");
	printf("%s\t %s\t relative-address:%d \n", name, type_str(node).data(), addr);
	printf("Symbol info : %s\n", newSymbol.information().data());
	puts("----------------------------------");
#endif
	table[name] = newSymbol;
	//if it is a record
	if (node->type == typeOpr && node->opr.oper == RECORD_TYPE_DECL) {
		//insert its members
		vector<string> member_names;
		vector<nodeType*> types;
		get_from_field_decl_list(member_names, types, node->opr.op[0]);
		int local_addr = addr;
		for (int i = 0; i < member_names.size(); i++) {
			string member = string(name) + "." + member_names[i];
			Symbol s(types[i], local_addr);
			table[member] = s;
#ifdef DEBUG
			puts("----------------------------------");
			printf("%s\t %s\t relative-address:%d \n", member.data(), type_str(types[i]).data(), local_addr);
			printf("Symbol info : %s\n", s.information().data());
			puts("----------------------------------");
#endif			
			local_addr += type_space(types[i]);
		}
	}

	int space = type_space(node);
	symbol_table_stack.back().address += space;
}


void enter_scope() {
	symbol_table_stack.push_back(Scope());
}

void exit_scope() {
	symbol_table_stack.pop_back();
}

nodeType* _lookup(string name) {
	//traverse the stack backwards to find symbol
	for (auto iter = symbol_table_stack.rbegin(); iter != symbol_table_stack.rend(); iter++) {
		auto item = iter->symbol_table.find(name);
		if (item != iter->symbol_table.end()) {
			return item->second.node; //return node information
		}
	}

	//nothing found, return NULL/type error
	char message[100];
	sprintf(message, "Identifier not found \"%s\"", name.data());
	type_error(message);
	return NULL;
}

nodeType* lookup(string name) {
	nodeType *result = _lookup(name);
	if (result->type == typeId) //if the id points to another id( type xx:yy var a:xx)
		return lookup(result->id.sValue);
	else
		return result;
}

int lookup_address(string name) {
	//traverse the stack backwards to find symbol
	for (auto iter = symbol_table_stack.rbegin(); iter != symbol_table_stack.rend(); iter++) {
		auto item = iter->symbol_table.find(name);
		if (item != iter->symbol_table.end()) {
			return item->second.addr; //return address
		}
	}
	return -1;
}

bool type_equal(nodeType *n1, nodeType *n2) {
	if (n1->type != n2->type)
	{
		if (n1->type == typeType && n2->type == typeCon) {
			if (n1->tp.type == SYS_TYPE_INTEGER && n2->con.type == INTEGER)
				return true;
			if (n1->tp.type == SYS_TYPE_REAL && n2->con.type == REAL)
				return true;
			if (n1->tp.type == SYS_TYPE_CHAR && n2->con.type == CHAR)
				return true;
			if (n1->tp.type == SYS_TYPE_BOOL && n2->con.type == BOOL)
				return true;

			//otherwise
			return false;
		}
		//array of char and string are equal
		else if (n1->type == typeOpr && n1->opr.op[1]->tp.type == SYS_TYPE_CHAR && n2->type == typeCon &&n2->con.type == STRING)
			return true;
		//subrange <- integer 
		else if (isSubrange(n1)) {
			//
			return type_equal(tp(SYS_TYPE_INTEGER), n2);
		}
		//enumeration <- element
		else if (n1->type == typeOpr && n1->opr.oper == ENUM && n2->type == typeId) {
			return lookup_in_name_list(n2->id.sValue, n1->opr.op[0]);
		}
	}

	if (n1->type == typeType) {
		if (n1->tp.type == SYS_TYPE_REAL) {
			if (n2->tp.type != SYS_TYPE_REAL && n2->tp.type != SYS_TYPE_INTEGER)
				return false;
			else
				return true;
		}
		else {
			if (n1->tp.type != n2->tp.type)
				return false;
			else
				return true;
		}
	}
	else if (n1->type == typeOpr) {
		if (n1->opr.oper != n2->opr.oper)
			return false;
		else {
			// enumeration
			if (n1->opr.oper == ENUM) {
				return name_list_equal(n1->opr.op[0], n2->opr.op[0]);
			}
			// subrange
			else if (n1->opr.oper == CONST_NEGATIVE_NEGATIVE || n1->opr.oper == CONST_NEGATIVE_POSITIVE || n1->opr.oper == CONST_POSITIVE_POSITIVE) {
				return const_value_equal(n1->opr.op[0], n2->opr.op[1]) && const_value_equal(n1->opr.op[1], n2->opr.op[1]);
			}
			//array
			else if (n1->opr.oper == ARRAY_TYPE_DECL) {
				//index type and element type should both be the same
				return type_equal(n1->opr.op[0], n2->opr.op[0]) && type_equal(n1->opr.op[1], n2->opr.op[1]);
			}

		}
	}
	else if (n1->type == typeId) {
		//array // record
		// simply decide by name now
		//nodeType *type1 = lookup(n1->id.name);
		//nodeType *type2 = lookup(n2->id.name);
		return  strcmp(n1->id.sValue, n2->id.sValue) == 0;
	}

	return false;
}

string type_str(nodeType *node) {
	if (node->type == typeType) {
		switch (node->tp.type) {
		case SYS_TYPE_INTEGER:return "integer";
		case SYS_TYPE_REAL:return "real";
		case SYS_TYPE_CHAR:return "char";
		case SYS_TYPE_BOOL:return "boolean";
		}
	}
	else if (node->type == typeId) {
		return node->id.sValue;
	}
	else if (node->type == typeOpr) {
		if (node->opr.oper == ENUM) {
			return "<enumeration type>";
		}
		else if (node->opr.oper == CONST_POSITIVE_POSITIVE || node->opr.oper == CONST_NEGATIVE_NEGATIVE || node->opr.oper == CONST_NEGATIVE_POSITIVE) {
			return "<subrange type>";
		}
		else if (node->opr.oper == ARRAY_TYPE_DECL) {
			return "array [" + type_str(node->opr.op[0]) + "] of " + type_str(node->opr.op[1]);
		}
		else if (node->opr.oper == RECORD_TYPE_DECL) {
			string info = "record [\n";
			vector<string> names;
			vector<nodeType*> types;
			get_from_field_decl_list(names, types, node->opr.op[0]);
			for (int i = 0; i < names.size(); i++)
				info += "\t" + names[i] + " " + type_str(types[i]) + "\n";
			info += "\t]";
			return info;
		}
		else if (node->opr.oper == FUNCTION_HEAD) {
			return "<function>";
		}
		else if (node->opr.oper == PROCEDURE_HEAD) {
			return "<procedure>";
		}
	}
	else if (node->type == typeCon) {
		switch (node->con.type) {
		case INTEGER:return "integer";
		case STRING:return "string";
		case CHAR:return "char";
		case REAL:return "real";
		case BOOL:return "boolean";
		}
	}
	else if (node->type == typeSysProc) {
		return "<system procedure>";
	}
	else if (node->type == typeSysFunc) {
		return "<system function>";
	}
	return "unknown";
}

bool lookup_in_name_list(char *name, nodeType *name_list) {
	if (name_list->opr.oper == NAME_LIST)
		return (strcmp(name, name_list->opr.op[1]->id.sValue) == 0) || lookup_in_name_list(name, name_list->opr.op[0]);
	else//a single id
		return strcmp(name, name_list->id.sValue) == 0;
}

nodeType* lookup_field_in_field(char *name, nodeType *node) {
	nodeType *name_list = node->opr.op[0];
	nodeType *type_decl = node->opr.op[1];
	if (lookup_in_name_list(name, name_list)) {
		return type_decl;
	}
	else {
		return NULL;
	}
}

nodeType* lookup_field_in_field_list(char *name, nodeType *node) {
	if (node->opr.oper == FIELD_DECL_LIST) {
		nodeType* result = lookup_field_in_field(name, node->opr.op[1]);
		if (result)
			return result;

		result = lookup_field_in_field_list(name, node->opr.op[0]);
		if (result)
			return result;
	}
	else {//FIELD_DECL
		return lookup_field_in_field(name, node);
	}
	//Not found
	return NULL;
}

nodeType *lookup_field_in_record(char* name, nodeType *record) {
	nodeType *field_list = record->opr.op[0];
	return lookup_field_in_field_list(name, field_list);
}

bool name_list_equal(nodeType *n1, nodeType *n2) {
	if (n1->type != n2->type)
		return false;

	if (n1->opr.oper != n2->opr.oper)
		return false;

	if (n1->opr.oper == NAME_LIST)
		return name_list_equal(n1->opr.op[0], n2->opr.op[0]) && strcmp(n1->opr.op[1]->id.sValue, n2->opr.op[1]->id.sValue) == 0;
	else
		return strcmp(n1->id.sValue, n2->id.sValue) == 0;
}


bool const_value_equal(nodeType *n1, nodeType *n2) {
	if (n1->con.type != n2->con.type)
		return false;
	else {
		switch (n1->con.type) {
		case INTEGER:return n1->con.integer == n2->con.integer;
		case REAL:return n1->con.real == n2->con.real;
		case CHAR:return n1->con.character == n2->con.character;
		case STRING:return strcmp(n1->con.str, n2->con.str) == 0;
		case BOOL:return n1->con.boolean == n2->con.boolean;
		}
	}

	return false;
}

nodeType* check_record_access(char *record, char *field) {
	char message[100];
	nodeType *node = lookup(record);
	if (node->type == typeOpr && node->opr.oper == RECORD_TYPE_DECL) {
		//search given field in field_list
		nodeType *fieldnode = lookup_field_in_record(field, node);
		if (fieldnode == NULL) {
			sprintf(message, "%s is not a member of %s", field, record);
			type_error(message);
		}
		else
			return fieldnode;
	}
	else {
		sprintf(message, "%s is not a record", record);
		type_error(message);
	}

	return NULL;
}

nodeType *check_array_access(char *array, nodeType *index) {
	char message[100];
	nodeType *node = lookup(array);
	if (node->type == typeOpr && node->opr.oper == ARRAY_TYPE_DECL) {
		//incompatible index type 
		if (!type_equal(node->opr.op[0], index)) {
			sprintf(message, "incompatible index type, \"%s\" expected but \"%s\" found", type_str(node->opr.op[0]).data(), type_str(index).data());
			type_error(message);
		}
		else
			return node->opr.op[1];
	}
	else {
		sprintf(message, "%s is not an array", array);
		type_error(message);
	}

	return NULL;
}

bool check_case_expression(nodeType *expression, nodeType *cases) {
	// more than one
	if (cases->opr.oper == CASE_EXPR_LIST) {
		nodeType *case_list = cases->opr.op[0];
		nodeType *case_expr = cases->opr.op[1];								//get const_value
		return check_case_expression(expression, case_list) && type_equal(expression, case_expr->opr.op[0]);
	}
	else {//just one case
		return type_equal(expression, cases->opr.op[0]);
	}
}

void push_back_from_para_type_list(vector<nodeType*> &v, nodeType *p, bool name_or_type) {
	//if(p->opr.oper == PARA_TYPE_LIST){//para_type_list	: var_para_list COLON  simple_type_decl
	nodeType *var_para_list = p->opr.op[0];
	nodeType *simple_type_decl = p->opr.op[1];
	nodeType *name_list;
	if (var_para_list->opr.oper == VAR_PARA_LIST) //para_type_list: var_para_list COLON simple_type_decl
		name_list = var_para_list->opr.op[0];
	else //para_type_list: val_para_list COLON simple_type_decl
		name_list = var_para_list;

	if (name_or_type) { // name
		nodeType *node = name_list;
		vector<nodeType*> names = flatten(name_list);
		v.insert(v.end(), names.begin(), names.end());
	}
	else {//type
		int cnt = 0; //count number of name
		nodeType *node = name_list;
		while (true) {
			if (node->type == typeOpr) {
				cnt++;
				node = node->opr.op[0];
			}
			//single ID
			else {
				cnt++;
				break;
			}
		}
		for (int i = 0; i < cnt; i++)
			v.push_back(simple_type_decl);
	}
	//}
	//else{// para_type_list: val_para_list COLON simple_type_decl // what is this!?

	//	type_error("unknown behavior");
	//	nodeType *simple_type_decl = p;
	//}
}

void push_back_from_para_decl_list(vector<nodeType*> &v, nodeType *p, bool name_or_type) {
	//para_type_list node
	if (p->opr.oper == PARA_TYPE_LIST) {
		push_back_from_para_type_list(v, p, name_or_type);
	}
	//para_decl_list node
	else {
		push_back_from_para_decl_list(v, p->opr.op[0], name_or_type);
		push_back_from_para_type_list(v, p->opr.op[1], name_or_type);
	}
}

vector<nodeType *> get_para_types(nodeType *function_head) {
	vector<nodeType *> result;
	nodeType *para = function_head->opr.op[1];
	if (para == NULL) {//no parameters
		return result;
	}
	else {//para is para_decl_list
		push_back_from_para_decl_list(result, para, false);
		return result;
	}
}

vector<nodeType*> get_para_names(nodeType *function_head) {
	vector<nodeType *> result;
	nodeType *para = function_head->opr.op[1];
	if (para == NULL) {//no parameters
		return result;
	}
	else {//para is para_decl_list
		push_back_from_para_decl_list(result, para, true);
		return result;
	}
}

void push_back_from_root(vector<nodeType*>&v, nodeType *node) {
	if (node->type == typeOpr) {
		push_back_from_root(v, node->opr.op[0]);
		v.push_back(node->opr.op[1]);
	}
	else {
		v.push_back(node);
	}
}

//return a vector contains all leaves of the tree with given root
vector<nodeType*> flatten(nodeType *root) {
	vector<nodeType*> result;
	push_back_from_root(result, root);
	return result;
}

void get_from_field_decl(vector<string> &fields, vector<nodeType*> &types, nodeType*field_decl)
{
	vector<nodeType*> name_nodes = flatten(field_decl->opr.op[0]);
	vector<string> names(name_nodes.size());
	for (int i = 0; i < name_nodes.size(); i++) {
		names[i] = string(name_nodes[i]->id.sValue);
	}
	//concatenate
	vector<nodeType*> ts(names.size(), field_decl->opr.op[1]);
	types.insert(types.end(), ts.begin(), ts.end());
	fields.insert(fields.end(), names.begin(), names.end());
}

void get_from_field_decl_list(vector<string> &fields, vector<nodeType*> &types, nodeType*field_decl_list)
{
	if (field_decl_list->opr.oper == FIELD_DECL_LIST) {
		get_from_field_decl_list(fields, types, field_decl_list->opr.op[0]);
		get_from_field_decl(fields, types, field_decl_list->opr.op[1]);
	}
	else
		get_from_field_decl(fields, types, field_decl_list);
}

bool check_parameters(nodeType *function_head, nodeType* args_list) {
	vector<nodeType*> args;
	vector<nodeType*> para_types = get_para_types(function_head);
	if (args_list->type == typeOpr&&args_list->opr.oper == ARGS_LIST)
		args = flatten(args_list);
	else
		args.push_back(args_list);
	if (para_types.size() != args.size()) {
		type_error("parameter number mismatch");
	}
	else {
		for (int i = 0; i < para_types.size(); i++) {
			nodeType *tocheck = args[i]->exp;
			if (!type_equal(para_types[i], args[i]->exp)) {
				char message[100];
				sprintf(message, "Incompatible type for arg no. %d: expected \"%s\" but \"%s\" found", i + 1, type_str(para_types[i]).data(), type_str(args[i]->exp).data());
				type_error(message);
			}
		}
	}
	return true;

}

void range_check(nodeType* node) {
	nodeType*left = node->opr.op[0];
	nodeType*right = node->opr.op[1];

	if (node->opr.oper == ID_ID) {
		left = lookup(left->id.sValue);
		right = lookup(right->id.sValue);
	}

	if (left->type != typeCon || left->con.type != INTEGER) {
		char message[100];
		sprintf(message, "\"constant integer\" expected but \"%s\" found", type_str(left).data());
		type_error(message);
	}
	if (right->type != typeCon || right->con.type != INTEGER) {
		char message[100];
		sprintf(message, "\"constant integer\" expected but \"%s\" found", type_str(right).data());
		type_error(message);
	}
	if (left->con.integer > right->con.integer) {
		type_error("the value of begin should not greater than end");
	}
}

#endif // !_SYMBOL_H_
