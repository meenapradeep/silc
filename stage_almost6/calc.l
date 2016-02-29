/*Stage 6*/
%{
#include<stdlib.h>
#include<stdio.h>
#include "tree.h"
#include "y.tab.h"
%}

%option noyywrap  

%%
"read" 			{yylval.ptr = TreeCreate(VOID_TYPE, READ_NODETYPE,  0 , NULL, NULL, NULL, NULL); return READ;	}
"write"			{yylval.ptr = TreeCreate(VOID_TYPE, WRITE_NODETYPE, 0 , NULL, NULL, NULL, NULL); return WRITE;	}
"if" 			{yylval.ptr = TreeCreate(VOID_TYPE, IF_NODETYPE,    0 , NULL, NULL, NULL, NULL); return IF;		}
"then"			return THEN;
"endif" 		return ENDIF;
"while" 		{yylval.ptr = TreeCreate(VOID_TYPE, WHILE_NODETYPE, 0 , NULL, NULL, NULL, NULL); return WHILE;	}
"do" 			return DO;
"endwhile" 		return ENDWHILE;
"decl"			return DECL;
"enddecl"		return ENDDECL;
"begin"			return BEG;
"end"			return END;
"int"			return INT;
"bool"			return BOOL;
"true"			{yylval.ptr = TreeCreate(BOOL_TYPE, TRUE_NODETYPE, 1 , NULL, NULL, NULL, NULL); return TRUE;}
"false"			{yylval.ptr = TreeCreate(BOOL_TYPE, FALSE_NODETYPE, 0 , NULL, NULL, NULL, NULL); return FALSE;}
"=="			{yylval.ptr = TreeCreate(BOOL_TYPE, EQ_NODETYPE, 0 , NULL, NULL, NULL, NULL); return EQ;}
"<"				{yylval.ptr = TreeCreate(BOOL_TYPE, LT_NODETYPE, 0 , NULL, NULL, NULL, NULL); return LT;}
">"				{yylval.ptr = TreeCreate(BOOL_TYPE, GT_NODETYPE, 0 , NULL, NULL, NULL, NULL); return GT;}
[+*=]			{
					switch(*yytext)
					{
					    case '+': yylval.ptr = TreeCreate(INT_TYPE, PLUS_NODETYPE, 0 , NULL, NULL, NULL, NULL); return PLUS;
					    case '*': yylval.ptr = TreeCreate(INT_TYPE, MUL_NODETYPE,  0 , NULL, NULL, NULL, NULL); return MUL; 
            		    case '=': yylval.ptr = TreeCreate(VOID_TYPE, ASG_NODETYPE, 0 , NULL, NULL, NULL, NULL); return ASG; 			
					}
				}
"and"			{
					yylval.ptr = TreeCreate(BOOL_TYPE, AND_NODETYPE, 0 , NULL, NULL, NULL, NULL); return AND;
				}
"or"			{
					yylval.ptr = TreeCreate(BOOL_TYPE, OR_NODETYPE, 0 , NULL, NULL, NULL, NULL); return OR;
				}
"not"			{
					yylval.ptr = TreeCreate(BOOL_TYPE, NOT_NODETYPE, 0 , NULL, NULL, NULL, NULL); return NOT;
				}
 	
[a-zA-Z][a-zA-Z0-9]*	{	char *id = (char*) malloc(sizeof(yytext));
							strcpy(id, yytext);
							yylval.ptr = TreeCreate(VOID_TYPE, ID_NODETYPE, 0, id, NULL, NULL, NULL);
							return ID;
						}
"[" | 
"]" |
[;(),]			return *yytext;
[0-9]+	 		{yylval.ptr = TreeCreate(INT_TYPE, NUM_NODETYPE, atoi(yytext),NULL, NULL, NULL, NULL); return NUM;}
[ \t\n]	 		{}
. 			{}
%%

