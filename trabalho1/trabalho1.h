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
#ifndef TRABALHO1_H
#define TRABALHO1_H

#ifndef TRABALHO1_H
#define TRABALHO1_H

#include <stdlib.h> 

typedef struct {
    int iDia;
    int iMes;
    int iAno;
    int valido; /
} DataQuebrada;

// Protótipos das funções
int validaData(int dia, int mes, int ano);
DataQuebrada quebraData(char data[]);
int q1(char data[]); // Função principal 

#endif /* TRABALHO1_H */

