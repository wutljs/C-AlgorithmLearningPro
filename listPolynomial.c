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
			printf("%.2f%c", p->coefficient, c);
		else
			printf("%.2fx^%.2f%c", p->coefficient, p->exponential, c);
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
void PolynomialListAdd(PolynomialLinkNode* L1, PolynomialLinkNode* L2, PolynomialLinkNode* L3) {

}


int main() {
	PolynomialLinkNode* L = InitList();  // create a polynomial list
	ElemType coefficient[] = { 1, 2, 1, 4 };
	ElemType exponential[] = { 2, 1, 0, 5 };
	int n = 4;
	CreateList(L, coefficient, exponential, n);
	DispList(L);

	if (ListSort(L)) {  // sort the list to do something
		DispList(L);
	}

	DestroyList(L);

	return 0;
}