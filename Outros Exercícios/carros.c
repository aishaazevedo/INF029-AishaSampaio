#include <stdio.h>
#define TAM 3

typedef struct {
    int ano;
    int chassi;
    float valor;
} Carro;

int menuGeral();
void listar_carros(Carro listaCarros[], int qtdCarros);
void cadastrar(Carro lista[], int qtd);
int excluir_carros(Carro listaCarros[], int *qtdCarros);
void atualizar_carros(Carro listaCarros[], int qtdCarros);

int main() {
    Carro listaCarros[TAM];
    int qtdCarros = 0;
    int opcao;

    do {
        opcao = menuGeral();
        switch (opcao) {
            case 0:
                printf("Saindo...\n");
                break;

            case 1: 
                if (qtdCarros == TAM) {
                    printf("Lista de carros está cheia!\n");
                } else {
                    cadastrar(listaCarros, qtdCarros);
                    qtdCarros++;
                }
                break;

            case 2: 
                if (qtdCarros == 0) {
                    printf("Não há carros cadastrados.\n");
                } else {
                    listar_carros(listaCarros, qtdCarros);
                }
                break;

            case 3: 
                if (qtdCarros == 0) {
                    printf("Não há carros cadastrados para atualizar.\n");
                } else {
                    atualizar_carros(listaCarros, qtdCarros);
                }
                break;

            case 4: 
                if (qtdCarros == 0) {
                    printf("Não há carros cadastrados para excluir.\n");
                } else {
                    if (excluir_carros(listaCarros, &qtdCarros)) {
                        printf("Carro excluído com sucesso!\n");
                    }
                }
                break;

            default:
                printf("Insira uma opção válida!\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}

int menuGeral() {
    int opcao;
    printf("\n===== MENU GERAL =====\n");
    printf("0 - Sair\n");
    printf("1 - Cadastrar\n");
    printf("2 - Listar\n");
    printf("3 - Atualizar\n");
    printf("4 - Excluir\n");
    printf("Escolha uma opção: ");
    if (scanf("%d", &opcao) != 1) {
        while (getchar() != '\n'); 
        return -1;
    }
    return opcao;
}

void listar_carros(Carro listaCarros[], int qtdCarros) {
    printf("\n----- Lista de Carros -----\n");
    for (int i = 0; i < qtdCarros; i++) {
        printf("Carro #%d -> Ano: %d | Chassi: %d | Valor: R$%.2f\n",
               i + 1, listaCarros[i].ano, listaCarros[i].chassi, listaCarros[i].valor);
    }
}

void cadastrar(Carro lista[], int qtd) {
    printf("\n--- Cadastrar Carro ---\n");
    printf("Ano: ");
    scanf("%d", &lista[qtd].ano);
    printf("Chassi: ");
    scanf("%d", &lista[qtd].chassi);
    printf("Valor: ");
    scanf("%f", &lista[qtd].valor);
}

int excluir_carros(Carro listaCarros[], int *qtdCarros) {
    int pos;
    printf("\nDigite o número do carro a excluir (1 a %d): ", *qtdCarros);
    scanf("%d", &pos);

    if (pos < 1 || pos > *qtdCarros) {
        printf("Número inválido.\n");
        return 0;
    }
    for (int i = pos - 1; i < *qtdCarros - 1; i++) {
        listaCarros[i] = listaCarros[i + 1];
    }

    (*qtdCarros)--;
    return 1;
}

void atualizar_carros(Carro listaCarros[], int qtdCarros) {
    int num;
    printf("\nDigite o número do carro que deseja atualizar (1 a %d): ", qtdCarros);
    scanf("%d", &num);

    if (num < 1 || num > qtdCarros) {
        printf("Número inválido.\n");
        return;
    }

    num--; 
    printf("Novo ano: ");
    scanf("%d", &listaCarros[num].ano);
    printf("Novo chassi: ");
    scanf("%d", &listaCarros[num].chassi);
    printf("Novo valor: ");
    scanf("%f", &listaCarros[num].valor);

    printf("Carro atualizado com sucesso!\n");
}

