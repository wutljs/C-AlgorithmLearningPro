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
	CDLinkNode* p = L->next, * s;
	int i = 1;
	while (i < n && p != L) {  //breaking the conditions of the cycle : i == n || p == L
		i++;
		p = p->next;
	}
	if (i != n) {
		return false;
	}
	s = (CDLinkNode*)malloc(sizeof(CDLinkNode));
	if (s != NULL) {
		s->data = e;
		s->next = p;
		s->prior = p->prior;
		p->prior->next = s;
		p->prior = s;
		return true;
	}
	return false;
}


bool ListDelete(CDLinkNode* L, int n, ElemType* e) {
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
	*e = p->data;
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
	return true;
}


int FindDataNodeNum(CDLinkNode* L, ElemType value) {
	CDLinkNode* p = L->next;
	int i = 0;
	while (p != L) {
		if (p->data == value) {
			i++;
		}
		p = p->next;
	}
	return i;
}


bool DeleteSpecialNode(CDLinkNode* L, ElemType value) {
	CDLinkNode* p = L->next;
	while (p != L && p->data != value) {
		p = p->next;
	}
	if (p == L) {
		return false;
	}
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
	return true;
}


bool ListIsSymmetric(CDLinkNode* L) {
	if (L->next == L || L->next->next == L) {  // The cDLinkedList with no (or only one) element cannot be considered symmetric.
		return false;
	}
	CDLinkNode* p = L->next, * q = L->prior;
	while ((q->next != p) && p != q) {
		if (p->data != q->data) {
			return false;
		}
		p = p->next;
		q = q->prior;
	}
	return true;
}


int main() {
	CDLinkNode* L = InitList();

	ElemType a[] = { 6, 7, 8, 7, 6 };
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

	ElemType value = 7;
	n = FindDataNodeNum(L, value);
	printf("\nThe number of %d(Elem) is %d.\n", value, n);

	value = 8;
	if (DeleteSpecialNode(L, value)) {
		printf("\nThe node which is %d was deleted.\n", value);
		DispList(L);
	}
	else {
		printf("\nNo such element!\n");
	}

	if (ListIsSymmetric(L)) {
		printf("\nThe cDLinkedList is symmetric.\n");
	}
	else {
		printf("\nThe cDLinkedList is not symmetric.\n");
	}

	DestroyList(L);

	return 0;
}