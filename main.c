#include <stdio.h>>
#include <stdlib.h>
#include <stdbool.h>

#define RED 1
#define BLACK 0

typedef struct arvoreRB{
	int info;
	bool cor;
	struct arvoreRB *esp;
	struct arvoreRB *dir;
} ArvoreRB;

bool eh_no_vermelho(ArvoreRB *no){
	if(!no) return BLACK;
	return (no->cor == RED);
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

void in_order(Arvore *a){
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

ArvoreRB *arv_inserir(ArvoreRB *a, int v){
	
}

void main(){
	ArvoreRB *a;
}

