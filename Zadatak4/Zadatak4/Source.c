#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ERROR (-1)
#define MAX_NAME (256)

typedef struct polinom* poz;
typedef struct polinom {
	int koef;
	int eks;
	poz next;
}polinom;

int UnosSort(poz p, int coef, int expo);
int CitaDat(poz p);
int Ispis(poz p);
int Zbroj(poz p1, poz p2);
int Umnozak(poz p1, poz p2);

int main() {
	polinom head1;
	polinom head2;
	head1.next = NULL;
	head2.next = NULL;
	CitaDat(&head1);
	CitaDat(&head2);
	printf("1. polinom:\n\n");
	Ispis(head1.next);
	printf("2. polinom:\n\n");
	Ispis(head2.next);
	Zbroj(&head1, &head2);
	Umnozak(&head1, &head2);
	return 0;
}

int CitaDat(poz p) {
	int k, e;
	char datoteka[MAX_NAME] = { 0 };
	printf("Unesi ime datoteke: ");
	scanf("%s", datoteka);
	printf("\n");
	FILE* fp = NULL;
	fp = fopen(datoteka, "r");
	if (fp == NULL) {
		printf("Datoteka %s se nije otvorila!", datoteka);
		return ERROR;
	}
	while (fscanf(fp, "%d %d", &k, &e) > 0) {
		UnosSort(p, k, e);
	}
	fclose(fp);
	return 0;
}

int UnosSort(poz p, int coef, int expo) {
	poz q = NULL;
	q = malloc(sizeof(polinom));
	if (q == NULL) {
		printf("Neuspjesna alokacija memorije!");
		return ERROR;
	}
	q->koef = coef;
	q->eks = expo;
	while (p->next != NULL && p->next->eks > expo) {
		p = p->next;
	}
	q->next = p->next;
	p->next = q;
	return 0;
}

int Ispis(poz p) {
	if (p == NULL) {
		printf("Prazna datoteka!");
	}
	else {
		while (p != NULL) {
			printf("%dX^%d", p->koef, p->eks);
			p = p->next;
			if (p != NULL) {
				printf(" + ");
			}
			else
				printf("\n");
		}
	}
	printf("\n");
	return 0;
}

int Zbroj(poz p1, poz p2) {
	poz q1 = p1;
	poz q2 = p2;
	poz p3 = NULL;
	while (q1 != NULL && q2 != NULL) {
		if (q1->eks == q2->eks) {
			UnosSort(p3, q1->koef + q2->koef, q1->eks);
			q1 = q1->next;
			q2 = q2->next;
		}
		else if (q1->eks > q2->eks) {
			UnosSort(p3, q1->koef, q1->eks);
			q1 = q1->next;
		}
		else if (q1->eks < q2->eks) {
			UnosSort(p3, q2->koef, q2->eks);
			q2 = q2->next;
		}
	}
	while (q1 != NULL) {
		UnosSort(p3, q1->koef, q1->eks);
		q1 = q1->next;
	}
	while (q2 != NULL) {
		UnosSort(p3, q2->koef, q2->eks);
		q2 = q2->next;
	}
	printf("Zbroj polinoma:\n\n");
	Ispis(p3);
	return 0;
}

int Umnozak(poz p1, poz p2) {
	poz q1 = p1;
	poz q2 = p2;
	poz p4 = NULL;
	if (p1 == NULL || p2 == NULL) {
		printf("Nema mnozenja!\n");
		return;
	}
	while (q1 != NULL) {
		while (q2 != NULL) {
			UnosSort(p4, q1->koef * q2->koef, q1->eks + q2->eks);
			q2 = q2->next;
		}
		q1 = q1->next;
	}
	printf("Umnozak polinoma:\n\n");
	Ispis(p4);
	return 0;
}