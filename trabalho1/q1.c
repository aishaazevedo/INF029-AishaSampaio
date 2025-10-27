
// trabalho1.h

#ifndef TRABALHO1_H
#define TRABALHO1_H

// Protótipo da função de validação de data
// Declara ao compilador que existe uma função com esta assinatura
int validaData(int dia, int mes, int ano);

#endif /* TRABALHO1_H */
// trabalho1.c

#include "trabalho1.h"

// trabalho1.c

int validaData(int dia, int mes, int ano) {
    int quantDias;

    if (mes < 1 || mes > 12) {
        return 0; // Mês inválido
    }
    // Lógica de ano bissexto para Fevereiro
    if (mes == 2) {
        if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
            quantDias = 29;
        } else {
            quantDias = 28;
        }
    } 
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        quantDias = 30;
    } 
    else {
        quantDias = 31;
    }

    if (dia < 1 || dia > quantDias) {
        return 0; // Dia inválido para o mês/ano
    }

    return 1; // Data válida
}

// ... Outras implementações de funções aqui ...

