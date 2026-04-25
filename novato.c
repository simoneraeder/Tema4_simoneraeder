#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Definição da Estrutura da Sala ---
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// --- Funções do Sistema ---

/**
 * Função: criarSala
 * Objetivo: Cria de forma dinâmica um novo cômodo (nó) da árvore.
 * Aloca memória, define o nome e inicializa os ponteiros como NULL.
 */
Sala* criarSala(char *nome) {
    Sala *novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala != NULL) {
        strcpy(novaSala->nome, nome);
        novaSala->esquerda = NULL;
        novaSala->direita = NULL;
    }
    return novaSala;
}

/**
 * Função: explorarSalas
 * Objetivo: Permite a navegação interativa do jogador pela árvore.
 */
void explorarSalas(Sala *raiz) {
    Sala *atual = raiz;
    char escolha;

    printf("\n--- Inicio da Investigacao ---\n");

    while (atual != NULL) {
        printf("\nVoce esta na: %s", atual->nome);

        // Verifica se é um nó-folha (fim do caminho)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("\n[FIM] Voce alcancou um comodo sem saidas. Fim da exploracao!\n");
            break;
        }

        // Mostra opções disponíveis
        printf("\nCaminhos disponiveis:");
        if (atual->esquerda != NULL) printf("\n [e] Ir para a Esquerda (%s)", atual->esquerda->nome);
        if (atual->direita != NULL) printf("\n [d] Ir para a Direita (%s)", atual->direita->nome);
        printf("\n [s] Sair do jogo");
        
        printf("\nEscolha sua direcao: ");
        scanf(" %c", &escolha); // Espaço antes de %c para limpar o buffer

        if (escolha == 's') {
            printf("\nSaindo da mansao...\n");
            break;
        } else if (escolha == 'e' && atual->esquerda != NULL) {
            atual = atual->esquerda;
        } else if (escolha == 'd' && atual->direita != NULL) {
            atual = atual->direita;
        } else {
            printf("\n[!] Escolha invalida ou caminho inexistente.");
        }
    }
}

/**
 * Função: main
 * Objetivo: Monta o mapa inicial da mansão e inicia a exploração.
 */
int main() {
    // 1. Criando os cômodos (Nós)
    Sala *hall = criarSala("Hall de Entrada");
    Sala *salaEstar = criarSala("Sala de Estar");
    Sala *cozinha = criarSala("Cozinha");
    Sala *biblioteca = criarSala("Biblioteca");
    Sala *jardim = criarSala("Jardim");
    Sala *sotao = criarSala("Sotao");

    // 2. Montando a estrutura da árvore (Mapa)
    //         Hall
    //        /    \
    //   Estar      Cozinha
    //    /   \        \
    // Biblio Jardim    Sotao
    
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;
    
    cozinha->direita = sotao;

    // 3. Iniciando o jogo
    printf("========================================");
    printf("\n     DETECTIVE QUEST - ENIGMA STUDIOS   ");
    printf("\n========================================");
    
    explorarSalas(hall);

    // Dica: Em um sistema real, aqui deveria haver uma função para 
    // liberar a memória alocada (free), mas para o nível novato 
    // focaremos na estrutura.

    return 0;
}