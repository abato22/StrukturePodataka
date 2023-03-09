#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_DIDNT_OPEN_ERROR (-1)
#define MAX_LINE (1024)
#define MAX_FILE_NAME (256)
#define MAX (25)

typedef struct {
	char ime[MAX];
	char prezime[MAX];
	int bodovi;
}student;

int prebroji(char* datoteka);
void ispis(student* studenti, int br, char* datoteka);

int main(){
	char datoteka[MAX_FILE_NAME] = { 0 };
	int brst;
	student* studenti;
	printf("Unesi ime datoteke: ");
	scanf(" %s", datoteka);
	brst = prebroji(datoteka);
	printf("Broj studenata u datoteci %s je %d\n", datoteka, brst);
	studenti = (student*)malloc(brst * sizeof(student));
	if (studenti == NULL){
		printf("Memorija nije alocirana!");
		return FILE_DIDNT_OPEN_ERROR;
	}
	ispis(studenti, brst, datoteka);
	return 0;
}

int prebroji(char* datoteka){
	FILE* fp = NULL;
	int broj = 0;
	char buffer[MAX_LINE] = { 0 };
	fp = fopen(datoteka, "r");
	if (fp == NULL){
		printf("Datoteka %s se nije otvorila!\n", datoteka);
		return FILE_DIDNT_OPEN_ERROR;
	}
	while (!feof(fp)){
		fgets(buffer, MAX_LINE, fp);
		if (strcmp("\n", buffer) != 0){
			broj++;
		}
	}
	fclose(fp);
	return broj;
}

void ispis(student* studenti, int br, char* datoteka) {
	FILE* fp = NULL;
	fp = fopen(datoteka, "r");
	int i = 0;
	double max = 100;
	for (i = 0; i < br; i++){
		fscanf(fp, "%s\t", studenti[i].ime);
		fscanf(fp, "%s\t", studenti[i].prezime);
		fscanf(fp, "%d\t", &studenti[i].bodovi);
	}
	fclose(fp);
	for (i = 0; i < br; i++){
		printf("Ime studenta: %s\t", studenti[i].ime);
		printf("prezime studenta: %s\t", studenti[i].prezime);
		printf("broj bodova: %d\t", studenti[i].bodovi);
		printf("relativan broj bodova: %.2f\t", (studenti[i].bodovi / max) * 100);
		printf("\n");
	}
}