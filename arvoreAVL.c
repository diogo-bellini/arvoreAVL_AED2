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
int* sucessor(ptrNo no); //Retorna o próximo valor da árvore (maior que o nó passado)
void rotacaoRR(ptrNo *no); //Gira para a esquerda (balanceando)
void rotacaoLL(ptrNo *no); //Gira para a direita (balanceando)
void rotacaoLR(ptrNo *no); //Gira para esquerda depois para a direita (balanceando)
void rotacaoRL(ptrNo *no); //Gira para direita depois para a esquerda (balanceando)
void balancear(ptrNo *no); //Chama a função de calcular fb e as funções de rotação se necessário
void inserir_chave(ptrNo *no, int ch); //Insere uma chave nova na árvore
void remover_chave(ptrNo *no, int ch); //Remove uma chave da árvore
ptrNo procura_menor(ptrNo no);

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
    inorder(raiz);
    printf("\n\n");

    // 3. Calcular fator de balanço de todos os nós
    inorder_fb(raiz);
    printf("\n\n");

    // 4. Remover as chaves (nessa ordem): 5, 10 e 15
    remover_chave(&raiz, 5);
    remover_chave(&raiz, 10);
    remover_chave(&raiz, 15);

    // 5. Mostrar percurso inorder (como fica a árvore após todas as rotações)
    inorder(raiz);
    printf("\n\n");

    // 6. Calcular fator de balanço de todos os nós
    inorder_fb(raiz);
    printf("\n");
    
    // Libera espaço da memória usado pela árvore
    destruir_arvore(&raiz);

    // Finaliza execução
    return 0;
}

// Funções
// Compara dois inteiros e retorna maior
int maior(int a, int b){
    if (a>b)
        return a;
    else
        return b;
}

// Retorna altura do nó
int altura_no(ptrNo aux){
    if (aux == NULL)
        return -1;
    else
        return aux->altura;
}

// Calcula fator de balanceamento do nó
int fator_balanco(ptrNo aux){
    return altura_no(aux->esq) - altura_no(aux->dir);
}

// Verifica se árvore está vazia
int estaVazia(ptrNo no){
    if (no == NULL)
        return TRUE;
    return FALSE;
}

// Verifica se chave está contida na árvore
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

// Libera espaço da árvore
void destruir_arvore(ptrNo *no){
    if (*no != NULL) {
        destruir_arvore(&((*no)->esq)); // Desaloca a subárvore esquerda
        destruir_arvore(&((*no)->dir)); // Desaloca a subárvore direita
        free(*no);                      // Desaloca o nó atual
        *no = NULL;                     // Define o ponteiro para o nó como NULL
    }
}

// Função para percorrer a árvore em ordem
void inorder(ptrNo no){
    if (no != NULL) {
        inorder(no->esq);           // Visita a subárvore esquerda
        printf("%d ", no->chave);   // Visita o nó raiz
        inorder(no->dir);           // Visita a subárvore direita
    }
}

// Função para percorrer a árvore e retornar fator de balanço em ordem
void inorder_fb(ptrNo no){
    if (no != NULL) {
        inorder_fb(no->esq);                // Visita a subárvore esquerda
        printf("%d ", fator_balanco(no));   // Visita o nó raiz
        inorder_fb(no->dir);                // Visita a subárvore direita
    }
}

// Retorna sucessor do nó
int* sucessor(ptrNo no){
    int* ponteiro_valor_sucessor = NULL;
    if (no->dir!=NULL)
    {
        ponteiro_valor_sucessor = &(no->dir->chave);
    }
    
    return ponteiro_valor_sucessor;
}

// Rotação simples à esquerda
void rotacaoRR(ptrNo *no){
    ptrNo aux = (*no)->dir;
    (*no)->dir = aux->esq;
    aux->esq = *no;
    (*no)->altura = maior(altura_no((*no)->esq), altura_no((*no)->dir)) + 1;
    aux->altura = maior(altura_no(aux->dir), altura_no(aux->esq)) + 1;
    *no = aux;
}

// Rotação simples à direita
void rotacaoLL(ptrNo *no){
    ptrNo aux = (*no)->esq;
    (*no)->esq = aux->dir;
    aux->dir = *no;
    (*no)->altura = maior(altura_no((*no)->esq), altura_no((*no)->dir)) + 1;
    aux->altura = maior(altura_no(aux->dir), altura_no(aux->esq)) + 1;
    *no = aux;
}

// Rotação dupla à direita
void rotacaoLR(ptrNo *no){
    rotacaoRR(&(*no)->esq); //Passado dessa forma, pois parametro é ptrNo* e (*no)->esq é ptrNo
    rotacaoLL(no);          // Como no já é um ptrNo*, é passado como no apenas
}

// Rotação dupla à esquerda
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

// Insere uma chave nova na árvore
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

//Remove uma chave da árvore
void remover_chave(ptrNo *no, int ch){
    if (!buscar_chave((*no), ch))
    {
        printf("Chave não encontrada\n");
        return;
    }

    if(ch > (*no)->chave)
        remover_chave(&(*no)->dir, ch);
    else if(ch < (*no)->chave)
        remover_chave(&(*no)->esq, ch);
    else
    {
        if((*no)->esq == NULL || (*no)->dir == NULL)
        {
            ptrNo temp = (*no)->esq ? (*no)->esq : (*no)->dir;

            if(temp == NULL)
            {
                temp = *no;
                *no = NULL;
            }
            else
                *no = temp;

            //free(temp);
        }
        else
        {
            ptrNo temp = procura_menor((*no)->dir);

            (*no)->chave = temp->chave;

            remover_chave(&(*no)->dir, temp->chave);
        }

        if(no == NULL)
            return;

        // Atualiza a altura do nó atual
        (*no)->altura = maior(altura_no((*no)->esq), altura_no((*no)->dir)) + 1;

        balancear(no);
    }
}

ptrNo procura_menor(ptrNo atual){
    while(atual->esq != NULL)
        atual = atual->esq;
    return atual;
}