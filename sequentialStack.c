#define _CRT_SECURE_NO_WARNINGS 1
#define MaxSize 20

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef int ElemType;
typedef struct {
	ElemType data[MaxSize];
	int top;
}SqStack;


SqStack* InitStack() {
	SqStack* s = (SqStack*)malloc(sizeof(SqStack));
	if (s != NULL) {
		s->top = -1;
	}

	return s;
}


void DestroyStack(SqStack* s) {
	free(s);
}


bool StackEmpty(SqStack* s) {
	return (s->top == -1);
}


bool Push(SqStack* s, ElemType e) {
	if (s->top == MaxSize - 1)
		return false;
	s->top++;
	s->data[s->top] = e;
	return true;
}


bool Pop(SqStack* s, ElemType* e) {
	if (s->top == -1)
		return false;
	*e = s->data[s->top];
	s->top--;
	return true;
}


bool GetTop(SqStack* s, ElemType* e) {
	if (s->top == -1)
		return false;
	*e = s->data[s->top];
	return true;
}


bool symmetry(char str[]) {
	SqStack* s = InitStack();
	int strLen = strlen(str);

	for (int i = 0; i < strLen; i++) {
		Push(s, str[i]);
	}

	ElemType e;
	for (int i = 0; i < strLen; i++) {
		Pop(s, &e);
		if (e != str[i])
			return false;
	}

	return true;
}


int main() {

	return 0;
}
