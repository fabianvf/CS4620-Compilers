

%{
#include <stdio.h>
#include "symtab.h"
%}

%union { int i; node *n; double d;}

%token GO TURN VAR JUMP
%token FOR WHILE STEP TO DO 
%token IF THEN ELSE 
%token COPEN CCLOSE
%token SIN COS SQRT
%token <d> FLOAT
%token <n> ID               
%token <i> NUMBER    
%token SEMICOLON PLUS MINUS TIMES DIV OPEN CLOSE ASSIGN
%token EQ NEQ LT GT GEQ LEQ OBRACE CBRACE 

%type <n> decl
%type <n> decllist

%%
program: head decllist stmtlist tail;

head: { printf("%%!PS Adobe\n"
               "\n"
	       "newpath 0 0 moveto\n"
	       );
      };

tail: { printf("stroke\n"); };

decllist: ;
decllist: decllist decl;


decl: VAR ID SEMICOLON { printf("/tlt%s 0 def\n",$2->symbol);} ;


stmtlist: ;
stmtlist: stmtlist stmt ;

//nestmtlist: stmtlist stmt;

stmt: ID ASSIGN expr SEMICOLON {printf("/tlt%s exch store\n",$1->symbol);} ;
stmt: GO expr SEMICOLON {printf("0 rlineto\n");};
stmt: JUMP expr SEMICOLON {printf("0 rmoveto\n");};
stmt: TURN expr SEMICOLON {printf("rotate\n");};

stmt: FOR ID ASSIGN expr 
          STEP expr
	  TO expr
	  DO {printf("{ /tlt%s exch store\n",$2->symbol);} 
	     stmt {printf("} for\n");};
		 
		 
stmt: WHILE OPEN {printf("{ ");} comp CLOSE {printf("\n{} {exit} ifelse\n");} block {printf("} loop\n");};

stmt: COPEN stmtlist CCLOSE;	 

stmt: IF OPEN comp CLOSE THEN ifblock ELSE {printf("} { ");} block  {printf("} ifelse\n");};
stmt: IF OPEN comp CLOSE THEN ifblock {printf("} if\n");};

block: stmt;
block: OBRACE stmtlist CBRACE;

ifblock: {printf("\n{ ");} OBRACE stmtlist CBRACE;
ifblock: {printf("\n{ ");} stmt;

expr: expr PLUS term { printf("add ");};
expr: expr MINUS term { printf("sub ");};
expr: term;

term: term TIMES factor { printf("mul ");};
term: term DIV factor { printf("div ");};
term: factor;

factor: MINUS atomic { printf("neg ");};
factor: PLUS atomic;
factor: SIN factor { printf("sin ");};
factor: COS factor { printf("cos ");};
factor: SQRT factor { printf("sqrt ");};
factor: atomic;


comp: atomic EQ atomic{printf("eq ");};
comp: atomic NEQ atomic{printf("ne ");};
comp: atomic LT atomic {printf("lt ");};
comp: atomic GT atomic{printf("gt ");};
comp: atomic LEQ atomic{printf("le ");};
comp: atomic GEQ atomic{printf("ge ");};



atomic: OPEN expr CLOSE;
atomic: NUMBER {printf("%d ",$1);};
atomic: FLOAT {printf("%f ",$1);};
atomic: ID {printf("tlt%s ", $1->symbol);};


%%
int yyerror(char *msg)
{  fprintf(stderr,"Error: %s\n",msg);
   return 0;
}

int main(void)
{   yyparse();
    return 0;
}

