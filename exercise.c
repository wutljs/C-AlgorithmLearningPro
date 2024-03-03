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
		L->next;
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


void PartListByX(LinkNode* L, int x) {
	LinkNode* pre = L->next, * p = pre->next, * q;
	pre->next = NULL;
	while (p != NULL) {
		q = p->next;
		if (p->data < x) {
			p->next = L->next;
			L->next = p;
		}
		else {
			p->next = pre->next;
			pre->next = p;
		}
		p = q;
	}
}


int main() {

	LinkNode* L = InitList();
	ElemType a[] = { 1, 4, 5, 8, 6, 7, 3, 1, 2, 9 };
	int n = 10;
	CreateList(L, a, n);
	DispList(L);

	int x = 6;
	PartListByX(L, x);
	printf("\nPart LinkedList by %d.\n", x);
	DispList(L);

	DestroyList(L);

	return 0;
}