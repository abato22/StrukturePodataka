#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ERROR (-1)
#define MAX_NAME_LEN (32)
#define MAX_FILE_NAME (64)

struct _date;
typedef struct _date* DateP;
typedef struct _date {
	int year;
	int month;
	int day;
}Date;

struct _hotel;
typedef struct _hotel* HotelP;
typedef struct _hotel {
	char name[MAX_NAME_LEN];
	DateP date;
	int income;
	HotelP next;
}Hotel;

int CitaDat(HotelP p);
int Unos(HotelP p, char ime[], int god, int mis, int dan, int prihod);
int Ispis(HotelP p);
int Brisi(HotelP p);
int DateCmp(DateP d1, DateP d2);
int Pros(HotelP p);
int UnosPros(HotelP p, int avg);

int main() {
	Hotel Head;
	Head.next = NULL;
	CitaDat(&Head);
	Ispis(Head.next);
	printf("Prosjek: %d\n\n", Pros(&Head));
	//UnosPros(&Head, Pros(&Head));
	//Ispis(Head.next);
	Brisi(&Head);
	return 0;
}

int CitaDat(HotelP p) {
	char datoteka[MAX_FILE_NAME] = { 0 };
	char ime[MAX_NAME_LEN] = { 0 };
	int god = 0;
	int mis = 0;
	int dan = 0;
	int prihod = 0;
	printf("Unesite ime datoteke:\n");
	scanf("%s", datoteka);
	printf("\n");
	FILE* fp = NULL;
	fp = fopen(datoteka, "r");
	if (fp == NULL) {
		printf("Datoteka se nije otvorila!\n");
		return ERROR;
	}
	while (fscanf(fp, "%s %d %d %d %d", ime, &god, &mis, &dan, &prihod) > 0) {
		Unos(p, ime, god, mis, dan, prihod);
	}
	fclose(fp);
	return 0;
}

int Unos(HotelP p, char ime[], int god, int mis, int dan, int prihod) {
	HotelP q = NULL;
	q = (HotelP)malloc(sizeof(Hotel));
	DateP qq = NULL;
	qq = (DateP)malloc(sizeof(Date));
	if (q == NULL) {
		printf("Neuspjesna alokacija memorije!");
		return ERROR;
	}
	if (qq == NULL) {
		printf("Neuspjesna alokacija memorije!");
		return ERROR;
	}
	strcpy(q->name, ime);
	q->date = qq;
	qq->year = god;
	qq->month = mis;
	qq->day = dan;
	q->income = prihod;
	while (p->next != NULL && DateCmp(p->next->date, q->date) < 0) {
		p = p->next;
	}
	q->next = p->next;
	p->next = q;
	return 0;
}

int Ispis(HotelP p) {
	if (p == NULL) {
		printf("Prazna datoteka!\n");
	}
	while (p != NULL) {
		printf("%s %d%d%d %d\n", p->name, p->date->year, p->date->month, p->date->day, p->income);
		p = p->next;
	}
	printf("\n");
	return 0;
}

int Brisi(HotelP p) {
	HotelP temp;
	while (p->next != NULL) {
		temp = p->next;
		p->next = temp->next;
		free(temp);
	}
	return 0;
}

int DateCmp(DateP d1, DateP d2) {
	int rez;
	rez = d1->year - d2->year;
	if (rez == 0) {
		rez = d1->month - d2->month;
		if (rez == 0) {
			rez = d1->day - d2->day;
		}
	}
	return rez;
}

int Pros(HotelP p) {
	int res = 0;
	while (p->next != NULL) {
		res = res + p->next->income;
		p = p->next;
	}
	return res / 20;
}

int UnosPros(HotelP p, int avg) {
	HotelP temp = NULL;
	temp = (HotelP)malloc(sizeof(Hotel));
	HotelP qqq = NULL;
	qqq = (HotelP)malloc(sizeof(Hotel));
	if (qqq == NULL) {
		printf("Neuspjesna alokacija memorije!");
		return ERROR;
	}
	if (temp == NULL) {
		printf("Neuspjesna alokacija memorije!");
		return ERROR;
	}
	while (p->next != NULL) {
		p = p->next;
	}
	temp = p;
	//free(p);
	while (temp->next != NULL && temp->next->income < avg) {
		qqq->next = temp->next;
		temp->next = qqq;
	}
	//qqq->next = temp->next;
	//temp->next = qqq;
	return 0;
}