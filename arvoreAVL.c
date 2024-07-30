//Bibliotecas
#include <stdio.h>
#include <stdlib.h>

//Constantes
#define TRUE 1
#define FALSE 0

//Struct de Nó
struct no
{
    int chave;
    struct no* esq;
    struct no* dir;
    int altura;
};

typedef struct no* ptrNo;

//Protótipos
int maior(int a, int b);
int altura_no(ptrNo aux);
int fator_balanco(ptrNo aux);
int estaVazia(ptrNo no);
int temChave(ptrNo no, int ch);
void destruir_arvore(ptrNo *no);
void inorder(ptrNo no);
// sucessor
void rotacaoRR(ptrNo *no);
void rotacaoLL(ptrNo *no);
void rotacaoLR(ptrNo *no);
void rotacaoRL(ptrNo *no);
void balancear(ptrNo *no);
void insere_chave(ptrNo *no, int ch);
// remover_chave

//Função Principal
int main(){
    ptrNo raiz = NULL;

    insere_chave(&raiz, 11);
    insere_chave(&raiz, 12);
    insere_chave(&raiz, 13);
    insere_chave(&raiz, 14);
    insere_chave(&raiz, 15);
    insere_chave(&raiz, 20);
    insere_chave(&raiz, 19);
    insere_chave(&raiz, 18);
    insere_chave(&raiz, 17);
    insere_chave(&raiz, 16);
    insere_chave(&raiz, 5);
    insere_chave(&raiz, 4);
    insere_chave(&raiz, 3);
    insere_chave(&raiz, 2);
    insere_chave(&raiz, 1);
    insere_chave(&raiz, 6);
    insere_chave(&raiz, 7);
    insere_chave(&raiz, 8);
    insere_chave(&raiz, 9);
    insere_chave(&raiz, 10);

    inorder(raiz);

    printf("\n");

    destruir_arvore(&raiz);

    return 0;
}

//Implementação das Funções
int maior(int a, int b){
    if (a>b)
        return a;
    else
        return b;
}

int altura_no(ptrNo aux){
    if (aux == NULL)
        return -1;
    else
        return aux->altura;
}
//DIFERENTE DO GPT
int fator_balanco(ptrNo aux){
    return altura_no(aux->esq) -  altura_no(aux->dir);
}
//DIFERENTE DO GPT
int estaVazia(ptrNo no){
    if (no == NULL)
        return TRUE;
    return FALSE;
}

int temChave(ptrNo no, int ch){
    if (estaVazia(no))
    {
        return FALSE;
    }
    else
    {
        if (no->chave == ch)
            return TRUE;
        else if(ch > no->chave)
            return temChave(no->dir, ch);
        else
            return temChave(no->esq, ch);
    }
}

void destruir_arvore(ptrNo *no) {
    if (*no != NULL) {
        destruir_arvore(&((*no)->esq)); // Desaloca a subárvore esquerda
        destruir_arvore(&((*no)->dir)); // Desaloca a subárvore direita
        free(*no); // Desaloca o nó atual
        *no = NULL; // Define o ponteiro para o nó como NULL
    }
}

// Função para percorrer a árvore em ordem
void inorder(ptrNo no) {
    if (no != NULL) {
        inorder(no->esq);    // Visita a subárvore esquerda
        printf("%d ", no->chave); // Visita o nó raiz
        inorder(no->dir);    // Visita a subárvore direita
    }
}

// void rotacaoRR(ptrNo *no){
//     ptrNo aux = (*no)->dir;
//     (*no)->dir = aux->esq;
//     aux->esq = (*no);
//     (*no)->altura = maior(altura_no((*no)->esq), altura_no((*no)->dir)) + 1;
//     aux->altura = maior(altura_no(aux->dir),altura_no(aux->esq)) + 1;
//     (*no) = aux;
// }

// void rotacaoLL(ptrNo *no){
//     ptrNo aux = (*no)->esq;
//     (*no)->esq = aux->dir;
//     aux->dir = (*no);
//     (*no)->altura = maior(altura_no((*no)->esq), altura_no((*no)->dir)) + 1;
//     aux->altura = maior(altura_no(aux->dir),altura_no(aux->esq)) + 1;
//     (*no) = aux;
// }

// void rotacaoLR(ptrNo *no){
//     rotacaoRR(&(*no)->esq); //Passado dessa forma, pois parametro é ptrNo* e (*no)->esq é ptrNo
//     rotacaoLL(no);          // Como no já é um ptrNo*, é passado como no apenas
// }

// void rotacaoRL(ptrNo *no){
//     rotacaoLL(&(*no)->esq); //Mesma explicação da rotacaoLR
//     rotacaoRR(no);
// }

void rotacaoRR(ptrNo *no) {
    ptrNo aux = (*no)->dir;
    (*no)->dir = aux->esq;
    aux->esq = *no;
    (*no)->altura = maior(altura_no((*no)->esq), altura_no((*no)->dir)) + 1;
    aux->altura = maior(altura_no(aux->dir), altura_no(aux->esq)) + 1;
    *no = aux;
}

void rotacaoLL(ptrNo *no) {
    ptrNo aux = (*no)->esq;
    (*no)->esq = aux->dir;
    aux->dir = *no;
    (*no)->altura = maior(altura_no((*no)->esq), altura_no((*no)->dir)) + 1;
    aux->altura = maior(altura_no(aux->dir), altura_no(aux->esq)) + 1;
    *no = aux;
}

void rotacaoLR(ptrNo *no) {
    rotacaoRR(&(*no)->esq);
    rotacaoLL(no);
}

void rotacaoRL(ptrNo *no) {
    rotacaoLL(&(*no)->dir);
    rotacaoRR(no);
}


//Considerando que o nó "C" foi inserido como filho do nó "B", e que "B" é filho do nó "A"
// se o "fator de balanceamento" for
// "A = +2" e "B = +1": Rotação LL
// "A = -2" e "B = -1": Rotação RR
// "A = +2" e "B = -1": Rotação LR
// "A =-2" e "B = +1": Rotação RL
void balancear(ptrNo* no) {
    if (*no == NULL) {
        return;
    }

    int balanco = fator_balanco(*no);
    if (balanco > 1) {
        if (fator_balanco((*no)->esq) > 0) {
            rotacaoLL(no); // Rotação simples à esquerda
        } else {
            rotacaoLR(no); // Rotação dupla esquerda-direita
        }
    } else if (balanco < -1) {
        if (fator_balanco((*no)->dir) < 0) {
            rotacaoRR(no); // Rotação simples à direita
        } else {
            rotacaoRL(no); // Rotação dupla direita-esquerda
        }
    } else {
        (*no)->altura = maior(altura_no((*no)->esq), altura_no((*no)->dir)) + 1;
    }
}

void insere_chave(ptrNo *no, int ch){
    if (temChave((*no), ch))
    {
        printf("Chave já inserida\n");
        return;
    }
    else
    {
        ptrNo novo_no = (ptrNo)malloc(sizeof(struct no));
        if (novo_no == NULL)
        {
            printf("Erro ao alocar memória\n");
            return;
        }

        if(estaVazia((*no))){ //Caso: nenhum elemento na árvore
            novo_no->dir = NULL;
            novo_no->esq = NULL;
            novo_no->chave = ch;
            novo_no->altura = 0;
            (*no) = novo_no;
        }
        else if(ch > (*no)->chave)
        {
            insere_chave(&(*no)->dir, ch);
        }
        else
        {
            insere_chave(&(*no)->esq, ch);
        }

        // Atualiza a altura do nó atual
        (*no)->altura = maior(altura_no((*no)->esq), altura_no((*no)->dir)) + 1;

        balancear(no);
    } 
}