%option noyywrap
%{
	#include <stdio.h>
	#include<stdlib.h>
	#define id 1
	#define er 2
	
%}

l [a-z]+
u [A-Z]+
n [0-9]+

%%

((l|u)+n) {return id;}
(.) {return er;}

%%

int main()
{	int x=yylex();
	printf("%d\n",x);
	if(x==id)
	{	printf("Acceptable\n");
	}
	else if(x==er)
	{
		printf("Unacceptable\n");
	}
	return 1;
}
