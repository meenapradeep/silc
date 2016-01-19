%option noyywrap
%{
	#include <stdio.h>
%}


EVEN [0-9]*[24680]
ODD  [0-9]*[13579]

%%

{EVEN} {printf(" FOUND EVEN NUMBER: %s with length %d \n",yytext,yyleng);}
{ODD} {printf(" FOUND ODD NUMBER: %s with length %d \n",yytext,yyleng );}

%%

int main()
{	yylex();
	return 1;
}


