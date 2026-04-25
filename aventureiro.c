#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Estrutura da Árvore de Pistas (BST) ---
typedef struct PistaNode {
    char conteudo[50];
    struct PistaNode *esq, *dir;
} PistaNode;

// --- Estrutura da Árvore do Mapa (Mansão) ---
typedef struct Sala {
    char nome[50];
    char pista[50]; // Conteúdo da pista na sala
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// --- Funções da Árvore de Pistas (BST) ---

/**
 * inserirPista: Adiciona uma pista na BST de forma ordenada (alfabética).
 */
PistaNode* inserirPista(PistaNode* raiz, char* novaPista) {
    if (raiz == NULL) {
        PistaNode* novo = (PistaNode*)malloc(sizeof(PistaNode));
        strcpy(novo->conteudo, novaPista);
        novo->esq = novo->dir = NULL;
        return novo;
    }

    // Comparação alfabética para decidir o lado (BST)
    if (strcmp(novaPista, raiz->conteudo) < 0) {
        raiz->esq = inserirPista(raiz->esq, novaPista);
    } else if (strcmp(novaPista, raiz->conteudo) > 0) {
        raiz->dir = inserirPista(raiz->dir, novaPista);
    }
    return raiz;
}

/**
 * exibirPistas: Percorre a BST (Em-Ordem) para listar as pistas em ordem alfabética.
 */
void exibirPistas(PistaNode* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esq);
        printf("- %s\n", raiz->conteudo);
        exibirPistas(raiz->dir);
    }
}

// --- Funções do Mapa da Mansão ---

/**
 * criarSala: Cria um cômodo com nome e uma pista opcional.
 */
Sala* criarSala(char* nome, char* pista) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esquerda = nova->direita = NULL;
    return nova;
}

/**
 * explorarSalasComPistas: Navegação e coleta automática de pistas.
 */
void explorarSalasComPistas(Sala* mapa) {
    Sala* atual = mapa;
    PistaNode* inventarioPistas = NULL;
    char escolha;

    printf("\n--- INVESTIGACAO INICIADA ---\n");

    while (atual != NULL) {
        printf("\n>>> Voce esta na sala: %s", atual->nome);

        // Coleta automática de pista se houver uma
        if (strlen(atual->pista) > 0) {
            printf("\n[!] PISTA ENCONTRADA: %s", atual->pista);
            inventarioPistas = inserirPista(inventarioPistas, atual->pista);
            // "Limpa" a pista da sala para não coletar repetido se voltar nela
            strcpy(atual->pista, ""); 
        }

        printf("\nPara onde deseja ir? (e: esquerda, d: direita, s: sair e ver pistas): ");
        scanf(" %c", &escolha);

        if (escolha == 's') break;

        if (escolha == 'e' && atual->esquerda != NULL) {
            atual = atual->esquerda;
        } else if (escolha == 'd' && atual->direita != NULL) {
            atual = atual->direita;
        } else if (escolha == 'e' || escolha == 'd') {
            printf("\n[!] Nao ha caminho por ai!");
        } else {
            printf("\n[!] Opcao invalida.");
        }
    }

    printf("\n========================================");
    printf("\n   RELATORIO FINAL DE PISTAS (A-Z)      ");
    printf("\n========================================\n");
    if (inventarioPistas == NULL) {
        printf("Nenhuma pista coletada.\n");
    } else {
        exibirPistas(inventarioPistas);
    }
}

// --- Função Principal ---

int main() {
    // 1. Montagem do Mapa (Fixo no código conforme nível Aventureiro)
    Sala* hall = criarSala("Hall", "");
    Sala* escritorio = criarSala("Escritorio", "Diario Antigo");
    Sala* cozinha = criarSala("Cozinha", "Faca de Prata");
    Sala* porao = criarSala("Porao", "Chave Enferrujada");
    Sala* sotao = criarSala("Sotao", "Bilhete Anonimo");

    hall->esquerda = escritorio;
    hall->direita = cozinha;
    escritorio->esquerda = porao;
    cozinha->direita = sotao;

    // 2. Início do Jogo
    printf("     DETECTIVE QUEST: NIVEL AVENTUREIRO\n");
    explorarSalasComPistas(hall);

    return 0;
}