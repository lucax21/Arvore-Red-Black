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

//ArvoreRB *arv_inserir(ArvoreRB *a, int v){	
//}

void main(){
	ArvoreRB *a;
	
	printf("aaa\n");
}

