#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX (256)
#define ERROR (-1)

typedef struct stablo* root;
typedef struct stablo {
	char dir[MAX];
	root sib;
	root chi;
}stablo;

root Stvori(root r, root q);
root Unos(root r, root q);
root Povratak();
root Ispis(root r);
root Promjena();
root Brisi(root r);

int main() {
	stablo* root = NULL;
	char ime[MAX];
	char izbor[MAX] = { 0 };
	while (1) {
		printf("--------------------------------------\n");
		printf("\t \tMENU\n");
		printf("--------------------------------------\n");
		printf("Unesite md      za unos direktorija\n");
		printf("Unesite cd dir  za promjenu direktorija\n");
		printf("Unesite cd..    za prethodni direktorij\n");
		printf("Unesite dir     za ispis direktorija\n");
		printf("Unesite exit    za izlaz\n");
		printf("--------------------------------------\n\n");
		scanf("%s", izbor);
		if (strcmp(izbor, "md") == 0) {
			scanf("md %s", ime);
			root = Unos(&root, ime);
		}
		else if (strcmp(izbor, "cd dir") == 0) {
			//Promjena();
			break;
		}
		else if (strcmp(izbor, "cd..") == 0) {
			//Povratak();
			break;
		}
		else if (strcmp(izbor, "dir") == 0) {
			Ispis(root);
		}
		else if (strcmp(izbor, "exit") == 0) {
			Brisi(root);
			break;
		}
		else {
			printf("\nKrivi unos, pokusajte ponovo!\n\n");
		}
	}
	return 0;
}

root Stvori(root r,root q) {
	r = (root)malloc(sizeof(stablo));
	if (r == NULL) {
		printf("\nNeuspjesna alokacija memorije!");
		return ERROR;
	}
	r->dir = q;
	r->sib = NULL;
	r->chi = NULL;
	return q;
}

root Unos(root r, root q) {
	root p = Stvori(r, q);
	if (p == NULL) {
		p = q;
		return p;
	}
	else {

	}
	return 0;
}

root Ispis(root r) {
	if (r == NULL) {
		printf("Direktorij je prazan\n");
		return 0;
	}
	else {
		if (r->sib != NULL) {
			Ispis(r->sib);
		}
		printf("%s", r->dir);
		if (r->chi != NULL) {
			Ispis(r->chi);
		}
		printf("%s", r->dir);

	}
}

root Brisi(root r) {
	if (r == NULL) {
		return 0;
	}
	Brisi(r->sib);
	Brisi(r->chi);
	free(r);
	return 0;
}