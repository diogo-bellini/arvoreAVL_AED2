//Bibliotecas
#include <stdio.h>

//Struct de Nó
struct no
{
    int info;
    struct no* esq;
    struct no* dir;
    int altura;
};

typedef struct no* ptrNo;

//Protótipos
ptrNo criar_arvore();
// inserir_chave
// buscar_chave
// remover_chave
// inorder
// sucessor
// fator_balanco
// rotacao_esq
// rotacao_dir
// rotacao_esq_dir
// rotacao_dir_esq.

//Função Principal
int main(){
    ptrNo raiz = criar_arvore();

    free(raiz);
}

//Implementação das Funções
ptrNo criar_arvore(){
    ptrNo aux = (ptrNo)malloc(sizeof(struct no));

    aux->dir = NULL;
    aux->esq = NULL;
    aux->altura = -1;

    return aux;
}