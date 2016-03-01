#ifndef TREE_H
#define TREE_H
#include<stdio.h>
#include<stdlib.h>

void InstallSym(char *, int, int);
struct Symbol *LookupSym(char*);
void setVal(char *, int, int);
int getVal(char *,int);

#define INT_TYPE	1
#define BOOL_TYPE	2
#define VOID_TYPE	3

#define DUMMY_TYPE 	0
#define DUMMY_NODETYPE	0

#define READ_NODETYPE	1
#define WRITE_NODETYPE	2
#define IF_NODETYPE	3
#define WHILE_NODETYPE	4
#define NUM_NODETYPE	5
#define ID_NODETYPE	6

#define PLUS_NODETYPE	7
#define MUL_NODETYPE	8
#define ASG_NODETYPE	9
#define LT_NODETYPE	10
#define GT_NODETYPE	11
#define EQ_NODETYPE	12
#define TRUE_NODETYPE 13
#define FALSE_NODETYPE 14
#define AND_NODETYPE 15
#define OR_NODETYPE 16
#define NOT_NODETYPE 17
#define SUB_NODETYPE 18
#define DIV_NODETYPE 19
#define MOD_NODETYPE 20

struct Tnode {
	int TYPE;
	int NODETYPE;
	int VALUE;
	char* NAME;
	
	struct Tnode *Ptr1, *Ptr2, *Ptr3;
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

void setNodeValues(struct Tnode* Node, struct Tnode* Ptr1, struct Tnode* Ptr2, struct Tnode* Ptr3){

	if(Node == NULL){
		printf("Error\n");
		exit(0);
	}

	switch(Node -> TYPE){
		case INT_TYPE:
	     switch(Node->NODETYPE){
					case NUM_NODETYPE:
						return;
					case PLUS_NODETYPE:
					case MUL_NODETYPE:
					case SUB_NODETYPE:
					case DIV_NODETYPE:
					case MOD_NODETYPE:
						if(Ptr1->TYPE == BOOL_TYPE || Ptr2->TYPE == BOOL_TYPE){
							printf("Both operators should be INT for arithmetic operations\n");
							exit(0);
						}
						if(Ptr1->TYPE == VOID_TYPE){
						  if(Ptr1->NODETYPE != ID_NODETYPE || getType(Ptr1->NAME) == BOOL_TYPE){
								printf("Both operators should be INT for arithmetic operations\n");
								exit(0);
							}
						}

						if(Ptr2->TYPE == VOID_TYPE){
						  if(Ptr2->NODETYPE != ID_NODETYPE || getType(Ptr2->NAME) == BOOL_TYPE){
								printf("Both operators should be INT for arithmetic operations\n");
								exit(0);
							}
						}
						break;

				 }
			  break;
		case VOID_TYPE:
		     switch(Node->NODETYPE){
					case READ_NODETYPE:
						if(Ptr1->TYPE != VOID_TYPE || Ptr1->NODETYPE != ID_NODETYPE || getType(Ptr1->NAME) == BOOL_TYPE){
							printf("Argument for 'read' should be INT variable\n");
							exit(0);
						}
						break;
					case WRITE_NODETYPE:
						if((Ptr1->TYPE == VOID_TYPE && Ptr1->NODETYPE != ID_NODETYPE) ||
								Ptr1->TYPE == BOOL_TYPE || (Ptr1->TYPE == VOID_TYPE && Ptr1->NODETYPE == ID_NODETYPE && getType(Ptr1->NAME) == BOOL_TYPE))
						{
							printf("Argument for 'write' should be integer expression\n");
							exit(0);
						}
						break;
					case IF_NODETYPE:
						if(Ptr1->TYPE != BOOL_TYPE && (Ptr1->TYPE != VOID_TYPE || Ptr1->NODETYPE != ID_NODETYPE || getType(Ptr1->NAME) != BOOL_TYPE)){
							printf("Condition for 'if' should be of BOOL type\n");
							exit(0);
						}
					  	break;
					case WHILE_NODETYPE:
						if(Ptr1->TYPE != BOOL_TYPE && (Ptr1->TYPE != VOID_TYPE || Ptr1->NODETYPE != ID_NODETYPE || getType(Ptr1->NAME) != BOOL_TYPE)){
							printf("Condition for 'while' should be of BOOL type\n");
							exit(0);
						}
					 	break;
					case ASG_NODETYPE:
						if(Ptr1->TYPE != VOID_TYPE || Ptr1->NODETYPE != ID_NODETYPE){
							printf("Left operand should be variable for assignment\n");
							exit(0);
						}
						if(getType(Ptr1->NAME) == BOOL_TYPE){
							if(Ptr2->TYPE == INT_TYPE || (Ptr2->TYPE == VOID_TYPE && getType(Ptr2->NAME) == INT_TYPE)){
								printf("Cannot assign INT type to BOOL variable\n");
								exit(0);
							}
						}
						else if(getType(Ptr1->NAME) == INT_TYPE){
							if(Ptr2->TYPE == BOOL_TYPE || (Ptr2->TYPE == VOID_TYPE && getType(Ptr2->NAME) == BOOL_TYPE)){
								printf("Cannot assign BOOL type to INT variable\n");
								exit(0);
							}
						}
						break;
					case ID_NODETYPE:
						if(Ptr1 != NULL){
						  if(Ptr1->TYPE != INT_TYPE && (Ptr1->TYPE != VOID_TYPE || Ptr1->NODETYPE != ID_NODETYPE || getType(Ptr1->NAME) != INT_TYPE )){
						    printf("Incompatible type for array index\n");
						  }
						}
						break;
			    }
			    break;
		case BOOL_TYPE:
			switch(Node->NODETYPE){
				case AND_NODETYPE:
				case OR_NODETYPE:
					if(Ptr1->TYPE == INT_TYPE || Ptr2->TYPE == INT_TYPE){
						printf("Both operators should be BOOL for logical operations\n");
						exit(0);
					}
					if(Ptr1->TYPE == VOID_TYPE){
						if(Ptr1->NODETYPE != ID_NODETYPE || getType(Ptr1->NAME) == INT_TYPE){
							printf("Both operators should be BOOL for logical operations\n");
							exit(0);
						}
					}

					if(Ptr2->TYPE == VOID_TYPE){
						if(Ptr2->NODETYPE != ID_NODETYPE || getType(Ptr2->NAME) == INT_TYPE){
							printf("Both operators should be BOOL for logical operations\n");
							exit(0);
						}
					}
					break;
				case NOT_NODETYPE:
					if(Ptr1->TYPE == INT_TYPE){
							printf("For 'not', operand should be of type BOOL\n");
							exit(0);
					}
					if(Ptr1->TYPE == VOID_TYPE){
						if(Ptr1->NODETYPE != ID_NODETYPE || getType(Ptr1->NAME) != BOOL_TYPE){
								printf("For 'not', operand should be of type BOOL\n");
								exit(0);
						}
					}
				}
	}
	Node->Ptr1 = Ptr1;
	Node->Ptr2 = Ptr2;
	Node->Ptr3 = Ptr3;
}

int Evaluate(struct Tnode* Node){
	int num;

	if(Node!=NULL){
		switch(Node->TYPE){
			case DUMMY_TYPE:
					Evaluate(Node->Ptr1);
					Evaluate(Node->Ptr2);
					break;
			case INT_TYPE:
			     switch(Node->NODETYPE){
					case NUM_NODETYPE: return Node->VALUE;
					case PLUS_NODETYPE:return(Evaluate(Node->Ptr1) + Evaluate(Node->Ptr2));
					case MUL_NODETYPE: return(Evaluate(Node->Ptr1) * Evaluate(Node->Ptr2));
					case SUB_NODETYPE: return(Evaluate(Node->Ptr1) - Evaluate(Node->Ptr2));
					case DIV_NODETYPE: return(Evaluate(Node->Ptr1) / Evaluate(Node->Ptr2));
					case MOD_NODETYPE: return(Evaluate(Node->Ptr1) % Evaluate(Node->Ptr2));
				 }
			     break;
			case BOOL_TYPE:
         switch(Node->NODETYPE){
					case LT_NODETYPE: return(Evaluate(Node->Ptr1) < Evaluate(Node->Ptr2));
					case GT_NODETYPE: return(Evaluate(Node->Ptr1) > Evaluate(Node->Ptr2));
					case EQ_NODETYPE: return(Evaluate(Node->Ptr1) == Evaluate(Node->Ptr2));
					case AND_NODETYPE: return(Evaluate(Node->Ptr1) && Evaluate(Node->Ptr2));
					case OR_NODETYPE: return(Evaluate(Node->Ptr1) || Evaluate(Node->Ptr2));
					case NOT_NODETYPE: return(!Evaluate(Node->Ptr1));
					case TRUE_NODETYPE: return 1;
					case FALSE_NODETYPE: return 0;
		     }
		     break;
			case VOID_TYPE:
			     switch(Node->NODETYPE){
					case READ_NODETYPE:
						//scanf("%d",&sym[*Node->Ptr1->NAME - 'a']);
						scanf("%d", &num);
						if(Node->Ptr1->Ptr1 == NULL)
							setVal(Node->Ptr1->NAME, 0, num);
						else
							setVal(Node->Ptr1->NAME, Evaluate(Node->Ptr1->Ptr1), num);
						break;
					case WRITE_NODETYPE:
						printf("%d\n",Evaluate(Node->Ptr1));
						break;
					case IF_NODETYPE:
						if(Node->Ptr3 == NULL){
							if(Evaluate(Node->Ptr1))
								Evaluate(Node->Ptr2);
						}
						else{
							if(Evaluate(Node->Ptr1))
								Evaluate(Node->Ptr2);
							else
								Evaluate(Node->Ptr3);
						}

					  	break;
					case WHILE_NODETYPE:
						while(Evaluate(Node->Ptr1))
						 	 Evaluate(Node->Ptr2);
					 	break;
					//case ASG_NODETYPE: sym[*Node->Ptr1->NAME-'a'] = Evaluate(Node->Ptr2); break;
					case ASG_NODETYPE:
						if(Node->Ptr1->Ptr1 == NULL)
							setVal(Node->Ptr1->NAME, 0, Evaluate(Node->Ptr2));
						else
							setVal(Node->Ptr1->NAME, Evaluate(Node->Ptr1->Ptr1), Evaluate(Node->Ptr2));

						break;
					case ID_NODETYPE:
						if(Node->Ptr1 == NULL)
							getVal(Node->NAME, 0);
						else
							getVal(Node->NAME, Evaluate(Node->Ptr1));
						break;

			    }
			    break;
		}
	}
}



#endif
