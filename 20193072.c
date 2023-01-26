#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char *optarg;
typedef struct Node {
	int adress;
	char listCode[3][10];
	struct Node* next;
}node;

void SetAdress(node* head, int* len, int *depth) {
	int stack, add = 0;
	node* p = head->next;

	while (p != NULL) {

		if (strcmp(p->listCode[1], "START") == 0) {
			p->adress = atoi(p->listCode[2]);
			stack = p->adress;
		}
		else if (strcmp(p->listCode[1], "END") == 0) {
			*depth = stack;
			stack += add;
			p->adress = stack;
			break;
		}
		else if (strcmp(p->listCode[0], "**") == 0) {
			stack += add;
			p->adress = stack;
			add = 3;
		}
		else if (strcmp(p->listCode[1], "WORD") == 0) {
			stack += add;
			p->adress = stack;
			add = 3;
		}
		else if (strcmp(p->listCode[1], "RESW") == 0) {
			stack += add;
			p->adress = stack;
			add = 3 * atoi(p->listCode[2]);
		}
		else if (strcmp(p->listCode[1], "BYTE") == 0) {
			stack += add;
			p->adress = stack;
			add = 1;
		}
		else if (strcmp(p->listCode[1], "RESB") == 0) {
			stack += add;
			p->adress = stack;
			add = 1 * atoi(p->listCode[2]);
		}
		p = p->next;
	}
	*len = p->adress - head->next->adress;
}

void InsertNode(node* head, char code[3][10]) {
	node* tem = (node*)malloc(sizeof(node));
	tem->next = NULL;
	for (int i = 0; i < 3; i++) {
		strcpy(tem->listCode[i], code[i]);
	}
	tem->adress = 0;
	if (head->next == NULL) {
		tem->next = head->next;
		head->next = tem;
		return;
	}
	node* q = head;
	while (q->next != NULL) {
		q = q->next;
	}
	q->next = tem;
}

void PrintLen(int * len) {
	printf("\n\n\nLength of the input program is %d\n\n\n", *len);
}

void PrintSymbolTable(node* head) {

	node* tmp = head->next;
	printf("The contents of Symbol table:\n\n\n");
	while (tmp != NULL) {
		if (strcmp(tmp->listCode[1], "RESW") == 0) {
			printf("%s\t%d\n", tmp->listCode[0], tmp->adress);
		}
		else if (strcmp(tmp->listCode[1], "RESB") == 0) {
			printf("%s\t%d\n", tmp->listCode[0], tmp->adress);
		}
		else if (strcmp(tmp->listCode[1], "WORD") == 0) {
			printf("%s\t%d\n", tmp->listCode[0], tmp->adress);
		}
		else if (strcmp(tmp->listCode[1], "BYTE") == 0) {
			printf("%s\t%d\n", tmp->listCode[0], tmp->adress);
		}
		tmp = tmp->next;
	}
	printf("\n\n\n\n");
}

void PrintNode(node* head) {
	node* tmp = head->next;
	printf("Ten contents of Intermed File:\n\n\n");
	while (tmp != NULL) {
		if (strcmp(tmp->listCode[1], "START") == 0) {
			for (int i = 0; i < 3; i++) {
				printf("%s\t", tmp->listCode[i]);
			}
		}
		else {
			printf("%d\t", tmp->adress);
			for (int i = 0; i < 3; i++) {
				printf("%s\t", tmp->listCode[i]);
			}
			
			
		}
		printf("\n");
		tmp = tmp->next;
	}
	printf("\n\n");
}

void PrintH(node* head) {
	char name[10];
	int stad, finad;
	node* tmp = head->next;
	strcpy(name, tmp->listCode[0]);
	stad = atoi(tmp->listCode[2]);
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}
	finad = tmp->adress;
	printf("H^%s^%06d^%06d\n", name, stad, finad);
}

void PrintT(node* head, int dif) {
	char  code[4][3] = { "33","44","53","57" };
	int startad = 0;
	node* cur;
	node* search;
	cur = head->next;
	startad = atoi(cur->listCode[2]);
	dif = dif - startad;
	printf("T^00%d^%d", startad, dif);
	
	while (cur != NULL) {
		search = head->next;
		char txt[11];
		int len;
		if (strcmp(cur->listCode[1], "LDA") == 0) {
			while (search != NULL) {
				if (strcmp(cur->listCode[2], search->listCode[0]) == 0) {
					printf("^%s%d",code[0],search->adress);
				}
				search = search->next;
			}
		}
		if (strcmp(cur->listCode[1], "STA") == 0) {
			while (search != NULL) {
				if (strcmp(cur->listCode[2], search->listCode[0]) == 0) {
					printf("^%s%d", code[1], search->adress);
				}
				search = search->next;
			}
		}
		if (strcmp(cur->listCode[1], "LDCH") == 0) {
			while (search != NULL) {
				if (strcmp(cur->listCode[2], search->listCode[0]) == 0) {
					printf("^%s%d", code[2], search->adress);
				}
				search = search->next;
			}
		}
		if (strcmp(cur->listCode[1], "STCH") == 0) {
			while (search != NULL) {
				if (strcmp(cur->listCode[2], search->listCode[0]) == 0) {
					printf("^%s%d", code[3], search->adress);
				}
				search = search->next;
			}
		}
		if (strcmp(cur->listCode[1], "WORD") == 0) {
			printf("^%06x",atoi(cur->listCode[2]));
		}
		if (strcmp(cur->listCode[1], "BYTE") == 0) {
			len = strlen(cur->listCode[2]) - 3;
			strcpy(txt, "");
			strncpy(txt, cur->listCode[2] + 2, len);
			txt[len] = 0;
			printf("^");
			for (int i = 0; i < strlen(txt); i++) {
				printf("%2x", txt[i]);
			}
			
		}
		cur = cur->next;
	}
	printf("\n");
	
}

void PrintE(node* head) {
	node *tmp = head->next;
	printf("E^%06d", tmp->adress);
}

int main(int argc, char ** argv) {
	char code[3][10];
	int len = 0, depth = 0,option = 0;
	FILE* fp;
	node* head = (node*)malloc(sizeof(node));
	while((option=getopt(argc,argv,"i:"))!=-1){
		switch(option)
		{
			case 'i': fp = fopen(optarg,"r"); break;
			default : printf("error"); break;
			
		}
	}
	head->next = NULL;
	printf("The contents of Input file:\n\n\n");
	while (1) {
		fscanf(fp, "%s%s%s", code[0], code[1], code[2]);
		printf("%s %s %s\n", code[0], code[1], code[2]);
		InsertNode(head, code);
		if (strcmp(code[1], "END") == 0) {
			break;
		}
	}
	SetAdress(head,&len, &depth);
	PrintLen(&len);
	PrintSymbolTable(head);
	PrintNode(head);
	printf("Object Program has been generated.\n\n\nObject Program :\n\n");
	PrintH(head);
	PrintT(head, depth);
	PrintE(head);
	fclose(fp);
	return 0;
}
