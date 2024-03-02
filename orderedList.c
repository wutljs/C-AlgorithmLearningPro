#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef int ElemType;
typedef struct LNode {  // use linkedList to store orderedList
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


void CreateList(LinkNode* L, ElemType a[], int n) {
	LinkNode* p = L, * s;
	for (int i = 0; i < n; i++) {
		s = (LinkNode*)malloc(sizeof(LinkNode));
		if (s != NULL) {
			s->data = a[i];
			p->next = s;
			p = s;
		}
		else
			printf("\nfail to InitList!\n");
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
	printf("\n(DispList)");
	while (p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}


void TwoWayMerge(LinkNode* A, LinkNode* B, LinkNode* L) {  // Assuming that both ordered lists are in ascending order.
	LinkNode* p1 = A->next;
	LinkNode* p2 = B->next;
	LinkNode* p3 = L;
	LinkNode* s;

	while (p1 != NULL && p2 != NULL) {
		s = (LinkNode*)malloc(sizeof(LinkNode));
		if (s != NULL) {
			if (p2->data < p1->data) {
				s->data = p2->data;
				p2 = p2->next;
			}
			else {
				s->data = p1->data;
				p1 = p1->next;
			}
			p3->next = s;  // tail insertion method
			p3 = s;
		}
	}

	LinkNode* p;  // Pointer p points to a single item in a single linked list with remaining items.
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

	p1 = p2 = p3 = s = p = NULL;
}


int main() {

	return 0;
}