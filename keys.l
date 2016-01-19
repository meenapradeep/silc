
%option noyywrap
%{
	#include <stdio.h>
%}


num [0-9]+
lc  [a-z]+
uc  [A-Z]+
op  [=+-/%*]

%%

{num} {printf(" FOUND: %s \n",yytext);}
{lc} {printf(" FOUND: %s \n",yytext );}
{uc} {printf(" FOUND: %s \n",yytext);}
{op} {printf(" FOUND: %s \n",yytext);}

%%
int main()
{	yylex();
	return 1;
}



