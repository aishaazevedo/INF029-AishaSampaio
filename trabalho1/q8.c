#include <stdio.h>

#define JOGADOR_X 'X'
#define JOGADOR_O 'O'
#define EMPATE 'E'
#define CARACTERE_BRANCO '_'

#define QTD_LINHAS 3
#define QTD_COLUNAS 3

// Jogo da velha 

void exibir_tabuleiro(char tabuleiro[QTD_LINHAS][QTD_COLUNAS])
{
    int linha, coluna;

    // Formar colunas
    printf("\n  1 2 3\n");
    
    // Formar linhas
    for (linha = 0; linha < QTD_LINHAS; linha += 1)
    {
        printf("%c ", 'A' + linha); 
        
        for (coluna = 0; coluna < QTD_COLUNAS; coluna += 1)
            printf("%c ", tabuleiro[linha][coluna]);
        
        printf("\n");
    }
    printf("\n");
}

// Função do limpa buffer
void limpar_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(int argc, char const *argv[])
{
    int linha;
    int coluna;
    
    char posicao_str[10]; 
    int jogada_valida;
    int cont_jogadas = 0;
    int tam_tabuleiro = QTD_LINHAS * QTD_COLUNAS;
    char jogador_atual = JOGADOR_X;
    char ganhador = EMPATE;

    char tabuleiro[QTD_LINHAS][QTD_COLUNAS];
    
    // Inicializa o tabuleiro
    for (linha = 0; linha < QTD_LINHAS; linha += 1)
        for (coluna = 0; coluna < QTD_COLUNAS; coluna += 1)
            tabuleiro[linha][coluna] = CARACTERE_BRANCO;
    
  while (1)
    {
        exibir_tabuleiro(tabuleiro);
        
        printf("Jogador %c, sua vez. Informe a posicao (ex: A1): ", jogador_atual);
        // Lendo no máximo 9 caracteres
        if (scanf("%9s", posicao_str) != 1) { 
            printf("\nErro na leitura da entrada! Digite novamente.\n");
            limpar_stdin();
            continue;
        }

        int len = 0;
        // Percorrendo o array 
        while (posicao_str[len] != '\0' && len < 9) {
            len++;
        }
        if (len != 2)
        {
            printf("\nPosicao invalida! Use o formato correto. (ex: A1).\n");
            limpar_stdin(); // limpa buffer
            continue;
        }

        // Conversão para maiusculo 
        char char_linha = posicao_str[0];
        if (char_linha >= 'a' && char_linha <= 'c') {
            char_linha = char_linha - ('a' - 'A'); 
        }

        char char_coluna = posicao_str[1];

       // Cáculo p/ encontrar posicao no tabuleiro
        linha = char_linha - 'A'; 
        coluna = char_coluna - '1'; 

        // Validação da jogada: 
        if (linha < 0 || linha >= QTD_LINHAS || coluna < 0 || coluna >= QTD_COLUNAS)
        {
            printf("\nCoordenada invalida! Use A, B, C para linhas e 1, 2, 3 para colunas.\n");
            continue;
        }
        
        // Verifica se a posição já está ocupada
        if (tabuleiro[linha][coluna] == CARACTERE_BRANCO)
        {
            tabuleiro[linha][coluna] = jogador_atual;
            jogada_valida = 1; 
        }
        else
        {
            printf("\nEssa posicao ja foi preenchida, escolha outra.\n");
            jogada_valida = 0; 
        }

        if (!jogada_valida)
            continue;

        // linhas
        for (int l = 0; l < QTD_LINHAS; l += 1)
        {
            ganhador = jogador_atual;
            for (int c = 1; c < QTD_COLUNAS; c += 1)
            {
                if (tabuleiro[l][c] == CARACTERE_BRANCO || tabuleiro[l][c] != tabuleiro[l][c - 1]) 
                {
                    ganhador = EMPATE;
                    break;
                }
            }
            if (ganhador != EMPATE)
                goto fim_loop_verificacao;
        }

        // colunas
        if (ganhador == EMPATE)
        {
            for (int c = 0; c < QTD_COLUNAS; c += 1)
            {
                ganhador = jogador_atual;
                for (int l = 1; l < QTD_LINHAS; l += 1)
                {
                    if (tabuleiro[l][c] == CARACTERE_BRANCO || tabuleiro[l][c] != tabuleiro[l - 1][c]) 
                    {
                        ganhador = EMPATE;
                        break;
                    }
                }
                if (ganhador != EMPATE)
                    goto fim_loop_verificacao;
            }
        }

        // diagonal principal
        if (ganhador == EMPATE)
        {
            ganhador = jogador_atual;
            for (int i = 1; i < QTD_LINHAS; i += 1)
            {
                if (tabuleiro[i][i] == CARACTERE_BRANCO || tabuleiro[i][i] != tabuleiro[i - 1][i - 1]) 
                {
                    ganhador = EMPATE;
                    break;
                }
            }
        }

        // diagonal secundaria
        if (ganhador == EMPATE)
        {
            ganhador = jogador_atual;
            for (int i = 1; i < QTD_LINHAS; i += 1)
            {
                if (tabuleiro[i][QTD_COLUNAS - 1 - i] == CARACTERE_BRANCO || 
                    tabuleiro[i][QTD_COLUNAS - 1 - i] != tabuleiro[i - 1][QTD_COLUNAS - 1 - (i - 1)]) 
                {
                    ganhador = EMPATE;
                    break;
                }
            }
        }

        fim_loop_verificacao:; 

        // fim do jogo
        cont_jogadas += 1;

        if (ganhador != EMPATE || cont_jogadas == tam_tabuleiro)
            break;

        // Troca dos jogadores nas rodadas
        if (jogador_atual == JOGADOR_X)
            jogador_atual = JOGADOR_O;
        else
            jogador_atual = JOGADOR_X;
    }

    // Resultado
    exibir_tabuleiro(tabuleiro); 
    
    if (ganhador != EMPATE)
        printf("\nParabéns! O jogador %c ganhou!\n", ganhador);
    else
        printf("\nEmpate! O jogo deu velha. \n");

    return 0;
}
