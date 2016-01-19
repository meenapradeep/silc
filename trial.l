%option noyywrap
%{ 
	#include <stdio.h>
%}

number [0-9]+
op [+*-/^=%]

%%

{number}	{printf(" number");}
{op}	{printf(" operator");}

%%

int main()
{	yylex();
	return 1;
}


