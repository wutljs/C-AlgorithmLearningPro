#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

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


void ListPolynomialAdd(LinkNode* L1, LinkNode* L2, LinkNode* L3) {
	/*
	The terms in a polynomial need to be sorted in ascending order of the degree of x in the terms.
	If a certain power term of x does not exist in the polynomial,
	its number of terms needs to be treated as 0 to add this term to this polynomial.

	In the comments below,
	'P' represents the original polynomial,
	'M' represents a polynomial arranged in ascending order,
	'L' represents the single linked list corresponding to the sorted polynomial.

	EX1:
	P = 3x^2 + 4 + 7x + 5x^8 + x^10  -->  M = 4 + 7x + 3x^2 + 5x^8 + x^10

	EX2:
	M1 = 1 + 2x + 3x^2 + 7x^3  -->  L1 : 1 2 3 7
	M2 = x^2 + 3x^4 + 4x^6  -->  L2 : 0 0 1 0 3 0 4
	*/

	LinkNode* p1 = L1->next, * p2 = L2->next, * p3 = L3, * s;

	while (p1 != NULL && p2 != NULL) {
		s = (LinkNode*)malloc(sizeof(LinkNode));
		if (s != NULL) {
			s->data = p1->data + p2->data;
			p3->next = s;
			p3 = s;
			p1 = p1->next;
			p2 = p2->next;
		}
	}

	LinkNode* p;
	if (p1 == NULL && p2 == NULL) {
		p = p1;  // or p = p2
	}
	else {
		if (p1 == NULL)
			p = p2;
		else
			p = p1;
	}

	while (p != NULL) {
		s = (LinkNode*)malloc(sizeof(LinkNode));
		if (s != NULL) {
			s->data = p->data;
			p3->next = s;
			p3 = s;
			p = p->next;
		}
	}

	p3->next = s = NULL;
}


void ListPolynomialMultiply(LinkNode* L1, LinkNode* L2, LinkNode* L3) {
	// The number of 'x' can be increased by inserting items with data of 0 using the head insertion method.

}


int main() {
	LinkNode* L1 = InitList();
	LinkNode* L2 = InitList();

	ElemType a[] = { 0, 0, -3, 4, 5, 6 }, b[] = { 0, 0, 1, 2, 3, 7 };
	int n = 6, m = 6;

	CreateList(L1, a, n);
	CreateList(L2, b, m);
	printf("\nCreateList : \n");
	DispList(L1);
	DispList(L2);
	printf("\n");

	LinkNode* L3 = InitList();
	ListPolynomialAdd(L1, L2, L3);
	printf("\nListPolynomialAdd : \n");
	DispList(L3);

	return 0;
}