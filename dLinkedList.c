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


bool InverseList(DLinkNode* L) {
	if (L->next == NULL) {
		return false;
	}
	DLinkNode* p = L->next, * q;
	L->next = NULL;
	while (p != NULL) {
		q = p;
		p = p->next;
		q->next = L->next;
		if (L->next != NULL) {
			L->next->prior = q;
		}
		q->prior = L;
		L->next = q;
	}
	return true;
}


bool SortList(DLinkNode* L) {
	if (L->next == NULL || L->next->next == NULL) {
		return false;
	}
	DLinkNode* p = L->next->next, * pre, * q;
	L->next->next = NULL;
	while (p != NULL) {
		q = p->next;
		pre = L;
		while (pre->next != NULL && pre->next->data < p->data) {
			pre = pre->next;
		}
		p->next = pre->next;
		if (pre->next != NULL) {
			pre->next->prior = p;
		}
		p->prior = pre;
		pre->next = p;
		p = q;
	}
	return true;
}


int main() {

	return 0;
}
