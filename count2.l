%option noyywrap
%{
	#include <stdio.h>
	#include <stdlib.h>
	int countint=0;
	int countfloat=0;
%}

int [0-9]+
float [0-9]+[.][0-9]+

%%

{int}	{countint++;}
{float}	{countfloat++;}

%%

int main()
{	yylex();
	printf("ints:%d\nfloats:%d\n",countint,countfloat);
	return 1;
}


