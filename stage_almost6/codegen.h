#include "tree.h"

FILE *outfile;

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

void initFile(){
	outfile = fopen("machinecode","w");
	fprintf(outfile, "START\n");
}

void closeFile(){
	fprintf(outfile, "HALT\n");
	fclose(outfile);
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
						fprintf(outfile,"MOV R%d, %d\n",r,Node->VALUE);
						return r;
					case PLUS_NODETYPE:
						r1 = CodeGen(Node->Ptr1);
						r2 = CodeGen(Node->Ptr2);
						fprintf(outfile,"ADD R%d, R%d\n",r1,r2);
						FreeReg();
						return r1;
					case MUL_NODETYPE:
						r1 = CodeGen(Node->Ptr1);
						r2 = CodeGen(Node->Ptr2);
						fprintf(outfile,"MUL R%d, R%d\n",r1,r2);
						FreeReg();
						return r1;
					case SUB_NODETYPE:
						r1 = CodeGen(Node->Ptr1);
						r2 = CodeGen(Node->Ptr2);
						fprintf(outfile,"SUB R%d, R%d\n",r1,r2);
						FreeReg();
						return r1;
					case DIV_NODETYPE:
						r1 = CodeGen(Node->Ptr1);
						r2 = CodeGen(Node->Ptr2);
						fprintf(outfile,"DIV R%d, R%d\n",r1,r2);
						FreeReg();
						return r1;
					case MOD_NODETYPE:
						r1 = CodeGen(Node->Ptr1);
						r2 = CodeGen(Node->Ptr2);
						fprintf(outfile,"MOD R%d, R%d\n",r1,r2);
						FreeReg();
						return r1;
				 }
		     break;
			case BOOL_TYPE:
         switch(Node->NODETYPE){
					case LT_NODETYPE:
						r1 = CodeGen(Node->Ptr1);
						r2 = CodeGen(Node->Ptr2);
						fprintf(outfile,"LT R%d, R%d\n",r1,r2);
						FreeReg();
						return r1;

					case GT_NODETYPE:
						r1 = CodeGen(Node->Ptr1);
						r2 = CodeGen(Node->Ptr2);
						fprintf(outfile,"GT R%d, R%d\n",r1,r2);
						FreeReg();
						return r1;

					case EQ_NODETYPE:
						r1 = CodeGen(Node->Ptr1);
						r2 = CodeGen(Node->Ptr2);
						fprintf(outfile,"EQ R%d, R%d\n",r1,r2);
						FreeReg();
						return r1;

			 		case TRUE_NODETYPE:
			 			r = GetReg();
			 			fprintf(outfile,"MOV R%d, 1\n",r);
			 			return r;
			 		case FALSE_NODETYPE:
						r = GetReg();
			 			fprintf(outfile,"MOV R%d, 0\n",r);
			 			return r;
			 		case AND_NODETYPE:
			 			r1 = CodeGen(Node->Ptr1);
						r2 = CodeGen(Node->Ptr2);
						fprintf(outfile,"MUL R%d, R%d\n",r1,r2);
						FreeReg();

						return r1;
			 		case OR_NODETYPE:
			 			r1 = CodeGen(Node->Ptr1);
						r2 = CodeGen(Node->Ptr2);
						fprintf(outfile,"ADD R%d, R%d\n",r1,r2);
						FreeReg();
						r = GetReg();
						fprintf(outfile,"MOV R%d, 1\n",r);
						fprintf(outfile,"GE R%d, R%d\n",r1,r);
						FreeReg();
						return r1;

			 		case NOT_NODETYPE:
						r1 = CodeGen(Node->Ptr1);
						r2 = GetReg();
						fprintf(outfile,"MOV R%d, 1 \n",r2);
			 			fprintf(outfile,"ADD R%d, R%d\n",r1,r2);
						FreeReg();
			 			r = GetReg();
						fprintf(outfile,"MOV R%d, 2 \n",r);
			 			fprintf(outfile,"MOD R%d, R%d\n",r1,r);
						FreeReg();
			 			return r1;
			     }
			     break;
			case VOID_TYPE:
		     switch(Node->NODETYPE){
					case READ_NODETYPE:
						r = GetReg();
						fprintf(outfile,"IN R%d\n",r);
						loc = getSymbolIndex(Node->Ptr1->NAME);

						if(Node->Ptr1->Ptr1 == NULL)
						{
							fprintf(outfile,"MOV [%d], R%d\n",loc,r);
							FreeReg();
							return;
						}

						offset = CodeGen(Node->Ptr1->Ptr1);
						r1 = GetReg();
						fprintf(outfile,"MOV R%d, %d\n", r1, loc);
						fprintf(outfile,"ADD R%d, R%d\n", r1, offset);
						fprintf(outfile,"MOV [R%d], R%d\n", r1, r);
						FreeReg();
						FreeReg();
						FreeReg();
		    		return;

					case WRITE_NODETYPE:
						r = CodeGen(Node->Ptr1);
						fprintf(outfile,"OUT R%d\n",r);
						FreeReg();
						return;

					case IF_NODETYPE:
						l1 = GetLabel();
						l2 = GetLabel();
						r1 = CodeGen(Node->Ptr1);
						fprintf(outfile,"JZ R%d,L%d\n",r1,l1);
						FreeReg();
						CodeGen(Node->Ptr2);

						fprintf(outfile,"JMP L%d\n",l2);
						fprintf(outfile,"L%d:\n",l1);

						if(Node->Ptr3 != NULL)
							CodeGen(Node->Ptr3);
						fprintf(outfile,"L%d:\n",l2);
						return;
					case WHILE_NODETYPE:
						l1 = GetLabel();
						l2 = GetLabel();
						fprintf(outfile,"L%d:\n",l1);
						r1 = CodeGen(Node->Ptr1);
						fprintf(outfile,"JZ R%d,L%d\n",r1,l2); //condition is false, go to label
						FreeReg();
						CodeGen(Node->Ptr2);
						fprintf(outfile,"JMP L%d\n",l1);
						fprintf(outfile,"L%d:\n",l2);
					 	break;
					case ASG_NODETYPE:
						r = CodeGen(Node->Ptr2);
						loc = getSymbolIndex(Node->Ptr1->NAME);

						if(Node->Ptr1->Ptr1 == NULL)
						{
							fprintf(outfile,"MOV [%d], R%d\n",loc,r);
							FreeReg();
							return;
						}

						offset = CodeGen(Node->Ptr1->Ptr1);
						r1 = GetReg();
						fprintf(outfile,"MOV R%d, %d\n", r1, loc);
						fprintf(outfile,"ADD R%d, R%d\n", r1, offset);
						fprintf(outfile,"MOV [R%d], R%d\n", r1, r);
						FreeReg();
						FreeReg();
						FreeReg();
		    		return;

		    	case ID_NODETYPE:
		    		loc = getSymbolIndex(Node->NAME);

						if(Node -> Ptr1 == NULL){
							r = GetReg();
							fprintf(outfile,"MOV R%d,[%d]\n",r, loc);
							return r;
						}

						r1 = GetReg();
						offset = CodeGen(Node->Ptr1);

						r2 = GetReg();
						fprintf(outfile,"MOV R%d, %d\n", r2, loc);
						fprintf(outfile,"ADD R%d, R%d\n", r2, offset);
						fprintf(outfile,"MOV R%d, [R%d]\n", r1, r2);
						FreeReg();
						FreeReg();
						return r1;
			    }
			    break;
		}
	}
}
