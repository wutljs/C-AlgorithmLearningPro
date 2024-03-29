#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char ElemType;
typedef struct CLNode {
	ElemType data;
	struct CLNode* next;
}CLinkNode;


CLinkNode* InitList() {
	CLinkNode* L = (CLinkNode*)malloc(sizeof(CLinkNode));
	if (L != NULL) {
		L->next = NULL;
	}
	return L;
}


void CreateList(CLinkNode* L, ElemType a[], int n) {
	CLinkNode* p = L, * s;
	for (int i = 0; i < n; i++) {
		s = (CLinkNode*)malloc(sizeof(CLinkNode));
		if (s != NULL) {
			s->data = a[i];
			p->next = s;
			p = s;
		}
	}
	p->next = L;
}


void DestroyList(CLinkNode* L) {
	CLinkNode* pre = L, * p = L->next;
	while (p != L) {
		free(pre);
		pre = p;
		p = p->next;
	}
	free(pre);
}


void DispList(CLinkNode* L) {
	CLinkNode* p = L->next;
	printf("CLinkedList : ");
	while (p != L) {
		printf("%c ", p->data);
		p = p->next;
	}
	printf("\n");
}


bool ListEmpty(CLinkNode* L) {
	return (L->next == L);
}


int ListLength(CLinkNode* L) {
	CLinkNode* p = L->next;
	int i = 0;
	while (p != L) {
		i++;
		p = p->next;
	}
	return i;
}


bool GetElem(CLinkNode* L, int n, ElemType* e) {
	if (n < 1) {
		return false;
	}
	CLinkNode* p = L->next;
	int i = 1;
	while (i < n && p != L) {
		i++;
		p = p->next;
	}
	if (p == L) {
		return false;
	}
	*e = p->data;
	return true;
}


int LocateElem(CLinkNode* L, ElemType e) {
	CLinkNode* p = L->next;
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


bool ListInsert(CLinkNode* L, int n, ElemType e) {
	if (n < 1) {
		return false;
	}
	CLinkNode* p = L, * s;
	bool t = true;
	int i = 0;
	while (i < n - 1 && (p != L || t)) {
		if (i == 0) {
			t = false;
		}
		i++;
		p = p->next;
	}
	if (p == L && !t) {
		return false;
	}
	s = (CLinkNode*)malloc(sizeof(CLinkNode));
	if (s != NULL) {
		s->data = e;
		s->next = p->next;
		p->next = s;
	}
	return true;
}


bool ListDelete(CLinkNode* L, int n, ElemType* e) {
	if (n < 1) {
		return false;
	}
	CLinkNode* p = L, * q;
	int i = 0;
	bool t = true;
	while (i < n - 1 && (p != L || t)) {
		if (i == 0) {
			t = false;
		}
		i++;
		p = p->next;
	}
	if ((p == L && !t) || p->next == L) {
		return false;
	}
	q = p->next;
	*e = q->data;
	p->next = q->next;
	free(q);
	return true;
}


int main() {

	return 0;
}
