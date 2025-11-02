// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Dados do Aluno -----
//  Nome: Aisha Azevedo Sampaio
//  email: 20251160023@ifba.edu.br
//  Matrícula: 20251160023
//  Semestre: 2 semestre
// #################################################

#include <stdio.h>    // Para printf/scanf (se houver) e outras funções de E/S
#include <string.h>   // Para funções de string (strlen, etc.)
#include <stdlib.h>   // <--- CORREÇÃO: Necessário para a função atoi()
#include "trabalho1.h" // Seus protótipos e structs

// ... seu código de q1 e quebraData

// Implementação da função somar (que estava faltando)
int somar(int a, int b) {
    // Implemente a lógica de soma aqui. Exemplo:
    return a + b;
}

// Implementação da função fatorial (que estava faltando)
int fatorial(int n) {
    // Implemente a lógica de fatorial aqui. Exemplo:
    if (n == 0)
        return 1;
    
    int res = 1;
    for (int i = 1; i <= n; i++) {
        res *= i;
    }
    return res;
}

// ... e assim por diante para quaisquer outras funções que o corretor.c exija

//Questão1 

int validaData(int dia, int mes, int ano) {
    int quantDias;

    if (mes < 1 || mes > 12) {
        return 0; // Mês inválido
    }

    // Verifica Ano Bissexto
    int bissexto = ((ano % 4 == 0) && (ano % 100 != 0)) || (ano % 400 == 0);

    // quant. máxima de dias para o mês
    if (mes == 2) {
        quantDias = bissexto ? 29 : 28;
    } 
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        quantDias = 30;
    } 
    else {
        quantDias = 31;
    }

    if (dia < 1 || dia > quantDias) {
        return 0; 
    }

    return 1; 
}

// FUNÇÃO Quebra da String de Data (dd/mm/aa ou d/m/aaaa)

DataQuebrada quebraData(char data[]){
    DataQuebrada dq;
    
    char sDia[5]; 
    char sMes[5];
    char sAno[5];
    int i; 
    int current_index = 0; // Ponteiro para percorrer a string 'data'
    
    dq.valido = 0; 
    
    // --- Processa o Dia (sDia) ---
    i = 0;
    while (data[current_index] != '/' && data[current_index] != '\0') {
        sDia[i] = data[current_index];  
        i++;
        current_index++;
    }

    if (i >= 1 && i <= 2) { 
        sDia[i] = '\0';
    } else {
        return dq; 
    }

    // Pula a barra '/' e verifica se a string não acabou
    if (data[current_index] != '/') {
        return dq; 
    }
    current_index++; 

    // --- Processa o Mês (sMes) ---
    i = 0;
    while (data[current_index] != '/' && data[current_index] != '\0') {
        sMes[i] = data[current_index];
        i++;
        current_index++;
    }

    if (i >= 1 && i <= 2) { 
        sMes[i] = '\0';
    } else {
        return dq; 
    }

    if (data[current_index] != '/') {
        return dq; 
    }
    current_index++; 
    

    // --- Processa o Ano (sAno) ---
    i = 0;
    while(data[current_index] != '\0') {
        sAno[i] = data[current_index];
        i++;
        current_index++;
    }

    if(i == 2 || i == 4){ 
        sAno[i] = '\0';
    } else {
        return dq; 
    }

    // Conversão das strings para inteiros 
    dq.iDia = atoi(sDia);
    dq.iMes = atoi(sMes);
    dq.iAno = atoi(sAno);   

    dq.valido = 1; // Quebra bem-sucedida!
    
    return dq;
}
// Função Principal (q1)

int q1(char data[]) {
    // quebra a string de data
    DataQuebrada data_processada = quebraData(data);
    
    if (!data_processada.valido) {
        return 0;
    }
    
    // Se a quebra foi bem-sucedida, chama a lógica de validação de calendário
    return validaData(data_processada.iDia, data_processada.iMes, data_processada.iAno);
}
