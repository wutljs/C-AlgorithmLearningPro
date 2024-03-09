#define _CRT_SECURE_NO_WARNINGS 1


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


typedef double ElemType;

typedef struct PLNode {
	ElemType coefficient;
	ElemType exponential;
	struct PLNode* next;
}PolynomialLinkNode;


PolynomialLinkNode* InitList() {
	PolynomialLinkNode* L = (PolynomialLinkNode*)malloc(sizeof(PolynomialLinkNode));
	if (L != NULL) {
		L->next = NULL;
	}
	return L;
}


void CreateList(PolynomialLinkNode* L, ElemType coefficient[], ElemType exponential[], int n) {
	PolynomialLinkNode* p = L, * s;
	for (int i = 0; i < n; i++) {
		s = (PolynomialLinkNode*)malloc(sizeof(PolynomialLinkNode));
		if (s != NULL) {
			s->coefficient = coefficient[i];
			s->exponential = exponential[i];
			p->next = s;
			p = s;
		}
	}
	p->next = NULL;
}


void DispList(PolynomialLinkNode* L) {
	PolynomialLinkNode* p = L->next;
	char c = '+';
	printf("\nPolynomialList >>> ");
	while (p != NULL) {
		if (p->exponential == 0)
			printf("(%.2f)%c", p->coefficient, c);
		else
			printf("(%.2fx^%.2f)%c", p->coefficient, p->exponential, c);
		if (p->next != NULL && p->next->next == NULL) {
			c = '\0';
		}
		p = p->next;
	}
	printf("\n");
}


void DestroyList(PolynomialLinkNode* L) {
	PolynomialLinkNode* pre = L, * p = pre->next;
	while (p != NULL) {
		free(pre);
		pre = p;
		p = p->next;
	}
	free(pre);
}


// Sort the PolynomialList in descending order of the exponent size of the unknown number x.
bool ListSort(PolynomialLinkNode* L) {
	if (L->next != NULL && L->next->next != NULL) {
		PolynomialLinkNode* p = L->next->next, * pre, * q;
		L->next->next = NULL;
		while (p != NULL) {
			pre = L;
			q = p->next;
			while (pre->next != NULL && pre->next->exponential > p->exponential) {
				pre = pre->next;
			}
			p->next = pre->next;
			pre->next = p;
			p = q;
		}
		return true;
	}
	else
		return false;
}


// Attention!The PolynomialList involved in the first two nodes of this function's formalparameters should be sorted in descending order of the exponential size ofthe unknown number x.If not, please call the ListSort function to process the PolynomialList before using this function.
PolynomialLinkNode* PolynomialListAdd(PolynomialLinkNode* L1, PolynomialLinkNode* L2) {
	PolynomialLinkNode* p1 = L1->next, * p2 = L2->next;
	PolynomialLinkNode* L3 = InitList(), * p3 = L3;
	PolynomialLinkNode* s, * p = NULL;
	double n, m;

	while (p1 != NULL && p2 != NULL) {
		s = (PolynomialLinkNode*)malloc(sizeof(PolynomialLinkNode));
		if (s != NULL) {
			n = p1->exponential, m = p2->exponential;
			if (n > m) {
				p = p1;
				p1 = p1->next;
			}
			else if (n < m) {
				p = p2;
				p2 = p2->next;
			}
			else {
				p = NULL;
				s->coefficient = p1->coefficient + p2->coefficient;
				s->exponential = n;  // or s->exponential = m
				p1 = p1->next;
				p2 = p2->next;
			}
			if (p != NULL) {
				s->coefficient = p->coefficient;
				s->exponential = p->exponential;
			}
			p3->next = s;
			p3 = s;
		}
	}

	if (p1 == NULL && p2 == NULL)
		p = NULL;
	else
		p = (p1 == NULL) ? p2 : p1;

	while (p != NULL) {
		s = (PolynomialLinkNode*)malloc(sizeof(PolynomialLinkNode));
		if (s != NULL) {
			s->coefficient = p->coefficient;
			s->exponential = p->exponential;
			p3->next = s;
			p3 = s;
			p = p->next;
		}
	}

	p3->next = s = NULL;

	return L3;
}


// The precautions for using this function are the same as PolynomialListAdd.
PolynomialLinkNode* PolynomialListMultiply(PolynomialLinkNode* L1, PolynomialLinkNode* L2) {
	PolynomialLinkNode* p1 = L1->next, * p2 = L2->next;
	PolynomialLinkNode* L3 = InitList(), * p3 = L3, * s;  // L4 is a PolynomialList which is ready for temporary storage.
	PolynomialLinkNode* L4 = InitList();  // 

	while (p1 != NULL) {
		while (p2 != NULL) {
			s = (PolynomialLinkNode*)malloc(sizeof(PolynomialLinkNode));
			if (s != NULL) {
				s->coefficient = p1->coefficient * p2->coefficient;
				s->exponential = p1->exponential + p2->exponential;
				p3->next = s;
				p3 = s;
			}
			p2 = p2->next;
		}
		p3->next = NULL;

		L4 = PolynomialListAdd(L3, L4);

		p1 = p1->next;
		p2 = L2->next;
		free(L3);
		L3 = InitList();
		p3 = L3;
	}

	return L4;
}


int main() {
	PolynomialLinkNode* L1 = InitList();  // create a polynomial list
	ElemType coefficient[] = { 2, 3, 4, 5 };
	ElemType exponential[] = { 0, 2, 3, 1 };
	int n = 4;
	CreateList(L1, coefficient, exponential, n);
	if (ListSort(L1)) {  // sort the list to do something
		printf("\nListSort L1");
		DispList(L1);
	}

	printf("\n");

	PolynomialLinkNode* L2 = InitList();  // create a polynomial list
	ElemType coefficient_[] = { 2, 1, 3, 4 };
	ElemType exponential_[] = { 2, 3, 1, 0 };
	n = 4;
	CreateList(L2, coefficient_, exponential_, n);
	if (ListSort(L2)) {  // sort the list to do something
		printf("\nListSort L2");
		DispList(L2);
	}

	PolynomialLinkNode* L3 = PolynomialListAdd(L1, L2);
	printf("\nL1 + L2");
	DispList(L3);

	PolynomialLinkNode* L4 = PolynomialListMultiply(L2, L1);
	printf("\nL1 * L2");
	DispList(L4);

	DestroyList(L1);
	DestroyList(L2);
	DestroyList(L3);

	return 0;
}