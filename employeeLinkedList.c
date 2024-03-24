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

			int m, n;
			for (m = 0; m < 4; m++) {
				n = 0;
				while (tmp_e[m][n] != '\0') {
					tmp_e[m][n] = '\0';
					n++;
				}
			}
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


void DestroyList(EmployeeLinkNode* L) {
	EmployeeLinkNode* pre = L, * p = L->next;
	while (p != NULL) {
		free(pre);
		pre = p;
		p = p->next;
	}
	free(pre);
}


void SortList(EmployeeLinkNode* L) {
	if (L->next == NULL || L->next->next == NULL)
		printf("\nAt least two elements are required to sort.\n");
	else {
		EmployeeLinkNode* pre = L->next->next, * p = pre->next, * q;
		L->next->next = NULL;
		while (pre != NULL) {
			q = L;
			while (q->next != NULL && pre->no > q->next->no) {  // sort by "no"
				q = q->next;
			}
			pre->next = q->next;
			q->next = pre;

			pre = p;
			if (p != NULL)
				p = p->next;
		}

	}
}


void ListAppend(EmployeeLinkNode* L, int no, char name[], char depno, double saraly) {
	EmployeeLinkNode* s = (EmployeeLinkNode*)malloc(sizeof(EmployeeLinkNode));
	if (s != NULL) {  // head insertion mehtod
		s->no = no;
		strcpy(s->name, name);
		s->depno = depno;
		s->salary = saraly;

		s->next = L->next;
		L->next = s;
	}
}


bool ListDelete(EmployeeLinkNode* L, int no) {
	EmployeeLinkNode* p = L, * q;

	while (p->next != NULL && p->next->no != no) {
		p = p->next;
	}
	if (p->next == NULL) {
		return false;
	}
	q = p->next;
	p->next = q->next;
	free(q);

	return true;
}


void SaveList(EmployeeLinkNode* L, FILE* fp) {
	EmployeeLinkNode* p = L->next;
	char info[MaxSize] = { '\0' };
	while (p != NULL) {
		sprintf(info, "%d,%s,%c,%d\n", p->no, p->name, p->depno, (int)p->salary);
		fputs(info, fp);
		p = p->next;
	}
}


int main() {

	return 0;
}