#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20  // Capacidade máxima de componentes na torre

// ===========================================
// DEFINIÇÃO DA ESTRUTURA DE DADOS
// ===========================================

// Estrutura para representar um componente da torre de resgate
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;


// ===========================================
// VARIÁVEIS GLOBAIS
// ===========================================

// Array de componentes
Componente torreComponentes[MAX_COMPONENTES];
int totalComponentes = 0;
Componente componentesCopia[MAX_COMPONENTES]; // Cópia para não modificar o vetor original

// Contadores de operações de ordenação e busca
long long comparacoesOrdenacao = 0;
long long comparacoesBusca = 0;
char statusOrdenacao[50] = "NAO ORDENADO";


// ===========================================
// FUNÇÕES AUXILIARES
// ===========================================

// Função para limpar o buffer de entrada.
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para exibir os componentes do array
void mostrarComponentes(Componente array[], int tamanho) {
    if (tamanho == 0) {
        printf("\nNenhum componente cadastrado.\n");
        return;
    }
    printf("\n--- Componentes da Torre de Resgate ---\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d. Nome: %s | Tipo: %s | Prioridade: %d\n",
               i + 1, array[i].nome, array[i].tipo, array[i].prioridade);
    }
    printf("---------------------------------------\n");
}

// ===========================================
// FUNÇÕES DE CADASTRO E REMOÇÃO
// ===========================================

// Função para adicionar um componente à torre
void adicionarComponente() {
    if (totalComponentes >= MAX_COMPONENTES) {
        printf("\nMochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    printf("\n--- Adicionar Componente ---\n");
    printf("Digite o nome do componente: ");
    fgets(torreComponentes[totalComponentes].nome, sizeof(torreComponentes[totalComponentes].nome), stdin);
    torreComponentes[totalComponentes].nome[strcspn(torreComponentes[totalComponentes].nome, "\n")] = 0;
    
    printf("Digite o tipo (ex: 'controle', 'suporte', 'propulsao'): ");
    fgets(torreComponentes[totalComponentes].tipo, sizeof(torreComponentes[totalComponentes].tipo), stdin);
    torreComponentes[totalComponentes].tipo[strcspn(torreComponentes[totalComponentes].tipo, "\n")] = 0;
    
    printf("Digite a prioridade (1 a 10): ");
    scanf("%d", &torreComponentes[totalComponentes].prioridade);
    limpar_buffer();
    
    totalComponentes++;
    printf("\nComponente adicionado com sucesso!\n");
    strcpy(statusOrdenacao, "NAO ORDENADO");
}

// Função para descartar um componente
void descartarComponente() {
    if (totalComponentes == 0) {
        printf("\nNao ha componentes para descartar.\n");
        return;
    }
    char nome[30];
    printf("\n--- Descartar Componente ---\n");
    printf("Digite o nome do componente que deseja descartar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    int encontrado = 0;
    for (int i = 0; i < totalComponentes; i++) {
        if (strcmp(torreComponentes[i].nome, nome) == 0) {
            encontrado = 1;
            // Desloca os itens subsequentes para a esquerda
            for (int j = i; j < totalComponentes - 1; j++) {
                torreComponentes[j] = torreComponentes[j + 1];
            }
            totalComponentes--;
            printf("\nComponente '%s' descartado com sucesso!\n", nome);
            strcpy(statusOrdenacao, "NAO ORDENADO");
            break;
        }
    }
    
    if (!encontrado) {
        printf("\nComponente '%s' nao encontrado.\n", nome);
    }
}

// ===========================================
// FUNÇÕES DE ORDENAÇÃO
// ===========================================

// Ordena os componentes por nome usando Bubble Sort
void bubbleSortNome(Componente array[], int tamanho) {
    comparacoesOrdenacao = 0;
    Componente temp;
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            comparacoesOrdenacao++;
            if (strcmp(array[j].nome, array[j+1].nome) > 0) {
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
    strcpy(statusOrdenacao, "ORDENADO POR NOME");
}

// Ordena os componentes por tipo usando Insertion Sort
void insertionSortTipo(Componente array[], int tamanho) {
    comparacoesOrdenacao = 0;
    for (int i = 1; i < tamanho; i++) {
        Componente chave = array[i];
        int j = i - 1;
        while (j >= 0 && strcmp(array[j].tipo, chave.tipo) > 0) {
            comparacoesOrdenacao++;
            array[j + 1] = array[j];
            j = j - 1;
        }
        comparacoesOrdenacao++;
        array[j + 1] = chave;
    }
    strcpy(statusOrdenacao, "ORDENADO POR TIPO");
}

// Ordena os componentes por prioridade usando Selection Sort
void selectionSortPrioridade(Componente array[], int tamanho) {
    comparacoesOrdenacao = 0;
    int indiceMinimo;
    Componente temp;
    for (int i = 0; i < tamanho - 1; i++) {
        indiceMinimo = i;
        for (int j = i + 1; j < tamanho; j++) {
            comparacoesOrdenacao++;
            if (array[j].prioridade < array[indiceMinimo].prioridade) {
                indiceMinimo = j;
            }
        }
        temp = array[indiceMinimo];
        array[indiceMinimo] = array[i];
        array[i] = temp;
    }
    strcpy(statusOrdenacao, "ORDENADO POR PRIORIDADE");
}

// ===========================================
// FUNÇÕES DE BUSCA
// ===========================================

// Busca binária por nome (requer array ordenado por nome)
int buscaBinariaPorNome(Componente array[], int tamanho, const char* nomeBusca) {
    comparacoesBusca = 0;
    int inicio = 0;
    int fim = tamanho - 1;
    
    while (inicio <= fim) {
        comparacoesBusca++;
        int meio = inicio + (fim - inicio) / 2;
        int resultadoComparacao = strcmp(array[meio].nome, nomeBusca);
        
        if (resultadoComparacao == 0) {
            return meio; // Item encontrado
        } else if (resultadoComparacao < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    
    return -1; // Item não encontrado
}


// ===========================================
// FUNÇÃO PRINCIPAL
// ===========================================

// Menu para organizar a mochila (ordenar componentes)
void menuOrganizar() {
    int opcao;
    clock_t inicio, fim;
    double tempo_execucao;

    do {
        printf("\n--- Organizar Mochila (Ordenar Componentes) ---\n");
        printf("1. Ordenar por Nome (Bubble Sort)\n");
        printf("2. Ordenar por Tipo (Insertion Sort)\n");
        printf("3. Ordenar por Prioridade (Selection Sort)\n");
        printf("0. Voltar\n");
        printf("\nEscolha uma opcao de ordenacao: ");
        scanf("%d", &opcao);
        limpar_buffer();

        if (totalComponentes == 0) {
            printf("\nCadastre os componentes primeiro!\n");
            opcao = 0; // Volta para o menu principal
        } else {
            memcpy(componentesCopia, torreComponentes, sizeof(Componente) * totalComponentes);
        }

        switch (opcao) {
            case 1:
                inicio = clock();
                bubbleSortNome(componentesCopia, totalComponentes);
                fim = clock();
                tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("\nOrdenacao por Nome (Bubble Sort) finalizada.\n");
                printf("Comparações: %lld\n", comparacoesOrdenacao);
                printf("Tempo de execucao: %.6f segundos\n", tempo_execucao);
                mostrarComponentes(componentesCopia, totalComponentes);
                break;
            case 2:
                inicio = clock();
                insertionSortTipo(componentesCopia, totalComponentes);
                fim = clock();
                tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("\nOrdenacao por Tipo (Insertion Sort) finalizada.\n");
                printf("Comparações: %lld\n", comparacoesOrdenacao);
                printf("Tempo de execucao: %.6f segundos\n", tempo_execucao);
                mostrarComponentes(componentesCopia, totalComponentes);
                break;
            case 3:
                inicio = clock();
                selectionSortPrioridade(componentesCopia, totalComponentes);
                fim = clock();
                tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("\nOrdenacao por Prioridade (Selection Sort) finalizada.\n");
                printf("Comparações: %lld\n", comparacoesOrdenacao);
                printf("Tempo de execucao: %.6f segundos\n", tempo_execucao);
                mostrarComponentes(componentesCopia, totalComponentes);
                break;
            case 0:
                printf("\nVoltando ao menu principal.\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);
}

int main() {
    int opcao;
    char nomeBusca[30];
    
    do {
        printf("\n=================================================\n");
        printf("PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
        printf("=================================================\n");
        printf("Itens na Mochila: %d/%d\n", totalComponentes, MAX_COMPONENTES);
        printf("Status da Ordenacao por Nome: %s\n", statusOrdenacao);
        printf("\n");
        printf("1. Adicionar Componente\n");
        printf("2. Descartar Componente\n");
        printf("3. Listar Componentes (Inventario)\n");
        printf("4. Organizar Mochila (Ordenar Componentes)\n");
        printf("5. Busca Binaria por Componente-Chave (por nome)\n");
        printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
        printf("\nEscolha sua opcao: ");
        scanf("%d", &opcao);
        limpar_buffer();
        
        switch (opcao) {
            case 1:
                adicionarComponente();
                break;
            case 2:
                descartarComponente();
                break;
            case 3:
                mostrarComponentes(torreComponentes, totalComponentes);
                break;
            case 4:
                menuOrganizar();
                break;
            case 5:
                if (totalComponentes == 0) {
                    printf("\nNao ha componentes para buscar.\n");
                    break;
                }
                if (strcmp(statusOrdenacao, "ORDENADO POR NOME") != 0) {
                    printf("\nATENCAO: A busca binaria so funciona com a mochila ordenada por nome (Opcao 4 -> Opcao 1).\n");
                    break;
                }
                printf("\n--- Busca Binaria por Componente-Chave ---\n");
                printf("Digite o nome do componente a buscar: ");
                fgets(nomeBusca, sizeof(nomeBusca), stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = 0;
                
                int indice = buscaBinariaPorNome(torreComponentes, totalComponentes, nomeBusca);
                
                if (indice != -1) {
                    printf("\nSUCESSO! Componente '%s' encontrado no indice %d.\n", nomeBusca, indice + 1);
                    printf("Comparações para a busca: %lld\n", comparacoesBusca);
                } else {
                    printf("\nComponente '%s' nao encontrado.\n", nomeBusca);
                    printf("Comparações para a busca: %lld\n", comparacoesBusca);
                }
                break;
            case 0:
                printf("\nAtivando a Torre de Fuga...\n");
                printf("Missao final encerrada. Ate a proxima partida!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }
        
    } while (opcao != 0);
    
    return 0;
}