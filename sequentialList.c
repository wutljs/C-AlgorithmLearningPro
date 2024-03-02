#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxSize 50


typedef char ElemType;

typedef struct
{
	ElemType data[MaxSize];
	int length;

}SqList;


SqList* InitList()
{
	return ((SqList*)malloc(sizeof(SqList)));
}


void CreateList(SqList* L, ElemType a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		L->data[i] = a[i];
	}

	L->length = n;
}


void DestroyList(SqList* L)
{
	free(L);
}


void DispList(SqList* L)
{
	printf("SqList:\n>>> ");

	for (int i = 0; i < L->length; i++)
	{
		printf("%c ", L->data[i]);
	}

	printf("\n");
}


void ListLength(SqList* L)
{
	printf("\nThe length of the SqList is %d.\n", L->length);
}


bool ListEmpty(SqList* L)
{
	return (L->length == 0);
}


bool GetElem(SqList* L, int index, ElemType* e)
{
	if (index < 1 || index > L->length)
	{
		return false;

	}
	else
	{
		index--;
		*e = L->data[index];
		return true;

	}
}


int LocateElem(SqList* L, ElemType e)
{
	for (int i = 0; i < L->length; i++) {
		if (L->data[i] == e) {
			return i + 1;
		}
	}

	return 0;
}


bool ListInsert(SqList* L, int location, ElemType e)
{
	if (location < 1 || location > L->length + 1) {
		return false;

	}
	else {
		location--;

		for (int i = L->length; i > location; i--) {
			L->data[i] = L->data[i - 1];
		}

		L->data[location] = e;
		L->length++;

		return true;
	}
}


bool ListDelete(SqList* L, int index, ElemType* e)
{
	if (index < 1 || index > L->length) {
		return false;

	}
	else {
		index--;
		*e = L->data[index];

		for (int i = index; i < L->length - 1; i++) {
			L->data[i] = L->data[i + 1];
		}

		L->length--;

		return true;
	}

}


int main()
{

	return 0;
}
