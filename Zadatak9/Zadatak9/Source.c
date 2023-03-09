#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX (256)
#define ERROR (-1)

typedef struct stablo* poz;
typedef struct stablo {
	int broj;
	poz left;
	poz right;
}stablo;

poz Unos(poz p, int br);
poz Inorder(poz p);
int Replace(poz p);
poz Upis(poz p);
poz InorderFile(FILE* fp, poz p);

int main() {
	srand(time(0));
	stablo* root = NULL;
	int i, br;

	/*int niz[10] = {2,5,7,8,11,1,4,2,3,7};
	for (i = 0; i < 10; i++) {
		root = Unos(root, niz[i]);
	}*/
	printf("Random brojevi:\n");
	for (i = 0; i < 10; i++) {
		br = (rand() % (89 - 11 + 1)) + 11;
		printf("%d ", br);
		root = Unos(root, br);
	}

	printf("\n\n");
	printf("a)\n");
	root = Inorder(root);
	printf("\n\n");

	Replace(root);
	printf("b)\n");
	root = Inorder(root);
	printf("\n\n");

	Upis(root);
	//Upis(Replace(root));
	return 0;
}

poz Unos(poz p, int br) {
	poz q = NULL;
	q = (poz)malloc(sizeof(stablo));
	if (q == NULL) {
		printf("\nNeuspjesna alokacija memorije!");
		return NULL;
	}
	q->broj = br;
	if (p == NULL) {
		p = q;
		p->left = NULL;
		p->right = NULL;
		return p;
	}
	if (p->broj < q->broj) {
		p->left = Unos(p->left, br);
	}
	else if (p->broj >= q->broj) {
		p->right = Unos(p->right, br);
	}
	return p;
}

poz Inorder(poz p) {
	if (p == NULL) {
		return NULL;
	}
	else {
		Inorder(p->left);
		printf("%d ", p->broj);
		Inorder(p->right);
		return p;
	}
}

int Replace(poz p) {
	if (p == NULL) {
		return NULL;
	}
	int num = p->broj;
	p->broj = Replace(p->left) + Replace(p->right);
	return p->broj + num;
}

poz Upis(poz p) {
	printf("\n");
	FILE* fp = NULL;
	fp = fopen("dat.txt", "w");
	if (fp == NULL) {
		printf("Datoteka se nije otvorila!\n");
		return ERROR;
	}
	InorderFile(fp, p);
	fclose(fp);
	return 0;
}

poz InorderFile(FILE* fp,poz p) {
	if (p == NULL) {
		return NULL;
	}
	else {
		InorderFile(fp, p->left);
		fprintf(fp, "%d ", p->broj);
		InorderFile(fp, p->right);
		return p;
	}
}