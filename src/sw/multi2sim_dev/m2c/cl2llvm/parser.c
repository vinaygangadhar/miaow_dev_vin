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
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse         cl2llvm_yyparse
#define yylex           cl2llvm_yylex
#define yyerror         cl2llvm_yyerror
#define yylval          cl2llvm_yylval
#define yychar          cl2llvm_yychar
#define yydebug         cl2llvm_yydebug
#define yynerrs         cl2llvm_yynerrs


/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "parser.y"


#define YYDEBUG 1

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lib/util/debug.h>
#include <lib/util/hash-table.h>
#include <lib/util/list.h>
#include <llvm-c/Core.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Transforms/Scalar.h>
#include <llvm-c/BitWriter.h>

#include "Type.h"
#include "vector-ops.h"
#include "for-blocks.h"
#include "while-blocks.h"
#include "arg.h"
#include "declarator-list.h"
#include "function.h"
#include "val.h"
#include "ret-error.h"
#include "Type.h"
#include "init.h"
#include "symbol.h"
#include "built-in-funcs.h"
#include "parser.h"
#include "cl2llvm.h"
#include "format.h"

#define CL2LLVM_MAX_FUNC_ARGS 64
#define CL2LLVM_MAX_ARG_NAME_LEN 200
#define CL2LLVM_MAX_NUM_ARRAY_INDEX_DIM 100

extern LLVMBuilderRef cl2llvm_builder;
extern LLVMModuleRef cl2llvm_module;
extern LLVMValueRef cl2llvm_function;
extern LLVMBasicBlockRef cl2llvm_basic_block;

extern int temp_var_count;
extern char temp_var_name[50];

int block_count;
char block_name[50];

int  func_count;
char func_name[50];

extern struct hash_table_t *cl2llvm_built_in_func_table;
struct hash_table_t *cl2llvm_symbol_table;
extern struct hash_table_t *cl2llvm_built_in_const_table;

struct cl2llvm_function_t *cl2llvm_current_function;
LLVMBasicBlockRef current_basic_block;



/* Line 268 of yacc.c  */
#line 143 "parser.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
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
     TOK_ID = 258,
     TOK_CONST_INT = 259,
     TOK_CONST_INT_U = 260,
     TOK_CONST_INT_L = 261,
     TOK_CONST_INT_UL = 262,
     TOK_CONST_INT_LL = 263,
     TOK_CONST_INT_ULL = 264,
     TOK_CONST_DEC = 265,
     TOK_CONST_DEC_H = 266,
     TOK_CONST_DEC_F = 267,
     TOK_CONST_DEC_L = 268,
     TOK_CONST_VAL = 269,
     TOK_STRING = 270,
     TOK_COMMA = 271,
     TOK_SEMICOLON = 272,
     TOK_ELLIPSIS = 273,
     TOK_SHIFT_LEFT_EQUAL = 274,
     TOK_SHIFT_RIGHT_EQUAL = 275,
     TOK_EXCLUSIVE_EQUAL = 276,
     TOK_OR_EQUAL = 277,
     TOK_AND_EQUAL = 278,
     TOK_MOD_EQUAL = 279,
     TOK_DIV_EQUAL = 280,
     TOK_MULT_EQUAL = 281,
     TOK_MINUS_EQUAL = 282,
     TOK_ADD_EQUAL = 283,
     TOK_EQUAL = 284,
     TOK_COLON = 285,
     TOK_CONDITIONAL = 286,
     TOK_LOGICAL_OR = 287,
     TOK_LOGICAL_AND = 288,
     TOK_BITWISE_OR = 289,
     TOK_BITWISE_EXCLUSIVE = 290,
     TOK_BITWISE_AND = 291,
     TOK_INEQUALITY = 292,
     TOK_EQUALITY = 293,
     TOK_LESS_EQUAL = 294,
     TOK_GREATER_EQUAL = 295,
     TOK_LESS = 296,
     TOK_GREATER = 297,
     TOK_SHIFT_LEFT = 298,
     TOK_SHIFT_RIGHT = 299,
     TOK_MINUS = 300,
     TOK_PLUS = 301,
     TOK_MOD = 302,
     TOK_DIV = 303,
     TOK_MULT = 304,
     TOK_BITWISE_NOT = 305,
     TOK_LOGICAL_NEGATE = 306,
     TOK_PREFIX = 307,
     TOK_CURLY_BRACE_CLOSE = 308,
     TOK_CURLY_BRACE_OPEN = 309,
     TOK_STRUCT_DEREF = 310,
     TOK_STRUCT_REF = 311,
     TOK_POSTFIX = 312,
     TOK_BRACKET_CLOSE = 313,
     TOK_BRACKET_OPEN = 314,
     TOK_PAR_CLOSE = 315,
     TOK_PAR_OPEN = 316,
     TOK_DECREMENT = 317,
     TOK_INCREMENT = 318,
     TOK_AUTO = 319,
     TOK_BOOL = 320,
     TOK_BREAK = 321,
     TOK_CASE = 322,
     TOK_CHAR = 323,
     TOK_CHARN = 324,
     TOK_CONSTANT = 325,
     TOK_CONST = 326,
     TOK_CONTINUE = 327,
     TOK_DEFAULT = 328,
     TOK_DO = 329,
     TOK_DOUBLE = 330,
     TOK_DOUBLE_LONG = 331,
     TOK_DOUBLEN = 332,
     TOK_ENUM = 333,
     TOK_EVENT_T = 334,
     TOK_EXTERN = 335,
     TOK_FLOAT = 336,
     TOK_FLOATN = 337,
     TOK_FOR = 338,
     TOK_GLOBAL = 339,
     TOK_GOTO = 340,
     TOK_HALF = 341,
     TOK_IF = 342,
     TOK_ELSE = 343,
     TOK_IMAGE2D_T = 344,
     TOK_IMAGE3D_T = 345,
     TOK_IMAGE2D_ARRAY_T = 346,
     TOK_IMAGE1D_T = 347,
     TOK_IMAGE1D_BUFFER_T = 348,
     TOK_IMAGE1D_ARRAY_T = 349,
     TOK_INLINE = 350,
     TOK_INT = 351,
     TOK_INT_LONG = 352,
     TOK_LONG_LONG = 353,
     TOK_INTN = 354,
     TOK_INTPTR_T = 355,
     TOK_KERNEL = 356,
     TOK_LOCAL = 357,
     TOK_LONG = 358,
     TOK_LONGN = 359,
     TOK_PRIVATE = 360,
     TOK_PTRDIFF_T = 361,
     TOK_READ_ONLY = 362,
     TOK_READ_WRITE = 363,
     TOK_REGISTER = 364,
     TOK_RETURN = 365,
     TOK_SAMPLER_T = 366,
     TOK_SHORT = 367,
     TOK_SHORTN = 368,
     TOK_SIGNED = 369,
     TOK_SIZEOF = 370,
     TOK_SIZE_T = 371,
     TOK_STATIC = 372,
     TOK_STRUCT = 373,
     TOK_SWITCH = 374,
     TOK_TYPEDEF = 375,
     TOK_TYPENAME = 376,
     TOK_UCHARN = 377,
     TOK_UCHAR = 378,
     TOK_ULONG = 379,
     TOK_USHORT = 380,
     TOK_UINT = 381,
     TOK_UINT_LONG = 382,
     TOK_UINT_LONG_LONG = 383,
     TOK_UINTN = 384,
     TOK_ULONGN = 385,
     TOK_UINTPTR_T = 386,
     TOK_UNION = 387,
     TOK_UNSIGNED = 388,
     TOK_USHORTN = 389,
     TOK_VOID = 390,
     TOK_VOLATILE = 391,
     TOK_WHILE = 392,
     TOK_WRITE_ONLY = 393
   };
#endif
/* Tokens.  */
#define TOK_ID 258
#define TOK_CONST_INT 259
#define TOK_CONST_INT_U 260
#define TOK_CONST_INT_L 261
#define TOK_CONST_INT_UL 262
#define TOK_CONST_INT_LL 263
#define TOK_CONST_INT_ULL 264
#define TOK_CONST_DEC 265
#define TOK_CONST_DEC_H 266
#define TOK_CONST_DEC_F 267
#define TOK_CONST_DEC_L 268
#define TOK_CONST_VAL 269
#define TOK_STRING 270
#define TOK_COMMA 271
#define TOK_SEMICOLON 272
#define TOK_ELLIPSIS 273
#define TOK_SHIFT_LEFT_EQUAL 274
#define TOK_SHIFT_RIGHT_EQUAL 275
#define TOK_EXCLUSIVE_EQUAL 276
#define TOK_OR_EQUAL 277
#define TOK_AND_EQUAL 278
#define TOK_MOD_EQUAL 279
#define TOK_DIV_EQUAL 280
#define TOK_MULT_EQUAL 281
#define TOK_MINUS_EQUAL 282
#define TOK_ADD_EQUAL 283
#define TOK_EQUAL 284
#define TOK_COLON 285
#define TOK_CONDITIONAL 286
#define TOK_LOGICAL_OR 287
#define TOK_LOGICAL_AND 288
#define TOK_BITWISE_OR 289
#define TOK_BITWISE_EXCLUSIVE 290
#define TOK_BITWISE_AND 291
#define TOK_INEQUALITY 292
#define TOK_EQUALITY 293
#define TOK_LESS_EQUAL 294
#define TOK_GREATER_EQUAL 295
#define TOK_LESS 296
#define TOK_GREATER 297
#define TOK_SHIFT_LEFT 298
#define TOK_SHIFT_RIGHT 299
#define TOK_MINUS 300
#define TOK_PLUS 301
#define TOK_MOD 302
#define TOK_DIV 303
#define TOK_MULT 304
#define TOK_BITWISE_NOT 305
#define TOK_LOGICAL_NEGATE 306
#define TOK_PREFIX 307
#define TOK_CURLY_BRACE_CLOSE 308
#define TOK_CURLY_BRACE_OPEN 309
#define TOK_STRUCT_DEREF 310
#define TOK_STRUCT_REF 311
#define TOK_POSTFIX 312
#define TOK_BRACKET_CLOSE 313
#define TOK_BRACKET_OPEN 314
#define TOK_PAR_CLOSE 315
#define TOK_PAR_OPEN 316
#define TOK_DECREMENT 317
#define TOK_INCREMENT 318
#define TOK_AUTO 319
#define TOK_BOOL 320
#define TOK_BREAK 321
#define TOK_CASE 322
#define TOK_CHAR 323
#define TOK_CHARN 324
#define TOK_CONSTANT 325
#define TOK_CONST 326
#define TOK_CONTINUE 327
#define TOK_DEFAULT 328
#define TOK_DO 329
#define TOK_DOUBLE 330
#define TOK_DOUBLE_LONG 331
#define TOK_DOUBLEN 332
#define TOK_ENUM 333
#define TOK_EVENT_T 334
#define TOK_EXTERN 335
#define TOK_FLOAT 336
#define TOK_FLOATN 337
#define TOK_FOR 338
#define TOK_GLOBAL 339
#define TOK_GOTO 340
#define TOK_HALF 341
#define TOK_IF 342
#define TOK_ELSE 343
#define TOK_IMAGE2D_T 344
#define TOK_IMAGE3D_T 345
#define TOK_IMAGE2D_ARRAY_T 346
#define TOK_IMAGE1D_T 347
#define TOK_IMAGE1D_BUFFER_T 348
#define TOK_IMAGE1D_ARRAY_T 349
#define TOK_INLINE 350
#define TOK_INT 351
#define TOK_INT_LONG 352
#define TOK_LONG_LONG 353
#define TOK_INTN 354
#define TOK_INTPTR_T 355
#define TOK_KERNEL 356
#define TOK_LOCAL 357
#define TOK_LONG 358
#define TOK_LONGN 359
#define TOK_PRIVATE 360
#define TOK_PTRDIFF_T 361
#define TOK_READ_ONLY 362
#define TOK_READ_WRITE 363
#define TOK_REGISTER 364
#define TOK_RETURN 365
#define TOK_SAMPLER_T 366
#define TOK_SHORT 367
#define TOK_SHORTN 368
#define TOK_SIGNED 369
#define TOK_SIZEOF 370
#define TOK_SIZE_T 371
#define TOK_STATIC 372
#define TOK_STRUCT 373
#define TOK_SWITCH 374
#define TOK_TYPEDEF 375
#define TOK_TYPENAME 376
#define TOK_UCHARN 377
#define TOK_UCHAR 378
#define TOK_ULONG 379
#define TOK_USHORT 380
#define TOK_UINT 381
#define TOK_UINT_LONG 382
#define TOK_UINT_LONG_LONG 383
#define TOK_UINTN 384
#define TOK_ULONGN 385
#define TOK_UINTPTR_T 386
#define TOK_UNION 387
#define TOK_UNSIGNED 388
#define TOK_USHORTN 389
#define TOK_VOID 390
#define TOK_VOLATILE 391
#define TOK_WHILE 392
#define TOK_WRITE_ONLY 393




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 64 "parser.y"

	long int const_int_val;
	unsigned long long const_int_val_ull;
	double  const_float_val;
	char * identifier;
	struct cl2llvmTypeWrap *llvm_type_ref;
	struct cl2llvm_val_t *llvm_value_ref;
	struct list_t * init_list;
	struct list_t * list_val_t;
	struct cl2llvm_arg_t *arg_t;
	struct list_t *arg_list;
	LLVMBasicBlockRef basic_block_ref;
	struct cl2llvm_while_blocks_t *llvm_while_blocks;
	struct cl2llvm_for_blocks_t *llvm_for_blocks;
	struct cl2llvm_decl_list_t *decl_list;



/* Line 293 of yacc.c  */
#line 474 "parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 486 "parser.c"

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
#define YYFINAL  63
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1728

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  139
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  204
/* YYNRULES -- Number of states.  */
#define YYNSTATES  336

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   393

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
     135,   136,   137,   138
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    19,    20,    30,
      31,    33,    37,    40,    42,    44,    47,    49,    51,    53,
      55,    57,    59,    61,    63,    65,    67,    69,    71,    73,
      75,    77,    79,    81,    83,    84,    87,    91,    94,    97,
      99,   103,   107,   112,   115,   117,   119,   121,   123,   125,
     127,   129,   133,   136,   139,   141,   143,   145,   150,   151,
     153,   157,   159,   163,   167,   173,   177,   178,   181,   184,
     187,   192,   196,   202,   206,   208,   212,   215,   219,   225,
     227,   229,   232,   235,   239,   244,   246,   247,   252,   253,
     260,   263,   264,   265,   276,   277,   278,   288,   289,   290,
     300,   301,   309,   310,   311,   313,   315,   319,   323,   327,
     331,   335,   339,   343,   347,   351,   355,   359,   363,   367,
     371,   375,   379,   383,   387,   391,   395,   399,   403,   407,
     411,   415,   419,   423,   429,   431,   433,   436,   440,   444,
     448,   451,   454,   457,   460,   463,   466,   471,   476,   479,
     482,   489,   493,   495,   499,   501,   503,   505,   507,   509,
     511,   513,   515,   517,   519,   521,   523,   525,   528,   530,
     532,   534,   536,   538,   540,   542,   544,   546,   548,   550,
     552,   554,   556,   558,   560,   562,   564,   566,   568,   570,
     572,   574,   576,   578,   580,   582,   584,   586,   588,   590,
     592,   594,   596,   598,   600
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     140,     0,    -1,   141,    -1,   140,   141,    -1,   143,    -1,
     142,    -1,   147,     3,    61,   145,    60,    17,    -1,    -1,
     147,     3,    61,   145,    60,    54,   144,   153,    53,    -1,
      -1,   146,    -1,   145,    16,   146,    -1,   147,     3,    -1,
     147,    -1,   149,    -1,   147,   149,    -1,    84,    -1,   102,
      -1,   105,    -1,    70,    -1,   193,    -1,   151,    -1,   101,
      -1,    95,    -1,   152,    -1,   148,    -1,   150,    -1,    71,
      -1,   136,    -1,   107,    -1,   138,    -1,   108,    -1,    80,
      -1,   117,    -1,    -1,   163,   153,    -1,    61,   154,    60,
      -1,   154,   155,    -1,    49,   154,    -1,     3,    -1,   154,
      56,     3,    -1,    59,   187,    58,    -1,   155,    59,   187,
      58,    -1,   186,    17,    -1,   162,    -1,   143,    -1,   142,
      -1,   174,    -1,   183,    -1,   180,    -1,   170,    -1,   110,
     186,    17,    -1,    72,    17,    -1,    66,    17,    -1,   166,
      -1,   164,    -1,   165,    -1,     3,    61,   158,    60,    -1,
      -1,   187,    -1,   155,    29,   187,    -1,   159,    -1,   158,
      16,   187,    -1,   158,    16,   159,    -1,   158,    16,   155,
      29,   187,    -1,    54,   158,    53,    -1,    -1,    29,   187,
      -1,    29,   159,    -1,     3,   160,    -1,   161,    16,     3,
     160,    -1,     3,   155,   160,    -1,   161,    16,     3,   155,
     160,    -1,   147,   161,    17,    -1,   156,    -1,    54,   153,
      53,    -1,     3,    30,    -1,    85,     3,    17,    -1,   119,
     187,    54,   167,    53,    -1,   168,    -1,   169,    -1,   167,
     168,    -1,   167,   169,    -1,    73,    30,   153,    -1,    67,
     187,    30,   153,    -1,   172,    -1,    -1,   172,    88,   171,
     163,    -1,    -1,    87,    61,   187,    60,   173,   163,    -1,
     175,   163,    -1,    -1,    -1,    83,    61,   186,    17,   176,
     186,    17,   177,   186,    60,    -1,    -1,    -1,    83,    61,
     162,   178,   186,    17,   179,   186,    60,    -1,    -1,    -1,
      74,   181,   163,   137,    61,   182,   187,    60,    17,    -1,
      -1,   137,    61,   185,   187,    60,   184,   163,    -1,    -1,
      -1,   187,    -1,   192,    -1,    61,   187,    60,    -1,   187,
      46,   187,    -1,   187,    45,   187,    -1,   187,    49,   187,
      -1,   187,    48,   187,    -1,   187,    47,   187,    -1,   187,
      43,   187,    -1,   187,    44,   187,    -1,   187,    38,   187,
      -1,   187,    37,   187,    -1,   187,    41,   187,    -1,   187,
      42,   187,    -1,   187,    39,   187,    -1,   187,    40,   187,
      -1,   187,    33,   187,    -1,   187,    32,   187,    -1,   154,
      29,   187,    -1,   154,    28,   187,    -1,   154,    27,   187,
      -1,   154,    25,   187,    -1,   154,    26,   187,    -1,   154,
      24,   187,    -1,   154,    23,   187,    -1,   154,    22,   187,
      -1,   154,    21,   187,    -1,   154,    20,   187,    -1,   154,
      19,   187,    -1,   187,    31,   187,    30,   187,    -1,   188,
      -1,   157,    -1,    51,   187,    -1,   187,    36,   187,    -1,
     187,    34,   187,    -1,   187,    35,   187,    -1,   154,    63,
      -1,    63,   154,    -1,    62,   154,    -1,   154,    62,    -1,
      45,   187,    -1,    46,   187,    -1,    61,   193,    60,   187,
      -1,   115,    61,   193,    60,    -1,    50,   187,    -1,    36,
     154,    -1,    61,   193,    60,    61,   191,    60,    -1,   187,
      16,   187,    -1,   190,    -1,   191,    16,   187,    -1,     4,
      -1,     6,    -1,     5,    -1,     7,    -1,     8,    -1,     9,
      -1,    10,    -1,    11,    -1,    12,    -1,    13,    -1,   154,
      -1,   189,    -1,   194,    -1,   193,    49,    -1,   100,    -1,
     106,    -1,   131,    -1,   111,    -1,    79,    -1,    89,    -1,
      90,    -1,    91,    -1,    92,    -1,    93,    -1,    94,    -1,
     126,    -1,   127,    -1,   128,    -1,   123,    -1,   112,    -1,
     125,    -1,   129,    -1,   122,    -1,   130,    -1,   134,    -1,
     113,    -1,    99,    -1,   104,    -1,    69,    -1,    82,    -1,
      77,    -1,    96,    -1,    97,    -1,    98,    -1,    68,    -1,
      81,    -1,    65,    -1,    75,    -1,    76,    -1,   135,    -1,
      86,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   224,   224,   225,   229,   230,   234,   243,   242,   399,
     405,   411,   419,   425,   436,   440,   482,   486,   490,   494,
     502,   508,   514,   520,   526,   533,   539,   548,   552,   556,
     557,   558,   563,   567,   573,   575,   579,   583,   661,   712,
     729,   750,   759,   769,   774,   775,   776,   777,   778,   779,
     780,   781,   809,   813,   817,   821,   825,   832,   908,   913,
     919,   924,   929,   934,   939,   947,   952,   955,   959,   967,
     978,   988,  1001,  1016,  1195,  1196,  1200,  1204,  1208,  1212,
    1213,  1214,  1215,  1219,  1223,  1227,  1236,  1235,  1264,  1263,
    1301,  1318,  1353,  1317,  1400,  1436,  1399,  1483,  1508,  1482,
    1531,  1530,  1559,  1586,  1589,  1595,  1597,  1601,  1656,  1709,
    1766,  1827,  1866,  1914,  1959,  2019,  2081,  2152,  2222,  2292,
    2362,  2453,  2539,  2565,  2638,  2710,  2788,  2863,  2935,  3002,
    3069,  3136,  3204,  3271,  3275,  3280,  3285,  3302,  3350,  3398,
    3451,  3522,  3592,  3663,  3734,  3782,  3786,  3797,  3802,  3848,
    3859,  3979,  3993,  3997,  4007,  4013,  4019,  4025,  4031,  4037,
    4043,  4049,  4055,  4061,  4067,  4162,  4170,  4174,  4192,  4197,
    4202,  4207,  4212,  4217,  4222,  4227,  4232,  4237,  4242,  4247,
    4253,  4259,  4265,  4271,  4277,  4283,  4290,  4297,  4304,  4311,
    4318,  4324,  4330,  4336,  4342,  4348,  4354,  4360,  4366,  4372,
    4378,  4384,  4390,  4396,  4403
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_ID", "TOK_CONST_INT",
  "TOK_CONST_INT_U", "TOK_CONST_INT_L", "TOK_CONST_INT_UL",
  "TOK_CONST_INT_LL", "TOK_CONST_INT_ULL", "TOK_CONST_DEC",
  "TOK_CONST_DEC_H", "TOK_CONST_DEC_F", "TOK_CONST_DEC_L", "TOK_CONST_VAL",
  "TOK_STRING", "TOK_COMMA", "TOK_SEMICOLON", "TOK_ELLIPSIS",
  "TOK_SHIFT_LEFT_EQUAL", "TOK_SHIFT_RIGHT_EQUAL", "TOK_EXCLUSIVE_EQUAL",
  "TOK_OR_EQUAL", "TOK_AND_EQUAL", "TOK_MOD_EQUAL", "TOK_DIV_EQUAL",
  "TOK_MULT_EQUAL", "TOK_MINUS_EQUAL", "TOK_ADD_EQUAL", "TOK_EQUAL",
  "TOK_COLON", "TOK_CONDITIONAL", "TOK_LOGICAL_OR", "TOK_LOGICAL_AND",
  "TOK_BITWISE_OR", "TOK_BITWISE_EXCLUSIVE", "TOK_BITWISE_AND",
  "TOK_INEQUALITY", "TOK_EQUALITY", "TOK_LESS_EQUAL", "TOK_GREATER_EQUAL",
  "TOK_LESS", "TOK_GREATER", "TOK_SHIFT_LEFT", "TOK_SHIFT_RIGHT",
  "TOK_MINUS", "TOK_PLUS", "TOK_MOD", "TOK_DIV", "TOK_MULT",
  "TOK_BITWISE_NOT", "TOK_LOGICAL_NEGATE", "TOK_PREFIX",
  "TOK_CURLY_BRACE_CLOSE", "TOK_CURLY_BRACE_OPEN", "TOK_STRUCT_DEREF",
  "TOK_STRUCT_REF", "TOK_POSTFIX", "TOK_BRACKET_CLOSE", "TOK_BRACKET_OPEN",
  "TOK_PAR_CLOSE", "TOK_PAR_OPEN", "TOK_DECREMENT", "TOK_INCREMENT",
  "TOK_AUTO", "TOK_BOOL", "TOK_BREAK", "TOK_CASE", "TOK_CHAR", "TOK_CHARN",
  "TOK_CONSTANT", "TOK_CONST", "TOK_CONTINUE", "TOK_DEFAULT", "TOK_DO",
  "TOK_DOUBLE", "TOK_DOUBLE_LONG", "TOK_DOUBLEN", "TOK_ENUM",
  "TOK_EVENT_T", "TOK_EXTERN", "TOK_FLOAT", "TOK_FLOATN", "TOK_FOR",
  "TOK_GLOBAL", "TOK_GOTO", "TOK_HALF", "TOK_IF", "TOK_ELSE",
  "TOK_IMAGE2D_T", "TOK_IMAGE3D_T", "TOK_IMAGE2D_ARRAY_T", "TOK_IMAGE1D_T",
  "TOK_IMAGE1D_BUFFER_T", "TOK_IMAGE1D_ARRAY_T", "TOK_INLINE", "TOK_INT",
  "TOK_INT_LONG", "TOK_LONG_LONG", "TOK_INTN", "TOK_INTPTR_T",
  "TOK_KERNEL", "TOK_LOCAL", "TOK_LONG", "TOK_LONGN", "TOK_PRIVATE",
  "TOK_PTRDIFF_T", "TOK_READ_ONLY", "TOK_READ_WRITE", "TOK_REGISTER",
  "TOK_RETURN", "TOK_SAMPLER_T", "TOK_SHORT", "TOK_SHORTN", "TOK_SIGNED",
  "TOK_SIZEOF", "TOK_SIZE_T", "TOK_STATIC", "TOK_STRUCT", "TOK_SWITCH",
  "TOK_TYPEDEF", "TOK_TYPENAME", "TOK_UCHARN", "TOK_UCHAR", "TOK_ULONG",
  "TOK_USHORT", "TOK_UINT", "TOK_UINT_LONG", "TOK_UINT_LONG_LONG",
  "TOK_UINTN", "TOK_ULONGN", "TOK_UINTPTR_T", "TOK_UNION", "TOK_UNSIGNED",
  "TOK_USHORTN", "TOK_VOID", "TOK_VOLATILE", "TOK_WHILE", "TOK_WRITE_ONLY",
  "$accept", "program", "external_def", "func_decl", "func_def", "$@1",
  "arg_list", "arg", "declarator_list", "addr_qual", "declarator",
  "type_qual", "access_qual", "sc_spec", "stmt_list", "lvalue",
  "array_deref_list", "stmt", "func_call", "param_list", "array_init",
  "init", "init_list", "declaration", "stmt_or_stmt_list", "label_stmt",
  "goto_stmt", "switch_stmt", "switch_body", "default_clause",
  "case_clause", "if_stmt", "@2", "if", "@3", "for_loop",
  "for_loop_header", "@4", "$@5", "@6", "$@7", "do_while_loop", "@8",
  "$@9", "while_loop", "$@10", "while_block_init", "maybe_expr", "expr",
  "unary_expr", "vec_literal", "vec_literal_param_two_elem",
  "vec_literal_param_list", "primary", "type_spec", "type_name", 0
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
     385,   386,   387,   388,   389,   390,   391,   392,   393
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   139,   140,   140,   141,   141,   142,   144,   143,   145,
     145,   145,   146,   146,   147,   147,   148,   148,   148,   148,
     149,   149,   149,   149,   149,   149,   149,   150,   150,   151,
     151,   151,   152,   152,   153,   153,   154,   154,   154,   154,
     154,   155,   155,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   157,   158,   158,
     158,   158,   158,   158,   158,   159,   160,   160,   160,   161,
     161,   161,   161,   162,   163,   163,   164,   165,   166,   167,
     167,   167,   167,   168,   169,   170,   171,   170,   173,   172,
     174,   176,   177,   175,   178,   179,   175,   181,   182,   180,
     184,   183,   185,   186,   186,   187,   187,   187,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     189,   190,   191,   191,   192,   192,   192,   192,   192,   192,
     192,   192,   192,   192,   192,   192,   193,   193,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     6,     0,     9,     0,
       1,     3,     2,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     2,     3,     2,     2,     1,
       3,     3,     4,     2,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     2,     1,     1,     1,     4,     0,     1,
       3,     1,     3,     3,     5,     3,     0,     2,     2,     2,
       4,     3,     5,     3,     1,     3,     2,     3,     5,     1,
       1,     2,     2,     3,     4,     1,     0,     4,     0,     6,
       2,     0,     0,    10,     0,     0,     9,     0,     0,     9,
       0,     7,     0,     0,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     5,     1,     1,     2,     3,     3,     3,
       2,     2,     2,     2,     2,     2,     4,     4,     2,     2,
       6,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   200,   198,   192,    19,    27,   201,   202,   194,   172,
      32,   199,   193,    16,   204,   173,   174,   175,   176,   177,
     178,    23,   195,   196,   197,   190,   168,    22,    17,   191,
      18,   169,    29,    31,   171,   183,   189,    33,   186,   182,
     184,   179,   180,   181,   185,   187,   170,   188,   203,    28,
      30,     0,     2,     5,     4,     0,    25,    14,    26,    21,
      24,    20,   166,     1,     3,     0,    15,   167,     9,     0,
      10,    13,     0,     0,    12,    11,     6,     7,    34,    39,
     154,   156,   155,   157,   158,   159,   160,   161,   162,   163,
       0,     0,     0,     0,     0,     0,    34,     0,     0,     0,
       0,     0,    97,     0,     0,     0,   103,     0,     0,     0,
      46,    45,     0,     0,   164,    74,   135,    44,    34,    55,
      56,    54,    50,    85,    47,   103,    49,    48,     0,   104,
     134,   165,   105,    76,    58,    39,     0,   149,    39,   144,
     145,    38,   148,   136,     0,   164,     0,     0,   142,   141,
      53,    52,   103,   103,     0,     0,     0,     0,     0,   102,
      66,     0,     8,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   143,   140,    37,    35,
      86,    90,    43,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    58,     0,     0,    61,    59,     0,    75,    36,
     106,     0,     0,     0,    94,     0,    77,     0,    51,     0,
       0,     0,     0,    66,    69,     0,    73,   132,   131,   130,
     129,   128,   127,   125,   126,   124,   123,   122,    40,     0,
       0,   103,     0,   121,   120,   138,   139,   137,   115,   114,
     118,   119,   116,   117,   112,   113,   108,   107,   111,   110,
     109,     0,     0,     0,    57,     0,   146,     0,    66,   103,
      91,    88,   147,     0,     0,     0,    79,    80,     0,    68,
      67,    71,    66,    41,     0,    87,     0,    65,    60,     0,
      63,    62,     0,   152,     0,    98,     0,   103,   103,     0,
      34,    78,    81,    82,   100,    66,    70,    42,   133,     0,
       0,     0,   150,     0,    95,     0,    89,    34,    83,   103,
      72,    64,   151,   153,     0,   103,    92,    84,   101,     0,
       0,   103,    99,    96,     0,    93
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    51,    52,   110,   111,    78,    69,    70,   112,    56,
      57,    58,    59,    60,   113,   114,   178,   115,   116,   204,
     205,   224,   161,   117,   118,   119,   120,   121,   275,   276,
     277,   122,   241,   123,   298,   124,   125,   297,   331,   269,
     325,   126,   152,   313,   127,   319,   221,   128,   129,   130,
     131,   293,   294,   132,    61,    62
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -213
static const yytype_int16 yypact[] =
{
    1264,  -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,
    -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,
    -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,
    -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,
    -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,
    -213,   158,  -213,  -213,  -213,   641,  -213,  -213,  -213,  -213,
    -213,     4,  -213,  -213,  -213,   -10,  -213,  -213,  1264,     9,
    -213,   716,  1264,    18,  -213,  -213,  -213,  -213,   294,     3,
    -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,
       1,  1215,  1215,     1,  1215,  1215,   294,  1002,     1,     1,
      75,    98,  -213,    55,   116,    60,  1215,    70,  1215,    76,
    -213,  -213,   791,    96,   426,  -213,  -213,  -213,   294,  -213,
    -213,  -213,  -213,    62,  -213,   430,  -213,  -213,   136,  1621,
    -213,  -213,  -213,  -213,  1135,  -213,     1,    58,    93,  -213,
    -213,    58,  -213,  -213,   102,   119,   549,   -19,    58,    58,
    -213,  -213,   430,   566,   139,  1215,   142,  1336,  1557,  -213,
      -1,    22,  -213,  1215,  1215,  1215,  1215,  1215,  1215,  1215,
    1215,  1215,  1215,  1215,   157,  1215,  -213,  -213,   103,  -213,
    -213,  -213,  -213,  1215,  1215,  1215,  1215,  1215,  1215,  1215,
    1215,  1215,  1215,  1215,  1215,  1215,  1215,  1215,  1215,  1215,
    1215,  1215,  1135,    -5,    11,  -213,  1621,   -16,  -213,  -213,
    -213,  1234,    24,   866,  -213,   148,  -213,   985,  -213,   -12,
     -31,  1215,  1154,    28,  -213,   161,  -213,  1621,  1621,  1621,
    1621,  1621,  1621,  1621,  1621,  1621,  1621,  1621,  -213,  1501,
    1215,   430,  1582,   279,  1637,  1652,  1666,  1679,   163,   163,
      81,    81,    81,    81,   147,   147,    87,    87,  -213,  -213,
    -213,     2,  1215,  1135,  -213,  1002,  -213,   105,    59,  1215,
    -213,  -213,  -213,  1215,   137,   -21,  -213,  -213,  1441,  -213,
    1621,  -213,    59,  -213,  1529,  -213,  1215,  -213,  1621,    61,
    -213,  1621,  1271,  -213,    13,  -213,   155,  1215,   430,  1602,
     294,  -213,  -213,  -213,  -213,    28,  -213,  -213,  1621,  1215,
    1215,  1215,  -213,  1215,  -213,   160,  -213,   294,  -213,   430,
    -213,  1621,  1621,  1621,  1471,  1215,  -213,  -213,  -213,   166,
     125,  1215,  -213,  -213,   126,  -213
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -213,  -213,   138,    12,    14,  -213,  -213,   115,    17,  -213,
     -45,  -213,  -213,  -213,   -87,   -77,  -111,  -213,  -213,    -4,
    -207,  -212,  -213,    37,  -118,  -213,  -213,  -213,  -213,   -76,
     -75,  -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,
    -213,  -213,  -213,  -213,  -213,  -213,  -213,  -106,   -89,  -213,
    -213,  -213,  -213,  -213,   -96,  -213
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -104
static const yytype_int16 yytable[] =
{
     156,   147,   139,   140,   135,   142,   143,   181,   146,   144,
      66,   281,    53,   137,    54,   279,   141,    55,   263,   158,
     145,   148,   149,   203,   262,    72,    66,   263,   222,   311,
      67,   179,   301,   133,   212,    76,   273,    67,   225,   226,
     174,   211,   274,   175,   209,   206,   273,   215,   272,   223,
      93,    68,   274,    67,   240,   287,   290,   222,   175,   207,
      68,   219,   136,    53,   134,    54,   217,    66,    55,    73,
     306,   264,    77,   312,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,    71,   239,   240,   222,    71,
     309,   203,   150,   320,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   206,   174,   151,   153,   175,   175,   154,
     240,   155,   266,   285,   195,   196,   197,   198,   199,   200,
     201,   157,   278,   280,   199,   200,   201,   159,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   162,
     180,   284,   289,   182,   134,   208,   216,   223,    63,   218,
     238,   267,   240,   296,   282,   270,   295,   300,    66,   147,
     213,   305,   314,   288,   291,   174,   292,   326,   175,   209,
     316,   176,   177,   332,   299,   333,   335,    75,   145,    64,
     214,   315,   197,   198,   199,   200,   201,   308,   261,   302,
     303,   328,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   318,     0,     0,     0,     0,     0,   330,
     321,   322,   323,     1,   324,   334,     2,     3,     4,     5,
     327,     0,     0,     6,     7,     8,     0,     9,    10,    11,
      12,     0,    13,     0,    14,     0,     0,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,     0,    29,    30,    31,    32,    33,     0,     0,    34,
      35,    36,     0,     0,     0,    37,     0,     0,     0,     0,
      38,    39,     0,    40,    41,    42,    43,    44,    45,    46,
       0,     0,    47,    48,    49,     0,    50,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,     0,     0,
       0,  -103,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,     0,
      90,     0,     0,     0,     0,     0,     0,     0,     0,    91,
      92,     0,     0,    93,    94,    95,     0,     0,    96,     0,
       0,     0,     0,     0,     0,    97,    98,    99,     0,     1,
     100,     0,     2,     3,     4,     5,   101,     0,   102,     6,
       7,     8,     0,     9,    10,    11,    12,   103,    13,   104,
      14,   105,     0,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,     0,    29,    30,
      31,    32,    33,     0,   106,    34,    35,    36,     0,   107,
       0,    37,     0,   108,     0,     0,    38,    39,     0,    40,
      41,    42,    43,    44,    45,    46,     0,     0,    47,    48,
      49,   109,    50,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,     0,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    90,     0,     0,     0,
       0,     0,     0,     0,     0,    91,    92,     0,     0,    93,
      94,    95,   174,     0,    96,   175,     0,     0,   176,   177,
       0,    97,    98,    99,     0,     1,   100,     0,     2,     3,
       4,     5,   101,     0,   102,     6,     7,     8,     0,     9,
      10,    11,    12,   103,    13,   104,    14,   105,     0,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,     0,    29,    30,    31,    32,    33,     0,
     106,    34,    35,    36,     0,   107,     0,    37,     0,   108,
       0,     0,    38,    39,     0,    40,    41,    42,    43,    44,
      45,    46,     0,     0,    47,    48,    49,   109,    50,   138,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,     0,
       0,     0,    90,     0,     0,     0,     0,     0,     0,   210,
       0,    91,    92,     0,     0,    93,    94,    95,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    97,    98,    99,
       0,     1,     0,     0,     2,     3,     4,     5,     0,     0,
       0,     6,     7,     8,    65,     9,    10,    11,    12,     0,
      13,     0,    14,     0,     0,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,     0,
      29,    30,    31,    32,    33,     0,     0,    34,    35,    36,
       0,   107,     0,    37,     0,     0,     0,     0,    38,    39,
       0,    40,    41,    42,    43,    44,    45,    46,     0,     0,
      47,    48,    49,     0,    50,     0,     1,     0,     0,     2,
       3,     4,     5,     0,     0,     0,     6,     7,     8,    74,
       9,    10,    11,    12,     0,    13,     0,    14,     0,     0,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,     0,    29,    30,    31,    32,    33,
       0,     0,    34,    35,    36,     0,     0,     0,    37,     0,
       0,     0,     0,    38,    39,     0,    40,    41,    42,    43,
      44,    45,    46,     0,     0,    47,    48,    49,     0,    50,
       0,     1,     0,     0,     2,     3,     4,     5,     0,     0,
       0,     6,     7,     8,   160,     9,    10,    11,    12,     0,
      13,     0,    14,     0,     0,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,     0,
      29,    30,    31,    32,    33,     0,     0,    34,    35,    36,
       0,     0,     0,    37,     0,     0,     0,     0,    38,    39,
       0,    40,    41,    42,    43,    44,    45,    46,     0,     0,
      47,    48,    49,     0,    50,     0,     1,     0,     0,     2,
       3,     4,     5,     0,     0,     0,     6,     7,     8,   268,
       9,    10,    11,    12,     0,    13,     0,    14,     0,     0,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,     0,    29,    30,    31,    32,    33,
       0,     0,    34,    35,    36,     0,     0,     0,    37,     0,
       0,     0,     0,    38,    39,     0,    40,    41,    42,    43,
      44,    45,    46,     0,     0,    47,    48,    49,     0,    50,
       0,     1,     0,     0,     2,     3,     4,     5,     0,     0,
       0,     6,     7,     8,     0,     9,    10,    11,    12,     0,
      13,     0,    14,     0,     0,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,     0,
      29,    30,    31,    32,    33,     0,     0,    34,    35,    36,
       0,     0,     0,    37,     0,     0,     0,     0,    38,    39,
       0,    40,    41,    42,    43,    44,    45,    46,     0,     0,
      47,    48,    49,     0,    50,   138,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,     0,     0,     0,    90,     0,
       0,     0,     0,     0,     0,   271,     0,    91,    92,     0,
       0,    93,    94,    95,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    97,    98,    99,     0,     1,     0,     0,
       2,     3,     0,     0,     0,     0,     0,     6,     7,     8,
       0,     9,     0,    11,    12,     0,     0,     0,    14,     0,
       0,    15,    16,    17,    18,    19,    20,     0,    22,    23,
      24,    25,    26,     0,     0,     0,    29,     0,    31,     0,
       0,     0,     0,    34,    35,    36,     0,   107,     0,     0,
       0,     0,     0,     0,    38,    39,     0,    40,    41,    42,
      43,    44,    45,    46,     0,     0,    47,    48,   138,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,     0,
       0,     0,     0,     0,     0,     0,     0,   138,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,     0,     0,
       0,    90,     0,     0,     0,     0,     0,     0,     0,     0,
      91,    92,     0,     0,    93,    94,    95,     0,     0,   202,
      90,     0,     0,     0,   175,     0,    97,    98,    99,    91,
      92,     0,     0,    93,    94,    95,     0,     0,   202,     0,
       0,     0,     0,     0,     0,    97,    98,    99,   138,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,     0,
       0,     0,     0,     0,     0,     0,     0,   138,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,     0,     0,
     107,    90,     0,     0,     0,     0,     0,     0,     0,     0,
      91,    92,     0,     0,    93,    94,    95,     0,     0,   107,
      90,     0,     0,     0,     0,     0,    97,    98,    99,    91,
      92,     0,     0,    93,    94,    95,     0,   310,     0,     0,
       0,     0,     0,     0,     0,   265,    98,    99,     0,     0,
       0,     0,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,     0,     0,     0,     0,     0,     0,     0,     0,     1,
     107,   210,     2,     3,     4,     5,     0,     0,     0,     6,
       7,     8,     0,     9,    10,    11,    12,     0,    13,   107,
      14,     0,     0,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,     0,    29,    30,
      31,    32,    33,     0,     0,    34,    35,    36,     0,     0,
       0,    37,     0,     0,     0,     0,    38,    39,     0,    40,
      41,    42,    43,    44,    45,    46,     0,     0,    47,    48,
      49,     1,    50,     0,     2,     3,     0,     0,     0,     0,
       0,     6,     7,     8,     0,     9,     0,    11,    12,     0,
       0,     0,    14,     0,     0,    15,    16,    17,    18,    19,
      20,     0,    22,    23,    24,    25,    26,     0,     0,     0,
      29,     0,    31,     0,     0,     0,     0,    34,    35,    36,
       0,     0,     0,     0,     0,     0,     0,     0,    38,    39,
       0,    40,    41,    42,    43,    44,    45,    46,     0,     0,
      47,    48,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   304,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   329,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,     0,     0,     0,     0,     0,     0,     0,     0,   283,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,     0,
       0,     0,     0,     0,     0,     0,     0,   307,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,     0,     0,     0,
       0,   220,   286,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   317,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-213))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
     106,    97,    91,    92,     3,    94,    95,   125,    97,    96,
      55,   223,     0,    90,     0,   222,    93,     0,    16,   108,
      97,    98,    99,   134,    29,    16,    71,    16,    29,    16,
      49,   118,    53,    30,   152,    17,    67,    49,    16,    17,
      56,    60,    73,    59,    60,   134,    67,   153,    60,   160,
      49,    61,    73,    49,    59,    53,   263,    29,    59,   136,
      61,   157,    61,    51,    61,    51,   155,   112,    51,    60,
     282,    60,    54,    60,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,    68,   175,    59,    29,    72,
      29,   202,    17,   305,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,    56,    17,    61,    59,    59,     3,
      59,    61,   211,   241,    43,    44,    45,    46,    47,    48,
      49,    61,   221,   222,    47,    48,    49,    61,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    53,
      88,   240,   263,    17,    61,    53,    17,   268,     0,    17,
       3,   137,    59,   269,     3,    17,    61,    30,   213,   265,
     153,   282,    17,   262,   263,    56,   265,    17,    59,    60,
     298,    62,    63,    17,   273,    60,    60,    72,   265,    51,
     153,   297,    45,    46,    47,    48,    49,   286,   202,   275,
     275,   319,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,   300,    -1,    -1,    -1,    -1,    -1,   325,
     309,   310,   311,    65,   313,   331,    68,    69,    70,    71,
     317,    -1,    -1,    75,    76,    77,    -1,    79,    80,    81,
      82,    -1,    84,    -1,    86,    -1,    -1,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,    -1,   104,   105,   106,   107,   108,    -1,    -1,   111,
     112,   113,    -1,    -1,    -1,   117,    -1,    -1,    -1,    -1,
     122,   123,    -1,   125,   126,   127,   128,   129,   130,   131,
      -1,    -1,   134,   135,   136,    -1,   138,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    17,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    -1,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      46,    -1,    -1,    49,    50,    51,    -1,    -1,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    62,    63,    -1,    65,
      66,    -1,    68,    69,    70,    71,    72,    -1,    74,    75,
      76,    77,    -1,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    -1,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,    -1,   104,   105,
     106,   107,   108,    -1,   110,   111,   112,   113,    -1,   115,
      -1,   117,    -1,   119,    -1,    -1,   122,   123,    -1,   125,
     126,   127,   128,   129,   130,   131,    -1,    -1,   134,   135,
     136,   137,   138,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    46,    -1,    -1,    49,
      50,    51,    56,    -1,    54,    59,    -1,    -1,    62,    63,
      -1,    61,    62,    63,    -1,    65,    66,    -1,    68,    69,
      70,    71,    72,    -1,    74,    75,    76,    77,    -1,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    -1,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,    -1,   104,   105,   106,   107,   108,    -1,
     110,   111,   112,   113,    -1,   115,    -1,   117,    -1,   119,
      -1,    -1,   122,   123,    -1,   125,   126,   127,   128,   129,
     130,   131,    -1,    -1,   134,   135,   136,   137,   138,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    -1,
      -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      -1,    45,    46,    -1,    -1,    49,    50,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,    63,
      -1,    65,    -1,    -1,    68,    69,    70,    71,    -1,    -1,
      -1,    75,    76,    77,     3,    79,    80,    81,    82,    -1,
      84,    -1,    86,    -1,    -1,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,    -1,
     104,   105,   106,   107,   108,    -1,    -1,   111,   112,   113,
      -1,   115,    -1,   117,    -1,    -1,    -1,    -1,   122,   123,
      -1,   125,   126,   127,   128,   129,   130,   131,    -1,    -1,
     134,   135,   136,    -1,   138,    -1,    65,    -1,    -1,    68,
      69,    70,    71,    -1,    -1,    -1,    75,    76,    77,     3,
      79,    80,    81,    82,    -1,    84,    -1,    86,    -1,    -1,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,    -1,   104,   105,   106,   107,   108,
      -1,    -1,   111,   112,   113,    -1,    -1,    -1,   117,    -1,
      -1,    -1,    -1,   122,   123,    -1,   125,   126,   127,   128,
     129,   130,   131,    -1,    -1,   134,   135,   136,    -1,   138,
      -1,    65,    -1,    -1,    68,    69,    70,    71,    -1,    -1,
      -1,    75,    76,    77,     3,    79,    80,    81,    82,    -1,
      84,    -1,    86,    -1,    -1,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,    -1,
     104,   105,   106,   107,   108,    -1,    -1,   111,   112,   113,
      -1,    -1,    -1,   117,    -1,    -1,    -1,    -1,   122,   123,
      -1,   125,   126,   127,   128,   129,   130,   131,    -1,    -1,
     134,   135,   136,    -1,   138,    -1,    65,    -1,    -1,    68,
      69,    70,    71,    -1,    -1,    -1,    75,    76,    77,     3,
      79,    80,    81,    82,    -1,    84,    -1,    86,    -1,    -1,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,    -1,   104,   105,   106,   107,   108,
      -1,    -1,   111,   112,   113,    -1,    -1,    -1,   117,    -1,
      -1,    -1,    -1,   122,   123,    -1,   125,   126,   127,   128,
     129,   130,   131,    -1,    -1,   134,   135,   136,    -1,   138,
      -1,    65,    -1,    -1,    68,    69,    70,    71,    -1,    -1,
      -1,    75,    76,    77,    -1,    79,    80,    81,    82,    -1,
      84,    -1,    86,    -1,    -1,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,    -1,
     104,   105,   106,   107,   108,    -1,    -1,   111,   112,   113,
      -1,    -1,    -1,   117,    -1,    -1,    -1,    -1,   122,   123,
      -1,   125,   126,   127,   128,   129,   130,   131,    -1,    -1,
     134,   135,   136,    -1,   138,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    -1,    -1,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    -1,    45,    46,    -1,
      -1,    49,    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    61,    62,    63,    -1,    65,    -1,    -1,
      68,    69,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,
      -1,    79,    -1,    81,    82,    -1,    -1,    -1,    86,    -1,
      -1,    89,    90,    91,    92,    93,    94,    -1,    96,    97,
      98,    99,   100,    -1,    -1,    -1,   104,    -1,   106,    -1,
      -1,    -1,    -1,   111,   112,   113,    -1,   115,    -1,    -1,
      -1,    -1,    -1,    -1,   122,   123,    -1,   125,   126,   127,
     128,   129,   130,   131,    -1,    -1,   134,   135,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    46,    -1,    -1,    49,    50,    51,    -1,    -1,    54,
      36,    -1,    -1,    -1,    59,    -1,    61,    62,    63,    45,
      46,    -1,    -1,    49,    50,    51,    -1,    -1,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    62,    63,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    -1,
     115,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    46,    -1,    -1,    49,    50,    51,    -1,    -1,   115,
      36,    -1,    -1,    -1,    -1,    -1,    61,    62,    63,    45,
      46,    -1,    -1,    49,    50,    51,    -1,    16,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    62,    63,    -1,    -1,
      -1,    -1,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
     115,    60,    68,    69,    70,    71,    -1,    -1,    -1,    75,
      76,    77,    -1,    79,    80,    81,    82,    -1,    84,   115,
      86,    -1,    -1,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,    -1,   104,   105,
     106,   107,   108,    -1,    -1,   111,   112,   113,    -1,    -1,
      -1,   117,    -1,    -1,    -1,    -1,   122,   123,    -1,   125,
     126,   127,   128,   129,   130,   131,    -1,    -1,   134,   135,
     136,    65,   138,    -1,    68,    69,    -1,    -1,    -1,    -1,
      -1,    75,    76,    77,    -1,    79,    -1,    81,    82,    -1,
      -1,    -1,    86,    -1,    -1,    89,    90,    91,    92,    93,
      94,    -1,    96,    97,    98,    99,   100,    -1,    -1,    -1,
     104,    -1,   106,    -1,    -1,    -1,    -1,   111,   112,   113,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   122,   123,
      -1,   125,   126,   127,   128,   129,   130,   131,    -1,    -1,
     134,   135,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    -1,    -1,    -1,
      -1,    54,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    65,    68,    69,    70,    71,    75,    76,    77,    79,
      80,    81,    82,    84,    86,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   104,
     105,   106,   107,   108,   111,   112,   113,   117,   122,   123,
     125,   126,   127,   128,   129,   130,   131,   134,   135,   136,
     138,   140,   141,   142,   143,   147,   148,   149,   150,   151,
     152,   193,   194,     0,   141,     3,   149,    49,    61,   145,
     146,   147,    16,    60,     3,   146,    17,    54,   144,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      36,    45,    46,    49,    50,    51,    54,    61,    62,    63,
      66,    72,    74,    83,    85,    87,   110,   115,   119,   137,
     142,   143,   147,   153,   154,   156,   157,   162,   163,   164,
     165,   166,   170,   172,   174,   175,   180,   183,   186,   187,
     188,   189,   192,    30,    61,     3,    61,   154,     3,   187,
     187,   154,   187,   187,   153,   154,   187,   193,   154,   154,
      17,    17,   181,    61,     3,    61,   186,    61,   187,    61,
       3,   161,    53,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    56,    59,    62,    63,   155,   153,
      88,   163,    17,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    54,   155,   158,   159,   187,   154,    53,    60,
      60,    60,   163,   147,   162,   186,    17,   187,    17,   193,
      54,   185,    29,   155,   160,    16,    17,   187,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,     3,   187,
      59,   171,   187,   187,   187,   187,   187,   187,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     187,   158,    29,    16,    60,    61,   187,   137,     3,   178,
      17,    60,    60,    67,    73,   167,   168,   169,   187,   159,
     187,   160,     3,    58,   187,   163,    30,    53,   187,   155,
     159,   187,   187,   190,   191,    61,   186,   176,   173,   187,
      30,    53,   168,   169,    60,   155,   160,    58,   187,    29,
      16,    16,    60,   182,    17,   186,   163,    30,   153,   184,
     160,   187,   187,   187,   187,   179,    17,   153,   163,    60,
     186,   177,    17,    60,   186,    60
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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
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
  *++yyvsp = yylval;

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
        case 6:

/* Line 1806 of yacc.c  */
#line 235 "parser.y"
    {
		
		cl2llvm_yyerror("function declarations not supported");
	}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 243 "parser.y"
    {
		int err;
		struct cl2llvm_function_t *new_function;	
		char arg_name[CL2LLVM_MAX_ARG_NAME_LEN];
		LLVMTypeRef func_args[CL2LLVM_MAX_FUNC_ARGS];
		LLVMTypeRef function_type;
		LLVMValueRef function;
		int arg_count;
		int i;

		/* Create name for function entry block */
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		
		arg_count = list_count((yyvsp[(4) - (6)].arg_list));

		/* Check that first argument is not empty.  This step is 
		necessary because of the grammar definition which allows 
		for the first argument of a multi-argument function to be empty. */
		if (list_get((yyvsp[(4) - (6)].arg_list), (yyvsp[(4) - (6)].arg_list)->head) == NULL && arg_count > 1)
				yyerror("expected declaration specifiers or" 
					"'...' before ',' token");
		
		/* Read function arguments and create an array of argument types */
		else if(list_get((yyvsp[(4) - (6)].arg_list), (yyvsp[(4) - (6)].arg_list)->head))
		{
			for (i = 0; i < arg_count; i++)
			{
				
				struct cl2llvm_arg_t *current_arg = list_get(
					(yyvsp[(4) - (6)].arg_list), i);
				if (!current_arg->name)
					yyerror("parameter name omitted");
				func_args[i] = cl2llvmTypeWrapGetLlvmType(current_arg->type_spec);
			}
		}
		else 
			arg_count = 0;

		/* Define function */
		function_type = LLVMFunctionType(
			cl2llvmTypeWrapGetLlvmType((yyvsp[(1) - (6)].decl_list)->type_spec), func_args, arg_count, 0);
		function = LLVMAddFunction(cl2llvm_module, (yyvsp[(2) - (6)].identifier),
			function_type);
		LLVMSetFunctionCallConv(function, LLVMCCallConv);

		/* Create function's variable declaration block */
		LLVMBasicBlockRef basic_block = LLVMAppendBasicBlock( 
			function, block_name);
		
		/* Position builder at start of function */
		LLVMPositionBuilderAtEnd(cl2llvm_builder, basic_block);
			current_basic_block = basic_block;

		/* Create and initialize function object */
		new_function = cl2llvm_function_create((yyvsp[(2) - (6)].identifier), (yyvsp[(4) - (6)].arg_list));

		new_function->func = function;
		new_function->func_type = function_type;
		new_function->sign = cl2llvmTypeWrapGetSign((yyvsp[(1) - (6)].decl_list)->type_spec);
		new_function->entry_block = basic_block;

		/* Set current function to newly created function */
		cl2llvm_current_function = new_function;

		/* Insert function into global symbol table */
		err = hash_table_insert(cl2llvm_symbol_table, 
			(yyvsp[(2) - (6)].identifier), new_function);
		if (!err)
			yyerror("function already defined");
	
		/* Declare parameters if the argument list is not empty*/
		if (list_get((yyvsp[(4) - (6)].arg_list), (yyvsp[(4) - (6)].arg_list)->head))
		{
			for (i = 0; i < arg_count; i++)
			{
				struct cl2llvm_arg_t *current_arg = list_get(
					(yyvsp[(4) - (6)].arg_list), i);

				snprintf(arg_name, sizeof arg_name,
					"%s_addr", current_arg->name);

				struct cl2llvm_val_t *arg_pointer = 
					cl2llvm_val_create_w_init( 
					LLVMBuildAlloca(cl2llvm_builder, 
					cl2llvmTypeWrapGetLlvmType(current_arg->type_spec), 
					arg_name),
					cl2llvmTypeWrapGetSign(current_arg->type_spec));

				struct cl2llvm_symbol_t *symbol = 
					cl2llvm_symbol_create_w_init(
					arg_pointer->val, 
					cl2llvmTypeWrapGetSign(current_arg->type_spec), 
					current_arg->name);

				cl2llvmTypeWrapSetLlvmType(symbol->cl2llvm_val->type, cl2llvmTypeWrapGetLlvmType(current_arg->type_spec));

				/* Name and store arguments */
				LLVMValueRef arg_val = LLVMGetParam(
					new_function->func, i);
				LLVMSetValueName(arg_val, current_arg->name);

				LLVMBuildStore(cl2llvm_builder, arg_val,
					arg_pointer->val);
				hash_table_insert(new_function->symbol_table,
					current_arg->name, symbol);

				/* Free argument */
				cl2llvm_val_free(arg_pointer);
			}
		}
		/* End declaration block and create first instruction block. */
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);

		LLVMBasicBlockRef first_block = LLVMAppendBasicBlock( 
			new_function->func, block_name);
		LLVMValueRef branch = LLVMBuildBr(cl2llvm_builder, 
			first_block);
		LLVMPositionBuilderAtEnd(cl2llvm_builder, first_block);

		/* Set current basic block */
		current_basic_block = first_block;

		/* initialize function branch instruction for building 
		declarations off of */
		new_function->branch_instr = branch;

		/* Free declarator list */
		cl2llvm_decl_list_free((yyvsp[(1) - (6)].decl_list));	
	}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 375 "parser.y"
    {
		/* If function is of type void, create return instruction 
		by default*/
		if (LLVMGetReturnType(cl2llvm_current_function->func_type)
			== LLVMVoidType())
		{
				if (LLVMGetLastInstruction(
					current_basic_block) != NULL)
				{
					if (LLVMGetInstructionOpcode(
						LLVMGetLastInstruction(
						current_basic_block)) != LLVMRet)
						LLVMBuildRetVoid(cl2llvm_builder);
				}
				else
					LLVMBuildRetVoid(cl2llvm_builder);
		}
	}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 399 "parser.y"
    {
		struct cl2llvm_arg_t *empty_arg = NULL;
		struct list_t *arg_list = list_create();
		list_add(arg_list, empty_arg);
		(yyval.arg_list) = arg_list;
	}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 406 "parser.y"
    {
		struct list_t *arg_list = list_create();
		list_add(arg_list, (yyvsp[(1) - (1)].arg_t));
		(yyval.arg_list) = arg_list;
	}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 412 "parser.y"
    {
		list_add((yyvsp[(1) - (3)].arg_list), (yyvsp[(3) - (3)].arg_t));
		(yyval.arg_list) = (yyvsp[(1) - (3)].arg_list);
	}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 420 "parser.y"
    {
		struct cl2llvm_arg_t *arg = cl2llvm_arg_create((yyvsp[(1) - (2)].decl_list), (yyvsp[(2) - (2)].identifier));
		cl2llvm_decl_list_struct_free((yyvsp[(1) - (2)].decl_list));
		(yyval.arg_t) = arg;
	}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 426 "parser.y"
    {
		struct cl2llvm_arg_t *arg = cl2llvm_arg_create((yyvsp[(1) - (1)].decl_list), NULL);
		cl2llvm_decl_list_struct_free((yyvsp[(1) - (1)].decl_list));
		(yyval.arg_t) = arg;
	}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 437 "parser.y"
    {
		(yyval.decl_list) = (yyvsp[(1) - (1)].decl_list);
	}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 441 "parser.y"
    {
		cl2llvm_attach_decl_to_list((yyvsp[(2) - (2)].decl_list), (yyvsp[(1) - (2)].decl_list));
		if ((yyvsp[(1) - (2)].decl_list)->type_spec != NULL && (yyvsp[(2) - (2)].decl_list)->addr_qual != 0)
		{
			switch ((yyvsp[(2) - (2)].decl_list)->addr_qual)
			{
				case 1:
					cl2llvmTypeWrapSetLlvmType((yyvsp[(1) - (2)].decl_list)->type_spec, LLVMPointerType(
						LLVMGetElementType(cl2llvmTypeWrapGetLlvmType((yyvsp[(1) - (2)].decl_list)->type_spec)), 1));
					break;
					
				case 2:
					cl2llvmTypeWrapSetLlvmType((yyvsp[(1) - (2)].decl_list)->type_spec, LLVMPointerType(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType((yyvsp[(1) - (2)].decl_list)->type_spec)), 2));
						break;

				default:
					break;
			}
		}
		if ((yyvsp[(1) - (2)].decl_list)->addr_qual != 0 && (yyvsp[(2) - (2)].decl_list)->type_spec != NULL)
		{
			switch ((yyvsp[(1) - (2)].decl_list)->addr_qual)
			{
				case 1:
					cl2llvmTypeWrapSetLlvmType((yyvsp[(1) - (2)].decl_list)->type_spec, LLVMPointerType(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType((yyvsp[(2) - (2)].decl_list)->type_spec)), 1));
						break;
					
				case 2:
					cl2llvmTypeWrapSetLlvmType((yyvsp[(1) - (2)].decl_list)->type_spec, LLVMPointerType(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType((yyvsp[(2) - (2)].decl_list)->type_spec)), 2));
						break;

				default:
					break;
			}
		}
		cl2llvm_decl_list_struct_free((yyvsp[(2) - (2)].decl_list));
		(yyval.decl_list) = (yyvsp[(1) - (2)].decl_list);
	}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 483 "parser.y"
    {
		(yyval.const_int_val) = 1;
	}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 487 "parser.y"
    {
		(yyval.const_int_val) = 3;
	}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 491 "parser.y"
    {
		(yyval.const_int_val) = 0;
	}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 495 "parser.y"
    {
		cl2llvm_yyerror("'constant' not supported");
		(yyval.const_int_val) = 0;
	}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 503 "parser.y"
    {
		struct cl2llvm_decl_list_t *decl_list = cl2llvm_decl_list_create();
		decl_list->type_spec = (yyvsp[(1) - (1)].llvm_type_ref);
		(yyval.decl_list) = decl_list;
	}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 509 "parser.y"
    {
		struct cl2llvm_decl_list_t *decl_list = cl2llvm_decl_list_create();
		decl_list->access_qual = NULL;
		(yyval.decl_list) = decl_list;
	}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 515 "parser.y"
    {
		struct cl2llvm_decl_list_t *decl_list = cl2llvm_decl_list_create();
		decl_list->kernel_t = 	"kernel";
		(yyval.decl_list) = decl_list;
	}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 521 "parser.y"
    {
		struct cl2llvm_decl_list_t *decl_list = cl2llvm_decl_list_create();
		decl_list->inline_t = NULL;
		(yyval.decl_list) = decl_list;
	}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 527 "parser.y"
    {
		struct cl2llvm_decl_list_t *decl_list = cl2llvm_decl_list_create();
		decl_list->sc_spec = NULL;
		(yyval.decl_list) = decl_list;

	}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 534 "parser.y"
    {
		struct cl2llvm_decl_list_t *decl_list = cl2llvm_decl_list_create();
		decl_list->addr_qual = (yyvsp[(1) - (1)].const_int_val);
		(yyval.decl_list) = decl_list;
	}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 540 "parser.y"
    {
		struct cl2llvm_decl_list_t *decl_list = cl2llvm_decl_list_create();
		decl_list->type_qual = NULL;
		(yyval.decl_list) = decl_list;
	}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 549 "parser.y"
    {
		cl2llvm_warning("const not supported");
	}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 564 "parser.y"
    {
		cl2llvm_yyerror("'extern' not supported");
	}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 568 "parser.y"
    {
		cl2llvm_yyerror("'static' not supported");
	}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 580 "parser.y"
    {
		(yyval.llvm_value_ref) = (yyvsp[(2) - (3)].llvm_value_ref);
	}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 584 "parser.y"
    {
		struct cl2llvm_val_t *ptr;
		int i;
		struct cl2llvm_val_t *current_index;
		LLVMValueRef deref_ptr;
		LLVMValueRef indices[CL2LLVM_MAX_NUM_ARRAY_INDEX_DIM];

		/*Retrieve symbol from table*/
	 	/*symbol = hash_table_get(cl2llvm_current_function->symbol_table, $1);
		if (symbol == NULL)	
			yyerror("symbol undeclared first use in this program");*/
		
		deref_ptr = (yyvsp[(1) - (2)].llvm_value_ref)->val;

		/* Loop through all dereference operators */	
		for (i = 0; i < list_count((yyvsp[(2) - (2)].list_val_t)); i++)
		{
			if  (LLVMGetTypeKind(LLVMGetElementType(LLVMTypeOf(
				deref_ptr))) == LLVMPointerTypeKind)
			{
				snprintf(temp_var_name, sizeof temp_var_name,
					"tmp_%d", temp_var_count++);
			
				deref_ptr = LLVMBuildLoad(cl2llvm_builder, 
					deref_ptr, temp_var_name);

				current_index = list_get((yyvsp[(2) - (2)].list_val_t), i);
				indices[0] = current_index->val;

				snprintf(temp_var_name, sizeof temp_var_name,
					"tmp_%d", temp_var_count++);
				deref_ptr = LLVMBuildGEP(cl2llvm_builder, 
					deref_ptr, indices, 1, 
					temp_var_name);
				
			}
			else if (LLVMGetTypeKind(LLVMGetElementType(LLVMTypeOf(
				deref_ptr))) == LLVMArrayTypeKind)

			{
				indices[0] = LLVMConstInt(LLVMInt32Type(), 0, 0);
				indices[1] = LLVMConstInt(LLVMInt32Type(), 0, 0);
				
				snprintf(temp_var_name, sizeof temp_var_name,
					"tmp_%d", temp_var_count++);
				
				deref_ptr = LLVMBuildGEP(cl2llvm_builder, 
					deref_ptr, indices, 2, temp_var_name); 

				current_index = list_get((yyvsp[(2) - (2)].list_val_t), i);
				indices[0] = current_index->val;
				

				/* Get element pointer */
				snprintf(temp_var_name, sizeof temp_var_name,
					"tmp_%d", temp_var_count++);

				deref_ptr = LLVMBuildGEP(cl2llvm_builder, 
					deref_ptr, indices, 1, temp_var_name);
			}
			else
				cl2llvm_yyerror("Subscripted value is neither array nor pointer");
		}

		ptr = cl2llvm_val_create_w_init(deref_ptr, 
			cl2llvmTypeWrapGetSign((yyvsp[(1) - (2)].llvm_value_ref)->type));

		/*Free pointers*/
		LIST_FOR_EACH((yyvsp[(2) - (2)].list_val_t), i)
		{
			cl2llvm_val_free(list_get((yyvsp[(2) - (2)].list_val_t), i));
		}
		list_free((yyvsp[(2) - (2)].list_val_t));
		cl2llvm_val_free((yyvsp[(1) - (2)].llvm_value_ref));

		(yyval.llvm_value_ref) = ptr;
	}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 662 "parser.y"
    {
		struct cl2llvm_val_t *ptr;
		LLVMValueRef deref_ptr;
		LLVMValueRef indices[CL2LLVM_MAX_NUM_ARRAY_INDEX_DIM];

		deref_ptr = (yyvsp[(2) - (2)].llvm_value_ref)->val;

		if  (LLVMGetTypeKind(LLVMGetElementType(LLVMTypeOf(
			deref_ptr))) == LLVMPointerTypeKind)
		{
			snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
			
			deref_ptr = LLVMBuildLoad(cl2llvm_builder, 
				deref_ptr, temp_var_name);

		}
		else if (LLVMGetTypeKind(LLVMGetElementType(LLVMTypeOf(
			deref_ptr))) == LLVMArrayTypeKind)

		{
			indices[0] = LLVMConstInt(LLVMInt32Type(), 0, 0);
			indices[1] = LLVMConstInt(LLVMInt32Type(), 0, 0);
				
			snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
				
			deref_ptr = LLVMBuildGEP(cl2llvm_builder, 
				deref_ptr, indices, 2, temp_var_name); 

			indices[0] = LLVMConstInt(LLVMInt32Type(), 0, 0);
				
			/* Get element pointer */
			snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);

			deref_ptr = LLVMBuildGEP(cl2llvm_builder, 
				deref_ptr, indices, 1, temp_var_name);
		}
		else
			cl2llvm_yyerror("Invalid type argument of unary '*'.");
		

		ptr = cl2llvm_val_create_w_init(deref_ptr, 
			cl2llvmTypeWrapGetSign((yyvsp[(2) - (2)].llvm_value_ref)->type));

		cl2llvm_val_free((yyvsp[(2) - (2)].llvm_value_ref));

		(yyval.llvm_value_ref) = ptr;
	}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 713 "parser.y"
    {
		struct cl2llvm_symbol_t *symbol;
		struct cl2llvm_val_t *symbol_val_dup;

		/* Access symbol from symbol table */
		symbol = hash_table_get(cl2llvm_current_function->symbol_table, (yyvsp[(1) - (1)].identifier));
		if (!symbol)
			yyerror("undefined identifier");

		/*Duplicate symbol*/
		symbol_val_dup = cl2llvm_val_create_w_init(symbol->cl2llvm_val->val, 
			cl2llvmTypeWrapGetSign(symbol->cl2llvm_val->type));


		(yyval.llvm_value_ref) = symbol_val_dup;
	}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 730 "parser.y"
    {

		
		/* Get symbol from hash table */
	/*	symbol = hash_table_get(cl2llvm_current_function->symbol_table, $1);
		if (!symbol)	
			yyerror("symbol undeclared first use in this program");
*/

		/* If symbol is a vector retrieve the specified indices */
		if (LLVMGetTypeKind(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType((yyvsp[(1) - (3)].llvm_value_ref)->type)))
			== LLVMVectorTypeKind)
		{	
			cl2llvm_get_vector_indices((yyvsp[(1) - (3)].llvm_value_ref), (yyvsp[(3) - (3)].identifier));
		}
		(yyval.llvm_value_ref) = (yyvsp[(1) - (3)].llvm_value_ref);
	}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 751 "parser.y"
    {
		struct list_t *array_deref_list = list_create();
		
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType((yyvsp[(2) - (3)].llvm_value_ref)->type)) != LLVMIntegerTypeKind)
			yyerror("array index is not an integer");
		list_add(array_deref_list, (yyvsp[(2) - (3)].llvm_value_ref));
		(yyval.list_val_t) = array_deref_list;
	}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 760 "parser.y"
    {
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType((yyvsp[(3) - (4)].llvm_value_ref)->type)) != LLVMIntegerTypeKind)
			yyerror("array index is not an integer");
		list_add((yyvsp[(1) - (4)].list_val_t), (yyvsp[(3) - (4)].llvm_value_ref));
		(yyval.list_val_t) = (yyvsp[(1) - (4)].list_val_t);
	}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 770 "parser.y"
    {
		if ((yyvsp[(1) - (2)].llvm_value_ref) != NULL)
			cl2llvm_val_free((yyvsp[(1) - (2)].llvm_value_ref));
	}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 782 "parser.y"
    {
		struct cl2llvm_val_t *ret_val;
		struct cl2llvmTypeWrap *type = cl2llvmTypeWrapCreate( LLVMGetReturnType(cl2llvm_current_function->func_type), cl2llvm_current_function->sign);
		if (cl2llvmTypeWrapGetLlvmType(type) == LLVMVoidType())
		{
			if ((yyvsp[(2) - (3)].llvm_value_ref) == NULL)
			{
				LLVMBuildRetVoid(cl2llvm_builder);
			}
			else
				cl2llvm_yyerror("returning a value to a void function");
		}
		else
		{
			if (cl2llvmTypeWrapGetLlvmType(type) != cl2llvmTypeWrapGetLlvmType((yyvsp[(2) - (3)].llvm_value_ref)->type) || cl2llvmTypeWrapGetSign(type) != cl2llvmTypeWrapGetSign((yyvsp[(2) - (3)].llvm_value_ref)->type))
				ret_val = llvm_type_cast((yyvsp[(2) - (3)].llvm_value_ref), type);
			else
				ret_val = (yyvsp[(2) - (3)].llvm_value_ref);
		
			LLVMBuildRet(cl2llvm_builder, ret_val->val);
			cl2llvmTypeWrapFree(type);
	
			if (ret_val != (yyvsp[(2) - (3)].llvm_value_ref))
				cl2llvm_val_free(ret_val);
			cl2llvm_val_free((yyvsp[(2) - (3)].llvm_value_ref));
		}
	}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 810 "parser.y"
    {
		cl2llvm_yyerror("'continue' not supported");
	}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 814 "parser.y"
    {
		cl2llvm_yyerror("'break' not supported");
	}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 818 "parser.y"
    {
		cl2llvm_yyerror("'switch' not supported");
	}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 822 "parser.y"
    {
		cl2llvm_yyerror("'label statements not supported");
	}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 826 "parser.y"
    {
		cl2llvm_yyerror("'goto' not supported");
	}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 833 "parser.y"
    {
		int i;
		LLVMValueRef cast_param_array[100];
		struct cl2llvm_arg_t *current_func_arg;
		struct cl2llvm_val_t *current_param;
		struct cl2llvm_function_t *function;
		struct cl2llvmTypeWrap *type;
		struct cl2llvm_val_t *cast_param;
		LLVMValueRef llvm_val_func_ret;
		struct cl2llvm_val_t *ret_val;

		/* If function is found in the built-in function table but not the
		   global symbol table, declare it and insert it into the  global
		   symbol table. */
		if (hash_table_get(cl2llvm_built_in_func_table, (yyvsp[(1) - (4)].identifier)))
			cl2llvm_built_in_func_analyze((yyvsp[(1) - (4)].identifier), (yyvsp[(3) - (4)].list_val_t));
	
		/* Retrieve function specs from sybmol table */
		function = hash_table_get(cl2llvm_symbol_table, (yyvsp[(1) - (4)].identifier));
		if (!function)
			yyerror("implicit declaration of function");
		
		/* check that parameter types match */
		for (i = 0; i < function->arg_count; i++)
		{
			current_func_arg = list_get(function->arg_list, i);
			current_param = list_get((yyvsp[(3) - (4)].list_val_t), i);
			if (current_func_arg == NULL)
				cast_param_array[i] = NULL;
			else if (cl2llvmTypeWrapGetLlvmType(current_func_arg->type_spec) 
				!= cl2llvmTypeWrapGetLlvmType(current_param->type))
			{
				type = cl2llvmTypeWrapCreate( 
					cl2llvmTypeWrapGetLlvmType(current_func_arg->type_spec),
					cl2llvmTypeWrapGetSign(current_func_arg->type_spec));
				cast_param = llvm_type_cast(current_param, type);
				cl2llvmTypeWrapFree(type);
				cast_param_array[i] = cast_param->val;
				cl2llvm_val_free(current_param);
				cl2llvm_val_free(cast_param);
			}
			else
			{
				cast_param_array[i] = current_param->val;
				cl2llvm_val_free(current_param);
			}
		}
		list_free((yyvsp[(3) - (4)].list_val_t));


		/* Build function call */
		if (LLVMGetReturnType(function->func_type) == LLVMVoidType())
		{
			llvm_val_func_ret = LLVMBuildCall(cl2llvm_builder, function->func,
				cast_param_array, function->arg_count, "");
		}
		else
		{
			snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);

			llvm_val_func_ret = LLVMBuildCall(cl2llvm_builder, function->func,
				cast_param_array, function->arg_count, temp_var_name);
		}

		/* Create return value */
		ret_val = cl2llvm_val_create_w_init(llvm_val_func_ret, 	
			function->sign);
		
		(yyval.llvm_value_ref) = ret_val;
	}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 908 "parser.y"
    {
		struct list_t *param_list = list_create();
		list_add(param_list, NULL);
		(yyval.list_val_t) = param_list;
	}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 914 "parser.y"
    {
		struct list_t *param_list = list_create();
		list_add(param_list, (yyvsp[(1) - (1)].llvm_value_ref));
		(yyval.list_val_t) = param_list;
	}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 920 "parser.y"
    {
		cl2llvm_yyerror("array initializers not supported");
		(yyval.list_val_t) = NULL;
	}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 925 "parser.y"
    {
		cl2llvm_yyerror("array initializers not supported");
		(yyval.list_val_t) = NULL;
	}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 930 "parser.y"
    {
		list_add((yyvsp[(1) - (3)].list_val_t), (yyvsp[(3) - (3)].llvm_value_ref));
		(yyval.list_val_t) = (yyvsp[(1) - (3)].list_val_t);
	}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 935 "parser.y"
    {
		cl2llvm_yyerror("array initializers not supported");
		(yyval.list_val_t) = NULL;
	}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 940 "parser.y"
    {
		cl2llvm_yyerror("array initializers not supported");
		(yyval.list_val_t) = NULL;
	}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 952 "parser.y"
    {
		(yyval.llvm_value_ref) = NULL;
	}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 956 "parser.y"
    {
		(yyval.llvm_value_ref) = (yyvsp[(2) - (2)].llvm_value_ref);
	}
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 960 "parser.y"
    {
		cl2llvm_yyerror("array initializers not supported");
		(yyval.llvm_value_ref) = NULL;
	}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 968 "parser.y"
    {
		struct list_t *init_list = list_create();
		struct cl2llvm_init_t *init = cl2llvm_init_create((yyvsp[(1) - (2)].identifier));

		cl2llvm_val_free(init->cl2llvm_val);
		init->cl2llvm_val = (yyvsp[(2) - (2)].llvm_value_ref);

		list_add(init_list, init);
		(yyval.init_list) = init_list;
	}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 979 "parser.y"
    {
		struct cl2llvm_init_t *init = cl2llvm_init_create((yyvsp[(3) - (4)].identifier));

		cl2llvm_val_free(init->cl2llvm_val);
		init->cl2llvm_val = (yyvsp[(4) - (4)].llvm_value_ref);

		list_add((yyvsp[(1) - (4)].init_list), init);
		(yyval.init_list) = (yyvsp[(1) - (4)].init_list);
	}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 989 "parser.y"
    {
		struct list_t *init_list = list_create();
		struct cl2llvm_init_t *init = cl2llvm_init_create((yyvsp[(1) - (3)].identifier));

		cl2llvm_val_free(init->cl2llvm_val);
		init->cl2llvm_val = (yyvsp[(3) - (3)].llvm_value_ref);
		init->array_deref_list = (yyvsp[(2) - (3)].list_val_t);

		list_add(init_list, init);
		(yyval.init_list) = init_list;

	}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 1002 "parser.y"
    {
		struct cl2llvm_init_t *init = cl2llvm_init_create((yyvsp[(3) - (5)].identifier));

		cl2llvm_val_free(init->cl2llvm_val);
		init->cl2llvm_val = (yyvsp[(5) - (5)].llvm_value_ref);
		init->array_deref_list = (yyvsp[(4) - (5)].list_val_t);

		list_add((yyvsp[(1) - (5)].init_list), init);
		(yyval.init_list) = (yyvsp[(1) - (5)].init_list);
	}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 1017 "parser.y"
    {
		struct cl2llvm_val_t *cl2llvm_index;
		LLVMTypeRef type;
		struct cl2llvm_val_t *ptr;
		struct cl2llvm_val_t *value;
		int i;
		struct cl2llvm_symbol_t *symbol;
		struct cl2llvm_val_t *cast_to_val;
		int init_count = list_count((yyvsp[(2) - (3)].init_list));
		struct cl2llvm_init_t *current_list_elem;
		struct cl2llvm_symbol_t *err_symbol;
		char error_message[50];
		LLVMValueRef var_addr;

		/*Create each sybmol in the init_list*/
		for(i = 0; i < init_count; i++)
		{	
			int err;			
			current_list_elem = list_get((yyvsp[(2) - (3)].init_list), i);			
			
			/*if variable type is a vector*/
			if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType((yyvsp[(1) - (3)].decl_list)->type_spec)) == LLVMVectorTypeKind)
			{	
				/*Go to entry block and declare variable*/
				LLVMPositionBuilder(cl2llvm_builder, cl2llvm_current_function->entry_block, cl2llvm_current_function->branch_instr);
				var_addr = LLVMBuildAlloca(cl2llvm_builder, 
					cl2llvmTypeWrapGetLlvmType((yyvsp[(1) - (3)].decl_list)->type_spec), current_list_elem->name);
				LLVMPositionBuilderAtEnd(cl2llvm_builder, current_basic_block);

				/*Create symbol*/
				symbol = cl2llvm_symbol_create_w_init( var_addr, 
					cl2llvmTypeWrapGetSign((yyvsp[(1) - (3)].decl_list)->type_spec), current_list_elem->name);
				
				/* If initializer is present, store it. */
				if (current_list_elem->cl2llvm_val != NULL)
				{

					if (LLVMTypeOf(current_list_elem->cl2llvm_val->val) == cl2llvmTypeWrapGetLlvmType((yyvsp[(1) - (3)].decl_list)->type_spec) 
						&& cl2llvmTypeWrapGetSign(current_list_elem->cl2llvm_val->type) == cl2llvmTypeWrapGetSign((yyvsp[(1) - (3)].decl_list)->type_spec))
					{
						LLVMBuildStore(cl2llvm_builder, 
							current_list_elem->cl2llvm_val->val, var_addr);
					}
					else 
					{
						yyerror("type of vector initializer does not match type of declarator");
					}
				}
			}
			/*If data type is not an array*/
			else if (current_list_elem->array_deref_list == NULL)
			{
				/*Go to entry block and declare variable*/
				LLVMPositionBuilder(cl2llvm_builder, cl2llvm_current_function->entry_block, cl2llvm_current_function->branch_instr);
				var_addr = LLVMBuildAlloca(cl2llvm_builder, 
					cl2llvmTypeWrapGetLlvmType((yyvsp[(1) - (3)].decl_list)->type_spec), current_list_elem->name);
				LLVMPositionBuilderAtEnd(cl2llvm_builder, current_basic_block);

				/*Create symbol*/
				symbol = cl2llvm_symbol_create_w_init( var_addr, 
					cl2llvmTypeWrapGetSign((yyvsp[(1) - (3)].decl_list)->type_spec), current_list_elem->name);
				cl2llvmTypeWrapSetLlvmType(symbol->cl2llvm_val->type, cl2llvmTypeWrapGetLlvmType((yyvsp[(1) - (3)].decl_list)->type_spec));

				
				/*If initializer is present, cast initializer to declarator 
				  type and store*/
				if (current_list_elem->cl2llvm_val != NULL)
				{
					cast_to_val = llvm_type_cast( 
						current_list_elem->cl2llvm_val, 
						(yyvsp[(1) - (3)].decl_list)->type_spec);
					LLVMBuildStore(cl2llvm_builder, cast_to_val->val, 
						symbol->cl2llvm_val->val);
					cl2llvm_val_free(cast_to_val);
				}
			}
			/*If init is an array*/
			else
			{		
				int i;
				int j;
				
				/* Check that array sizes are constants */
				for (i = 0; i < list_count(
					current_list_elem->array_deref_list); i++)
				{	
					value = list_get(current_list_elem->array_deref_list, i);
					if (!LLVMIsConstant(value->val))
						cl2llvm_yyerror("Array size must be a constant.");
				}

				/* Create type for pointer to array. */
				type = cl2llvmTypeWrapGetLlvmType((yyvsp[(1) - (3)].decl_list)->type_spec);

				for (i = 0; i < list_count(
					current_list_elem->array_deref_list); i++)
				{
					cl2llvm_index = list_get(current_list_elem->array_deref_list, i);
					j = 0;
					while(LLVMConstInt(LLVMInt1Type() ,1 ,0) 
						== LLVMConstICmp(LLVMIntSLT, 
						LLVMConstInt(LLVMInt32Type(), j,
						0), cl2llvm_index->val))
					{
						j++;
					}

					type = LLVMArrayType(type, j);
				}
				
				/* if array is not stored in private memory */
				if((yyvsp[(1) - (3)].decl_list)->addr_qual)
				{
					char local_name[200];
					snprintf(local_name, sizeof(local_name),
						"aclocal_%s", current_list_elem->name);
					ptr = cl2llvm_val_create_w_init(LLVMAddGlobalInAddressSpace(cl2llvm_module, type, local_name, (yyvsp[(1) - (3)].decl_list)->addr_qual), cl2llvmTypeWrapGetSign((yyvsp[(1) - (3)].decl_list)->type_spec));
				}
				else
				{
				/* Go to entry block and allocate array pointer */
				LLVMPositionBuilder(cl2llvm_builder,
					cl2llvm_current_function->entry_block,
					cl2llvm_current_function->branch_instr);

				ptr = cl2llvm_val_create_w_init( LLVMBuildAlloca( 
					cl2llvm_builder, type,
					current_list_elem->name), 
					cl2llvmTypeWrapGetSign((yyvsp[(1) - (3)].decl_list)->type_spec));
	
				LLVMPositionBuilderAtEnd(cl2llvm_builder,
					current_basic_block);


				}
				/* Create symbol */
				symbol = cl2llvm_symbol_create_w_init( 
					ptr->val , cl2llvmTypeWrapGetSign((yyvsp[(1) - (3)].decl_list)->type_spec), 
					current_list_elem->name);

				
				cl2llvm_val_free(ptr);

			}
			
			/* Insert symbol into symbol table */
			err = hash_table_insert(cl2llvm_current_function->symbol_table, 
				current_list_elem->name, symbol);
			if (!err)
			{
				snprintf(error_message, sizeof error_message,
					"Symbol '%s' previously declared.", current_list_elem->name);

				cl2llvm_yyerror(error_message);
			}
			/* Check that symbol is not a reserved constant */
			err_symbol = hash_table_get(cl2llvm_built_in_const_table, 
				current_list_elem->name);
			if (err_symbol)
			{
				snprintf(error_message, sizeof error_message,
					"'%s' expected an identifier.", current_list_elem->name);
				cl2llvm_yyerror(error_message);
			}

		}

		/* Free pointers */
		cl2llvm_decl_list_free((yyvsp[(1) - (3)].decl_list));
		LIST_FOR_EACH((yyvsp[(2) - (3)].init_list), i)
		{
			cl2llvm_init_free(list_get((yyvsp[(2) - (3)].init_list), i));
		}
		list_free((yyvsp[(2) - (3)].init_list));
	}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 1228 "parser.y"
    {
		/* goto endif block*/
		if (check_for_ret());
			LLVMBuildBr(cl2llvm_builder, (yyvsp[(1) - (1)].basic_block_ref));
		LLVMPositionBuilderAtEnd(cl2llvm_builder, (yyvsp[(1) - (1)].basic_block_ref));
		current_basic_block = (yyvsp[(1) - (1)].basic_block_ref);
	}
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 1236 "parser.y"
    { 
		/*create endif block. $1 now becomes the if false block*/
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef endif = LLVMAppendBasicBlock(cl2llvm_current_function->func, block_name);
		
		/*Branch to endif*/
		if (check_for_ret())
			LLVMBuildBr(cl2llvm_builder, endif);
		/*position builder at if false block*/
		LLVMPositionBuilderAtEnd(cl2llvm_builder, (yyvsp[(1) - (2)].basic_block_ref));
		current_basic_block = (yyvsp[(1) - (2)].basic_block_ref);

		(yyval.basic_block_ref) = endif;
	}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 1252 "parser.y"
    {
		/*branch to endif block and prepare to write code for endif block*/
		if (check_for_ret())
			LLVMBuildBr(cl2llvm_builder, (yyvsp[(3) - (4)].basic_block_ref));
		LLVMPositionBuilderAtEnd(cl2llvm_builder, (yyvsp[(3) - (4)].basic_block_ref));
		current_basic_block = (yyvsp[(3) - (4)].basic_block_ref);

	}
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 1264 "parser.y"
    {
		struct cl2llvmTypeWrap *i1 = cl2llvmTypeWrapCreate(LLVMInt1Type(), 1);
		
		/*Create endif block*/
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef endif = LLVMAppendBasicBlock(cl2llvm_current_function->func, block_name);
		
		/*Create if true block*/
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef if_true = LLVMAppendBasicBlock(
			cl2llvm_current_function->func, block_name);
		
		/*evaluate expression*/
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType((yyvsp[(3) - (4)].llvm_value_ref)->type)) == LLVMVectorTypeKind)
			cl2llvm_yyerror("expression must have arithmetic, enum "
				"or pointer type");
		struct cl2llvm_val_t *bool_val =  cl2llvm_to_bool_ne_0((yyvsp[(3) - (4)].llvm_value_ref));
		LLVMBuildCondBr(cl2llvm_builder, bool_val->val, if_true, endif);
		(yyval.basic_block_ref) = endif;
		
		/*prepare to write if_true block*/
		LLVMPositionBuilderAtEnd(cl2llvm_builder, if_true);
		current_basic_block = if_true;
	
		cl2llvm_val_free(bool_val);
		cl2llvm_val_free((yyvsp[(3) - (4)].llvm_value_ref));
		cl2llvmTypeWrapFree(i1);
	}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 1295 "parser.y"
    {
		(yyval.basic_block_ref) = (yyvsp[(5) - (6)].basic_block_ref);
	}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 1302 "parser.y"
    {
		/*Finish for loop statement*/
		LLVMBuildBr(cl2llvm_builder, (yyvsp[(1) - (2)].llvm_for_blocks)->for_incr);

		/*Prepare to build for end*/
		LLVMPositionBuilderAtEnd(cl2llvm_builder, (yyvsp[(1) - (2)].llvm_for_blocks)->for_end);
		current_basic_block = (yyvsp[(1) - (2)].llvm_for_blocks)->for_end;

		/*Free for_blocks*/
		cl2llvm_for_blocks_free((yyvsp[(1) - (2)].llvm_for_blocks));

	}
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 1318 "parser.y"
    {
		struct cl2llvm_for_blocks_t *for_blocks;
		
		/*Initialize "for" blocks*/
		for_blocks = cl2llvm_for_blocks_create();
		
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef for_cond = LLVMAppendBasicBlock(cl2llvm_current_function->func,
			block_name);
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef for_stmt = LLVMAppendBasicBlock(cl2llvm_current_function->func,
			block_name);
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef for_incr = LLVMAppendBasicBlock(cl2llvm_current_function->func,
			block_name);
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef for_end = LLVMAppendBasicBlock(cl2llvm_current_function->func, 
			block_name);

		for_blocks->for_cond = for_cond;
		for_blocks->for_stmt = for_stmt;
		for_blocks->for_incr = for_incr;
		for_blocks->for_end = for_end;

		/*Prepare to build for loop conditional*/
		LLVMBuildBr(cl2llvm_builder, for_blocks->for_cond);
		LLVMPositionBuilderAtEnd(cl2llvm_builder, for_blocks->for_cond);

		(yyval.llvm_for_blocks) = for_blocks;
	}
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 1353 "parser.y"
    {
		struct cl2llvm_val_t *bool_val = NULL;

		/*Build for loop conditional*/
		if ((yyvsp[(6) - (7)].llvm_value_ref) != NULL)
		{
			if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType((yyvsp[(6) - (7)].llvm_value_ref)->type))
				== LLVMVectorTypeKind)
				cl2llvm_yyerror("expression must have "
					"arithmetic, enum or pointer type");
			bool_val = cl2llvm_to_bool_ne_0((yyvsp[(6) - (7)].llvm_value_ref));
			LLVMBuildCondBr(cl2llvm_builder, bool_val->val, 
				(yyvsp[(5) - (7)].llvm_for_blocks)->for_stmt, (yyvsp[(5) - (7)].llvm_for_blocks)->for_end);	
		}
		else
		{
			LLVMBuildBr(cl2llvm_builder, (yyvsp[(5) - (7)].llvm_for_blocks)->for_stmt);
		}
		
		/*Prepare to build for loop increment*/
		LLVMPositionBuilderAtEnd(cl2llvm_builder, (yyvsp[(5) - (7)].llvm_for_blocks)->for_incr);

			
		/*Free pointers*/
		if (bool_val != NULL)
			cl2llvm_val_free(bool_val);
		if ((yyvsp[(3) - (7)].llvm_value_ref) != NULL)
			cl2llvm_val_free((yyvsp[(3) - (7)].llvm_value_ref));
		if ((yyvsp[(6) - (7)].llvm_value_ref) != NULL)
			cl2llvm_val_free((yyvsp[(6) - (7)].llvm_value_ref));
	}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 1385 "parser.y"
    {
		/*Finish for loop increment*/
		LLVMBuildBr(cl2llvm_builder, (yyvsp[(5) - (10)].llvm_for_blocks)->for_cond);
			
		/*Prepare to build for loop statements*/
		LLVMPositionBuilderAtEnd(cl2llvm_builder, (yyvsp[(5) - (10)].llvm_for_blocks)->for_stmt);
		current_basic_block = (yyvsp[(5) - (10)].llvm_for_blocks)->for_stmt;

		/*Free pointers*/
		if ((yyvsp[(9) - (10)].llvm_value_ref) != NULL)
			cl2llvm_val_free((yyvsp[(9) - (10)].llvm_value_ref));

		(yyval.llvm_for_blocks) = (yyvsp[(5) - (10)].llvm_for_blocks);
	}
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 1400 "parser.y"
    {
		struct cl2llvm_for_blocks_t *for_blocks;
		
		/*Initialize "for" blocks*/
		for_blocks = cl2llvm_for_blocks_create();
		
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef for_cond = LLVMAppendBasicBlock(cl2llvm_current_function->func,
			block_name);
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef for_stmt = LLVMAppendBasicBlock(cl2llvm_current_function->func,
			block_name);
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef for_incr = LLVMAppendBasicBlock(cl2llvm_current_function->func,
			block_name);
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef for_end = LLVMAppendBasicBlock(cl2llvm_current_function->func, 
			block_name);

		for_blocks->for_cond = for_cond;
		for_blocks->for_stmt = for_stmt;
		for_blocks->for_incr = for_incr;
		for_blocks->for_end = for_end;

		/*Prepare to build for loop conditional*/
		LLVMBuildBr(cl2llvm_builder, for_blocks->for_cond);
		LLVMPositionBuilderAtEnd(cl2llvm_builder, for_blocks->for_cond);

		(yyval.llvm_for_blocks) = for_blocks;
		
	}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 1436 "parser.y"
    {
		struct cl2llvm_val_t *bool_val = NULL;

		/*Build for loop conditional*/
		if ((yyvsp[(5) - (6)].llvm_value_ref) != NULL)
		{
			if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType((yyvsp[(5) - (6)].llvm_value_ref)->type))
				== LLVMVectorTypeKind)
				cl2llvm_yyerror("expression must have "
					"arithmetic, enum or pointer type");
			bool_val = cl2llvm_to_bool_ne_0((yyvsp[(5) - (6)].llvm_value_ref));
			LLVMBuildCondBr(cl2llvm_builder, bool_val->val, 
				(yyvsp[(4) - (6)].llvm_for_blocks)->for_stmt, (yyvsp[(4) - (6)].llvm_for_blocks)->for_end);
		}
		else
		{
			LLVMBuildBr(cl2llvm_builder, (yyvsp[(4) - (6)].llvm_for_blocks)->for_stmt);
		}

		/*Prepare to build for loop increment*/
		LLVMPositionBuilderAtEnd(cl2llvm_builder, (yyvsp[(4) - (6)].llvm_for_blocks)->for_incr);
		
		/*Free pointers*/
		if (bool_val != NULL)
			cl2llvm_val_free(bool_val);
		if ((yyvsp[(5) - (6)].llvm_value_ref) != NULL)
			cl2llvm_val_free((yyvsp[(5) - (6)].llvm_value_ref));
		
	}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 1466 "parser.y"
    {
		LLVMBuildBr(cl2llvm_builder, (yyvsp[(4) - (9)].llvm_for_blocks)->for_cond);

		/*Prepare to build for loop statements*/
		LLVMPositionBuilderAtEnd(cl2llvm_builder, (yyvsp[(4) - (9)].llvm_for_blocks)->for_stmt);
		current_basic_block = (yyvsp[(4) - (9)].llvm_for_blocks)->for_stmt;
		/*Free pointers*/
		if ((yyvsp[(8) - (9)].llvm_value_ref) != NULL)
			cl2llvm_val_free((yyvsp[(8) - (9)].llvm_value_ref));

		(yyval.llvm_for_blocks) = (yyvsp[(4) - (9)].llvm_for_blocks);

	}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 1483 "parser.y"
    {
		struct cl2llvm_while_blocks_t *while_blocks = cl2llvm_while_blocks_create();

		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef while_stmt = LLVMAppendBasicBlock(cl2llvm_current_function->func, block_name);

		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef while_cond = LLVMAppendBasicBlock(cl2llvm_current_function->func, block_name);
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef while_end = LLVMAppendBasicBlock(cl2llvm_current_function->func, block_name);
		
		LLVMBuildBr(cl2llvm_builder, while_stmt);
		LLVMPositionBuilderAtEnd(cl2llvm_builder, while_stmt);
		current_basic_block = while_stmt;

		while_blocks->while_stmt = while_stmt;
		while_blocks->while_cond = while_cond;
		while_blocks->while_end = while_end;

		(yyval.llvm_while_blocks) = while_blocks;
	}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 1508 "parser.y"
    {
		LLVMBuildBr(cl2llvm_builder, (yyvsp[(2) - (5)].llvm_while_blocks)->while_cond);
		LLVMPositionBuilderAtEnd(cl2llvm_builder, (yyvsp[(2) - (5)].llvm_while_blocks)->while_cond);
		current_basic_block = (yyvsp[(2) - (5)].llvm_while_blocks)->while_cond;
	}
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 1514 "parser.y"
    {
		struct cl2llvm_val_t *bool_val;
	
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType((yyvsp[(7) - (9)].llvm_value_ref)->type))
			== LLVMVectorTypeKind)
			cl2llvm_yyerror("expression must have "
				"arithmetic, enum or pointer type");
		bool_val = cl2llvm_to_bool_ne_0((yyvsp[(7) - (9)].llvm_value_ref));
		LLVMBuildCondBr(cl2llvm_builder, bool_val->val, (yyvsp[(2) - (9)].llvm_while_blocks)->while_stmt,
			(yyvsp[(2) - (9)].llvm_while_blocks)->while_end);
		LLVMPositionBuilderAtEnd(cl2llvm_builder, (yyvsp[(2) - (9)].llvm_while_blocks)->while_end);
		current_basic_block = (yyvsp[(2) - (9)].llvm_while_blocks)->while_end;
	}
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 1531 "parser.y"
    {
		struct cl2llvm_val_t *bool_val;
		
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType((yyvsp[(4) - (5)].llvm_value_ref)->type))
			== LLVMVectorTypeKind)
			cl2llvm_yyerror("expression must have "
				"arithmetic, enum or pointer type");
		bool_val = cl2llvm_to_bool_ne_0((yyvsp[(4) - (5)].llvm_value_ref));
		LLVMBuildCondBr(cl2llvm_builder, bool_val->val, (yyvsp[(3) - (5)].llvm_while_blocks)->while_stmt, (yyvsp[(3) - (5)].llvm_while_blocks)->while_end);

		LLVMPositionBuilderAtEnd(cl2llvm_builder, (yyvsp[(3) - (5)].llvm_while_blocks)->while_stmt);
	
		current_basic_block = (yyvsp[(3) - (5)].llvm_while_blocks)->while_stmt;
	
		cl2llvm_val_free(bool_val);
		cl2llvm_val_free((yyvsp[(4) - (5)].llvm_value_ref));
	}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 1549 "parser.y"
    {
		LLVMBuildBr(cl2llvm_builder, (yyvsp[(3) - (7)].llvm_while_blocks)->while_cond);
		LLVMPositionBuilderAtEnd(cl2llvm_builder, (yyvsp[(3) - (7)].llvm_while_blocks)->while_end);
		current_basic_block = (yyvsp[(3) - (7)].llvm_while_blocks)->while_end;
		cl2llvm_while_blocks_free((yyvsp[(3) - (7)].llvm_while_blocks));
	}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 1559 "parser.y"
    {
		struct cl2llvm_while_blocks_t *while_blocks = cl2llvm_while_blocks_create();

		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef while_stmt = LLVMAppendBasicBlock(cl2llvm_current_function->func, block_name);

		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef while_cond = LLVMAppendBasicBlock(cl2llvm_current_function->func, block_name);
		snprintf(block_name, sizeof block_name,
			"block_%d", block_count++);
		LLVMBasicBlockRef while_end = LLVMAppendBasicBlock(cl2llvm_current_function->func, block_name);
		
		LLVMBuildBr(cl2llvm_builder, while_cond);
		LLVMPositionBuilderAtEnd(cl2llvm_builder, while_cond);

		while_blocks->while_stmt = while_stmt;
		while_blocks->while_cond = while_cond;
		while_blocks->while_end = while_end;

		(yyval.llvm_while_blocks) = while_blocks;
	}
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 1586 "parser.y"
    {
		(yyval.llvm_value_ref) = NULL;
	}
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 1590 "parser.y"
    {
		(yyval.llvm_value_ref) = (yyvsp[(1) - (1)].llvm_value_ref);
	}
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 1598 "parser.y"
    {
		(yyval.llvm_value_ref) = (yyvsp[(2) - (3)].llvm_value_ref);
	}
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 1602 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *op1, *op2;
		
		/* Find out which value differs from the original and set the
		   dominant type equal to the type of that value. */
		type_unify((yyvsp[(1) - (3)].llvm_value_ref), (yyvsp[(3) - (3)].llvm_value_ref), &op1, &op2);
		
		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(op1->type), cl2llvmTypeWrapGetSign(op1->type));
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(op1->type))  == LLVMVectorTypeKind)
		{
			cl2llvmTypeWrapSetLlvmType(switch_type, LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(op1->type)));
		}

		snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
		
		/* Determine which type of addition to use based on type of
		   operators. */
		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:

			value = cl2llvm_val_create_w_init(LLVMBuildAdd(cl2llvm_builder, op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			value = cl2llvm_val_create_w_init(LLVMBuildFAdd(cl2llvm_builder, op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;

		default:

			yyerror("invalid type of operands for addition");
		}
		
		/* Free pointers */
		if ((yyvsp[(1) - (3)].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
			cl2llvm_val_free( op2);
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value;
	}
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 1657 "parser.y"
    {
		struct cl2llvm_val_t *value;
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvm_val_t *op1, *op2;

		/* Find out which value differs from the original and set the
		   dominant type equal to the type of that value. */	
		type_unify((yyvsp[(1) - (3)].llvm_value_ref), (yyvsp[(3) - (3)].llvm_value_ref), &op1, & op2);
		
		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(op1->type)) == LLVMVectorTypeKind)
		{
			switch_type =  cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(op1->type)), cl2llvmTypeWrapGetSign(op2->type));
		}
		else
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(op1->type), cl2llvmTypeWrapGetSign(op1->type));

		snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);

		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:

			value = cl2llvm_val_create_w_init(LLVMBuildSub(cl2llvm_builder, op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			value = cl2llvm_val_create_w_init(LLVMBuildFSub(cl2llvm_builder, op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;

		default:

			yyerror("invalid type of operands for subtraction");
		}
		if ((yyvsp[(1) - (3)].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);

		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value;
	}
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 1710 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvm_val_t *value;


		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);

		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[(1) - (3)].llvm_value_ref), (yyvsp[(3) - (3)].llvm_value_ref), &op1, &op2);
			
		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(op1->type)) == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(op1->type)), cl2llvmTypeWrapGetSign(op1->type));
		}
		else 
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(op1->type), cl2llvmTypeWrapGetSign(op1->type));

		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:

			value = cl2llvm_val_create_w_init(LLVMBuildMul(cl2llvm_builder, op1->val,
				op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			value = cl2llvm_val_create_w_init(LLVMBuildFMul(cl2llvm_builder, op1->val,
				op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;

		default:

			yyerror("invalid type of operands for addition");
		}

		/* Free pointers */
		if ((yyvsp[(1) - (3)].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value;

	}
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 1767 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvm_val_t *value;
		
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);

		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[(1) - (3)].llvm_value_ref), (yyvsp[(3) - (3)].llvm_value_ref), &op1, & op2);
		
		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(op1->type)) == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(op1->type)), cl2llvmTypeWrapGetSign(op1->type));
		}
		else
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(op1->type), cl2llvmTypeWrapGetSign(op1->type));

		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:
			if (cl2llvmTypeWrapGetSign(switch_type))
			{
				value = cl2llvm_val_create_w_init(LLVMBuildSDiv(cl2llvm_builder, 
					op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			}
			else
			{
				value = cl2llvm_val_create_w_init(LLVMBuildUDiv(cl2llvm_builder, 
					op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			}
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:
			value = cl2llvm_val_create_w_init(LLVMBuildFDiv(cl2llvm_builder, 
					op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;

		default:
			
			yyerror("invalid type of operands for '/'");
		}

		/* Free pointers */
		if ((yyvsp[(1) - (3)].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value;
	}
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 1828 "parser.y"
    {
		struct cl2llvm_val_t *value;
		
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
	
		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[(1) - (3)].llvm_value_ref), (yyvsp[(3) - (3)].llvm_value_ref), &op1, & op2);

		switch (cl2llvmTypeWrapGetSign(op1->type))
		{
		case 1:
			value = cl2llvm_val_create_w_init(LLVMBuildSRem(cl2llvm_builder, 
				op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;

		case 0:
			value = cl2llvm_val_create_w_init(LLVMBuildURem(cl2llvm_builder, 
				op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;

		default:
			
			yyerror("invalid type of operands for addition");
		}
		
		/* Free pointers */
		if ((yyvsp[(1) - (3)].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));

		(yyval.llvm_value_ref) = value;

	}
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 1867 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvm_val_t *value;
		
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);

		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[(1) - (3)].llvm_value_ref), (yyvsp[(3) - (3)].llvm_value_ref), &op1, & op2);

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(op1->type)) == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(op1->type)), cl2llvmTypeWrapGetSign(op1->type));
		}
		else 
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(op1->type), cl2llvmTypeWrapGetSign(op1->type));

		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:
			value = cl2llvm_val_create_w_init(LLVMBuildShl(cl2llvm_builder, 
				op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;


		default:
			
			yyerror("Invalid type of operands for '<<'.");
		}

		/* Free pointers */
		if ((yyvsp[(1) - (3)].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value;

	}
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 1915 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvm_val_t *value;
		
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);

		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[(1) - (3)].llvm_value_ref), (yyvsp[(3) - (3)].llvm_value_ref), &op1, & op2);

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(op1->type)) == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(op1->type)), cl2llvmTypeWrapGetSign(op1->type));
		}
		else
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(op1->type), cl2llvmTypeWrapGetSign(op1->type));
		
		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:
			value = cl2llvm_val_create_w_init(LLVMBuildAShr(cl2llvm_builder, 
				op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;
		default:
			
			yyerror("Invalid type of operands for '>>'.");
		}

		/* Free pointers */
		if ((yyvsp[(1) - (3)].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value;
	}
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 1960 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *bool_val;

		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[(1) - (3)].llvm_value_ref), (yyvsp[(3) - (3)].llvm_value_ref), &op1, & op2);
		
		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(op1->type)) == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(op1->type)), cl2llvmTypeWrapGetSign(op1->type));
		}
		else
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(op1->type), cl2llvmTypeWrapGetSign(op1->type));
		
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		
		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(op1->type)))
		{
		case LLVMIntegerTypeKind:

			bool_val = cl2llvm_val_create_w_init(LLVMBuildICmp(cl2llvm_builder, LLVMIntEQ,
				op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			bool_val = cl2llvm_val_create_w_init(LLVMBuildFCmp(cl2llvm_builder,
				LLVMRealOEQ, op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;

		default:

			yyerror("invalid type of operands for equality");
		}

		/* Extend bits */
		value = cl2llvm_bool_ext(bool_val, (yyvsp[(1) - (3)].llvm_value_ref)->type);

		/* Free pointers */
		if ((yyvsp[(1) - (3)].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));
		cl2llvm_val_free(bool_val);
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value;
	}
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 2020 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *bool_val;
		

		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[(1) - (3)].llvm_value_ref), (yyvsp[(3) - (3)].llvm_value_ref), &op1, & op2);

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(op1->type)) == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(op1->type)), cl2llvmTypeWrapGetSign(op1->type));
		}
		else
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(op1->type), cl2llvmTypeWrapGetSign(op1->type));
		
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);

		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(op1->type)))
		{
		case LLVMIntegerTypeKind:

			bool_val = cl2llvm_val_create_w_init(LLVMBuildICmp(cl2llvm_builder, LLVMIntNE,
				op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			bool_val = cl2llvm_val_create_w_init(LLVMBuildFCmp(cl2llvm_builder, 
				LLVMRealONE, op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;

		default:

			yyerror("invalid type of operands for addition");
		}
	
		/* Extend bits */
		value = cl2llvm_bool_ext(bool_val, (yyvsp[(1) - (3)].llvm_value_ref)->type);

		/* Free pointers */
		if ((yyvsp[(1) - (3)].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));
		cl2llvm_val_free(bool_val);
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value;

	}
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 2082 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *bool_val;
		
		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[(1) - (3)].llvm_value_ref), (yyvsp[(3) - (3)].llvm_value_ref), &op1, & op2);	

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(op1->type)) == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(op1->type)), cl2llvmTypeWrapGetSign(op1->type));
		}
		else
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(op1->type), cl2llvmTypeWrapGetSign(op1->type));
		
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);

		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:

			if (cl2llvmTypeWrapGetSign(op1->type))
			{
				bool_val = cl2llvm_val_create_w_init(LLVMBuildICmp(cl2llvm_builder, 
					LLVMIntSLT, op1->val, op2->val, 
					temp_var_name), 1);
			}
			else
			{
				bool_val = cl2llvm_val_create_w_init(LLVMBuildICmp(cl2llvm_builder, 
					LLVMIntULT, op1->val, op2->val, 
					temp_var_name), 1);
			}
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			bool_val = cl2llvm_val_create_w_init(LLVMBuildFCmp(cl2llvm_builder, 
				LLVMRealOLT, op1->val, op2->val, temp_var_name), 1);
			break;

		default:

			yyerror("invalid type of operands for comparison");
		}

		/* Extend bits */
		value = cl2llvm_bool_ext(bool_val, (yyvsp[(1) - (3)].llvm_value_ref)->type);

		/* Free pointers */
		if ((yyvsp[(1) - (3)].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));
		cl2llvm_val_free(bool_val);
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value;

	}
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 2153 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *bool_val;
		
		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[(1) - (3)].llvm_value_ref), (yyvsp[(3) - (3)].llvm_value_ref), &op1, & op2);

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(op1->type)) == LLVMVectorTypeKind)
		{
			cl2llvmTypeWrapSetLlvmType(switch_type, LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(op1->type)));
		}
		else
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(op1->type), cl2llvmTypeWrapGetSign(op1->type));
	
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);

		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:

			if (cl2llvmTypeWrapGetSign(op1->type))
			{
				bool_val = cl2llvm_val_create_w_init(LLVMBuildICmp(cl2llvm_builder, 
					LLVMIntSGT, op1->val, op2->val, 
					temp_var_name), 1);
			}
			else
			{
				bool_val = cl2llvm_val_create_w_init(LLVMBuildICmp(cl2llvm_builder, 
					LLVMIntUGT, op1->val, op2->val, 
					temp_var_name), 1);
			}
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			bool_val = cl2llvm_val_create_w_init(LLVMBuildFCmp(cl2llvm_builder, 
				LLVMRealOGT, op1->val, op2->val, temp_var_name), 1);
			break;

		default:

			yyerror("invalid type of operands for comparison");
		}

		/* Extend bits */
		value = cl2llvm_bool_ext(bool_val, (yyvsp[(1) - (3)].llvm_value_ref)->type);

		/* Free pointers */
		if ((yyvsp[(1) - (3)].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));
		cl2llvm_val_free(bool_val);
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value;
	}
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 2223 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *bool_val;
		
		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[(1) - (3)].llvm_value_ref), (yyvsp[(3) - (3)].llvm_value_ref), &op1, & op2);
		
		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(op1->type)) == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(op1->type)), cl2llvmTypeWrapGetSign(op1->type));
		}
		else
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(op1->type), cl2llvmTypeWrapGetSign(op1->type));
		
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);

		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:

			if (cl2llvmTypeWrapGetSign(op1->type))
			{
				bool_val = cl2llvm_val_create_w_init(LLVMBuildICmp(cl2llvm_builder, 
					LLVMIntSLE, op1->val, op2->val, 
					temp_var_name), 1);
			}
			else
			{
				bool_val = cl2llvm_val_create_w_init(LLVMBuildICmp(cl2llvm_builder, 
					LLVMIntULE, op1->val, op2->val, 
					temp_var_name), 1);
			}
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			bool_val = cl2llvm_val_create_w_init(LLVMBuildFCmp(cl2llvm_builder, 
				LLVMRealOLE, op1->val, op2->val, temp_var_name), 1);
			break;

		default:

			yyerror("invalid type of operands for comparison");
		}
	
		/* Extend bits */
		value = cl2llvm_bool_ext(bool_val, (yyvsp[(1) - (3)].llvm_value_ref)->type);

		/* Free pointers */
		if ((yyvsp[(1) - (3)].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));
		cl2llvm_val_free(bool_val);
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value;
	}
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 2293 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *bool_val;
		
		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[(1) - (3)].llvm_value_ref), (yyvsp[(3) - (3)].llvm_value_ref), &op1, & op2);

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(op1->type)) == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(op1->type)), cl2llvmTypeWrapGetSign(op1->type));
		}
		else
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(op1->type), cl2llvmTypeWrapGetSign(op1->type));

		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);

		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:

			if (cl2llvmTypeWrapGetSign(op1->type))
			{
				bool_val = cl2llvm_val_create_w_init(LLVMBuildICmp(cl2llvm_builder, 
					LLVMIntSGE, op1->val, op2->val, 
					temp_var_name), 1);
			}
			else
			{
				bool_val = cl2llvm_val_create_w_init(LLVMBuildICmp(cl2llvm_builder, 
					LLVMIntUGE, op1->val, op2->val, 
					temp_var_name), 1);
			}
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			bool_val = cl2llvm_val_create_w_init(LLVMBuildFCmp(cl2llvm_builder, 
				LLVMRealOGE, op1->val, op2->val, temp_var_name), 1);
			break;

		default:

			yyerror("invalid type of operands for comparison");
		}
	
		/* Extend bits */
		value = cl2llvm_bool_ext(bool_val, (yyvsp[(1) - (3)].llvm_value_ref)->type);

		/* Free pointers */
		if ((yyvsp[(1) - (3)].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));
		cl2llvm_val_free(bool_val);
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value;
	}
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 2363 "parser.y"
    {
		struct cl2llvm_val_t *bool1;
		struct cl2llvm_val_t *bool2;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *land_cond;
		LLVMBasicBlockRef land_rhs;
		LLVMBasicBlockRef land_end;
		struct cl2llvm_val_t *op1, *op2;
		
		/* If one value is a vector */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType((yyvsp[(1) - (3)].llvm_value_ref)->type)) == LLVMVectorTypeKind
			|| LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType((yyvsp[(3) - (3)].llvm_value_ref)->type)) == LLVMVectorTypeKind)
		{
			type_unify((yyvsp[(1) - (3)].llvm_value_ref), (yyvsp[(3) - (3)].llvm_value_ref), &op1, &op2);
			
			/* Convert to bool */
			bool1 = cl2llvm_to_bool_ne_0(op1);
			bool2 = cl2llvm_to_bool_ne_0(op2);

			snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
			
			/* Compare vectors */
			land_cond = cl2llvm_val_create_w_init(LLVMBuildAnd(
				cl2llvm_builder, bool1->val, bool2->val, temp_var_name), 0);
			
			/* Sign extend vector */
			value = cl2llvm_bool_ext(land_cond, op1->type);
		
			/* Free pointers */
			if ((yyvsp[(1) - (3)].llvm_value_ref) != op1)
				cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
				cl2llvm_val_free(op2);

		}
		/* If neither value is a vector */
		else
		{
			/* Create basic blocks */
			land_rhs = LLVMAppendBasicBlock(
				cl2llvm_current_function->func, "land_rhs");
			land_end = LLVMAppendBasicBlock(
				cl2llvm_current_function->func, "land_end");

			/* Convert LHS to boolean value */
			bool1 = cl2llvm_to_bool_ne_0((yyvsp[(1) - (3)].llvm_value_ref));

			/* Create conditional branch. Branch will skip to end block if LHS
			   is false */
			LLVMBuildCondBr(cl2llvm_builder, bool1->val, land_rhs, land_end);
		
			/* Move builder to RHS block */
			LLVMPositionBuilderAtEnd(cl2llvm_builder, land_rhs);

			/* Convert RHS to Bool */
			bool2 = cl2llvm_to_bool_ne_0((yyvsp[(3) - (3)].llvm_value_ref));

			/* Build branch to end block */
			LLVMBuildBr(cl2llvm_builder, land_end);
			LLVMPositionBuilderAtEnd(cl2llvm_builder, land_end);

			/* Position builder at end block */
		
			/* Build Phi node */
			LLVMValueRef phi_vals[] = {LLVMConstInt(
				LLVMInt1Type(), 0, 0), bool2->val};
			LLVMBasicBlockRef phi_blocks[] = 
				{current_basic_block, land_rhs};
			land_cond = cl2llvm_val_create_w_init(
				LLVMBuildPhi(cl2llvm_builder, 
				LLVMInt1Type(), "land_cond"), 0);
			LLVMAddIncoming(land_cond->val, phi_vals, phi_blocks, 2);
			
			/* sign extend */
			value = cl2llvm_bool_ext(land_cond, (yyvsp[(1) - (3)].llvm_value_ref)->type);

			/* Set current current basic block */
			current_basic_block = land_end;

		}
		/* Free pointers */
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));
		cl2llvm_val_free(bool1);
		cl2llvm_val_free(bool2);
		cl2llvm_val_free(land_cond);
	
		(yyval.llvm_value_ref) = value;
	}
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 2454 "parser.y"
    {
		struct cl2llvm_val_t *bool1;
		struct cl2llvm_val_t *bool2;
		struct cl2llvm_val_t *value;
		LLVMBasicBlockRef land_rhs;
		LLVMBasicBlockRef land_end;
		struct cl2llvm_val_t *land_cond;
		struct cl2llvm_val_t *op1, *op2;


		
		/* If one value is a vector */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType((yyvsp[(1) - (3)].llvm_value_ref)->type)) == LLVMVectorTypeKind
			|| LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType((yyvsp[(3) - (3)].llvm_value_ref)->type)) == LLVMVectorTypeKind)
		{
			type_unify((yyvsp[(1) - (3)].llvm_value_ref), (yyvsp[(3) - (3)].llvm_value_ref), &op1, &op2);
			
			/* Convert to bool */
			bool1 = cl2llvm_to_bool_ne_0(op1);
			bool2 = cl2llvm_to_bool_ne_0(op2);

			snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
			
			/* Compare vectors */
			land_cond = cl2llvm_val_create_w_init(LLVMBuildOr(
				cl2llvm_builder, bool1->val, bool2->val, temp_var_name), 0);
			
			/* Sign extend vector */
			value = cl2llvm_bool_ext(land_cond, op1->type);
		
			/* Free pointers */
			if ((yyvsp[(1) - (3)].llvm_value_ref) != op1)
				cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
				cl2llvm_val_free(op2);

		}
		/* If neither value is a vector */
		else
		{
			/* Create basic blocks */
			land_rhs = LLVMAppendBasicBlock(cl2llvm_current_function->func, "land_rhs");
			land_end = LLVMAppendBasicBlock(cl2llvm_current_function->func, "land_end");

			/* Convert LHS to boolean value */
			bool1 = cl2llvm_to_bool_ne_0((yyvsp[(1) - (3)].llvm_value_ref));

			/* Create conditional branch. Branch will skip to end block if LHS
			   is true */
			LLVMBuildCondBr(cl2llvm_builder, bool1->val, land_end, land_rhs);
		
			/* Move builder to RHS block */
			LLVMPositionBuilderAtEnd(cl2llvm_builder, land_rhs);

			/* Convert RHS to Bool */
			bool2 = cl2llvm_to_bool_ne_0((yyvsp[(3) - (3)].llvm_value_ref));

			/* Build branch to end block */
			LLVMBuildBr(cl2llvm_builder, land_end);
	
			/* Position builder at end block */
			LLVMPositionBuilderAtEnd(cl2llvm_builder, land_end);
		
			/* Build Phi node */
			LLVMValueRef phi_vals[] = {LLVMConstInt(LLVMInt1Type(), 1, 0), bool2->val};
			LLVMBasicBlockRef phi_blocks[] = {current_basic_block, land_rhs};
			land_cond = cl2llvm_val_create_w_init(LLVMBuildPhi(
				cl2llvm_builder, LLVMInt1Type(), "land_cond"), 0);
			LLVMAddIncoming(land_cond->val, phi_vals, phi_blocks, 2);

			/* Set current current basic block */
			current_basic_block = land_end;

			value = cl2llvm_val_create_w_init(land_cond->val, 1);
		}
		/* Free pointers */
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));
		cl2llvm_val_free(bool1);
		cl2llvm_val_free(bool2);
		cl2llvm_val_free(land_cond);

		(yyval.llvm_value_ref) = value;
	}
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 2540 "parser.y"
    {
		struct cl2llvm_val_t *value;
		struct cl2llvmTypeWrap *type; 
		
		type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType((yyvsp[(1) - (3)].llvm_value_ref)->type)) , cl2llvmTypeWrapGetSign((yyvsp[(1) - (3)].llvm_value_ref)->type));

		/* If lvalue is a component referenced vector. */
		if ((yyvsp[(1) - (3)].llvm_value_ref)->vector_indices[0])
		{
			value = cl2llvm_build_component_wise_assignment((yyvsp[(1) - (3)].llvm_value_ref), (yyvsp[(3) - (3)].llvm_value_ref));
		}
		else
		{
			/*Cast rvalue to type of lvalue and store*/
			value = llvm_type_cast((yyvsp[(3) - (3)].llvm_value_ref), type);
			LLVMBuildStore(cl2llvm_builder, value->val, (yyvsp[(1) - (3)].llvm_value_ref)->val);
		}

		/*Free pointers*/
		cl2llvmTypeWrapFree(type);
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));

		(yyval.llvm_value_ref) = value;
	}
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 2566 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *op1, *op2;
		struct cl2llvm_val_t *lval;
		struct cl2llvm_val_t *rval;

		/* Load lval */
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[(1) - (3)].llvm_value_ref)->val, temp_var_name),
			cl2llvmTypeWrapGetSign((yyvsp[(1) - (3)].llvm_value_ref)->type));

		/* Find out which value differs from the original and set the
		   dominant type equal to the type of that value. */
		type_unify(lval, (yyvsp[(3) - (3)].llvm_value_ref), &op1, &op2);
		
		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(op1->type)) == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(op1->type)), cl2llvmTypeWrapGetSign(op1->type));
		}
		else
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(op1->type), cl2llvmTypeWrapGetSign(op1->type));

		snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
		
		/* Determine which type of addition to use based on type of
		   operators. */
		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:

			rval = cl2llvm_val_create_w_init(LLVMBuildAdd(cl2llvm_builder, op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			rval = cl2llvm_val_create_w_init(LLVMBuildFAdd(cl2llvm_builder, op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;

		default:

			yyerror("invalid type of operands for addition");
		}

		/* Cast result to type of lvalue and store */
		value = llvm_type_cast(rval, lval->type);
		
		LLVMBuildStore(cl2llvm_builder, value->val, (yyvsp[(1) - (3)].llvm_value_ref)->val);

		/* Free pointers */
		if (lval != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
			cl2llvm_val_free( op2);
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free(lval);
		cl2llvm_val_free(rval);
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value;

	}
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 2639 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *op1, *op2;
		struct cl2llvm_val_t *lval;
		struct cl2llvm_val_t *rval;

		/* Load lval */
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[(1) - (3)].llvm_value_ref)->val, temp_var_name),
			cl2llvmTypeWrapGetSign((yyvsp[(1) - (3)].llvm_value_ref)->type));

		/* Find out which value differs from the original and set the
		   dominant type equal to the type of that value. */
		type_unify(lval, (yyvsp[(3) - (3)].llvm_value_ref), &op1, &op2);

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(op1->type)) == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(op1->type)), cl2llvmTypeWrapGetSign(op1->type));
		}
		else
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(op1->type), cl2llvmTypeWrapGetSign(op1->type));

		snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
		/* Determine which type of addition to use based on type of
		   operators. */
		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:

			rval = cl2llvm_val_create_w_init(LLVMBuildSub(cl2llvm_builder, op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			rval = cl2llvm_val_create_w_init(LLVMBuildFSub(cl2llvm_builder, op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;

		default:

			yyerror("invalid type of operands for addition");
		}

		/* Cast result to type of lvalue and store */
		value = llvm_type_cast(rval, lval->type);
		
		LLVMBuildStore(cl2llvm_builder, value->val, (yyvsp[(1) - (3)].llvm_value_ref)->val);

		/* Free pointers */
		if (lval != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
			cl2llvm_val_free( op2);
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free(lval);
		cl2llvm_val_free(rval);
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value;

	}
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 2711 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *op1, *op2;
		struct cl2llvm_val_t *lval;
		struct cl2llvm_val_t *rval;

		/* Load lval */
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[(1) - (3)].llvm_value_ref)->val, temp_var_name),
			cl2llvmTypeWrapGetSign((yyvsp[(1) - (3)].llvm_value_ref)->type));

		/* Find out which value differs from the original and set the
		   dominant type equal to the type of that value. */
		type_unify(lval, (yyvsp[(3) - (3)].llvm_value_ref), &op1, &op2);

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(op1->type)) == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(op1->type)), cl2llvmTypeWrapGetSign(op1->type));
		}
		else
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(op1->type), cl2llvmTypeWrapGetSign(op1->type));

		snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
		
		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:
			if (cl2llvmTypeWrapGetSign(op1->type))
			{
				rval = cl2llvm_val_create_w_init(LLVMBuildSDiv(cl2llvm_builder, 
					op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			}
			else
			{
				rval = cl2llvm_val_create_w_init(LLVMBuildUDiv(cl2llvm_builder, 
					op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			}
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:
			rval = cl2llvm_val_create_w_init(LLVMBuildFDiv(cl2llvm_builder, 
					op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;

		default:
			
			yyerror("invalid type of operands for '/='");
		}
	
		/* Cast result to type of lvalue and store */
		value = llvm_type_cast(rval, lval->type);
		
		LLVMBuildStore(cl2llvm_builder, value->val, (yyvsp[(1) - (3)].llvm_value_ref)->val);

		/* Free pointers */
		if (lval != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
			cl2llvm_val_free( op2);
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free(lval);
		cl2llvm_val_free(rval);
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value;
	}
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 2789 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *op1, *op2;
		struct cl2llvm_val_t *lval;
		struct cl2llvm_val_t *rval;

		/* Load lval */
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[(1) - (3)].llvm_value_ref)->val, temp_var_name),
			cl2llvmTypeWrapGetSign((yyvsp[(1) - (3)].llvm_value_ref)->type));

		/* Find out which value differs from the original and set the
		   dominant type equal to the type of that value. */
		type_unify(lval, (yyvsp[(3) - (3)].llvm_value_ref), &op1, &op2);
		
		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(op1->type)) == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(op1->type)), cl2llvmTypeWrapGetSign(op1->type));
		}
		else
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(op1->type), cl2llvmTypeWrapGetSign(op1->type));

		snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
		
		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:
			rval = cl2llvm_val_create_w_init(LLVMBuildMul(cl2llvm_builder, 
				op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:
			rval = cl2llvm_val_create_w_init(LLVMBuildFMul(cl2llvm_builder, 
					op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;

		default:
			
			yyerror("invalid type of operands for '/='");
		}


		/* Cast result to type of lvalue and store */
		value = llvm_type_cast(rval, lval->type);
		
		LLVMBuildStore(cl2llvm_builder, value->val, (yyvsp[(1) - (3)].llvm_value_ref)->val);

		/* Free pointers */
		if (lval != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
			cl2llvm_val_free( op2);
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free(lval);
		cl2llvm_val_free(rval);
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value;




	}
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 2864 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *op1, *op2;
		struct cl2llvm_val_t *lval;
		struct cl2llvm_val_t *rval;

		/* Load lval */
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[(1) - (3)].llvm_value_ref)->val, temp_var_name),
			cl2llvmTypeWrapGetSign((yyvsp[(1) - (3)].llvm_value_ref)->type));

		/* Find out which value differs from the original and set the
		   dominant type equal to the type of that value. */
		type_unify(lval, (yyvsp[(3) - (3)].llvm_value_ref), &op1, &op2);

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(op1->type)) == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(op1->type)), cl2llvmTypeWrapGetSign(op1->type));
		}
		else
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(op1->type), cl2llvmTypeWrapGetSign(op1->type));

		snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
		
		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:

			if (cl2llvmTypeWrapGetSign(op1->type))
			{
				rval = cl2llvm_val_create_w_init(LLVMBuildSRem(cl2llvm_builder, 
					op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			}
			else
			{
				rval = cl2llvm_val_create_w_init(LLVMBuildURem(cl2llvm_builder, 
					op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			}
			break;
		
		default:
			
			yyerror("invalid type of operands for '%='");
		}

		/* Cast result to type of lvalue and store */
		value = llvm_type_cast(rval, lval->type);
		
		LLVMBuildStore(cl2llvm_builder, value->val, (yyvsp[(1) - (3)].llvm_value_ref)->val);

		/* Free pointers */
		if (lval != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
			cl2llvm_val_free( op2);
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free(lval);
		cl2llvm_val_free(rval);
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value;
	}
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 2936 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *op1, *op2;
		struct cl2llvm_val_t *lval;
		struct cl2llvm_val_t *rval;

		/* Load lval */
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[(1) - (3)].llvm_value_ref)->val, temp_var_name),
			cl2llvmTypeWrapGetSign((yyvsp[(1) - (3)].llvm_value_ref)->type));
 
		/* Find out which value differs from the original and set the
		   dominant type equal to the type of that value. */
		type_unify(lval, (yyvsp[(3) - (3)].llvm_value_ref), &op1, &op2);
		
		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(op1->type)) == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(op1->type)), cl2llvmTypeWrapGetSign(op1->type));;
		}
		else
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(op1->type), cl2llvmTypeWrapGetSign(op1->type));

		snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
		
		/* Determine which type of addition to use based on type of
		   operators. */
		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:

			rval = cl2llvm_val_create_w_init(LLVMBuildAnd(cl2llvm_builder, op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;


		default:

			yyerror("invalid type of operands for binary '&'.");
		}

		/* Cast result to type of lvalue and store */
		value = llvm_type_cast(rval, lval->type);
		
		LLVMBuildStore(cl2llvm_builder, value->val, (yyvsp[(1) - (3)].llvm_value_ref)->val);

		/* Free pointers */
		if (lval != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
			cl2llvm_val_free( op2);
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free(lval);
		cl2llvm_val_free(rval);
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value;

	}
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 3003 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *op1, *op2;
		struct cl2llvm_val_t *lval;
		struct cl2llvm_val_t *rval;

		/* Load lval */
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[(1) - (3)].llvm_value_ref)->val, temp_var_name),
			cl2llvmTypeWrapGetSign((yyvsp[(1) - (3)].llvm_value_ref)->type));
 
		/* Find out which value differs from the original and set the
		   dominant type equal to the type of that value. */
		type_unify(lval, (yyvsp[(3) - (3)].llvm_value_ref), &op1, &op2);

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(op1->type))  == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(op1->type)), cl2llvmTypeWrapGetSign(op1->type));
		}
		else
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(op1->type), cl2llvmTypeWrapGetSign(op1->type));

		snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
		
		/* Determine which type of addition to use based on type of
		   operators. */
		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:

			rval = cl2llvm_val_create_w_init(LLVMBuildOr(cl2llvm_builder, op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;


		default:

			yyerror("invalid type of operands for '|='.");
		}

		/* Cast result to type of lvalue and store */
		value = llvm_type_cast(rval, lval->type);
		
		LLVMBuildStore(cl2llvm_builder, value->val, (yyvsp[(1) - (3)].llvm_value_ref)->val);

		/* Free pointers */
		if (lval != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
			cl2llvm_val_free( op2);
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free(lval);
		cl2llvm_val_free(rval);
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value;

	}
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 3070 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *op1, *op2;
		struct cl2llvm_val_t *lval;
		struct cl2llvm_val_t *rval;

		/* Load lval */
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[(1) - (3)].llvm_value_ref)->val, temp_var_name),
			cl2llvmTypeWrapGetSign((yyvsp[(1) - (3)].llvm_value_ref)->type));
 
		/* Find out which value differs from the original and set the
		   dominant type equal to the type of that value. */
		type_unify(lval, (yyvsp[(3) - (3)].llvm_value_ref), &op1, &op2);
		
		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(op1->type))  == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(op1->type)), cl2llvmTypeWrapGetSign(op1->type));
		}
		else
		switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(op1->type), cl2llvmTypeWrapGetSign(op1->type));

		snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
		
		/* Determine which type of addition to use based on type of
		   operators. */
		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:

			rval = cl2llvm_val_create_w_init(LLVMBuildXor(cl2llvm_builder, op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;


		default:

			yyerror("invalid type of operands for binary '^='.");
		}

		/* Cast result to type of lvalue and store */
		value = llvm_type_cast(rval, lval->type);
		
		LLVMBuildStore(cl2llvm_builder, value->val, (yyvsp[(1) - (3)].llvm_value_ref)->val);

		/* Free pointers */
		if (lval != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
			cl2llvm_val_free( op2);
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free(lval);
		cl2llvm_val_free(rval);
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value;

	}
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 3137 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *op1, *op2;
		struct cl2llvm_val_t *lval;
		struct cl2llvm_val_t *rval;

		/* Load lval */
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[(1) - (3)].llvm_value_ref)->val, temp_var_name),
			cl2llvmTypeWrapGetSign((yyvsp[(1) - (3)].llvm_value_ref)->type));
 
		/* Find out which value differs from the original and set the
		   dominant type equal to the type of that value. */
		type_unify(lval, (yyvsp[(3) - (3)].llvm_value_ref), &op1, &op2);
		
		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(op1->type))  == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(op1->type)), cl2llvmTypeWrapGetSign(op1->type));
		}
		else
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(op1->type), cl2llvmTypeWrapGetSign(op1->type));

		snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
		
		/* Determine which type of addition to use based on type of
		   operators. */
		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:

			rval = cl2llvm_val_create_w_init(LLVMBuildAShr(cl2llvm_builder, op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;


		default:

			yyerror("invalid type of operands for '>>='.");
		}

		/* Cast result to type of lvalue and store */
		value = llvm_type_cast(rval, lval->type);
		
		LLVMBuildStore(cl2llvm_builder, value->val, (yyvsp[(1) - (3)].llvm_value_ref)->val);

		/* Free pointers */
		if (lval != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
			cl2llvm_val_free( op2);
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free(lval);
		cl2llvm_val_free(rval);
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value;


	}
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 3205 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *op1, *op2;
		struct cl2llvm_val_t *lval;
		struct cl2llvm_val_t *rval;

		/* Load lval */
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[(1) - (3)].llvm_value_ref)->val, temp_var_name),
			cl2llvmTypeWrapGetSign((yyvsp[(1) - (3)].llvm_value_ref)->type));
 
		/* Find out which value differs from the original and set the
		   dominant type equal to the type of that value. */
		type_unify(lval, (yyvsp[(3) - (3)].llvm_value_ref), &op1, &op2);

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(op1->type))  == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(op1->type)), cl2llvmTypeWrapGetSign(op1->type));
		}
		else
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(op1->type), cl2llvmTypeWrapGetSign(op1->type));

		snprintf(temp_var_name, sizeof temp_var_name,
				"tmp_%d", temp_var_count++);
		
		/* Determine which type of addition to use based on type of
		   operators. */
		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:

			rval = cl2llvm_val_create_w_init(LLVMBuildShl(cl2llvm_builder, op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;


		default:

			yyerror("invalid type of operands for '<<='.");
		}

		/* Cast result to type of lvalue and store */
		value = llvm_type_cast(rval, lval->type);
		
		LLVMBuildStore(cl2llvm_builder, value->val, (yyvsp[(1) - (3)].llvm_value_ref)->val);

		/* Free pointers */
		if (lval != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
			cl2llvm_val_free( op2);
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free(lval);
		cl2llvm_val_free(rval);
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value;

	}
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 3272 "parser.y"
    {
		cl2llvm_yyerror("a'?'b':'c not supported");
	}
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 3276 "parser.y"
    {
		(yyval.llvm_value_ref) = (yyvsp[(1) - (1)].llvm_value_ref);
	}
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 3281 "parser.y"
    {
		(yyval.llvm_value_ref) = (yyvsp[(1) - (1)].llvm_value_ref);
	}
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 3286 "parser.y"
    {
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *bool_val;
		
		/* Convert $2 to bool */
		bool_val = cl2llvm_to_bool_eq_0((yyvsp[(2) - (2)].llvm_value_ref));

		/* Convert bool back to type of $2 */
		value = cl2llvm_bool_ext(bool_val, (yyvsp[(2) - (2)].llvm_value_ref)->type);

		/* Free pointers */
		cl2llvm_val_free((yyvsp[(2) - (2)].llvm_value_ref));
		cl2llvm_val_free(bool_val);

		(yyval.llvm_value_ref) = value;
	}
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 3303 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvm_val_t *value;
		
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);

		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[(1) - (3)].llvm_value_ref), (yyvsp[(3) - (3)].llvm_value_ref), &op1, & op2);

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(op1->type))  == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(op1->type)), cl2llvmTypeWrapGetSign(op1->type));
		}
		else
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(op1->type), cl2llvmTypeWrapGetSign(op1->type));

		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:
			value = cl2llvm_val_create_w_init(LLVMBuildAnd(cl2llvm_builder, 
				op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;


		default:
			
			yyerror("Invalid type of operands for binary '&'.");
		}

		/* Free pointers */
		if ((yyvsp[(1) - (3)].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value;
		
	}
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 3351 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvm_val_t *value;
		
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);

		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[(1) - (3)].llvm_value_ref), (yyvsp[(3) - (3)].llvm_value_ref), &op1, & op2);

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(op1->type))  == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(op1->type)), cl2llvmTypeWrapGetSign(op1->type));
		}
		else
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(op1->type), cl2llvmTypeWrapGetSign(op1->type));

		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:
			value = cl2llvm_val_create_w_init(LLVMBuildOr(cl2llvm_builder, 
				op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;


		default:
			
			yyerror("Invalid type of operands for '|'.");
		}

		/* Free pointers */
		if ((yyvsp[(1) - (3)].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value;

	}
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 3399 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvm_val_t *value;
		

		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);

		struct cl2llvm_val_t *op1, *op2;
		
		type_unify((yyvsp[(1) - (3)].llvm_value_ref), (yyvsp[(3) - (3)].llvm_value_ref), &op1, & op2);
	
		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(op1->type))  == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(op1->type)), cl2llvmTypeWrapGetSign(op1->type));
		}
		else
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(op1->type), cl2llvmTypeWrapGetSign(op1->type));

		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:
			value = cl2llvm_val_create_w_init(LLVMBuildXor(cl2llvm_builder, 
				op1->val, op2->val, temp_var_name), cl2llvmTypeWrapGetSign(op1->type));
			break;


		default:
			
			yyerror("Invalid type of operands for '^'.");
		}

		/* Free pointers */
		if ((yyvsp[(1) - (3)].llvm_value_ref) != op1)
			cl2llvm_val_free(op1);
		else if ((yyvsp[(3) - (3)].llvm_value_ref) != op2)
			cl2llvm_val_free(op2);
		cl2llvm_val_free((yyvsp[(1) - (3)].llvm_value_ref));
		cl2llvm_val_free((yyvsp[(3) - (3)].llvm_value_ref));
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value;

	}
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 3452 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvmTypeWrap *type;
		struct cl2llvm_val_t *value_plus_one;
		struct cl2llvm_val_t *one;

		/* Create constant one to add to variable */
		one = cl2llvm_val_create_w_init(LLVMConstInt(LLVMInt32Type(), 1, 0), 1);

		type = cl2llvmTypeWrapCreate(LLVMGetElementType(
			cl2llvmTypeWrapGetLlvmType((yyvsp[(1) - (2)].llvm_value_ref)->type)), cl2llvmTypeWrapGetSign((yyvsp[(1) - (2)].llvm_value_ref)->type));

		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		struct cl2llvm_val_t *lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[(1) - (2)].llvm_value_ref)->val, temp_var_name),
			cl2llvmTypeWrapGetSign((yyvsp[(1) - (2)].llvm_value_ref)->type));

		/* Cast constant one to type of variable */
		struct cl2llvm_val_t *cast_one = llvm_type_cast(one, type);
	
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		
		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(lval->type)) == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(type)), cl2llvmTypeWrapGetSign(type));
		}
		else
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(type), cl2llvmTypeWrapGetSign(type));

		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:

			value_plus_one = cl2llvm_val_create_w_init(
				LLVMBuildAdd(cl2llvm_builder, lval->val, 
				cast_one->val, temp_var_name), cl2llvmTypeWrapGetSign(type));
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			value_plus_one = cl2llvm_val_create_w_init(
				LLVMBuildFAdd(cl2llvm_builder, lval->val, 
				cast_one->val, temp_var_name), cl2llvmTypeWrapGetSign(type));
			break;

		default:

			yyerror("invalid type of operand for post '++'");
		}
		
		LLVMBuildStore(cl2llvm_builder, value_plus_one->val, (yyvsp[(1) - (2)].llvm_value_ref)->val);
		
		cl2llvm_val_free(one);
		cl2llvm_val_free(value_plus_one);
		cl2llvm_val_free(cast_one);
		cl2llvm_val_free((yyvsp[(1) - (2)].llvm_value_ref));
		cl2llvmTypeWrapFree(type);
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = lval;

	}
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 3523 "parser.y"
    {	
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvmTypeWrap *type;
		struct cl2llvm_val_t *value_plus_one;
		struct cl2llvm_val_t *one;

		/* Create constant one to add to variable */
		one = cl2llvm_val_create_w_init(LLVMConstInt(LLVMInt32Type(), 1, 0), 1);

		type = cl2llvmTypeWrapCreate(LLVMGetElementType(
			cl2llvmTypeWrapGetLlvmType((yyvsp[(2) - (2)].llvm_value_ref)->type)), cl2llvmTypeWrapGetSign((yyvsp[(2) - (2)].llvm_value_ref)->type));

		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		struct cl2llvm_val_t *lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[(2) - (2)].llvm_value_ref)->val, temp_var_name),
			cl2llvmTypeWrapGetSign((yyvsp[(2) - (2)].llvm_value_ref)->type));

		/* Cast constant one to type of variable */
		struct cl2llvm_val_t *cast_one = llvm_type_cast(one, type);
	
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		
		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)) == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(type)), cl2llvmTypeWrapGetSign(type));
		}
		else
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(type), cl2llvmTypeWrapGetSign(type));

		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:

			value_plus_one = cl2llvm_val_create_w_init(
				LLVMBuildAdd(cl2llvm_builder, lval->val, 
				cast_one->val, temp_var_name), cl2llvmTypeWrapGetSign(type));
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			value_plus_one = cl2llvm_val_create_w_init(
				LLVMBuildFAdd(cl2llvm_builder, lval->val, 
				cast_one->val, temp_var_name), cl2llvmTypeWrapGetSign(type));
			break;

		default:

			yyerror("invalid type of operand for pre '++'");
		}
		
		LLVMBuildStore(cl2llvm_builder, value_plus_one->val, (yyvsp[(2) - (2)].llvm_value_ref)->val);
		
		cl2llvm_val_free(one);
		cl2llvm_val_free((yyvsp[(2) - (2)].llvm_value_ref));
		cl2llvm_val_free(cast_one);
		cl2llvm_val_free(lval);
		cl2llvmTypeWrapFree(type);
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value_plus_one;
	}
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 3593 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvmTypeWrap *type;
		struct cl2llvm_val_t *value_minus_one;
		struct cl2llvm_val_t *one;

		/* Create constant one to add to variable */
		one = cl2llvm_val_create_w_init(LLVMConstInt(LLVMInt32Type(), 1, 0), 1);

		type = cl2llvmTypeWrapCreate(LLVMGetElementType(
			cl2llvmTypeWrapGetLlvmType((yyvsp[(2) - (2)].llvm_value_ref)->type)), cl2llvmTypeWrapGetSign((yyvsp[(2) - (2)].llvm_value_ref)->type));

		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		struct cl2llvm_val_t *lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[(2) - (2)].llvm_value_ref)->val, temp_var_name),
			cl2llvmTypeWrapGetSign((yyvsp[(2) - (2)].llvm_value_ref)->type));

		/* Cast constant one to type of variable */
		struct cl2llvm_val_t *cast_one = llvm_type_cast(one, type);
	
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		
		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)) == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(type)), cl2llvmTypeWrapGetSign(type));
		}
		else
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(type), cl2llvmTypeWrapGetSign(type));

		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:

			value_minus_one = cl2llvm_val_create_w_init(
				LLVMBuildSub(cl2llvm_builder, lval->val, 
				cast_one->val, temp_var_name), cl2llvmTypeWrapGetSign(type));
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			value_minus_one = cl2llvm_val_create_w_init(
				LLVMBuildFSub(cl2llvm_builder, lval->val, 
				cast_one->val, temp_var_name), cl2llvmTypeWrapGetSign(type));
			break;

		default:

			yyerror("invalid type of operand for pre '--'");
		}
		
		LLVMBuildStore(cl2llvm_builder, value_minus_one->val, (yyvsp[(2) - (2)].llvm_value_ref)->val);
		
		cl2llvm_val_free(one);
		cl2llvm_val_free((yyvsp[(2) - (2)].llvm_value_ref));
		cl2llvm_val_free(cast_one);
		cl2llvm_val_free(lval);
		cl2llvmTypeWrapFree(type);
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value_minus_one;

	}
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 3664 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvmTypeWrap *type;
		struct cl2llvm_val_t *value_minus_one;
		struct cl2llvm_val_t *one;

		/* Create constant one to add to variable */
		one = cl2llvm_val_create_w_init(LLVMConstInt(LLVMInt32Type(), 1, 0), 1);

		type = cl2llvmTypeWrapCreate(LLVMGetElementType(
			cl2llvmTypeWrapGetLlvmType((yyvsp[(1) - (2)].llvm_value_ref)->type)), cl2llvmTypeWrapGetSign((yyvsp[(1) - (2)].llvm_value_ref)->type));

		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		struct cl2llvm_val_t *lval = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[(1) - (2)].llvm_value_ref)->val, temp_var_name),
			cl2llvmTypeWrapGetSign((yyvsp[(1) - (2)].llvm_value_ref)->type));

		/* Cast constant one to type of variable */
		struct cl2llvm_val_t *cast_one = llvm_type_cast(one, type);
	
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		
		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)) == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(type)), cl2llvmTypeWrapGetSign(type));
		}
		else
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType(type), cl2llvmTypeWrapGetSign(type));

		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:

			value_minus_one = cl2llvm_val_create_w_init(
				LLVMBuildSub(cl2llvm_builder, lval->val, 
				cast_one->val, temp_var_name), cl2llvmTypeWrapGetSign(type));
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			value_minus_one = cl2llvm_val_create_w_init(
				LLVMBuildFSub(cl2llvm_builder, lval->val, 
				cast_one->val, temp_var_name), cl2llvmTypeWrapGetSign(type));
			break;

		default:

			yyerror("invalid type of operand for post '--'");
		}
		
		LLVMBuildStore(cl2llvm_builder, value_minus_one->val, (yyvsp[(1) - (2)].llvm_value_ref)->val);
		
		cl2llvm_val_free(one);
		cl2llvm_val_free(value_minus_one);
		cl2llvm_val_free(cast_one);
		cl2llvm_val_free((yyvsp[(1) - (2)].llvm_value_ref));
		cl2llvmTypeWrapFree(type);
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = lval;

	}
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 3735 "parser.y"
    {
		struct cl2llvm_val_t *value;
		struct cl2llvmTypeWrap *switch_type;
		
		snprintf(temp_var_name, sizeof temp_var_name,
			"tmp_%d", temp_var_count++);
		
		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType((yyvsp[(2) - (2)].llvm_value_ref)->type)) == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType((yyvsp[(2) - (2)].llvm_value_ref)->type)), cl2llvmTypeWrapGetSign((yyvsp[(2) - (2)].llvm_value_ref)->type));
		}
		else
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType((yyvsp[(2) - (2)].llvm_value_ref)->type), cl2llvmTypeWrapGetSign((yyvsp[(2) - (2)].llvm_value_ref)->type));

		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:

			value = cl2llvm_val_create_w_init(
				LLVMBuildNeg(cl2llvm_builder, (yyvsp[(2) - (2)].llvm_value_ref)->val, 
				temp_var_name), cl2llvmTypeWrapGetSign((yyvsp[(2) - (2)].llvm_value_ref)->type));
			break;

		case LLVMHalfTypeKind:
		case LLVMFloatTypeKind:
		case LLVMDoubleTypeKind:

			value = cl2llvm_val_create_w_init(
				LLVMBuildFNeg(cl2llvm_builder, (yyvsp[(2) - (2)].llvm_value_ref)->val, 
				temp_var_name), cl2llvmTypeWrapGetSign((yyvsp[(2) - (2)].llvm_value_ref)->type));
			break;

		default:

			yyerror("invalid type of operand for unary '-'");
		}
		
		/* Free pointers */
		cl2llvm_val_free((yyvsp[(2) - (2)].llvm_value_ref));
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value;
	}
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 3783 "parser.y"
    {
		(yyval.llvm_value_ref) = (yyvsp[(2) - (2)].llvm_value_ref);
	}
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 3787 "parser.y"
    {
		struct cl2llvm_val_t *value;

		value = llvm_type_cast((yyvsp[(4) - (4)].llvm_value_ref), (yyvsp[(2) - (4)].llvm_type_ref));
	
		/* Free pointers */
		cl2llvm_val_free((yyvsp[(4) - (4)].llvm_value_ref));
		cl2llvmTypeWrapFree((yyvsp[(2) - (4)].llvm_type_ref));
		(yyval.llvm_value_ref) = value;
	}
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 3798 "parser.y"
    {
		cl2llvm_yyerror("'sizeof' not supported");
		(yyval.llvm_value_ref) = NULL;
	}
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 3803 "parser.y"
    {
		struct cl2llvmTypeWrap *switch_type;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *neg_one;
		struct cl2llvm_val_t *cast_neg_one;

		/* Create a negative one value to use in the xor operation */
		neg_one = cl2llvm_val_create_w_init(LLVMConstInt(
			LLVMInt32Type(), -1, 0), 1);

		/* Cast negative one to type of $2 */
		cast_neg_one = llvm_type_cast(neg_one, (yyvsp[(2) - (2)].llvm_value_ref)->type);		

		/* Create an object that will hold the type of the operands.
		   This extra object is necessary since in the case of a vector 
		   type, we are concerned with the type of its components, but the
		   resultant type of the operation is a vector. */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType((yyvsp[(2) - (2)].llvm_value_ref)->type)) == LLVMVectorTypeKind)
		{
			switch_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType((yyvsp[(2) - (2)].llvm_value_ref)->type)), cl2llvmTypeWrapGetSign((yyvsp[(2) - (2)].llvm_value_ref)->type));
		}
		else
			switch_type = cl2llvmTypeWrapCreate(cl2llvmTypeWrapGetLlvmType((yyvsp[(2) - (2)].llvm_value_ref)->type), cl2llvmTypeWrapGetSign((yyvsp[(2) - (2)].llvm_value_ref)->type));

		switch (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(switch_type)))
		{
		case LLVMIntegerTypeKind:
			value = cl2llvm_val_create_w_init(LLVMBuildXor(cl2llvm_builder, 
				(yyvsp[(2) - (2)].llvm_value_ref)->val, cast_neg_one->val, temp_var_name), cl2llvmTypeWrapGetSign((yyvsp[(2) - (2)].llvm_value_ref)->type));
			break;


		default:
			
			yyerror("Invalid type of operands for '~'.");
		}

		/* Free pointers */
		cl2llvm_val_free((yyvsp[(2) - (2)].llvm_value_ref));
		cl2llvm_val_free(neg_one);
		cl2llvm_val_free(cast_neg_one);
		cl2llvmTypeWrapFree(switch_type);

		(yyval.llvm_value_ref) = value;
	}
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 3849 "parser.y"
    {
		(yyval.llvm_value_ref) = (yyvsp[(2) - (2)].llvm_value_ref);
	}
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 3860 "parser.y"
    {
		int index;
		struct cl2llvm_val_t *current_vec_elem;
		struct cl2llvmTypeWrap *elem_type;
		struct cl2llvm_val_t *cast_val;
		struct cl2llvm_val_t *value;
		struct cl2llvm_val_t *blank_elem = cl2llvm_val_create_w_init( LLVMConstInt(LLVMInt32Type(), 0, 0), 1);
		struct cl2llvm_val_t *cast_index;
		struct cl2llvm_val_t *cl2llvm_index;
		LLVMValueRef vec_const_elems[16];
		int vec_nonconst_elems[16];
		int elem_count = 0;
		int non_const_elem_count = 0;

		cast_index = NULL;
		cast_val = NULL;
		current_vec_elem = NULL;

		snprintf(temp_var_name, sizeof(temp_var_name),
			"tmp_%d", temp_var_count++);
		/* Create type object to represent element type */
		elem_type = cl2llvmTypeWrapCreate(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType((yyvsp[(2) - (6)].llvm_type_ref))), cl2llvmTypeWrapGetSign((yyvsp[(2) - (6)].llvm_type_ref)));
		/*Go to entry block and declare vector*/
		LLVMPositionBuilder(cl2llvm_builder, cl2llvm_current_function->entry_block, cl2llvm_current_function->branch_instr);
		LLVMValueRef vec_addr = LLVMBuildAlloca(cl2llvm_builder, 
			cl2llvmTypeWrapGetLlvmType((yyvsp[(2) - (6)].llvm_type_ref)), temp_var_name);
		LLVMPositionBuilderAtEnd(cl2llvm_builder, current_basic_block);

		/*Expand any vectors present in list*/
		expand_vectors((yyvsp[(5) - (6)].list_val_t));

		/*Iterate over list and build a vector of all constant entries*/
		for (index = 0; index < list_count((yyvsp[(5) - (6)].list_val_t)); ++index)
		{
			current_vec_elem = list_get((yyvsp[(5) - (6)].list_val_t), index);
			if(LLVMIsConstant(current_vec_elem->val) == 1)
			{
				
				cast_val = llvm_type_cast(current_vec_elem, elem_type);
				vec_const_elems[index] = cast_val->val;
				vec_nonconst_elems[index] = 0;
				elem_count++;
			}
			else
			{
				cast_val = llvm_type_cast(blank_elem, elem_type);
				vec_const_elems[index] = cast_val->val;
				vec_nonconst_elems[index] = 1;
				elem_count++;
				non_const_elem_count++;
			}
			if (elem_count > LLVMGetVectorSize(cl2llvmTypeWrapGetLlvmType((yyvsp[(2) - (6)].llvm_type_ref))))
				yyerror("Too many elements in vector literal");
			cl2llvm_val_free(cast_val);
		}
		if (elem_count < LLVMGetVectorSize(cl2llvmTypeWrapGetLlvmType((yyvsp[(2) - (6)].llvm_type_ref))))
			yyerror("Too few elements in vector literal");
		
		LLVMValueRef new_vector = LLVMConstVector(vec_const_elems, elem_count);

		/*Store constant vector*/
		if(non_const_elem_count < elem_count)
			LLVMBuildStore(cl2llvm_builder, new_vector, vec_addr);

		
		/*If there are non-constant entries in vector, insert them*/
		if (non_const_elem_count)
		{
			for (index = 0; index < elem_count; index++)
			{	
				cl2llvm_index = cl2llvm_val_create_w_init( LLVMConstInt(LLVMInt32Type(), index, 0), 1);
				cast_val = NULL;
				cast_index = NULL;

				current_vec_elem = list_get((yyvsp[(5) - (6)].list_val_t), index);
				if (vec_nonconst_elems[index])
				{
					cast_val = llvm_type_cast(current_vec_elem, elem_type);
					
					snprintf(temp_var_name, sizeof(temp_var_name),
						"tmp_%d", temp_var_count++);

					LLVMValueRef vector_load = LLVMBuildLoad( cl2llvm_builder, vec_addr, temp_var_name);

					snprintf(temp_var_name, sizeof(temp_var_name),
						"tmp_%d", temp_var_count++);
					cast_index = llvm_type_cast(cl2llvm_index, elem_type);

					new_vector = LLVMBuildInsertElement( cl2llvm_builder, vector_load, cast_val->val, cl2llvm_index->val, temp_var_name);

					LLVMBuildStore(cl2llvm_builder, new_vector, vec_addr);

				}
				if (cast_val != NULL)
					cl2llvm_val_free(cast_val);
				if (cast_index != NULL)
					cl2llvm_val_free(cast_index);
				cl2llvm_val_free(cl2llvm_index);
			}

		}
		cl2llvm_val_free(blank_elem);
		cl2llvmTypeWrapFree(elem_type);

		LIST_FOR_EACH((yyvsp[(5) - (6)].list_val_t), index)
		{
			cl2llvm_val_free(list_get((yyvsp[(5) - (6)].list_val_t), index));
		}
		list_free((yyvsp[(5) - (6)].list_val_t));

		value = cl2llvm_val_create_w_init(new_vector, cl2llvmTypeWrapGetSign((yyvsp[(2) - (6)].llvm_type_ref)));
		
		(yyval.llvm_value_ref) = value;

		cl2llvmTypeWrapFree((yyvsp[(2) - (6)].llvm_type_ref));
	}
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 3980 "parser.y"
    {
		struct list_t *vec_elem_list;

		vec_elem_list = list_create();
		list_add(vec_elem_list, (yyvsp[(1) - (3)].llvm_value_ref));
		list_add(vec_elem_list, (yyvsp[(3) - (3)].llvm_value_ref));

		(yyval.list_val_t) = vec_elem_list;

	}
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 3994 "parser.y"
    {
		(yyval.list_val_t) = (yyvsp[(1) - (1)].list_val_t);
	}
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 3998 "parser.y"
    {
		list_add((yyvsp[(1) - (3)].list_val_t), (yyvsp[(3) - (3)].llvm_value_ref));

		(yyval.list_val_t) = (yyvsp[(1) - (3)].list_val_t);
	}
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 4008 "parser.y"
    {
		struct cl2llvm_val_t *value = cl2llvm_val_create_w_init(
			LLVMConstInt(LLVMInt32Type(), (yyvsp[(1) - (1)].const_int_val), 0), 1);
		(yyval.llvm_value_ref) = value;
	}
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 4014 "parser.y"
    {
		struct cl2llvm_val_t *value = cl2llvm_val_create_w_init(
			LLVMConstInt(LLVMInt32Type(), (yyvsp[(1) - (1)].const_int_val), 0), 1);
		(yyval.llvm_value_ref) = value;
	}
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 4020 "parser.y"
    {
		struct cl2llvm_val_t *value = cl2llvm_val_create_w_init(
			LLVMConstInt(LLVMInt32Type(), (yyvsp[(1) - (1)].const_int_val), 0), 0);
		(yyval.llvm_value_ref) = value;
	}
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 4026 "parser.y"
    {
		struct cl2llvm_val_t *value =  cl2llvm_val_create_w_init(
			LLVMConstInt(LLVMInt32Type(), (yyvsp[(1) - (1)].const_int_val), 0), 0);
		(yyval.llvm_value_ref) = value;
	}
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 4032 "parser.y"
    {
		struct cl2llvm_val_t *value = cl2llvm_val_create_w_init(
			LLVMConstInt(LLVMInt64Type(), (yyvsp[(1) - (1)].const_int_val_ull), 0), 1);
		(yyval.llvm_value_ref) = value;
	}
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 4038 "parser.y"
    {
		struct cl2llvm_val_t *value = cl2llvm_val_create_w_init(
			LLVMConstInt(LLVMInt64Type(), (yyvsp[(1) - (1)].const_int_val_ull), 0), 0);
		(yyval.llvm_value_ref) = value;
	}
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 4044 "parser.y"
    {
		struct cl2llvm_val_t *value = cl2llvm_val_create_w_init( 
			LLVMConstReal(LLVMDoubleType(), (yyvsp[(1) - (1)].const_float_val)), 1);
		(yyval.llvm_value_ref) = value;
	}
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 4050 "parser.y"
    {
		struct cl2llvm_val_t *value = cl2llvm_val_create_w_init(
			LLVMConstReal(LLVMHalfType(), (yyvsp[(1) - (1)].const_float_val)), 1);
		(yyval.llvm_value_ref) = value;
	}
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 4056 "parser.y"
    {
		struct cl2llvm_val_t *value = cl2llvm_val_create_w_init(
			LLVMConstReal(LLVMFloatType(), (yyvsp[(1) - (1)].const_float_val)), 1);
		(yyval.llvm_value_ref) = value;
	}
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 4062 "parser.y"
    {
		struct cl2llvm_val_t *value = cl2llvm_val_create_w_init(
			LLVMConstReal(LLVMDoubleType(), (yyvsp[(1) - (1)].const_float_val)), 1);
		(yyval.llvm_value_ref) = value;
	}
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 4068 "parser.y"
    {
		int i;
		int component_count = 0;
		LLVMValueRef new_vector_addr;
		LLVMValueRef new_vector;
		LLVMValueRef component;
		
		snprintf(temp_var_name, sizeof(temp_var_name),
			"tmp_%d", temp_var_count++);
		struct cl2llvm_val_t *value = cl2llvm_val_create_w_init(
			LLVMBuildLoad(cl2llvm_builder, (yyvsp[(1) - (1)].llvm_value_ref)->val, temp_var_name),
			cl2llvmTypeWrapGetSign((yyvsp[(1) - (1)].llvm_value_ref)->type));

		/* If value is an array element, retrieve element type */
		if (LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(value->type)) == LLVMArrayTypeKind
			|| LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(value->type)) == LLVMPointerTypeKind
			|| LLVMGetTypeKind(cl2llvmTypeWrapGetLlvmType(value->type)) == LLVMStructTypeKind)
		{
			cl2llvmTypeWrapSetLlvmType(value->type, LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(value->type)));
		}

		/* If element is of vector type, check for component indices. */
		if (LLVMGetTypeKind(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType((yyvsp[(1) - (1)].llvm_value_ref)->type)))
			== LLVMVectorTypeKind && (yyvsp[(1) - (1)].llvm_value_ref)->vector_indices[i])
		{
			/* Get vector component count */
			while((yyvsp[(1) - (1)].llvm_value_ref)->vector_indices[component_count])
				component_count++;
			/* If there are multiple components */
			if (component_count == 2 || component_count == 3
				|| component_count == 4 || component_count == 8
				|| component_count == 16)
			{

				snprintf(temp_var_name, sizeof temp_var_name,
					"tmp_%d", temp_var_count++);

				/* Go to entry block and allocate new vector */
				LLVMPositionBuilder(cl2llvm_builder, 
					cl2llvm_current_function->entry_block,
					cl2llvm_current_function->branch_instr);
			
				new_vector_addr = LLVMBuildAlloca(cl2llvm_builder,
					LLVMVectorType(LLVMGetElementType(cl2llvmTypeWrapGetLlvmType(value->type)),
					component_count), temp_var_name);

				LLVMPositionBuilderAtEnd(cl2llvm_builder, current_basic_block);


				/* Load new vector */
				snprintf(temp_var_name, sizeof temp_var_name,
					"tmp_%d", temp_var_count++);
				new_vector = LLVMBuildLoad(cl2llvm_builder, new_vector_addr,
					temp_var_name);

				while ((yyvsp[(1) - (1)].llvm_value_ref)->vector_indices[i])
				{
					snprintf(temp_var_name, sizeof temp_var_name,
						"tmp_%d", temp_var_count++);
					component = LLVMBuildExtractElement(cl2llvm_builder, 
						value->val, (yyvsp[(1) - (1)].llvm_value_ref)->vector_indices[i]->val,
						temp_var_name);

					snprintf(temp_var_name, sizeof temp_var_name,
						"tmp_%d", temp_var_count++);
					new_vector = LLVMBuildInsertElement(cl2llvm_builder, 
						new_vector, component, (yyvsp[(1) - (1)].llvm_value_ref)->vector_indices[i]->val,
						temp_var_name);
					i++;
				}
				value->val = new_vector;
				cl2llvmTypeWrapSetLlvmType(value->type, LLVMTypeOf(new_vector));
			}
			else if (component_count == 1)
			{
				snprintf(temp_var_name, sizeof temp_var_name,
					"tmp_%d", temp_var_count++);
				
				component = LLVMBuildExtractElement(cl2llvm_builder, 
					value->val, (yyvsp[(1) - (1)].llvm_value_ref)->vector_indices[0]->val,
					temp_var_name);
				value->val = component;
				cl2llvmTypeWrapSetLlvmType(value->type, LLVMTypeOf(component));
			}
			else
				cl2llvm_yyerror("Invalid vector type.");
		}
			

		cl2llvm_val_free((yyvsp[(1) - (1)].llvm_value_ref));

		(yyval.llvm_value_ref) = value;
	}
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 4163 "parser.y"
    {
		(yyval.llvm_value_ref) = (yyvsp[(1) - (1)].llvm_value_ref);
	}
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 4171 "parser.y"
    {
		(yyval.llvm_type_ref) = (yyvsp[(1) - (1)].llvm_type_ref);
	}
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 4175 "parser.y"
    {
		LLVMTypeRef ptr_type;
		struct cl2llvmTypeWrap *type;
		
		/* Create pointer type */
		ptr_type = LLVMPointerType(cl2llvmTypeWrapGetLlvmType((yyvsp[(1) - (2)].llvm_type_ref)), 0);
		
		type = cl2llvmTypeWrapCreate(ptr_type, cl2llvmTypeWrapGetSign((yyvsp[(1) - (2)].llvm_type_ref)));
	
		/* Free pointers */
		cl2llvmTypeWrapFree((yyvsp[(1) - (2)].llvm_type_ref));
		
		(yyval.llvm_type_ref) = type;
	}
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 4193 "parser.y"
    {
		cl2llvm_yyerror("'intptr_t' not supported");
		(yyval.llvm_type_ref) = NULL;
	}
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 4198 "parser.y"
    {
		cl2llvm_yyerror("'ptrdiff_t' not supported");
		(yyval.llvm_type_ref) = NULL;
	}
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 4203 "parser.y"
    {
		cl2llvm_yyerror("'uintptr_t' not supported");
		(yyval.llvm_type_ref) = NULL;
	}
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 4208 "parser.y"
    {
		cl2llvm_yyerror("'sampler_t' not supported");
		(yyval.llvm_type_ref) = NULL;
	}
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 4213 "parser.y"
    {
		cl2llvm_yyerror("'event_t' not supported");
		(yyval.llvm_type_ref) = NULL;
	}
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 4218 "parser.y"
    {
		cl2llvm_yyerror("'image2d_t' not supported");
		(yyval.llvm_type_ref) = NULL;
	}
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 4223 "parser.y"
    {
		cl2llvm_yyerror("'image3d_t' not supported");
		(yyval.llvm_type_ref) = NULL;
	}
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 4228 "parser.y"
    {
		cl2llvm_yyerror("'image2d_array_t' not supported");
		(yyval.llvm_type_ref) = NULL;
	}
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 4233 "parser.y"
    {
		cl2llvm_yyerror("'image1d_t' not supported");
		(yyval.llvm_type_ref) = NULL;
	}
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 4238 "parser.y"
    {
		cl2llvm_yyerror("'image1d_buffer_t' not supported");
		(yyval.llvm_type_ref) = NULL;
	}
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 4243 "parser.y"
    {
		cl2llvm_yyerror("'image1d_array_t' not supported");
		(yyval.llvm_type_ref) = NULL;
	}
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 4248 "parser.y"
    {
		struct cl2llvmTypeWrap *type = cl2llvmTypeWrapCreate(
			LLVMInt32Type(), 0);
		(yyval.llvm_type_ref) = type;
	}
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 4254 "parser.y"
    {
		struct cl2llvmTypeWrap *type = cl2llvmTypeWrapCreate(
			LLVMInt32Type(), 0);
		(yyval.llvm_type_ref) = type;
	}
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 4260 "parser.y"
    {
		struct cl2llvmTypeWrap *type = cl2llvmTypeWrapCreate(
			LLVMInt64Type(), 0);
		(yyval.llvm_type_ref) = type;
	}
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 4266 "parser.y"
    {
		struct cl2llvmTypeWrap *type = cl2llvmTypeWrapCreate(
			LLVMInt8Type(), 0);
		(yyval.llvm_type_ref) = type;
	}
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 4272 "parser.y"
    {
		struct cl2llvmTypeWrap *type = cl2llvmTypeWrapCreate(
			LLVMInt16Type(), 1);
		(yyval.llvm_type_ref) = type;
	}
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 4278 "parser.y"
    {
		struct cl2llvmTypeWrap *type = cl2llvmTypeWrapCreate(
			LLVMInt16Type(), 0);
		(yyval.llvm_type_ref) = type;
	}
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 4284 "parser.y"
    {
		struct cl2llvmTypeWrap *type;
		type = cl2llvmTypeWrapCreate(LLVMVectorType(LLVMInt32Type(), (yyvsp[(1) - (1)].const_int_val)), 0);
		(yyval.llvm_type_ref) = type;

	}
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 4291 "parser.y"
    {
		struct cl2llvmTypeWrap *type;
		type = cl2llvmTypeWrapCreate(LLVMVectorType(LLVMInt8Type(), (yyvsp[(1) - (1)].const_int_val)), 0);
		(yyval.llvm_type_ref) = type;

	}
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 4298 "parser.y"
    {
		struct cl2llvmTypeWrap *type;
		type = cl2llvmTypeWrapCreate(LLVMVectorType(LLVMInt32Type(), (yyvsp[(1) - (1)].const_int_val)), 0);
		(yyval.llvm_type_ref) = type;

	}
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 4305 "parser.y"
    {
		struct cl2llvmTypeWrap *type;
		type = cl2llvmTypeWrapCreate(LLVMVectorType(LLVMInt16Type(), (yyvsp[(1) - (1)].const_int_val)), 0);
		(yyval.llvm_type_ref) = type;

	}
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 4312 "parser.y"
    {
		struct cl2llvmTypeWrap *type;
		type = cl2llvmTypeWrapCreate(LLVMVectorType(LLVMInt16Type(), (yyvsp[(1) - (1)].const_int_val)), 1);
		(yyval.llvm_type_ref) = type;

	}
    break;

  case 190:

/* Line 1806 of yacc.c  */
#line 4319 "parser.y"
    {
		struct cl2llvmTypeWrap *type;
		type = cl2llvmTypeWrapCreate(LLVMVectorType(LLVMInt32Type(), (yyvsp[(1) - (1)].const_int_val)), 1);
		(yyval.llvm_type_ref) = type;
	}
    break;

  case 191:

/* Line 1806 of yacc.c  */
#line 4325 "parser.y"
    {
		struct cl2llvmTypeWrap *type;
		type = cl2llvmTypeWrapCreate(LLVMVectorType(LLVMInt32Type(), (yyvsp[(1) - (1)].const_int_val)), 1);
		(yyval.llvm_type_ref) = type;
	}
    break;

  case 192:

/* Line 1806 of yacc.c  */
#line 4331 "parser.y"
    {
		struct cl2llvmTypeWrap *type;
		type = cl2llvmTypeWrapCreate(LLVMVectorType(LLVMInt8Type(), (yyvsp[(1) - (1)].const_int_val)), 1);
		(yyval.llvm_type_ref) = type;
	}
    break;

  case 193:

/* Line 1806 of yacc.c  */
#line 4337 "parser.y"
    {
		struct cl2llvmTypeWrap *type;
		type = cl2llvmTypeWrapCreate(LLVMVectorType(LLVMFloatType(), (yyvsp[(1) - (1)].const_int_val)), 1);
		(yyval.llvm_type_ref) = type;
	}
    break;

  case 194:

/* Line 1806 of yacc.c  */
#line 4343 "parser.y"
    {
		struct cl2llvmTypeWrap *type;
		type = cl2llvmTypeWrapCreate(LLVMVectorType(LLVMDoubleType(), (yyvsp[(1) - (1)].const_int_val)), 1);
		(yyval.llvm_type_ref) = type;
	}
    break;

  case 195:

/* Line 1806 of yacc.c  */
#line 4349 "parser.y"
    {
		struct cl2llvmTypeWrap *type = cl2llvmTypeWrapCreate(
			LLVMInt32Type(), 1);
		(yyval.llvm_type_ref) = type;
	}
    break;

  case 196:

/* Line 1806 of yacc.c  */
#line 4355 "parser.y"
    {
		struct cl2llvmTypeWrap *type = cl2llvmTypeWrapCreate(
			LLVMInt32Type(), 1);
		(yyval.llvm_type_ref) = type;
	}
    break;

  case 197:

/* Line 1806 of yacc.c  */
#line 4361 "parser.y"
    {
		struct cl2llvmTypeWrap *type = cl2llvmTypeWrapCreate(
			LLVMInt64Type(), 1);
		(yyval.llvm_type_ref) = type;
	}
    break;

  case 198:

/* Line 1806 of yacc.c  */
#line 4367 "parser.y"
    {
		struct cl2llvmTypeWrap *type = cl2llvmTypeWrapCreate(
			LLVMInt8Type(), 1);
		(yyval.llvm_type_ref) = type;
	}
    break;

  case 199:

/* Line 1806 of yacc.c  */
#line 4373 "parser.y"
    {
		struct cl2llvmTypeWrap *type = cl2llvmTypeWrapCreate(
			LLVMFloatType(), 1);
		(yyval.llvm_type_ref) = type;
	}
    break;

  case 200:

/* Line 1806 of yacc.c  */
#line 4379 "parser.y"
    {
		struct cl2llvmTypeWrap *type = cl2llvmTypeWrapCreate(
			LLVMInt1Type(), 1);
		(yyval.llvm_type_ref) = type;
	}
    break;

  case 201:

/* Line 1806 of yacc.c  */
#line 4385 "parser.y"
    {
		struct cl2llvmTypeWrap *type = cl2llvmTypeWrapCreate(
			LLVMDoubleType(), 1);
		(yyval.llvm_type_ref) = type;
	}
    break;

  case 202:

/* Line 1806 of yacc.c  */
#line 4391 "parser.y"
    {
		struct cl2llvmTypeWrap *type = cl2llvmTypeWrapCreate(
			LLVMInt64Type(), 1);
		(yyval.llvm_type_ref) = type;
	}
    break;

  case 203:

/* Line 1806 of yacc.c  */
#line 4397 "parser.y"
    {
		struct cl2llvmTypeWrap *type = cl2llvmTypeWrapCreate(
			LLVMVoidType(), 1);
		(yyval.llvm_type_ref) = type;

	}
    break;

  case 204:

/* Line 1806 of yacc.c  */
#line 4404 "parser.y"
    {
		struct cl2llvmTypeWrap *type = cl2llvmTypeWrapCreate(
			LLVMHalfType(), 1);
		(yyval.llvm_type_ref) = type;
	}
    break;



/* Line 1806 of yacc.c  */
#line 7229 "parser.c"
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

  *++yyvsp = yylval;


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



/* Line 2067 of yacc.c  */
#line 4414 "parser.y"



