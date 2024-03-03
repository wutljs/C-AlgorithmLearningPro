#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;
typedef struct LNode {
	ElemType data;
	struct LNode* next;
}LinkNode;


LinkNode* InitList() {
	LinkNode* L = (LinkNode*)malloc(sizeof(LinkNode));
	if (L != NULL) {
		L->next = NULL;
	}
	return L;
}


void CreateList(LinkNode* L, ElemType a[], int n) {  // tail insertion method
	LinkNode* p = L, * s;
	for (int i = 0; i < n; i++) {
		s = (LinkNode*)malloc(sizeof(LinkNode));
		if (s != NULL) {
			s->data = a[i];
			p->next = s;
			p = s;
		}
	}
	p->next = NULL;
}


void DestroyList(LinkNode* L) {
	LinkNode* pre = L, * p = L->next;
	while (p != NULL) {
		free(pre);
		pre = p;
		p = p->next;
	}
	free(pre);
}


void DispList(LinkNode* L) {
	LinkNode* p = L->next;
	printf("(DispList) ");
	while (p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}


void CombineList(LinkNode* L1, LinkNode* L2, LinkNode* L3) {
	LinkNode* p1 = L1->next, * p2 = L2->next, * p3 = L3, * s;
	bool getElemFromL1 = true;

	while (p1 != NULL && p2 != NULL) {
		s = (LinkNode*)malloc(sizeof(LinkNode));
		if (s != NULL) {
			if (getElemFromL1) {
				s->data = p1->data;
				p3->next = s;
				p3 = s;

				p1 = p1->next;
				getElemFromL1 = false;
			}
			else {
				s->data = p2->data;
				p3->next = s;
				p3 = s;

				p2 = p2->next;
				getElemFromL1 = true;
			}
		}
	}

	LinkNode* p;
	if (p1 == NULL) {
		p = p2;
	}
	else
		p = p1;

	while (p != NULL) {
		s = (LinkNode*)malloc(sizeof(LinkNode));
		if (s != NULL) {
			s->data = p->data;
			p3->next = s;
			p3 = s;

			p = p->next;
		}
	}

	p3->next = NULL;
}


int main() {

	LinkNode* L1 = InitList();
	ElemType a[] = { 1, 2, 3 };
	int n = 3;
	CreateList(L1, a, n);
	DispList(L1);

	LinkNode* L2 = InitList();
	ElemType b[] = { 2, 3, 5 };
	n = 3;
	CreateList(L2, b, n);
	DispList(L2);

	LinkNode* L3 = InitList();
	CombineList(L1, L2, L3);
	DispList(L3);

	return 0;
}