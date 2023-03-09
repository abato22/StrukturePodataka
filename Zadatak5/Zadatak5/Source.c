#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ERROR (-1)
#define MAX_NAME (256)
#define MAX_LINE (1024)

typedef struct postfix* poz;
typedef struct postfix {
	int broj;
	poz next;
}postfix;

int CitaDat(poz p);
int Push(poz p, int el);
int Pop(poz p);

int main() {
	postfix head;
	head.next = NULL;
	CitaDat(&head);
	return 0;
}

int CitaDat(poz p) {
	int num, a, b, rez;
	char buffer[MAX_LINE] = { 0 };
	char datoteka[MAX_NAME] = { 0 };
	printf("Unesi ime datoteke: ");
	scanf("%s", datoteka);
	printf("\n");
	FILE* fp = NULL;
	fp = fopen(datoteka, "r");
	if (fp == NULL) {
		printf("Datoteka %s se nije otvorila!\n", datoteka);
		return ERROR;
	}
	while (fgets(buffer, MAX_LINE, fp) != NULL) {
		if (sscanf(buffer, "%d", &num) > 0) {
			Push(p, num);
		}
		else {
			a = Pop(p);
			b = Pop(p);
			switch (num) {
			case'+':
				rez = b + a;
				Push(p, rez);
				break;
			case'-':
				rez = b - a;
				Push(p, rez);
				break;
			case'*':
				rez = b * a;
				Push(p, rez);
				break;
			case'/':
				rez = b / a;
				Push(p, rez);
				break;
			default:
				printf("Nepoznat operator!\n");
			}
		}
	}
	if (p != NULL && p->next == NULL)
		printf("Rezultat: %d\n", p->broj);
	fclose(fp);
	return 0;
}

int Push(poz p, int el) {
	poz q = NULL;
	q = (poz)malloc(sizeof(postfix));
	if (q == NULL) {
		printf("Neuspjesna alokacija memorije!\n");
		return ERROR;
	}
	if (p == NULL) {
		q->broj = el;
		q->next = NULL;
		p = q;
	}
	else{
	q->broj = el;
	q->next = p->next;
	p->next = q;
	}
	return 0;
}

int Pop(poz p) {
	int data;
	poz temp;
	if (p == NULL) {
		printf("Stog je prazan!\n");
		return ERROR;
	}
	data = p->broj;
	temp = p;
	p = p->next;
	free(temp);
	return data;
}