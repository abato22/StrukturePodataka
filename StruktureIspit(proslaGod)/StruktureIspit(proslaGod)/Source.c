#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_ID_LEN (8)
#define MAX_NAME_LEN (64)
#define MAX_FILE_NAME (64)
#define ERROR (-1)

struct _date;
typedef struct _date* DateP;
typedef struct _date {
	int year;
	int month;
	int day;
}Date;

struct _vehicle;
typedef struct _vehicle* VehicleP;
typedef struct _vehicle {
	char brandName[MAX_NAME_LEN];
	char modelName[MAX_NAME_LEN];
	DateP date;
	VehicleP next;
}Vehicle;

struct _person;
typedef struct _person* PersonP;
typedef struct _person {
	char id[MAX_ID_LEN];
	char firstName[MAX_NAME_LEN];
	char lastName[MAX_NAME_LEN];
	PersonP next;
	VehicleP child;
}Person;

int CitaDat(PersonP p);
int Unos(PersonP p, char ID[], char ime[], char prez[]);
int Ispis(PersonP p);
int Brisi(PersonP p);
int CitaDat2(VehicleP p);
int Unos2(VehicleP p, char ID[], char brand[], char model[], int god, int mis, int dan);

int main() {
	Person head1;
	head1.next = NULL;
	Vehicle head2;
	head2.next = NULL;
	CitaDat(&head1);
	Ispis(head1.next);
	CitaDat2(&head2);
	Brisi(&head1);
	return 0;
}

int CitaDat(PersonP p) {
	char datoteka[MAX_FILE_NAME] = { 0 };
	char ID[MAX_ID_LEN] = { 0 };
	char ime[MAX_NAME_LEN] = { 0 };
	char prez[MAX_NAME_LEN] = { 0 };
	printf("Unesite ime datoteke:\n");
	scanf("%s", datoteka);
	printf("\n");
	FILE* fp = NULL;
	fp = fopen(datoteka, "r");
	if (fp == NULL) {
		printf("Datoteka se nije otvorila!\n");
		return ERROR;
	}
	while (fscanf(fp, "%s %s %s", ID, ime, prez) > 0) {
		Unos(p, ID, ime, prez);
	}
	fclose(fp);
	return 0;
}

int Unos(PersonP p, char ID[], char ime[], char prez[]) {
	PersonP q = NULL;
	q = (PersonP)malloc(sizeof(Person));
	if (q == NULL) {
		printf("Neuspjela alokacija memorije!\n");
		return ERROR;
	}
	strcpy(q->id, ID);
	strcpy(q->lastName, prez);
	strcpy(q->firstName, ime);
	while (p->next != NULL && strcmp(p->next->firstName, ime) < 0) {
		p = p->next;
	}
	q->next = p->next;
	p->next = q;
	return 0;
}

int Ispis(PersonP p) {
	while (p != NULL) {
		printf("%s %s %s\n", p->id, p->firstName, p->lastName);
		p = p->next;
	}
	printf("\n");
	return 0;
}

int Brisi(PersonP p) {
	PersonP temp;
	while (p->next != NULL) {
		temp = p->next;
		p->next = temp->next;
		free(temp);
	}
	return 0;
}

int CitaDat2(VehicleP p) {
	char datoteka[MAX_FILE_NAME] = { 0 };
	char ID[MAX_ID_LEN] = { 0 };
	char brand[MAX_NAME_LEN] = { 0 };
	char model[MAX_NAME_LEN] = { 0 };
	int god, mis, dan;
	printf("Unesite ime datoteke:\n");
	scanf("%s", datoteka);
	printf("\n");
	FILE* fp = NULL;
	fp = fopen(datoteka, "r");
	if (fp == NULL) {
		printf("Datoteka se nije otvorila!\n");
		return ERROR;
	}
	while (fscanf(fp, "%s %s %s %d %d %d", ID, brand, model, god, mis, dan) > 0) {
		Unos2(p, ID, brand, model, god, mis, dan);
	}
	fclose(fp);
	return 0;
}

int Unos2(VehicleP p, char ID[], char brand[], char model[], int god, int mis, int dan) {
	VehicleP q = NULL;
	q = (VehicleP)malloc(sizeof(Vehicle));
	PersonP qq = NULL;
	qq = (PersonP)malloc(sizeof(Person));
	DateP qqq = NULL;
	qqq = (DateP)malloc(sizeof(Date));
	if (q == NULL) {
		printf("Neuspjela alokacija memorije!\n");
		return ERROR;
	}
	if (qq == NULL) {
		printf("Neuspjela alokacija memorije!\n");
		return ERROR;
	}
	if (qqq== NULL) {
		printf("Neuspjela alokacija memorije!\n");
		return ERROR;
	}
	q->date = qqq;
	strcpy(qq->id, ID);
	strcpy(q->brandName, brand);
	strcpy(q->modelName, model);
	qqq->year = god;
	qqq->month = mis;
	qqq->day = dan;
	while (p->next != NULL && qq->id) {
		p = p->next;
	}
	q->next = p->next;
	p->next = q;
	return 0;
}