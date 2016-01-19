%option noyywrap
%{
	#include <stdio.h>
	#include <stdlib.h>
	int countchar=0;
	int countline=0;
	int countword=0;
%}

char [a-zA-Z]
line [a-zA-Z.]
word [a-zA-Z]+[ .,;:]

%%

{char}	{countchar++;}
{line}	{countline++;}
{word}	{countword++;}

%%

int main()
{	yylex();
	printf("char:%d\nlines:%d\nwords:%d\n",countchar,countline,countword);
	return 1;
}


