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
	printf("(DispList) ");
	while (p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
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


bool ListDistinct(LinkNode* L) {  // The LinkedList should be sorted by ascending.
	LinkNode* pre = L->next, * p, * q;
	if (pre == NULL || pre->next == NULL) {
		printf("\nThe LinkedList doesn't have enough elements.\n");
		return false;
	}
	p = pre->next;

	while (p != NULL) {
		if (p->data != pre->data) {
			pre = p;
			p = p->next;
		}
		else {
			q = p;
			p = p->next;
			pre->next = p;
			free(q);
		}
	}

	q = NULL;

	return true;
}


void ListsUnionSet(LinkNode* L1, LinkNode* L2, LinkNode* L3) {  // Get the union of two sets (stored in ascending order using a linked list)
	LinkNode* p1 = L1->next, * p2 = L2->next, * p3 = L3, * s;
	while (p1 != NULL && p2 != NULL) {
		s = (LinkNode*)malloc(sizeof(LinkNode));
		if (s != NULL) {
			if (p1->data < p2->data) {
				s->data = p1->data;
				p1 = p1->next;
			}
			else if (p1->data > p2->data) {
				s->data = p2->data;
				p2 = p2->next;
			}
			else {
				p1 = p1->next;  // or "p2 = p2->next"
				continue;
			}
			p3->next = s;
			p3 = s;
		}
	}

	LinkNode* p;
	if (p1 == NULL)
		p = p2;
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


void ListsIntersectedSet(LinkNode* L1, LinkNode* L2, LinkNode* L3) {  // Get the Intersection of two sets (stored in ascending order using a linked list)
	LinkNode* p1 = L1->next, * p2 = L2->next, * p3 = L3, * s, * q = L2->next;

	while (p1 != NULL) {
		while (p2 != NULL && p1->data != p2->data) {
			p2 = p2->next;
			if (p2 != NULL && p2->data > p1->data)
				break;
		}
		if (p2 != NULL) {
			if (p1->data == p2->data) {
				s = (LinkNode*)malloc(sizeof(LinkNode));
				if (s != NULL) {
					s->data = p1->data;
					p3->next = s;
					p3 = s;
					q = p2->next;
				}
			}
		}
		p2 = q;
		p1 = p1->next;
	}

	p3->next = NULL;
}


void ListsDifferentSet(LinkNode* L1, LinkNode* L2, LinkNode* L3) {  // Get the difference of two sets (stored in ascending order using a linked list)
	LinkNode* p1 = L1->next, * p2 = L2->next, * p3 = L3, * s, * q = L2->next;

	while (p1 != NULL) {
		while (p2 != NULL && p1->data != p2->data) {
			p2 = p2->next;
			if (p2 != NULL && p2->data > p1->data) {
				p2 = NULL;
			}
		}
		if (p2 == NULL) {
			s = (LinkNode*)malloc(sizeof(LinkNode));
			if (s != NULL) {
				s->data = p1->data;
				p3->next = s;
				p3 = s;
			}
		}
		else {  // In other words, there must be p1->data == p2->data at this point.
			q = p2->next;
		}
		p2 = q;
		p1 = p1->next;
	}

	p3->next = NULL;
}


int main() {
	LinkNode* L1 = InitList();
	ElemType a[] = { 2, 4, 5, 6, 7, 4, 1, 2, 8, 9 };
	int n = 10;
	CreateList(L1, a, n);  // create a normal linked list
	ListSort(L1);  // sort the linked list
	ListDistinct(L1);  // distinct the linked list to get a set
	DispList(L1);

	LinkNode* L2 = InitList();
	ElemType b[] = { 4, 5, 3, 6, 9, 8, 2 };
	n = 7;
	CreateList(L2, b, n);
	ListSort(L2);
	ListDistinct(L2);
	DispList(L2);

	printf("\n");

	printf("Get the union set of two sets >>>\n");
	LinkNode* L3 = InitList();
	ListsUnionSet(L1, L2, L3);
	DispList(L3);

	printf("\nGet the intersected set of two sets >>>\n");
	L3 = InitList();
	ListsIntersectedSet(L1, L2, L3);
	DispList(L3);

	printf("\nGet the different set of two sets >>>\n");
	L3 = InitList();
	ListsDifferentSet(L1, L2, L3);  // DifferentSet = Set(L1) - IntersectedSet
	DispList(L3);

	return 0;
}