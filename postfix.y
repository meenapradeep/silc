%{	
	void yyerror(char *s);
	#include "lex.yy.c"
	#include<stdio.h>
%}

%token NUMBER

%%
start: expr '\n'	{exit(1);}
     ;
expr: expr '+' expr	{printf("+ ");}
    | expr '*' expr	{printf("* ");}
    | expr '-' expr	{printf("- ");}
    | expr '/' expr	{printf("/ ");}
    | '(' expr ')'
    | NUMBER	{printf("NUM ");}
    ;


%%

int main(void){

	return yyparse();
//	pos++;
}

void yyerror(char *s){
	printf("Error\n");
	exit(1);
}
