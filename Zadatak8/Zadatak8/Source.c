#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX (256)

typedef struct stablo* poz;
typedef struct stablo {
	int broj;
	poz left;
	poz right;
}stablo;

poz Unos(poz p, int br);
poz Inorder(poz p);
poz Preorder(poz p);
poz Postorder(poz p);
poz Levelorder(poz p);
poz Brisi(poz p, int br);
poz Trazi(poz p,int br);
poz Brisisve(poz p);
poz Trazimax(poz p);
poz Trazimin(poz p);
int Visina(poz p);
poz print(poz p, int v);

int main() {
	stablo* root = NULL;
	int el1, el2, el3;
	char izbor[MAX] = { 0 };
	while (1) {
		printf("--------------------------------------\n");
		printf("\t \tMENU\n");
		printf("--------------------------------------\n");
		printf("Unesite 1 za unos novog elementa\n");
		printf("Unesite 2 za inorder ispis\n");
		printf("Unesite 3 za preorder ispis\n");
		printf("Unesite 4 za postorder ispis\n");
		printf("Unesite 5 za level order ispis\n");
		printf("Unesite 6 za brisanje elementa\n");
		printf("Unesite 7 za trazenje elementa\n");
		printf("Unesite 8 za izlaz\n");
		printf("--------------------------------------\n\n");
		scanf("%s", izbor);
		printf("\n");
		if (strcmp(izbor, "1") == 0) {
			printf("Unesite novi element: ");
			scanf("%d", &el1);
			root = Unos(root, el1);
		}
		else if (strcmp(izbor, "2") == 0) {
			printf("Inorder ispis:\n");
			root = Inorder(root);
			printf("\n");
		}
		else if (strcmp(izbor, "3") == 0) {
			printf("Preorder ispis:\n");
			root = Preorder(root);
			printf("\n");
		}
		else if (strcmp(izbor, "4") == 0) {
			printf("Postorder ispis:\n");
			root = Postorder(root);
			printf("\n");
		}
		else if (strcmp(izbor, "5") == 0) {
			printf("Level order ispis:\n");
			root = Levelorder(root);
			printf("\n");
		}
		else if (strcmp(izbor, "6") == 0) {
			printf("Element koji zelite izbrisati: ");
			scanf("%d", &el2);

			root = Brisi(root, el2);
		}
		else if (strcmp(izbor, "7") == 0) {
			printf("Element koji zelite pronaci: ");
			scanf("%d", &el3);
			root = Trazi(root, el3);
			if (Trazi(root, el3) != NULL) {
				printf("Element se nalazi na adresi: %p\n", Trazi(root, el3));
			}
			else {
				printf("Trazeni element ne postoji!\n");
			}
		}
		else if (strcmp(izbor, "8") == 0) {
			root = Brisisve(root);
			break;
		}
		else {
			printf("Krivi unos, pokusajte ponovo!\n\n");
		}
	}
	return 0;
}

poz Unos(poz p,int br) {
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
		p->right = Unos(p->right, br);
	}
	else if (p->broj > q->broj) {
		p->left = Unos(p->left, br);
	}
	else {
		free(q);
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

poz Preorder(poz p) {
	if (p == NULL) {
		return NULL;
	}
	else {
		printf("%d ", p->broj);
		Preorder(p->left);
		Preorder(p->right);
		return p;
	}
}

poz Postorder(poz p) {
	if (p == NULL) {
		return NULL;
	}
	else {
		Postorder(p->left);
		Postorder(p->right);
		printf("%d ", p->broj);
		return p;
	}
}

poz Levelorder(poz p) {
	int i;
	int v = Visina(p);
	for (i = 0; i <= v; i++) {
		print(p->left, v - 1);
		printf(p->right, v - 1);
		return p;
	}
}

poz Brisi(poz p, int br) {
	if (p == NULL) {
		return NULL;
	}
	else if (p->broj < br) {
		p->right = Brisi(p->right, br);
	}
	else if (p->broj > br) {
		p->left = Brisi(p->left, br);
	}
	else {
		if (p->left) {
			poz temp = Trazimax(p->left);
			p->broj = temp->broj;
			p->left = Brisi(p->left, br);
		}
		else if (p->right) {
			poz temp = Trazimin(p->right);
			p->broj = temp->broj;
			p->right = Brisi(p->right, br);
		}
		else {
			free(p); 
			return NULL;
		}
		return p;
	}
}

poz Trazi(poz p, int br) {
	if (p == NULL) {
		return NULL;
	}
	else if (p->broj == br) {
		return p;
	}
	else if (br > p->broj) {
		return Trazi(p->right, br);
	}
	else if (br < p->broj) {
		return Trazi(p->left, br);
	}
	return p;
}

poz Brisisve(poz p) {
	if (p == NULL) {
		return NULL;
	}
	Brisisve(p->left);
	Brisisve(p->right);
	free(p);
	return NULL;
}

poz Trazimax(poz p) {
	if (p == NULL) {
		return NULL;
	}
	else if (p->right != NULL) {
		p = p->right;
		return Trazimax(p);
	}
	return p;
}

poz Trazimin(poz p) {
	if (p == NULL) {
		return NULL;
	}
	else if (p->left != NULL) {
		p = p->left;
		return Trazimin(p);
	}
	return p;
}

int Visina(poz p) {
	if (p == NULL) {
		return NULL;
	}
	else {
		int lvisina = Visina(p->left);
		int rvisina = Visina(p->right);
		if (lvisina > rvisina) {
			return(lvisina + 1);
		}
		else {
			return(rvisina + 1);
		}
	}
}

poz print(poz p, int v) {
	int i;
	if (p == NULL) {
		return NULL;
	}
	else if (v == 1) {
		printf("%d ", p->broj);
		return p;
	}
	else  if (v > 1) {
		for (i = 1; i <= v; i++) {
			Levelorder(p->left);
			Levelorder(p->right);
		}
	}
	return p;
}