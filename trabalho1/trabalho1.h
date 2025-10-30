<<<<<<< HEAD
// CORREÇÃO: Proteção de cabeçalho completa
#ifndef TRABALHO1_H
#define TRABALHO1_H

// Estrutura necessária para a função quebraData
// CORREÇÃO: Definição da struct (tipo) que estava faltando
=======
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

>>>>>>> 4c6c284a3b782e4c8972d9549c4f9c08d865dba9
typedef struct {
    int iDia;
    int iMes;
    int iAno;
<<<<<<< HEAD
    int valido; // Campo para indicar se a quebra foi bem-sucedida
=======
    int valido; 
>>>>>>> 4c6c284a3b782e4c8972d9549c4f9c08d865dba9
} DataQuebrada;


// PROTÓTIPOS DE FUNÇÕES
<<<<<<< HEAD
// Protótipos das funções que estão em trabalho1.c
=======
>>>>>>> 4c6c284a3b782e4c8972d9549c4f9c08d865dba9
int validaData(int dia, int mes, int ano);
DataQuebrada quebraData(char data[]);
int q1(char data[]);

<<<<<<< HEAD
// Protótipos de outras funções que você usará no trabalho (exemplo, para corretor.c)
=======
// Protótipos 
>>>>>>> 4c6c284a3b782e4c8972d9549c4f9c08d865dba9
int somar(int a, int b);
int fatorial(int n);
// ... adicione aqui todos os protótipos de funções globais

<<<<<<< HEAD
// CORREÇÃO: Fechamento da proteção de cabeçalho
#endif // TRABALHO1_H
=======
#endif // TRABALHO1_H
>>>>>>> 4c6c284a3b782e4c8972d9549c4f9c08d865dba9
