/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "Parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <iostream>
#include "node.h"
#include "Lexer.h"
#include "Midcode.h"

int yylex(void);
void yyerror(char *s);
nodeType *con(void* value,int type);
//nodeType *id(int i);
nodeType *id(char *name);
nodeType *tp(int i);
nodeType *sysProc(int i);
//nodeType *sysProc(char *name);
nodeType *sysFunc(int i);
//nodeType *sysFunc(char *name);
nodeType *opr(int oper, int nops, ...);
void freeNode(nodeType *p) ;

//int count;

//hdj: symbol table
#include "symbol.h"
//symbol table end

nodeType* syntaxTree;


/* Line 371 of yacc.c  */
#line 101 "Parser.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "Parser.h".  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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
     ID_ID = 372,
     LABEL = 373,
     TRUE = 374,
     FALSE = 375,
     SYS_CON_TRUE = 376,
     SYS_CON_FALSE = 377,
     SYS_CON_MAXINT = 378,
     SYS_TYPE_INTEGER = 379,
     SYS_TYPE_REAL = 380,
     SYS_TYPE_CHAR = 381,
     SYS_TYPE_BOOL = 382,
     SYS_FUNCT_ABS = 383,
     SYS_FUNCT_CHR = 384,
     SYS_FUNCT_ODD = 385,
     SYS_FUNCT_ORD = 386,
     SYS_FUNCT_PRED = 387,
     SYS_FUNCT_SQR = 388,
     SYS_FUNCT_SQRT = 389,
     SYS_FUNCT_SUCC = 390,
     SYS_PROC_WRITE = 391,
     SYS_PROC_WRITELN = 392
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 37 "Parser.y"

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


/* Line 387 of yacc.c  */
#line 295 "Parser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 323 "Parser.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   350

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  138
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
#define YYNRULES  128
/* YYNRULES -- Number of states.  */
#define YYNSTATES  260

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   392

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,    11,    14,    17,    23,    24,    27,
      28,    32,    35,    39,    41,    43,    45,    47,    49,    52,
      53,    56,    58,    63,    65,    67,    69,    71,    73,    77,
      81,    86,    92,    96,   103,   107,   110,   112,   117,   121,
     123,   126,   127,   130,   132,   137,   140,   143,   145,   147,
     148,   153,   159,   164,   168,   172,   173,   177,   179,   183,
     187,   190,   192,   194,   198,   202,   203,   207,   209,   211,
     213,   215,   217,   219,   221,   223,   225,   227,   231,   238,
     244,   246,   251,   253,   258,   263,   269,   272,   273,   278,
     283,   292,   294,   296,   302,   305,   307,   312,   317,   320,
     324,   326,   330,   334,   338,   342,   346,   350,   352,   356,
     360,   364,   366,   370,   374,   378,   382,   384,   386,   391,
     393,   398,   400,   404,   407,   410,   415,   419,   423
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     139,     0,    -1,   140,   141,    24,    -1,    59,     7,    29,
      -1,   143,   172,    -1,   143,   172,    -1,   144,   145,   149,
     159,   162,    -1,    -1,    13,   146,    -1,    -1,   146,   147,
      29,    -1,   147,    29,    -1,     7,    16,   148,    -1,     3,
      -1,     6,    -1,     5,    -1,     4,    -1,     8,    -1,    56,
     150,    -1,    -1,   150,   151,    -1,   151,    -1,     7,    16,
     152,    29,    -1,   153,    -1,   154,    -1,   155,    -1,     9,
      -1,     7,    -1,    42,   158,    47,    -1,   148,    32,   148,
      -1,    23,   148,    32,   148,    -1,    23,   148,    32,    23,
     148,    -1,     7,    32,     7,    -1,    37,    28,   153,    36,
      52,   152,    -1,    33,   156,    41,    -1,   156,   157,    -1,
     157,    -1,   158,    35,   152,    29,    -1,   158,    55,     7,
      -1,     7,    -1,    46,   160,    -1,    -1,   160,   161,    -1,
     161,    -1,   158,    35,   152,    29,    -1,   162,   163,    -1,
     162,   165,    -1,   163,    -1,   165,    -1,    -1,   164,    29,
     142,    29,    -1,    39,     7,   167,    35,   153,    -1,   166,
      29,   142,    29,    -1,    48,     7,   167,    -1,    42,   168,
      47,    -1,    -1,   168,    29,   169,    -1,   169,    -1,   170,
      35,   153,    -1,   171,    35,   153,    -1,    46,   158,    -1,
     158,    -1,   173,    -1,    26,   174,    41,    -1,   174,   175,
      29,    -1,    -1,     3,    35,   176,    -1,   176,    -1,   177,
      -1,   178,    -1,   173,    -1,   179,    -1,   181,    -1,   182,
      -1,   183,    -1,   185,    -1,   188,    -1,     7,    38,   190,
      -1,     7,    28,   190,    36,    38,   190,    -1,     7,    24,
       7,    38,   190,    -1,     7,    -1,     7,    42,   194,    47,
      -1,    10,    -1,    10,    42,   189,    47,    -1,    15,    42,
     193,    47,    -1,    49,   190,    12,   175,   180,    -1,    44,
     175,    -1,    -1,    40,   174,    31,   190,    -1,    18,   190,
      14,   175,    -1,    43,     7,    38,   190,   184,   190,    14,
     175,    -1,    30,    -1,    53,    -1,    25,   190,    52,   186,
      41,    -1,   186,   187,    -1,   187,    -1,   148,    35,   175,
      29,    -1,     7,    35,   175,    29,    -1,    17,     3,    -1,
     189,    55,   190,    -1,   190,    -1,   190,    45,   191,    -1,
     190,    51,   191,    -1,   190,    27,   191,    -1,   190,    34,
     191,    -1,   190,    16,   191,    -1,   190,    21,   191,    -1,
     191,    -1,   191,    20,   192,    -1,   191,    23,   192,    -1,
     191,    57,   192,    -1,   192,    -1,   192,    19,   193,    -1,
     192,    22,   193,    -1,   192,    58,   193,    -1,   192,    50,
     193,    -1,   193,    -1,     7,    -1,     7,    42,   194,    47,
      -1,    11,    -1,    11,    42,   194,    47,    -1,   148,    -1,
      42,   190,    47,    -1,    54,   193,    -1,    23,   193,    -1,
       7,    28,   190,    36,    -1,     7,    24,     7,    -1,   194,
      55,   190,    -1,   190,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    96,    96,   109,   117,   121,   125,   129,   131,   135,
     138,   141,   145,   153,   154,   155,   156,   157,   171,   175,
     178,   181,   185,   195,   196,   197,   199,   200,   202,   207,
     213,   218,   223,   230,   251,   258,   260,   263,   267,   271,
     277,   279,   282,   284,   286,   308,   310,   312,   314,   317,
     320,   333,   350,   358,   373,   376,   379,   381,   385,   389,
     396,   400,   404,   408,   412,   415,   418,   420,   424,   426,
     428,   430,   432,   434,   436,   438,   440,   444,   488,   518,
     553,   555,   557,   559,   561,   565,   575,   577,   579,   591,
     603,   628,   629,   631,   641,   643,   648,   650,   654,   658,
     660,   664,   679,   694,   709,   724,   739,   754,   758,   781,
     801,   817,   823,   843,   863,   877,   892,   898,   920,   938,
     945,   987,   994,   998,  1013,  1028,  1037,  1048,  1050
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "STRING", "CHAR", "REAL",
  "ID", "SYS_CON", "SYS_TYPE", "SYS_PROC", "SYS_FUNCT", "THEN", "CONST",
  "DO", "READ", "EQUAL", "GOTO", "WHILE", "MUL", "PLUS", "UNEQUAL", "DIV",
  "MINUS", "DOT", "CASE", "PBEGIN", "LE", "LB", "SEMI", "TO", "UNTIL",
  "DOTDOT", "RECORD", "LT", "COLON", "RB", "ARRAY", "ASSIGN", "FUNCTION",
  "REPEAT", "END", "LP", "FOR", "ELSE", "GE", "VAR", "RP", "PROCEDURE",
  "IF", "AND", "GT", "OF", "DOWNTO", "NOT", "COMMA", "TYPE", "OR", "MOD",
  "PROGRAM", "ROUTINE", "ROUTINE_HEAD", "CONST_PART", "CONST_EXPR_LIST",
  "CONST_EXPR", "CONST_VALUE", "TYPE_PART", "TYPE_DECL_LIST",
  "TYPE_DEFINITION", "TYPE_DECL", "SIMPLE_TYPE_DECL", "ARRAY_TYPE_DECL",
  "RECORD_TYPE_DECL", "FIELD_DECL_LIST", "FIELD_DECL", "NAME_LIST",
  "VAR_PART", "VAR_DECL_LIST", "VAR_DECL", "ROUTINE_PART", "FUNCTION_DECL",
  "FUNCTION_HEAD", "PROCEDURE_DECL", "PROCEDURE_HEAD", "PARAMETERS",
  "PARA_DECL_LIST", "PARA_TYPE_LIST", "VAR_PARA_LIST", "VAL_PARA_LIST",
  "ROUTINE_BODY", "COMPOUND_STMT", "STMT_LIST", "STMT", "NON_LABEL_STMT",
  "ASSIGN_STMT", "PROC_STMT", "IF_STMT", "ELSE_CLAUSE", "REPEAT_STMT",
  "WHILE_STMT", "FOR_STMT", "CASE_STMT", "CASE_EXPR_LIST", "CASE_EXPR",
  "GOTO_STMT", "EXPRESSION_LIST", "EXPRESSION", "EXPR", "TERM", "FACTOR",
  "ARGS_LIST", "SUB_ROUTINE", "BOOL", "CONST_POSITIVE_POSITIVE",
  "CONST_NEGATIVE_POSITIVE", "CONST_NEGATIVE_NEGATIVE", "ENUM", "ID_ID",
  "LABEL", "TRUE", "FALSE", "SYS_CON_TRUE", "SYS_CON_FALSE",
  "SYS_CON_MAXINT", "SYS_TYPE_INTEGER", "SYS_TYPE_REAL", "SYS_TYPE_CHAR",
  "SYS_TYPE_BOOL", "SYS_FUNCT_ABS", "SYS_FUNCT_CHR", "SYS_FUNCT_ODD",
  "SYS_FUNCT_ORD", "SYS_FUNCT_PRED", "SYS_FUNCT_SQR", "SYS_FUNCT_SQRT",
  "SYS_FUNCT_SUCC", "SYS_PROC_WRITE", "SYS_PROC_WRITELN", "$accept",
  "program", "program_head", "routine", "sub_routine", "routine_head",
  "label_part", "const_part", "const_expr_list", "const_expr",
  "const_value", "type_part", "type_decl_list", "type_definition",
  "type_decl", "simple_type_decl", "array_type_decl", "record_type_decl",
  "field_decl_list", "field_decl", "name_list", "var_part",
  "var_decl_list", "var_decl", "routine_part", "function_decl",
  "function_head", "procedure_decl", "procedure_head", "parameters",
  "para_decl_list", "para_type_list", "var_para_list", "val_para_list",
  "routine_body", "compound_stmt", "stmt_list", "stmt", "non_label_stmt",
  "assign_stmt", "proc_stmt", "if_stmt", "else_clause", "repeat_stmt",
  "while_stmt", "for_stmt", "direction", "case_stmt", "case_expr_list",
  "case_expr", "goto_stmt", "expression_list", "expression", "expr",
  "term", "factor", "args_list", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   138,   139,   140,   141,   142,   143,   144,   145,   145,
     146,   146,   147,   148,   148,   148,   148,   148,   149,   149,
     150,   150,   151,   152,   152,   152,   153,   153,   153,   153,
     153,   153,   153,   154,   155,   156,   156,   157,   158,   158,
     159,   159,   160,   160,   161,   162,   162,   162,   162,   162,
     163,   164,   165,   166,   167,   167,   168,   168,   169,   169,
     170,   171,   172,   173,   174,   174,   175,   175,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   177,   177,   177,
     178,   178,   178,   178,   178,   179,   180,   180,   181,   182,
     183,   184,   184,   185,   186,   186,   187,   187,   188,   189,
     189,   190,   190,   190,   190,   190,   190,   190,   191,   191,
     191,   191,   192,   192,   192,   192,   192,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   194,   194
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     3,     2,     2,     5,     0,     2,     0,
       3,     2,     3,     1,     1,     1,     1,     1,     2,     0,
       2,     1,     4,     1,     1,     1,     1,     1,     3,     3,
       4,     5,     3,     6,     3,     2,     1,     4,     3,     1,
       2,     0,     2,     1,     4,     2,     2,     1,     1,     0,
       4,     5,     4,     3,     3,     0,     3,     1,     3,     3,
       2,     1,     1,     3,     3,     0,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     6,     5,
       1,     4,     1,     4,     4,     5,     2,     0,     4,     4,
       8,     1,     1,     5,     2,     1,     4,     4,     2,     3,
       1,     3,     3,     3,     3,     3,     3,     1,     3,     3,
       3,     1,     3,     3,     3,     3,     1,     1,     4,     1,
       4,     1,     3,     2,     2,     4,     3,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     7,     0,     1,     0,     0,     9,     3,
       2,    65,     4,    62,     0,    19,     0,     0,     8,     0,
       0,    41,     0,    80,    82,     0,     0,     0,     0,    65,
      63,     0,     0,    70,     0,    67,    68,    69,    71,    72,
      73,    74,    75,    76,     0,     0,    11,     0,    18,    21,
       0,    49,     0,     0,     0,     0,     0,     0,     0,    98,
      13,    16,    15,    14,   117,    17,   119,     0,     0,     0,
     121,     0,   107,   111,   116,     0,     0,     0,     0,    64,
      12,    10,     0,    20,    39,     0,    40,    43,     0,     0,
       6,    47,     0,    48,     0,    66,     0,     0,    77,   128,
       0,     0,   100,     0,     0,     0,     0,     0,   124,     0,
     123,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    27,
      26,     0,     0,     0,     0,     0,     0,    23,    24,    25,
       0,     0,    42,    55,    55,    45,    46,     7,     7,     0,
       0,    81,     0,    83,     0,    84,   126,     0,     0,     0,
     122,    89,   105,   106,   103,   104,   101,   102,   108,   109,
     110,   112,   113,   115,   114,     0,     0,     0,    95,    88,
       0,    87,     0,     0,     0,    36,     0,     0,     0,     0,
      22,     0,    38,     0,     0,    53,     0,     0,     0,    79,
       0,   127,    99,   125,   118,   120,     0,     0,    93,    94,
      91,    92,     0,     0,    85,    32,     0,    34,    35,     0,
       0,    28,    29,    44,     0,    61,     0,    57,     0,     0,
       0,    50,     5,    52,    78,     0,     0,     0,    86,     0,
      30,     0,     0,    60,     0,    54,     0,     0,    51,    97,
      96,     0,    31,    37,     0,    56,    58,    59,    90,    33
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     6,   196,   197,     8,    15,    18,    19,
      70,    21,    48,    49,   136,   137,   138,   139,   184,   185,
      85,    51,    86,    87,    90,    91,    92,    93,    94,   194,
     226,   227,   228,   229,    12,    33,    16,    34,    35,    36,
      37,    38,   214,    39,    40,    41,   212,    42,   177,   178,
      43,   101,    99,    72,    73,    74,   100
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -185
static const yytype_int16 yypact[] =
{
     -37,    18,    33,  -185,    35,  -185,    61,    66,    92,  -185,
    -185,  -185,  -185,  -185,    91,    51,   141,    93,    91,    89,
     112,    79,   106,   155,    86,    96,   124,    36,    36,  -185,
    -185,   140,    36,  -185,   128,  -185,  -185,  -185,  -185,  -185,
    -185,  -185,  -185,  -185,   342,   132,  -185,   137,   112,  -185,
     157,   -22,   145,   158,    36,    36,    36,    36,    36,  -185,
    -185,  -185,  -185,  -185,    55,  -185,   126,    36,    36,    36,
    -185,   230,     4,    -1,  -185,    72,   189,   135,   221,  -185,
    -185,  -185,    47,  -185,  -185,   -20,   157,  -185,   162,   167,
     -22,  -185,   147,  -185,   149,  -185,   142,   261,   287,   287,
     -27,   -18,   287,   151,   180,    36,    36,    36,  -185,   262,
    -185,   209,    36,    36,    36,    36,    36,    36,    36,    36,
      36,    36,    36,    36,    36,   319,    36,    36,   209,   168,
    -185,   342,   157,   173,   157,   176,   182,  -185,  -185,  -185,
      47,   198,  -185,   171,   171,  -185,  -185,  -185,  -185,    36,
     179,  -185,    36,  -185,    36,  -185,  -185,   284,    75,    85,
    -185,  -185,     4,     4,     4,     4,     4,     4,    -1,    -1,
      -1,  -185,  -185,  -185,  -185,   174,   183,   108,  -185,   287,
     220,   181,   223,   196,     7,  -185,   -19,    68,    95,   342,
    -185,   202,  -185,    12,   204,  -185,   211,    66,   214,   287,
      36,   287,   287,  -185,  -185,  -185,   209,   209,  -185,  -185,
    -185,  -185,    36,   209,  -185,  -185,   131,  -185,  -185,    47,
     217,  -185,  -185,  -185,   157,   190,   -17,  -185,   224,   225,
      68,  -185,  -185,  -185,   287,   232,   233,   253,  -185,   342,
    -185,   234,   216,   190,    12,  -185,    68,    68,  -185,  -185,
    -185,   209,  -185,  -185,    47,  -185,  -185,  -185,  -185,  -185
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -185,  -185,  -185,  -185,   122,   273,  -185,  -185,  -185,   238,
     -44,  -185,  -185,   231,  -133,  -184,  -185,  -185,  -185,   100,
    -124,  -185,  -185,   199,  -185,   200,  -185,   201,  -185,   148,
    -185,    42,  -185,  -185,    97,    -6,   264,  -105,   247,  -185,
    -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,   125,
    -185,  -185,   -23,   227,   103,   -56,   -12
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      80,    13,   103,   220,    71,    75,   161,   191,   186,    78,
     188,   108,   244,   110,    84,   140,   219,    88,   121,    84,
     151,   122,     1,   181,   118,     4,    89,   119,   152,   153,
     245,    97,    98,     5,   102,   141,   141,   154,   135,    60,
      61,    62,    63,    64,    65,   109,   248,    66,   217,   123,
      60,    61,    62,    63,   129,    65,   130,   124,   224,    67,
     186,   120,   256,   257,     9,   171,   172,   173,   174,   225,
     131,    60,    61,    62,    63,   129,    65,   130,    68,   104,
     132,   176,   157,   105,   133,    10,   241,   183,   112,   134,
      69,   131,    11,   113,   158,   159,   135,   106,    17,   114,
     243,   235,   236,   179,   180,    14,   115,    20,   238,    44,
     134,    60,    61,    62,    63,   175,    65,   116,    46,    47,
     225,   259,   204,   117,   125,    50,   199,    59,    57,   201,
     152,   202,   205,   176,    60,    61,    62,    63,    58,    65,
     152,    52,   221,   135,    22,   222,   258,    77,    23,   208,
     141,    24,    23,    82,   239,    24,    25,    79,    26,    27,
      25,    81,    26,    27,    84,    96,    28,    11,   107,   143,
      28,    11,   240,   127,   144,   135,   147,   234,   148,    53,
     149,    29,    30,    54,    31,    29,   135,   156,    31,   237,
      32,    13,    22,    55,    32,   252,    23,    56,   155,    24,
     182,   187,   135,   135,    25,   192,    26,    27,   189,   206,
     135,   190,    22,   193,    28,    11,    23,   200,   207,    24,
     126,   168,   169,   170,    25,   213,    26,    27,   216,    29,
     215,   223,    31,   128,    28,    11,   112,   112,    32,   230,
     231,   113,   113,   233,   111,   141,   112,   114,   114,    29,
     210,   113,    31,   242,   115,   115,    45,   114,    32,   246,
     247,   249,   250,   253,   115,   116,   116,   251,   254,   112,
     198,   117,   117,   211,   113,   116,     7,   112,   112,    83,
     114,   117,   113,   113,   218,   142,   255,   115,   114,   114,
     145,   146,   195,    76,   232,   115,   115,   150,   116,    95,
     112,     0,   209,   112,   117,   113,   116,   116,   113,   160,
       0,   114,   117,   117,   114,     0,     0,     0,   115,     0,
     203,   115,    60,    61,    62,    63,   175,    65,     0,   116,
       0,     0,   116,     0,     0,   117,     0,     0,   117,   162,
     163,   164,   165,   166,   167,    60,    61,    62,    63,     0,
      65
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-185)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      44,     7,    58,   187,    27,    28,   111,   140,   132,    32,
     134,    67,    29,    69,     7,    35,    35,    39,    19,     7,
      47,    22,    59,   128,    20,     7,    48,    23,    55,    47,
      47,    54,    55,     0,    57,    55,    55,    55,    82,     3,
       4,     5,     6,     7,     8,    68,   230,    11,    41,    50,
       3,     4,     5,     6,     7,     8,     9,    58,    46,    23,
     184,    57,   246,   247,    29,   121,   122,   123,   124,   193,
      23,     3,     4,     5,     6,     7,     8,     9,    42,    24,
      33,   125,   105,    28,    37,    24,   219,   131,    16,    42,
      54,    23,    26,    21,   106,   107,   140,    42,     7,    27,
     224,   206,   207,   126,   127,    13,    34,    56,   213,    16,
      42,     3,     4,     5,     6,     7,     8,    45,    29,     7,
     244,   254,    47,    51,    52,    46,   149,     3,    42,   152,
      55,   154,    47,   177,     3,     4,     5,     6,    42,     8,
      55,    35,    47,   187,     3,   189,   251,     7,     7,    41,
      55,    10,     7,    16,    23,    10,    15,    29,    17,    18,
      15,    29,    17,    18,     7,     7,    25,    26,    42,     7,
      25,    26,   216,    38,     7,   219,    29,   200,    29,    24,
      38,    40,    41,    28,    43,    40,   230,     7,    43,   212,
      49,   197,     3,    38,    49,   239,     7,    42,    47,    10,
      32,    28,   246,   247,    15,     7,    17,    18,    32,    35,
     254,    29,     3,    42,    25,    26,     7,    38,    35,    10,
      31,   118,   119,   120,    15,    44,    17,    18,    32,    40,
       7,    29,    43,    12,    25,    26,    16,    16,    49,    35,
      29,    21,    21,    29,    14,    55,    16,    27,    27,    40,
      30,    21,    43,    36,    34,    34,    18,    27,    49,    35,
      35,    29,    29,    29,    34,    45,    45,    14,    52,    16,
     148,    51,    51,    53,    21,    45,     3,    16,    16,    48,
      27,    51,    21,    21,   184,    86,   244,    34,    27,    27,
      90,    90,   144,    29,   197,    34,    34,    36,    45,    52,
      16,    -1,   177,    16,    51,    21,    45,    45,    21,    47,
      -1,    27,    51,    51,    27,    -1,    -1,    -1,    34,    -1,
      36,    34,     3,     4,     5,     6,     7,     8,    -1,    45,
      -1,    -1,    45,    -1,    -1,    51,    -1,    -1,    51,   112,
     113,   114,   115,   116,   117,     3,     4,     5,     6,    -1,
       8
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    59,   139,   140,     7,     0,   141,   143,   144,    29,
      24,    26,   172,   173,    13,   145,   174,     7,   146,   147,
      56,   149,     3,     7,    10,    15,    17,    18,    25,    40,
      41,    43,    49,   173,   175,   176,   177,   178,   179,   181,
     182,   183,   185,   188,    16,   147,    29,     7,   150,   151,
      46,   159,    35,    24,    28,    38,    42,    42,    42,     3,
       3,     4,     5,     6,     7,     8,    11,    23,    42,    54,
     148,   190,   191,   192,   193,   190,   174,     7,   190,    29,
     148,    29,    16,   151,     7,   158,   160,   161,    39,    48,
     162,   163,   164,   165,   166,   176,     7,   190,   190,   190,
     194,   189,   190,   193,    24,    28,    42,    42,   193,   190,
     193,    14,    16,    21,    27,    34,    45,    51,    20,    23,
      57,    19,    22,    50,    58,    52,    31,    38,    12,     7,
       9,    23,    33,    37,    42,   148,   152,   153,   154,   155,
      35,    55,   161,     7,     7,   163,   165,    29,    29,    38,
      36,    47,    55,    47,    55,    47,     7,   190,   194,   194,
      47,   175,   191,   191,   191,   191,   191,   191,   192,   192,
     192,   193,   193,   193,   193,     7,   148,   186,   187,   190,
     190,   175,    32,   148,   156,   157,   158,    28,   158,    32,
      29,   152,     7,    42,   167,   167,   142,   143,   142,   190,
      38,   190,   190,    36,    47,    47,    35,    35,    41,   187,
      30,    53,   184,    44,   180,     7,    32,    41,   157,    35,
     153,    47,   148,    29,    46,   158,   168,   169,   170,   171,
      35,    29,   172,    29,   190,   175,   175,   190,   175,    23,
     148,   152,    36,   158,    29,    47,    35,    35,   153,    29,
      29,    14,   148,    29,    52,   169,   153,   153,   175,   152
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 96 "Parser.y"
    {
					syntaxTree = (yyval.nodetype) = (yyvsp[(2) - (3)].nodetype);
					
					printTree(syntaxTree);
					printSymbolTable();
					Gen_Drive(syntaxTree, "output.txt");

					//hdj
					//program ends, exit scope
					exit_scope();
				}
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 110 "Parser.y"
    {
					//hdj
					//program starts, enter new scope
					enter_scope();
				}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 118 "Parser.y"
    {(yyval.nodetype) = opr(ROUTINE,2,(yyvsp[(1) - (2)].nodetype),(yyvsp[(2) - (2)].nodetype));}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 122 "Parser.y"
    {(yyval.nodetype) = opr(ROUTINE,2,(yyvsp[(1) - (2)].nodetype),(yyvsp[(2) - (2)].nodetype));}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 126 "Parser.y"
    {(yyval.nodetype) = opr(ROUTINE_HEAD,3,(yyvsp[(2) - (5)].nodetype),(yyvsp[(3) - (5)].nodetype),(yyvsp[(4) - (5)].nodetype));}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 131 "Parser.y"
    {
					(yyval.nodetype)=(yyvsp[(2) - (2)].nodetype);
}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 135 "Parser.y"
    {(yyval.nodetype) = NULL;}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 138 "Parser.y"
    {
					(yyval.nodetype) = opr(CONST_EXPR_LIST,2,(yyvsp[(1) - (3)].nodetype),(yyvsp[(2) - (3)].nodetype));
}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 141 "Parser.y"
    {
					(yyval.nodetype) = (yyvsp[(1) - (2)].nodetype);
				}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 145 "Parser.y"
    {
					(yyval.nodetype) = opr(CONST_EXPR,2,id((yyvsp[(1) - (3)].sValue)),(yyvsp[(3) - (3)].nodetype));
					//example:
					//const
					//PI = 3.141592654;
					insert((yyvsp[(1) - (3)].sValue), (yyvsp[(3) - (3)].nodetype));
}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 153 "Parser.y"
    {(yyval.nodetype) = con(&((yyvsp[(1) - (1)].iValue)),INTEGER);}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 154 "Parser.y"
    {(yyval.nodetype) = con(&((yyvsp[(1) - (1)].rValue)),REAL);}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 155 "Parser.y"
    {(yyval.nodetype) = con(&((yyvsp[(1) - (1)].cValue)),CHAR);}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 156 "Parser.y"
    {(yyval.nodetype) = con(((yyvsp[(1) - (1)].sValue)),STRING);}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 157 "Parser.y"
    {
					if((yyvsp[(1) - (1)].syscon)==SYS_CON_TRUE){
						int value = true;
						(yyval.nodetype) = con(&value,BOOL);
					}else if((yyvsp[(1) - (1)].syscon)==SYS_CON_FALSE){
						int value = false;
						(yyval.nodetype) = con(&value,BOOL);
					}else if((yyvsp[(1) - (1)].syscon)==SYS_CON_MAXINT){
						int value = INT_MAX;
						(yyval.nodetype) = con(&value, INTEGER);
					}
				}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 171 "Parser.y"
    {
					(yyval.nodetype) = (yyvsp[(2) - (2)].nodetype);
				}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 175 "Parser.y"
    {(yyval.nodetype)=NULL;}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 178 "Parser.y"
    {
					(yyval.nodetype)=opr(TYPE_DECL_LIST,2,(yyvsp[(1) - (2)].nodetype),(yyvsp[(2) - (2)].nodetype));
}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 181 "Parser.y"
    {
					(yyval.nodetype)=(yyvsp[(1) - (1)].nodetype);
				}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 185 "Parser.y"
    {
					(yyval.nodetype)=opr(TYPE_DEFINITION,2,(yyvsp[(1) - (4)].sValue),(yyvsp[(3) - (4)].nodetype));

					//example:
					//type
					//days, age = integer;
					insert((yyvsp[(1) - (4)].sValue), (yyvsp[(3) - (4)].nodetype));

}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 195 "Parser.y"
    {(yyval.nodetype)=(yyvsp[(1) - (1)].nodetype);}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 196 "Parser.y"
    {(yyval.nodetype)=(yyvsp[(1) - (1)].nodetype);}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 197 "Parser.y"
    {(yyval.nodetype)=(yyvsp[(1) - (1)].nodetype);}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 199 "Parser.y"
    {(yyval.nodetype)=tp((yyvsp[(1) - (1)].sysType));}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 201 "Parser.y"
    {(yyval.nodetype)=id((yyvsp[(1) - (1)].sValue));}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 203 "Parser.y"
    {
					//$$=$2;
					(yyval.nodetype)=opr(ENUM, 1, (yyvsp[(2) - (3)].nodetype));
				}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 208 "Parser.y"
    {
					//check error : Upper bound of range is less than lower bound
					(yyval.nodetype)=opr(CONST_POSITIVE_POSITIVE,2,(yyvsp[(1) - (3)].nodetype),(yyvsp[(3) - (3)].nodetype));
					range_check((yyval.nodetype));
				}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 214 "Parser.y"
    {
					(yyval.nodetype)=opr(CONST_NEGATIVE_POSITIVE,2,(yyvsp[(2) - (4)].nodetype),(yyvsp[(4) - (4)].nodetype));
					range_check((yyval.nodetype));
				}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 219 "Parser.y"
    {
					(yyval.nodetype)=opr(CONST_NEGATIVE_NEGATIVE,2,(yyvsp[(2) - (5)].nodetype),(yyvsp[(5) - (5)].nodetype));
					range_check((yyval.nodetype));
				}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 224 "Parser.y"
    {
					(yyval.nodetype)=opr(ID_ID,2,(yyvsp[(1) - (3)].sValue),(yyvsp[(3) - (3)].sValue));
					range_check((yyval.nodetype));
				}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 231 "Parser.y"
    {
					(yyval.nodetype)=opr(ARRAY_TYPE_DECL,2,(yyvsp[(3) - (6)].nodetype),(yyvsp[(6) - (6)].nodetype));
					//type check
					//index-type can be any scalar data type except real
					if((yyvsp[(3) - (6)].nodetype)->type == typeType){
						if((yyvsp[(3) - (6)].nodetype)->tp.type == SYS_TYPE_REAL){
							type_error("Error in type definition");
						}
					}
					else if((yyvsp[(3) - (6)].nodetype)->type == typeOpr){
						if((yyvsp[(3) - (6)].nodetype)->opr.oper == ENUM||(yyvsp[(3) - (6)].nodetype)->opr.oper==CONST_POSITIVE_POSITIVE||(yyvsp[(3) - (6)].nodetype)->opr.oper==CONST_NEGATIVE_NEGATIVE){

						}
						else{
							type_error("Error in type definition");	
						}
					}
				}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 252 "Parser.y"
    {
					//$$=$2;
					(yyval.nodetype)=opr(RECORD_TYPE_DECL, 1, (yyvsp[(2) - (3)].nodetype));
				}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 259 "Parser.y"
    {(yyval.nodetype)=opr(FIELD_DECL_LIST,2,(yyvsp[(1) - (2)].nodetype),(yyvsp[(2) - (2)].nodetype));}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 260 "Parser.y"
    {(yyval.nodetype)=(yyvsp[(1) - (1)].nodetype);}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 264 "Parser.y"
    {(yyval.nodetype)=opr(FIELD_DECL,2,(yyvsp[(1) - (4)].nodetype),(yyvsp[(3) - (4)].nodetype));}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 268 "Parser.y"
    {
					(yyval.nodetype)=opr(NAME_LIST,2,(yyvsp[(1) - (3)].nodetype),id((yyvsp[(3) - (3)].sValue)));
				}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 272 "Parser.y"
    {
					(yyval.nodetype)=id((yyvsp[(1) - (1)].sValue));
				}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 277 "Parser.y"
    {(yyval.nodetype)=(yyvsp[(2) - (2)].nodetype);}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 279 "Parser.y"
    {(yyval.nodetype)=NULL;}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 283 "Parser.y"
    {(yyval.nodetype)=opr(VAR_DECL_LIST,2,(yyvsp[(1) - (2)].nodetype),(yyvsp[(2) - (2)].nodetype));}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 284 "Parser.y"
    {(yyval.nodetype)=(yyvsp[(1) - (1)].nodetype);}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 287 "Parser.y"
    {
					(yyval.nodetype)=opr(VAR_DECL,2,(yyvsp[(1) - (4)].nodetype),(yyvsp[(3) - (4)].nodetype));
					//just one name
					if((yyvsp[(1) - (4)].nodetype)->type==typeId){
						insert((yyvsp[(1) - (4)].nodetype)->id.sValue, (yyvsp[(3) - (4)].nodetype));
					}
					//more than one name
					else{
						nodeType *p = (yyvsp[(1) - (4)].nodetype);
						while(1){
							insert(p->opr.op[1]->id.sValue, (yyvsp[(3) - (4)].nodetype));
							p = p->opr.op[0];
							if(p->type==typeId)
								break;
						}
						insert(p->id.sValue, (yyvsp[(3) - (4)].nodetype));
					}

				}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 309 "Parser.y"
    {(yyval.nodetype)=opr(ROUTINE_PART,2,(yyvsp[(1) - (2)].nodetype),(yyvsp[(2) - (2)].nodetype));}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 311 "Parser.y"
    {(yyval.nodetype)=opr(ROUTINE_PART,2,(yyvsp[(1) - (2)].nodetype),(yyvsp[(2) - (2)].nodetype));}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 313 "Parser.y"
    {(yyval.nodetype)=opr(ROUTINE_PART,1,(yyvsp[(1) - (1)].nodetype));}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 315 "Parser.y"
    {(yyval.nodetype)=opr(ROUTINE_PART,1,(yyvsp[(1) - (1)].nodetype));}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 317 "Parser.y"
    {(yyval.nodetype)=NULL;}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 321 "Parser.y"
    {
				//hdj:function overloading is not supported yet
				//example:
				//function max(num1, num2: integer): integer;
					(yyval.nodetype)=opr(FUNCTION_DECL,2,(yyvsp[(1) - (4)].nodetype),(yyvsp[(3) - (4)].nodetype));
				
				// a function is finished, now exit its scope
				exit_scope();
				
				}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 334 "Parser.y"
    {
					nodeType* node = opr(FUNCTION_HEAD,3,id((yyvsp[(2) - (5)].sValue)),(yyvsp[(3) - (5)].nodetype),(yyvsp[(5) - (5)].nodetype));
					(yyval.nodetype)= node;
					insert((yyvsp[(2) - (5)].sValue), node);

					//hdj
					//enter a new scope
					enter_scope();
					vector<nodeType*> parameters = get_para_names(node);
					vector<nodeType*> types = get_para_types(node);
					for(int i=0;i<types.size();i++){
						insert(parameters[i]->id.sValue, types[i]);
					}
				}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 351 "Parser.y"
    {
					opr(PROCEDURE_DECL,2,(yyvsp[(1) - (4)].nodetype),(yyvsp[(3) - (4)].nodetype));
					// a procedure is finished, now exit its scope
					exit_scope();
				}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 359 "Parser.y"
    {
					nodeType* node = opr(PROCEDURE_HEAD,2,id((yyvsp[(2) - (3)].sValue)),(yyvsp[(3) - (3)].nodetype));
					(yyval.nodetype)=node;
					insert((yyvsp[(2) - (3)].sValue), node);
					//enter a new scope
					enter_scope();
					vector<nodeType*> parameters = get_para_names(node);
					vector<nodeType*> types = get_para_types(node);
					for(int i=0;i<types.size();i++){
						insert(parameters[i]->id.sValue, types[i]);
					}
				}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 374 "Parser.y"
    {(yyval.nodetype)=(yyvsp[(2) - (3)].nodetype);}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 376 "Parser.y"
    {(yyval.nodetype)=NULL;}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 380 "Parser.y"
    {(yyval.nodetype)=opr(PARA_DECL_LIST,2,(yyvsp[(1) - (3)].nodetype),(yyvsp[(3) - (3)].nodetype));}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 382 "Parser.y"
    {(yyval.nodetype)=(yyvsp[(1) - (1)].nodetype);}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 386 "Parser.y"
    {
					(yyval.nodetype)=opr(PARA_TYPE_LIST,2,(yyvsp[(1) - (3)].nodetype),(yyvsp[(3) - (3)].nodetype));
				}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 390 "Parser.y"
    {
					//$$=$1;
					(yyval.nodetype)=opr(PARA_TYPE_LIST,2,(yyvsp[(1) - (3)].nodetype),(yyvsp[(3) - (3)].nodetype));
				}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 397 "Parser.y"
    {(yyval.nodetype)=opr(VAR_PARA_LIST,1,(yyvsp[(2) - (2)].nodetype));}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 401 "Parser.y"
    {(yyval.nodetype)=(yyvsp[(1) - (1)].nodetype);}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 405 "Parser.y"
    {(yyval.nodetype)=(yyvsp[(1) - (1)].nodetype);}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 409 "Parser.y"
    {(yyval.nodetype)=(yyvsp[(2) - (3)].nodetype);}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 413 "Parser.y"
    {(yyval.nodetype)=opr(STMT_LIST,2,(yyvsp[(1) - (3)].nodetype),(yyvsp[(2) - (3)].nodetype));}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 415 "Parser.y"
    {(yyval.nodetype)=NULL;}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 419 "Parser.y"
    {(yyval.nodetype)=opr(COLON,2,con(&((yyvsp[(1) - (3)].iValue)),INTEGER),(yyvsp[(3) - (3)].nodetype));}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 421 "Parser.y"
    {(yyval.nodetype)=(yyvsp[(1) - (1)].nodetype);}
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 425 "Parser.y"
    {(yyval.nodetype)=(yyvsp[(1) - (1)].nodetype);}
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 427 "Parser.y"
    {(yyval.nodetype)=(yyvsp[(1) - (1)].nodetype);}
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 429 "Parser.y"
    {(yyval.nodetype)=(yyvsp[(1) - (1)].nodetype);}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 431 "Parser.y"
    {(yyval.nodetype)=(yyvsp[(1) - (1)].nodetype);}
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 433 "Parser.y"
    {(yyval.nodetype)=(yyvsp[(1) - (1)].nodetype);}
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 435 "Parser.y"
    {(yyval.nodetype)=(yyvsp[(1) - (1)].nodetype);}
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 437 "Parser.y"
    {(yyval.nodetype)=(yyvsp[(1) - (1)].nodetype);}
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 439 "Parser.y"
    {(yyval.nodetype)=(yyvsp[(1) - (1)].nodetype);}
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 441 "Parser.y"
    {(yyval.nodetype)=(yyvsp[(1) - (1)].nodetype);}
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 445 "Parser.y"
    {
					(yyval.nodetype)=opr(ASSIGN,2,id((yyvsp[(1) - (3)].sValue)),(yyvsp[(3) - (3)].nodetype));
					nodeType *check = (yyvsp[(3) - (3)].nodetype);
					//type check
					//not consider array assignment yet
					char message[100];
					nodeType *node = lookup((yyvsp[(1) - (3)].sValue));
					if(node->type == typeType){
						// REAL := REAL or INT
						if(node->tp.type == SYS_TYPE_REAL){
							//if($3->exp->type != SYS_TYPE_REAL && $3->exp->type!=SYS_TYPE_INTEGER){
							if( !(type_equal(tp(SYS_TYPE_REAL),(yyvsp[(3) - (3)].nodetype)->exp)||type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(3) - (3)].nodetype)->exp)) ){
								sprintf(message, "\"%s\" expected but \"%s\" found", type_str(node).data(), type_str((yyvsp[(3) - (3)].nodetype)->exp).data());
								type_error(message);
							}
						}
						//others
						else if(!type_equal(node,(yyvsp[(3) - (3)].nodetype)->exp)){
							sprintf(message, "\"%s\" expected but \"%s\" found", type_str(node).data(), type_str((yyvsp[(3) - (3)].nodetype)->exp).data());
							type_error(message);
						}
					}
					//function return value
					else if(node->type == typeOpr && node->opr.oper == FUNCTION_HEAD){
						//check return value
						nodeType *returnType = node->opr.op[2];
						if(!type_equal(returnType, (yyvsp[(3) - (3)].nodetype)->exp)){
							sprintf(message, "\"%s\" expected but \"%s\" found", type_str(returnType).data(), type_str((yyvsp[(3) - (3)].nodetype)->exp).data());
							type_error(message);
						}
					}
					//it is a record
					else if(node->type == typeOpr && node->opr.oper == RECORD_TYPE_DECL){
						if(!type_equal(_lookup((yyvsp[(1) - (3)].sValue)), (yyvsp[(3) - (3)].nodetype)->exp)){
							sprintf(message, "\"%s\" expected but \"%s\" found", type_str(node).data(), type_str((yyvsp[(3) - (3)].nodetype)->exp).data());
							type_error(message);
						}
					}
					else{
						sprintf(message, "Variable identifier expected");
							type_error(message);
					}
				}
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 489 "Parser.y"
    {
					(yyval.nodetype)=opr(ASSIGN,3,id((yyvsp[(1) - (6)].sValue)),(yyvsp[(3) - (6)].nodetype),(yyvsp[(6) - (6)].nodetype));
					//type check
					nodeType *check1 = (yyvsp[(3) - (6)].nodetype);
					nodeType *check2 = (yyvsp[(6) - (6)].nodetype);
					
					char message[200];
					nodeType *node = lookup((yyvsp[(1) - (6)].sValue));
					if(node->type == typeOpr && node->opr.oper == ARRAY_TYPE_DECL){
						//incompatible index type 
						if(!type_equal(node->opr.op[0], (yyvsp[(3) - (6)].nodetype)->exp)){
							sprintf(message, "incompatible index type, \"%s\" expected but \"%s\" found", type_str(node->opr.op[0]).data(), type_str((yyvsp[(3) - (6)].nodetype)->exp).data());
							type_error(message);
						}
						//incompatible element type 
						if(!type_equal(node->opr.op[1],(yyvsp[(6) - (6)].nodetype)->exp)){
							string tinfo1 = type_str(node->opr.op[1]);
							string tinfo2 = type_str((yyvsp[(6) - (6)].nodetype)->exp);
							//sprintf("incompatible element type, \"%s\" expected but \"%s\" found", type_str(node->opr.op[1]).data(), type_str($6->exp).data());
							sprintf(message, "incompatible element type, \"%s\" expected but \"%s\" found", tinfo1.data(), tinfo2.data());
							
							type_error(message);
						}
					}
					else{
						sprintf(message, "%s is not an array", (yyvsp[(1) - (6)].sValue));
						type_error(message);
					}
				}
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 519 "Parser.y"
    {

					(yyval.nodetype)=opr(ASSIGN,3,id((yyvsp[(1) - (5)].sValue)),id((yyvsp[(3) - (5)].sValue)),(yyvsp[(5) - (5)].nodetype));
					nodeType *field = check_record_access((yyvsp[(1) - (5)].sValue), (yyvsp[(3) - (5)].sValue));

					if(!type_equal(field, (yyvsp[(5) - (5)].nodetype)->exp)){
						char message[100];
						sprintf(message, "\"%s\" expected but \"%s\" found", type_str(field).data(), type_str((yyvsp[(5) - (5)].nodetype)->exp).data());
						type_error(message);
					}
					//type check
					/*char message[100];
					nodeType *node = lookup($1);
					if(node->type == typeOpr && node->opr.oper == RECORD_TYPE_DECL){
						//search given field in field_list
						nodeType *field = lookup_field_in_record($3, node);
						if(field == NULL){
							sprintf(message, "%s is not a member of %s", $3, $1);
							type_error(message);
						}
						else if(!type_equal(field, $5)){
							sprintf(message, "\"%s\" expected but \"%s\" found", type_str(field).data(), type_str($5).data());
							type_error(message);
						}
					}
					else{
						sprintf(message, "%s is not a record", $1);
						type_error(message);
					}*/

				}
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 554 "Parser.y"
    {(yyval.nodetype)=opr(PROC_STMT,1,id((yyvsp[(1) - (1)].sValue)));}
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 556 "Parser.y"
    {(yyval.nodetype)=opr(PROC_STMT,2,id((yyvsp[(1) - (4)].sValue)),(yyvsp[(3) - (4)].nodetype));}
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 558 "Parser.y"
    {(yyval.nodetype)=opr(PROC_STMT,1,sysProc((yyvsp[(1) - (1)].sysProc)));}
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 560 "Parser.y"
    {(yyval.nodetype)=opr(PROC_STMT,2,sysProc((yyvsp[(1) - (4)].sysProc)),(yyvsp[(3) - (4)].nodetype));}
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 562 "Parser.y"
    {(yyval.nodetype)=opr(READ,1,(yyvsp[(3) - (4)].nodetype));}
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 566 "Parser.y"
    {
					(yyval.nodetype)=opr(IF,3,(yyvsp[(2) - (5)].nodetype),(yyvsp[(4) - (5)].nodetype),(yyvsp[(5) - (5)].nodetype));
					//check if condition(expression) is boolean
					if(!type_equal(tp(SYS_TYPE_BOOL),(yyvsp[(2) - (5)].nodetype)->exp)){
						char message[100];
						sprintf(message, "boolean expected but \"%s\" found", type_str((yyvsp[(2) - (5)].nodetype)->exp).data());
						type_error(message);
					}
				}
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 576 "Parser.y"
    {(yyval.nodetype)=(yyvsp[(2) - (2)].nodetype);}
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 577 "Parser.y"
    {(yyval.nodetype)=NULL;}
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 580 "Parser.y"
    {
					(yyval.nodetype)=opr(REPEAT,2,(yyvsp[(2) - (4)].nodetype),(yyvsp[(4) - (4)].nodetype));
					//type check: until expression should be boolean
					if(!type_equal(tp(SYS_TYPE_BOOL), (yyvsp[(4) - (4)].nodetype)->exp)){
						char message[100];
						sprintf(message, " \"boolean\" expression expected but found \"%s\"", type_str((yyvsp[(4) - (4)].nodetype)->exp).data());
						type_error(message);
					}
				}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 592 "Parser.y"
    {
					(yyval.nodetype)=opr(WHILE,2,(yyvsp[(2) - (4)].nodetype),(yyvsp[(4) - (4)].nodetype));	
					//check while condition (expression) is boolean
					if(!type_equal(tp(SYS_TYPE_BOOL),(yyvsp[(2) - (4)].nodetype)->exp)){
						char message[100];
						sprintf(message, "boolean expected but \"%s\" found", type_str((yyvsp[(2) - (4)].nodetype)->exp).data());
						type_error(message);
					}
				}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 604 "Parser.y"
    {
					//type check:id-expression
					nodeType *node = lookup((yyvsp[(2) - (8)].sValue));

					if(!type_equal(tp(SYS_TYPE_INTEGER), node)){
						char message[100];
						sprintf(message, "\"integer\" expected but \"%s\" found", type_str(node).data());
						type_error(message);
					}

					if(!type_equal(tp(SYS_TYPE_INTEGER), (yyvsp[(4) - (8)].nodetype)->exp)){
						char message[100];
						sprintf(message, "\"integer\" expected but \"%s\" found", type_str((yyvsp[(4) - (8)].nodetype)->exp).data());
						type_error(message);
					}
					if(!type_equal(tp(SYS_TYPE_INTEGER), (yyvsp[(6) - (8)].nodetype)->exp)){
						char message[100];
						sprintf(message, "\"integer\" expected but \"%s\" found", type_str((yyvsp[(6) - (8)].nodetype)->exp).data());
						type_error(message);
					}

					(yyval.nodetype)=opr(FOR,5,id((yyvsp[(2) - (8)].sValue)),(yyvsp[(4) - (8)].nodetype),(yyvsp[(6) - (8)].nodetype),(yyvsp[(8) - (8)].nodetype));
				}
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 632 "Parser.y"
    {
					(yyval.nodetype)=opr(CASE,2,(yyvsp[(2) - (5)].nodetype),(yyvsp[(4) - (5)].nodetype));
					//type check:expression--case_expr
					if(!check_case_expression((yyvsp[(2) - (5)].nodetype)->exp, (yyvsp[(4) - (5)].nodetype))){
						type_error("Constant and CASE types do not match");
					}
				}
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 642 "Parser.y"
    {(yyval.nodetype)=opr(CASE_EXPR_LIST,2,(yyvsp[(1) - (2)].nodetype),(yyvsp[(2) - (2)].nodetype));}
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 644 "Parser.y"
    {(yyval.nodetype)=(yyvsp[(1) - (1)].nodetype);}
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 649 "Parser.y"
    {(yyval.nodetype)=opr(CASE_EXPR,2,(yyvsp[(1) - (4)].nodetype),(yyvsp[(3) - (4)].nodetype));}
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 651 "Parser.y"
    {(yyval.nodetype)=opr(CASE_EXPR,2,id((yyvsp[(1) - (4)].sValue)),(yyvsp[(3) - (4)].nodetype));}
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 655 "Parser.y"
    {(yyval.nodetype)=opr(GOTO,1,con(&((yyvsp[(2) - (2)].iValue)),INTEGER));}
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 659 "Parser.y"
    {(yyval.nodetype)=opr(EXPRESSION_LIST,2,(yyvsp[(1) - (3)].nodetype),(yyvsp[(3) - (3)].nodetype));}
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 661 "Parser.y"
    {(yyval.nodetype)=(yyvsp[(1) - (1)].nodetype);}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 665 "Parser.y"
    {
					//$$=opr(GE,2,$1,$3);
					if(( type_equal(tp(SYS_TYPE_REAL),(yyvsp[(1) - (3)].nodetype)->exp)||type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(1) - (3)].nodetype)->exp) ) 
					&& ( type_equal(tp(SYS_TYPE_REAL),(yyvsp[(3) - (3)].nodetype)->exp)||type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(3) - (3)].nodetype)->exp) )){
						nodeType* node = opr(GE, 2, (yyvsp[(1) - (3)].nodetype), (yyvsp[(3) - (3)].nodetype));
						node->exp = tp(SYS_TYPE_BOOL);
						(yyval.nodetype) = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \">=\" not supported for types \"%s\" and \"%s\"", type_str((yyvsp[(1) - (3)].nodetype)->exp).data(), type_str((yyvsp[(3) - (3)].nodetype)->exp).data());
						type_error(messgae);
					}
				}
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 680 "Parser.y"
    {
					//$$=opr(GT,2,$1,$3);
					if(( type_equal(tp(SYS_TYPE_REAL),(yyvsp[(1) - (3)].nodetype)->exp)||type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(1) - (3)].nodetype)->exp) ) 
					&& ( type_equal(tp(SYS_TYPE_REAL),(yyvsp[(3) - (3)].nodetype)->exp)||type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(3) - (3)].nodetype)->exp) )){
						nodeType* node = opr(GT, 2, (yyvsp[(1) - (3)].nodetype), (yyvsp[(3) - (3)].nodetype));
						node->exp = tp(SYS_TYPE_BOOL);
						(yyval.nodetype) = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \">\" not supported for types \"%s\" and \"%s\"", type_str((yyvsp[(1) - (3)].nodetype)->exp).data(), type_str((yyvsp[(3) - (3)].nodetype)->exp).data());
						type_error(messgae);
					}
				}
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 695 "Parser.y"
    {
					//$$=opr(LE,2,$1,$3);
					if(( type_equal(tp(SYS_TYPE_REAL),(yyvsp[(1) - (3)].nodetype)->exp)||type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(1) - (3)].nodetype)->exp) ) 
					&& ( type_equal(tp(SYS_TYPE_REAL),(yyvsp[(3) - (3)].nodetype)->exp)||type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(3) - (3)].nodetype)->exp) )){
						nodeType* node = opr(LE, 2, (yyvsp[(1) - (3)].nodetype), (yyvsp[(3) - (3)].nodetype));
						node->exp = tp(SYS_TYPE_BOOL);
						(yyval.nodetype) = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \"<=\" not supported for types \"%s\" and \"%s\"", type_str((yyvsp[(1) - (3)].nodetype)->exp).data(), type_str((yyvsp[(3) - (3)].nodetype)->exp).data());
						type_error(messgae);
					}
				}
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 710 "Parser.y"
    {
					//$$=opr(LT,2,$1,$3);
					if(( type_equal(tp(SYS_TYPE_REAL),(yyvsp[(1) - (3)].nodetype)->exp)||type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(1) - (3)].nodetype)->exp) ) 
					&& ( type_equal(tp(SYS_TYPE_REAL),(yyvsp[(3) - (3)].nodetype)->exp)||type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(3) - (3)].nodetype)->exp) )){
						nodeType* node = opr(LT, 2, (yyvsp[(1) - (3)].nodetype), (yyvsp[(3) - (3)].nodetype));
						node->exp = tp(SYS_TYPE_BOOL);
						(yyval.nodetype) = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \"<\" not supported for types \"%s\" and \"%s\"", type_str((yyvsp[(1) - (3)].nodetype)->exp).data(), type_str((yyvsp[(3) - (3)].nodetype)->exp).data());
						type_error(messgae);
					}
				}
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 725 "Parser.y"
    {
					//$$=opr(EQUAL,2,$1,$3);
					if(( type_equal(tp(SYS_TYPE_REAL),(yyvsp[(1) - (3)].nodetype)->exp)||type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(1) - (3)].nodetype)->exp) ) 
					&& ( type_equal(tp(SYS_TYPE_REAL),(yyvsp[(3) - (3)].nodetype)->exp)||type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(3) - (3)].nodetype)->exp) )){
						nodeType* node = opr(EQUAL, 2, (yyvsp[(1) - (3)].nodetype), (yyvsp[(3) - (3)].nodetype));
						node->exp = tp(SYS_TYPE_BOOL);
						(yyval.nodetype) = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \"==\" not supported for types \"%s\" and \"%s\"", type_str((yyvsp[(1) - (3)].nodetype)->exp).data(), type_str((yyvsp[(3) - (3)].nodetype)->exp).data());
						type_error(messgae);
					}
				}
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 740 "Parser.y"
    {
					//$$=opr(UNEQUAL,2,$1,$3);
					if(( type_equal(tp(SYS_TYPE_REAL),(yyvsp[(1) - (3)].nodetype)->exp)||type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(1) - (3)].nodetype)->exp) ) 
					&& ( type_equal(tp(SYS_TYPE_REAL),(yyvsp[(3) - (3)].nodetype)->exp)||type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(3) - (3)].nodetype)->exp) )){
						nodeType* node = opr(UNEQUAL, 2, (yyvsp[(1) - (3)].nodetype), (yyvsp[(3) - (3)].nodetype));
						node->exp = tp(SYS_TYPE_BOOL);
						(yyval.nodetype) = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \"!=\" not supported for types \"%s\" and \"%s\"", type_str((yyvsp[(1) - (3)].nodetype)->exp).data(), type_str((yyvsp[(3) - (3)].nodetype)->exp).data());
						type_error(messgae);
					}
				}
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 755 "Parser.y"
    {(yyval.nodetype)=(yyvsp[(1) - (1)].nodetype);}
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 759 "Parser.y"
    {
					//$$=opr(PLUS,2,$1,$3);
					nodeType *check1 = (yyvsp[(1) - (3)].nodetype);
					nodeType *check2 = (yyvsp[(3) - (3)].nodetype);

					if(( type_equal(tp(SYS_TYPE_REAL),(yyvsp[(1) - (3)].nodetype)->exp)||type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(1) - (3)].nodetype)->exp) ) 
					&& ( type_equal(tp(SYS_TYPE_REAL),(yyvsp[(3) - (3)].nodetype)->exp)||type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(3) - (3)].nodetype)->exp) )){
						nodeType* node = opr(PLUS, 2, (yyvsp[(1) - (3)].nodetype), (yyvsp[(3) - (3)].nodetype));
						//both integer, result is integer
						if(type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(1) - (3)].nodetype)->exp) && type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(3) - (3)].nodetype)->exp))
							node->exp = tp(SYS_TYPE_INTEGER);
						//one of them is real, result should be real
						else
							node->exp = tp(SYS_TYPE_REAL);
						(yyval.nodetype) = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \"plus\" not supported for types \"%s\" and \"%s\"", type_str((yyvsp[(1) - (3)].nodetype)->exp).data(), type_str((yyvsp[(3) - (3)].nodetype)->exp).data());
						type_error(messgae);
					}
				}
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 782 "Parser.y"
    {
					//$$=opr(MINUS,2,$1,$3);
					if(( type_equal(tp(SYS_TYPE_REAL),(yyvsp[(1) - (3)].nodetype)->exp)||type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(1) - (3)].nodetype)->exp) ) 
					&& ( type_equal(tp(SYS_TYPE_REAL),(yyvsp[(3) - (3)].nodetype)->exp)||type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(3) - (3)].nodetype)->exp) )){
						nodeType* node = opr(MINUS, 2, (yyvsp[(1) - (3)].nodetype), (yyvsp[(3) - (3)].nodetype));
						//both integer, result is integer
						if(type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(1) - (3)].nodetype)->exp) && type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(3) - (3)].nodetype)->exp))
							node->exp = tp(SYS_TYPE_INTEGER);
						//one of them is real, result should be real
						else
							node->exp = tp(SYS_TYPE_REAL);
						(yyval.nodetype) = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \"minus\" not supported for types \"%s\" and \"%s\"", type_str((yyvsp[(1) - (3)].nodetype)->exp).data(), type_str((yyvsp[(3) - (3)].nodetype)->exp).data());
						type_error(messgae);
					}
				}
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 802 "Parser.y"
    {
					//$$=opr(OR,2,$1,$3);
					nodeType *check1 = (yyvsp[(1) - (3)].nodetype);
					nodeType *check2 = (yyvsp[(3) - (3)].nodetype);
					if(type_equal(tp(SYS_TYPE_BOOL),(yyvsp[(1) - (3)].nodetype)->exp) && type_equal(tp(SYS_TYPE_BOOL),(yyvsp[(3) - (3)].nodetype)->exp)){
						nodeType* node = opr(OR, 2, (yyvsp[(1) - (3)].nodetype), (yyvsp[(3) - (3)].nodetype));
						node->exp = tp(SYS_TYPE_BOOL);
						(yyval.nodetype) = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \"or\" not supported for types \"%s\" and \"%s\"", type_str((yyvsp[(1) - (3)].nodetype)->exp).data(), type_str((yyvsp[(3) - (3)].nodetype)->exp).data());
						type_error(messgae);
					}
				}
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 818 "Parser.y"
    {
					(yyval.nodetype)=(yyvsp[(1) - (1)].nodetype);
				}
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 824 "Parser.y"
    {
					//$$=opr(MUL,2,$1,$3);
					if(( type_equal(tp(SYS_TYPE_REAL),(yyvsp[(1) - (3)].nodetype)->exp)||type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(1) - (3)].nodetype)->exp) ) 
					&& ( type_equal(tp(SYS_TYPE_REAL),(yyvsp[(3) - (3)].nodetype)->exp)||type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(3) - (3)].nodetype)->exp) )){
						nodeType* node = opr(MUL, 2, (yyvsp[(1) - (3)].nodetype), (yyvsp[(3) - (3)].nodetype));
						//both integer, result is integer
						if(type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(1) - (3)].nodetype)->exp) && type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(3) - (3)].nodetype)->exp))
							node->exp = tp(SYS_TYPE_INTEGER);
						//one of them is real, result should be real
						else
							node->exp = tp(SYS_TYPE_REAL);
						(yyval.nodetype) = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \"mul\" not supported for types \"%s\" and \"%s\"", type_str((yyvsp[(1) - (3)].nodetype)->exp).data(), type_str((yyvsp[(3) - (3)].nodetype)->exp).data());
						type_error(messgae);
					}
				}
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 844 "Parser.y"
    {
					//$$=opr(DIV,2,$1,$3);
					if(( type_equal(tp(SYS_TYPE_REAL),(yyvsp[(1) - (3)].nodetype)->exp)||type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(1) - (3)].nodetype)->exp) ) 
					&& ( type_equal(tp(SYS_TYPE_REAL),(yyvsp[(3) - (3)].nodetype)->exp)||type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(3) - (3)].nodetype)->exp) )){
						nodeType* node = opr(DIV, 2, (yyvsp[(1) - (3)].nodetype), (yyvsp[(3) - (3)].nodetype));
						//both integer, result is integer
						if(type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(1) - (3)].nodetype)->exp) && type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(3) - (3)].nodetype)->exp))
							node->exp = tp(SYS_TYPE_INTEGER);
						//one of them is real, result should be real
						else
							node->exp = tp(SYS_TYPE_REAL);
						(yyval.nodetype) = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \"div\" not supported for types \"%s\" and \"%s\"", type_str((yyvsp[(1) - (3)].nodetype)->exp).data(), type_str((yyvsp[(3) - (3)].nodetype)->exp).data());
						type_error(messgae);
					}
				}
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 864 "Parser.y"
    {
					//$$=opr(MOD,2,$1,$3);
					if(type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(1) - (3)].nodetype)->exp) && type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(3) - (3)].nodetype)->exp)){
						nodeType* node = opr(MOD, 2, (yyvsp[(1) - (3)].nodetype), (yyvsp[(3) - (3)].nodetype));
						node->exp = tp(SYS_TYPE_INTEGER);
						(yyval.nodetype) = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \"mod\" not supported for types \"%s\" and \"%s\"", type_str((yyvsp[(1) - (3)].nodetype)->exp).data(), type_str((yyvsp[(3) - (3)].nodetype)->exp).data());
						type_error(messgae);
					}
				}
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 878 "Parser.y"
    {
					//$$=opr(AND,2,$1,$3);
					//if($1->exp->tp.type == SYS_TYPE_BOOL && $3->exp->tp.type == SYS_TYPE_BOOL){
					if(type_equal(tp(SYS_TYPE_BOOL),(yyvsp[(1) - (3)].nodetype)->exp) && type_equal(tp(SYS_TYPE_BOOL),(yyvsp[(3) - (3)].nodetype)->exp)){
						nodeType* node = opr(AND, 2, (yyvsp[(1) - (3)].nodetype), (yyvsp[(3) - (3)].nodetype));
						node->exp = tp(SYS_TYPE_BOOL);
						(yyval.nodetype) = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \"and\" not supported for types \"%s\" and \"%s\"", type_str((yyvsp[(1) - (3)].nodetype)->exp).data(), type_str((yyvsp[(3) - (3)].nodetype)->exp).data());
						type_error(messgae);
					}
				}
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 893 "Parser.y"
    {
					(yyval.nodetype)=(yyvsp[(1) - (1)].nodetype);
				}
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 899 "Parser.y"
    {
					//$$=id($1);
					nodeType *node = id((yyvsp[(1) - (1)].sValue));
					nodeType *refer = lookup((yyvsp[(1) - (1)].sValue));
					node->exp = refer;
					//if it is function
					if(refer->type==typeOpr && refer->opr.oper == FUNCTION_HEAD){
						//this function should not have any parameters
						nodeType* parameters = refer->opr.op[1];
						if(parameters!=NULL){
							char messgae[100];
							sprintf(messgae, "no parameters found for function %s", (yyvsp[(1) - (1)].sValue));
							type_error(messgae);
						}
						else{
							//return type
							node->exp = refer->opr.op[2];
						}
					}
					(yyval.nodetype)=node;
				}
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 921 "Parser.y"
    {
					//$$=opr(LP,2,$1,$3);
					nodeType *node = opr(LP, 2, (yyvsp[(1) - (4)].sValue), (yyvsp[(3) - (4)].nodetype));
					nodeType *refer = lookup((yyvsp[(1) - (4)].sValue));
					if(refer->type==typeOpr && refer->opr.oper == FUNCTION_HEAD){
						//check parameters!!!
						check_parameters(refer, (yyvsp[(3) - (4)].nodetype));
					}
					else{
						//not a function/procedure
						char message[100];
						sprintf(message, "\"function\" expected but \"%s\" found", type_str(node).data());
						type_error(message);
					}
					node->exp = refer->opr.op[2];//return type
					(yyval.nodetype)=node;
				}
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 939 "Parser.y"
    {
					//$$=sysFunc($1);
					nodeType *node=sysFunc((yyvsp[(1) - (1)].sysFunc));
					node->exp = node;
					(yyval.nodetype) = node;
				}
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 946 "Parser.y"
    {
					//$$=opr(SYS_FUNCT,2,$1,$3);
					//..never check input type now
					nodeType *node=sysFunc((yyvsp[(1) - (4)].sysFunc));
					switch((yyvsp[(1) - (4)].sysFunc)){
						case SYS_FUNCT_ABS:{
							node->exp=tp(SYS_TYPE_INTEGER);
							break;
						}
						case SYS_FUNCT_CHR:{
							node->exp=tp(SYS_TYPE_CHAR);
							break;
						}
						case SYS_FUNCT_ODD:{
							node->exp=tp(SYS_TYPE_BOOL);
							break;
						}
						case SYS_FUNCT_ORD:{
							//..need to be done
							node->exp=tp(SYS_TYPE_INTEGER);
							break;
						}
						case SYS_FUNCT_PRED:{
							node->exp=tp(SYS_TYPE_INTEGER);
							break;
						}
						case SYS_FUNCT_SQR:{
							node->exp=tp(SYS_TYPE_REAL);
							break;
						}
						case SYS_FUNCT_SQRT:{
							node->exp=tp(SYS_TYPE_REAL);
							break;
						}
						case SYS_FUNCT_SUCC:{
							node->exp=tp(SYS_TYPE_INTEGER);
							break;
						}
					}
					(yyval.nodetype) = node;
				}
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 988 "Parser.y"
    {
					//$$=$1;
					nodeType *node = (yyvsp[(1) - (1)].nodetype);
					node->exp = (yyvsp[(1) - (1)].nodetype);
					(yyval.nodetype) = node;
				}
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 995 "Parser.y"
    {
					(yyval.nodetype)=(yyvsp[(2) - (3)].nodetype);
				}
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 999 "Parser.y"
    {
					//$$=opr(NOT,1,$2);
					//check_not_exp($2->exp);
					if(type_equal(tp(SYS_TYPE_BOOL),(yyvsp[(2) - (2)].nodetype)->exp)){
						nodeType *node = opr(NOT, 1, (yyvsp[(2) - (2)].nodetype));
						node->exp = (yyvsp[(2) - (2)].nodetype)->exp;
						(yyval.nodetype) = node;						
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \"not\" not supported for type \"%s\" ", type_str((yyvsp[(2) - (2)].nodetype)->exp).data());
						type_error(messgae);
					}
				}
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 1014 "Parser.y"
    {
					//$$=opr(MINUS,1,$2);
					//check_minus_exp($2->exp);
					if(type_equal(tp(SYS_TYPE_REAL),(yyvsp[(2) - (2)].nodetype)->exp)||type_equal(tp(SYS_TYPE_INTEGER),(yyvsp[(2) - (2)].nodetype)->exp) ){
						nodeType* node = opr(MINUS, 1, (yyvsp[(2) - (2)].nodetype));
						node->exp = (yyvsp[(2) - (2)].nodetype)->exp;
						(yyval.nodetype) = node;
					}
					else{
						char messgae[100];
						sprintf(messgae, "Operation \"minus\" not supported for type \"%s\" ", type_str((yyvsp[(2) - (2)].nodetype)->exp).data());
						type_error(messgae);
					}
				}
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 1029 "Parser.y"
    {
					//access array
					//$$=opr(LB,2,id($1),$3);
					nodeType* node = opr(LB,2,id((yyvsp[(1) - (4)].sValue)), (yyvsp[(3) - (4)].nodetype));
					nodeType*element = check_array_access((yyvsp[(1) - (4)].sValue),(yyvsp[(3) - (4)].nodetype)->exp);
					node->exp = element;
					(yyval.nodetype) = node;
				}
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 1038 "Parser.y"
    {
					//$$=opr(DOT,2,id($1),id($3));
					//access record
					nodeType *node = opr(DOT,2,id((yyvsp[(1) - (3)].sValue)),id((yyvsp[(3) - (3)].sValue)));
					nodeType *field = check_record_access((yyvsp[(1) - (3)].sValue), (yyvsp[(3) - (3)].sValue));
					node->exp = field;
					(yyval.nodetype) = node;
				}
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 1049 "Parser.y"
    {(yyval.nodetype)=opr(ARGS_LIST,2,(yyvsp[(1) - (3)].nodetype),(yyvsp[(3) - (3)].nodetype));}
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 1051 "Parser.y"
    {(yyval.nodetype)=(yyvsp[(1) - (1)].nodetype);}
    break;


/* Line 1792 of yacc.c  */
#line 3177 "Parser.cpp"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 1055 "Parser.y"




//hdj: symbol table

//symbol table end

nodeType *con(void* value,int type) {
	nodeType *p;

	/* allocate node */
	if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
		yyerror("out of memory");

	/* copy information */
	p->type = typeCon;
	p->con.type = type;
	if(type == REAL){
		p->con.real=*((double*)value);
	}else if(type == INTEGER){
		p->con.integer=*((int*)value);
	}else if(type == STRING){
		p->con.str = (char*)value;
	}else if(type == CHAR){
		p->con.character = *((char*)value);
	}else if(type == BOOL){
		p->con.boolean = *((int*)value);
	}

	return p;
}

nodeType *id(char * name) {
	nodeType *p;

	if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
		yyerror("out of memory");

	p->type = typeId;
	p->id.sValue = (char *)malloc(strlen(name)+1);
	strcpy(p->id.sValue, name);

	return p;
}

nodeType *tp(int i) {
	nodeType *p;

	/* allocate node */
	if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
		yyerror("out of memory");

	/* copy information */
	p->type = typeType;
	p->tp.type = i;

	return p;
}

nodeType *sysProc(int i) {
	nodeType *p;

	
	if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
		yyerror("out of memory");


	p->type = typeSysProc;
	p->sysProc.name = i;

	return p;
}


nodeType *sysFunc(int i) {
	nodeType *p;


	if ((p = (nodeType*)malloc(sizeof(nodeType))) == NULL)
		yyerror("out of memory");


	p->type = typeSysFunc;
	p->sysFunc.name = i;

	return p;
}

nodeType *opr(int oper, int nops, ...) {
	va_list ap;
	nodeType *p;
	int i;

	/* allocate node, extending op array */
	if ((p = (nodeType*)malloc(sizeof(nodeType) + (nops-1) * sizeof(nodeType* ))) == NULL)
		yyerror("out of memory");

	/* copy information */
	p->type = typeOpr;
	p->opr.oper = oper;
	p->opr.nops = nops;
	va_start(ap, nops);
	for (i = 0; i < nops; i++)
		p->opr.op[i] = va_arg(ap, nodeType*);
	va_end(ap);
	return p;
}

void freeNode(nodeType *p) {
	int i;

	if (!p) return;
	if (p->type == typeOpr) {
		for (i = 0; i < p->opr.nops; i++)
			freeNode(p->opr.op[i]);
	}
	free (p);
}
void yyerror(char *s) {
	fprintf(stdout, "%s\n", s);
}

int main(int argc, char *argv[]) {

	yyparse();
	//printf("Number of  pairs of BEGIN and END: %d\n", count);
	return 0;
}
