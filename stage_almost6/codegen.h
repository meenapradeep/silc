#include "tree.h"

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

int CodeGen(struct Tnode* Node){
	int l1,l2,r1,r2,r;
	int loc, offset;

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
						printf("MOV R%d, %d\n",r,Node->VALUE);
						return r;
					case PLUS_NODETYPE:
						r1 = CodeGen(Node->Ptr1);
						r2 = CodeGen(Node->Ptr2);
						printf("ADD R%d, R%d\n",r1,r2);
						FreeReg();
						return r1;
					case MUL_NODETYPE:
						r1 = CodeGen(Node->Ptr1);
						r2 = CodeGen(Node->Ptr2);
						printf("MUL R%d, R%d\n",r1,r2);
						FreeReg();
						return r1;
					case SUB_NODETYPE:
						r1 = CodeGen(Node->Ptr1);
						r2 = CodeGen(Node->Ptr2);
						printf("SUB R%d, R%d\n",r1,r2);
						FreeReg();
						return r1;
					case DIV_NODETYPE:
						r1 = CodeGen(Node->Ptr1);
						r2 = CodeGen(Node->Ptr2);
						printf("DIV R%d, R%d\n",r1,r2);
						FreeReg();
						return r1;
					case MOD_NODETYPE:
						r1 = CodeGen(Node->Ptr1);
						r2 = CodeGen(Node->Ptr2);
						printf("MOD R%d, R%d\n",r1,r2);
						FreeReg();
						return r1;
				 }
		     break;
			case BOOL_TYPE:
         switch(Node->NODETYPE){
					case LT_NODETYPE:
						r1 = CodeGen(Node->Ptr1);
						r2 = CodeGen(Node->Ptr2);
						printf("LT R%d, R%d\n",r1,r2);
						FreeReg();
						return r1;

					case GT_NODETYPE:
						r1 = CodeGen(Node->Ptr1);
						r2 = CodeGen(Node->Ptr2);
						printf("GT R%d, R%d\n",r1,r2);
						FreeReg();
						return r1;

					case EQ_NODETYPE:
						r1 = CodeGen(Node->Ptr1);
						r2 = CodeGen(Node->Ptr2);
						printf("EQ R%d, R%d\n",r1,r2);
						FreeReg();
						return r1;

			 		case TRUE_NODETYPE:
			 			r = GetReg();
			 			printf("MOV R%d, 1\n",r);
			 			return r;
			 		case FALSE_NODETYPE:
						r = GetReg();
			 			printf("MOV R%d, 0\n",r);
			 			return r;
			 		case AND_NODETYPE:
			 			r1 = CodeGen(Node->Ptr1);
						r2 = CodeGen(Node->Ptr2);
						printf("MUL R%d, R%d\n",r1,r2);
						FreeReg();

						return r1;
			 		case OR_NODETYPE:
			 			r1 = CodeGen(Node->Ptr1);
						r2 = CodeGen(Node->Ptr2);
						printf("ADD R%d, R%d\n",r1,r2);
						FreeReg();
						r = GetReg();
						printf("MOV R%d, 1\n",r);
						printf("GE R%d, R%d\n",r1,r);
						FreeReg();
						return r1;

			 		case NOT_NODETYPE:
						r1 = CodeGen(Node->Ptr1);
						r2 = GetReg();
						printf("MOV R%d, 1 \n",r2);
			 			printf("ADD R%d, R%d\n",r1,r2);
						FreeReg();
			 			r = GetReg();
						printf("MOV R%d, 2 \n",r);
			 			printf("MOD R%d, R%d\n",r1,r);
						FreeReg();
			 			return r1;
			     }
			     break;
			case VOID_TYPE:
		     switch(Node->NODETYPE){
					case READ_NODETYPE:
						r = GetReg();
						printf("IN R%d\n",r);
						loc = getSymbolIndex(Node->Ptr1->NAME);

						if(Node->Ptr1->Ptr1 == NULL)
						{
							printf("MOV [%d], R%d\n",loc,r);
							FreeReg();
							return;
						}

						offset = CodeGen(Node->Ptr1->Ptr1);
						r1 = GetReg();
						printf("MOV R%d, %d\n", r1, loc);
						printf("ADD R%d, R%d\n", r1, offset);
						printf("MOV [R%d], R%d\n", r1, r);
						FreeReg();
						FreeReg();
						FreeReg();
		    		return;

					case WRITE_NODETYPE:
						r = CodeGen(Node->Ptr1);
						printf("OUT R%d\n",r);
						FreeReg();
						return;

					case IF_NODETYPE:
						l1 = GetLabel();
						l2 = GetLabel();
						r1 = CodeGen(Node->Ptr1);
						printf("JZ R%d,L%d\n",r1,l1);
						FreeReg();
						CodeGen(Node->Ptr2);

						printf("JMP L%d\n",l2);
						printf("L%d:\n",l1);

						if(Node->Ptr3 != NULL)
							CodeGen(Node->Ptr3);
						printf("L%d:\n",l2);
						return;
					case WHILE_NODETYPE:
						l1 = GetLabel();
						l2 = GetLabel();
						printf("L%d:\n",l1);
						r1 = CodeGen(Node->Ptr1);
						printf("JZ R%d,L%d\n",r1,l2); //condition is false, go to label
						FreeReg();
						CodeGen(Node->Ptr2);
						printf("JMP L%d\n",l1);
						printf("L%d:\n",l2);
					 	break;
					case ASG_NODETYPE:
						r = CodeGen(Node->Ptr2);
						loc = getSymbolIndex(Node->Ptr1->NAME);

						if(Node->Ptr1->Ptr1 == NULL)
						{
							printf("MOV [%d], R%d\n",loc,r);
							FreeReg();
							return;
						}

						offset = CodeGen(Node->Ptr1->Ptr1);
						r1 = GetReg();
						printf("MOV R%d, %d\n", r1, loc);
						printf("ADD R%d, R%d\n", r1, offset);
						printf("MOV [R%d], R%d\n", r1, r);
						FreeReg();
						FreeReg();
						FreeReg();
		    		return;

		    	case ID_NODETYPE:
		    		loc = getSymbolIndex(Node->NAME);

						if(Node -> Ptr1 == NULL){
							r = GetReg();
							printf("MOV R%d,[%d]\n",r, loc);
							return r;
						}

						r1 = GetReg();
						offset = CodeGen(Node->Ptr1);

						r2 = GetReg();
						printf("MOV R%d, %d\n", r2, loc);
						printf("ADD R%d, R%d\n", r2, offset);
						printf("MOV R%d, [R%d]\n", r1, r2);
						FreeReg();
						FreeReg();
						return r1;
			    }
			    break;
		}
	}
}
