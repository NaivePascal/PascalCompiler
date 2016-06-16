/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INTEGER = 258,
    STRING = 259,
    CHAR = 260,
    REAL = 261,
    ID = 262,
    SYS_CON = 263,
    SYS_TYPE = 264,
    SYS_PROC = 265,
    SYS_FUNCT = 266,
    THEN = 267,
    CONST = 268,
    DO = 269,
    READ = 270,
    EQUAL = 271,
    GOTO = 272,
    WHILE = 273,
    MUL = 274,
    PLUS = 275,
    UNEQUAL = 276,
    DIV = 277,
    MINUS = 278,
    DOT = 279,
    CASE = 280,
    PBEGIN = 281,
    LE = 282,
    LB = 283,
    SEMI = 284,
    TO = 285,
    UNTIL = 286,
    DOTDOT = 287,
    RECORD = 288,
    LT = 289,
    COLON = 290,
    RB = 291,
    ARRAY = 292,
    ASSIGN = 293,
    FUNCTION = 294,
    REPEAT = 295,
    END = 296,
    LP = 297,
    FOR = 298,
    ELSE = 299,
    GE = 300,
    VAR = 301,
    RP = 302,
    PROCEDURE = 303,
    IF = 304,
    AND = 305,
    GT = 306,
    OF = 307,
    DOWNTO = 308,
    NOT = 309,
    COMMA = 310,
    TYPE = 311,
    OR = 312,
    MOD = 313,
    PROGRAM = 314,
    ROUTINE = 315,
    ROUTINE_HEAD = 316,
    CONST_PART = 317,
    CONST_EXPR_LIST = 318,
    CONST_EXPR = 319,
    CONST_VALUE = 320,
    TYPE_PART = 321,
    TYPE_DECL_LIST = 322,
    TYPE_DEFINITION = 323,
    TYPE_DECL = 324,
    SIMPLE_TYPE_DECL = 325,
    ARRAY_TYPE_DECL = 326,
    RECORD_TYPE_DECL = 327,
    FIELD_DECL_LIST = 328,
    FIELD_DECL = 329,
    NAME_LIST = 330,
    VAR_PART = 331,
    VAR_DECL_LIST = 332,
    VAR_DECL = 333,
    ROUTINE_PART = 334,
    FUNCTION_DECL = 335,
    FUNCTION_HEAD = 336,
    PROCEDURE_DECL = 337,
    PROCEDURE_HEAD = 338,
    PARAMETERS = 339,
    PARA_DECL_LIST = 340,
    PARA_TYPE_LIST = 341,
    VAR_PARA_LIST = 342,
    VAL_PARA_LIST = 343,
    ROUTINE_BODY = 344,
    COMPOUND_STMT = 345,
    STMT_LIST = 346,
    STMT = 347,
    NON_LABEL_STMT = 348,
    ASSIGN_STMT = 349,
    PROC_STMT = 350,
    IF_STMT = 351,
    ELSE_CLAUSE = 352,
    REPEAT_STMT = 353,
    WHILE_STMT = 354,
    FOR_STMT = 355,
    CASE_STMT = 356,
    CASE_EXPR_LIST = 357,
    CASE_EXPR = 358,
    GOTO_STMT = 359,
    EXPRESSION_LIST = 360,
    EXPRESSION = 361,
    EXPR = 362,
    TERM = 363,
    FACTOR = 364,
    ARGS_LIST = 365,
    SUB_ROUTINE = 366,
    BOOL = 367,
    CONST_POSITIVE_POSITIVE = 368,
    CONST_NEGATIVE_POSITIVE = 369,
    CONST_NEGATIVE_NEGATIVE = 370,
    ENUM = 371,
    ID_ID = 372
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 34 "Parser.y" /* yacc.c:1915  */

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

#line 185 "Parser.h" /* yacc.c:1915  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
