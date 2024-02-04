#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char ElemType;
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
	if (n < 1) {
		printf("The least length of the linked list is 1.\n");
	}
	else {
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
}


void DispList(LinkNode* L) {
	LinkNode* p = L->next;
	printf(">>> ");
	while (p != NULL) {
		printf("%c ", p->data);
		p = p->next;
	}
	printf("\n");
}


int ListLength(LinkNode* L) {
	LinkNode* p = L->next;
	int i = 0;
	while (p != NULL) {
		i++;
		p = p->next;
	}
	return i;
}


bool ListEmpty(LinkNode* L) {
	return (L->next == NULL);
}


bool GetElem(LinkNode* L, int n, ElemType* e) {
	if (n < 1) {
		return false;
	}
	LinkNode* p = L;
	int i = 0;
	while (i < n && p != NULL) {
		i++;
		p = p->next;
	}
	if (p == NULL) {
		return false;
	}
	else {
		*e = p->data;
		return true;
	}
}


int LocateElem(LinkNode* L, ElemType e) {
	LinkNode* p = L->next;
	int i = 0;
	while (p != NULL) {
		i++;
		if (p->data == e) {
			return i;
		}
		p = p->next;
	}
	return 0;
}


bool ListInsert(LinkNode* L, int n, ElemType e) {
	if (n < 1) {
		return false;
	}
	int i = 0;
	LinkNode* p = L, * s;
	while (i < n - 1 && p != NULL) {
		i++;
		p = p->next;
	}
	if (p == NULL) {
		return false;
	}
	else {
		s = (LinkNode*)malloc(sizeof(LinkNode));
		if (s != NULL) {
			s->data = e;
			s->next = p->next;
			p->next = s;
			return true;
		}
		return false;
	}
}


bool ListDelete(LinkNode* L, int n, ElemType* e) {
	if (n < 1) {
		return false;
	}
	LinkNode* p = L, * q;
	int i = 0;
	while (i < n - 1 && p != NULL) {
		i++;
		p = p->next;
	}
	if (p == NULL) {
		return false;
	}
	else {
		q = p->next;
		if (q == NULL) {
			return false;
		}
		*e = q->data;
		p->next = q->next;
		free(q);
		return true;
	}
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


void PartListByParity(LinkNode* L, LinkNode* A, LinkNode* B) {
	LinkNode* p = L->next, * pre = L, * s = B;
	bool t = false;
	while (p != NULL) {
		if (t) {
			s->next = p;
			s = p;
			p = p->next;
			pre->next = p;
			t = false;
		}
		else {
			pre = p;
			p = p->next;
			t = true;
		}
	}
	s->next = NULL;
	*A = *L;
}


bool DeleteMaxNode(LinkNode* L) {
	if (L->next == NULL) {
		return false;
	}
	LinkNode* pre = L, * p = L->next, * maxpre = pre, * maxp = p;
	while (p != NULL) {
		if (p->data > maxp->data) {
			maxpre = pre;
			maxp = p;
		}
		pre = p;
		p = p->next;
	}
	maxpre->next = maxp->next;
	free(maxp);
	return true;
}


bool ListSort(LinkNode* L) {
	if (L->next != NULL && L->next->next != NULL) {
		LinkNode* p = L->next->next, * pre, * q;
		L->next->next = NULL;
		while (p != NULL) {
			pre = L;
			q = p->next;
			while (pre->next != NULL && pre->next->data < p->data) {
				pre = pre->next;
			}
			p->next = pre->next;
			pre->next = p;
			p = q;
		}
		return true;
	}
	else {
		return false;
	}
}


int main() {
	LinkNode* L = InitList();

	ElemType a[] = { 'a', 'b', 'c', 'd', 'e' };
	CreateList(L, a, 5);

	DispList(L);

	int listLength = ListLength(L);
	printf("\nThe length of the linked list is %d.\n", listLength);

	if (ListEmpty(L)) {
		printf("\nEmpty.\n");
	}
	else {
		printf("\nNot Empty.\n");
	}

	int n = 3;
	ElemType e;
	if (GetElem(L, n, &e)) {
		printf("\nThe %d element is %c.\n", n, e);
	}
	else {
		printf("\nIndexError!\n");
	}

	e = 'd';
	int location = LocateElem(L, e);
	if (location == 0) {
		printf("\nNot found.\n");
	}
	else {
		printf("\nThe location of Elem %c is %d.\n", e, location);
	}

	if (ListInsert(L, 4, 'f')) {
		printf("\n");
		DispList(L);
	}
	else {
		printf("\nInsertError!\n");
	}

	if (ListDelete(L, 3, &e)) {
		printf("\nDelete %c\n", e);
		DispList(L);
	}
	else {
		printf("\nDeleteError!\n");
	}

	LinkNode* A = InitList();
	LinkNode* B = InitList();
	PartListByParity(L, A, B);
	printf("\n");
	DispList(A);
	DispList(B);

	DestroyList(L);

	return 0;
}