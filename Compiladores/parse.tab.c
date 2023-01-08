/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parse.y"

	#define YYPARSER 
	#include "utils.h"
  	#define YYSTYPE TreeNode*
	
	static int yylex();
	int yyerror(char *error);
	
	Stack func_stack;
	char *attr_name, *var_name, *func_name;
	
 	int cur_line_number, func_cur_line_number;
 	
 	int firstFunc = 1;
  
   	TreeNode* treeToReturn;

#line 88 "parse.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSE_TAB_H_INCLUDED
# define YY_YY_PARSE_TAB_H_INCLUDED
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
    IF = 258,
    ELSE = 259,
    WHILE = 260,
    RETURN = 261,
    INT = 262,
    VOID = 263,
    ID = 264,
    NUM = 265,
    ASSIGN = 266,
    EQUAL = 267,
    DIF = 268,
    LT = 269,
    GT = 270,
    LTE = 271,
    GTE = 272,
    PLUS = 273,
    MINUS = 274,
    TIMES = 275,
    SLASH = 276,
    OPARENT = 277,
    CPARENT = 278,
    OBRACKET = 279,
    CBRACKET = 280,
    OKEY = 281,
    CKEY = 282,
    SEMICOLON = 283,
    COMMA = 284,
    COMENT = 285,
    NEWLINE = 286,
    WHITESPACE = 287,
    ERROR = 288,
    FINISHED = 289
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSE_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   112

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  109

#define YYUNDEFTOK  2
#define YYMAXUTOK   289


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    27,    27,    29,    37,    39,    44,    50,    51,    52,
      53,    61,    66,    72,    81,    83,    83,    85,    93,    95,
     103,   105,   110,   116,   116,   118,   118,   134,   134,   158,
     158,   178,   192,   192,   212,   213,   220,   221,   222,   223,
     224,   226,   240,   253,   255,   262,   271,   279,   283,   290,
     301,   301,   316,   321,   325,   330,   335,   340,   346,   346,
     366,   366,   368,   381,   383,   396,   397,   399,   412,   414,
     427
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "WHILE", "RETURN", "INT",
  "VOID", "ID", "NUM", "ASSIGN", "EQUAL", "DIF", "LT", "GT", "LTE", "GTE",
  "PLUS", "MINUS", "TIMES", "SLASH", "OPARENT", "CPARENT", "OBRACKET",
  "CBRACKET", "OKEY", "CKEY", "SEMICOLON", "COMMA", "COMENT", "NEWLINE",
  "WHITESPACE", "ERROR", "FINISHED", "$accept", "program", "term", "mult",
  "factor", "sum", "exp", "exp_decl", "exp_simple", "exp_sum", "exp_kind",
  "decl", "var_decl", "$@1", "$@2", "func_decl", "$@3", "arg", "$@4",
  "params", "stmt", "bloc_decl", "local_decl", "cond_decl", "loop_decl",
  "return_decl", "var", "$@5", "operator", "activate", "$@6", "arguments",
  "list_decl", "list_arg", "list_params", "list_stmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289
};
# endif

#define YYPACT_NINF (-74)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-59)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      51,   -74,   -74,     7,    15,   -74,   -74,   -74,    51,   -74,
      -6,   -74,   -17,    13,    19,   -74,    33,    65,    21,    31,
      47,   -74,    37,    49,    53,    55,    56,    51,   -74,    59,
     -74,   -74,   -74,    60,    51,   -74,    71,   -74,     3,    62,
      66,    67,    -5,     4,   -74,     5,   -74,   -74,    54,   -74,
      63,   -74,   -74,    52,   -74,   -74,   -74,   -74,   -74,    73,
     -74,     5,     5,   -74,    64,    69,    68,    72,   -74,   -74,
       5,   -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,
       5,     5,     5,    74,    75,   -74,     5,    40,   -74,   -74,
     -74,    54,    58,   -74,    29,    29,    76,   -74,   -74,    77,
      70,    83,   -74,   -74,   -74,     5,    29,   -74,   -74
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    21,    22,     0,     0,    63,    23,    24,     2,     1,
      25,    62,     0,     0,     0,    26,     0,     0,     0,    22,
       0,    68,     0,    34,     0,    31,     0,     0,    28,     0,
      43,    30,    67,     0,    70,    33,     0,    42,     0,    25,
       0,     0,     0,    49,    10,     0,    41,    16,    20,     4,
       0,    36,    14,    18,    69,    37,    38,    39,    40,     8,
       9,     0,     0,    47,     0,     0,     0,     0,     5,     6,
       0,    15,    56,    57,    53,    54,    52,    55,    11,    12,
       0,     0,     0,     0,     0,    48,     0,    61,     7,     3,
       8,    19,    17,    13,     0,     0,     0,    66,    65,     0,
      60,    44,    46,    51,    59,     0,     0,    64,    45
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -74,   -74,    14,   -74,    26,   -74,   -42,   -74,   -74,    22,
       2,    94,    78,   -74,   -74,   -74,   -74,   -26,   -74,   -74,
     -73,    79,   -74,   -74,   -74,   -74,   -28,   -74,   -74,   -74,
     -74,   -74,   -74,   -74,   -74,   -74
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,    48,    70,    49,    80,    50,    51,    52,    53,
      20,     5,     6,    12,    13,     7,    14,    21,    29,    22,
      54,    55,    34,    56,    57,    58,    59,    65,    81,    60,
      66,    99,     8,   100,    23,    38
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      64,    32,     4,    67,    43,    44,    40,     9,    41,    42,
       4,    15,    43,    44,    43,    44,   -29,    45,   -27,    83,
      84,   101,   102,    63,    10,    45,   -58,    45,   -50,    30,
      46,    47,    40,   108,    41,    42,    36,    16,    43,    44,
      93,    17,    90,    18,    96,    97,    24,     1,     2,    43,
      44,    45,    90,    90,   -35,    30,    25,    47,     1,     2,
      26,    98,    45,   107,    72,    73,    74,    75,    76,    77,
      78,    79,     1,    19,    68,    69,    78,    79,    27,   -32,
      39,    28,    30,    33,    82,    35,   -27,   106,    61,    62,
      87,    71,    85,    86,    91,    88,    89,    94,    95,   105,
     104,   103,    11,    92,     0,    31,     0,     0,     0,     0,
       0,     0,    37
};

static const yytype_int8 yycheck[] =
{
      42,    27,     0,    45,     9,    10,     3,     0,     5,     6,
       8,    28,     9,    10,     9,    10,    22,    22,    24,    61,
      62,    94,    95,    28,     9,    22,    22,    22,    24,    26,
      27,    28,     3,   106,     5,     6,    34,    24,     9,    10,
      82,    22,    70,    10,    86,    87,    25,     7,     8,     9,
      10,    22,    80,    81,    23,    26,     9,    28,     7,     8,
      23,    87,    22,   105,    12,    13,    14,    15,    16,    17,
      18,    19,     7,     8,    20,    21,    18,    19,    29,    24,
       9,    28,    26,    24,    11,    25,    24,     4,    22,    22,
      22,    28,    28,    24,    80,    23,    70,    23,    23,    29,
      23,    25,     8,    81,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    34
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,     8,    36,    45,    46,    47,    50,    67,     0,
       9,    46,    48,    49,    51,    28,    24,    22,    10,     8,
      45,    52,    54,    69,    25,     9,    23,    29,    28,    53,
      26,    56,    52,    24,    57,    25,    45,    47,    70,     9,
       3,     5,     6,     9,    10,    22,    27,    28,    37,    39,
      41,    42,    43,    44,    55,    56,    58,    59,    60,    61,
      64,    22,    22,    28,    41,    62,    65,    41,    20,    21,
      38,    28,    12,    13,    14,    15,    16,    17,    18,    19,
      40,    63,    11,    41,    41,    28,    24,    22,    23,    39,
      61,    37,    44,    41,    23,    23,    41,    41,    52,    66,
      68,    55,    55,    25,    23,    29,     4,    41,    55
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    35,    36,    37,    37,    38,    38,    39,    39,    39,
      39,    40,    40,    41,    41,    42,    42,    43,    43,    44,
      44,    45,    45,    46,    46,    48,    47,    49,    47,    51,
      50,    52,    53,    52,    54,    54,    55,    55,    55,    55,
      55,    56,    57,    57,    58,    58,    59,    60,    60,    61,
      62,    61,    63,    63,    63,    63,    63,    63,    65,    64,
      66,    66,    67,    67,    68,    68,    68,    69,    69,    70,
      70
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     3,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     3,     1,     2,     1,     3,     1,     3,
       1,     1,     1,     1,     1,     0,     4,     0,     7,     0,
       7,     2,     0,     5,     1,     1,     1,     1,     1,     1,
       1,     4,     2,     0,     5,     7,     5,     2,     3,     1,
       0,     5,     1,     1,     1,     1,     1,     1,     0,     5,
       1,     0,     2,     1,     3,     1,     1,     3,     1,     2,
       0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
      yychar = yylex ();
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

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
#line 27 "parse.y"
                    { treeToReturn = yyvsp[0]; }
#line 1425 "parse.tab.c"
    break;

  case 3:
#line 29 "parse.y"
                        {
	
            yyval = create_exp_tree_node(exp_op);

            yyval->child[0] = yyvsp[-2];
            yyval->child[1] = yyvsp[0];
            yyval->attr.op = yyvsp[-1]->attr.op; 
          }
#line 1438 "parse.tab.c"
    break;

  case 4:
#line 37 "parse.y"
                           { yyval = yyvsp[0]; }
#line 1444 "parse.tab.c"
    break;

  case 5:
#line 39 "parse.y"
             { 

          yyval = create_exp_tree_node(exp_id); 
          yyval->attr.op = TIMES;
        }
#line 1454 "parse.tab.c"
    break;

  case 6:
#line 44 "parse.y"
                {
        	
          yyval = create_exp_tree_node(exp_id); 
          yyval->attr.op = SLASH;
        }
#line 1464 "parse.tab.c"
    break;

  case 7:
#line 50 "parse.y"
                             { yyval = yyvsp[-2]; }
#line 1470 "parse.tab.c"
    break;

  case 8:
#line 51 "parse.y"
              { yyval = yyvsp[0]; }
#line 1476 "parse.tab.c"
    break;

  case 9:
#line 52 "parse.y"
                   { yyval = yyvsp[0]; }
#line 1482 "parse.tab.c"
    break;

  case 10:
#line 53 "parse.y"
              { 
        
          yyval = create_exp_tree_node(exp_num);

          yyval->attr.value = atoi(token_str);
          yyval->p_kind = Integer;
        }
#line 1494 "parse.tab.c"
    break;

  case 11:
#line 61 "parse.y"
           {
 
          yyval = create_exp_tree_node(exp_id); 
          yyval->attr.op = PLUS; 
        }
#line 1504 "parse.tab.c"
    break;

  case 12:
#line 66 "parse.y"
                {
        	
          yyval = create_exp_tree_node(exp_id); 
          yyval->attr.op = MINUS;
        }
#line 1514 "parse.tab.c"
    break;

  case 13:
#line 72 "parse.y"
                     { 

              yyval = create_stmt_tree_node(stmt_atrib);

              yyval->child[0] = yyvsp[-2];
              yyval->child[1] = yyvsp[0];
              yyval->p_kind = Integer;
              yyval->attr.op = ASSIGN; 
            }
#line 1528 "parse.tab.c"
    break;

  case 14:
#line 81 "parse.y"
                         { yyval = yyvsp[0]; }
#line 1534 "parse.tab.c"
    break;

  case 15:
#line 83 "parse.y"
                         { yyval = yyvsp[-1]; }
#line 1540 "parse.tab.c"
    break;

  case 16:
#line 83 "parse.y"
                                                  { yyval = NULL; }
#line 1546 "parse.tab.c"
    break;

  case 17:
#line 85 "parse.y"
                                      { 

                  yyval = create_exp_tree_node(exp_op);
                  
                  yyval->child[0] = yyvsp[-2];
                  yyval->child[1] = yyvsp[0];
                  yyval->attr.op = yyvsp[-1]->attr.op; 
                }
#line 1559 "parse.tab.c"
    break;

  case 18:
#line 93 "parse.y"
                                          { yyval = yyvsp[0]; }
#line 1565 "parse.tab.c"
    break;

  case 19:
#line 95 "parse.y"
                           { 

              yyval = create_exp_tree_node(exp_op);
              
              yyval->child[0] = yyvsp[-2];
              yyval->child[1] = yyvsp[0];
              yyval->attr.op = yyvsp[-1]->attr.op; 
            }
#line 1578 "parse.tab.c"
    break;

  case 20:
#line 103 "parse.y"
                               { yyval = yyvsp[0]; }
#line 1584 "parse.tab.c"
    break;

  case 21:
#line 105 "parse.y"
               { 

              yyval = create_decl_tree_node(decl_kind); 
              yyval->p_kind = Integer; 
            }
#line 1594 "parse.tab.c"
    break;

  case 22:
#line 110 "parse.y"
                               { 
			
              yyval = create_decl_tree_node(decl_kind); 
              yyval->p_kind = Void; 
            }
#line 1604 "parse.tab.c"
    break;

  case 23:
#line 116 "parse.y"
                { yyval = yyvsp[0]; }
#line 1610 "parse.tab.c"
    break;

  case 24:
#line 116 "parse.y"
                                         { yyval = yyvsp[0]; }
#line 1616 "parse.tab.c"
    break;

  case 25:
#line 118 "parse.y"
                       { 

                  attr_name = token_str;
                  cur_line_number = line_num;
                }
#line 1626 "parse.tab.c"
    break;

  case 26:
#line 123 "parse.y"
                          {
              		
                  yyval = yyvsp[-3];
                  YYSTYPE tree_node = create_decl_tree_node(decl_var);

                  tree_node->attr.name = attr_name;
                  tree_node->line_num = cur_line_number;
                  tree_node->p_kind = yyvsp[-3]->p_kind;
                  
                  yyval->child[0] = tree_node;
                }
#line 1642 "parse.tab.c"
    break;

  case 27:
#line 134 "parse.y"
                              { 
            	
                  attr_name = token_str;
                  cur_line_number = line_num;
                }
#line 1652 "parse.tab.c"
    break;

  case 28:
#line 139 "parse.y"
                                                { 
            	
                  yyval = yyvsp[-6];
                  
                  YYSTYPE exp_node = create_exp_tree_node(exp_num);
                  exp_node->attr.value = atoi(token_str);
                  exp_node->p_kind = Integer;
                  
                  YYSTYPE tree_node = create_decl_tree_node(decl_var);
                  tree_node->attr.name = attr_name;
                  tree_node->line_num = cur_line_number;
                  tree_node->child[0] = exp_node;

                  if (yyvsp[-6]->p_kind == Integer) tree_node->p_kind = Array;
                  else tree_node->p_kind = Void;
                  
                  yyval->child[0] = tree_node; 
                }
#line 1675 "parse.tab.c"
    break;

  case 29:
#line 158 "parse.y"
                         {
	
                func_name = token_str;
                func_cur_line_number = line_num;
              }
#line 1685 "parse.tab.c"
    break;

  case 30:
#line 163 "parse.y"
                                               {
                
				yyval = yyvsp[-6];

                YYSTYPE func_node = create_decl_tree_node(decl_func);
                
                func_node->child[0] = yyvsp[-2];
                func_node->child[1] = yyvsp[0];
                func_node->attr.name = func_name;
                func_node->line_num = func_cur_line_number;
                func_node->p_kind = yyvsp[-6]->p_kind;
                
                yyval->child[0] = func_node;
              }
#line 1704 "parse.tab.c"
    break;

  case 31:
#line 178 "parse.y"
                   { 

            yyval = yyvsp[-1];

            attr_name = token_str;
            cur_line_number = line_num;
            
            YYSTYPE decl_node = create_decl_tree_node(decl_var); 
            
            decl_node->attr.name = attr_name;
            decl_node->line_num = cur_line_number;
            decl_node->p_kind = yyvsp[-1]->p_kind;
            
            yyval->child[0] = decl_node;
          }
#line 1724 "parse.tab.c"
    break;

  case 32:
#line 192 "parse.y"
                          {
          	
            attr_name = token_str;
            cur_line_number = line_num;
          }
#line 1734 "parse.tab.c"
    break;

  case 33:
#line 197 "parse.y"
                            {    
    	  
            yyval = yyvsp[-4];

            YYSTYPE decl_node = create_decl_tree_node(decl_var);
            
            decl_node->attr.name = attr_name;
            decl_node->line_num = cur_line_number;
            
            if (yyvsp[-4]->p_kind == Integer) decl_node->p_kind = Array;
            else decl_node->p_kind = yyvsp[-4]->p_kind;

            yyval->child[0] = decl_node;
          }
#line 1753 "parse.tab.c"
    break;

  case 34:
#line 212 "parse.y"
                     { yyval = yyvsp[0]; }
#line 1759 "parse.tab.c"
    break;

  case 35:
#line 213 "parse.y"
                       { 
			
			yyval = create_exp_tree_node(exp_id); 
			yyval->attr.name = "void"; 
			yyval->p_kind = Void; 
		}
#line 1770 "parse.tab.c"
    break;

  case 36:
#line 220 "parse.y"
                 { yyval = yyvsp[0]; }
#line 1776 "parse.tab.c"
    break;

  case 37:
#line 221 "parse.y"
                 { yyval = yyvsp[0]; }
#line 1782 "parse.tab.c"
    break;

  case 38:
#line 222 "parse.y"
                  { yyval = yyvsp[0]; }
#line 1788 "parse.tab.c"
    break;

  case 39:
#line 223 "parse.y"
                 { yyval = yyvsp[0]; }
#line 1794 "parse.tab.c"
    break;

  case 40:
#line 224 "parse.y"
                    { yyval = yyvsp[0]; }
#line 1800 "parse.tab.c"
    break;

  case 41:
#line 226 "parse.y"
                                           { 

            YYSTYPE tmp = yyvsp[-2];
                                                    
            if (tmp != NULL) {
            	
                while (tmp->sibling != NULL) tmp = tmp->sibling;
                  
                tmp->sibling = yyvsp[-1];
                yyval = yyvsp[-2];
            }
            else yyval = yyvsp[-1];
        }
#line 1818 "parse.tab.c"
    break;

  case 42:
#line 240 "parse.y"
                                 {
 
                  YYSTYPE tmp = yyvsp[-1];
                                    
                  if (tmp != NULL) {
                  	
                    while (tmp->sibling != NULL) tmp = tmp->sibling;

                    tmp->sibling = yyvsp[0];
                    yyval = yyvsp[-1];
                  }
                  else yyval = yyvsp[0];
                }
#line 1836 "parse.tab.c"
    break;

  case 43:
#line 253 "parse.y"
                                  { yyval = NULL; }
#line 1842 "parse.tab.c"
    break;

  case 44:
#line 255 "parse.y"
                                        { 

                yyval = create_stmt_tree_node(stmt_if);
              
                yyval->child[0] = yyvsp[-2];
                yyval->child[1] = yyvsp[0];
              }
#line 1854 "parse.tab.c"
    break;

  case 45:
#line 262 "parse.y"
                                                     { 
              
                yyval = create_stmt_tree_node(stmt_if);
                
                yyval->child[0] = yyvsp[-4];
                yyval->child[1] = yyvsp[-2];
                yyval->child[2] = yyvsp[0];
              }
#line 1867 "parse.tab.c"
    break;

  case 46:
#line 271 "parse.y"
                                           { 

                yyval = create_stmt_tree_node(stmt_while);

                yyval->child[0] = yyvsp[-2];
                yyval->child[1] = yyvsp[0];
            }
#line 1879 "parse.tab.c"
    break;

  case 47:
#line 279 "parse.y"
                               { 

                yyval = create_stmt_tree_node(stmt_return);
              }
#line 1888 "parse.tab.c"
    break;

  case 48:
#line 283 "parse.y"
                                     {
              	
                yyval = create_stmt_tree_node(stmt_return);
                
                yyval->child[0] = yyvsp[-1];
              }
#line 1899 "parse.tab.c"
    break;

  case 49:
#line 290 "parse.y"
         { 

        attr_name = token_str;
        cur_line_number = line_num;

        yyval = create_exp_tree_node(exp_id);
        
        yyval->attr.name = attr_name;
        yyval->line_num = cur_line_number;
        yyval->p_kind = Void;
      }
#line 1915 "parse.tab.c"
    break;

  case 50:
#line 301 "parse.y"
           { 
      
        var_name = token_str;
        cur_line_number = line_num;
      }
#line 1925 "parse.tab.c"
    break;

  case 51:
#line 306 "parse.y"
                            {
      	
        yyval = create_exp_tree_node(exp_id);

        yyval->attr.name = var_name;
        yyval->line_num = cur_line_number;
        yyval->child[0] = yyvsp[-1];
        yyval->p_kind = Integer; 
      }
#line 1939 "parse.tab.c"
    break;

  case 52:
#line 316 "parse.y"
               { 

              yyval = create_exp_tree_node(exp_id); 
              yyval->attr.op = LTE; 
            }
#line 1949 "parse.tab.c"
    break;

  case 53:
#line 321 "parse.y"
                 { 
              yyval = create_exp_tree_node(exp_id); 
              yyval->attr.op = LT; 
            }
#line 1958 "parse.tab.c"
    break;

  case 54:
#line 325 "parse.y"
                 { 
            
              yyval = create_exp_tree_node(exp_id); 
              yyval->attr.op = GT; 
            }
#line 1968 "parse.tab.c"
    break;

  case 55:
#line 330 "parse.y"
                  { 
            
              yyval = create_exp_tree_node(exp_id); 
              yyval->attr.op = GTE; 
            }
#line 1978 "parse.tab.c"
    break;

  case 56:
#line 335 "parse.y"
                    { 
            
              yyval = create_exp_tree_node(exp_id); 
              yyval->attr.op = EQUAL; 
            }
#line 1988 "parse.tab.c"
    break;

  case 57:
#line 340 "parse.y"
                  { 
            
              yyval = create_exp_tree_node(exp_id); 
              yyval->attr.op = DIF; 
            }
#line 1998 "parse.tab.c"
    break;

  case 58:
#line 346 "parse.y"
              { 
              
			  if (firstFunc) {
			  	
                init_stack(&func_stack);
                firstFunc = 0;
              }

              push_stack(&func_stack, token_str);
              cur_line_number = line_num;
            }
#line 2014 "parse.tab.c"
    break;

  case 59:
#line 357 "parse.y"
                                      { 
            
              yyval = create_stmt_tree_node(stmt_func);

              yyval->child[1] = yyvsp[-1]; 
              yyval->attr.name = pop_stack(&func_stack);
              yyval->line_num = cur_line_number;
            }
#line 2027 "parse.tab.c"
    break;

  case 60:
#line 366 "parse.y"
                     { yyval = yyvsp[0]; }
#line 2033 "parse.tab.c"
    break;

  case 61:
#line 366 "parse.y"
                                    { yyval = NULL; }
#line 2039 "parse.tab.c"
    break;

  case 62:
#line 368 "parse.y"
                           { 

                  YYSTYPE tmp = yyvsp[-1];
                  
                  if (tmp != NULL)  {
                    
					while (tmp->child[0]->sibling != NULL) tmp = tmp->child[0]->sibling;
					
                    tmp->child[0]->sibling = yyvsp[0];
                    yyval = yyvsp[-1];
                  }
                  else yyval = yyvsp[0];
                }
#line 2057 "parse.tab.c"
    break;

  case 63:
#line 381 "parse.y"
                       { yyval = yyvsp[0]; }
#line 2063 "parse.tab.c"
    break;

  case 64:
#line 383 "parse.y"
                              { 

                YYSTYPE tmp = yyvsp[-2];
                                    
                if (tmp != NULL) {
                	
                    while (tmp->sibling != NULL) tmp = tmp->sibling;

                    tmp->sibling = yyvsp[0];
                    yyval = yyvsp[-2];
                }
                else yyval = yyvsp[0];
              }
#line 2081 "parse.tab.c"
    break;

  case 65:
#line 396 "parse.y"
                                { yyval = yyvsp[0]; }
#line 2087 "parse.tab.c"
    break;

  case 66:
#line 397 "parse.y"
                                { yyval = yyvsp[0]; }
#line 2093 "parse.tab.c"
    break;

  case 67:
#line 399 "parse.y"
                                    { 
                
				YYSTYPE tmp = yyvsp[-2];

                if (tmp != NULL) {
                	
                  while (tmp->sibling != NULL) tmp = tmp->sibling;

                  tmp->sibling = yyvsp[0];
                  yyval = yyvsp[-2];
                } 
                else yyval = yyvsp[0];
              }
#line 2111 "parse.tab.c"
    break;

  case 68:
#line 412 "parse.y"
                                { yyval = yyvsp[0]; }
#line 2117 "parse.tab.c"
    break;

  case 69:
#line 414 "parse.y"
                           { 
                  
				  YYSTYPE tmp = yyvsp[-1];
                                    
                  if (tmp != NULL) {
                    
					while (tmp->sibling != NULL) tmp = tmp->sibling;

                    tmp->sibling = yyvsp[0];
                    yyval = yyvsp[-1];
                  }
                  else yyval = yyvsp[0];
                }
#line 2135 "parse.tab.c"
    break;

  case 70:
#line 427 "parse.y"
                                  { yyval = NULL; }
#line 2141 "parse.tab.c"
    break;


#line 2145 "parse.tab.c"

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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
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
  return yyresult;
}
#line 428 "parse.y"


static int yylex(void) { 

	return get_token(); 
}

TreeNode *parse(void) { 

	yyparse(); 
	return treeToReturn; 
}

int yyerror(char *error_msg) {
	
    char* token_name = get_token_name(yychar);

    if (yychar == ID || yychar == NUM) fprintf(stdout,"ERRO SINTATICO %s - Linha : %d\n", token_name, line_num);
    else fprintf(stdout,"ERRO SINTATICO %s (%s) - Linha: %d\n", token_name, yytext, line_num); 

    free(token_name);
}
