/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Substitute the type names.  */
#define YYSTYPE         QSYYSTYPE
#define YYLTYPE         QSYYLTYPE
/* Substitute the variable and function names.  */
#define yyparse         qsyyparse
#define yylex           qsyylex
#define yyerror         qsyyerror
#define yydebug         qsyydebug
#define yynerrs         qsyynerrs
#define yylval          qsyylval
#define yychar          qsyychar
#define yylloc          qsyylloc

/* First part of user prologue.  */
#line 1 "grammar.y"

/****************************************************************************
**
** Copyright (C) 1992-$THISYEAR$ Trolltech AS. All rights reserved.
**
** This file is part of the $MODULE$ of the Qt Toolkit.
**
** $LICENSE$
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <string.h>
#include "qsengine.h"
#include "qsnodes.h"
#include "qslexer.h"

/* default values for bison */
#define YYDEBUG 0
#define YYMAXDEPTH 0
#ifdef QSDEBUGGER
#define DBG(l, s, e) { l->setLoc(s.first_line, e.last_line); } // location
#else
#define DBG(l, s, e)
#endif

extern int yylex();
static int yyerror (const char *);
static bool automatic();


#line 118 "grammar.cpp"

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

#include "grammar.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NULLTOKEN = 3,                  /* NULLTOKEN  */
  YYSYMBOL_TRUETOKEN = 4,                  /* TRUETOKEN  */
  YYSYMBOL_FALSETOKEN = 5,                 /* FALSETOKEN  */
  YYSYMBOL_STRING = 6,                     /* STRING  */
  YYSYMBOL_NUMBER = 7,                     /* NUMBER  */
  YYSYMBOL_BREAK = 8,                      /* BREAK  */
  YYSYMBOL_CASE = 9,                       /* CASE  */
  YYSYMBOL_DEFAULT = 10,                   /* DEFAULT  */
  YYSYMBOL_FOR = 11,                       /* FOR  */
  YYSYMBOL_NEW = 12,                       /* NEW  */
  YYSYMBOL_VAR = 13,                       /* VAR  */
  YYSYMBOL_CONTINUE = 14,                  /* CONTINUE  */
  YYSYMBOL_FUNCTION = 15,                  /* FUNCTION  */
  YYSYMBOL_RETURN = 16,                    /* RETURN  */
  YYSYMBOL_QS_VOID = 17,                   /* QS_VOID  */
  YYSYMBOL_QS_DELETE = 18,                 /* QS_DELETE  */
  YYSYMBOL_IF = 19,                        /* IF  */
  YYSYMBOL_THIS = 20,                      /* THIS  */
  YYSYMBOL_DO = 21,                        /* DO  */
  YYSYMBOL_WHILE = 22,                     /* WHILE  */
  YYSYMBOL_ELSE = 23,                      /* ELSE  */
  YYSYMBOL_QS_IN = 24,                     /* QS_IN  */
  YYSYMBOL_INSTANCEOF = 25,                /* INSTANCEOF  */
  YYSYMBOL_TYPEOF = 26,                    /* TYPEOF  */
  YYSYMBOL_IS = 27,                        /* IS  */
  YYSYMBOL_SWITCH = 28,                    /* SWITCH  */
  YYSYMBOL_WITH = 29,                      /* WITH  */
  YYSYMBOL_RESERVED = 30,                  /* RESERVED  */
  YYSYMBOL_THROW = 31,                     /* THROW  */
  YYSYMBOL_TRY = 32,                       /* TRY  */
  YYSYMBOL_CATCH = 33,                     /* CATCH  */
  YYSYMBOL_FINALLY = 34,                   /* FINALLY  */
  YYSYMBOL_CLASS = 35,                     /* CLASS  */
  YYSYMBOL_CONSTRUCTOR = 36,               /* CONSTRUCTOR  */
  YYSYMBOL_EXTENDS = 37,                   /* EXTENDS  */
  YYSYMBOL_ABSTRACT = 38,                  /* ABSTRACT  */
  YYSYMBOL_FINAL = 39,                     /* FINAL  */
  YYSYMBOL_PRIVATE = 40,                   /* PRIVATE  */
  YYSYMBOL_PUBLIC = 41,                    /* PUBLIC  */
  YYSYMBOL_STATIC = 42,                    /* STATIC  */
  YYSYMBOL_QS_CONST = 43,                  /* QS_CONST  */
  YYSYMBOL_PACKAGE = 44,                   /* PACKAGE  */
  YYSYMBOL_IMPORT = 45,                    /* IMPORT  */
  YYSYMBOL_EQEQ = 46,                      /* EQEQ  */
  YYSYMBOL_NE = 47,                        /* NE  */
  YYSYMBOL_STREQ = 48,                     /* STREQ  */
  YYSYMBOL_STRNEQ = 49,                    /* STRNEQ  */
  YYSYMBOL_LE = 50,                        /* LE  */
  YYSYMBOL_GE = 51,                        /* GE  */
  YYSYMBOL_OR = 52,                        /* OR  */
  YYSYMBOL_AND = 53,                       /* AND  */
  YYSYMBOL_PLUSPLUS = 54,                  /* PLUSPLUS  */
  YYSYMBOL_MINUSMINUS = 55,                /* MINUSMINUS  */
  YYSYMBOL_LSHIFT = 56,                    /* LSHIFT  */
  YYSYMBOL_RSHIFT = 57,                    /* RSHIFT  */
  YYSYMBOL_URSHIFT = 58,                   /* URSHIFT  */
  YYSYMBOL_PLUSEQUAL = 59,                 /* PLUSEQUAL  */
  YYSYMBOL_MINUSEQUAL = 60,                /* MINUSEQUAL  */
  YYSYMBOL_MULTEQUAL = 61,                 /* MULTEQUAL  */
  YYSYMBOL_DIVEQUAL = 62,                  /* DIVEQUAL  */
  YYSYMBOL_LSHIFTEQUAL = 63,               /* LSHIFTEQUAL  */
  YYSYMBOL_RSHIFTEQUAL = 64,               /* RSHIFTEQUAL  */
  YYSYMBOL_URSHIFTEQUAL = 65,              /* URSHIFTEQUAL  */
  YYSYMBOL_ANDEQUAL = 66,                  /* ANDEQUAL  */
  YYSYMBOL_MODEQUAL = 67,                  /* MODEQUAL  */
  YYSYMBOL_XOREQUAL = 68,                  /* XOREQUAL  */
  YYSYMBOL_OREQUAL = 69,                   /* OREQUAL  */
  YYSYMBOL_IDENT = 70,                     /* IDENT  */
  YYSYMBOL_71_ = 71,                       /* '/'  */
  YYSYMBOL_72_ = 72,                       /* '('  */
  YYSYMBOL_73_ = 73,                       /* ')'  */
  YYSYMBOL_74_ = 74,                       /* '{'  */
  YYSYMBOL_75_ = 75,                       /* '}'  */
  YYSYMBOL_76_ = 76,                       /* '['  */
  YYSYMBOL_77_ = 77,                       /* ']'  */
  YYSYMBOL_78_ = 78,                       /* ','  */
  YYSYMBOL_79_ = 79,                       /* ':'  */
  YYSYMBOL_80_ = 80,                       /* '.'  */
  YYSYMBOL_81_ = 81,                       /* '+'  */
  YYSYMBOL_82_ = 82,                       /* '-'  */
  YYSYMBOL_83_ = 83,                       /* '~'  */
  YYSYMBOL_84_ = 84,                       /* '!'  */
  YYSYMBOL_85_ = 85,                       /* '*'  */
  YYSYMBOL_86_ = 86,                       /* '%'  */
  YYSYMBOL_87_ = 87,                       /* '<'  */
  YYSYMBOL_88_ = 88,                       /* '>'  */
  YYSYMBOL_89_ = 89,                       /* '&'  */
  YYSYMBOL_90_ = 90,                       /* '^'  */
  YYSYMBOL_91_ = 91,                       /* '|'  */
  YYSYMBOL_92_ = 92,                       /* '?'  */
  YYSYMBOL_93_ = 93,                       /* '='  */
  YYSYMBOL_94_ = 94,                       /* ';'  */
  YYSYMBOL_YYACCEPT = 95,                  /* $accept  */
  YYSYMBOL_Literal = 96,                   /* Literal  */
  YYSYMBOL_PrimaryExpr = 97,               /* PrimaryExpr  */
  YYSYMBOL_ArrayLiteral = 98,              /* ArrayLiteral  */
  YYSYMBOL_ElementList = 99,               /* ElementList  */
  YYSYMBOL_ElisionOpt = 100,               /* ElisionOpt  */
  YYSYMBOL_Elision = 101,                  /* Elision  */
  YYSYMBOL_PropertyNameAndValueList = 102, /* PropertyNameAndValueList  */
  YYSYMBOL_PropertyName = 103,             /* PropertyName  */
  YYSYMBOL_MemberExpr = 104,               /* MemberExpr  */
  YYSYMBOL_NewExpr = 105,                  /* NewExpr  */
  YYSYMBOL_CallExpr = 106,                 /* CallExpr  */
  YYSYMBOL_Arguments = 107,                /* Arguments  */
  YYSYMBOL_ArgumentList = 108,             /* ArgumentList  */
  YYSYMBOL_LeftHandSideExpr = 109,         /* LeftHandSideExpr  */
  YYSYMBOL_PostfixExpr = 110,              /* PostfixExpr  */
  YYSYMBOL_UnaryExpr = 111,                /* UnaryExpr  */
  YYSYMBOL_MultiplicativeExpr = 112,       /* MultiplicativeExpr  */
  YYSYMBOL_AdditiveExpr = 113,             /* AdditiveExpr  */
  YYSYMBOL_ShiftExpr = 114,                /* ShiftExpr  */
  YYSYMBOL_RelationalExpr = 115,           /* RelationalExpr  */
  YYSYMBOL_EqualityExpr = 116,             /* EqualityExpr  */
  YYSYMBOL_BitwiseANDExpr = 117,           /* BitwiseANDExpr  */
  YYSYMBOL_BitwiseXORExpr = 118,           /* BitwiseXORExpr  */
  YYSYMBOL_BitwiseORExpr = 119,            /* BitwiseORExpr  */
  YYSYMBOL_LogicalANDExpr = 120,           /* LogicalANDExpr  */
  YYSYMBOL_LogicalORExpr = 121,            /* LogicalORExpr  */
  YYSYMBOL_ConditionalExpr = 122,          /* ConditionalExpr  */
  YYSYMBOL_AssignmentExpr = 123,           /* AssignmentExpr  */
  YYSYMBOL_AssignmentOperator = 124,       /* AssignmentOperator  */
  YYSYMBOL_Expr = 125,                     /* Expr  */
  YYSYMBOL_Statement = 126,                /* Statement  */
  YYSYMBOL_Block = 127,                    /* Block  */
  YYSYMBOL_StatementList = 128,            /* StatementList  */
  YYSYMBOL_EmptyStatement = 129,           /* EmptyStatement  */
  YYSYMBOL_ExprStatement = 130,            /* ExprStatement  */
  YYSYMBOL_IfStatement = 131,              /* IfStatement  */
  YYSYMBOL_IterationStatement = 132,       /* IterationStatement  */
  YYSYMBOL_ExprOpt = 133,                  /* ExprOpt  */
  YYSYMBOL_ContinueStatement = 134,        /* ContinueStatement  */
  YYSYMBOL_BreakStatement = 135,           /* BreakStatement  */
  YYSYMBOL_ReturnStatement = 136,          /* ReturnStatement  */
  YYSYMBOL_WithStatement = 137,            /* WithStatement  */
  YYSYMBOL_SwitchStatement = 138,          /* SwitchStatement  */
  YYSYMBOL_CaseBlock = 139,                /* CaseBlock  */
  YYSYMBOL_CaseClausesOpt = 140,           /* CaseClausesOpt  */
  YYSYMBOL_CaseClauses = 141,              /* CaseClauses  */
  YYSYMBOL_CaseClause = 142,               /* CaseClause  */
  YYSYMBOL_DefaultClause = 143,            /* DefaultClause  */
  YYSYMBOL_LabelledStatement = 144,        /* LabelledStatement  */
  YYSYMBOL_ThrowStatement = 145,           /* ThrowStatement  */
  YYSYMBOL_TryStatement = 146,             /* TryStatement  */
  YYSYMBOL_Catch = 147,                    /* Catch  */
  YYSYMBOL_Finally = 148,                  /* Finally  */
  YYSYMBOL_PackageDefinition = 149,        /* PackageDefinition  */
  YYSYMBOL_ImportStatement = 150,          /* ImportStatement  */
  YYSYMBOL_PackageName = 151,              /* PackageName  */
  YYSYMBOL_FunctionDeclaration = 152,      /* FunctionDeclaration  */
  YYSYMBOL_ResultSignature = 153,          /* ResultSignature  */
  YYSYMBOL_FunctionExpr = 154,             /* FunctionExpr  */
  YYSYMBOL_FormalParameterList = 155,      /* FormalParameterList  */
  YYSYMBOL_FunctionBody = 156,             /* FunctionBody  */
  YYSYMBOL_ClassDefinition = 157,          /* ClassDefinition  */
  YYSYMBOL_Program = 158,                  /* Program  */
  YYSYMBOL_SourceElements = 159,           /* SourceElements  */
  YYSYMBOL_SourceElement = 160,            /* SourceElement  */
  YYSYMBOL_Attributes = 161,               /* Attributes  */
  YYSYMBOL_Attribute = 162,                /* Attribute  */
  YYSYMBOL_VariableDefinition = 163,       /* VariableDefinition  */
  YYSYMBOL_VariableDefinitionKind = 164,   /* VariableDefinitionKind  */
  YYSYMBOL_VariableBindingList = 165,      /* VariableBindingList  */
  YYSYMBOL_VariableBinding = 166,          /* VariableBinding  */
  YYSYMBOL_TypedVariable = 167,            /* TypedVariable  */
  YYSYMBOL_TypeExpression = 168            /* TypeExpression  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_int16 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined QSYYLTYPE_IS_TRIVIAL && QSYYLTYPE_IS_TRIVIAL \
             && defined QSYYSTYPE_IS_TRIVIAL && QSYYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  200
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1288

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  95
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  74
/* YYNRULES -- Number of rules.  */
#define YYNRULES  224
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  407

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   325


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    84,     2,     2,     2,    86,    89,     2,
      72,    73,    85,    81,    78,    82,    80,    71,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    79,    94,
      87,    93,    88,    92,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    76,     2,    77,    90,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    74,    91,    75,    83,     2,     2,     2,
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
      65,    66,    67,    68,    69,    70
};

#if QSYYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   169,   169,   170,   171,   172,   173,   174,   180,   181,
     183,   184,   185,   186,   187,   191,   192,   193,   197,   198,
     203,   204,   208,   209,   213,   214,   219,   221,   222,   226,
     227,   228,   229,   231,   235,   236,   240,   241,   242,   243,
     248,   249,   253,   254,   258,   259,   263,   264,   265,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   282,
     283,   284,   285,   289,   290,   291,   295,   296,   297,   298,
     302,   303,   305,   307,   309,   311,   313,   315,   320,   321,
     322,   323,   324,   328,   329,   333,   334,   338,   339,   343,
     344,   349,   350,   355,   356,   361,   362,   367,   368,   369,
     370,   371,   372,   373,   374,   375,   376,   377,   378,   382,
     383,   387,   388,   389,   390,   391,   392,   393,   394,   395,
     396,   397,   398,   399,   400,   401,   402,   403,   404,   408,
     409,   413,   414,   418,   422,   424,   432,   433,   438,   439,
     440,   443,   446,   449,   455,   456,   460,   461,   465,   467,
     475,   476,   480,   482,   491,   492,   496,   497,   507,   512,
     517,   518,   523,   524,   528,   529,   533,   534,   538,   539,
     543,   549,   553,   554,   555,   559,   563,   567,   573,   577,
     578,   582,   584,   586,   589,   595,   596,   600,   601,   607,
     609,   611,   612,   617,   618,   622,   624,   626,   632,   633,
     637,   638,   642,   643,   647,   648,   652,   653,   654,   655,
     656,   657,   658,   659,   665,   667,   673,   674,   678,   679,
     684,   685,   689,   691,   698
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NULLTOKEN",
  "TRUETOKEN", "FALSETOKEN", "STRING", "NUMBER", "BREAK", "CASE",
  "DEFAULT", "FOR", "NEW", "VAR", "CONTINUE", "FUNCTION", "RETURN",
  "QS_VOID", "QS_DELETE", "IF", "THIS", "DO", "WHILE", "ELSE", "QS_IN",
  "INSTANCEOF", "TYPEOF", "IS", "SWITCH", "WITH", "RESERVED", "THROW",
  "TRY", "CATCH", "FINALLY", "CLASS", "CONSTRUCTOR", "EXTENDS", "ABSTRACT",
  "FINAL", "PRIVATE", "PUBLIC", "STATIC", "QS_CONST", "PACKAGE", "IMPORT",
  "EQEQ", "NE", "STREQ", "STRNEQ", "LE", "GE", "OR", "AND", "PLUSPLUS",
  "MINUSMINUS", "LSHIFT", "RSHIFT", "URSHIFT", "PLUSEQUAL", "MINUSEQUAL",
  "MULTEQUAL", "DIVEQUAL", "LSHIFTEQUAL", "RSHIFTEQUAL", "URSHIFTEQUAL",
  "ANDEQUAL", "MODEQUAL", "XOREQUAL", "OREQUAL", "IDENT", "'/'", "'('",
  "')'", "'{'", "'}'", "'['", "']'", "','", "':'", "'.'", "'+'", "'-'",
  "'~'", "'!'", "'*'", "'%'", "'<'", "'>'", "'&'", "'^'", "'|'", "'?'",
  "'='", "';'", "$accept", "Literal", "PrimaryExpr", "ArrayLiteral",
  "ElementList", "ElisionOpt", "Elision", "PropertyNameAndValueList",
  "PropertyName", "MemberExpr", "NewExpr", "CallExpr", "Arguments",
  "ArgumentList", "LeftHandSideExpr", "PostfixExpr", "UnaryExpr",
  "MultiplicativeExpr", "AdditiveExpr", "ShiftExpr", "RelationalExpr",
  "EqualityExpr", "BitwiseANDExpr", "BitwiseXORExpr", "BitwiseORExpr",
  "LogicalANDExpr", "LogicalORExpr", "ConditionalExpr", "AssignmentExpr",
  "AssignmentOperator", "Expr", "Statement", "Block", "StatementList",
  "EmptyStatement", "ExprStatement", "IfStatement", "IterationStatement",
  "ExprOpt", "ContinueStatement", "BreakStatement", "ReturnStatement",
  "WithStatement", "SwitchStatement", "CaseBlock", "CaseClausesOpt",
  "CaseClauses", "CaseClause", "DefaultClause", "LabelledStatement",
  "ThrowStatement", "TryStatement", "Catch", "Finally",
  "PackageDefinition", "ImportStatement", "PackageName",
  "FunctionDeclaration", "ResultSignature", "FunctionExpr",
  "FormalParameterList", "FunctionBody", "ClassDefinition", "Program",
  "SourceElements", "SourceElement", "Attributes", "Attribute",
  "VariableDefinition", "VariableDefinitionKind", "VariableBindingList",
  "VariableBinding", "TypedVariable", "TypeExpression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-307)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-213)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     829,  -307,   266,   334,  -307,  -307,     9,    66,   169,  -307,
      15,   127,    63,  1185,  1185,    70,  -307,   913,   119,  1185,
     126,   142,  1185,   164,    22,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,    90,    90,  1185,  1185,   190,  -307,  1185,   409,
     196,  1185,  1185,  1185,  1185,  -307,  -307,  -307,  -307,   -32,
    -307,    56,   910,  -307,  -307,   -40,    89,    73,    98,   207,
     187,   204,   205,   250,   -19,  -307,  -307,    19,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,   310,   829,  -307,
    1102,  -307,  -307,   241,  -307,    25,  -307,   260,  -307,  -307,
     240,  -307,    12,   -32,  -307,  -307,    27,  -307,   244,   -10,
    -307,  -307,    20,    -3,  -307,  -307,  1185,   295,  1245,  1185,
    -307,  1185,  1185,   -36,   493,    67,   -20,  -307,    46,    47,
    -307,  -307,   913,    26,   239,   242,   190,  1005,   158,   243,
    -307,   577,  -307,   135,  1048,   245,  -307,  -307,  -307,  -307,
    1079,  1185,   249,  -307,  1185,   257,  -307,  -307,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,  -307,
    -307,  1185,  1185,  1185,  1185,  1185,  1185,  1185,  1185,  1185,
    1185,  1185,  1185,  1185,  1185,  1185,  1185,  1185,  1185,  1185,
    1185,  1185,  1185,  1185,  1185,  1185,  1185,  -307,  1185,  -307,
    -307,  -307,  -307,  -307,   258,  -307,  -307,   241,   254,   251,
    -307,   227,  -307,  -307,   241,   141,   259,   246,  -307,  -307,
    -307,  -307,  -307,  -307,  -307,   174,   256,   271,    85,  -307,
    -307,    86,   276,    88,   104,   114,  -307,  -307,   278,   164,
     317,  -307,   285,   661,  -307,  -307,   286,  -307,  -307,  -307,
    -307,  -307,    18,  1185,  -307,  -307,  -307,   196,  -307,  -307,
    -307,  -307,   138,  -307,   154,  -307,   184,  -307,  -307,  -307,
    -307,  -307,   -40,   -40,    89,    89,    89,    73,    73,    73,
      73,    73,    73,    73,    98,    98,    98,    98,   207,   187,
     204,   205,   250,   279,  -307,   287,   251,   285,   241,  1185,
     -23,   333,  1185,  1185,   282,   146,   285,  -307,   271,   292,
     913,  1185,   913,   290,   913,   296,  -307,  -307,  -307,   271,
    -307,   745,  -307,   288,  -307,  1161,  -307,  1185,  -307,  -307,
    1185,   176,  -307,  -307,  -307,  1185,  1185,   147,   277,   285,
     271,   282,  -307,  -307,   299,   342,   148,  -307,   373,  -307,
    -307,   312,  -307,  -307,  1185,  -307,  -307,  -307,  -307,   282,
     149,   289,   150,   913,  1185,  -307,  -307,   271,   285,   913,
    -307,  1185,    31,   373,  -307,   164,  -307,   271,   282,  1185,
     913,  -307,   345,  -307,  -307,  -307,   209,   340,  -307,   373,
    -307,  -307,  -307,   271,   359,  -307,   913,   913,   913,   358,
    -307,   913,  -307,   913,   913,  -307,  -307
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
     198,     2,     3,     4,     6,     5,     0,     0,     0,   216,
       0,     0,     0,     0,     0,     0,     8,     0,     0,     0,
       0,     0,     0,     0,     0,   213,   206,   207,   208,   209,
     210,   217,     0,     0,     0,     0,     9,     7,     0,     0,
      20,     0,     0,     0,     0,   133,    10,    29,    11,    34,
      44,    45,    46,    49,    59,    63,    66,    70,    78,    83,
      85,    87,    89,    91,    93,    95,   109,     0,   202,   111,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   115,   128,   203,    30,   113,     0,   199,   200,
       0,   204,   112,     0,   151,     0,   150,   144,     3,     4,
       0,     9,     0,    34,    35,   147,     0,   146,     0,     0,
     155,   154,     0,    46,    51,    50,     0,     0,     0,     0,
      52,     0,     0,     0,     0,     0,     0,   179,     0,     0,
      53,    54,     0,     0,     6,     5,     9,    13,     0,     0,
     131,     0,    22,     0,     0,    21,    55,    56,    57,    58,
       0,     0,     0,    36,     0,     0,    37,    47,    48,    98,
      99,   100,   101,   102,   103,   104,   105,   108,   106,   107,
      97,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   135,     0,   134,
       1,   201,   211,   212,     0,   114,   205,     0,   222,   214,
     218,   220,   153,   152,     0,    46,   145,     0,    27,    28,
      26,    13,    33,   149,   148,     0,   189,     0,     0,   157,
     156,     0,     0,     0,     0,     0,   171,   129,     0,     0,
     172,   173,     0,     0,   195,   196,     0,   177,   178,   170,
      12,    14,     0,     0,   130,   132,    16,    20,    15,    18,
      23,    40,     0,    42,     0,    32,     0,    39,    96,    61,
      60,    62,    64,    65,    67,    68,    69,    77,    76,    75,
      73,    74,    71,    72,    79,    80,    81,    82,    84,    86,
      88,    90,    92,     0,   110,     0,   215,     0,     0,     0,
       0,   218,     0,   144,   185,     0,     0,   187,     0,     0,
       0,     0,     0,     0,     0,     0,   176,   174,   224,     0,
     193,     0,   180,     0,    24,     0,    41,     0,    31,    38,
       0,     0,   223,   219,   221,   144,     0,     0,     0,     0,
       0,   185,   190,   188,   191,   136,     0,   139,   162,   159,
     158,     0,   197,   194,     0,    17,    19,    43,    94,   185,
       0,     0,     0,     0,   144,   186,   181,     0,     0,     0,
     138,     0,     0,   163,   164,     0,    25,     0,   185,   144,
       0,   142,     0,   182,   192,   137,     0,     0,   160,   162,
     165,   175,   183,     0,     0,   143,     0,   166,   168,     0,
     184,     0,   140,   167,   169,   161,   141
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -307,  -307,  -307,  -307,  -307,   177,  -307,  -307,   191,   428,
     431,  -307,    -8,  -307,   216,  -307,    -5,   123,     1,   -30,
      95,   255,   263,   264,   248,   261,  -307,  -307,  -137,  -307,
     -11,   -17,   -21,  -108,  -307,  -307,  -307,  -307,  -288,  -307,
    -307,  -307,  -307,  -307,  -307,    69,  -307,    87,  -307,  -307,
    -307,  -307,  -307,   219,  -307,  -307,   429,  -307,  -306,  -307,
    -219,  -125,   -41,  -307,   218,   -84,     5,   -34,  -307,   -28,
    -157,  -202,  -307,  -274
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    46,    47,    48,   143,   144,   145,   138,   139,    49,
      50,    51,   153,   262,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,   171,
      67,    68,    69,   141,    70,    71,    72,    73,   217,    74,
      75,    76,    77,    78,   349,   372,   373,   374,   389,    79,
      80,    81,   240,   241,    82,    83,   128,    84,   340,    85,
     228,   245,    86,    87,    88,    89,   118,    91,    92,    93,
     209,   210,   211,   319
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     117,   112,   125,   247,   201,    90,   305,   259,   114,   115,
      94,   123,   301,   263,   120,   338,   105,   242,   218,   219,
     197,   229,   140,   332,   218,   219,   212,   133,   223,   130,
     131,   172,   342,   195,   268,   367,   146,   147,   148,   149,
     150,   387,   198,   156,   151,   173,   174,   361,   152,   205,
     296,   157,   158,   377,   243,   298,   206,   300,   236,   293,
     226,   294,   207,   227,   110,   365,     1,    98,    99,     4,
       5,   335,   393,   196,   244,     8,   382,   205,   100,    95,
      13,    14,   220,    16,   206,   106,   216,   221,   220,    19,
     207,   394,   126,    90,   384,   222,   333,   198,   198,   250,
     238,   239,   307,    96,   198,   231,   388,   140,   233,   107,
     234,   235,   360,   199,   230,   249,   324,    34,    35,   213,
     243,   224,   180,   181,   255,   182,   246,   246,   150,   177,
     178,   179,   154,   101,    37,    38,   155,   102,    97,    40,
     264,   248,   116,   266,    41,    42,    43,    44,   183,   184,
     277,   278,   279,   280,   281,   282,   283,   111,   308,   310,
     127,   312,   334,   309,   198,   302,   198,   269,   270,   271,
     175,   176,     1,    98,    99,     4,     5,   313,   274,   275,
     276,     8,   198,   343,   100,   185,   186,   314,   356,    16,
     357,   119,   198,   358,   352,   157,   158,   108,   121,   109,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   326,   256,   257,   122,   366,   327,   376,   316,   341,
     363,   370,   378,   380,   309,   198,   198,   309,   198,   113,
     113,   328,   198,   251,   170,   113,   252,   201,   124,   101,
      37,    38,   383,   102,   226,    40,   226,   304,    90,   359,
     113,   113,   392,   187,   188,   189,   190,   113,   113,   113,
     113,   329,   198,     1,    98,    99,     4,     5,   400,   132,
    -211,  -211,     8,   214,   142,   100,   191,    13,    14,  -211,
      16,  -211,   284,   285,   286,   287,    19,   198,   397,   403,
     404,   337,   216,   345,   192,   347,   193,   350,   272,   273,
     346,  -211,  -211,   194,  -211,  -211,  -211,  -211,  -211,  -211,
     200,   208,   109,   215,    34,    35,   225,   232,   -27,   265,
     299,   -28,   253,   260,   216,   362,    90,   267,   295,   298,
     101,    37,    38,   297,   102,   306,    40,   198,  -212,  -212,
     303,    41,    42,    43,    44,   243,   381,  -212,   311,  -212,
     315,   239,   385,   216,   391,   318,   322,   336,   330,   331,
     386,   339,   344,   395,   348,   369,   351,   354,   216,  -212,
    -212,   364,  -212,  -212,  -212,  -212,  -212,  -212,   368,   402,
     140,   140,   371,   379,   406,   375,   255,   255,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,     1,     2,     3,   134,   135,     6,   396,   398,
       7,     8,     9,    10,   100,    12,    13,    14,    15,    16,
      17,    18,   401,   405,   325,    19,   103,    20,    21,   104,
      22,    23,   291,   323,    24,    25,   288,    26,    27,    28,
      29,    30,    31,    32,    33,   289,   292,   290,   399,   317,
     390,   321,   129,    34,    35,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   136,
      37,    38,     0,    39,   137,    40,     0,     0,     0,     0,
      41,    42,    43,    44,     0,     0,     1,     2,     3,     4,
       5,     6,     0,    45,     7,     8,     9,    10,   100,    12,
      13,    14,    15,    16,    17,    18,     0,     0,     0,    19,
       0,    20,    21,     0,    22,    23,     0,     0,    24,    25,
       0,    26,    27,    28,    29,    30,    31,    32,    33,     0,
       0,     0,     0,     0,     0,     0,     0,    34,    35,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    36,    37,    38,     0,    39,   237,    40,
       0,     0,     0,     0,    41,    42,    43,    44,     0,     0,
       1,     2,     3,     4,     5,     6,     0,    45,     7,     8,
       9,    10,   100,    12,    13,    14,    15,    16,    17,    18,
       0,     0,     0,    19,     0,    20,    21,     0,    22,    23,
       0,     0,    24,    25,     0,    26,    27,    28,    29,    30,
      31,    32,    33,     0,     0,     0,     0,     0,     0,     0,
       0,    34,    35,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    36,    37,    38,
       0,    39,   254,    40,     0,     0,     0,     0,    41,    42,
      43,    44,     0,     0,     1,     2,     3,     4,     5,     6,
       0,    45,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,     0,     0,     0,    19,     0,    20,
      21,     0,    22,    23,     0,     0,    24,    25,     0,    26,
      27,    28,    29,    30,    31,    32,    33,     0,     0,     0,
       0,     0,     0,     0,     0,    34,    35,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    36,    37,    38,     0,    39,   320,    40,     0,     0,
       0,     0,    41,    42,    43,    44,     0,     0,     1,     2,
       3,     4,     5,     6,     0,    45,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,     0,     0,
       0,    19,     0,    20,    21,     0,    22,    23,     0,     0,
      24,    25,     0,    26,    27,    28,    29,    30,    31,    32,
      33,     0,     0,     0,     0,     0,     0,     0,     0,    34,
      35,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    36,    37,    38,     0,    39,
     353,    40,     0,     0,     0,     0,    41,    42,    43,    44,
       0,     0,     1,     2,     3,     4,     5,     6,     0,    45,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,     0,     0,     0,    19,     0,    20,    21,     0,
      22,    23,     0,     0,    24,    25,     0,    26,    27,    28,
      29,    30,    31,    32,    33,     0,     0,     0,     0,     0,
       0,     0,     0,    34,    35,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    36,
      37,    38,     0,    39,     0,    40,     0,     0,     0,     0,
      41,    42,    43,    44,     0,     0,     1,     2,     3,     4,
       5,     6,     0,    45,     7,     8,     9,    10,   100,    12,
      13,    14,    15,    16,    17,    18,     0,     0,     0,    19,
       0,    20,    21,     0,    22,    23,     0,     0,    24,    25,
       0,    26,    27,    28,    29,    30,    31,    32,    33,     0,
       0,     0,     0,     0,   157,   158,     0,    34,    35,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
       0,     0,     0,    36,    37,    38,     0,    39,     0,    40,
       0,     0,     0,     0,    41,    42,    43,    44,     0,     0,
       0,     0,     0,   170,     0,  -129,     0,    45,  -129,  -129,
    -129,  -129,  -129,  -129,  -129,  -129,  -129,  -129,  -129,  -129,
    -129,  -129,  -129,  -129,  -129,  -129,  -129,  -129,  -129,     0,
       0,  -129,     0,  -129,  -129,     0,  -129,  -129,     0,     0,
    -129,  -129,     0,  -129,  -129,  -129,  -129,  -129,  -129,  -129,
    -129,     1,    98,    99,     4,     5,     0,     0,     0,     0,
       8,     0,     0,   100,     0,    13,    14,     0,    16,     0,
       0,     0,     0,     0,    19,  -129,     0,     0,     0,  -129,
    -129,     0,     1,    98,    99,     4,     5,     0,  -129,  -129,
       0,     8,     0,     0,   100,     0,    13,    14,     0,    16,
       0,     0,    34,    35,     0,    19,   202,   203,     0,     0,
       0,     0,     0,     0,     0,     9,     0,   204,   101,    37,
      38,     0,   102,     0,    40,   258,     0,     0,     0,    41,
      42,    43,    44,    34,    35,     0,     0,    24,    25,     0,
      26,    27,    28,    29,    30,    31,     0,     0,     0,   101,
      37,    38,   261,   102,     0,    40,     0,     0,     0,     0,
      41,    42,    43,    44,     1,    98,    99,     4,     5,     0,
       0,     0,     0,     8,     0,     0,   100,     0,    13,    14,
       0,    16,     0,     0,     0,     0,     0,    19,     1,    98,
      99,     4,     5,     0,     0,     0,     0,     8,     0,     0,
     100,     0,    13,    14,     0,    16,     0,     0,     0,     0,
       0,    19,     0,     0,     0,    34,    35,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   101,    37,    38,     0,   102,     0,    40,   355,    34,
      35,     0,    41,    42,    43,    44,     0,     0,     0,   202,
     203,     0,     0,     0,     0,   101,    37,    38,     9,   102,
       0,    40,     0,     0,     0,     0,    41,    42,    43,    44,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      24,    25,     0,    26,    27,    28,    29,    30,    31
};

static const yytype_int16 yycheck[] =
{
      17,    12,    23,   128,    88,     0,   225,   144,    13,    14,
       1,    22,   214,   150,    19,   303,     1,    37,     6,     7,
       1,     1,    39,   297,     6,     7,     1,    38,     1,    34,
      35,    71,   306,    52,   171,   341,    41,    42,    43,    44,
      72,    10,    78,    51,    76,    85,    86,   335,    80,    90,
     207,    54,    55,   359,    74,    78,    90,   214,    94,   196,
      70,   198,    90,    73,     1,   339,     3,     4,     5,     6,
       7,    94,   378,    92,    94,    12,   364,   118,    15,    70,
      17,    18,    70,    20,   118,    70,    97,    75,    70,    26,
     118,   379,    70,    88,   368,   103,   298,    78,    78,    73,
      33,    34,   227,    94,    78,   116,    75,   124,   119,    94,
     121,   122,   331,    94,    94,   132,   253,    54,    55,    94,
      74,    94,    24,    25,   141,    27,    80,    80,    72,    56,
      57,    58,    76,    70,    71,    72,    80,    74,    72,    76,
     151,    94,    72,   154,    81,    82,    83,    84,    50,    51,
     180,   181,   182,   183,   184,   185,   186,    94,    73,    73,
      70,    73,   299,    78,    78,    24,    78,   172,   173,   174,
      81,    82,     3,     4,     5,     6,     7,    73,   177,   178,
     179,    12,    78,   308,    15,    87,    88,    73,   325,    20,
     327,    72,    78,   330,   319,    54,    55,    70,    72,    72,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    73,    77,    78,    72,   340,    78,   354,   239,    73,
      73,    73,    73,    73,    78,    78,    78,    78,    78,    13,
      14,    77,    78,    75,    93,    19,    78,   321,    74,    70,
      71,    72,   367,    74,    70,    76,    70,    73,   243,    73,
      34,    35,   377,    46,    47,    48,    49,    41,    42,    43,
      44,    77,    78,     3,     4,     5,     6,     7,   393,    79,
       4,     5,    12,    13,    78,    15,    89,    17,    18,    13,
      20,    15,   187,   188,   189,   190,    26,    78,    79,   397,
     398,   302,   303,   310,    90,   312,    91,   314,   175,   176,
     311,    35,    36,    53,    38,    39,    40,    41,    42,    43,
       0,    70,    72,    97,    54,    55,    72,    22,    79,    70,
      93,    79,    79,    78,   335,   336,   321,    70,    70,    78,
      70,    71,    72,    79,    74,    79,    76,    78,     4,     5,
      94,    81,    82,    83,    84,    74,   363,    13,    72,    15,
      72,    34,   369,   364,   375,    70,    70,    24,    79,    72,
     371,    79,    70,   380,    74,    23,    70,    79,   379,    35,
      36,    94,    38,    39,    40,    41,    42,    43,    79,   396,
     397,   398,     9,    94,   401,    73,   403,   404,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,     3,     4,     5,     6,     7,     8,    73,    79,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    73,    75,   257,    26,     8,    28,    29,     8,
      31,    32,   194,   252,    35,    36,   191,    38,    39,    40,
      41,    42,    43,    44,    45,   192,   195,   193,   389,   240,
     373,   243,    33,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      71,    72,    -1,    74,    75,    76,    -1,    -1,    -1,    -1,
      81,    82,    83,    84,    -1,    -1,     3,     4,     5,     6,
       7,     8,    -1,    94,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    -1,    -1,    26,
      -1,    28,    29,    -1,    31,    32,    -1,    -1,    35,    36,
      -1,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    71,    72,    -1,    74,    75,    76,
      -1,    -1,    -1,    -1,    81,    82,    83,    84,    -1,    -1,
       3,     4,     5,     6,     7,     8,    -1,    94,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    -1,    -1,    26,    -1,    28,    29,    -1,    31,    32,
      -1,    -1,    35,    36,    -1,    38,    39,    40,    41,    42,
      43,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,
      -1,    74,    75,    76,    -1,    -1,    -1,    -1,    81,    82,
      83,    84,    -1,    -1,     3,     4,     5,     6,     7,     8,
      -1,    94,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    -1,    -1,    26,    -1,    28,
      29,    -1,    31,    32,    -1,    -1,    35,    36,    -1,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    71,    72,    -1,    74,    75,    76,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    -1,    -1,     3,     4,
       5,     6,     7,     8,    -1,    94,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    -1,
      -1,    26,    -1,    28,    29,    -1,    31,    32,    -1,    -1,
      35,    36,    -1,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    71,    72,    -1,    74,
      75,    76,    -1,    -1,    -1,    -1,    81,    82,    83,    84,
      -1,    -1,     3,     4,     5,     6,     7,     8,    -1,    94,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    -1,    -1,    -1,    26,    -1,    28,    29,    -1,
      31,    32,    -1,    -1,    35,    36,    -1,    38,    39,    40,
      41,    42,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      71,    72,    -1,    74,    -1,    76,    -1,    -1,    -1,    -1,
      81,    82,    83,    84,    -1,    -1,     3,     4,     5,     6,
       7,     8,    -1,    94,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    -1,    -1,    -1,    26,
      -1,    28,    29,    -1,    31,    32,    -1,    -1,    35,    36,
      -1,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      -1,    -1,    -1,    -1,    54,    55,    -1,    54,    55,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      -1,    -1,    -1,    70,    71,    72,    -1,    74,    -1,    76,
      -1,    -1,    -1,    -1,    81,    82,    83,    84,    -1,    -1,
      -1,    -1,    -1,    93,    -1,     0,    -1,    94,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    -1,
      -1,    26,    -1,    28,    29,    -1,    31,    32,    -1,    -1,
      35,    36,    -1,    38,    39,    40,    41,    42,    43,    44,
      45,     3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,
      12,    -1,    -1,    15,    -1,    17,    18,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    26,    70,    -1,    -1,    -1,    74,
      75,    -1,     3,     4,     5,     6,     7,    -1,    83,    84,
      -1,    12,    -1,    -1,    15,    -1,    17,    18,    -1,    20,
      -1,    -1,    54,    55,    -1,    26,     4,     5,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    13,    -1,    15,    70,    71,
      72,    -1,    74,    -1,    76,    77,    -1,    -1,    -1,    81,
      82,    83,    84,    54,    55,    -1,    -1,    35,    36,    -1,
      38,    39,    40,    41,    42,    43,    -1,    -1,    -1,    70,
      71,    72,    73,    74,    -1,    76,    -1,    -1,    -1,    -1,
      81,    82,    83,    84,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    -1,    12,    -1,    -1,    15,    -1,    17,    18,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    26,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    -1,    12,    -1,    -1,
      15,    -1,    17,    18,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    26,    -1,    -1,    -1,    54,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    71,    72,    -1,    74,    -1,    76,    77,    54,
      55,    -1,    81,    82,    83,    84,    -1,    -1,    -1,     4,
       5,    -1,    -1,    -1,    -1,    70,    71,    72,    13,    74,
      -1,    76,    -1,    -1,    -1,    -1,    81,    82,    83,    84,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    36,    -1,    38,    39,    40,    41,    42,    43
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    26,
      28,    29,    31,    32,    35,    36,    38,    39,    40,    41,
      42,    43,    44,    45,    54,    55,    70,    71,    72,    74,
      76,    81,    82,    83,    84,    94,    96,    97,    98,   104,
     105,   106,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   125,   126,   127,
     129,   130,   131,   132,   134,   135,   136,   137,   138,   144,
     145,   146,   149,   150,   152,   154,   157,   158,   159,   160,
     161,   162,   163,   164,     1,    70,    94,    72,     4,     5,
      15,    70,    74,   104,   105,     1,    70,    94,    70,    72,
       1,    94,   125,   109,   111,   111,    72,   126,   161,    72,
     111,    72,    72,   125,    74,   127,    70,    70,   151,   151,
     111,   111,    79,   125,     6,     7,    70,    75,   102,   103,
     126,   128,    78,    99,   100,   101,   111,   111,   111,   111,
      72,    76,    80,   107,    76,    80,   107,    54,    55,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      93,   124,    71,    85,    86,    81,    82,    56,    57,    58,
      24,    25,    27,    50,    51,    87,    88,    46,    47,    48,
      49,    89,    90,    91,    53,    52,    92,     1,    78,    94,
       0,   160,     4,     5,    15,   157,   162,   164,    70,   165,
     166,   167,     1,    94,    13,   109,   125,   133,     6,     7,
      70,    75,   107,     1,    94,    72,    70,    73,   155,     1,
      94,   125,    22,   125,   125,   125,    94,    75,    33,    34,
     147,   148,    37,    74,    94,   156,    80,   156,    94,   126,
      73,    75,    78,    79,    75,   126,    77,    78,    77,   123,
      78,    73,   108,   123,   125,    70,   125,    70,   123,   111,
     111,   111,   112,   112,   113,   113,   113,   114,   114,   114,
     114,   114,   114,   114,   115,   115,   115,   115,   116,   117,
     118,   119,   120,   123,   123,    70,   165,    79,    78,    93,
     165,   166,    24,    94,    73,   155,    79,   156,    73,    78,
      73,    72,    73,    73,    73,    72,   127,   148,    70,   168,
      75,   159,    70,   103,   123,   100,    73,    78,    77,    77,
      79,    72,   168,   166,   123,    94,    24,   125,   133,    79,
     153,    73,   168,   156,    70,   126,   125,   126,    74,   139,
     126,    70,   156,    75,    79,    77,   123,   123,   123,    73,
     155,   133,   125,    73,    94,   168,   156,   153,    79,    23,
      73,     9,   140,   141,   142,    73,   123,   153,    73,    94,
      73,   126,   133,   156,   168,   126,   125,    10,    75,   143,
     142,   127,   156,   153,   133,   126,    73,    79,    79,   140,
     156,    73,   126,   128,   128,    75,   126
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    95,    96,    96,    96,    96,    96,    96,    97,    97,
      97,    97,    97,    97,    97,    98,    98,    98,    99,    99,
     100,   100,   101,   101,   102,   102,   103,   103,   103,   104,
     104,   104,   104,   104,   105,   105,   106,   106,   106,   106,
     107,   107,   108,   108,   109,   109,   110,   110,   110,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   112,
     112,   112,   112,   113,   113,   113,   114,   114,   114,   114,
     115,   115,   115,   115,   115,   115,   115,   115,   116,   116,
     116,   116,   116,   117,   117,   118,   118,   119,   119,   120,
     120,   121,   121,   122,   122,   123,   123,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   125,
     125,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   127,
     127,   128,   128,   129,   130,   130,   131,   131,   132,   132,
     132,   132,   132,   132,   133,   133,   134,   134,   134,   134,
     135,   135,   135,   135,   136,   136,   136,   136,   137,   138,
     139,   139,   140,   140,   141,   141,   142,   142,   143,   143,
     144,   145,   146,   146,   146,   147,   148,   149,   150,   151,
     151,   152,   152,   152,   152,   153,   153,   154,   154,   155,
     155,   155,   155,   156,   156,   157,   157,   157,   158,   158,
     159,   159,   160,   160,   161,   161,   162,   162,   162,   162,
     162,   162,   162,   162,   163,   163,   164,   164,   165,   165,
     166,   166,   167,   167,   168
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     2,     3,     3,     3,     5,     2,     4,
       0,     1,     1,     2,     3,     5,     1,     1,     1,     1,
       1,     4,     3,     3,     1,     2,     2,     2,     4,     3,
       2,     3,     1,     3,     1,     1,     1,     2,     2,     1,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     1,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       1,     3,     3,     3,     3,     3,     3,     3,     1,     3,
       3,     3,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     5,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       3,     1,     2,     1,     2,     2,     5,     7,     6,     5,
       9,    10,     7,     8,     0,     1,     2,     2,     3,     3,
       2,     2,     3,     3,     2,     2,     3,     3,     5,     5,
       3,     5,     0,     1,     1,     2,     3,     4,     2,     3,
       3,     3,     3,     3,     4,     5,     2,     3,     3,     1,
       3,     6,     7,     7,     8,     0,     2,     4,     5,     1,
       3,     3,     5,     2,     3,     3,     3,     5,     0,     1,
       1,     2,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     3,     1,     1,     1,     3,
       1,     3,     1,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = QSYYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == QSYYEMPTY)                                        \
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

/* Backward compatibility with an undocumented macro.
   Use QSYYerror or QSYYUNDEF. */
#define YYERRCODE QSYYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if QSYYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined QSYYLTYPE_IS_TRIVIAL && QSYYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !QSYYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !QSYYDEBUG */


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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
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
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
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
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
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


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind)
    {
    case YYSYMBOL_STRING: /* STRING  */
#line 48 "grammar.y"
            { delete ((*yyvaluep).ustr); }
#line 1851 "grammar.cpp"
        break;

    case YYSYMBOL_IDENT: /* IDENT  */
#line 48 "grammar.y"
            { delete ((*yyvaluep).ustr); }
#line 1857 "grammar.cpp"
        break;

    case YYSYMBOL_Literal: /* Literal  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 1863 "grammar.cpp"
        break;

    case YYSYMBOL_PrimaryExpr: /* PrimaryExpr  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 1869 "grammar.cpp"
        break;

    case YYSYMBOL_ArrayLiteral: /* ArrayLiteral  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 1875 "grammar.cpp"
        break;

    case YYSYMBOL_ElementList: /* ElementList  */
#line 45 "grammar.y"
            { if (((*yyvaluep).elm) && ((*yyvaluep).elm)->deref()) delete ((*yyvaluep).elm); }
#line 1881 "grammar.cpp"
        break;

    case YYSYMBOL_ElisionOpt: /* ElisionOpt  */
#line 45 "grammar.y"
            { if (((*yyvaluep).eli) && ((*yyvaluep).eli)->deref()) delete ((*yyvaluep).eli); }
#line 1887 "grammar.cpp"
        break;

    case YYSYMBOL_Elision: /* Elision  */
#line 45 "grammar.y"
            { if (((*yyvaluep).eli) && ((*yyvaluep).eli)->deref()) delete ((*yyvaluep).eli); }
#line 1893 "grammar.cpp"
        break;

    case YYSYMBOL_PropertyNameAndValueList: /* PropertyNameAndValueList  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 1899 "grammar.cpp"
        break;

    case YYSYMBOL_PropertyName: /* PropertyName  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 1905 "grammar.cpp"
        break;

    case YYSYMBOL_MemberExpr: /* MemberExpr  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 1911 "grammar.cpp"
        break;

    case YYSYMBOL_NewExpr: /* NewExpr  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 1917 "grammar.cpp"
        break;

    case YYSYMBOL_CallExpr: /* CallExpr  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 1923 "grammar.cpp"
        break;

    case YYSYMBOL_Arguments: /* Arguments  */
#line 45 "grammar.y"
            { if (((*yyvaluep).args) && ((*yyvaluep).args)->deref()) delete ((*yyvaluep).args); }
#line 1929 "grammar.cpp"
        break;

    case YYSYMBOL_ArgumentList: /* ArgumentList  */
#line 45 "grammar.y"
            { if (((*yyvaluep).alist) && ((*yyvaluep).alist)->deref()) delete ((*yyvaluep).alist); }
#line 1935 "grammar.cpp"
        break;

    case YYSYMBOL_LeftHandSideExpr: /* LeftHandSideExpr  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 1941 "grammar.cpp"
        break;

    case YYSYMBOL_PostfixExpr: /* PostfixExpr  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 1947 "grammar.cpp"
        break;

    case YYSYMBOL_UnaryExpr: /* UnaryExpr  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 1953 "grammar.cpp"
        break;

    case YYSYMBOL_MultiplicativeExpr: /* MultiplicativeExpr  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 1959 "grammar.cpp"
        break;

    case YYSYMBOL_AdditiveExpr: /* AdditiveExpr  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 1965 "grammar.cpp"
        break;

    case YYSYMBOL_ShiftExpr: /* ShiftExpr  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 1971 "grammar.cpp"
        break;

    case YYSYMBOL_RelationalExpr: /* RelationalExpr  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 1977 "grammar.cpp"
        break;

    case YYSYMBOL_EqualityExpr: /* EqualityExpr  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 1983 "grammar.cpp"
        break;

    case YYSYMBOL_BitwiseANDExpr: /* BitwiseANDExpr  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 1989 "grammar.cpp"
        break;

    case YYSYMBOL_BitwiseXORExpr: /* BitwiseXORExpr  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 1995 "grammar.cpp"
        break;

    case YYSYMBOL_BitwiseORExpr: /* BitwiseORExpr  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 2001 "grammar.cpp"
        break;

    case YYSYMBOL_LogicalANDExpr: /* LogicalANDExpr  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 2007 "grammar.cpp"
        break;

    case YYSYMBOL_LogicalORExpr: /* LogicalORExpr  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 2013 "grammar.cpp"
        break;

    case YYSYMBOL_ConditionalExpr: /* ConditionalExpr  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 2019 "grammar.cpp"
        break;

    case YYSYMBOL_AssignmentExpr: /* AssignmentExpr  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 2025 "grammar.cpp"
        break;

    case YYSYMBOL_Expr: /* Expr  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 2031 "grammar.cpp"
        break;

    case YYSYMBOL_Statement: /* Statement  */
#line 45 "grammar.y"
            { if (((*yyvaluep).stat) && ((*yyvaluep).stat)->deref()) delete ((*yyvaluep).stat); }
#line 2037 "grammar.cpp"
        break;

    case YYSYMBOL_Block: /* Block  */
#line 45 "grammar.y"
            { if (((*yyvaluep).stat) && ((*yyvaluep).stat)->deref()) delete ((*yyvaluep).stat); }
#line 2043 "grammar.cpp"
        break;

    case YYSYMBOL_StatementList: /* StatementList  */
#line 45 "grammar.y"
            { if (((*yyvaluep).slist) && ((*yyvaluep).slist)->deref()) delete ((*yyvaluep).slist); }
#line 2049 "grammar.cpp"
        break;

    case YYSYMBOL_EmptyStatement: /* EmptyStatement  */
#line 45 "grammar.y"
            { if (((*yyvaluep).stat) && ((*yyvaluep).stat)->deref()) delete ((*yyvaluep).stat); }
#line 2055 "grammar.cpp"
        break;

    case YYSYMBOL_ExprStatement: /* ExprStatement  */
#line 45 "grammar.y"
            { if (((*yyvaluep).stat) && ((*yyvaluep).stat)->deref()) delete ((*yyvaluep).stat); }
#line 2061 "grammar.cpp"
        break;

    case YYSYMBOL_IfStatement: /* IfStatement  */
#line 45 "grammar.y"
            { if (((*yyvaluep).stat) && ((*yyvaluep).stat)->deref()) delete ((*yyvaluep).stat); }
#line 2067 "grammar.cpp"
        break;

    case YYSYMBOL_IterationStatement: /* IterationStatement  */
#line 45 "grammar.y"
            { if (((*yyvaluep).stat) && ((*yyvaluep).stat)->deref()) delete ((*yyvaluep).stat); }
#line 2073 "grammar.cpp"
        break;

    case YYSYMBOL_ExprOpt: /* ExprOpt  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 2079 "grammar.cpp"
        break;

    case YYSYMBOL_ContinueStatement: /* ContinueStatement  */
#line 45 "grammar.y"
            { if (((*yyvaluep).stat) && ((*yyvaluep).stat)->deref()) delete ((*yyvaluep).stat); }
#line 2085 "grammar.cpp"
        break;

    case YYSYMBOL_BreakStatement: /* BreakStatement  */
#line 45 "grammar.y"
            { if (((*yyvaluep).stat) && ((*yyvaluep).stat)->deref()) delete ((*yyvaluep).stat); }
#line 2091 "grammar.cpp"
        break;

    case YYSYMBOL_ReturnStatement: /* ReturnStatement  */
#line 45 "grammar.y"
            { if (((*yyvaluep).stat) && ((*yyvaluep).stat)->deref()) delete ((*yyvaluep).stat); }
#line 2097 "grammar.cpp"
        break;

    case YYSYMBOL_WithStatement: /* WithStatement  */
#line 45 "grammar.y"
            { if (((*yyvaluep).stat) && ((*yyvaluep).stat)->deref()) delete ((*yyvaluep).stat); }
#line 2103 "grammar.cpp"
        break;

    case YYSYMBOL_SwitchStatement: /* SwitchStatement  */
#line 45 "grammar.y"
            { if (((*yyvaluep).stat) && ((*yyvaluep).stat)->deref()) delete ((*yyvaluep).stat); }
#line 2109 "grammar.cpp"
        break;

    case YYSYMBOL_CaseBlock: /* CaseBlock  */
#line 45 "grammar.y"
            { if (((*yyvaluep).cblk) && ((*yyvaluep).cblk)->deref()) delete ((*yyvaluep).cblk); }
#line 2115 "grammar.cpp"
        break;

    case YYSYMBOL_CaseClausesOpt: /* CaseClausesOpt  */
#line 45 "grammar.y"
            { if (((*yyvaluep).clist) && ((*yyvaluep).clist)->deref()) delete ((*yyvaluep).clist); }
#line 2121 "grammar.cpp"
        break;

    case YYSYMBOL_CaseClauses: /* CaseClauses  */
#line 45 "grammar.y"
            { if (((*yyvaluep).clist) && ((*yyvaluep).clist)->deref()) delete ((*yyvaluep).clist); }
#line 2127 "grammar.cpp"
        break;

    case YYSYMBOL_CaseClause: /* CaseClause  */
#line 45 "grammar.y"
            { if (((*yyvaluep).ccl) && ((*yyvaluep).ccl)->deref()) delete ((*yyvaluep).ccl); }
#line 2133 "grammar.cpp"
        break;

    case YYSYMBOL_DefaultClause: /* DefaultClause  */
#line 45 "grammar.y"
            { if (((*yyvaluep).ccl) && ((*yyvaluep).ccl)->deref()) delete ((*yyvaluep).ccl); }
#line 2139 "grammar.cpp"
        break;

    case YYSYMBOL_LabelledStatement: /* LabelledStatement  */
#line 45 "grammar.y"
            { if (((*yyvaluep).stat) && ((*yyvaluep).stat)->deref()) delete ((*yyvaluep).stat); }
#line 2145 "grammar.cpp"
        break;

    case YYSYMBOL_ThrowStatement: /* ThrowStatement  */
#line 45 "grammar.y"
            { if (((*yyvaluep).stat) && ((*yyvaluep).stat)->deref()) delete ((*yyvaluep).stat); }
#line 2151 "grammar.cpp"
        break;

    case YYSYMBOL_TryStatement: /* TryStatement  */
#line 45 "grammar.y"
            { if (((*yyvaluep).stat) && ((*yyvaluep).stat)->deref()) delete ((*yyvaluep).stat); }
#line 2157 "grammar.cpp"
        break;

    case YYSYMBOL_Catch: /* Catch  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 2163 "grammar.cpp"
        break;

    case YYSYMBOL_Finally: /* Finally  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 2169 "grammar.cpp"
        break;

    case YYSYMBOL_PackageDefinition: /* PackageDefinition  */
#line 45 "grammar.y"
            { if (((*yyvaluep).stat) && ((*yyvaluep).stat)->deref()) delete ((*yyvaluep).stat); }
#line 2175 "grammar.cpp"
        break;

    case YYSYMBOL_ImportStatement: /* ImportStatement  */
#line 45 "grammar.y"
            { if (((*yyvaluep).stat) && ((*yyvaluep).stat)->deref()) delete ((*yyvaluep).stat); }
#line 2181 "grammar.cpp"
        break;

    case YYSYMBOL_PackageName: /* PackageName  */
#line 48 "grammar.y"
            { delete ((*yyvaluep).ustr); }
#line 2187 "grammar.cpp"
        break;

    case YYSYMBOL_FunctionDeclaration: /* FunctionDeclaration  */
#line 45 "grammar.y"
            { if (((*yyvaluep).func) && ((*yyvaluep).func)->deref()) delete ((*yyvaluep).func); }
#line 2193 "grammar.cpp"
        break;

    case YYSYMBOL_ResultSignature: /* ResultSignature  */
#line 45 "grammar.y"
            { if (((*yyvaluep).type) && ((*yyvaluep).type)->deref()) delete ((*yyvaluep).type); }
#line 2199 "grammar.cpp"
        break;

    case YYSYMBOL_FunctionExpr: /* FunctionExpr  */
#line 45 "grammar.y"
            { if (((*yyvaluep).node) && ((*yyvaluep).node)->deref()) delete ((*yyvaluep).node); }
#line 2205 "grammar.cpp"
        break;

    case YYSYMBOL_FormalParameterList: /* FormalParameterList  */
#line 45 "grammar.y"
            { if (((*yyvaluep).param) && ((*yyvaluep).param)->deref()) delete ((*yyvaluep).param); }
#line 2211 "grammar.cpp"
        break;

    case YYSYMBOL_FunctionBody: /* FunctionBody  */
#line 45 "grammar.y"
            { if (((*yyvaluep).body) && ((*yyvaluep).body)->deref()) delete ((*yyvaluep).body); }
#line 2217 "grammar.cpp"
        break;

    case YYSYMBOL_ClassDefinition: /* ClassDefinition  */
#line 45 "grammar.y"
            { if (((*yyvaluep).clss) && ((*yyvaluep).clss)->deref()) delete ((*yyvaluep).clss); }
#line 2223 "grammar.cpp"
        break;

    case YYSYMBOL_SourceElements: /* SourceElements  */
#line 45 "grammar.y"
            { if (((*yyvaluep).srcs) && ((*yyvaluep).srcs)->deref()) delete ((*yyvaluep).srcs); }
#line 2229 "grammar.cpp"
        break;

    case YYSYMBOL_SourceElement: /* SourceElement  */
#line 45 "grammar.y"
            { if (((*yyvaluep).src) && ((*yyvaluep).src)->deref()) delete ((*yyvaluep).src); }
#line 2235 "grammar.cpp"
        break;

    case YYSYMBOL_Attributes: /* Attributes  */
#line 45 "grammar.y"
            { if (((*yyvaluep).attrs) && ((*yyvaluep).attrs)->deref()) delete ((*yyvaluep).attrs); }
#line 2241 "grammar.cpp"
        break;

    case YYSYMBOL_VariableDefinition: /* VariableDefinition  */
#line 45 "grammar.y"
            { if (((*yyvaluep).stat) && ((*yyvaluep).stat)->deref()) delete ((*yyvaluep).stat); }
#line 2247 "grammar.cpp"
        break;

    case YYSYMBOL_VariableBindingList: /* VariableBindingList  */
#line 45 "grammar.y"
            { if (((*yyvaluep).blist) && ((*yyvaluep).blist)->deref()) delete ((*yyvaluep).blist); }
#line 2253 "grammar.cpp"
        break;

    case YYSYMBOL_VariableBinding: /* VariableBinding  */
#line 45 "grammar.y"
            { if (((*yyvaluep).vbin) && ((*yyvaluep).vbin)->deref()) delete ((*yyvaluep).vbin); }
#line 2259 "grammar.cpp"
        break;

    case YYSYMBOL_TypedVariable: /* TypedVariable  */
#line 45 "grammar.y"
            { if (((*yyvaluep).tvar) && ((*yyvaluep).tvar)->deref()) delete ((*yyvaluep).tvar); }
#line 2265 "grammar.cpp"
        break;

    case YYSYMBOL_TypeExpression: /* TypeExpression  */
#line 45 "grammar.y"
            { if (((*yyvaluep).type) && ((*yyvaluep).type)->deref()) delete ((*yyvaluep).type); }
#line 2271 "grammar.cpp"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined QSYYLTYPE_IS_TRIVIAL && QSYYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = QSYYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == QSYYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= QSYYEOF)
    {
      yychar = QSYYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == QSYYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = QSYYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = QSYYEMPTY;
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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Literal: NULLTOKEN  */
#line 169 "grammar.y"
                                   { (yyval.node) = new QSNullNode(); }
#line 2569 "grammar.cpp"
    break;

  case 3: /* Literal: TRUETOKEN  */
#line 170 "grammar.y"
                                   { (yyval.node) = new QSBooleanNode(true); }
#line 2575 "grammar.cpp"
    break;

  case 4: /* Literal: FALSETOKEN  */
#line 171 "grammar.y"
                                   { (yyval.node) = new QSBooleanNode(false); }
#line 2581 "grammar.cpp"
    break;

  case 5: /* Literal: NUMBER  */
#line 172 "grammar.y"
                                   { (yyval.node) = new QSNumberNode((yyvsp[0].dval)); }
#line 2587 "grammar.cpp"
    break;

  case 6: /* Literal: STRING  */
#line 173 "grammar.y"
                                   { (yyval.node) = new QSStringNode((yyvsp[0].ustr)); delete (yyvsp[0].ustr); }
#line 2593 "grammar.cpp"
    break;

  case 7: /* Literal: '/'  */
#line 174 "grammar.y"
                                   { QSLexer *l = QSLexer::lexer();
                                     if (!l->scanRegExp()) YYABORT;
                                     (yyval.node) = new QSRegExpNode(l->pattern,l->flags);}
#line 2601 "grammar.cpp"
    break;

  case 8: /* PrimaryExpr: THIS  */
#line 180 "grammar.y"
                                   { (yyval.node) = new QSThisNode(); }
#line 2607 "grammar.cpp"
    break;

  case 9: /* PrimaryExpr: IDENT  */
#line 181 "grammar.y"
                                   { (yyval.node) = new QSResolveNode((yyvsp[0].ustr));
                                     delete (yyvsp[0].ustr); }
#line 2614 "grammar.cpp"
    break;

  case 12: /* PrimaryExpr: '(' Expr ')'  */
#line 185 "grammar.y"
                                   { (yyval.node) = new QSGroupNode((yyvsp[-1].node)); }
#line 2620 "grammar.cpp"
    break;

  case 13: /* PrimaryExpr: '{' '}'  */
#line 186 "grammar.y"
                                   { (yyval.node) = new QSObjectLiteralNode(0L); }
#line 2626 "grammar.cpp"
    break;

  case 14: /* PrimaryExpr: '{' PropertyNameAndValueList '}'  */
#line 187 "grammar.y"
                                       { (yyval.node) = new QSObjectLiteralNode((yyvsp[-1].node)); }
#line 2632 "grammar.cpp"
    break;

  case 15: /* ArrayLiteral: '[' ElisionOpt ']'  */
#line 191 "grammar.y"
                                       { (yyval.node) = new QSArrayNode((yyvsp[-1].eli)); }
#line 2638 "grammar.cpp"
    break;

  case 16: /* ArrayLiteral: '[' ElementList ']'  */
#line 192 "grammar.y"
                                       { (yyval.node) = new QSArrayNode((yyvsp[-1].elm)); }
#line 2644 "grammar.cpp"
    break;

  case 17: /* ArrayLiteral: '[' ElementList ',' ElisionOpt ']'  */
#line 193 "grammar.y"
                                       { (yyval.node) = new QSArrayNode((yyvsp[-1].eli), (yyvsp[-3].elm)); }
#line 2650 "grammar.cpp"
    break;

  case 18: /* ElementList: ElisionOpt AssignmentExpr  */
#line 197 "grammar.y"
                                   { (yyval.elm) = new QSElementNode((yyvsp[-1].eli), (yyvsp[0].node)); }
#line 2656 "grammar.cpp"
    break;

  case 19: /* ElementList: ElementList ',' ElisionOpt AssignmentExpr  */
#line 199 "grammar.y"
                                   { (yyval.elm) = new QSElementNode((yyvsp[-3].elm), (yyvsp[-1].eli), (yyvsp[0].node)); }
#line 2662 "grammar.cpp"
    break;

  case 20: /* ElisionOpt: %empty  */
#line 203 "grammar.y"
                                   { (yyval.eli) = 0L; }
#line 2668 "grammar.cpp"
    break;

  case 22: /* Elision: ','  */
#line 208 "grammar.y"
                                   { (yyval.eli) = new QSElisionNode(0L); }
#line 2674 "grammar.cpp"
    break;

  case 23: /* Elision: Elision ','  */
#line 209 "grammar.y"
                                   { (yyval.eli) = new QSElisionNode((yyvsp[-1].eli)); }
#line 2680 "grammar.cpp"
    break;

  case 24: /* PropertyNameAndValueList: PropertyName ':' AssignmentExpr  */
#line 213 "grammar.y"
                                        { (yyval.node) = new QSPropertyValueNode((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2686 "grammar.cpp"
    break;

  case 25: /* PropertyNameAndValueList: PropertyNameAndValueList ',' PropertyName ':' AssignmentExpr  */
#line 215 "grammar.y"
                                   { (yyval.node) = new QSPropertyValueNode((yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-4].node)); }
#line 2692 "grammar.cpp"
    break;

  case 26: /* PropertyName: IDENT  */
#line 219 "grammar.y"
                                   { (yyval.node) = new QSPropertyNode((yyvsp[0].ustr));
                                     delete (yyvsp[0].ustr); }
#line 2699 "grammar.cpp"
    break;

  case 27: /* PropertyName: STRING  */
#line 221 "grammar.y"
                                   { (yyval.node) = new QSPropertyNode((yyvsp[0].ustr)); delete (yyvsp[0].ustr); }
#line 2705 "grammar.cpp"
    break;

  case 28: /* PropertyName: NUMBER  */
#line 222 "grammar.y"
                                   { (yyval.node) = new QSPropertyNode((yyvsp[0].dval)); }
#line 2711 "grammar.cpp"
    break;

  case 31: /* MemberExpr: MemberExpr '[' Expr ']'  */
#line 228 "grammar.y"
                                   { (yyval.node) = new QSAccessorNode1((yyvsp[-3].node), (yyvsp[-1].node)); }
#line 2717 "grammar.cpp"
    break;

  case 32: /* MemberExpr: MemberExpr '.' IDENT  */
#line 229 "grammar.y"
                                   { (yyval.node) = new QSAccessorNode2((yyvsp[-2].node), (yyvsp[0].ustr));
                                     delete (yyvsp[0].ustr); }
#line 2724 "grammar.cpp"
    break;

  case 33: /* MemberExpr: NEW MemberExpr Arguments  */
#line 231 "grammar.y"
                                   { (yyval.node) = new QSNewExprNode((yyvsp[-1].node), (yyvsp[0].args)); }
#line 2730 "grammar.cpp"
    break;

  case 35: /* NewExpr: NEW NewExpr  */
#line 236 "grammar.y"
                                   { (yyval.node) = new QSNewExprNode((yyvsp[0].node)); }
#line 2736 "grammar.cpp"
    break;

  case 36: /* CallExpr: MemberExpr Arguments  */
#line 240 "grammar.y"
                                   { (yyval.node) = new QSFunctionCallNode((yyvsp[-1].node), (yyvsp[0].args)); }
#line 2742 "grammar.cpp"
    break;

  case 37: /* CallExpr: CallExpr Arguments  */
#line 241 "grammar.y"
                                   { (yyval.node) = new QSFunctionCallNode((yyvsp[-1].node), (yyvsp[0].args)); }
#line 2748 "grammar.cpp"
    break;

  case 38: /* CallExpr: CallExpr '[' Expr ']'  */
#line 242 "grammar.y"
                                   { (yyval.node) = new QSAccessorNode1((yyvsp[-3].node), (yyvsp[-1].node)); }
#line 2754 "grammar.cpp"
    break;

  case 39: /* CallExpr: CallExpr '.' IDENT  */
#line 243 "grammar.y"
                                   { (yyval.node) = new QSAccessorNode2((yyvsp[-2].node), (yyvsp[0].ustr));
                                     delete (yyvsp[0].ustr); }
#line 2761 "grammar.cpp"
    break;

  case 40: /* Arguments: '(' ')'  */
#line 248 "grammar.y"
                                   { (yyval.args) = new QSArgumentsNode(0L); }
#line 2767 "grammar.cpp"
    break;

  case 41: /* Arguments: '(' ArgumentList ')'  */
#line 249 "grammar.y"
                                   { (yyval.args) = new QSArgumentsNode((yyvsp[-1].alist)); }
#line 2773 "grammar.cpp"
    break;

  case 42: /* ArgumentList: AssignmentExpr  */
#line 253 "grammar.y"
                                    { (yyval.alist) = new QSArgumentListNode((yyvsp[0].node)); }
#line 2779 "grammar.cpp"
    break;

  case 43: /* ArgumentList: ArgumentList ',' AssignmentExpr  */
#line 254 "grammar.y"
                                    { (yyval.alist) = new QSArgumentListNode((yyvsp[-2].alist), (yyvsp[0].node)); }
#line 2785 "grammar.cpp"
    break;

  case 47: /* PostfixExpr: LeftHandSideExpr PLUSPLUS  */
#line 264 "grammar.y"
                                   { (yyval.node) = new QSPostfixNode((yyvsp[-1].node), OpPlusPlus); }
#line 2791 "grammar.cpp"
    break;

  case 48: /* PostfixExpr: LeftHandSideExpr MINUSMINUS  */
#line 265 "grammar.y"
                                   { (yyval.node) = new QSPostfixNode((yyvsp[-1].node), OpMinusMinus); }
#line 2797 "grammar.cpp"
    break;

  case 50: /* UnaryExpr: QS_DELETE UnaryExpr  */
#line 270 "grammar.y"
                                   { (yyval.node) = new QSDeleteNode((yyvsp[0].node)); }
#line 2803 "grammar.cpp"
    break;

  case 51: /* UnaryExpr: QS_VOID UnaryExpr  */
#line 271 "grammar.y"
                                   { (yyval.node) = new QSVoidNode((yyvsp[0].node)); }
#line 2809 "grammar.cpp"
    break;

  case 52: /* UnaryExpr: TYPEOF UnaryExpr  */
#line 272 "grammar.y"
                                   { (yyval.node) = new QSTypeOfNode((yyvsp[0].node)); }
#line 2815 "grammar.cpp"
    break;

  case 53: /* UnaryExpr: PLUSPLUS UnaryExpr  */
#line 273 "grammar.y"
                                   { (yyval.node) = new QSPrefixNode(OpPlusPlus, (yyvsp[0].node)); }
#line 2821 "grammar.cpp"
    break;

  case 54: /* UnaryExpr: MINUSMINUS UnaryExpr  */
#line 274 "grammar.y"
                                   { (yyval.node) = new QSPrefixNode(OpMinusMinus, (yyvsp[0].node)); }
#line 2827 "grammar.cpp"
    break;

  case 55: /* UnaryExpr: '+' UnaryExpr  */
#line 275 "grammar.y"
                                   { (yyval.node) = new QSUnaryPlusNode((yyvsp[0].node)); }
#line 2833 "grammar.cpp"
    break;

  case 56: /* UnaryExpr: '-' UnaryExpr  */
#line 276 "grammar.y"
                                   { (yyval.node) = new QSNegateNode((yyvsp[0].node)); }
#line 2839 "grammar.cpp"
    break;

  case 57: /* UnaryExpr: '~' UnaryExpr  */
#line 277 "grammar.y"
                                   { (yyval.node) = new QSBitwiseNotNode((yyvsp[0].node)); }
#line 2845 "grammar.cpp"
    break;

  case 58: /* UnaryExpr: '!' UnaryExpr  */
#line 278 "grammar.y"
                                   { (yyval.node) = new QSLogicalNotNode((yyvsp[0].node)); }
#line 2851 "grammar.cpp"
    break;

  case 60: /* MultiplicativeExpr: MultiplicativeExpr '*' UnaryExpr  */
#line 283 "grammar.y"
                                     { (yyval.node) = new QSMultNode((yyvsp[-2].node), (yyvsp[0].node), '*'); }
#line 2857 "grammar.cpp"
    break;

  case 61: /* MultiplicativeExpr: MultiplicativeExpr '/' UnaryExpr  */
#line 284 "grammar.y"
                                     { (yyval.node) = new QSMultNode((yyvsp[-2].node), (yyvsp[0].node), '/'); }
#line 2863 "grammar.cpp"
    break;

  case 62: /* MultiplicativeExpr: MultiplicativeExpr '%' UnaryExpr  */
#line 285 "grammar.y"
                                     { (yyval.node) = new QSMultNode((yyvsp[-2].node),(yyvsp[0].node),'%'); }
#line 2869 "grammar.cpp"
    break;

  case 64: /* AdditiveExpr: AdditiveExpr '+' MultiplicativeExpr  */
#line 290 "grammar.y"
                                        { (yyval.node) = new QSAddNode((yyvsp[-2].node), (yyvsp[0].node), '+'); }
#line 2875 "grammar.cpp"
    break;

  case 65: /* AdditiveExpr: AdditiveExpr '-' MultiplicativeExpr  */
#line 291 "grammar.y"
                                        { (yyval.node) = new QSAddNode((yyvsp[-2].node), (yyvsp[0].node), '-'); }
#line 2881 "grammar.cpp"
    break;

  case 67: /* ShiftExpr: ShiftExpr LSHIFT AdditiveExpr  */
#line 296 "grammar.y"
                                   { (yyval.node) = new QSShiftNode((yyvsp[-2].node), OpLShift, (yyvsp[0].node)); }
#line 2887 "grammar.cpp"
    break;

  case 68: /* ShiftExpr: ShiftExpr RSHIFT AdditiveExpr  */
#line 297 "grammar.y"
                                   { (yyval.node) = new QSShiftNode((yyvsp[-2].node), OpRShift, (yyvsp[0].node)); }
#line 2893 "grammar.cpp"
    break;

  case 69: /* ShiftExpr: ShiftExpr URSHIFT AdditiveExpr  */
#line 298 "grammar.y"
                                   { (yyval.node) = new QSShiftNode((yyvsp[-2].node), OpURShift, (yyvsp[0].node)); }
#line 2899 "grammar.cpp"
    break;

  case 71: /* RelationalExpr: RelationalExpr '<' ShiftExpr  */
#line 304 "grammar.y"
                           { (yyval.node) = new QSRelationalNode((yyvsp[-2].node), OpLess, (yyvsp[0].node)); }
#line 2905 "grammar.cpp"
    break;

  case 72: /* RelationalExpr: RelationalExpr '>' ShiftExpr  */
#line 306 "grammar.y"
                           { (yyval.node) = new QSRelationalNode((yyvsp[-2].node), OpGreater, (yyvsp[0].node)); }
#line 2911 "grammar.cpp"
    break;

  case 73: /* RelationalExpr: RelationalExpr LE ShiftExpr  */
#line 308 "grammar.y"
                           { (yyval.node) = new QSRelationalNode((yyvsp[-2].node), OpLessEq, (yyvsp[0].node)); }
#line 2917 "grammar.cpp"
    break;

  case 74: /* RelationalExpr: RelationalExpr GE ShiftExpr  */
#line 310 "grammar.y"
                           { (yyval.node) = new QSRelationalNode((yyvsp[-2].node), OpGreaterEq, (yyvsp[0].node)); }
#line 2923 "grammar.cpp"
    break;

  case 75: /* RelationalExpr: RelationalExpr IS ShiftExpr  */
#line 312 "grammar.y"
                           { (yyval.node) = new QSRelationalNode((yyvsp[-2].node), OpIs, (yyvsp[0].node)); }
#line 2929 "grammar.cpp"
    break;

  case 76: /* RelationalExpr: RelationalExpr INSTANCEOF ShiftExpr  */
#line 314 "grammar.y"
                           { (yyval.node) = new QSRelationalNode((yyvsp[-2].node), OpInstanceOf, (yyvsp[0].node)); }
#line 2935 "grammar.cpp"
    break;

  case 77: /* RelationalExpr: RelationalExpr QS_IN ShiftExpr  */
#line 316 "grammar.y"
                           { (yyval.node) = new QSRelationalNode((yyvsp[-2].node), OpIn, (yyvsp[0].node)); }
#line 2941 "grammar.cpp"
    break;

  case 79: /* EqualityExpr: EqualityExpr EQEQ RelationalExpr  */
#line 321 "grammar.y"
                                       { (yyval.node) = new QSEqualNode((yyvsp[-2].node), OpEqEq, (yyvsp[0].node)); }
#line 2947 "grammar.cpp"
    break;

  case 80: /* EqualityExpr: EqualityExpr NE RelationalExpr  */
#line 322 "grammar.y"
                                       { (yyval.node) = new QSEqualNode((yyvsp[-2].node), OpNotEq, (yyvsp[0].node)); }
#line 2953 "grammar.cpp"
    break;

  case 81: /* EqualityExpr: EqualityExpr STREQ RelationalExpr  */
#line 323 "grammar.y"
                                       { (yyval.node) = new QSEqualNode((yyvsp[-2].node), OpStrEq, (yyvsp[0].node)); }
#line 2959 "grammar.cpp"
    break;

  case 82: /* EqualityExpr: EqualityExpr STRNEQ RelationalExpr  */
#line 324 "grammar.y"
                                       { (yyval.node) = new QSEqualNode((yyvsp[-2].node), OpStrNEq, (yyvsp[0].node));}
#line 2965 "grammar.cpp"
    break;

  case 84: /* BitwiseANDExpr: BitwiseANDExpr '&' EqualityExpr  */
#line 329 "grammar.y"
                                    { (yyval.node) = new QSBitOperNode((yyvsp[-2].node), OpBitAnd, (yyvsp[0].node)); }
#line 2971 "grammar.cpp"
    break;

  case 86: /* BitwiseXORExpr: BitwiseXORExpr '^' BitwiseANDExpr  */
#line 334 "grammar.y"
                                      { (yyval.node) = new QSBitOperNode((yyvsp[-2].node), OpBitXOr, (yyvsp[0].node)); }
#line 2977 "grammar.cpp"
    break;

  case 88: /* BitwiseORExpr: BitwiseORExpr '|' BitwiseXORExpr  */
#line 339 "grammar.y"
                                     { (yyval.node) = new QSBitOperNode((yyvsp[-2].node), OpBitOr, (yyvsp[0].node)); }
#line 2983 "grammar.cpp"
    break;

  case 90: /* LogicalANDExpr: LogicalANDExpr AND BitwiseORExpr  */
#line 345 "grammar.y"
                           { (yyval.node) = new QSBinaryLogicalNode((yyvsp[-2].node), OpAnd, (yyvsp[0].node)); }
#line 2989 "grammar.cpp"
    break;

  case 92: /* LogicalORExpr: LogicalORExpr OR LogicalANDExpr  */
#line 351 "grammar.y"
                           { (yyval.node) = new QSBinaryLogicalNode((yyvsp[-2].node), OpOr, (yyvsp[0].node)); }
#line 2995 "grammar.cpp"
    break;

  case 94: /* ConditionalExpr: LogicalORExpr '?' AssignmentExpr ':' AssignmentExpr  */
#line 357 "grammar.y"
                           { (yyval.node) = new QSConditionalNode((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3001 "grammar.cpp"
    break;

  case 96: /* AssignmentExpr: LeftHandSideExpr AssignmentOperator AssignmentExpr  */
#line 363 "grammar.y"
                           { (yyval.node) = new QSAssignNode((yyvsp[-2].node), (yyvsp[-1].op), (yyvsp[0].node));}
#line 3007 "grammar.cpp"
    break;

  case 97: /* AssignmentOperator: '='  */
#line 367 "grammar.y"
                                   { (yyval.op) = OpEqual; }
#line 3013 "grammar.cpp"
    break;

  case 98: /* AssignmentOperator: PLUSEQUAL  */
#line 368 "grammar.y"
                                   { (yyval.op) = OpPlusEq; }
#line 3019 "grammar.cpp"
    break;

  case 99: /* AssignmentOperator: MINUSEQUAL  */
#line 369 "grammar.y"
                                   { (yyval.op) = OpMinusEq; }
#line 3025 "grammar.cpp"
    break;

  case 100: /* AssignmentOperator: MULTEQUAL  */
#line 370 "grammar.y"
                                   { (yyval.op) = OpMultEq; }
#line 3031 "grammar.cpp"
    break;

  case 101: /* AssignmentOperator: DIVEQUAL  */
#line 371 "grammar.y"
                                   { (yyval.op) = OpDivEq; }
#line 3037 "grammar.cpp"
    break;

  case 102: /* AssignmentOperator: LSHIFTEQUAL  */
#line 372 "grammar.y"
                                   { (yyval.op) = OpLShift; }
#line 3043 "grammar.cpp"
    break;

  case 103: /* AssignmentOperator: RSHIFTEQUAL  */
#line 373 "grammar.y"
                                   { (yyval.op) = OpRShift; }
#line 3049 "grammar.cpp"
    break;

  case 104: /* AssignmentOperator: URSHIFTEQUAL  */
#line 374 "grammar.y"
                                   { (yyval.op) = OpURShift; }
#line 3055 "grammar.cpp"
    break;

  case 105: /* AssignmentOperator: ANDEQUAL  */
#line 375 "grammar.y"
                                   { (yyval.op) = OpAndEq; }
#line 3061 "grammar.cpp"
    break;

  case 106: /* AssignmentOperator: XOREQUAL  */
#line 376 "grammar.y"
                                   { (yyval.op) = OpXOrEq; }
#line 3067 "grammar.cpp"
    break;

  case 107: /* AssignmentOperator: OREQUAL  */
#line 377 "grammar.y"
                                   { (yyval.op) = OpOrEq; }
#line 3073 "grammar.cpp"
    break;

  case 108: /* AssignmentOperator: MODEQUAL  */
#line 378 "grammar.y"
                                   { (yyval.op) = OpModEq; }
#line 3079 "grammar.cpp"
    break;

  case 110: /* Expr: Expr ',' AssignmentExpr  */
#line 383 "grammar.y"
                                   { (yyval.node) = new QSCommaNode((yyvsp[-2].node), (yyvsp[0].node)); }
#line 3085 "grammar.cpp"
    break;

  case 113: /* Statement: ClassDefinition  */
#line 389 "grammar.y"
                                   { (yyval.stat) = (yyvsp[0].clss); }
#line 3091 "grammar.cpp"
    break;

  case 114: /* Statement: Attributes ClassDefinition  */
#line 390 "grammar.y"
                                   { (yyvsp[0].clss)->setAttributes( (yyvsp[-1].attrs) ); (yyval.stat) = (yyvsp[0].clss); }
#line 3097 "grammar.cpp"
    break;

  case 129: /* Block: '{' '}'  */
#line 408 "grammar.y"
                                   { (yyval.stat) = new QSBlockNode(0L); DBG((yyval.stat), (yylsp[0]), (yylsp[0])); }
#line 3103 "grammar.cpp"
    break;

  case 130: /* Block: '{' StatementList '}'  */
#line 409 "grammar.y"
                                   { (yyval.stat) = new QSBlockNode((yyvsp[-1].slist)); DBG((yyval.stat), (yylsp[0]), (yylsp[0])); }
#line 3109 "grammar.cpp"
    break;

  case 131: /* StatementList: Statement  */
#line 413 "grammar.y"
                                   { (yyval.slist) = new QSStatListNode((yyvsp[0].stat)); }
#line 3115 "grammar.cpp"
    break;

  case 132: /* StatementList: StatementList Statement  */
#line 414 "grammar.y"
                                   { (yyval.slist) = new QSStatListNode((yyvsp[-1].slist), (yyvsp[0].stat)); }
#line 3121 "grammar.cpp"
    break;

  case 133: /* EmptyStatement: ';'  */
#line 418 "grammar.y"
                                   { (yyval.stat) = new QSEmptyStatementNode(); }
#line 3127 "grammar.cpp"
    break;

  case 134: /* ExprStatement: Expr ';'  */
#line 422 "grammar.y"
                                   { (yyval.stat) = new QSExprStatementNode((yyvsp[-1].node));
                                     DBG((yyval.stat), (yylsp[-1]), (yylsp[0])); }
#line 3134 "grammar.cpp"
    break;

  case 135: /* ExprStatement: Expr error  */
#line 424 "grammar.y"
                                   { if (automatic()) {
                                       (yyval.stat) = new QSExprStatementNode((yyvsp[-1].node));
				       DBG((yyval.stat), (yylsp[-1]), (yylsp[-1]));
                                     } else
				       YYABORT; }
#line 3144 "grammar.cpp"
    break;

  case 136: /* IfStatement: IF '(' Expr ')' Statement  */
#line 432 "grammar.y"
                                   { (yyval.stat) = new QSIfNode((yyvsp[-2].node),(yyvsp[0].stat),0L);DBG((yyval.stat),(yylsp[-4]),(yylsp[-1])); }
#line 3150 "grammar.cpp"
    break;

  case 137: /* IfStatement: IF '(' Expr ')' Statement ELSE Statement  */
#line 434 "grammar.y"
                                   { (yyval.stat) = new QSIfNode((yyvsp[-4].node),(yyvsp[-2].stat),(yyvsp[0].stat));DBG((yyval.stat),(yylsp[-6]),(yylsp[-3])); }
#line 3156 "grammar.cpp"
    break;

  case 138: /* IterationStatement: DO Statement WHILE '(' Expr ')'  */
#line 438 "grammar.y"
                                    { (yyval.stat)=new QSDoWhileNode((yyvsp[-4].stat),(yyvsp[-1].node));DBG((yyval.stat),(yylsp[-5]),(yylsp[-3]));}
#line 3162 "grammar.cpp"
    break;

  case 139: /* IterationStatement: WHILE '(' Expr ')' Statement  */
#line 439 "grammar.y"
                                   { (yyval.stat) = new QSWhileNode((yyvsp[-2].node),(yyvsp[0].stat));DBG((yyval.stat),(yylsp[-4]),(yylsp[-1])); }
#line 3168 "grammar.cpp"
    break;

  case 140: /* IterationStatement: FOR '(' ExprOpt ';' ExprOpt ';' ExprOpt ')' Statement  */
#line 441 "grammar.y"
                                   { (yyval.stat) = new QSForNode((yyvsp[-6].node),(yyvsp[-4].node),(yyvsp[-2].node),(yyvsp[0].stat));
	                             DBG((yyval.stat),(yylsp[-8]),(yylsp[-1])); }
#line 3175 "grammar.cpp"
    break;

  case 141: /* IterationStatement: FOR '(' VAR VariableBindingList ';' ExprOpt ';' ExprOpt ')' Statement  */
#line 444 "grammar.y"
                                   { (yyval.stat) = new QSForNode((yyvsp[-6].blist),(yyvsp[-4].node),(yyvsp[-2].node),(yyvsp[0].stat));
	                             DBG((yyval.stat),(yylsp[-9]),(yylsp[-1])); }
#line 3182 "grammar.cpp"
    break;

  case 142: /* IterationStatement: FOR '(' LeftHandSideExpr QS_IN Expr ')' Statement  */
#line 447 "grammar.y"
                                   { (yyval.stat) = new QSForInNode((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].stat));
	                             DBG((yyval.stat),(yylsp[-6]),(yylsp[-1])); }
#line 3189 "grammar.cpp"
    break;

  case 143: /* IterationStatement: FOR '(' VAR VariableBinding QS_IN Expr ')' Statement  */
#line 450 "grammar.y"
                                   { (yyval.stat) = new QSForInNode((yyvsp[-4].vbin),(yyvsp[-2].node),(yyvsp[0].stat));
	                             DBG((yyval.stat),(yylsp[-7]),(yylsp[-1])); }
#line 3196 "grammar.cpp"
    break;

  case 144: /* ExprOpt: %empty  */
#line 455 "grammar.y"
                                   { (yyval.node) = 0L; }
#line 3202 "grammar.cpp"
    break;

  case 146: /* ContinueStatement: CONTINUE ';'  */
#line 460 "grammar.y"
                                   { (yyval.stat) = new QSContinueNode(); DBG((yyval.stat),(yylsp[-1]),(yylsp[0])); }
#line 3208 "grammar.cpp"
    break;

  case 147: /* ContinueStatement: CONTINUE error  */
#line 461 "grammar.y"
                                   { if (automatic()) {
                                       (yyval.stat) = new QSContinueNode(); DBG((yyval.stat),(yylsp[-1]),(yylsp[0]));
                                     } else
				       YYABORT; }
#line 3217 "grammar.cpp"
    break;

  case 148: /* ContinueStatement: CONTINUE IDENT ';'  */
#line 465 "grammar.y"
                                   { (yyval.stat) = new QSContinueNode((yyvsp[-1].ustr)); DBG((yyval.stat),(yylsp[-2]),(yylsp[0]));
                                     delete (yyvsp[-1].ustr); }
#line 3224 "grammar.cpp"
    break;

  case 149: /* ContinueStatement: CONTINUE IDENT error  */
#line 467 "grammar.y"
                                   { if (automatic()) {
                                       (yyval.stat) = new QSContinueNode((yyvsp[-1].ustr));DBG((yyval.stat),(yylsp[-2]),(yylsp[-1]));
				       delete (yyvsp[-1].ustr);
                                     } else
				       YYABORT; }
#line 3234 "grammar.cpp"
    break;

  case 150: /* BreakStatement: BREAK ';'  */
#line 475 "grammar.y"
                                   { (yyval.stat) = new QSBreakNode();DBG((yyval.stat),(yylsp[-1]),(yylsp[0])); }
#line 3240 "grammar.cpp"
    break;

  case 151: /* BreakStatement: BREAK error  */
#line 476 "grammar.y"
                                   { if (automatic()) {
                                       (yyval.stat) = new QSBreakNode(); DBG((yyval.stat),(yylsp[-1]),(yylsp[-1]));
                                     } else
				       YYABORT; }
#line 3249 "grammar.cpp"
    break;

  case 152: /* BreakStatement: BREAK IDENT ';'  */
#line 480 "grammar.y"
                                   { (yyval.stat) = new QSBreakNode((yyvsp[-1].ustr)); DBG((yyval.stat),(yylsp[-2]),(yylsp[0]));
                                     delete (yyvsp[-1].ustr); }
#line 3256 "grammar.cpp"
    break;

  case 153: /* BreakStatement: BREAK IDENT error  */
#line 482 "grammar.y"
                                   { if (automatic()) {
                                       (yyval.stat) = new QSBreakNode((yyvsp[-1].ustr)); DBG((yyval.stat),(yylsp[-2]),(yylsp[-1]));
				       delete (yyvsp[-1].ustr);
                                     } else
				       YYABORT;
                                   }
#line 3267 "grammar.cpp"
    break;

  case 154: /* ReturnStatement: RETURN ';'  */
#line 491 "grammar.y"
                                   { (yyval.stat) = new QSReturnNode(0L); DBG((yyval.stat),(yylsp[-1]),(yylsp[0])); }
#line 3273 "grammar.cpp"
    break;

  case 155: /* ReturnStatement: RETURN error  */
#line 492 "grammar.y"
                                   { if (automatic()) {
                                       (yyval.stat) = new QSReturnNode(0L); DBG((yyval.stat),(yylsp[-1]),(yylsp[-1]));
                                     } else
				       YYABORT; }
#line 3282 "grammar.cpp"
    break;

  case 156: /* ReturnStatement: RETURN Expr ';'  */
#line 496 "grammar.y"
                                   { (yyval.stat) = new QSReturnNode((yyvsp[-1].node)); DBG((yyval.stat),(yylsp[-2]),(yylsp[-1])); }
#line 3288 "grammar.cpp"
    break;

  case 157: /* ReturnStatement: RETURN Expr error  */
#line 497 "grammar.y"
                                   { if (automatic()) {
                                       (yyval.stat) = new QSReturnNode((yyvsp[-1].node));
                                       DBG((yyval.stat),(yylsp[-2]),(yylsp[-1]));
                                     } else {
				       YYABORT;
				     } 
                                   }
#line 3300 "grammar.cpp"
    break;

  case 158: /* WithStatement: WITH '(' Expr ')' Statement  */
#line 507 "grammar.y"
                                   { (yyval.stat) = new QSWithNode((yyvsp[-2].node),(yyvsp[0].stat));
                                     DBG((yyval.stat), (yylsp[-4]), (yylsp[-1])); }
#line 3307 "grammar.cpp"
    break;

  case 159: /* SwitchStatement: SWITCH '(' Expr ')' CaseBlock  */
#line 512 "grammar.y"
                                   { (yyval.stat) = new QSSwitchNode((yyvsp[-2].node), (yyvsp[0].cblk));
                                     DBG((yyval.stat), (yylsp[-4]), (yylsp[-1])); }
#line 3314 "grammar.cpp"
    break;

  case 160: /* CaseBlock: '{' CaseClausesOpt '}'  */
#line 517 "grammar.y"
                                   { (yyval.cblk) = new QSCaseBlockNode((yyvsp[-1].clist), 0L, 0L); }
#line 3320 "grammar.cpp"
    break;

  case 161: /* CaseBlock: '{' CaseClausesOpt DefaultClause CaseClausesOpt '}'  */
#line 519 "grammar.y"
                                   { (yyval.cblk) = new QSCaseBlockNode((yyvsp[-3].clist), (yyvsp[-2].ccl), (yyvsp[-1].clist)); }
#line 3326 "grammar.cpp"
    break;

  case 162: /* CaseClausesOpt: %empty  */
#line 523 "grammar.y"
                                   { (yyval.clist) = 0L; }
#line 3332 "grammar.cpp"
    break;

  case 164: /* CaseClauses: CaseClause  */
#line 528 "grammar.y"
                                   { (yyval.clist) = new QSClauseListNode((yyvsp[0].ccl)); }
#line 3338 "grammar.cpp"
    break;

  case 165: /* CaseClauses: CaseClauses CaseClause  */
#line 529 "grammar.y"
                                   { (yyval.clist) = (yyvsp[-1].clist)->append((yyvsp[0].ccl)); }
#line 3344 "grammar.cpp"
    break;

  case 166: /* CaseClause: CASE Expr ':'  */
#line 533 "grammar.y"
                                   { (yyval.ccl) = new QSCaseClauseNode((yyvsp[-1].node), 0L); }
#line 3350 "grammar.cpp"
    break;

  case 167: /* CaseClause: CASE Expr ':' StatementList  */
#line 534 "grammar.y"
                                   { (yyval.ccl) = new QSCaseClauseNode((yyvsp[-2].node), (yyvsp[0].slist)); }
#line 3356 "grammar.cpp"
    break;

  case 168: /* DefaultClause: DEFAULT ':'  */
#line 538 "grammar.y"
                                   { (yyval.ccl) = new QSCaseClauseNode(0L, 0L);; }
#line 3362 "grammar.cpp"
    break;

  case 169: /* DefaultClause: DEFAULT ':' StatementList  */
#line 539 "grammar.y"
                                   { (yyval.ccl) = new QSCaseClauseNode(0L, (yyvsp[0].slist)); }
#line 3368 "grammar.cpp"
    break;

  case 170: /* LabelledStatement: IDENT ':' Statement  */
#line 543 "grammar.y"
                                   { (yyvsp[0].stat)->pushLabel((yyvsp[-2].ustr));
                                     (yyval.stat) = new QSLabelNode((yyvsp[-2].ustr), (yyvsp[0].stat));
                                     delete (yyvsp[-2].ustr); }
#line 3376 "grammar.cpp"
    break;

  case 171: /* ThrowStatement: THROW Expr ';'  */
#line 549 "grammar.y"
                                   { (yyval.stat) = new QSThrowNode((yyvsp[-1].node)); }
#line 3382 "grammar.cpp"
    break;

  case 172: /* TryStatement: TRY Block Catch  */
#line 553 "grammar.y"
                                   { (yyval.stat) = new QSTryNode((yyvsp[-1].stat), (yyvsp[0].node)); }
#line 3388 "grammar.cpp"
    break;

  case 173: /* TryStatement: TRY Block Finally  */
#line 554 "grammar.y"
                                   { (yyval.stat) = new QSTryNode((yyvsp[-1].stat), 0L, (yyvsp[0].node)); }
#line 3394 "grammar.cpp"
    break;

  case 174: /* TryStatement: TRY Block Catch Finally  */
#line 555 "grammar.y"
                                   { (yyval.stat) = new QSTryNode((yyvsp[-2].stat), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 3400 "grammar.cpp"
    break;

  case 175: /* Catch: CATCH '(' IDENT ')' Block  */
#line 559 "grammar.y"
                                   { (yyval.node) = new QSCatchNode((yyvsp[-2].ustr), (yyvsp[0].stat)); delete (yyvsp[-2].ustr); }
#line 3406 "grammar.cpp"
    break;

  case 176: /* Finally: FINALLY Block  */
#line 563 "grammar.y"
                                   { (yyval.node) = new QSFinallyNode((yyvsp[0].stat)); }
#line 3412 "grammar.cpp"
    break;

  case 177: /* PackageDefinition: PACKAGE PackageName FunctionBody  */
#line 568 "grammar.y"
                                   { (yyval.stat) = new QSPackageNode((yyvsp[-1].ustr), (yyvsp[0].body));
                                     delete (yyvsp[-1].ustr); }
#line 3419 "grammar.cpp"
    break;

  case 178: /* ImportStatement: IMPORT PackageName ';'  */
#line 573 "grammar.y"
                                   { (yyval.stat) = new QSImportNode((yyvsp[-1].ustr)); delete (yyvsp[-1].ustr); }
#line 3425 "grammar.cpp"
    break;

  case 179: /* PackageName: IDENT  */
#line 577 "grammar.y"
                                   { (yyval.ustr) = (yyvsp[0].ustr); }
#line 3431 "grammar.cpp"
    break;

  case 180: /* PackageName: PackageName '.' IDENT  */
#line 578 "grammar.y"
                                   { *(yyval.ustr) += QString::fromLatin1(".") + *(yyvsp[0].ustr); delete (yyvsp[0].ustr); }
#line 3437 "grammar.cpp"
    break;

  case 181: /* FunctionDeclaration: FUNCTION IDENT '(' ')' ResultSignature FunctionBody  */
#line 583 "grammar.y"
                        { (yyval.func) = new QSFuncDeclNode((yyvsp[-4].ustr), 0L, (yyvsp[-1].type), (yyvsp[0].body)); delete (yyvsp[-4].ustr); }
#line 3443 "grammar.cpp"
    break;

  case 182: /* FunctionDeclaration: FUNCTION IDENT '(' FormalParameterList ')' ResultSignature FunctionBody  */
#line 585 "grammar.y"
                        { (yyval.func) = new QSFuncDeclNode((yyvsp[-5].ustr), (yyvsp[-3].param), (yyvsp[-1].type), (yyvsp[0].body)); delete (yyvsp[-5].ustr); }
#line 3449 "grammar.cpp"
    break;

  case 183: /* FunctionDeclaration: Attributes FUNCTION IDENT '(' ')' ResultSignature FunctionBody  */
#line 587 "grammar.y"
                        { (yyval.func) = new QSFuncDeclNode((yyvsp[-4].ustr), 0L, (yyvsp[-1].type), (yyvsp[0].body));
			  (yyval.func)->setAttributes( (yyvsp[-6].attrs) ); delete (yyvsp[-4].ustr); }
#line 3456 "grammar.cpp"
    break;

  case 184: /* FunctionDeclaration: Attributes FUNCTION IDENT '(' FormalParameterList ')' ResultSignature FunctionBody  */
#line 590 "grammar.y"
                        { (yyval.func) = new QSFuncDeclNode((yyvsp[-5].ustr), (yyvsp[-3].param), (yyvsp[-1].type), (yyvsp[0].body));
                          (yyval.func)->setAttributes( (yyvsp[-7].attrs) ); delete (yyvsp[-5].ustr); }
#line 3463 "grammar.cpp"
    break;

  case 185: /* ResultSignature: %empty  */
#line 595 "grammar.y"
                                   { (yyval.type) = 0L; }
#line 3469 "grammar.cpp"
    break;

  case 186: /* ResultSignature: ':' TypeExpression  */
#line 596 "grammar.y"
                                   { (yyval.type) = (yyvsp[0].type); }
#line 3475 "grammar.cpp"
    break;

  case 187: /* FunctionExpr: FUNCTION '(' ')' FunctionBody  */
#line 600 "grammar.y"
                                   { (yyval.node) = new QSFuncExprNode(0L, (yyvsp[0].body)); }
#line 3481 "grammar.cpp"
    break;

  case 188: /* FunctionExpr: FUNCTION '(' FormalParameterList ')' FunctionBody  */
#line 602 "grammar.y"
                                   { (yyval.node) = new QSFuncExprNode((yyvsp[-2].param), (yyvsp[0].body)); }
#line 3487 "grammar.cpp"
    break;

  case 189: /* FormalParameterList: IDENT  */
#line 607 "grammar.y"
                                   { (yyval.param) = new QSParameterNode((yyvsp[0].ustr), 0L);
                                     delete (yyvsp[0].ustr); }
#line 3494 "grammar.cpp"
    break;

  case 190: /* FormalParameterList: IDENT ':' TypeExpression  */
#line 609 "grammar.y"
                                   { (yyval.param) = new QSParameterNode((yyvsp[-2].ustr), (yyvsp[0].type));
                                     delete (yyvsp[-2].ustr); }
#line 3501 "grammar.cpp"
    break;

  case 191: /* FormalParameterList: FormalParameterList ',' IDENT  */
#line 611 "grammar.y"
                                   { (yyval.param) = (yyvsp[-2].param)->append((yyvsp[0].ustr), 0L); delete (yyvsp[0].ustr); }
#line 3507 "grammar.cpp"
    break;

  case 192: /* FormalParameterList: FormalParameterList ',' IDENT ':' TypeExpression  */
#line 613 "grammar.y"
                                   { (yyval.param) = (yyvsp[-4].param)->append((yyvsp[-2].ustr), (yyvsp[0].type)); delete (yyvsp[-2].ustr); }
#line 3513 "grammar.cpp"
    break;

  case 193: /* FunctionBody: '{' '}'  */
#line 617 "grammar.y"
                                   { (yyval.body) = new QSFunctionBodyNode(0L); }
#line 3519 "grammar.cpp"
    break;

  case 194: /* FunctionBody: '{' SourceElements '}'  */
#line 618 "grammar.y"
                                   { (yyval.body) = new QSFunctionBodyNode((yyvsp[-1].srcs)); }
#line 3525 "grammar.cpp"
    break;

  case 195: /* ClassDefinition: CLASS IDENT ';'  */
#line 622 "grammar.y"
                                   { (yyval.clss) = new QSClassDefNode((yyvsp[-1].ustr), 0L, 0L);
                                     delete (yyvsp[-1].ustr); }
#line 3532 "grammar.cpp"
    break;

  case 196: /* ClassDefinition: CLASS IDENT FunctionBody  */
#line 624 "grammar.y"
                                   { (yyval.clss) = new QSClassDefNode((yyvsp[-1].ustr), 0L, (yyvsp[0].body));
                                     delete (yyvsp[-1].ustr); }
#line 3539 "grammar.cpp"
    break;

  case 197: /* ClassDefinition: CLASS IDENT EXTENDS TypeExpression FunctionBody  */
#line 627 "grammar.y"
                                   { (yyval.clss) = new QSClassDefNode((yyvsp[-3].ustr), (yyvsp[-1].type), (yyvsp[0].body));
                                     delete (yyvsp[-3].ustr); }
#line 3546 "grammar.cpp"
    break;

  case 198: /* Program: %empty  */
#line 632 "grammar.y"
                                   { (yyval.prog) = new QSProgramNode(0L); }
#line 3552 "grammar.cpp"
    break;

  case 199: /* Program: SourceElements  */
#line 633 "grammar.y"
                                   { (yyval.prog) = new QSProgramNode((yyvsp[0].srcs)); }
#line 3558 "grammar.cpp"
    break;

  case 200: /* SourceElements: SourceElement  */
#line 637 "grammar.y"
                                   { (yyval.srcs) = new QSSourceElementsNode((yyvsp[0].src)); }
#line 3564 "grammar.cpp"
    break;

  case 201: /* SourceElements: SourceElements SourceElement  */
#line 638 "grammar.y"
                                   { (yyval.srcs) = new QSSourceElementsNode((yyvsp[-1].srcs), (yyvsp[0].src)); }
#line 3570 "grammar.cpp"
    break;

  case 202: /* SourceElement: Statement  */
#line 642 "grammar.y"
                                   { (yyval.src) = new QSSourceElementNode((yyvsp[0].stat)); }
#line 3576 "grammar.cpp"
    break;

  case 203: /* SourceElement: FunctionDeclaration  */
#line 643 "grammar.y"
                                   { (yyval.src) = new QSSourceElementNode((yyvsp[0].func)); }
#line 3582 "grammar.cpp"
    break;

  case 204: /* Attributes: Attribute  */
#line 647 "grammar.y"
                                   { (yyval.attrs) = new QSAttributeNode((yyvsp[0].attr)); }
#line 3588 "grammar.cpp"
    break;

  case 205: /* Attributes: Attributes Attribute  */
#line 648 "grammar.y"
                                   { (yyvsp[-1].attrs)->add((yyvsp[0].attr)); (yyval.attrs) = (yyvsp[-1].attrs); }
#line 3594 "grammar.cpp"
    break;

  case 206: /* Attribute: ABSTRACT  */
#line 652 "grammar.y"
                                   { (yyval.attr) = AttributeAbstract; }
#line 3600 "grammar.cpp"
    break;

  case 207: /* Attribute: FINAL  */
#line 653 "grammar.y"
                                   { (yyval.attr) = AttributeFinal; }
#line 3606 "grammar.cpp"
    break;

  case 208: /* Attribute: PRIVATE  */
#line 654 "grammar.y"
                                   { (yyval.attr) = AttributePrivate; }
#line 3612 "grammar.cpp"
    break;

  case 209: /* Attribute: PUBLIC  */
#line 655 "grammar.y"
                                   { (yyval.attr) = AttributePublic; }
#line 3618 "grammar.cpp"
    break;

  case 210: /* Attribute: STATIC  */
#line 656 "grammar.y"
                                   { (yyval.attr) = AttributeStatic; }
#line 3624 "grammar.cpp"
    break;

  case 211: /* Attribute: TRUETOKEN  */
#line 657 "grammar.y"
                                   { (yyval.attr) = AttributeTrue; }
#line 3630 "grammar.cpp"
    break;

  case 212: /* Attribute: FALSETOKEN  */
#line 658 "grammar.y"
                                   { (yyval.attr) = AttributeFalse; }
#line 3636 "grammar.cpp"
    break;

  case 213: /* Attribute: CONSTRUCTOR  */
#line 659 "grammar.y"
                                   { (yyval.attr) = AttributeConstructor; }
#line 3642 "grammar.cpp"
    break;

  case 214: /* VariableDefinition: VariableDefinitionKind VariableBindingList  */
#line 666 "grammar.y"
                             { (yyval.stat) = new QSVarDefNode((yyvsp[-1].ival), (yyvsp[0].blist)); DBG((yyval.stat), (yylsp[-1]), (yylsp[0])); }
#line 3648 "grammar.cpp"
    break;

  case 215: /* VariableDefinition: Attributes VariableDefinitionKind VariableBindingList  */
#line 668 "grammar.y"
                             { (yyval.stat) = new QSVarDefNode((yyvsp[-1].ival), (yyvsp[0].blist)); DBG((yyval.stat), (yylsp[-2]), (yylsp[0]));
                               ((QSVarDefNode*)(yyval.stat))->setAttributes( (yyvsp[-2].attrs) ); }
#line 3655 "grammar.cpp"
    break;

  case 216: /* VariableDefinitionKind: VAR  */
#line 673 "grammar.y"
                                                { (yyval.ival) = 0; }
#line 3661 "grammar.cpp"
    break;

  case 217: /* VariableDefinitionKind: QS_CONST  */
#line 674 "grammar.y"
                                                { (yyval.ival) = 1; }
#line 3667 "grammar.cpp"
    break;

  case 218: /* VariableBindingList: VariableBinding  */
#line 678 "grammar.y"
                                   { (yyval.blist) = new QSVarBindingListNode(0L, (yyvsp[0].vbin)); }
#line 3673 "grammar.cpp"
    break;

  case 219: /* VariableBindingList: VariableBindingList ',' VariableBinding  */
#line 680 "grammar.y"
                                   { (yyval.blist) = new QSVarBindingListNode((yyvsp[-2].blist), (yyvsp[0].vbin)); }
#line 3679 "grammar.cpp"
    break;

  case 220: /* VariableBinding: TypedVariable  */
#line 684 "grammar.y"
                                       { (yyval.vbin) = new QSVarBindingNode((yyvsp[0].tvar), 0L); }
#line 3685 "grammar.cpp"
    break;

  case 221: /* VariableBinding: TypedVariable '=' AssignmentExpr  */
#line 685 "grammar.y"
                                       { (yyval.vbin) = new QSVarBindingNode((yyvsp[-2].tvar), (yyvsp[0].node)); }
#line 3691 "grammar.cpp"
    break;

  case 222: /* TypedVariable: IDENT  */
#line 689 "grammar.y"
                                   { (yyval.tvar) = new QSTypedVarNode((yyvsp[0].ustr), 0L);
                                     delete (yyvsp[0].ustr); }
#line 3698 "grammar.cpp"
    break;

  case 223: /* TypedVariable: IDENT ':' TypeExpression  */
#line 691 "grammar.y"
                                   { (yyval.tvar) = new QSTypedVarNode((yyvsp[-2].ustr), (yyvsp[0].type));
                                     delete (yyvsp[-2].ustr); }
#line 3705 "grammar.cpp"
    break;

  case 224: /* TypeExpression: IDENT  */
#line 698 "grammar.y"
                                   { (yyval.type) = new QSTypeNode((yyvsp[0].ustr)); delete (yyvsp[0].ustr); }
#line 3711 "grammar.cpp"
    break;


#line 3715 "grammar.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

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
  yytoken = yychar == QSYYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= QSYYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == QSYYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = QSYYEMPTY;
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != QSYYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 701 "grammar.y"


int yyerror ( const char *errstr )  /* Called by yyparse on error */
{
  QString message = QString::fromLatin1( errstr );
  // keep the message format of the old parser generator, qs_format_error() relies on it
  if ( message.startsWith( QString::fromLatin1("syntax error") ) )
    message.replace( 0, 12, QString::fromLatin1("parse error") );
  QSLexer::lexer()->setErrorMessage( message );
  return 1;
}

/* may we automatically insert a semicolon ? */
bool automatic()
{
  if ( yychar == '}' || yychar == 0 )
    return true;
  else if ( QSLexer::lexer()->prevTerminator() )
    return true;

  return false;
}
