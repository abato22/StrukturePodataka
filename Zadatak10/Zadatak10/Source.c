#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX (256)
#define ERROR (-1)

struct grad;
typedef struct grad* pozg;
typedef struct grad {
	char imeg[MAX];
	int brstan;
	pozg left;
	pozg right;
}grad;

struct drzava;
typedef struct drzava* pozd;
typedef struct drzava {
	char imed[MAX];
	pozd next;
	pozg root;
}drzava;

int CitaDatDrzave(pozd p);
int UnosSortDrzave(pozd p, char named[]);
int IspisDrzave(pozd p);
pozg UnosGradovi(pozg p, char nameg[], int stan);
int CitaDatGradovi(pozd p, char namef[]);
pozg IspisGradovi(pozg p);

int main()
{
	drzava Head;
	Head.next = NULL;
	Head.root = NULL;
	CitaDatDrzave(&Head);
	IspisDrzave(Head.next);
	return 0;
}

int CitaDatDrzave(pozd p) {
	char named[MAX];
	char filename[MAX];
	FILE* fp = NULL;
	fp = fopen("drzave.txt", "r");
	if (fp == NULL) {
		printf("Datoteka se nije otvorila!\n");
		return ERROR;
	}
	while (fscanf(fp, "%s %s", named, filename) > 0) {
		UnosSortDrzave(p, named);
		CitaDatGradovi(p->next, filename);
	}
	fclose(fp);
	return 0;
}

int UnosSortDrzave(pozd p, char named[]) {
	pozd q = NULL;
	q = (pozd)malloc(sizeof(drzava));
	if (q == NULL) {
		printf("Neuspjesna alokacija memorije!");
		return ERROR;
	}
	strcpy(q->imed, named);
	while (p->next != NULL && strcmp(p->next->imed, named) < 0) {
		p = p->next;
	}
	p->root = NULL;
	q->next = p->next;
	p->next = q;
	return 0;
}

int IspisDrzave(pozd p) {
	if (p == NULL) {
		printf("Prazna datoteka!");
	}
	else {
		while (p != NULL) {
			printf("*******%s*******\n\n", p->imed);
			IspisGradovi(p->root);
			printf("\n");
			p = p->next;
		}
	}
	printf("\n");
	return 0;
}

int CitaDatGradovi(pozd p, char namef[]) {
	char nameg[MAX];
	int stan = 0;
	p->root = NULL;
	FILE* fp = NULL;
	fp = fopen(namef, "r");
	if (fp == NULL) {
		printf("Datoteka se nije otvorila!\n");
		return ERROR;
	}
	while (fscanf(fp, "%s %d", nameg, &stan) > 0) {
		p->root = UnosGradovi(p->root, nameg, stan);
	}
	fclose(fp);
	return 0;
}

pozg UnosGradovi(pozg p, char nameg[], int stan) {
	pozg q = NULL;
	q = (pozg)malloc(sizeof(grad));
	if (q == NULL) {
		printf("\nNeuspjesna alokacija memorije!");
		return NULL;
	}
	strcpy(q->imeg, nameg);
	q->brstan = stan;
	if (p == NULL) {
		p = q;
		p->left = NULL;
		p->right = NULL;
		return p;
	}
	if (p->brstan < q->brstan) {
		p->right = UnosGradovi(p->right, nameg, stan);
	}
	else if (p->brstan > q->brstan) {
		p->left = UnosGradovi(p->left, nameg, stan);
	}
	else {
		free(q);
	}
	return p;
}

pozg IspisGradovi(pozg p) {
	if (p == NULL) {
		return NULL;
	}
	else {
		IspisGradovi(p->left);
		printf("%s %d\n", p->imeg, p->brstan);
		IspisGradovi(p->right);
		return p;
	}
}