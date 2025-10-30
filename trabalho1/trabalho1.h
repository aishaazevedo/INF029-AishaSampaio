// CORREÇÃO: Proteção de cabeçalho completa
#ifndef TRABALHO1_H
#define TRABALHO1_H

// Estrutura necessária para a função quebraData
// CORREÇÃO: Definição da struct (tipo) que estava faltando
typedef struct {
    int iDia;
    int iMes;
    int iAno;
    int valido; // Campo para indicar se a quebra foi bem-sucedida
} DataQuebrada;


// PROTÓTIPOS DE FUNÇÕES
// Protótipos das funções que estão em trabalho1.c
int validaData(int dia, int mes, int ano);
DataQuebrada quebraData(char data[]);
int q1(char data[]);

// Protótipos de outras funções que você usará no trabalho (exemplo, para corretor.c)
int somar(int a, int b);
int fatorial(int n);
// ... adicione aqui todos os protótipos de funções globais

// CORREÇÃO: Fechamento da proteção de cabeçalho
#endif // TRABALHO1_H