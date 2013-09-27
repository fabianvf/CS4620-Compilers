/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     GO = 258,
     TURN = 259,
     VAR = 260,
     JUMP = 261,
     FOR = 262,
     WHILE = 263,
     STEP = 264,
     TO = 265,
     DO = 266,
     IF = 267,
     THEN = 268,
     ELSE = 269,
     COPEN = 270,
     CCLOSE = 271,
     SIN = 272,
     COS = 273,
     SQRT = 274,
     FLOAT = 275,
     ID = 276,
     NUMBER = 277,
     SEMICOLON = 278,
     PLUS = 279,
     MINUS = 280,
     TIMES = 281,
     DIV = 282,
     OPEN = 283,
     CLOSE = 284,
     ASSIGN = 285,
     EQ = 286,
     NEQ = 287,
     LT = 288,
     GT = 289,
     GEQ = 290,
     LEQ = 291,
     OBRACE = 292,
     CBRACE = 293
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 8 "turtle_fsv5d.y"
 int i; node *n; double d;


/* Line 2068 of yacc.c  */
#line 92 "turtle_fsv5d.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


