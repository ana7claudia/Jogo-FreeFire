#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10  // Capacidade máxima do vetor

// ===========================================
// DEFINIÇÃO DAS ESTRUTURAS DE DADOS
// ===========================================

// Estrutura para representar um item na mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Estrutura para um nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;


// ===========================================
// VARIÁVEIS GLOBAIS
// ===========================================

// Para a implementação com vetor (array)
Item mochilaVetor[MAX_ITENS];
int totalItensVetor = 0;

// Para a implementação com lista encadeada
No* mochilaLista = NULL;

// Contadores de operações de busca
long long comparacoesSequencialVetor = 0;
long long comparacoesBinariaVetor = 0;
long long comparacoesSequencialLista = 0;


// ===========================================
// FUNÇÕES AUXILIARES
// ===========================================

// Função para limpar o buffer de entrada.
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ===========================================
// FUNÇÕES PARA O VETOR (LISTA SEQUENCIAL)
// ===========================================

// Inserir um item no vetor
void inserirItemVetor() {
    if (totalItensVetor >= MAX_ITENS) {
        printf("\nMochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }
    limpar_buffer();
    printf("\n--- Adicionar Item (Vetor) ---\n");
    printf("Digite o nome do item: ");
    fgets(mochilaVetor[totalItensVetor].nome, sizeof(mochilaVetor[totalItensVetor].nome), stdin);
    mochilaVetor[totalItensVetor].nome[strcspn(mochilaVetor[totalItensVetor].nome, "\n")] = 0;
    
    printf("Digite o tipo do item (arma, municao, cura, ferramenta): ");
    fgets(mochilaVetor[totalItensVetor].tipo, sizeof(mochilaVetor[totalItensVetor].tipo), stdin);
    mochilaVetor[totalItensVetor].tipo[strcspn(mochilaVetor[totalItensVetor].tipo, "\n")] = 0;
    
    printf("Digite a quantidade: ");
    scanf("%d", &mochilaVetor[totalItensVetor].quantidade);
    limpar_buffer();
    
    totalItensVetor++;
    printf("\nItem adicionado com sucesso!\n");
}

// Remover um item do vetor por nome
void removerItemVetor() {
    if (totalItensVetor == 0) {
        printf("\nA mochila esta vazia!\n");
        return;
    }
    
    char nome[30];
    limpar_buffer();
    printf("\n--- Remover Item (Vetor) ---\n");
    printf("Digite o nome do item que deseja remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;
    
    int encontrado = 0;
    for (int i = 0; i < totalItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            encontrado = 1;
            // Desloca os itens subsequentes para a esquerda
            for (int j = i; j < totalItensVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }
            totalItensVetor--;
            printf("\nItem '%s' removido com sucesso!\n", nome);
            break;
        }
    }
    
    if (!encontrado) {
        printf("\nItem '%s' nao encontrado na mochila.\n", nome);
    }
}

// Listar todos os itens do vetor
void listarItensVetor() {
    if (totalItensVetor == 0) {
        printf("\nA mochila (vetor) esta vazia!\n");
        return;
    }
    
    printf("\n--- Itens na Mochila (Vetor) ---\n");
    for (int i = 0; i < totalItensVetor; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
                i + 1, mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

// Buscar um item no vetor usando busca sequencial
void buscarSequencialVetor() {
    if (totalItensVetor == 0) {
        printf("\nA mochila esta vazia!\n");
        return;
    }
    
    char nome[30];
    limpar_buffer();
    printf("\n--- Busca Sequencial no Vetor ---\n");
    printf("Digite o nome do item que deseja buscar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;
    
    comparacoesSequencialVetor = 0;
    int encontrado = 0;
    for (int i = 0; i < totalItensVetor; i++) {
        comparacoesSequencialVetor++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            printf("\nItem '%s' encontrado!\n", mochilaVetor[i].nome);
            printf("Tipo: %s | Quantidade: %d\n", mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("\nItem '%s' nao esta na mochila.\n", nome);
    }
    printf("Comparacoes realizadas: %lld\n", comparacoesSequencialVetor);
}

// Ordenar o vetor usando Bubble Sort (ordem alfabética por nome)
void ordenarVetor() {
    if (totalItensVetor <= 1) {
        printf("\nNao ha itens suficientes para ordenar.\n");
        return;
    }
    
    printf("\n--- Ordenando o Vetor (Bubble Sort) ---\n");
    for (int i = 0; i < totalItensVetor - 1; i++) {
        for (int j = 0; j < totalItensVetor - i - 1; j++) {
            // Compara os nomes e troca se estiverem fora de ordem
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    printf("Vetor ordenado com sucesso!\n");
}

// Buscar um item no vetor usando busca binária (necessita de vetor ordenado)
void buscarBinariaVetor() {
    if (totalItensVetor == 0) {
        printf("\nA mochila esta vazia!\n");
        return;
    }
    
    char nome[30];
    limpar_buffer();
    printf("\n--- Busca Binaria no Vetor ---\n");
    printf("OBS: O vetor deve estar ordenado para que a busca funcione corretamente.\n");
    printf("Digite o nome do item que deseja buscar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;
    
    comparacoesBinariaVetor = 0;
    int inicio = 0;
    int fim = totalItensVetor - 1;
    int encontrado = 0;
    
    while (inicio <= fim) {
        comparacoesBinariaVetor++;
        int meio = inicio + (fim - inicio) / 2;
        int resultadoComparacao = strcmp(mochilaVetor[meio].nome, nome);
        
        if (resultadoComparacao == 0) {
            printf("\nItem '%s' encontrado!\n", mochilaVetor[meio].nome);
            printf("Tipo: %s | Quantidade: %d\n", mochilaVetor[meio].tipo, mochilaVetor[meio].quantidade);
            encontrado = 1;
            break;
        } else if (resultadoComparacao < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    
    if (!encontrado) {
        printf("\nItem '%s' nao esta na mochila.\n", nome);
    }
    printf("Comparacoes realizadas: %lld\n", comparacoesBinariaVetor);
}


// ===========================================
// FUNÇÕES PARA A LISTA ENCAIXEADA
// ===========================================

// Inserir um item na lista encadeada
void inserirItemLista() {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("\nErro de alocacao de memoria!\n");
        return;
    }
    
    limpar_buffer();
    printf("\n--- Adicionar Item (Lista Encadeada) ---\n");
    printf("Digite o nome do item: ");
    fgets(novoNo->dados.nome, sizeof(novoNo->dados.nome), stdin);
    novoNo->dados.nome[strcspn(novoNo->dados.nome, "\n")] = 0;
    
    printf("Digite o tipo do item (arma, municao, cura, ferramenta): ");
    fgets(novoNo->dados.tipo, sizeof(novoNo->dados.tipo), stdin);
    novoNo->dados.tipo[strcspn(novoNo->dados.tipo, "\n")] = 0;
    
    printf("Digite a quantidade: ");
    scanf("%d", &novoNo->dados.quantidade);
    limpar_buffer();
    
    novoNo->proximo = NULL;
    
    if (mochilaLista == NULL) {
        mochilaLista = novoNo;
    } else {
        No* atual = mochilaLista;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoNo;
    }
    printf("\nItem adicionado com sucesso!\n");
}

// Remover um item da lista encadeada por nome
void removerItemLista() {
    if (mochilaLista == NULL) {
        printf("\nA mochila esta vazia!\n");
        return;
    }
    
    char nome[30];
    limpar_buffer();
    printf("\n--- Remover Item (Lista Encadeada) ---\n");
    printf("Digite o nome do item que deseja remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;
    
    No* atual = mochilaLista;
    No* anterior = NULL;
    int encontrado = 0;
    
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            encontrado = 1;
            if (anterior == NULL) { // Remove o primeiro nó
                mochilaLista = atual->proximo;
            } else { // Remove um nó do meio ou do fim
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("\nItem '%s' removido com sucesso!\n", nome);
            break;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    
    if (!encontrado) {
        printf("\nItem '%s' nao encontrado na mochila.\n", nome);
    }
}

// Listar todos os itens da lista encadeada
void listarItensLista() {
    if (mochilaLista == NULL) {
        printf("\nA mochila (lista encadeada) esta vazia!\n");
        return;
    }
    
    printf("\n--- Itens na Mochila (Lista Encadeada) ---\n");
    No* atual = mochilaLista;
    int i = 1;
    while (atual != NULL) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
                i++, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

// Buscar um item na lista encadeada usando busca sequencial
void buscarSequencialLista() {
    if (mochilaLista == NULL) {
        printf("\nA mochila esta vazia!\n");
        return;
    }
    
    char nome[30];
    limpar_buffer();
    printf("\n--- Busca Sequencial na Lista Encadeada ---\n");
    printf("Digite o nome do item que deseja buscar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;
    
    comparacoesSequencialLista = 0;
    No* atual = mochilaLista;
    int encontrado = 0;
    
    while (atual != NULL) {
        comparacoesSequencialLista++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("\nItem '%s' encontrado!\n", atual->dados.nome);
            printf("Tipo: %s | Quantidade: %d\n", atual->dados.tipo, atual->dados.quantidade);
            encontrado = 1;
            break;
        }
        atual = atual->proximo;
    }
    
    if (!encontrado) {
        printf("\nItem '%s' nao esta na mochila.\n", nome);
    }
    printf("Comparacoes realizadas: %lld\n", comparacoesSequencialLista);
}

// Função principal com menu interativo
int main() {
    int opcao;
    
    do {
        printf("\n===========================================\n");
        printf("MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
        printf("===========================================\n");
        printf("Itens na Mochila: %d/%d\n", totalItensVetor, MAX_ITENS);
        printf("\n");
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("4. Buscar Item por Nome\n");
        printf("5. Sair\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        limpar_buffer();
        
        switch (opcao) {
            case 1: inserirItemVetor(); break;
            case 2: removerItemVetor(); break;
            case 3: listarItensVetor(); break;
            case 4: buscarSequencialVetor(); break;
            case 5: 
                printf("\nSaindo do jogo... ate a proxima partida!\n");
                break;
            default: printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 5);
    
    // Libera a memória alocada para a lista encadeada no final do programa
    No* atual = mochilaLista;
    while (atual != NULL) {
        No* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    
    return 0;
}