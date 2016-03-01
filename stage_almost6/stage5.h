#ifndef TREE_H
#define TREE_H
#include<stdio.h>
#include<stdlib.h>

//#include "symbol.h"
int sym[26];
int Reg=-1;
int Label=0;
int GetReg()
{	Reg++;
	return Reg;	
}

void FreeReg()
{	Reg--;
}

int GetLabel()
{	Label++;
	return Label;
}
#define INT_TYPE		1
#define BOOL_TYPE		2
#define VOID_TYPE		3

#define DUMMY_TYPE 		0
#define DUMMY_NODETYPE	0

#define READ_NODETYPE	1
#define WRITE_NODETYPE	2
#define IF_NODETYPE		3
#define WHILE_NODETYPE	4
#define NUM_NODETYPE	5
#define ID_NODETYPE		6

#define PLUS_NODETYPE	7
#define MUL_NODETYPE	8
#define ASG_NODETYPE	9
#define LT_NODETYPE		10
#define GT_NODETYPE		11
#define EQ_NODETYPE		12


#define TRUE_NODETYPE   13
#define FALSE_NODETYPE   14

struct Tnode {
int TYPE; // Integer, Boolean or Void (for statements)
int NODETYPE;/* Must point to the type expression tree for user defined types */
		/* this field should carry following information:
		* a) operator : (+,*,/ etc.) for expressions
		* b) statement Type : (WHILE, READ etc.) for statements */
int VALUE; // for constants
char* NAME; // For Identifiers/Functions

//struct Tnode *ArgList; // List of arguments for functions
struct Tnode *Ptr1, *Ptr2, *Ptr3; /* Maximum of three subtrees (3 required for IF THEN ELSE */
};

struct Tnode* TreeCreate(int TYPE, int NODETYPE, int VALUE, char* NAME, struct Tnode* Ptr1, struct Tnode* Ptr2, struct Tnode* Ptr3){

	struct Tnode *ptr = malloc(sizeof(struct Tnode));
	ptr->TYPE = TYPE;
	ptr->NODETYPE = NODETYPE;
	ptr->VALUE = VALUE;
	ptr->NAME = NAME;
	ptr->Ptr1 = Ptr1;
	ptr->Ptr2 = Ptr2;
	ptr->Ptr3 = Ptr3;
	return ptr;
}

int CodeGen(struct Tnode* Node){
	int l1,l2,r1,r2,r;
	
	if(Node!=NULL){	
		switch(Node->TYPE){
			case DUMMY_TYPE:
					CodeGen(Node->Ptr1);
					CodeGen(Node->Ptr2);
					break;
			case INT_TYPE:
			     switch(Node->NODETYPE){				
					case NUM_NODETYPE:  
						r = GetReg();
						printf("MOV R%d,%d\n",r,Node->VALUE);
						return r;
						
					case ID_NODETYPE:
						r = GetReg();
						printf("MOV R%d,[%d]\n",r,*Node->NAME-'a');
						return r;
						
					case PLUS_NODETYPE: 
						r1 = CodeGen(Node->Ptr1);
						r2 = CodeGen(Node->Ptr2);
						printf("ADD R%d,R%d\n",r1,r2);
						FreeReg();
						return r1;
					case MUL_NODETYPE:  
						r1 = CodeGen(Node->Ptr1);
						r2 = CodeGen(Node->Ptr2);
						printf("MUL R%d,R%d\n",r1,r2);
						FreeReg();
						return r1;
					
				 }
			     break;
			case BOOL_TYPE:
	             switch(Node->NODETYPE){
					case LT_NODETYPE: 
						r1 = CodeGen(Node->Ptr1);
						r2 = CodeGen(Node->Ptr2);
						printf("LT R%d,R%d\n",r1,r2);
						FreeReg();
						return r1;

					case GT_NODETYPE: 
						r1 = CodeGen(Node->Ptr1);
						r2 = CodeGen(Node->Ptr2);
						printf("GT R%d,R%d\n",r1,r2);
						FreeReg();
						return r1;
					
					case EQ_NODETYPE: 
						r1 = CodeGen(Node->Ptr1);
						r2 = CodeGen(Node->Ptr2);
						printf("EQ R%d,R%d\n",r1,r2);
						FreeReg();
						return r1;

			 		case TRUE_NODETYPE:
			 			r = GetReg();
			 			printf("MOV R%d,1\n",r);
			 			return r;
			 		case FALSE_NODETYPE:
						r = GetReg();
			 			printf("MOV R%d,0\n",r);
			 			return r;
			 		
			     }
			     break;
			case VOID_TYPE:
			     switch(Node->NODETYPE){
					case READ_NODETYPE:
						scanf(" %d",&sym[*Node->Ptr1->NAME - 'a']);
						r = GetReg();
						printf("IN R%d\n",r);
						printf("MOV [%d],R%d\n",*Node->Ptr1->NAME - 'a',r);
						FreeReg();
						return r;

						
					case WRITE_NODETYPE:
						//printf(" %d\n",CodeGen(Node->Ptr1));
						r = CodeGen(Node->Ptr1);
						printf("OUT R%d\n",r);
						FreeReg();
						return r;
						
					case IF_NODETYPE:
						l1 = GetLabel();
					    r1 = CodeGen(Node->Ptr1);					
						printf("JZ R%d,L%d\n",r1,l1); //if false go to label 
						FreeReg();
						r2 = CodeGen(Node->Ptr2);	//evaluates true condition
						printf("JMP L%d\n",l1);
						printf("L%d:\n",l1);
					  	break;				
					case WHILE_NODETYPE:
						l1 = GetLabel();
						l2 = GetLabel();
						printf("L%d:\n",l1);
						r1 = CodeGen(Node->Ptr1);
						printf("JZ R%d,L%d\n",r1,l2); //condition is false, go to label 
						FreeReg();
						r2 = CodeGen(Node->Ptr2);
						printf("JMP L%d\n",l1);
						printf("L%d:\n",l2);
					 	break;
					case ASG_NODETYPE: 
						r = CodeGen(Node->Ptr2);
						printf("MOV [%d],R%d\n",*Node->Ptr1->NAME - 'a',r);
						FreeReg();
						return r;

//						sym[*Node->Ptr1->NAME-'a'] = CodeGen(Node->Ptr2); break;
			    }
			    break;
		}
	}
}
#endif
