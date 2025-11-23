#include <stdio.h>
#include <string.h>

#define TAMANHO 10
#define NUM_NAVIOS 5

//Jogo: Batalha Naval

char tabuleiro1[TAMANHO][TAMANHO];
char tabuleiro2[TAMANHO][TAMANHO];

void inicializarTabuleiro(char tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
}
void mostrarTabuleiro(char tabuleiro[TAMANHO][TAMANHO]) {
    printf("    ");
    for (int j = 0; j < TAMANHO; j++) {
        printf("%5d", j); // cada coluna ocupa 5 posições para formatar o tabuleiro
    }
    printf("\n");

    for (int i = 0; i < TAMANHO; i++) {
        printf("%2d  ", i);
        for (int j = 0; j < TAMANHO; j++) {
            printf("%5s", (tabuleiro[i][j] == 'N') ? "[ N ]" :
                          (tabuleiro[i][j] == '0') ? "[ 0 ]" :
                          (tabuleiro[i][j] == 'X') ? "[ X ]" : "[   ]");
        }
        printf("\n");
    }
}


void posicionarNavios(char tabuleiro[TAMANHO][TAMANHO], int jogador) {
    int tamanhos[NUM_NAVIOS] = {4, 3, 1, 1, 1};
    int linha, coluna;
    char direcao;

    printf("\nJogador %d, posicione seus navios:\n", jogador);
    mostrarTabuleiro(tabuleiro);
    
    for (int n = 0; n < NUM_NAVIOS; n++) {
        printf("Navio de tamanho %d\n", tamanhos[n]);
        printf("Linha inicial (0-9): ");
        scanf("%d", &linha);
        printf("Coluna inicial (0-9): ");
        scanf("%d", &coluna);
        printf("Direção (h para horizontal, v para vertical): ");
        scanf(" %c", &direcao);

        int valido = 1;
        for (int i = 0; i < tamanhos[n]; i++) {
            int l = linha + (direcao == 'v' ? i : 0);
            int c = coluna + (direcao == 'h' ? i : 0);
            if (l >= TAMANHO || c >= TAMANHO || tabuleiro[l][c] != ' ') {
                valido = 0;
                break;
            }
        }
        if (valido) {
            for (int i = 0; i < tamanhos[n]; i++) {
                int l = linha + (direcao == 'v' ? i : 0);
                int c = coluna + (direcao == 'h' ? i : 0);
                tabuleiro[l][c] = 'N';
            }
            printf("Navio posicionado com sucesso!\n");
            mostrarTabuleiro(tabuleiro); 
        } else {
            printf("Posição inválida. Tente novamente.\n");
            n--; 
        }
    }
}
// Realiza um ataque
int atacar(char tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    if (tabuleiro[linha][coluna] == 'N') {
        tabuleiro[linha][coluna] = '0';
        printf(" Acertou!\n");
        return 1;
    } else if (tabuleiro[linha][coluna] == ' ') {
        tabuleiro[linha][coluna] = 'X';
        printf("Errou!\n");
        return 0;
    } else {
        printf("Tiro inválido.\n");
        return 0;
    }
}

// Verifica se venceu todos os navios do oponente
int venceu(char tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            if (tabuleiro[i][j] == 'N') return 0;
        }
    }
    return 1;
}

int main() {
    int linha, coluna;
    int jogador = 1;

    inicializarTabuleiro(tabuleiro1);
    inicializarTabuleiro(tabuleiro2);

    posicionarNavios(tabuleiro1, 1);
    posicionarNavios(tabuleiro2, 2);

    while (1) {
        printf("\nJogador %d, sua vez de atirar!\n", jogador);
        printf("Linha (0-9): ");
        scanf("%d", &linha);
        printf("Coluna (0-9): ");
        scanf("%d", &coluna);

        if (jogador == 1) {
            atacar(tabuleiro2, linha, coluna);
            if (venceu(tabuleiro2)) {
                printf(" Jogador 1 venceu!\n");
                break;
            }
            jogador = 2;
        } else {
            atacar(tabuleiro1, linha, coluna);
            if (venceu(tabuleiro1)) {
                printf("Jogador 2 venceu!\n");
                break;
            }
            jogador = 1;
        }

        printf("\nTabuleiro do Jogador 1:\n");
        mostrarTabuleiro(tabuleiro1);
        printf("\nTabuleiro do Jogador 2:\n");
        mostrarTabuleiro(tabuleiro2);
    }

    return 0;
}
