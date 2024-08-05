//Bibliotecas
#include <stdio.h>
#include <stdlib.h>

// Constantes
#define TRUE 1
#define FALSE 0

typedef struct No* ptrNo;

// Struct de Nó
struct No
{
    int chave;
    struct No* esq;
    struct No* dir;
    int altura;
};

// Protótipos
int maior(int a, int b); //Define o maior valor entre os parâmetros
int altura_no(ptrNo no); //Retorna a altura do nó
int fator_balanco(ptrNo no); //Calcula o fator de balanceamento do nó
int estaVazia(ptrNo no); //Retorna se a arvore está ou não vazia
int buscar_chave(ptrNo no, int ch); //Faz uma busca pela chave "ch" na arvore
void destruir_arvore(ptrNo *no); //Desaloca arvore toda recursivamente
void inorder(ptrNo no); //Faz o print dos valores da árvore em ordem crescente
void inorder_fb(ptrNo no); // Função para percorrer a árvore e retornar fator de balanço em ordem
ptrNo sucessor(ptrNo no); //Retorna o menor valor da sub-árvore direita
void rotacaoRR(ptrNo *no); //Gira para a esquerda (balanceando)
void rotacaoLL(ptrNo *no); //Gira para a direita (balanceando)
void rotacaoLR(ptrNo *no); //Gira para esquerda depois para a direita (balanceando)
void rotacaoRL(ptrNo *no); //Gira para direita depois para a esquerda (balanceando)
void balancear(ptrNo *no); //Chama a função de calcular fb e as funções de rotação se necessário
void inserir_chave(ptrNo *no, int ch); //Insere uma chave nova na árvore
void remover_chave(ptrNo *no, int ch); //Remove uma chave da árvore

//Função Principal
int main(){
    // Inicializa árvore
    ptrNo raiz = NULL;

    // 1. Inserir conjunto de chaves em ordem
    inserir_chave(&raiz, 11);
    inserir_chave(&raiz, 12);
    inserir_chave(&raiz, 13);
    inserir_chave(&raiz, 14);
    inserir_chave(&raiz, 15);
    inserir_chave(&raiz, 20);
    inserir_chave(&raiz, 19);
    inserir_chave(&raiz, 18);
    inserir_chave(&raiz, 17);
    inserir_chave(&raiz, 16);
    inserir_chave(&raiz, 5);
    inserir_chave(&raiz, 4);
    inserir_chave(&raiz, 3);
    inserir_chave(&raiz, 2);
    inserir_chave(&raiz, 1);
    inserir_chave(&raiz, 6);
    inserir_chave(&raiz, 7);
    inserir_chave(&raiz, 8);
    inserir_chave(&raiz, 9);
    inserir_chave(&raiz, 10);

    // 2. Mostrar percurso inorder (como fica a árvore após todas as rotações). 
    printf("\nÁrvore depois das inserções:\n");
    inorder(raiz);
    printf("\n\n");

    // 3. Calcular fator de balanço de todos os nós
    printf("\nFator de balanço dos nós:\n");
    inorder_fb(raiz);
    printf("\n\n");

    // 4. Remover as chaves (nessa ordem): 5, 10 e 15
    remover_chave(&raiz, 5);
    remover_chave(&raiz, 10);
    remover_chave(&raiz, 15);

    // 5. Mostrar percurso inorder (como fica a árvore após todas as rotações)
    printf("\nÁrvore depois das remoções:\n");
    inorder(raiz);
    printf("\n\n");

    // 6. Calcular fator de balanço de todos os nós
    printf("\nFator de balanço dos nós:\n");
    inorder_fb(raiz);
    printf("\n");
    
    // Libera espaço da memória usado pela árvore
    destruir_arvore(&raiz);

    // Finaliza execução
    return 0;
}

// Implementação das Funções

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

int fator_balanco(ptrNo aux){
    return altura_no(aux->esq) - altura_no(aux->dir);
}

int estaVazia(ptrNo no){
    if (no == NULL)
        return TRUE;
    return FALSE;
}

int buscar_chave(ptrNo no, int ch){
    if (estaVazia(no))
    {
        return FALSE;
    }
    else
    {
        if (no->chave == ch)
            return TRUE;
        else if(ch > no->chave)
            return buscar_chave(no->dir, ch);
        else
            return buscar_chave(no->esq, ch);
    }
}

void destruir_arvore(ptrNo *no){
    if (*no != NULL) {
        destruir_arvore(&((*no)->esq)); // Desaloca a subárvore esquerda
        destruir_arvore(&((*no)->dir)); // Desaloca a subárvore direita
        free(*no);                      // Desaloca o nó atual
        *no = NULL;                     // Define o ponteiro para o nó como NULL
    }
}

void inorder(ptrNo no){
    if (no != NULL) {
        inorder(no->esq);           // Visita a subárvore esquerda
        printf("%d ", no->chave);   // Visita o nó raiz
        inorder(no->dir);           // Visita a subárvore direita
    }
}

void inorder_fb(ptrNo no){
    if (no != NULL) {
        inorder_fb(no->esq);                // Visita a subárvore esquerda
        printf("%d ", fator_balanco(no));   // Visita o nó raiz
        inorder_fb(no->dir);                // Visita a subárvore direita
    }
}


ptrNo sucessor(ptrNo no){
    ptrNo aux = no->dir;
    while (aux->esq != NULL)
    {
        aux = aux->esq;
    }
    return aux;
}

void rotacaoRR(ptrNo *no){
    ptrNo aux = (*no)->dir;
    (*no)->dir = aux->esq;
    aux->esq = *no;
    (*no)->altura = maior(altura_no((*no)->esq), altura_no((*no)->dir)) + 1;
    aux->altura = maior(altura_no(aux->dir), altura_no(aux->esq)) + 1;
    *no = aux;
}

void rotacaoLL(ptrNo *no){
    ptrNo aux = (*no)->esq;
    (*no)->esq = aux->dir;
    aux->dir = *no;
    (*no)->altura = maior(altura_no((*no)->esq), altura_no((*no)->dir)) + 1;
    aux->altura = maior(altura_no(aux->dir), altura_no(aux->esq)) + 1;
    *no = aux;
}

void rotacaoLR(ptrNo *no){
    rotacaoRR(&(*no)->esq); //Passado dessa forma, pois parametro é ptrNo* e (*no)->esq é ptrNo
    rotacaoLL(no);          // Como no já é um ptrNo*, é passado como no apenas
}

void rotacaoRL(ptrNo *no){
    rotacaoLL(&(*no)->dir); //Mesma explicação da rotacaoLR
    rotacaoRR(no);
}

/* 
    Considerando que o nó "C" foi inserido como filho do nó "B", e 
    que "B" é filho do nó "A" se o "fator de balanceamento" for:
    "A = +2" e "B = +1": Rotação LL
    "A = -2" e "B = -1": Rotação RR
    "A = +2" e "B = -1": Rotação LR
    "A =-2" e "B = +1": Rotação RL
*/
void balancear(ptrNo *no) {
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

void inserir_chave(ptrNo *no, int ch){
    if (buscar_chave((*no), ch))
    {
        printf("Chave já inserida\n");
        return;
    }
    else
    {
        ptrNo novo_no = (ptrNo)malloc(sizeof(struct No));
        if (novo_no == NULL)
        {
            printf("Erro ao alocar memória\n");
            return;
        }

        //Caso: nenhum elemento na árvore
        if(estaVazia(*no))
        {
            novo_no->dir = NULL;
            novo_no->esq = NULL;
            novo_no->chave = ch;
            novo_no->altura = 0;
            (*no) = novo_no;
        }
        else if(ch > (*no)->chave) //Caso: árvore não vazia...
        {
            inserir_chave(&(*no)->dir, ch);
        }
        else
        {
            inserir_chave(&(*no)->esq, ch);
        }

        // Atualiza a altura do nó atual
        (*no)->altura = maior(altura_no((*no)->esq), altura_no((*no)->dir)) + 1;

        balancear(no);
    } 
}

void remover_chave(ptrNo *no, int ch){
    if ((*no) != NULL) {
        if ((*no)->chave == ch) {
            if ((*no)->esq == NULL && (*no)->dir == NULL) { // Caso 1: Nó é uma folha
                free(*no);
                (*no) = NULL;
            } else if ((*no)->esq != NULL && (*no)->dir == NULL) { // Caso 2: Nó tem apenas filho esquerdo
                ptrNo aux = (*no);
                (*no) = (*no)->esq;
                free(aux);
                aux = NULL;
            } else if ((*no)->esq == NULL && (*no)->dir != NULL) { // Caso 2: Nó tem apenas filho direito
                ptrNo aux = (*no);
                (*no) = (*no)->dir;
                free(aux);
                aux = NULL;
            } else { // Caso 3: Nó tem dois filhos
                ptrNo temp = sucessor(*no);
                (*no)->chave = temp->chave;
                remover_chave(&(*no)->dir, temp->chave); // Remove o sucessor
            }
        } else if ((*no)->chave > ch) {
            remover_chave(&(*no)->esq, ch);
        } else {
            remover_chave(&(*no)->dir, ch);
        }

        // Rebalanceamento e atualização da altura do nó após a remoção
        if (*no != NULL) {
            (*no)->altura = maior(altura_no((*no)->esq), altura_no((*no)->dir)) + 1;
            balancear(no);    
        }
    }
}