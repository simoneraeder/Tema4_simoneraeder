#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Configurações ---
#define TAM_HASH 10

// --- Estruturas ---

// Nó da Árvore de Pistas (BST)
typedef struct PistaNode {
    char conteudo[50];
    struct PistaNode *esq, *dir;
} PistaNode;

// Nó da Tabela Hash (Associação Pista -> Suspeito)
typedef struct HashNode {
    char pista[50];
    char suspeito[50];
    struct HashNode *proximo;
} HashNode;

// Nó da Árvore da Mansão (Mapa)
typedef struct Sala {
    char nome[50];
    char pista[50];
    struct Sala *esquerda, *direita;
} Sala;

// --- Sistema de Tabela Hash ---

/**
 * funcaoHash: Gera um índice simples baseado na soma ASCII da string.
 */
int funcaoHash(char *str) {
    int soma = 0;
    for (int i = 0; str[i] != '\0'; i++) soma += str[i];
    return soma % TAM_HASH;
}

/**
 * inserirNaHash: Associa uma pista a um suspeito.
 */
void inserirNaHash(HashNode *tabela[], char *pista, char *suspeito) {
    int indice = funcaoHash(pista);
    HashNode *novo = (HashNode*)malloc(sizeof(HashNode));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->proximo = tabela[indice];
    tabela[indice] = novo;
}

/**
 * encontrarSuspeito: Busca na Hash qual suspeito está ligado à pista.
 */
char* encontrarSuspeito(HashNode *tabela[], char *pista) {
    int indice = funcaoHash(pista);
    HashNode *atual = tabela[indice];
    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0) return atual->suspeito;
        atual = atual->proximo;
    }
    return "Desconhecido";
}

// --- Sistema de Pistas (BST) ---

PistaNode* inserirPista(PistaNode *raiz, char *pista) {
    if (raiz == NULL) {
        PistaNode *novo = (PistaNode*)malloc(sizeof(PistaNode));
        strcpy(novo->conteudo, pista);
        novo->esq = novo->dir = NULL;
        return novo;
    }
    if (strcmp(pista, raiz->conteudo) < 0) raiz->esq = inserirPista(raiz->esq, pista);
    else if (strcmp(pista, raiz->conteudo) > 0) raiz->dir = inserirPista(raiz->dir, pista);
    return raiz;
}

// --- Lógica de Julgamento ---

/**
 * verificarSuspeitoFinal: Conta quantas pistas da BST apontam para o acusado.
 */
int contarPistasSuspeito(PistaNode *raiz, HashNode *tabela[], char *acusado) {
    if (raiz == NULL) return 0;
    int count = 0;
    if (strcmp(encontrarSuspeito(tabela, raiz->conteudo), acusado) == 0) count = 1;
    return count + contarPistasSuspeito(raiz->esq, tabela, acusado) + contarPistasSuspeito(raiz->dir, tabela, acusado);
}

// --- Sistema de Exploração ---

Sala* criarSala(char *nome, char *pista) {
    Sala *nova = (Sala*)malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esquerda = nova->direita = NULL;
    return nova;
}

void explorar(Sala *raiz, HashNode *tabela[]) {
    Sala *atual = raiz;
    PistaNode *pistasColetadas = NULL;
    char escolha, acusado[50];

    while (atual != NULL) {
        printf("\nVoce esta na: %s", atual->nome);
        if (strlen(atual->pista) > 0) {
            printf("\n[!] PISTA: %s (Suspeito: %s)", atual->pista, encontrarSuspeito(tabela, atual->pista));
            pistasColetadas = inserirPista(pistasColetadas, atual->pista);
        }

        printf("\nIr para: [e] Esquerda, [d] Direita ou [s] Sair para Acusacao: ");
        scanf(" %c", &escolha);

        if (escolha == 's') break;
        if (escolha == 'e' && atual->esquerda) atual = atual->esquerda;
        else if (escolha == 'd' && atual->direita) atual = atual->direita;
        else printf("\nCaminho sem saida!");
    }

    // FASE FINAL: O JULGAMENTO
    printf("\n--- HORA DA ACUSACAO ---");
    printf("\nDigite o nome do suspeito (Mordomo, Cozinheira ou Jardineiro): ");
    scanf("%s", acusado);

    int totalPistas = contarPistasSuspeito(pistasColetadas, tabela, acusado);
    printf("\nVoce encontrou %d pistas contra %s.", totalPistas, acusado);

    if (totalPistas >= 2) {
        printf("\n[SUCESSO] Provas suficientes! %s foi preso(a)!\n", acusado);
    } else {
        printf("\n[FALHA] Provas insuficientes. O culpado escapou!\n");
    }
}

int main() {
    srand(10); // Semente fixa para consistência
    HashNode *tabelaHash[TAM_HASH] = {NULL};

    // 1. Configurando a Tabela Hash (Pista -> Suspeito)
    inserirNaHash(tabelaHash, "Veneno", "Cozinheira");
    inserirNaHash(tabelaHash, "Luvas", "Mordomo");
    inserirNaHash(tabelaHash, "Pegadas", "Jardineiro");
    inserirNaHash(tabelaHash, "Bilhete", "Cozinheira");
    inserirNaHash(tabelaHash, "Chave", "Mordomo");

    // 2. Montando a Mansao
    Sala *hall = criarSala("Hall", "");
    Sala *cozinha = criarSala("Cozinha", "Veneno");
    Sala *jardim = criarSala("Jardim", "Pegadas");
    Sala *escritorio = criarSala("Escritorio", "Bilhete");
    Sala *biblioteca = criarSala("Biblioteca", "Chave");

    hall->esquerda = cozinha; hall->direita = jardim;
    cozinha->esquerda = escritorio;
    jardim->direita = biblioteca;

    printf("=== DETECTIVE QUEST: NIVEL MESTRE ===\n");
    explorar(hall, tabelaHash);

    return 0;
}