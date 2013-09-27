
%{
#include <stdio.h>
#include "symtab.h"
%}

%union { int i; node *n; double d;}

%token GO TURN VAR JUMP
%token FOR WHILE STEP TO DO
%token COPEN CCLOSE
%token SIN COS SQRT
%token <d> FLOAT
%token <n> ID               
%token <i> NUMBER    
%token SEMICOLON PLUS MINUS TIMES DIV OPEN CLOSE ASSIGN
%token EQ NEQ LT GT GEQ LEQ OBRACE CBRACE //Don't know if these go here or not...


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

stmt: ID ASSIGN expr SEMICOLON {printf("/tlt%s exch store\n",$1->symbol);} ;
stmt: GO expr SEMICOLON {printf("0 rlineto\n");};
stmt: JUMP expr SEMICOLON {printf("0 rmoveto\n");};
stmt: TURN expr SEMICOLON {printf("rotate\n");};

stmt: FOR ID ASSIGN expr 
          STEP expr
	  TO expr
	  DO {printf("{ /tlt%s exch store\n",$2->symbol);} 
	     stmt {printf("} for\n");};
		 
		 
//stmt: WHILE OPEN ID LT NUMBER CLOSE OBRACE stmtlist CBRACE {printf("HERE");};

stmt: COPEN stmtlist CCLOSE;	 


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

//TODO
//comp: atomic EQ atomic{printf("eq\n");};
//comp: atomic NEQ atomic{printf("ne\n");};
//comp: ID LT NUMBER {printf("%s %d lt\n", $1->symbol, $3);};
//comp: atomic GT atomic{printf("gt\n");};
//comp: atomic LEQ atomic{printf("le\n");};
//comp: atomic GEQ atomic{printf("ge\n");};



atomic: OPEN expr CLOSE;
atomic: NUMBER {printf("%d ",$1);};
atomic: FLOAT {printf("%f ",$1);};
atomic: ID {printf("tlt%s ", $1->symbol);};


%%
int yyerror(char *msg)
{  fprintf(stderr,"Error: %s\n",msg);
//   fprintf("In line: %d\n On token: %s",yylineno, yytext)
   return 0;
}

int main(void)
{   yyparse();
    return 0;
}

