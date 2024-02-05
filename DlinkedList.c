#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef int ElemType;

typedef struct DNode {
	ElemType data;
	struct DNode* prior;
	struct DNode* next;
}DLinkNode;


DLinkNode* InitList() {
	DLinkNode* L = (DLinkNode*)malloc(sizeof(DLinkNode));
	if (L != NULL) {
		L->prior = L->next = NULL;
	}
	return L;
}


void CreateList(DLinkNode* L, ElemType a[], int n) {  // tail insertion method
	DLinkNode* p = L, * s;
	for (int i = 0; i < n; i++) {  // head insertion method
		s = (DLinkNode*)malloc(sizeof(DLinkNode));
		if (s != NULL) {
			s->data = a[i];
			s->prior = p;
			p->next = s;
			p = s;
		}
	}
	p->next = NULL;
}


void DestroyList(DLinkNode* L) {
	DLinkNode* pre = L, * p = L->next;
	while (p != NULL) {
		free(pre);
		pre = p;
		p = p->next;
	}
	free(pre);
}


int ListLength(DLinkNode* L) {
	if (L->next == NULL) {
		return 0;
	}
	DLinkNode* p = L->next;
	int i = 0;
	while (p != NULL) {
		i++;
		p = p->next;
	}
	return i;
}


bool ListEmpty(DLinkNode* L) {
	return (L->next == NULL);
}


void DispList(DLinkNode* L) {
	if (L->next == NULL) {
		printf("\n");
	}
	else {
		printf("\n>>> ");
		DLinkNode* p = L->next;
		while (p != NULL) {
			printf("%d ", p->data);
			p = p->next;
		}
		printf("\n");
	}
}


bool GetElem(DLinkNode* L, int n, ElemType* e) {
	if (n < 1) {
		return false;
	}
	DLinkNode* p = L;
	int i = 0;
	while (i < n && p != NULL) {
		i++;
		p = p->next;
	}
	if (p == NULL) {
		return false;
	}
	*e = p->data;
	return true;
}


int LocateElem(DLinkNode* L, ElemType e) {
	DLinkNode* p = L;
	int i = 0;
	while (p != NULL && p->data != e) {
		i++;
		p = p->next;
	}
	if (p == NULL) {
		return 0;
	}
	return i;
}


bool ListInsert(DLinkNode* L, int n, ElemType e) {
	if (n < 1) {
		return false;
	}
	DLinkNode* p = L, * s;
	int i = 0;
	while (i < n - 1 && p != NULL) {
		i++;
		p = p->next;
	}
	if (p == NULL) {
		return false;
	}
	s = (DLinkNode*)malloc(sizeof(DLinkNode));
	if (s != NULL) {
		s->data = e;
		s->next = p->next;
		if (p->next != NULL) {
			p->next->prior = s;
		}
		s->prior = p;
		p->next = s;
		return true;
	}
	return false;
}


bool ListDelete(DLinkNode* L, int n, ElemType* e) {
	if (n < 1) {
		return false;
	}
	DLinkNode* p = L, * q;
	int i = 0;
	while (i < n - 1 && p != NULL) {
		i++;
		p = p->next;
	}
	if (p == NULL || p->next == NULL) {
		return false;
	}
	q = p->next;
	*e = q->data;
	p->next = q->next;
	if (q->next != NULL) {
		q->next->prior = p;
	}
	free(q);
	return true;
}


int main() {
	DLinkNode* L = InitList();

	ElemType a[] = { 1, 2, 3, 4, 5, 6 };
	int n = 6;
	CreateList(L, a, n);
	DispList(L);

	int listLength = ListLength(L);
	printf("\nThe length of the double linked list is %d.\n", listLength);

	n = 2;
	ElemType e;
	if (GetElem(L, n, &e)) {
		printf("\nThe %d element of the double linked list is %d.\n", n, e);
	}
	else {
		printf("\nIndexError!\n");
	}

	e = 1;
	int locateResult = LocateElem(L, e);
	if (locateResult == 0) {
		printf("\nNo such the element.\n");
	}
	else {
		printf("\nThe location of %d is %d.\n", e, locateResult);
	}

	if (ListEmpty(L)) {
		printf("\nEmpty.\n");
	}
	else {
		printf("\nNot empty.\n");
	}

	n = 6, e = 7;
	if (ListInsert(L, n, e)) {
		DispList(L);
	}
	else {
		printf("\nIndexError!\n");
	}

	n = 1;
	if (ListDelete(L, n, &e)) {
		printf("\nThe element which was deleted is %d.\n", e);
		DispList(L);
	}
	else {
		printf("\nIndexError!\n");
	}

	DestroyList(L);

	return 0;
}