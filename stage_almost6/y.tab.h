/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    NUM = 258,
    ID = 259,
    READ = 260,
    WRITE = 261,
    IF = 262,
    WHILE = 263,
    EQ = 264,
    GT = 265,
    LT = 266,
    ASG = 267,
    PLUS = 268,
    MUL = 269,
    SUB = 270,
    DIV = 271,
    MOD = 272,
    TRUE = 273,
    FALSE = 274,
    AND = 275,
    OR = 276,
    NOT = 277,
    THEN = 278,
    ELSE = 279,
    ENDIF = 280,
    DO = 281,
    ENDWHILE = 282,
    DECL = 283,
    ENDDECL = 284,
    BEG = 285,
    END = 286,
    INT = 287,
    BOOL = 288
  };
#endif
/* Tokens.  */
#define NUM 258
#define ID 259
#define READ 260
#define WRITE 261
#define IF 262
#define WHILE 263
#define EQ 264
#define GT 265
#define LT 266
#define ASG 267
#define PLUS 268
#define MUL 269
#define SUB 270
#define DIV 271
#define MOD 272
#define TRUE 273
#define FALSE 274
#define AND 275
#define OR 276
#define NOT 277
#define THEN 278
#define ELSE 279
#define ENDIF 280
#define DO 281
#define ENDWHILE 282
#define DECL 283
#define ENDDECL 284
#define BEG 285
#define END 286
#define INT 287
#define BOOL 288

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 29 "calc.y" /* yacc.c:1909  */
struct Tnode* ptr;

#line 123 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
