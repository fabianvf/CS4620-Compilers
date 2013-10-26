/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 12 "parser.y"


/* Just like lex, the text within this first region delimited by %{ and %}
 * is assumed to be C/C++ code and will be copied verbatim to the y.tab.c
 * file ahead of the definitions of the yyparse() function. Add other header
 * file inclusions or C++ variable declarations/prototypes that are needed
 * by your code here.
 */
#include "scanner.h" // for yylex
#include "parser.h"
#include "errors.h"

void yyerror(const char *msg); // standard error-handling routine



/* Line 268 of yacc.c  */
#line 88 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_Void = 258,
     T_Bool = 259,
     T_Int = 260,
     T_Double = 261,
     T_String = 262,
     T_Class = 263,
     T_LessEqual = 264,
     T_GreaterEqual = 265,
     T_Equal = 266,
     T_NotEqual = 267,
     T_Dims = 268,
     T_And = 269,
     T_Or = 270,
     T_Null = 271,
     T_Extends = 272,
     T_This = 273,
     T_Interface = 274,
     T_Implements = 275,
     T_While = 276,
     T_For = 277,
     T_If = 278,
     T_Else = 279,
     T_Return = 280,
     T_Break = 281,
     T_New = 282,
     T_NewArray = 283,
     T_Print = 284,
     T_ReadInteger = 285,
     T_ReadLine = 286,
     T_Switch = 287,
     T_Case = 288,
     T_Default = 289,
     T_Identifier = 290,
     T_StringConstant = 291,
     T_IntConstant = 292,
     T_DoubleConstant = 293,
     T_BoolConstant = 294,
     LTELSE = 295,
     UNARY = 296
   };
#endif
/* Tokens.  */
#define T_Void 258
#define T_Bool 259
#define T_Int 260
#define T_Double 261
#define T_String 262
#define T_Class 263
#define T_LessEqual 264
#define T_GreaterEqual 265
#define T_Equal 266
#define T_NotEqual 267
#define T_Dims 268
#define T_And 269
#define T_Or 270
#define T_Null 271
#define T_Extends 272
#define T_This 273
#define T_Interface 274
#define T_Implements 275
#define T_While 276
#define T_For 277
#define T_If 278
#define T_Else 279
#define T_Return 280
#define T_Break 281
#define T_New 282
#define T_NewArray 283
#define T_Print 284
#define T_ReadInteger 285
#define T_ReadLine 286
#define T_Switch 287
#define T_Case 288
#define T_Default 289
#define T_Identifier 290
#define T_StringConstant 291
#define T_IntConstant 292
#define T_DoubleConstant 293
#define T_BoolConstant 294
#define LTELSE 295
#define UNARY 296




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 43 "parser.y"

    int integerConstant;
    bool boolConstant;
    char *stringConstant;
    double doubleConstant;
    char identifier[MaxIdentLen+1]; // +1 for terminating null
    Decl *decl;
    VarDecl *var;
    FnDecl *fDecl;
    ClassDecl *cDecl;
    InterfaceDecl *iDecl;
    Type *type;
    Stmt *stmt;
    Expr *expr;
    NamedType *namedtype;
    List<NamedType*> *ntypeList;
    List<Stmt*> *stmtList;
    List<VarDecl*> *varList;
    List<Decl*> *declList;
    List<Expr*> *exprList;
    List<Case*> *cases;



/* Line 293 of yacc.c  */
#line 231 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 256 "y.tab.c"

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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
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
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  22
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   515

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  105
/* YYNRULES -- Number of states.  */
#define YYNSTATES  215

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   296

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,     2,     2,     2,    48,     2,     2,
      51,    56,    47,    44,    58,    45,    50,    46,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    59,    57,
      42,    41,    43,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    52,     2,    60,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    54,     2,    55,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    53
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    16,    18,
      24,    25,    28,    35,    42,    50,    53,    54,    55,    58,
      60,    62,    63,    67,    72,    75,    78,    80,    82,    84,
      86,    88,    91,    94,   100,   106,   108,   109,   113,   115,
     120,   123,   124,   125,   128,   131,   133,   135,   137,   139,
     141,   143,   145,   147,   148,   150,   156,   164,   170,   180,
     184,   187,   193,   201,   207,   214,   219,   222,   226,   228,
     230,   231,   235,   237,   239,   241,   243,   247,   251,   255,
     259,   263,   267,   270,   274,   278,   282,   286,   290,   294,
     298,   302,   305,   309,   313,   318,   325,   327,   331,   336,
     341,   348,   350,   352,   354,   356
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      62,     0,    -1,    63,    -1,    63,    64,    -1,    64,    -1,
      73,    -1,    76,    -1,    68,    -1,    65,    -1,    19,    35,
      54,    66,    55,    -1,    -1,    66,    67,    -1,    75,    35,
      51,    78,    56,    57,    -1,     3,    35,    51,    78,    56,
      57,    -1,     8,    35,    69,    72,    54,    70,    55,    -1,
      17,    35,    -1,    -1,    -1,    70,    71,    -1,    73,    -1,
      76,    -1,    -1,    20,    35,    72,    -1,    58,    20,    35,
      72,    -1,    74,    57,    -1,    75,    35,    -1,     5,    -1,
       4,    -1,     7,    -1,     6,    -1,    35,    -1,    75,    13,
      -1,    77,    80,    -1,    75,    35,    51,    78,    56,    -1,
       3,    35,    51,    78,    56,    -1,    79,    -1,    -1,    79,
      58,    74,    -1,    74,    -1,    54,    81,    82,    55,    -1,
      81,    73,    -1,    -1,    -1,    83,    82,    -1,    84,    57,
      -1,    85,    -1,    86,    -1,    87,    -1,    89,    -1,    88,
      -1,    90,    -1,    91,    -1,    80,    -1,    -1,    96,    -1,
      23,    51,    96,    56,    83,    -1,    23,    51,    96,    56,
      83,    24,    83,    -1,    21,    51,    96,    56,    83,    -1,
      22,    51,    84,    57,    96,    57,    84,    56,    83,    -1,
      25,    84,    57,    -1,    26,    57,    -1,    29,    51,    94,
      56,    57,    -1,    32,    51,    96,    56,    54,    92,    55,
      -1,    33,    37,    59,    82,    92,    -1,    33,    37,    59,
      82,    93,    57,    -1,    33,    37,    59,    82,    -1,    34,
      82,    -1,    94,    58,    96,    -1,    96,    -1,    94,    -1,
      -1,    97,    41,    96,    -1,    99,    -1,    97,    -1,    18,
      -1,    98,    -1,    51,    96,    56,    -1,    96,    44,    96,
      -1,    96,    45,    96,    -1,    96,    47,    96,    -1,    96,
      46,    96,    -1,    96,    48,    96,    -1,    45,    96,    -1,
      96,    42,    96,    -1,    96,     9,    96,    -1,    96,    43,
      96,    -1,    96,    10,    96,    -1,    96,    11,    96,    -1,
      96,    12,    96,    -1,    96,    14,    96,    -1,    96,    15,
      96,    -1,    49,    96,    -1,    30,    51,    56,    -1,    31,
      51,    56,    -1,    27,    51,    35,    56,    -1,    28,    51,
      96,    58,    75,    56,    -1,    35,    -1,    96,    50,    35,
      -1,    96,    52,    96,    60,    -1,    35,    51,    95,    56,
      -1,    96,    50,    35,    51,    95,    56,    -1,    37,    -1,
      38,    -1,    39,    -1,    36,    -1,    16,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   137,   137,   147,   148,   150,   151,   152,   153,   156,
     158,   159,   162,   163,   165,   167,   168,   170,   171,   173,
     174,   176,   177,   178,   181,   184,   187,   188,   189,   190,
     191,   192,   195,   198,   200,   204,   205,   208,   210,   213,
     217,   218,   221,   222,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   235,   236,   239,   240,   244,   247,   250,
     253,   256,   259,   262,   263,   264,   267,   270,   271,   274,
     275,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   305,   306,   307,   309,
     310,   315,   316,   317,   318,   319
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_Void", "T_Bool", "T_Int", "T_Double",
  "T_String", "T_Class", "T_LessEqual", "T_GreaterEqual", "T_Equal",
  "T_NotEqual", "T_Dims", "T_And", "T_Or", "T_Null", "T_Extends", "T_This",
  "T_Interface", "T_Implements", "T_While", "T_For", "T_If", "T_Else",
  "T_Return", "T_Break", "T_New", "T_NewArray", "T_Print", "T_ReadInteger",
  "T_ReadLine", "T_Switch", "T_Case", "T_Default", "T_Identifier",
  "T_StringConstant", "T_IntConstant", "T_DoubleConstant",
  "T_BoolConstant", "LTELSE", "'='", "'<'", "'>'", "'+'", "'-'", "'/'",
  "'*'", "'%'", "'!'", "'.'", "'('", "'['", "UNARY", "'{'", "'}'", "')'",
  "';'", "','", "':'", "']'", "$accept", "Program", "DeclList", "Decl",
  "InterfaceDecl", "ProtoList", "Prototype", "ClassDecl", "PeExtend",
  "Fields", "Field", "ImplList", "VarDecl", "Variable", "Type", "FnDecl",
  "FnHeader", "Formals", "FormalList", "StmtBlock", "VarDecls", "StmtList",
  "Stmt", "PeExpr", "IfStmt", "WhileStmt", "ForStmt", "ReturnStmt",
  "BreakStmt", "PrintStmt", "SwitchStmt", "Cases", "Default", "NeExprList",
  "ExprList", "Expr", "LValue", "Call", "Constant", 0
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
     295,    61,    60,    62,    43,    45,    47,    42,    37,    33,
      46,    40,    91,   296,   123,   125,    41,    59,    44,    58,
      93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    61,    62,    63,    63,    64,    64,    64,    64,    65,
      66,    66,    67,    67,    68,    69,    69,    70,    70,    71,
      71,    72,    72,    72,    73,    74,    75,    75,    75,    75,
      75,    75,    76,    77,    77,    78,    78,    79,    79,    80,
      81,    81,    82,    82,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    84,    84,    85,    85,    86,    87,    88,
      89,    90,    91,    92,    92,    92,    93,    94,    94,    95,
      95,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    97,    97,    97,    98,
      98,    99,    99,    99,    99,    99
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     5,
       0,     2,     6,     6,     7,     2,     0,     0,     2,     1,
       1,     0,     3,     4,     2,     2,     1,     1,     1,     1,
       1,     2,     2,     5,     5,     1,     0,     3,     1,     4,
       2,     0,     0,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     1,     5,     7,     5,     9,     3,
       2,     5,     7,     5,     6,     4,     2,     3,     1,     1,
       0,     3,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     3,     3,     4,     6,     1,     3,     4,     4,
       6,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    27,    26,    29,    28,     0,     0,    30,     0,
       2,     4,     8,     7,     5,     0,     0,     6,     0,     0,
      16,     0,     1,     3,    24,    31,    25,    41,    32,    36,
       0,    21,    10,    36,    42,    38,     0,     0,    35,    15,
       0,     0,     0,     0,     0,   105,    74,     0,     0,     0,
      53,     0,     0,     0,     0,     0,     0,     0,    96,   104,
     101,   102,   103,     0,     0,     0,    40,    52,     0,    42,
       0,    45,    46,    47,    49,    48,    50,    51,    54,    73,
      75,    72,    25,    34,     0,    21,     0,    17,     0,     9,
      11,     0,    33,     0,    53,     0,    96,     0,    60,     0,
       0,     0,     0,     0,     0,    70,    82,    91,     0,    39,
      43,    44,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    37,    22,
      21,     0,     0,     0,     0,     0,     0,    59,     0,     0,
       0,    68,    92,    93,     0,    69,     0,    76,    84,    86,
      87,    88,    89,    90,    83,    85,    77,    78,    80,    79,
      81,    97,     0,    71,    23,    14,    18,    19,    20,    36,
      36,    53,     0,    53,    94,     0,     0,     0,     0,    99,
      70,    98,     0,     0,    57,     0,    55,     0,    61,    67,
       0,     0,     0,     0,    53,    53,    95,     0,     0,   100,
      13,    12,     0,    56,     0,    62,    53,    42,    58,    65,
      42,    63,     0,    66,    64
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    10,    11,    12,    43,    90,    13,    31,   131,
     166,    42,    14,    15,    36,    17,    18,    37,    38,    67,
      34,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,   198,   212,   145,   146,    78,    79,    80,    81
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -156
static const yytype_int16 yypact[] =
{
     252,    24,  -156,  -156,  -156,  -156,    25,    39,  -156,    35,
     252,  -156,  -156,  -156,  -156,    20,     2,  -156,    31,    28,
      69,    33,  -156,  -156,  -156,  -156,    48,  -156,  -156,    98,
      65,   -12,  -156,    98,   133,  -156,     4,    52,    53,  -156,
      78,    99,    66,    23,    67,  -156,  -156,    71,    74,    76,
      79,    89,    83,    84,    85,   101,   102,   106,    -4,  -156,
    -156,  -156,  -156,    79,    79,    79,  -156,  -156,    95,   461,
     109,  -156,  -156,  -156,  -156,  -156,  -156,  -156,   380,   126,
    -156,  -156,  -156,  -156,    98,   -12,   138,  -156,   139,  -156,
    -156,     6,  -156,    79,    79,    79,   125,   120,  -156,   144,
      79,    79,   124,   127,    79,    79,  -156,   -29,   254,  -156,
    -156,  -156,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,   146,    79,    79,  -156,  -156,
     -12,    77,   134,   135,   302,   131,   317,  -156,   142,   193,
     -36,   380,  -156,  -156,   365,   137,   143,  -156,   165,   165,
      46,    46,   391,   391,   165,   165,   -14,   -14,   -29,   -29,
     -29,   149,   182,   380,  -156,  -156,  -156,  -156,  -156,    98,
      98,   461,    79,   461,  -156,    98,   132,    79,   147,  -156,
      79,  -156,   150,   158,  -156,   238,   192,    -8,  -156,   380,
     185,   163,   164,   166,    79,   461,  -156,   183,   167,  -156,
    -156,  -156,   175,  -156,   174,  -156,   461,   424,  -156,    -9,
     461,  -156,   187,  -156,  -156
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -156,  -156,  -156,   236,  -156,  -156,  -156,  -156,  -156,  -156,
    -156,   -78,   -30,   -27,     0,   123,  -156,   -22,  -156,   243,
    -156,   -66,  -155,   -49,  -156,  -156,  -156,  -156,  -156,  -156,
    -156,    58,  -156,   161,    90,   -51,  -156,  -156,  -156
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -54
static const yytype_int16 yytable[] =
{
      16,    97,    35,   110,    66,    25,    35,   129,    40,   -30,
      16,    44,   106,   107,   108,    25,   184,    25,   186,    25,
     176,   125,   177,   126,   197,   210,    88,     2,     3,     4,
       5,   -30,   122,   123,   124,    22,   125,    26,   126,    82,
     203,   133,   134,    91,   136,   135,    41,   105,   196,   139,
     141,   208,   164,   144,   141,   112,   113,   128,     8,    19,
      20,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,    21,   162,   163,    24,    89,    29,
       1,     2,     3,     4,     5,    27,    30,    32,   118,   119,
     120,   121,   122,   123,   124,    45,   125,    46,   126,    33,
      39,   167,     2,     3,     4,     5,    52,    53,    83,    55,
      56,    84,     8,    85,    96,    59,    60,    61,    62,    86,
      87,   185,    93,    92,    63,    94,   189,    95,    64,   141,
      65,    16,   165,     8,    99,   100,   101,     2,     3,     4,
       5,   209,    35,    35,   213,   202,    98,   182,   183,    45,
     109,    46,   102,   103,    47,    48,    49,   104,    50,    51,
      52,    53,    54,    55,    56,    57,   111,   127,    58,    59,
      60,    61,    62,   130,   132,   187,   105,   137,    63,   138,
     142,   161,    64,   143,    65,   169,   170,    27,   172,   188,
     -53,   112,   113,   114,   115,   177,   116,   117,   174,   179,
     180,   190,   112,   113,   114,   115,   192,   116,   117,   120,
     121,   122,   123,   124,   193,   125,   195,   126,   197,   199,
     204,   200,   205,   201,   118,   119,   120,   121,   122,   123,
     124,   206,   125,   207,   126,   118,   119,   120,   121,   122,
     123,   124,   181,   125,   214,   126,    23,   112,   113,   114,
     115,   175,   116,   117,   168,     1,     2,     3,     4,     5,
       6,    28,   140,   112,   113,   114,   115,   211,   116,   117,
     191,     7,     0,     0,     0,     0,     0,     0,     0,     0,
     118,   119,   120,   121,   122,   123,   124,     8,   125,     0,
     126,     0,     0,     0,     0,   194,   118,   119,   120,   121,
     122,   123,   124,     0,   125,     0,   126,     0,     0,     0,
     147,   112,   113,   114,   115,     0,   116,   117,     0,     0,
       0,     0,     0,     0,     0,     0,   112,   113,   114,   115,
       0,   116,   117,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   118,   119,   120,   121,   122,   123,
     124,     0,   125,     0,   126,     0,     0,     0,   171,   118,
     119,   120,   121,   122,   123,   124,     0,   125,     0,   126,
       0,     0,     0,   173,   112,   113,   114,   115,     0,   116,
     117,     0,     0,     0,     0,     0,     0,     0,     0,   112,
     113,   114,   115,     0,   116,   117,     0,     0,     0,     0,
     112,   113,   114,   115,     0,     0,     0,   118,   119,   120,
     121,   122,   123,   124,     0,   125,     0,   126,     0,     0,
       0,   178,   118,   119,   120,   121,   122,   123,   124,     0,
     125,     0,   126,   118,   119,   120,   121,   122,   123,   124,
      45,   125,    46,   126,     0,    47,    48,    49,     0,    50,
      51,    52,    53,    54,    55,    56,    57,     0,     0,    96,
      59,    60,    61,    62,     0,     0,     0,     0,     0,    63,
       0,     0,     0,    64,     0,    65,     0,    45,    27,    46,
       0,   -53,    47,    48,    49,     0,    50,    51,    52,    53,
      54,    55,    56,    57,     0,     0,    96,    59,    60,    61,
      62,     0,     0,     0,     0,     0,    63,     0,     0,     0,
      64,     0,    65,     0,     0,    27
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-156))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       0,    50,    29,    69,    34,    13,    33,    85,    20,    13,
      10,    33,    63,    64,    65,    13,   171,    13,   173,    13,
      56,    50,    58,    52,    33,    34,     3,     4,     5,     6,
       7,    35,    46,    47,    48,     0,    50,    35,    52,    35,
     195,    35,    93,    43,    95,    94,    58,    51,    56,   100,
     101,   206,   130,   104,   105,     9,    10,    84,    35,    35,
      35,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,    35,   126,   127,    57,    55,    51,
       3,     4,     5,     6,     7,    54,    17,    54,    42,    43,
      44,    45,    46,    47,    48,    16,    50,    18,    52,    51,
      35,   131,     4,     5,     6,     7,    27,    28,    56,    30,
      31,    58,    35,    35,    35,    36,    37,    38,    39,    20,
      54,   172,    51,    56,    45,    51,   177,    51,    49,   180,
      51,   131,    55,    35,    51,    51,    51,     4,     5,     6,
       7,   207,   169,   170,   210,   194,    57,   169,   170,    16,
      55,    18,    51,    51,    21,    22,    23,    51,    25,    26,
      27,    28,    29,    30,    31,    32,    57,    41,    35,    36,
      37,    38,    39,    35,    35,   175,    51,    57,    45,    35,
      56,    35,    49,    56,    51,    51,    51,    54,    57,    57,
      57,     9,    10,    11,    12,    58,    14,    15,    56,    56,
      51,    54,     9,    10,    11,    12,    56,    14,    15,    44,
      45,    46,    47,    48,    56,    50,    24,    52,    33,    56,
      37,    57,    55,    57,    42,    43,    44,    45,    46,    47,
      48,    56,    50,    59,    52,    42,    43,    44,    45,    46,
      47,    48,    60,    50,    57,    52,    10,     9,    10,    11,
      12,    58,    14,    15,   131,     3,     4,     5,     6,     7,
       8,    18,   101,     9,    10,    11,    12,   209,    14,    15,
     180,    19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      42,    43,    44,    45,    46,    47,    48,    35,    50,    -1,
      52,    -1,    -1,    -1,    -1,    57,    42,    43,    44,    45,
      46,    47,    48,    -1,    50,    -1,    52,    -1,    -1,    -1,
      56,     9,    10,    11,    12,    -1,    14,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     9,    10,    11,    12,
      -1,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    42,    43,    44,    45,    46,    47,
      48,    -1,    50,    -1,    52,    -1,    -1,    -1,    56,    42,
      43,    44,    45,    46,    47,    48,    -1,    50,    -1,    52,
      -1,    -1,    -1,    56,     9,    10,    11,    12,    -1,    14,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      10,    11,    12,    -1,    14,    15,    -1,    -1,    -1,    -1,
       9,    10,    11,    12,    -1,    -1,    -1,    42,    43,    44,
      45,    46,    47,    48,    -1,    50,    -1,    52,    -1,    -1,
      -1,    56,    42,    43,    44,    45,    46,    47,    48,    -1,
      50,    -1,    52,    42,    43,    44,    45,    46,    47,    48,
      16,    50,    18,    52,    -1,    21,    22,    23,    -1,    25,
      26,    27,    28,    29,    30,    31,    32,    -1,    -1,    35,
      36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    -1,    49,    -1,    51,    -1,    16,    54,    18,
      -1,    57,    21,    22,    23,    -1,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    -1,    35,    36,    37,    38,
      39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,
      49,    -1,    51,    -1,    -1,    54
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    19,    35,    62,
      63,    64,    65,    68,    73,    74,    75,    76,    77,    35,
      35,    35,     0,    64,    57,    13,    35,    54,    80,    51,
      17,    69,    54,    51,    81,    74,    75,    78,    79,    35,
      20,    58,    72,    66,    78,    16,    18,    21,    22,    23,
      25,    26,    27,    28,    29,    30,    31,    32,    35,    36,
      37,    38,    39,    45,    49,    51,    73,    80,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    96,    97,
      98,    99,    35,    56,    58,    35,    20,    54,     3,    55,
      67,    75,    56,    51,    51,    51,    35,    84,    57,    51,
      51,    51,    51,    51,    51,    51,    96,    96,    96,    55,
      82,    57,     9,    10,    11,    12,    14,    15,    42,    43,
      44,    45,    46,    47,    48,    50,    52,    41,    74,    72,
      35,    70,    35,    35,    96,    84,    96,    57,    35,    96,
      94,    96,    56,    56,    96,    94,    95,    56,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    35,    96,    96,    72,    55,    71,    73,    76,    51,
      51,    56,    57,    56,    56,    58,    56,    58,    56,    56,
      51,    60,    78,    78,    83,    96,    83,    75,    57,    96,
      54,    95,    56,    56,    57,    24,    56,    33,    92,    56,
      57,    57,    84,    83,    37,    55,    56,    59,    83,    82,
      34,    92,    93,    82,    57
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

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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
		  Type, Value, Location); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
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
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

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
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

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
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
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
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  *++yyvsp = yylval;
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 137 "parser.y"
    {  /* pp2: The @1 is needed to convince 
                                       * yacc to set up yylloc. You can remove 
                                       * it once you have other uses of @n*/
                                      Program *program = new Program((yyvsp[(1) - (1)].declList));
                                      // if no errors, advance to next phase
                                      if (ReportError::NumErrors() == 0) 
                                          program->Print(0);
                                    }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 147 "parser.y"
    { ((yyval.declList)=(yyvsp[(1) - (2)].declList))->Append((yyvsp[(2) - (2)].decl)); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 148 "parser.y"
    { ((yyval.declList) = new List<Decl*>)->Append((yyvsp[(1) - (1)].decl)); }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 150 "parser.y"
    { (yyval.decl)=(yyvsp[(1) - (1)].var); }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 151 "parser.y"
    { (yyval.decl)=(yyvsp[(1) - (1)].fDecl); }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 152 "parser.y"
    { (yyval.decl)=(yyvsp[(1) - (1)].cDecl); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 153 "parser.y"
    { (yyval.decl) = (yyvsp[(1) - (1)].iDecl);}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 156 "parser.y"
    { (yyval.iDecl) = new InterfaceDecl(new Identifier((yylsp[(2) - (5)]), (yyvsp[(2) - (5)].identifier)), (yyvsp[(4) - (5)].declList));}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 158 "parser.y"
    {(yyval.declList) = new List<Decl*>;}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 159 "parser.y"
    {(yyval.declList)=(yyvsp[(1) - (2)].declList);
				(yyval.declList)->Append((yyvsp[(2) - (2)].decl));}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 162 "parser.y"
    {(yyval.decl) = new FnDecl(new Identifier((yylsp[(2) - (6)]),(yyvsp[(2) - (6)].identifier)), (yyvsp[(1) - (6)].type), (yyvsp[(4) - (6)].varList));}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 163 "parser.y"
    {(yyval.decl) = new FnDecl(new Identifier((yylsp[(2) - (6)]),(yyvsp[(2) - (6)].identifier)), Type::voidType,(yyvsp[(4) - (6)].varList));}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 165 "parser.y"
    { (yyval.cDecl) = new ClassDecl(new Identifier((yylsp[(2) - (7)]), (yyvsp[(2) - (7)].identifier)), (yyvsp[(3) - (7)].namedtype), (yyvsp[(4) - (7)].ntypeList), (yyvsp[(6) - (7)].declList));}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 167 "parser.y"
    {(yyval.namedtype) = new NamedType(new Identifier((yylsp[(2) - (2)]),(yyvsp[(2) - (2)].identifier)));}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 168 "parser.y"
    {(yyval.namedtype) = NULL;}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 170 "parser.y"
    {(yyval.declList) = new List<Decl*>;}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 171 "parser.y"
    { (yyval.declList) = (yyvsp[(1) - (2)].declList); (yyval.declList)->Append((yyvsp[(2) - (2)].decl));}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 173 "parser.y"
    {(yyval.decl) = (yyvsp[(1) - (1)].var);}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 174 "parser.y"
    {(yyval.decl) = (yyvsp[(1) - (1)].fDecl);}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 176 "parser.y"
    {(yyval.ntypeList) = new List<NamedType*>;}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 177 "parser.y"
    {(yyval.ntypeList) = (yyvsp[(3) - (3)].ntypeList); (yyval.ntypeList)->Append(new NamedType(new Identifier((yylsp[(2) - (3)]),(yyvsp[(2) - (3)].identifier))));}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 178 "parser.y"
    {(yyval.ntypeList) = (yyvsp[(4) - (4)].ntypeList); (yyval.ntypeList)->Append(new NamedType(new Identifier((yylsp[(3) - (4)]),(yyvsp[(3) - (4)].identifier))));}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 181 "parser.y"
    { (yyval.var)=(yyvsp[(1) - (2)].var); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 184 "parser.y"
    { (yyval.var) = new VarDecl(new Identifier((yylsp[(2) - (2)]), (yyvsp[(2) - (2)].identifier)), (yyvsp[(1) - (2)].type)); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 187 "parser.y"
    { (yyval.type) = Type::intType; }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 188 "parser.y"
    { (yyval.type) = Type::boolType; }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 189 "parser.y"
    { (yyval.type) = Type::stringType; }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 190 "parser.y"
    { (yyval.type) = Type::doubleType; }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 191 "parser.y"
    { (yyval.type) = new NamedType(new Identifier((yylsp[(1) - (1)]),(yyvsp[(1) - (1)].identifier))); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 192 "parser.y"
    { (yyval.type) = new ArrayType(Join((yylsp[(1) - (2)]), (yylsp[(2) - (2)])), (yyvsp[(1) - (2)].type)); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 195 "parser.y"
    { ((yyval.fDecl)=(yyvsp[(1) - (2)].fDecl))->SetFunctionBody((yyvsp[(2) - (2)].stmt)); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 199 "parser.y"
    { (yyval.fDecl) = new FnDecl(new Identifier((yylsp[(2) - (5)]), (yyvsp[(2) - (5)].identifier)), (yyvsp[(1) - (5)].type), (yyvsp[(4) - (5)].varList)); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 201 "parser.y"
    { (yyval.fDecl) = new FnDecl(new Identifier((yylsp[(2) - (5)]), (yyvsp[(2) - (5)].identifier)), Type::voidType, (yyvsp[(4) - (5)].varList)); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 204 "parser.y"
    { (yyval.varList) = (yyvsp[(1) - (1)].varList); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 205 "parser.y"
    { (yyval.varList) = new List<VarDecl*>; }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 209 "parser.y"
    { ((yyval.varList)=(yyvsp[(1) - (3)].varList))->Append((yyvsp[(3) - (3)].var)); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 210 "parser.y"
    { ((yyval.varList) = new List<VarDecl*>)->Append((yyvsp[(1) - (1)].var)); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 214 "parser.y"
    { (yyval.stmt) = new StmtBlock((yyvsp[(2) - (4)].varList), (yyvsp[(3) - (4)].stmtList)); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 217 "parser.y"
    { ((yyval.varList)=(yyvsp[(1) - (2)].varList))->Append((yyvsp[(2) - (2)].var)); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 218 "parser.y"
    { (yyval.varList) = new List<VarDecl*>; }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 221 "parser.y"
    { (yyval.stmtList) = new List<Stmt*>; }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 222 "parser.y"
    {(yyval.stmtList) = (yyvsp[(2) - (2)].stmtList); (yyval.stmtList)->InsertAt((yyvsp[(1) - (2)].stmt), 0);}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 224 "parser.y"
    {(yyval.stmt) = (yyvsp[(1) - (2)].expr);}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 225 "parser.y"
    {(yyval.stmt) = (yyvsp[(1) - (1)].stmt);}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 226 "parser.y"
    {(yyval.stmt) = (yyvsp[(1) - (1)].stmt);}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 227 "parser.y"
    {(yyval.stmt) = (yyvsp[(1) - (1)].stmt);}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 228 "parser.y"
    {(yyval.stmt) = (yyvsp[(1) - (1)].stmt);}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 229 "parser.y"
    {(yyval.stmt) = (yyvsp[(1) - (1)].stmt);}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 230 "parser.y"
    {(yyval.stmt) = (yyvsp[(1) - (1)].stmt);}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 231 "parser.y"
    {(yyval.stmt)=(yyvsp[(1) - (1)].stmt);}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 232 "parser.y"
    {(yyval.stmt) = (yyvsp[(1) - (1)].stmt);}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 235 "parser.y"
    {(yyval.expr) = new EmptyExpr;}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 236 "parser.y"
    { (yyval.expr) =(yyvsp[(1) - (1)].expr);}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 239 "parser.y"
    {(yyval.stmt) = new IfStmt((yyvsp[(3) - (5)].expr), (yyvsp[(5) - (5)].stmt), NULL);}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 240 "parser.y"
    {(yyval.stmt) = new IfStmt((yyvsp[(3) - (7)].expr), (yyvsp[(5) - (7)].stmt), (yyvsp[(7) - (7)].stmt));}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 244 "parser.y"
    {(yyval.stmt) = new WhileStmt((yyvsp[(3) - (5)].expr), (yyvsp[(5) - (5)].stmt));}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 247 "parser.y"
    {(yyval.stmt) = new ForStmt((yyvsp[(3) - (9)].expr), (yyvsp[(5) - (9)].expr), (yyvsp[(7) - (9)].expr), (yyvsp[(9) - (9)].stmt)); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 250 "parser.y"
    {(yyval.stmt) = new ReturnStmt((yylsp[(1) - (3)]), (yyvsp[(2) - (3)].expr));}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 253 "parser.y"
    {(yyval.stmt) = new BreakStmt((yylsp[(1) - (2)]));}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 256 "parser.y"
    {(yyval.stmt) = new PrintStmt((yyvsp[(3) - (5)].exprList));}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 259 "parser.y"
    {(yyval.stmt) = new SwitchStmt((yyvsp[(3) - (7)].expr), (yyvsp[(6) - (7)].cases));}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 262 "parser.y"
    {}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 263 "parser.y"
    {}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 264 "parser.y"
    {}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 267 "parser.y"
    {}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 270 "parser.y"
    {(yyval.exprList) = (yyvsp[(1) - (3)].exprList); (yyval.exprList)->Append((yyvsp[(3) - (3)].expr));}
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 271 "parser.y"
    {(yyval.exprList) = new List<Expr*>; (yyval.exprList)->Append((yyvsp[(1) - (1)].expr));}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 274 "parser.y"
    {(yyval.exprList) = (yyvsp[(1) - (1)].exprList);}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 275 "parser.y"
    {(yyval.exprList) = new List<Expr*>;}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 278 "parser.y"
    { (yyval.expr) = new AssignExpr((yyvsp[(1) - (3)].expr), new Operator((yylsp[(2) - (3)]), "="), (yyvsp[(3) - (3)].expr));}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 279 "parser.y"
    {(yyval.expr) = (yyvsp[(1) - (1)].expr);}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 280 "parser.y"
    {(yyval.expr) = (yyvsp[(1) - (1)].expr);}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 281 "parser.y"
    {(yyval.expr) = new This((yylsp[(1) - (1)]));}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 282 "parser.y"
    {(yyval.expr) = (yyvsp[(1) - (1)].expr);}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 283 "parser.y"
    {(yyval.expr) = (yyvsp[(2) - (3)].expr);}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 284 "parser.y"
    {(yyval.expr) = new ArithmeticExpr((yyvsp[(1) - (3)].expr), new Operator((yylsp[(2) - (3)]), "+"), (yyvsp[(3) - (3)].expr));}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 285 "parser.y"
    {(yyval.expr) = new ArithmeticExpr((yyvsp[(1) - (3)].expr), new Operator((yylsp[(2) - (3)]), "-"), (yyvsp[(3) - (3)].expr));}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 286 "parser.y"
    { (yyval.expr) = new ArithmeticExpr((yyvsp[(1) - (3)].expr), new Operator((yylsp[(2) - (3)]), "*"), (yyvsp[(3) - (3)].expr));}
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 287 "parser.y"
    {(yyval.expr) = new ArithmeticExpr((yyvsp[(1) - (3)].expr), new Operator((yylsp[(2) - (3)]), "/"), (yyvsp[(3) - (3)].expr));}
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 288 "parser.y"
    {(yyval.expr) = new ArithmeticExpr((yyvsp[(1) - (3)].expr), new Operator((yylsp[(2) - (3)]), "%"), (yyvsp[(3) - (3)].expr));}
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 289 "parser.y"
    {(yyval.expr) = new ArithmeticExpr(new Operator((yylsp[(1) - (2)]), "-"), (yyvsp[(2) - (2)].expr));}
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 290 "parser.y"
    {(yyval.expr) = new RelationalExpr((yyvsp[(1) - (3)].expr), new Operator((yylsp[(2) - (3)]), "<"), (yyvsp[(3) - (3)].expr));}
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 291 "parser.y"
    {(yyval.expr) = new RelationalExpr((yyvsp[(1) - (3)].expr), new Operator((yylsp[(2) - (3)]), "<="), (yyvsp[(3) - (3)].expr));}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 292 "parser.y"
    {(yyval.expr) = new RelationalExpr((yyvsp[(1) - (3)].expr), new Operator((yylsp[(2) - (3)]), ">"), (yyvsp[(3) - (3)].expr));}
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 293 "parser.y"
    {(yyval.expr) = new RelationalExpr((yyvsp[(1) - (3)].expr), new Operator((yylsp[(2) - (3)]), ">="), (yyvsp[(3) - (3)].expr));}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 294 "parser.y"
    {(yyval.expr) = new EqualityExpr((yyvsp[(1) - (3)].expr), new Operator((yylsp[(2) - (3)]), "=="), (yyvsp[(3) - (3)].expr));}
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 295 "parser.y"
    {(yyval.expr) = new EqualityExpr((yyvsp[(1) - (3)].expr), new Operator((yylsp[(2) - (3)]), "!="), (yyvsp[(3) - (3)].expr));}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 296 "parser.y"
    {(yyval.expr) = new LogicalExpr((yyvsp[(1) - (3)].expr), new Operator((yylsp[(2) - (3)]), "&&"), (yyvsp[(3) - (3)].expr));}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 297 "parser.y"
    {(yyval.expr) = new LogicalExpr((yyvsp[(1) - (3)].expr), new Operator((yylsp[(2) - (3)]), "||"), (yyvsp[(3) - (3)].expr));}
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 298 "parser.y"
    {(yyval.expr) = new LogicalExpr(new Operator((yylsp[(2) - (2)]), "!"), (yyvsp[(2) - (2)].expr));}
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 299 "parser.y"
    {(yyval.expr) = new ReadIntegerExpr((yylsp[(1) - (3)]));}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 300 "parser.y"
    {(yyval.expr) = new ReadLineExpr((yylsp[(1) - (3)]));}
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 301 "parser.y"
    {(yyval.expr) = new NewExpr((yylsp[(1) - (4)]), new NamedType(new Identifier((yylsp[(3) - (4)]),(yyvsp[(3) - (4)].identifier))));}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 302 "parser.y"
    {(yyval.expr) = new NewArrayExpr((yylsp[(1) - (6)]),(yyvsp[(3) - (6)].expr),(yyvsp[(5) - (6)].type));}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 305 "parser.y"
    {(yyval.expr) = new FieldAccess(NULL, new Identifier((yylsp[(1) - (1)]),(yyvsp[(1) - (1)].identifier)));}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 306 "parser.y"
    {(yyval.expr) = new FieldAccess((yyvsp[(1) - (3)].expr), new Identifier((yylsp[(3) - (3)]),(yyvsp[(3) - (3)].identifier)));}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 307 "parser.y"
    {(yyval.expr) = new ArrayAccess((yylsp[(1) - (4)]),(yyvsp[(1) - (4)].expr),(yyvsp[(3) - (4)].expr));}
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 309 "parser.y"
    {(yyval.expr) = new Call((yylsp[(1) - (4)]),NULL, new Identifier((yylsp[(1) - (4)]),(yyvsp[(1) - (4)].identifier)), (yyvsp[(3) - (4)].exprList));}
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 310 "parser.y"
    {(yyval.expr) = new Call((yylsp[(1) - (6)]), (yyvsp[(1) - (6)].expr), new Identifier((yylsp[(3) - (6)]),(yyvsp[(3) - (6)].identifier)), (yyvsp[(5) - (6)].exprList));}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 315 "parser.y"
    {(yyval.expr) = new IntConstant((yylsp[(1) - (1)]),(yyvsp[(1) - (1)].integerConstant));}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 316 "parser.y"
    {(yyval.expr) = new DoubleConstant((yylsp[(1) - (1)]),(yyvsp[(1) - (1)].doubleConstant));}
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 317 "parser.y"
    {(yyval.expr) = new BoolConstant((yylsp[(1) - (1)]),(yyvsp[(1) - (1)].boolConstant));}
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 318 "parser.y"
    {(yyval.expr) = new StringConstant((yylsp[(1) - (1)]),(yyvsp[(1) - (1)].stringConstant));}
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 319 "parser.y"
    {(yyval.expr) = new NullConstant((yylsp[(1) - (1)]));}
    break;



/* Line 1806 of yacc.c  */
#line 2517 "y.tab.c"
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
  *++yylsp = yyloc;

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

  yyerror_range[1] = yylloc;

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
		      yytoken, &yylval, &yylloc);
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

  yyerror_range[1] = yylsp[1-yylen];
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
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



/* Line 2067 of yacc.c  */
#line 321 "parser.y"


/* The closing %% above marks the end of the Rules section and the beginning
 * of the User Subroutines section. All text from here to the end of the
 * file is copied verbatim to the end of the generated y.tab.c file.
 * This section is where you put definitions of helper functions.
 */

/* Function: InitParser
 * --------------------
 * This function will be called before any calls to yyparse().  It is designed
 * to give you an opportunity to do anything that must be done to initialize
 * the parser (set global variables, configure starting state, etc.). One
 * thing it already does for you is assign the value of the global variable
 * yydebug that controls whether yacc prints debugging information about
 * parser actions (shift/reduce) and contents of state stack during parser.
 * If set to false, no information is printed. Setting it to true will give
 * you a running trail that might be helpful when debugging your parser.
 * Please be sure the variable is set to false when submitting your final
 * version.
 */
void InitParser()
{
   PrintDebug("parser", "Initializing parser");
   //yydebug = false;
}

