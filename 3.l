%option noyywrap
%{
	#include <stdlib.h>
	#include <stdio.h>
%}
	
number [0-9]+
 
%%
 
{number} {printf("Found : %d\n",atoi(yytext));}
 
%%
 
int main()
{
	yylex();
	yylex();/* need to use ctrl+d twice to exit yylex() */
	return 1;
}
