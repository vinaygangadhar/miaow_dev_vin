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
     TOK_SCALAR_REGISTER = 258,
     TOK_VECTOR_REGISTER = 259,
     TOK_SPECIAL_REGISTER = 260,
     TOK_DECIMAL = 261,
     TOK_HEX = 262,
     TOK_FLOAT = 263,
     TOK_ID = 264,
     TOK_COMMA = 265,
     TOK_COLON = 266,
     TOK_FORMAT = 267,
     TOK_OFFEN = 268,
     TOK_IDXEN = 269,
     TOK_OFFSET = 270,
     TOK_OBRA = 271,
     TOK_CBRA = 272,
     TOK_OPAR = 273,
     TOK_CPAR = 274,
     TOK_NEW_LINE = 275,
     TOK_AMP = 276,
     TOK_ABS = 277,
     TOK_NEG = 278
   };
#endif
/* Tokens.  */
#define TOK_SCALAR_REGISTER 258
#define TOK_VECTOR_REGISTER 259
#define TOK_SPECIAL_REGISTER 260
#define TOK_DECIMAL 261
#define TOK_HEX 262
#define TOK_FLOAT 263
#define TOK_ID 264
#define TOK_COMMA 265
#define TOK_COLON 266
#define TOK_FORMAT 267
#define TOK_OFFEN 268
#define TOK_IDXEN 269
#define TOK_OFFSET 270
#define TOK_OBRA 271
#define TOK_CBRA 272
#define TOK_OPAR 273
#define TOK_CPAR 274
#define TOK_NEW_LINE 275
#define TOK_AMP 276
#define TOK_ABS 277
#define TOK_NEG 278




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 53 "parser.y"

	int num;
	float num_float;
	struct si_id_t *id;
	struct si_dis_inst_t *inst;
	struct si_label_t *label;
	struct list_t *list;
	struct si_arg_t *arg;



/* Line 2068 of yacc.c  */
#line 108 "parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


