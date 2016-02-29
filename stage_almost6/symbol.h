#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define INT_TYPE 1
#define BOOL_TYPE 2

struct Symbol{
	char *name;
	int TYPE;
	int SIZE;
	int *binding;
	int symindex;
	struct Symbol *next;
} *symbol = NULL;

int symindex = 0;

void InstallSym(char *name, int SIZE, int TYPE){
	struct Symbol *tmp;
	int *data;
	
	if(LookupSym(name) != NULL){
		printf("Variable already declared\n");
		exit(0);
	}
	tmp = (struct Symbol*) malloc(sizeof(struct Symbol));
	tmp -> name = name;
	tmp -> SIZE = SIZE;
	tmp -> TYPE = TYPE;
	data = (int*) malloc(sizeof(int) * SIZE);
	tmp -> binding = data;
	tmp -> symindex = symindex;
	symindex += SIZE;
	
	if(symbol == NULL){
		tmp -> next = NULL;
		symbol = tmp;
	}
	else{
		tmp -> next = symbol;
		symbol = tmp;
	}
	
}

struct Symbol *LookupSym(char *name){
	struct Symbol *tmp;
	tmp = symbol;
	while(tmp != NULL){
		if(strcmp(name, tmp -> name) == 0){
			return tmp;
		}
		tmp = tmp -> next;
	}
	
	return NULL;
}

int getSymbolIndex(char *name){
	struct Symbol *t;
	
	t = LookupSym(name);
	if(t == NULL){
		printf("\nUndefined variable %s\n", name);
		exit(0);
	}
	else{
		return t->symindex;
		}
	return -1;
}

int getType(char *name){
	struct Symbol *t;
	
	t = LookupSym(name);
	if(t == NULL){
		printf("\nUndefined variable %s\n", name);
		exit(0);
	}
	else{
		return t->TYPE;
		}
	return -1;
}

int getVal(char *name, int pos){
	struct Symbol *t;
	
	t = LookupSym(name);
	if(t == NULL){
		printf("\nUndefined variable %s\n", name);
		exit(0);
	}
	else{
		return *(t->binding + pos);
		}
	return -1;
}

void setVal(char *name, int pos, int val){
	struct Symbol *t;
	
	t = LookupSym(name);
	if(t == NULL){
		printf("\nUndefined variable %s\n", name);
		exit(0);
	}
	else
		*(t->binding+pos) = val;
		
}

int *GetBind(char *name ,int pos)
{	struct Symbol *t;
	
	t = LookupSym(name);
	if(t == NULL){
		printf("\nUndefined variable %s\n", name);
		exit(0);
	}
	else{
		return (t->binding + pos);
		}
	return ;
}
