#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10  // capacidade da mochila

// Definição da struct Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Vetor que representa a mochila
Item mochila[MAX_ITENS];
int totalItens = 0; // quantidade atual de itens na mochila

// Função para inserir um item
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\nMochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novoItem;
    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", novoItem.nome); // lê até encontrar enter
    printf("Digite o tipo do item (arma, munição, cura, ferramenta): ");
    scanf(" %[^\n]", novoItem.tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &novoItem.quantidade);

    mochila[totalItens] = novoItem;
    totalItens++;

    printf("\nItem adicionado com sucesso!\n");
}

// Função para remover um item pelo nome
void removerItem() {
    if (totalItens == 0) {
        printf("\nA mochila está vazia!\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item que deseja remover: ");
    scanf(" %[^\n]", nome);

    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            encontrado = 1;
            // desloca os itens para "fechar o buraco"
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            printf("\nItem '%s' removido com sucesso!\n", nome);
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem '%s' não encontrado na mochila.\n", nome);
    }
}

// Função para listar todos os itens da mochila
void listarItens() {
    if (totalItens == 0) {
        printf("\nA mochila está vazia!\n");
        return;
    }

    printf("\nItens na mochila:\n");
    for (int i = 0; i < totalItens; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Função para buscar um item pelo nome
void buscarItem() {
    if (totalItens == 0) {
        printf("\nA mochila está vazia!\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item que deseja buscar: ");
    scanf(" %[^\n]", nome);

    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem '%s' não está na mochila.\n", nome);
    }
}

// Função principal com menu interativo
int main() {
    int opcao;

    do {
        printf("\n===== MOCHILA DE SOBREVIVÊNCIA - CÓDIGO DA ILHA =====\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem();
                listarItens();
                break;
            case 2:
                removerItem();
                listarItens();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 5:
                printf("\nSaindo do jogo... até a próxima partida!\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

    } while (opcao != 5);

    return 0;
}
