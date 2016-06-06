#ifndef _SYMBOL_H_
#define _SYMBOL_H_
#include "node.h"
#include "Parser.h"
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
vector<nodeType*> get_para_names(nodeType *function_head);
vector<nodeType*> get_para_types(nodeType *function_head);
vector<nodeType*> flatten(nodeType *root);



#include <map>
#include <string>
#include <vector>

using namespace std;

/*struct Symbol {
nodeType *type;
map<string, nodeType*> record;
};*/
bool lookup_in_name_list(char *name, nodeType *name_list);
bool isSubrange(nodeType *node) {
	return node->type == typeOpr && (
		node->opr.oper == CONST_NEGATIVE_NEGATIVE ||
		node->opr.oper == CONST_NEGATIVE_POSITIVE ||
		node->opr.oper == CONST_POSITIVE_POSITIVE);
}

vector<map<string, nodeType*>> symbol_table_stack;
//vector<map<string, symbol>> Symbol_table_stack;

void insert(char *name, nodeType* type) {
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

void enter_scope() {
	symbol_table_stack.push_back(map<string, nodeType*>());
}

void exit_scope() {
	symbol_table_stack.pop_back();
}

nodeType* _lookup(string name) {
	//traverse the stack backwards to find symbol
	for (auto iter = symbol_table_stack.rbegin(); iter != symbol_table_stack.rend(); iter++) {
		auto item = iter->find(name);
		if (item != iter->end()) {
			return item->second; //return node information
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
		for (int i = 0; i<cnt; i++)
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
		for (int i = 0; i<para_types.size(); i++) {
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

#endif // !_SYMBOL_H_
