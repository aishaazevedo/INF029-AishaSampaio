// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br
//  Aluno: Aisha Azevedo Sampaio

<<<<<<< HEAD
#include <stdio.h>
#include <string.h>

//renomeie o arquivo do include abaixo para trabalho1.h
#include "trabalho1.h"
=======
//  ----- Dados do Aluno -----
//  Nome: Aisha Azevedo Sampaio
//  email: 20251160023@ifba.edu.br
//  Matrícula: 20251160023
//  Semestre: 2 semestre
// #################################################

#include <stdio.h>    
#include <string.h>  
#include <stdlib.h>  
#include "trabalho1.h" 

int somar(int a, int b) {
    // Implemente a lógica de soma aqui. Exemplo:
    return a + b;
}

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


//Questão1 
>>>>>>> 4c6c284a3b782e4c8972d9549c4f9c08d865dba9

void testSomar();    //função utilizada para testes
void testFatorial(); //função utilizada para testes
void testQ1();
void testQ2();
void testQ3();
void testQ4();
void testQ5();
void testQ6();
void testQ7();

int main()
{
    //testSomar();
    //testFatorial();
    testQ1();
    /*testQ2();
    testQ3();
    testQ4();
    testQ5();
    testQ6();
    testQ7();*/
}

void testSomar()
{
    printf("%d\n", somar(3, 4) == 7);
    printf("%d\n", somar(-1, -3) == -4);
    printf("%d\n", somar(-6, 6) == 0);
    printf("%d\n", somar(74, 9) == 83);
    printf("%d\n", somar(30, -9) == 21);
    printf("%d\n", somar(-2, 8) == 6);
    printf("%d\n", somar(1000, 99) == 1099);

<<<<<<< HEAD
=======
DataQuebrada quebraData(char data[]){
    DataQuebrada dq;
    
    char sDia[5]; 
    char sMes[5];
    char sAno[5];
    int i; 
    int current_index = 0; // Ponteiro para percorrer a string 'data'
    
    dq.valido = 0; 
    
    // --- Processa o Dia 
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

    if (data[current_index] != '/') {
        return dq; 
    }
    current_index++; 

    // --- Processa o Mês 
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
    

    // --- Processa o Ano 
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
>>>>>>> 4c6c284a3b782e4c8972d9549c4f9c08d865dba9
}

void testFatorial()
{
    printf("%d\n", fatorial(3) == 6);
    printf("%d\n", fatorial(1) == 1);
    printf("%d\n", fatorial(5) == 120);
}

void testQ1()
{
    char str[11];
    strcpy(str, "29/02/2015");
    printf("%d\n", q1(str) == 0);
    strcpy(str, "29/02/2012");
    printf("%d\n", q1(str) == 1);
    strcpy(str, "9/13/2014");
    printf("%d\n", q1(str) == 0);
    strcpy(str, "45/4/2014");
    printf("%d\n", q1(str) == 0);
    strcpy(str, "/9/2014");
    printf("%d\n", q1(str) == 0);
}

