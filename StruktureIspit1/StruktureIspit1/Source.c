#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ERROR (-1)
#define MAX_NAME_LEN (256)
#define MAX_FILE_NAME (256)

struct _student;
typedef struct _student* StudentP;
typedef struct _student {
	char firstName[MAX_NAME_LEN];
	char lastName[MAX_NAME_LEN];
	int Subject1;
	int Subject2;
	int Subject3;
	StudentP Next;
}student;

int CitaDat(StudentP p);
int Unos(StudentP p, char ln[], char fn[], int sub);
int Ispis(StudentP p);
int Brisi(StudentP p);

int main() {
	student Head1;
	Head1.Next = NULL;
	student Head2;
	Head2.Next = NULL;
	student Head3;
	Head3.Next = NULL;
	CitaDat(&Head1);
	CitaDat(&Head2);
	CitaDat(&Head3);
	Ispis(Head1.Next);
	Ispis(Head2.Next);
	Ispis(Head3.Next);
	Brisi(&Head1);
	Brisi(&Head2);
	Brisi(&Head3);
	return 0;
}

int CitaDat(StudentP p) {
	char datoteka[MAX_FILE_NAME] = { 0 };
	char ln[MAX_NAME_LEN] = { 0 };
	char fn[MAX_NAME_LEN] = { 0 };
	int sub = 0;
	printf("Unesite ime datoteke:\n");
	scanf("%s", datoteka);
	printf("\n");
	FILE* fp = NULL;
	fp = fopen(datoteka, "r");
	if (fp == NULL) {
		printf("Datoteka se nije otvorila!\n");
		return ERROR;
	}
	while (fscanf(fp, "%s %s %d", ln, fn, &sub) > 0) {
		Unos(p, ln, fn, sub);
	}
	fclose(fp);
	return 0;
}

int Unos(StudentP p, char ln[], char fn[], int sub) {
	StudentP q = NULL;
	q = (StudentP)malloc(sizeof(student));
	if (q == NULL) {
		printf("Neuspjesna alokacija memorije!");
		return ERROR;
	}
	strcpy(q->lastName, ln);
	strcpy(q->firstName, fn);
	q->Subject1 = sub;
	while (p->Next != NULL && strcmp(p->Next->lastName, ln) < 0) {
		p = p->Next;
	}
	q->Next = p->Next;
	p->Next = q;
	return 0;
}

int Ispis(StudentP p) {
	if (p == NULL) {
		printf("Prazna datoteka!\n");
	}
	while (p != NULL) {
		printf("- %s %s (%d)\n", p->lastName, p->firstName, p->Subject1);
		p = p->Next;
	}
	printf("\n");
	return 0;
}

int Brisi(StudentP p) {
	StudentP temp;
	while (p != NULL) {
		temp = p;
		p = p->Next;
		free(temp);
	}
	return 0;
}