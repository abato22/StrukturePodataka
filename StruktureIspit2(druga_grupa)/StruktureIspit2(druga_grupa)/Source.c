#define _CRT_SECURE_NO_WARNINGS
#define MAX_FILE_NAME (32)
#define MAX_NAME_LEN (32)
#define ERROR (-1)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

struct _proizvod;
typedef struct _proizvod* ProizvodP;
typedef struct _proizvod {
	char proizvodIme[MAX_NAME_LEN];
	char kategorija[MAX_NAME_LEN];
	int cijena;
	ProizvodP next;
}Proizvod;

struct _kategorija;
typedef struct _kategorija* KategorijaP;
typedef struct _kategorija {
	char imeKategorije[MAX_NAME_LEN];
	int minCijena;
	int maxCijena;
	float avgCijena;
	KategorijaP next;
	ProizvodP child;
}Kategorija;

int Citadat1(KategorijaP p);
int Unos1(KategorijaP p, char ime[], int min, int max);
int Ispis(KategorijaP p);
int Brisi(KategorijaP p);
int Citadat2(KategorijaP p);
int Unos2(KategorijaP p, char ime[], char vrsta[]);

int main() {
	Kategorija head;
	head.next = NULL;
	Citadat1(&head);
	Ispis(head.next);
	Citadat2(&head);
	Ispis(head.next);
	Brisi(&head);
	return 0;
}

int Citadat1(KategorijaP p) {
	char datoteka[MAX_FILE_NAME] = { 0 };
	char ime[MAX_NAME_LEN] = { 0 };
	int min = 0;
	int max = 0;
	printf("Unesite ime datoteke:\n");
	scanf("%s", datoteka);
	printf("\n");
	FILE* fp = NULL;
	fp = fopen(datoteka, "r");
	if (fp == NULL) {
		printf("Datoteka se nije otvorila!\n");
		return ERROR;
	}
	while (fscanf(fp, "%s %d %d", ime, &min, &max) > 0) {
		Unos1(p, ime, min, max);
	}
	fclose(fp);
	return 0;
}

int Unos1(KategorijaP p, char ime[], int min, int max) {
	KategorijaP q = NULL;
	q = (KategorijaP)malloc(sizeof(Kategorija));
	if (q == NULL) {
		printf("Neuspjela alokacija memorije!\n");
		return ERROR;
	}
	strcpy(q->imeKategorije, ime);
	q->minCijena = min;
	q->maxCijena = max;
	q->child = NULL;
	while (p->next != NULL && strcmp(p->next->imeKategorije, q->imeKategorije) < 0) {
		p = p->next;
	}
	q->next = p->next;
	p->next = q;
	return 0;
}

int Ispis(KategorijaP p) {
	if (p == NULL) {
		printf("Prazna datoteka!\n");
	}
	while (p != NULL) {
		printf("%s %d %d", p->imeKategorije, p->minCijena, p->maxCijena);
		ProizvodP temp = p->child;
		while (temp != NULL) {
			printf("\n\t - %s %d", temp->proizvodIme, temp->cijena);
			temp = temp->next;
		}
		printf("\n");
		p = p->next;
	}
	printf("\n");
	return 0;
}

int Brisi(KategorijaP p) {
	KategorijaP temp;
	while (p->next != NULL) {
		temp = p->next;
		p->next = temp->next;
		free(temp);
	}
	return 0;
}

int Citadat2(KategorijaP p) {
	char datoteka[MAX_FILE_NAME] = { 0 };
	char ime[MAX_NAME_LEN] = { 0 };
	char vrsta[MAX_NAME_LEN] = { 0 };
	printf("Unesite ime datoteke:\n");
	scanf("%s", datoteka);
	printf("\n");
	FILE* fp = NULL;
	fp = fopen(datoteka, "r");
	if (fp == NULL) {
		printf("Datoteka se nije otvorila!\n");
		return ERROR;
	}
	while (fscanf(fp, "%s %s", ime, vrsta) > 0) {
		Unos2(p->next, ime, vrsta);
	}
	fclose(fp);
	return 0;
}

int Unos2(KategorijaP p, char ime[], char vrsta[]) {
	ProizvodP q = NULL;
	q = (ProizvodP)malloc(sizeof(Proizvod));
	if (q == NULL) {
		printf("Neuspjela alokacija memorije!\n");
		return ERROR;
	}
	strcpy(q->proizvodIme, ime);
	strcpy(q->kategorija, vrsta);
	while (p != NULL) {
		if (strcmp(p->imeKategorije, q->kategorija) == 0) {
			break;
		}
		p = p->next;
	}
	q->next = p->child;
	p->child = q;
	q->cijena = rand() % (p->maxCijena - p->minCijena + 1) + p->minCijena;
	return 0;
}
