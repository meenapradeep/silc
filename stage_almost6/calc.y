%{
#include <stdio.h>
#include <stdlib.h>
#include "lex.yy.c"
#include "symbol.h"
#include "tree.h"

void yyerror(char *str){
	fprintf(stderr, "ERROR : %s\n", str);
}

int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		FILE *fp = fopen(argv[1], "r");
		if(fp)
			yyin = fp;
	}
	
	return yyparse();
}

%}

%union{struct Tnode* ptr;};

%token <ptr> NUM ID READ WRITE IF WHILE EQ GT LT ASG PLUS MUL TRUE FALSE AND OR NOT
%token THEN ENDIF DO ENDWHILE DECL ENDDECL BEG END INT BOOL
%type <ptr> expr
%type <ptr> Stmt
%type <ptr> StmtList 
%nonassoc EQ LT GT
%left PLUS
%left MUL
%%
Pgm 		: DECLARATION BEG StmtList END 	{Evaluate($3);printf("\n");exit(0);}
			;
DECLARATION	: DECL declist ENDDECL
			;
declist		: declist declar 
			| declar
			;
declar		: INT ID ';' 					{InstallSym($2->NAME, 1, INT_TYPE);}
			| INT ID '[' expr ']' ';' 		{InstallSym($2->NAME, Evaluate($4), INT_TYPE);}
			| BOOL ID ';' 					{InstallSym($2->NAME, 1, BOOL_TYPE);}
			| BOOL ID '[' expr ']' ';' 		{InstallSym($2->NAME, Evaluate($4), BOOL_TYPE);}
			  
			;
StmtList 	: Stmt							{$$ = $1;}
	 		| StmtList Stmt					{$$ = TreeCreate(DUMMY_TYPE, DUMMY_NODETYPE, 0 , NULL, $1, $2, NULL);}
	 		;
Stmt		: ID ASG expr';' 				{setNodeValues($2, $1, $3, NULL); $$ = $2;} 
			| ID '[' expr ']' ASG expr	';'	{setNodeValues($1, $3, NULL, NULL); setNodeValues($5, $1, $6, NULL); $$ = $5;}
		    | READ'('ID')'';'				{setNodeValues($1, $3, NULL, NULL); $$ = $1;}
		    | READ'('ID '[' expr ']' ')'';'	{setNodeValues($3, $5, NULL, NULL); setNodeValues($1, $3, NULL, NULL); $$ = $1;}
		    | WRITE'('expr')'';' 			{setNodeValues($1, $3, NULL, NULL); $$ = $1;}
		    | IF'('expr')' THEN StmtList ENDIF';'
		    								{setNodeValues($1, $3, $6, NULL); $$ = $1;}
		    | WHILE'('expr')' DO StmtList ENDWHILE';'	
		    								{setNodeValues($1, $3, $6, NULL); $$ = $1;}
		    ;
expr 		: expr PLUS expr 				{setNodeValues($2, $1, $3, NULL); $$=$2;}//$2->Ptr1 = $1; $2->Ptr2 = $3; $$ = $2;}
		    | expr MUL expr 				{setNodeValues($2, $1, $3, NULL); $$=$2;}
		    | expr LT expr			     	{setNodeValues($2, $1, $3, NULL); $$=$2;}
     		| expr GT expr     				{setNodeValues($2, $1, $3, NULL); $$=$2;}
     		| expr EQ expr     				{setNodeValues($2, $1, $3, NULL); $$=$2;}
     		| '('expr')' 	{$$ = $2;}
     		| NUM			{$$ = $1;}
		    | ID  			{$$ = $1;}
		    | ID'['expr']'	{setNodeValues( $1, $3, NULL,NULL); $$=$1;}
		    ;
%%

