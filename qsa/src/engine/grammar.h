/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_QSYY_GRAMMAR_H_INCLUDED
# define YY_QSYY_GRAMMAR_H_INCLUDED
/* Debug traces.  */
#ifndef QSYYDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define QSYYDEBUG 1
#  else
#   define QSYYDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define QSYYDEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined QSYYDEBUG */
#if QSYYDEBUG
extern int qsyydebug;
#endif

/* Token kinds.  */
#ifndef QSYYTOKENTYPE
# define QSYYTOKENTYPE
  enum qsyytokentype
  {
    QSYYEMPTY = -2,
    QSYYEOF = 0,                   /* "end of file"  */
    QSYYerror = 256,               /* error  */
    QSYYUNDEF = 257,               /* "invalid token"  */
    NULLTOKEN = 258,               /* NULLTOKEN  */
    TRUETOKEN = 259,               /* TRUETOKEN  */
    FALSETOKEN = 260,              /* FALSETOKEN  */
    STRING = 261,                  /* STRING  */
    NUMBER = 262,                  /* NUMBER  */
    BREAK = 263,                   /* BREAK  */
    CASE = 264,                    /* CASE  */
    DEFAULT = 265,                 /* DEFAULT  */
    FOR = 266,                     /* FOR  */
    NEW = 267,                     /* NEW  */
    VAR = 268,                     /* VAR  */
    CONTINUE = 269,                /* CONTINUE  */
    FUNCTION = 270,                /* FUNCTION  */
    RETURN = 271,                  /* RETURN  */
    QS_VOID = 272,                 /* QS_VOID  */
    QS_DELETE = 273,               /* QS_DELETE  */
    IF = 274,                      /* IF  */
    THIS = 275,                    /* THIS  */
    DO = 276,                      /* DO  */
    WHILE = 277,                   /* WHILE  */
    ELSE = 278,                    /* ELSE  */
    QS_IN = 279,                   /* QS_IN  */
    INSTANCEOF = 280,              /* INSTANCEOF  */
    TYPEOF = 281,                  /* TYPEOF  */
    IS = 282,                      /* IS  */
    SWITCH = 283,                  /* SWITCH  */
    WITH = 284,                    /* WITH  */
    RESERVED = 285,                /* RESERVED  */
    THROW = 286,                   /* THROW  */
    TRY = 287,                     /* TRY  */
    CATCH = 288,                   /* CATCH  */
    FINALLY = 289,                 /* FINALLY  */
    CLASS = 290,                   /* CLASS  */
    CONSTRUCTOR = 291,             /* CONSTRUCTOR  */
    EXTENDS = 292,                 /* EXTENDS  */
    ABSTRACT = 293,                /* ABSTRACT  */
    FINAL = 294,                   /* FINAL  */
    PRIVATE = 295,                 /* PRIVATE  */
    PUBLIC = 296,                  /* PUBLIC  */
    STATIC = 297,                  /* STATIC  */
    QS_CONST = 298,                /* QS_CONST  */
    PACKAGE = 299,                 /* PACKAGE  */
    IMPORT = 300,                  /* IMPORT  */
    EQEQ = 301,                    /* EQEQ  */
    NE = 302,                      /* NE  */
    STREQ = 303,                   /* STREQ  */
    STRNEQ = 304,                  /* STRNEQ  */
    LE = 305,                      /* LE  */
    GE = 306,                      /* GE  */
    OR = 307,                      /* OR  */
    AND = 308,                     /* AND  */
    PLUSPLUS = 309,                /* PLUSPLUS  */
    MINUSMINUS = 310,              /* MINUSMINUS  */
    LSHIFT = 311,                  /* LSHIFT  */
    RSHIFT = 312,                  /* RSHIFT  */
    URSHIFT = 313,                 /* URSHIFT  */
    PLUSEQUAL = 314,               /* PLUSEQUAL  */
    MINUSEQUAL = 315,              /* MINUSEQUAL  */
    MULTEQUAL = 316,               /* MULTEQUAL  */
    DIVEQUAL = 317,                /* DIVEQUAL  */
    LSHIFTEQUAL = 318,             /* LSHIFTEQUAL  */
    RSHIFTEQUAL = 319,             /* RSHIFTEQUAL  */
    URSHIFTEQUAL = 320,            /* URSHIFTEQUAL  */
    ANDEQUAL = 321,                /* ANDEQUAL  */
    MODEQUAL = 322,                /* MODEQUAL  */
    XOREQUAL = 323,                /* XOREQUAL  */
    OREQUAL = 324,                 /* OREQUAL  */
    IDENT = 325                    /* IDENT  */
  };
  typedef enum qsyytokentype qsyytoken_kind_t;
#endif

/* Value type.  */
#if ! defined QSYYSTYPE && ! defined QSYYSTYPE_IS_DECLARED
union QSYYSTYPE
{
#line 50 "grammar.y"

  int                 ival;
  double              dval;
  QString             *ustr;
  QSNode                *node;
  QSStatementNode       *stat;
  QSParameterNode       *param;
  QSFunctionBodyNode    *body;
  QSFuncDeclNode        *func;
  QSClassDefNode        *clss;
  QSProgramNode         *prog;
  QSAssignExprNode      *init;
  QSSourceElementNode   *src;
  QSSourceElementsNode  *srcs;
  QSStatListNode        *slist;
  QSArgumentsNode       *args;
  QSArgumentListNode    *alist;
  QSCaseBlockNode       *cblk;
  QSClauseListNode      *clist;
  QSCaseClauseNode      *ccl;
  QSElementNode         *elm;
  QSElisionNode         *eli;
  QSTypeNode            *type;
  QSTypedVarNode        *tvar;
  QSVarBindingNode      *vbin;
  QSVarBindingListNode  *blist;
  QSAttributeNode       *attrs;
  QSAttribute            attr;
  Operator            op;

#line 173 "grammar.h"

};
typedef union QSYYSTYPE QSYYSTYPE;
# define QSYYSTYPE_IS_TRIVIAL 1
# define QSYYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined QSYYLTYPE && ! defined QSYYLTYPE_IS_DECLARED
typedef struct QSYYLTYPE QSYYLTYPE;
struct QSYYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define QSYYLTYPE_IS_DECLARED 1
# define QSYYLTYPE_IS_TRIVIAL 1
#endif


extern QSYYSTYPE qsyylval;
extern QSYYLTYPE qsyylloc;

int qsyyparse (void);


#endif /* !YY_QSYY_GRAMMAR_H_INCLUDED  */
