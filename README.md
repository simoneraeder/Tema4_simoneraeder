# 🔍 Detective Quest - Sistema de Investigação

![C](https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c)
![CS](https://img.shields.io/badge/Status-Complete-green?style=for-the-badge)
![Estácio](https://img.shields.io/badge/Instituição-Estácio-red?style=for-the-badge)

Projeto desenvolvido para a disciplina de **Estrutura de Dados**, simulando um jogo de investigação criminal. O software utiliza estruturas de dados avançadas para gerenciar o mapa de uma mansão, organizar evidências e associar suspeitos através de algoritmos de busca e espalhamento.

---

## 🗺️ Evolução do Desenvolvimento

O projeto foi estruturado em três níveis crescentes de complexidade técnica:

### 1. Nível Novato: O Mapa (Árvore Binária)
Foco na navegação hierárquica e alocação dinâmica.
* **Estrutura:** Árvore Binária simples.
* **Objetivo:** Representar os cômodos da mansão como nós.
* **Técnica:** Uso de ponteiros para conectar salas à esquerda e à direita, permitindo a exploração do Hall de Entrada até os nós-folha.

### 2. Nível Aventureiro: Coleta de Pistas (BST)
Implementação de organização automática de dados.
* **Estrutura:** Binary Search Tree (BST).
* **Objetivo:** Armazenar pistas coletadas durante a exploração.
* **Técnica:** Inserção ordenada via `strcmp`. Ao finalizar o jogo, as pistas são exibidas em **ordem alfabética** através de um percurso recursivo *In-Order*.

### 3. Nível Mestre: O Culpado (Tabela Hash)
Integração total de estruturas para tomada de decisão lógica.
* **Estrutura:** Tabela Hash com encadeamento.
* **Objetivo:** Associar cada pista a um suspeito (Mordomo, Cozinheira ou Jardineiro).
* **Técnica:** Função de espalhamento (Hash) para busca instantânea de evidências. O sistema valida a acusação do jogador verificando se há provas suficientes (mínimo de 2) contra o suspeito indicado.

---

## 🛠️ Tecnologias e Conceitos

* **Linguagem:** C (Padrão C11)
* **Gestão de Memória:** Alocação dinâmica com `malloc` e manipulação de ponteiros.
* **Algoritmos:** Recursividade para navegação em árvores e funções de espalhamento para Hash.

---

