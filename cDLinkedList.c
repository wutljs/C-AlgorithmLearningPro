#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef int ElemType;
typedef struct CDNode {
	ElemType data;
	struct CDNode* prior;
	struct CDNode* next;
}CDLinkNode;


CDLinkNode* InitList() {
	CDLinkNode* L = (CDLinkNode*)malloc(sizeof(CDLinkNode));
	if (L != NULL) {
		L->prior = L->next = L;
	}
	return L;
}


void CreateList(CDLinkNode* L, ElemType a[], int n) {
	CDLinkNode* p = L, * s;
	for (int i = 0; i < n; i++) {
		s = (CDLinkNode*)malloc(sizeof(CDLinkNode));
		if (s != NULL) {
			s->data = a[i];
			p->next = s;
			s->prior = p;
			p = s;
		}
	}
	p->next = L;
	L->prior = p;
}


void DestroyList(CDLinkNode* L) {
	CDLinkNode* p = L->next, * pre = L;
	while (p != L) {
		free(pre);
		pre = p;
		p = p->next;
	}
	free(pre);
}


int ListLength(CDLinkNode* L) {
	CDLinkNode* p = L->next;
	int n = 0;
	while (p != L) {
		n++;
		p = p->next;
	}
	return n;
}


bool ListEmpty(CDLinkNode* L) {
	return (L->prior == L);
}


void DispList(CDLinkNode* L) {
	CDLinkNode* p = L->next;
	printf("CDLinkedList:\n");
	while (p != L) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}


bool GetElem(CDLinkNode* L, int n, ElemType* e) {
	if (n < 1) {
		return false;
	}
	CDLinkNode* p = L->next;
	int i = 1;
	while (i < n && p != L) {
		i++;
		p = p->next;
	}
	if (p == L) {
		return false;
	}
	else {
		*e = p->data;
		return true;
	}
}


int LocateElem(CDLinkNode* L, ElemType e) {
	CDLinkNode* p = L->next;
	int i = 1;
	while (p != L && p->data != e) {
		i++;
		p = p->next;
	}
	if (p == L) {
		return 0;
	}
	return i;
}


bool ListInsert(CDLinkNode* L, int n, ElemType e) {
	if (n < 1) {
		return false;
	}
	int i = 0;
	bool t = false;
	CDLinkNode* p = L, * s;
	while (i < n - 1 && (p != L || !t)) {
		if (i == 0) {
			t = true;
		}
		i++;
		p = p->next;
	}
	if (p == L && t) {
		return false;
	}
	s = (CDLinkNode*)malloc(sizeof(CDLinkNode));
	if (s != NULL) {
		s->data = e;
		s->next = p->next;
		p->next->prior = s;
		s->prior = p;
		p->next = s;
		return true;
	}
	return false;
}


bool ListDelete(CDLinkNode* L, int n, ElemType* e) {
	if (n < 1) {
		return false;
	}
	int i = 0;
	bool t = false;
	CDLinkNode* p = L, * q;
	while (i < n - 1 && (p != L || !t)) {
		if (i == 0) {
			t = true;
		}
		i++;
		p = p->next;
	}
	if ((p == L && t) || (p->next == L)) {
		return false;
	}
	q = p->next;
	*e = q->data;
	p->next = q->next;
	q->next->prior = p;
	free(q);
	return true;
}


int main() {
	CDLinkNode* L = InitList();

	ElemType a[] = { 1, 2, 3, 4, 5 };
	int n = 5;
	CreateList(L, a, n);

	DispList(L);

	int listLength = ListLength(L);
	printf("\nThe length of the cDLinkedList is %d.\n", listLength);

	if (ListEmpty(L)) {
		printf("\nEmpty!\n");
	}
	else {
		printf("\nNot Empty.\n");
	}

	n = 1;
	ElemType e;
	if (GetElem(L, n, &e)) {
		printf("\nThe %d element of the cDLinkedList is %d.\n", n, e);
	}
	else {
		printf("\nIndexError!\n");
	}

	e = 6;
	int elemLocation = LocateElem(L, e);
	if (elemLocation == 0) {
		printf("\n%d is not in the cDLinkedList.\n", e);
	}
	else {
		printf("\nThe location of %d is %d", e, elemLocation);
	}

	n = 2;
	e = 78;
	if (ListInsert(L, n, e)) {
		printf("\nInsert %d successfully!\n", e);
		DispList(L);
	}
	else {
		printf("\nIndexError!\n");
	}

	n = 2;  // "n" is the index of the number which was deleted, "e" is the number which was deleted.
	if (ListDelete(L, n, &e)) {
		printf("\nDelete %d successfully!\n", e);
		DispList(L);
	}
	else {
		printf("\nIndexError!\n");
	}

	DestroyList(L);

	return 0;
}