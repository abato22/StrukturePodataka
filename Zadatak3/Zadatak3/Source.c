#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX (50)
#define ERROR (-1)
#define MAX_FILE (256)

typedef struct _osoba* pozicija;
typedef struct _osoba {
    char ime[MAX];
    char prezime[MAX];
    int godina;
    pozicija next;
}osoba;

int UnosP(pozicija p);
int UnosK(pozicija p);
int Trazi(pozicija p);
int Brisi(pozicija p);
int Ispis(pozicija p);
int UnosIz(pozicija p);
int UnosIs(pozicija p);
int Sort(pozicija p);
int UpisDat(pozicija p);
int CitaDat(pozicija p);
int BrisiSve(pozicija p);

int main() {
    osoba Head;
    Head.next = NULL;
    int izbor1 = 0, izbor2 = 0;
    do {
        printf("Zelite li nesto raditi sa listom? ");
        printf("\nUnesite broj 1 za odgovor DA");
        printf("\nUnesite bilo koji drugi broj za odgovor NE\n");
        printf("\nUnesite broj: ");
        scanf("%d", &izbor1);
        if (izbor1 == 1) {
            printf("\nIzaberite sto zelite napraviti:\n\n");
            printf("Unesite broj 1 za dodavanje osobe na pocetak liste\n");
            printf("Unesite broj 2 za dodavanje osobe na kraj liste\n");
            printf("Unesite broj 3 za trazenje osobe u listi(po prezimenu)\n");
            printf("Unesite broj 4 za brisanje osobe iz liste\n");
            printf("Unesite broj 5 za ispis liste\n");
            printf("Unesite broj 6 za dodavanje osobe iza odradene osobe\n");
            printf("Unesite broj 7 za dodavanje osobe ispred odredene osobe\n");
            printf("Unesite broj 8 za sortiranje liste po prezimenima osoba\n");
            printf("Unesite broj 9 za upisivanje liste u datoteku\n");
            printf("Unesite broj 0 za citanje liste iz datoteke\n");
            printf("\nUnesite broj: ");
            scanf("%d", &izbor2);
            printf("\n");
            if (izbor2 == 1) {
                UnosP(&Head);
            }
            if (izbor2 == 2) {
                UnosK(&Head);
            }
            if (izbor2 == 3) {
                Trazi(Head.next);
            }
            if (izbor2 == 4) {
                Brisi(&Head);
            }
            if (izbor2 == 5) {
                Ispis(Head.next);
            }
            if (izbor2 == 6) {
                UnosIz(Head.next);
            }
            if (izbor2 == 7) {
                UnosIs(&Head);
            }
            if (izbor2 == 8) {
                Sort(&Head);
            }
            if (izbor2 == 9) {
                UpisDat(&Head);
            }
            if (izbor2 == 0) {
                CitaDat(Head.next);
            }
        }
        if (izbor1 != 1) {
            BrisiSve(&Head);
        }
    } while (izbor1 == 1);
}
int UnosP(pozicija p) {
    pozicija q = NULL;
    q = (pozicija)malloc(sizeof(osoba));
    if (q == NULL) {
        printf("\nNeuspjesna alokacija memorije!");
        return ERROR;
    }
    printf("Unesite ime osobe: ");
    scanf("%s", q->ime);
    printf("Unesite prezime osobe: ");
    scanf("%s", q->prezime);
    printf("Unesite godinu rodenja osobe: ");
    scanf("%d", &(q->godina));
    printf("\n");
    q->next = p->next;
    p->next = q;
    return 0;
}
int UnosK(pozicija p) {
    while (p->next != NULL)
    {
        p = p->next;
    }
    pozicija q = NULL;
    q = (pozicija)malloc(sizeof(osoba));
    if (q == NULL)
    {
        printf("\nNeuspjesna alokacija memorije!");
        return ERROR;
    }
    printf("Unesite ime osobe: ");
    scanf(" %s", q->ime);
    printf("Unesite prezime osobe: ");
    scanf(" %s", q->prezime);
    printf("Unesite godinu rodenja osobe: ");
    scanf("%d", &q->godina);
    printf("\n");
    q->next = p->next;
    p->next = q;
    return 0;
}
int Trazi(pozicija p) {
    char prez[MAX] = { 0 };
    printf("Unesite prezime osobe koju zelite pronaci: ");
    scanf("%s", &prez);
    printf("\n");
    while (p != NULL && strcmp(prez, p->prezime) != 0){
        p =p->next;
    }
    if (p == NULL)
        printf("Osoba ne postoji!\n\n");
    else
        printf("Adresa trazene osobe je: %p\n\n", p);
    return 0;
}
int Brisi(pozicija p) {
    pozicija pret = NULL;
    char prez[MAX] = { 0 };
    printf("Unesite prezime osobe koju zelite izbrisati: ");
    scanf("%s", &prez);
    printf("\n");
    while (p->next != NULL && strcmp(prez, p->prezime) != 0)
    {
        pret = p;
        p = p->next;
    }
    if (pret != NULL && strcmp(prez, p->prezime) == 0)
    {
        p = pret->next;
        pret->next = p->next;
    }
    if (p->next == NULL)
        printf("Osoba ne postoji!\n\n");
    return 0;
}
int Ispis(pozicija p) {
    while (p != NULL) {
        printf("%s\t%s\t%d\n", p->ime, p->prezime, p->godina);
        p = p->next;
    }
    printf("\n");
    return 0;
}
int UnosIz(pozicija p) {
    pozicija q = NULL;
    char prez[MAX] = { 0 };
    printf("Unesite prezime osobe iza koje zelite unijeti novu osobu: ");
    scanf("%s", &prez);
    while (p != NULL && strcmp(prez, p->prezime) != 0){
        p = p->next;
    }
    if (p == NULL)
        printf("Osoba ne postoji!\n\n");
    else {
        q = (pozicija)malloc(sizeof(osoba));
        printf("\nUnesite ime osobe: ");
        scanf(" %s", q->ime);
        printf("Unesite prezime osobe: ");
        scanf(" %s", q->prezime);
        printf("Unesite godinu rodenja osobe: ");
        scanf("%d", &q->godina);
        printf("\n");
        q->next = p->next;
        p->next = q;
    }
    return 0;
}
int UnosIs(pozicija p) {
    pozicija q = NULL;
    char prez[MAX] = { 0 };
    printf("Unesite prezime osobe ispred koje zelite unijeti novu osobu: ");
    scanf("%s", &prez);
    while (p->next != NULL && strcmp(prez, p->next->prezime) != 0){
        p = p->next;
    }
    if (p->next == NULL)
        printf("Osoba ne postoji!\n\n");
    else {
        q = (pozicija)malloc(sizeof(osoba));
        printf("\nUnesite ime osobe: ");
        scanf(" %s", q->ime);
        printf("Unesite prezime osobe: ");
        scanf(" %s", q->prezime);
        printf("Unesite godinu rodenja osobe: ");
        scanf("%d", &q->godina);
        printf("\n");
        q->next = p->next;
        p->next = q;
    }
    return 0;
}
int Sort(pozicija p) {
    pozicija j, pret_j, temp, end;
    end = NULL;
    while (p->next != end) {
        pret_j = p;
        j = p->next;
        while (j->next != end) {
            if (strcmp(j->prezime, j->next->prezime) > 0) {
                temp = j->next;
                pret_j->next = temp;
                j->next = temp->next;
                temp->next = j;
                j = temp;
            }
            pret_j = j;
            j = j->next;
        }
        end = j;
    }
    return 0;
}
int UpisDat(pozicija p) {
    char datoteka[MAX_FILE] = { 0 };
    printf("Unesi ime datoteke: ");
    scanf(" %s", datoteka);
    printf("\n");
    FILE* fp = NULL;
    fp = fopen(datoteka, "w");
    if (fp == NULL)
    {
        printf("Datoteka %s se nije otvorila!\n\n", datoteka);
        return ERROR;
    }
    while (fp != NULL) {
        fprintf(fp, "%s\t%s\t%d\n", p->ime, p->prezime, p->godina);
        p = p->next;
    }
    fclose(fp);
    return 0;
}
int CitaDat(pozicija p) {
    char datoteka[MAX_FILE] = { 0 };
    printf("Unesi ime datoteke: ");
    scanf(" %s", datoteka);
    printf("\n");
    FILE* fp = NULL;
    fp = fopen(datoteka, "r");
    if (fp == NULL)
    {
        printf("Datoteka %s se nije otvorila!\n\n", datoteka);
        return ERROR;
    }
    /*while (!feof(fp)) {
        fscanf(fp, "%s\t%s\t%d\n", p->ime, p->prezime, &(p->godina));
        p = p->next;
    }
    while (p!=NULL) {
        printf("%s\t%s\t%d\n", p->ime, p->prezime, p->godina);
        p = p->next;
    }*/
    /*char buffer[MAX] = {0};
    while (!feof(fp)) {
        sscanf(p, "%s %s %d", p->ime, p->prezime, &p->godina);
        //printf("%s %s %d\n", p->ime, p->prezime, p->godina);
        fgets(buffer, MAX, fp);
        //printf("%s %s %d\n", p->ime, p->prezime, p->godina);
        printf("%s", buffer);
    }
    printf("\n");
    fclose(fp);*/
    return 0;
}

int BrisiSve(pozicija p) {
    pozicija temp, pocetak = p;
    while (p->next != NULL) {
        while (p->next->next != NULL)
            p = p->next;
        temp = p->next;
        p->next = temp->next;
        free(temp);
        p = pocetak;
    }
    return 0;
}