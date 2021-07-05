#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define RED 1
#define BLACK 0

typedef struct arvoreRB{
	int info;
	bool cor;
	struct arvoreRB *esq;
	struct arvoreRB *dir;
} ArvoreRB;

ArvoreRB *rot_esq(ArvoreRB *no);
ArvoreRB *rot_dir(ArvoreRB *no);
ArvoreRB *flip_cor(ArvoreRB *no);

bool eh_no_vermelho(ArvoreRB *no){
	if(!no) return BLACK;
	return (no->cor == RED);
}

ArvoreRB *arv_constroi(int x, int cor, ArvoreRB *e, ArvoreRB *d){
	ArvoreRB *a = (ArvoreRB*)malloc(sizeof(ArvoreRB));
	a->info = x;
	a->esq = e;
	a->dir = d;
	a->cor = cor;
	return a;
}

bool buscar (ArvoreRB *a, int v){
	if(a == NULL) return 0; // nao achou
	else if(v < a->info)
		return buscar(a->esq, v);
	else if(v > a->info)
		return buscar(a->dir, v);
	else 
		return 1;
}

void in_order(ArvoreRB *a){
	if(!a)
		return;
	in_order(a->esq);
	printf("%d ", a->info);
	in_order(a->dir);
}

void print(ArvoreRB *a, int spaces){
	for(int i=0; i<spaces; i++)
		printf(" ");
	if(!a){
		printf("//\n");
		return;
	}
	printf("%d\n", a->info);
	print(a->esq, spaces+2);
	print(a->dir, spaces+2);
}

short int altura_preta(ArvoreRB *a){
	int alt_esq, alt_dir;
	if(!a) return -1;

	alt_esq = altura_preta(a->esq);
	alt_dir = altura_preta(a->dir);

	if(!a->esq || a->esq->cor == BLACK) alt_esq++;
	if(!a->dir || a->dir->cor == RED) alt_dir++;

	if(alt_esq != alt_dir) 
		return -2;
	else 
		return alt_esq;//alt_esq e alt_dir sao iguais(tem o mesmo valor)
}

bool check_balanceamento_preto(ArvoreRB *a){
	if(altura_preta(a) == -2) return 0;
	else return 1;
}

bool check_in_ordem(ArvoreRB *a){
	if(!a) return 1;

	if(a->esq && a->esq->info >= a->info) return 0;
	if(a->dir && a->dir->info <= a->info) return 0;

	if(!check_in_ordem(a->esq)) return 0;
	if(!check_in_ordem(a->dir)) return 0;

	return 1;
}

bool check_arestas_vermelhas(ArvoreRB *a){
	if(!a) return 1;

	if(!check_arestas_vermelhas(a->esq)) return 0;
	if(!check_arestas_vermelhas(a->dir)) return 0;

	if(a->dir && a->dir->cor == RED) return 0;

	if(a->cor == RED) 
		if(a->esq && a->esq->cor == RED) return 0;

	return 1;
}

bool check_arvore_RB(ArvoreRB *a){
	return (check_balanceamento_preto(a) &&
		check_arestas_vermelhas(a) &&
		check_in_ordem(a));
}

ArvoreRB *arv_inserir(ArvoreRB *a, int v){	
	if(a == NULL){
		a = (ArvoreRB *)malloc(sizeof(ArvoreRB));
		a->info = v;
		a->cor = RED;
		a->esq = a->dir = NULL;
	}
	else if(v < a->info){
		a->esq = arv_inserir(a->esq, v);
	}
	else{
		a->dir = arv_inserir(a->esq, v);
	}

	//recolori 
	if(a->esq->cor == BLACK && a->dir->cor == RED){
		a = rot_esq(a);
	}
	else if(a->esq->cor == RED && a->esq->esq->cor == RED){
		a = rot_dir(a);
	}
	else if(a->esq->cor == RED && a->dir->cor == RED){
		a = flip_cor(a);
	}

	return a;
}

ArvoreRB *rot_esq(ArvoreRB *no){
	ArvoreRB *aux = no->dir;
	no->dir = aux->esq;
	aux->esq = no;
	aux->cor = no->cor;
	aux->cor = RED;
	return aux;
}

ArvoreRB *rot_dir(ArvoreRB *no){
	ArvoreRB *aux = no->esq;
	no->esq = aux->dir;
	aux->dir = no;
	aux->cor = no->cor;
	no->cor = RED;
	return aux;
}


ArvoreRB *flip_cor(ArvoreRB *no){
	no->cor = RED;
	no->esq->cor = BLACK;
	no->dir->cor = BLACK;
	return no;
}

ArvoreRB *remove(ArvoreRB *a, int dado){
	ArvoreRB *aux;
	int filhos = 0, tmp;

	if(!a)
		return NULL;
	if(a->info < dado)
		a->dir = remove(a->dir, dado);
	else if(a->info > dado)
		a->esq = remove(a->dir, dado);
	else{
		if(a->esq)
			filhos++;
		if(a->dir)
			filhos++;

		if(filhos == 0)a{
			free(a);
			return NULL;
		}
		else if(filhos == 1){
			aux = a->esq ? a->esq : a->dir;
			free(a);
			aux->cor = BLACK;
			return aux;
		}
		else {
			aux = a->esq;
			while(aux->dir)
				aux = aux->dir;
			tmp = a->info;
			a->info = tmp;
			a->esq = remove(a->esq, tmp);
			
			return aux;
		}

	}
}

void main(){
	ArvoreRB *a;
	
	a = arv_inserir(NULL, 14);
	a = arv_inserir(a, 5);
	a = arv_inserir(a, 211);
	a = arv_inserir(a, 121);
	a = arv_inserir(a, 41);
	a = arv_inserir(a, 1);
	
	in_order(a);
	printf("eh arvoreRB %d\n", check_arvore_RB(a));
	printf("aaa\n");
}

