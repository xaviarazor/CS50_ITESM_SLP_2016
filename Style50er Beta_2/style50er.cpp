#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const char* dataTypeCasts[]={"(short)","(int)","(long int)","(long long int)","(char)","(bool)","(float)","(double)","(long double)"};
const char* sLStatementsAndCycles[]={"else if","if","else","while","for"};
FILE* original;
FILE* outputFile;
struct list{
	char val;
	struct list* next;
};
list* mainList;
list* lastE;
void pushToList(char value){
	if(value!='\t'){
		list* newNode=new struct list;
		newNode->val=value;
		newNode->next=NULL;
		if(mainList==NULL){
			mainList=newNode;
			lastE=mainList;
		}
		else{
			lastE->next=newNode;
			lastE=newNode;
		}
	}
}
void checkBracketKeys(){
	list* prev=mainList;
	list* current=mainList;
	list* newLine=mainList;
	while(current!=NULL){
		if(current->val=='/'){
			if(current->next->val=='/'){
				current=current->next->next;
				while(current!=NULL&&current->val!='\n'){
					current=current->next;
				}
			}
			if(current->next->val=='*'){
				current=current->next->next;
				while(current!=NULL&&(current->val!='*'||current->next->val!='/')){
					current=current->next;
				}
			}
		}
		if(current->val=='{'&&prev->val!='\n'){
			list* newNode=new struct list;
			newNode->val='\n';
			newNode->next=current;
			prev->next=newNode;
		}
		prev=current;
		current=current->next;
	}
}

void checkSpaces(){
	list* prev=mainList;
	list* current=mainList;
	list* temp=NULL;
	while(current!=NULL){
		if(current->val=='/'){
			if(current->next!=NULL){
				if(current->next->val=='/'){
					prev=current->next;
					current=current->next->next;
					if(current->val!=' '){
						list* newNode=new struct list;
						newNode->val=' ';
						newNode->next=current;
						prev->next=newNode;
					}
					while(current!=NULL){
						if(current->val=='\n')
							break;
						current=current->next;
					}
				}
				else if(current->next->val=='*'){
					current=current->next->next;
					while(current!=NULL){
						if(current->val=='*'&&current->next->val=='/')
							break;
						current=current->next;
					}
					current=current->next;
				}
				else if(current->next->val=='='){
					if(prev->val!=' '){
						list* newNode=new struct list;
						newNode->val=' ';
						newNode->next=current;
						prev->next=newNode;
					}
					if(current->next->next->val!=' '){
						list* newNode=new struct list;
						newNode->val=' ';
						newNode->next=current->next->next;
						current->next->next=newNode;
						current=newNode;
					}
				}
				else{
					if(prev->val!=' '){
						list* newNode=new struct list;
						newNode->val=' ';
						newNode->next=current;
						prev->next=newNode;
					}
					if(current->next->val!=' '){
						list* newNode=new struct list;
						newNode->val=' ';
						newNode->next=current->next;
						current->next=newNode;
						current=newNode;
					}
				}
			}
		}
		else if(current->val=='#'){
			current=current->next;
			while(current!=NULL){
				if(current->val=='\n')
						break;
				current=current->next;
			}
		}
		else if(current->val=='\''){
			current=current->next;
			while(current!=NULL){
				if(current->val=='\'')
						break;
				current=current->next;
			}
		}
		else if(current->val=='"'){
			current=current->next;
			while(current!=NULL){
				if(current->val=='"')
					break;
				current=current->next;
			}
		}
		else if(current->val==','){
			if(current->next!=NULL){
				if(current->next->val!=' '){
					list* newNode=new struct list;
					newNode->val=' ';
					newNode->next=current->next;
					current->next=newNode;
				}
				current=current->next;
				if(current->next->val=='-'||current->next->val=='&'){
					if(current->next->next!=NULL&&current->next->next->next!=NULL){
						if(current->next->next->val==' '){
							temp=current->next->next;
							current->next->next=current->next->next->next;
							free(temp);
						}
						current=current->next->next->next;
					}
				}
			}
		}
		else if(current->val=='+'||current->val=='-'||current->val=='*'||current->val=='%'||current->val=='&'||current->val=='|'||current->val=='^'||current->val=='='||current->val=='<'||current->val=='>'||current->val=='!'){
			if(current->next->val=='='){
				if(prev->val!=' '){
					list* newNode=new struct list;
					newNode->val=' ';
					newNode->next=current;
					prev->next=newNode;
				}
				if(current->next->next->val!=' '){
					list* newNode=new struct list;
					newNode->val=' ';
					newNode->next=current->next->next;
					current->next->next=newNode;
					current=newNode;
				}
				else{
					current=current->next->next;
				}
				if(current->next!=NULL){
					if(current->next->val==' ')
						current=current->next;
				}
				if(current->next->val=='-'||current->next->val=='&'){
					if(current->next->next!=NULL&&current->next->next->next!=NULL){
						if(current->next->next->val==' '){
							temp=current->next->next;
							current->next->next=current->next->next->next;
							free(temp);
						}
						current=current->next->next;
					}
				}
			}
			else if(current->next->val==current->val){
				temp=current;
				while(current!=NULL){
					if(current->val!=temp->val)
						break;
					temp=current;
					current=current->next;
				}
				if(current!=NULL){
					if(current->val=='='){
						if(prev->val!=' '){
							list* newNode=new struct list;
							newNode->val=' ';
							newNode->next=current;
							prev->next=newNode;
						}
						if(current->next->val!=' '){
							list* newNode=new struct list;
							newNode->val=' ';
							newNode->next=current->next;
							current->next=newNode;
							current=newNode;
						}
					}
					else if(temp->val=='&'||temp->val=='|'){
						if(prev->val!=' '){
							list* newNode=new struct list;
							newNode->val=' ';
							newNode->next=prev->next;
							prev->next=newNode;
						}
						if(current->val!=' '){
							list* newNode=new struct list;
							newNode->val=' ';
							newNode->next=temp->next;
							temp->next=newNode;
							current=newNode;
						}
					}
				}
			}
			else{
				if(current->val=='-'&&(current->next->val=='>'||current->next->next->val=='>')){
					if(current->next->val==' '){
						if(current->next->next->val=='>'){
							if(current->next->next->val==' '){
								temp=current->next;
								current->next=current->next->next;
								free(temp);
							}
						}
					}
					if(current->next->val=='>'){
						if(current->next->next->val==' '){
							temp=current->next->next;
							current->next->next=current->next->next->next;
							free(temp);
							
						}
						current=current->next->next;
					}
				}
				else if(current->val!='!'){
					if(prev->val!=' '){
						list* newNode=new struct list;
						newNode->val=' ';
						newNode->next=current;
						prev->next=newNode;
						prev=newNode;
					}
					if(current->next->val!=' '){
						list* newNode=new struct list;
						newNode->val=' ';
						newNode->next=current->next;
						current->next=newNode;
						current=newNode;
					}
					if(current->next!=NULL){
						if(current->next->val==' ')
							current=current->next;
					}
					if(current->next->val=='-'||current->next->val=='&'){
						if(current->next->next!=NULL&&current->next->next->next!=NULL){
							if(current->next->next->val==' '){
								temp=current->next->next;
								current->next->next=current->next->next->next;
								free(temp);
							}
							current=current->next->next;
						}
					}
				}
			}
		}
		else if(current->val=='i'){
			if(prev->val=='\n'||prev->val==' '){
				if(current->next->val=='f'){
					if(current->next->next->val=='('){
						list* newNode=new struct list;
						newNode->val=' ';
						newNode->next=current->next->next;
						current->next->next=newNode;
						current=newNode;
					}
				}
			}
		}
		else if(current->val=='('){
			int found=-1;
			for(int i=0;i<(sizeof(dataTypeCasts)/sizeof(char*))&&found==-1;i++){
				temp=current;
				found=i;
				for(int i2=0;i2<strlen(dataTypeCasts[i])&&temp!=NULL;i2++){
					if(temp->val!=dataTypeCasts[i][i2]){
						found=-1;
						break;
					}
					prev=temp;
					temp=temp->next;
				}
			}
			if(found!=-1){
				if(temp->val!=' '){
					list* newNode=new struct list;
					newNode->val=' ';
					newNode->next=temp;
					prev->next=newNode;
					current=newNode;
				}
			}
			if(current->next!=NULL){
				if(current->next->val==' ')
					current=current->next;
			}
			if(current->next->val=='-'||current->next->val=='&'){
				if(current->next->next!=NULL&&current->next->next->next!=NULL){
					if(current->next->next->val==' '){
						temp=current->next->next;
						current->next->next=current->next->next->next;
						free(temp);
					}
					current=current->next->next;
				}
			}
		}
		prev=current;
		current=current->next;
	}
}
void indent(){
	int indentationLevel=0;
	list* current=mainList;
	list* prev=mainList;
	list* temp=NULL;
	while(current!=NULL){
		if(current->val=='/'){
			if(current->next!=NULL){
				if(current->next->val=='/'){
					while(current!=NULL){
						if(current->val=='\n')
							break;
						prev=current;
						current=current->next;
					}
					if(current!=NULL)
						current=prev;
				}
				else if(current->next->val=='*'){
					current=current->next->next;
					while(current!=NULL){
						if(current->val=='\n'){
							for(int i=0;i<indentationLevel*4;i++){
								list* newNode=new struct list;
								newNode->val=' ';
								newNode->next=current->next;
								current->next=newNode;
								current=newNode;
							}
						}
						if(current->val=='*'&&current->next->val=='/')
							break;
						current=current->next;
					}
				}
			}
		}
		else if(current->val=='{'){
			indentationLevel++;
		}
		else if(current->val=='\n'){
			if(current->next!=NULL){
				if(current->next->val=='}'){
					indentationLevel--;
				}
			}
			for(int i=0;i<indentationLevel*4;i++){
				list* newNode=new struct list;
				newNode->val=' ';
				newNode->next=current->next;
				current->next=newNode;
				current=newNode;
			}
		}
		else{
			if(prev->val==' '){
				int found=-1;
				for(int i=0;i<(sizeof(sLStatementsAndCycles)/sizeof(char*))&&found==-1;i++){
					temp=current;
					found=i;
					for(int i2=0;i2<strlen(sLStatementsAndCycles[i])&&temp!=NULL;i2++){
						if(temp->val!=sLStatementsAndCycles[i][i2]){
							found=-1;
							break;
						}
						prev=temp;
						temp=temp->next;
					}
				}
				if(found!=-1){
					temp=prev;
					current=temp;
					if(temp->next->val==' '||temp->next->val=='('||temp->next->val=='\n'){
						while(temp!=NULL){
							if(temp->val=='\n')
								break;
							temp=temp->next;
						}
						if(temp!=NULL){
							if(temp->next!=NULL){
								if(temp->next->val!='{'){
									for(int i=0;i<4;i++){
										list* newNode=new struct list;
										newNode->val=' ';
										newNode->next=temp->next;
										temp->next=newNode;
										temp=newNode;
									}
								}
							}
						}
					}
				}
			}
		}
		prev=current;
		current=current->next;
	}
}

void emptyList(){
	list* current;
	while(mainList!=NULL){
		current=mainList;
		fprintf(outputFile,"%c",current->val);
		mainList=mainList->next;
		free(current);
	}
}
int main(int argc, char** argv){
	if(argc!=3){
		printf("\033[0;31mUsage: ./style50er 'file name' 'output file'\n");
		return 0;
	}
	original=fopen(argv[1],"r");
	if(original==NULL){
		printf("\033[0;31mNo such file named: %s\n",argv[1]);
		return 0;
	}
	char c;
	char pvrc=' ';
	long int length=0;
	while(!feof(original)){
		fscanf(original,"%c",&c);
		if(c==' '&&pvrc=='\n'){
			while(c==' '&&feof(original)==false){
				fscanf(original,"%c",&c);
			}
		}
		else if(c==' '){
			pushToList(' ');
			while(c==' '&&feof(original)==false){
				fscanf(original,"%c",&c);
			}
		}
		if(!feof(original)){
			pushToList(c);
		}
		pvrc=c;
	}
	
	fclose(original);
	printf("Sepparating inline bracket keys...\n");
	checkBracketKeys();
	printf("Setting up missing spaces...\n");
	checkSpaces();
	printf("Indenting code...\n");
	indent();
	
	outputFile=fopen(argv[2],"w");
	emptyList();
	fclose(outputFile);
	printf("\033[0;32mSuccessfully stylized50 the file: %s\n",argv[1]);
	return 0;
}
