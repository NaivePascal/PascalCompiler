#include "node.h"
#include "Parser.h"
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <sstream>

SymbolTag symbolTag;

SymbolTag::SymbolTag(){
    table[THEN]="THEN";
    table[CONST]="CONST";
    table[DO]="DO";
    table[READ]="READ";
    table[EQUAL]="EQUAL";
    table[GOTO]="GOTO";
    table[WHILE]="WHILE";
    table[MUL]="MUL";
    table[PLUS]="PLUS";
    table[UNEQUAL]="UNEQUAL";
    table[DIV]="DIV";
    table[MINUS]="MINUS";
    table[DOT]="DOT";
    table[CASE]="CASE";
    table[PBEGIN]="PBEGIN";
    table[LE]="LE";
    table[LB]="LB";
    table[SEMI]="SEMI";
    table[TO]="TO";
    table[UNTIL]="UNTIL";
    table[DOTDOT]="DOTDOT";
    table[RECORD]="RECORD";
    table[LT]="LT";
    table[COLON]="COLON";
    table[RB]="RB";
    table[ARRAY]="ARRAY";
    table[ASSIGN]="ASSIGN";
    table[FUNCTION]="FUNCTION";
    table[REPEAT]="REPEAT";
    table[END]="END";
    table[LP]="LP";
    table[FOR]="FOR";
    table[ELSE]="ELSE";
    table[GE]="GE";
    table[VAR]="VAR";
    table[RP]="RP";
    table[PROCEDURE]="PROCEDURE";
    table[IF]="IF";
    table[AND]="AND";
    table[GT]="GT";
    table[OF]="OF";
    table[DOWNTO]="DOWNTO";
    table[NOT]="NOT";
    table[COMMA]="COMMA";
    table[TYPE]="TYPE";
    table[OR]="OR";
    table[MOD]="MOD";
    table[PROGRAM]="PROGRAM";
    table[ROUTINE]="ROUTINE";
    table[ROUTINE_HEAD]="ROUTINE_HEAD";
    table[CONST_PART]="CONST_PART";
    table[CONST_EXPR_LIST]="CONST_EXPR_LIST";
    table[CONST_EXPR]="CONST_EXPR";
    table[CONST_VALUE]="CONST_VALUE";
    table[TYPE_PART]="TYPE_PART";
    table[TYPE_DECL_LIST]="TYPE_DECL_LIST";
    table[TYPE_DEFINITION]="TYPE_DEFINITION";
    table[TYPE_DECL]="TYPE_DECL";
    table[SIMPLE_TYPE_DECL]="SIMPLE_TYPE_DECL";
    table[ARRAY_TYPE_DECL]="ARRAY_TYPE_DECL";
    table[RECORD_TYPE_DECL]="RECORD_TYPE_DECL";
    table[FIELD_DECL_LIST]="FIELD_DECL_LIST";
    table[FIELD_DECL]="FIELD_DECL";
    table[NAME_LIST]="NAME_LIST";
    table[VAR_PART]="VAR_PART";
    table[VAR_DECL_LIST]="VAR_DECL_LIST";
    table[VAR_DECL]="VAR_DECL";
    table[ROUTINE_PART]="ROUTINE_PART";
    table[FUNCTION_DECL]="FUNCTION_DECL";
    table[FUNCTION_HEAD]="FUNCTION_HEAD";
    table[PROCEDURE_DECL]="PROCEDURE_DECL";
    table[PROCEDURE_HEAD]="PROCEDURE_HEAD";
    table[PARAMETERS]="PARAMETERS";
    table[PARA_DECL_LIST]="PARA_DECL_LIST";
    table[PARA_TYPE_LIST]="PARA_TYPE_LIST";
    table[VAR_PARA_LIST]="VAR_PARA_LIST";
    table[VAL_PARA_LIST]="VAL_PARA_LIST";
    table[ROUTINE_BODY]="ROUTINE_BODY";
    table[COMPOUND_STMT]="COMPOUND_STMT";
    table[STMT_LIST]="STMT_LIST";
    table[STMT]="STMT";
    table[NON_LABEL_STMT]="NON_LABEL_STMT";
    table[ASSIGN_STMT]="ASSIGN_STMT";
    table[PROC_STMT]="PROC_STMT";
    table[IF_STMT]="IF_STMT";
    table[ELSE_CLAUSE]="ELSE_CLAUSE";
    table[REPEAT_STMT]="REPEAT_STMT";
    table[WHILE_STMT]="WHILE_STMT";
    table[FOR_STMT]="FOR_STMT";
    table[CASE_STMT]="CASE_STMT";
    table[CASE_EXPR_LIST]="CASE_EXPR_LIST";
    table[CASE_EXPR]="CASE_EXPR";
    table[GOTO_STMT]="GOTO_STMT";
    table[EXPRESSION_LIST]="EXPRESSION_LIST";
    table[EXPRESSION]="EXPRESSION";
    table[EXPR]="EXPR";
    table[TERM]="TERM";
    table[FACTOR]="FACTOR";
    table[ARGS_LIST]="ARGS_LIST";
    table[SUB_ROUTINE]="SUB_ROUTINE";
    table[BOOL]="BOOL";
    table[CONST_POSITIVE_POSITIVE]="CONST_POSITIVE_POSITIVE";
    table[CONST_NEGATIVE_POSITIVE]="CONST_NEGATIVE_POSITIVE";
    table[CONST_NEGATIVE_NEGATIVE]="CONST_NEGATIVE_NEGATIVE";
    table[ENUM]="ENUM";
    table[ID_ID]="ID_ID";
    table[INTEGER]="INTEGER";
    table[STRING]="STRING";
    table[CHAR]="CHAR";
    table[REAL]="REAL";
    table[ID]="ID";
    table[ID]="ID";
    table[SYS_CON]="SYS_CON";
    table[SYS_TYPE]="SYS_TYPE";
    table[SYS_PROC]="SYS_PROC";
    table[SYS_FUNCT]="SYS_FUNCT";
    
    table[TRUE]="TRUE";
    table[FALSE]="FALSE";
    table[SYS_CON_TRUE]="SYS_CON_TRUE";
    table[SYS_CON_FALSE]="SYS_CON_FALSE";
    table[SYS_CON_MAXINT]="SYS_CON_MAXINT";
    table[SYS_TYPE_INTEGER]="SYS_TYPE_INTEGER";
    table[SYS_TYPE_REAL]="SYS_TYPE_REAL";
    table[SYS_TYPE_CHAR]="SYS_TYPE_CHAR";
    table[SYS_TYPE_BOOL]="SYS_TYPE_BOOL";
    table[SYS_FUNCT_ABS]="SYS_FUNCT_ABS";
    table[SYS_FUNCT_CHR]="SYS_FUNCT_CHR";
    table[SYS_FUNCT_ODD]="SYS_FUNCT_ODD";
    table[SYS_FUNCT_ORD]="SYS_FUNCT_ORD";
    table[SYS_FUNCT_PRED]="SYS_FUNCT_PRED";
    table[SYS_FUNCT_SQR]="SYS_FUNCT_SQR";
    table[SYS_FUNCT_SQRT]="SYS_FUNCT_SQRT";
    table[SYS_FUNCT_SUCC]="SYS_FUNCT_SUCC";
    table[SYS_PROC_WRITE]="SYS_PROC_WRITE";
    table[SYS_PROC_WRITELN]="SYS_PROC_WRITELN";
}


void printTreeImpl(nodeType* tree, int& count);
void printTreeNode(const string& s, int count);
string intToString(int i);
string doubleToString(int i);

string intToString(int i){
    stringstream  ss;
    ss << i;
    string ret;
    ss>>ret;
    return ret;
}
string doubleToString(int i){
    stringstream  ss;
    ss << i;
    string ret;
    ss>>ret;
    return ret;    
}

void printTree(nodeType* tree){
    int count=0;
    cout<<"***********************************************************"<<endl;
    cout<<"syntax tree:"<<endl;
    cout<<"***********************************************************"<<endl;
    printTreeImpl(tree, count);
    cout<<"***********************************************************"<<endl;
    cout<<"end"<<endl;
    cout<<"***********************************************************"<<endl;
}

void printTreeImpl(nodeType* tree, int& count){
    count++;
    switch(tree->type){
        case typeCon:{
            string printStr="constant ";
            conNodeType* node = &tree->con;
            switch(tree->con.type){
                case INTEGER:{
                    printStr += "integer: "+intToString(node->integer);
                }break;
                case STRING:{
                    printStr = printStr + "string: " + node->str;
                }break;
                case CHAR:{
                    printStr = printStr + "char: " + node->str;
                }break;
                case REAL:{
                    printStr = printStr + "real: " + doubleToString(node->real);
                }break;
                case BOOL:{
                    switch(node->boolean){
                        case(true):{
                            printStr = printStr + "bool: true";
                        }break;
                        case(false):{
                            printStr = printStr + "bool: false";
                        }break;
                    }
                }break;
                default: break;
            }
            printTreeNode(printStr,count);           
        }break;
        case typeId:{
            printTreeNode(string("Id: ")+tree->id.sValue,count);
        }break;
        case typeOpr:{
            printTreeNode(symbolTag.table[tree->opr.oper],count);
            for(int i=0;i<tree->opr.nops;i++){
                //cout<<tree->opr.nops<<endl;
                if(tree->opr.op[i]){
                    printTreeImpl(tree->opr.op[i],count);
                }
            }
        }break;
        case typeSysFunc:{
            printTreeNode("SysFunc: "+symbolTag.table[tree->sysProc.name],count);
        }break;
        case typeSysProc:{
            printTreeNode("SysProc: "+symbolTag.table[tree->sysFunc.name],count);
        }break;
        default:break;
    }
    
    count--;
}


void printTreeNode(const string& s, int count){
    for(int i=0;i<count;i++){
        cout<<"--";
    }
    cout<<s<<endl;
}