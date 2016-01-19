%option noyywrap
%{
	#include <stdio.h>
%}

num [0-9]+
op	[+*/%^=-]
lc	[a-z]+
uc	[A-Z]+
an	[`~!@#$&()_,<.>/?;:'"{}\|]


%%

{num} {printf(" number");}
{op} {printf(" operator");}
{lc} {printf(" lowercase");}
{uc} {printf(" uppercase");}
{an} {printf(" alphanumeric ");}

%%

int main()
{
	yylex();
	return 1;
}

