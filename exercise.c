#define _CRT_SECURE_NO_WARNINGS 1
#define MaxSize 50

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct ELNode {
	int no;
	char name[MaxSize / 5];
	char depno;
	double salary;
	struct ELNode* next;
}EmployeeLinkNode;


EmployeeLinkNode* InitList() {
	EmployeeLinkNode* L = (EmployeeLinkNode*)malloc(sizeof(EmployeeLinkNode));
	if (L != NULL) {
		L->next = NULL;
	}
	return L;
}


void CreateList(EmployeeLinkNode* L, FILE* fp) {
	EmployeeLinkNode* p = L, * s;  // tail insertion method
	char tmp_f[MaxSize], tmp_e[4][MaxSize / 5] = { '\0' }, * ptmp_f;  // If the tmp_e character array is not initialized (each element is initialized to '\0'), the result of calling functions such as "puts()" may be a bunch of garbled code.
	int i, j;

	while (!feof(fp)) {
		s = (EmployeeLinkNode*)malloc(sizeof(EmployeeLinkNode));
		if (s != NULL) {
			fgets(tmp_f, MaxSize, fp);
			ptmp_f = tmp_f;
			i = j = 0;
			while (*ptmp_f != '\n' && *ptmp_f != '\0') {  // The string in the last line of the file does not contain '\n', so it needs to be added with "*ptmp != '\0'".
				if (*ptmp_f == ',') {
					i++;
					j = 0;
					ptmp_f++;
				}
				tmp_e[i][j] = *ptmp_f;
				ptmp_f++;
				j++;
			}

			s->no = atoi(tmp_e[0]);
			strcpy(s->name, tmp_e[1]);
			s->depno = tmp_e[2][0];
			s->salary = atof(tmp_e[3]);
			
			p->next = s;
			p = s;
		}
	}
	p->next = NULL;
}


void DispList(EmployeeLinkNode* L) {
	EmployeeLinkNode* p = L->next;
	while (p != NULL) {
		printf("Employee %d:\nname : %s, depno : %c, salary : %.2f\n", p->no, p->name, p->depno, p->salary);
		p = p->next;
	}
}


int main() {
	EmployeeLinkNode* L = InitList();
	FILE* fp = fopen("C:/Users/34803/Desktop/a.dat", "r");
	CreateList(L, fp);
	DispList(L);

	return 0;
}