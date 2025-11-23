// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Aisha Azevedo Sampaio
//  email: 20251160023@ifba.edu.br
//  Matrícula: 20251160023
//  Semestre: 2 semestre

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016 - 17/10/2025

// #################################################

#include <stdio.h>
#include "trabalho1.h" 
#include <stdlib.h>
#include <string.h>

DataQuebrada quebraData(char data[]);
int diasNoMes(int mes, int ano);
int datafinalehmaior(DataQuebrada dqInicial, DataQuebrada dqFinal);
void configurar(char *texto);
int extrairNum(int num, int* entrada);
/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
  int datavalida = 1;

  // quebrar a string data em strings sDia, sMes, sAno
  int quantDias;
  DataQuebrada dq = quebraData(data);

  if (dq.iDia <= 0 || dq.iDia > 31)
    datavalida = 0;

  if (dq.iMes <= 0 || dq.iMes > 12)
    datavalida = 0;

  if (dq.iAno < 0 || dq.iAno > 2025)
    datavalida = 0;

  int bissexto = ((dq.iAno % 4 == 0) && (dq.iAno % 100 != 0)) || (dq.iAno % 400 == 0);

    // quant. máxima de dias para o mês
    if (dq.iMes == 2) {
        quantDias = bissexto ? 29 : 28;
    } 
    else if (dq.iMes == 4 || dq.iMes == 6 || dq.iMes == 9 || dq.iMes == 11) {
        quantDias = 30;
    } 
    else {
        quantDias = 31;
    }

    if (dq.iDia < 1 || dq.iDia > quantDias) {
        datavalida = 0; 
    }

  if (datavalida)
    return 1;
  else
    return 0;
}

/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
int diasNoMes(int mes, int ano) {
    // Retorno qualquer para o linker encontrar a função
    return 30; 
}

//testando 
int datafinalehmaior(DataQuebrada dqInicial, DataQuebrada dqFinal)
{
    if (dqFinal.iAno > dqInicial.iAno) return 1;
    if (dqFinal.iAno < dqInicial.iAno) return 0;

    // Anos iguais
    if (dqFinal.iMes > dqInicial.iMes) return 1;
    if (dqFinal.iMes < dqInicial.iMes) return 0;

    // Meses iguais
    if (dqFinal.iDia >= dqInicial.iDia) return 1;
    return 0;
}


DiasMesesAnos q2(char datainicial[], char datafinal[])
{

    //calcule os dados e armazene nas três variáveis a seguir
    DiasMesesAnos dma;

    if (q1(datainicial) == 0){
      dma.retorno = 2;
      return dma;
    }else if (q1(datafinal) == 0){
      dma.retorno = 3;
      return dma;
    }else{
      //verifique se a data final não é menor que a data inicial
    DataQuebrada dqInicial = quebraData(datainicial);
    DataQuebrada dqFinal = quebraData(datafinal);

    if (!datafinalehmaior(dqInicial, dqFinal)) {
        dma.retorno = 4;
        return dma;
    }
      //calcule a distancia entre as datas
    dma.qtdDias = dqFinal.iDia - dqInicial.iDia;
    dma.qtdMeses = dqFinal.iMes - dqInicial.iMes;
    dma.qtdAnos = dqFinal.iAno - dqInicial.iAno;

    if (dma.qtdMeses < 0) {
        dma.qtdMeses += 12;
        dma.qtdAnos--;
    }

    if (dma.qtdDias < 0) {
        if (dqFinal.iMes == 1) {
            dma.qtdDias += diasNoMes(12, dqFinal.iAno - 1);
        } else {
            dma.qtdDias += diasNoMes(dqFinal.iMes - 1, dqFinal.iAno);
        }
        dma.qtdMeses--;
    }

      //se tudo der certo
      dma.retorno = 1;
      return dma;
      
    }
    
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0;

    
    if (isCaseSensitive != 1) { 
        for (int i = 0; texto[i] != '\0'; i++) {
            if (texto[i] == c || texto[i] == c - 32 || texto[i] == c + 32) {
                qtdOcorrencias++;
            }
        }
    }
    else { 
        for (int i = 0; texto[i] != '\0'; i++) {
            if (texto[i] == c) {
                qtdOcorrencias++;
            }
        }
    }

    return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
    int qtdOcorrencias = 0;
    int i, j, k, tamanho;

    configurar(strTexto);
    configurar(strBusca);

    for (tamanho = 0; strBusca[tamanho]; tamanho++);
    for (i = 0, k = 0; strTexto[i] != '\0'; i++) {
        for (j = 0; strBusca[j] != '\0'; j++) {
            if (strTexto[i + j] != strBusca[j]) {
                break;
            }
        }

        if (tamanho == j) {
            posicoes[k++] = i + 1;
            posicoes[k++] = i + tamanho;
            qtdOcorrencias++;
            i++;
        }
    }
    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
    
int invertido = 0;
    int resto;
    
    while (num > 0){
        resto = num % 10;
        invertido = invertido * 10 + resto;
        num = num/10;
    }
    num = invertido;

    return num;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
    int qtdOcorrencias = 0;
    int digitosBase[50];
    int digitosBusca[50];
    int tamBase = 0;
    int Busca = 0;

    tamBase = extrairNum(numerobase, digitosBase);
    Busca = extrairNum(numerobusca, digitosBusca);

    if (Busca == 0 || Busca > tamBase) {
        return 0;
    }

    for (int i = 0; i <= tamBase - Busca;) {
        int encontrado = 1;
        for (int j = 0; j < Busca; j++) {
            if (digitosBase[i + j] != digitosBusca[j]) {
                encontrado = 0;
                break;
            }
        }
        if (encontrado) {
            qtdOcorrencias++;   
            i = i + Busca;
        } else {
            i++;
        }
    }
    return qtdOcorrencias;
}

/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

  int q7(char matriz[8][10], char palavra[5])
 {
    int achou = 0;
    int i, j, k, tam_p;
    char invertido[5];
    for (tam_p = 0; palavra[tam_p]; tam_p++);
    for (i = tam_p - 1, j = 0; i >= 0; i--, j++) {
        invertido[j] = palavra[i];
    }
    // sentido horizontal para frente e para trás
    for (i = 0; i < 8 && !achou; i++) {
        for (j = 0; j < 10 - tam_p + 1 && !achou; j++) {
            for (k = 0; k < tam_p; k++) {
                if (matriz[i][j + k] != palavra[k] && matriz[i][j + k] != invertido[k]) {
                    break;
                }
            }
            if (k == tam_p)
                achou = 1;
        }
    }
    // sentido vertical para cima e para baixo
    for (i = 0; i < 10 && !achou; i++) {
        for (j = 0; j < 8 - tam_p + 1 && !achou; j++) {
            for (k = 0; k < tam_p; k++) {
                if (matriz[j + k][i] != palavra[k] && matriz[j + k][i] != invertido[k]) {
                    break;
                }
            }
            if (k == tam_p)
                achou = 1;
        }
    }
    // diagonal
    for (int l = 0; l < 8 - tam_p && !achou; l++) {
        for (int c = 0; c < 10 - tam_p && !achou; c++) {
            for (i = l; i < 8 - tam_p + 1 && !achou; i++) {
                for (j = c; j < 10 - tam_p + 1 && !achou; j++) {
                    for (k = 0; k < tam_p && j + k < 10; k++) {
                        if (matriz[i + k][j + k] != palavra[k] && matriz[i + k][j + k] != invertido[k])
                            break;
                    }
                    if (k == tam_p)
                        achou = 1;
                }
            }
        }
    }
    for (int l = 0; l < 8 - tam_p && !achou; l++) {
        for (int c = 10 - 1; c >= 0 && !achou; c--) {
            for (i = l; i < 8 - tam_p + 1 && !achou; i++) {
                for (j = c; j >= 0 && !achou; j--) {
                    for (k = 0; k < tam_p; k++) {
                        if (matriz[i + k][j - k] != palavra[k] && matriz[i + k][j - k] != invertido[k])
                            break;
                    }
                    if (k == tam_p)
                        achou = 1;
                }
            }
        }
    }
     return achou;
 }

DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
}
int extrairNum(int num, int* entrada) {
    int tempEntrada[50];
    int count = 0;

    if (num == 0) {
        entrada[0] = 0;
        return 1;
    }

    while (num > 0) {
        tempEntrada[count] = (int)(num % 10);
        num = num / 10;
        count++;
    }

    for (int i = 0; i < count; i++) {
        entrada[i] = tempEntrada[count - 1 - i];
    }

    return count;
}
 void configurar(char *texto) {
    int i, j, tam;
    char com_acento[] = "ÄÁÂÀÃäáâàãÉÊËÈéêëèÍÎÏÌíîïìÖÓÔÒÕöóôòõÜÚÛÙüúûù";
    char sem_acento[] = "AAAAAAAAAAaaaaaaaaaaEEEEEEEEeeeeeeeeIIIIIIIIiiiiiiiiOOOOOOOOOOooooooooooUUUUUUUUuuuuuuuu";
    for(tam = 0; texto[tam] != '\0'; tam++);
    for(i = 0; texto[i] != '\0'; i++){
        for(j = 0; com_acento[j] != '\0'; j++) {
            if(texto[i] == com_acento[j] && texto[i+1] == com_acento[j+1]) {
                texto[i] = sem_acento[j];
                for (int k = i + 1; k < tam - 1; k++) {
                    texto[k] = texto[k+1];
                }
                texto[tam - 1] = '\0';
                tam--;
                break;
            }
        }
    }
}