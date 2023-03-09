#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ERROR (-1)
#define MAX_ID_LENGTH (64)
#define MAX_NAME_LENGTH (64)
#define MAX_FILE_NAME (64)

struct _visit;
typedef struct _visit* VisitP;
typedef struct _visit {
    char userId[MAX_ID_LENGTH];
    int year;
    int month;
    int day;
    VisitP next;
}Visit;

struct _membership;
typedef struct _membership* MembershipP;
typedef struct _membership {
    char userId[MAX_ID_LENGTH];
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    int month;
    int year;
    int price;
    VisitP visits;
    MembershipP next;
}Membership;

int CitaDat1(MembershipP p);
int Unos(MembershipP p, char id[], char ime[], char prez[], int mis, int god, int cij);
int Ispis(MembershipP p);
int Brisi(MembershipP p);
int DateCmp(int year1, int year2, int month1, int month2);
int CitaDat2(MembershipP p);
int Unos2(MembershipP p, char id[], int dan, int mis, int god);

int main() {
    Membership Head;
    Head.next = NULL;
    CitaDat1(&Head);
    Ispis(Head.next);
    CitaDat2(&Head);
    Ispis(Head.next);
    Brisi(&Head);
    return 0;
}

int CitaDat1(MembershipP p) {
    char datoteka[MAX_FILE_NAME] = { 0 };
    char id[MAX_ID_LENGTH] = { 0 };
    char ime[MAX_NAME_LENGTH] = { 0 };
    char prez[MAX_NAME_LENGTH] = { 0 };
    int god = 0;
    int mis = 0;
    int cij = 0;
    printf("Unesite ime datoteke:\n");
    scanf("%s", datoteka);
    FILE* fp = NULL;
    fp = fopen(datoteka, "r");
    if (fp == NULL) {
        printf("Datoteka se nije otvorila!\n");
        return ERROR;
    }
    while (fscanf(fp, "%s %s %s %d-%d %d", id, ime, prez, &mis, &god, &cij) > 0) {
        Unos(p, id, ime, prez, mis, god, cij);
    }
    fclose(fp);
    return 0;
}

int Unos(MembershipP p, char id[], char ime[], char prez[], int mis, int god, int cij) {
    MembershipP q = NULL;
    q = (MembershipP)malloc(sizeof(Membership));
    if (q == NULL) {
        printf("Neuspjesna alokacija memorije!");
        return ERROR;
    }
    strcpy(q->userId, id);
    strcpy(q->firstName, ime);
    strcpy(q->lastName, prez);
    q->month = mis;
    q->year = god;
    q->price = cij;
    q->visits = NULL;
    while (p->next != NULL && DateCmp(p->next->year, q->year, p->next->month, q->month) < 0) {
        p = p->next;
    }
    q->next = p->next;
    p->next = q;
    return 0;
}

int Ispis(MembershipP p) {
    if (p == NULL) {
        printf("Prazna datoteka!\n");
    }
    while (p != NULL) {
        printf("\n%s %s %s %d-%d %d", p->userId, p->firstName, p->lastName, p->month, p->year, p->price);

        VisitP temp = p->visits;
        while (temp != NULL) {
            printf("\n\t - %d-%d-%d", temp->day, temp->month, temp->year);
            temp = temp->next;
        }
        p = p->next;
    }
    printf("\n");
    return 0;
}

int Brisi(MembershipP p) {
    MembershipP temp;
    while (p->next != NULL) {
        temp = p->next;
        p->next = temp->next;
        free(temp);
    }
    return 0;
}

int DateCmp(int year1, int year2, int month1, int month2) {
    int rez;
    rez = year1 - year2;
    if (rez == 0) {
        rez = month1 - month2;
    }
    return rez;
}

int CitaDat2(MembershipP p) {
    char datoteka[MAX_FILE_NAME] = { 0 };
    char id[MAX_ID_LENGTH] = { 0 };
    int god = 0;
    int mis = 0;
    int dan = 0;
    printf("\nUnesite ime datoteke:\n");
    scanf("%s", datoteka);
    FILE* fp = NULL;
    fp = fopen(datoteka, "r");
    if (fp == NULL) {
        printf("Datoteka se nije otvorila!\n");
        return ERROR;
    }
    while (fscanf(fp, "%s %d-%d-%d", id, &dan, &mis, &god) > 0) {
        Unos2(p->next, id, dan, mis, god);
    }
    fclose(fp);
    return 0;
}

int Unos2(MembershipP p, char id[], int dan, int mis, int god) {
    VisitP q = NULL;
    VisitP vPoc = NULL;
    q = (VisitP)malloc(sizeof(Visit));
    if (q == NULL) {
        printf("Neuspjesna alokacija memorije!");
        return ERROR;
    }
    strcpy(q->userId, id);
    q->day = dan;
    q->month = mis;
    q->year = god;
    q->next = NULL;
    while (p != NULL) {
        if (strcmp(q->userId, p->userId) == 0 && q->month - p->month == 0 && q->year - p->year == 0)
            break;
        p = p->next;
    }
    if (p == NULL) {
        return 0;
    }
    if (p->visits == NULL || p->visits->day > q->day) {
        q->next = p->visits;
        p->visits = q;
    }
    else {
        vPoc = p->visits;
        while (vPoc->next != NULL && vPoc->next->day < q->day) {
            vPoc = vPoc->next;
        }
        q->next = vPoc->next;
        vPoc->next = q;
    }
    return 0;
}