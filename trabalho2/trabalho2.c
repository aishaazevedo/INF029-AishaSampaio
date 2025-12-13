#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "trabalho2.h"

typedef struct {
    int *aux;   
    int qtd;    
    int tam;
} Estrutura;

Estrutura vetorPrincipal[TAM];

int posicao_valida(int pos) {
    if (pos >= 0 && pos < TAM) 
        return 1;
    else 
        return 0;
}

int existeEstrutura(Estrutura *e) {
    if (e->aux != NULL && e->tam > 0) 
        return 1;
     else 
        return 0;
    
}

int temEspaco(Estrutura *e) {
    if (e->qtd < e->tam) 
        return 1;
    else 
        return 0;
}

int BuscaValor(int posicao, int valor) {
    for (int i = 0; i < vetorPrincipal[posicao].qtd; i++) {
        if (vetorPrincipal[posicao].aux[i] == valor)
            return i;
    }
    return -1;
}

// Retorna total de elementos em todas as estruturas
int get_tam(Estrutura vet[]) {
    int tam = 0;
    for (int i = 0; i < TAM; i++) {
        tam += vet[i].qtd;
    }
    return tam;
}

// Insertion Sort para ordenar
void insertion_sort(int vet[], int tam) {
    for (int i = 1; i < tam; i++) {
        int atual = vet[i];
        int j = i - 1;
        while (j >= 0 && vet[j] > atual) {
            vet[j + 1] = vet[j];
            j--;
        }
        vet[j + 1] = atual;
    }
}

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho) {
    // se posição é um valor válido {entre 1 e 10}
    if (!posicao_valida(posicao))
        return POSICAO_INVALIDA;

    // a posicao pode já existir estrutura auxiliar
    if (existeEstrutura(&vetorPrincipal[posicao]))
        return JA_TEM_ESTRUTURA_AUXILIAR;

    // o tamanho nao pode ser menor que 1
    if (tamanho < 1)
        return TAMANHO_INVALIDO;
   // o tamanho ser muito grande
    int *p = malloc(tamanho * sizeof(int));
    if (p == NULL)
        return SEM_ESPACO_DE_MEMORIA;
    free(p);
    
    // deu tudo certo, crie
    vetorPrincipal[posicao].aux = malloc(tamanho * sizeof(int));
    vetorPrincipal[posicao].qtd = 0;
    vetorPrincipal[posicao].tam = tamanho;

    return SUCESSO;
}
/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
   
    posicao--;

    if (!posicao_valida(posicao))
        return POSICAO_INVALIDA;

    if (!existeEstrutura(&vetorPrincipal[posicao]))
        return SEM_ESTRUTURA_AUXILIAR;

    if (!temEspaco(&vetorPrincipal[posicao]))
        return SEM_ESPACO;

    vetorPrincipal[posicao].aux[vetorPrincipal[posicao].qtd] = valor;
    vetorPrincipal[posicao].qtd++;

    return SUCESSO;
}


/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    posicao--; 

    if (!posicao_valida(posicao))
        return POSICAO_INVALIDA;

    if (!existeEstrutura(&vetorPrincipal[posicao]))
        return SEM_ESTRUTURA_AUXILIAR;

    if (vetorPrincipal[posicao].qtd == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    vetorPrincipal[posicao].qtd--;

    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
  int retorno = SUCESSO;
    posicao--;

    if (!posicao_valida(posicao + 1))
        retorno = POSICAO_INVALIDA;
    else if (!existeEstrutura(posicao))
        retorno = SEM_ESTRUTURA_AUXILIAR;
    else if (!(vetorPrincipal[posicao].qtd))
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
    else {
        int encontrado = 0;

        // percorre todos os elementos
        for (int i = 0; i < vetorPrincipal[posicao].qtd; i++) {
            if (vetorPrincipal[posicao].aux[i] == valor) {
                // "apaga" o valor encontrado
                vetorPrincipal[posicao].aux[i] = 0;
                encontrado = 1;

                // desloca os elementos seguintes para não deixar buraco
                for (int j = i; j < vetorPrincipal[posicao].qtd - 1; j++) {
                    vetorPrincipal[posicao].aux[j] = vetorPrincipal[posicao].aux[j + 1];
                }

                vetorPrincipal[posicao].qtd--; // exclusão lógica
                break; // sai do laço após excluir
            }
        }

        if (!encontrado)
            retorno = ESTRUTURA_AUXILIAR_VAZIA; // ou outro código de "valor não encontrado"
    }

    return retorno;
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
    int retorno = 0;
    if (posicao < 1 || posicao > 10)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
        retorno = SUCESSO;

    return retorno;
}
/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{

    int retorno = SUCESSO;
    posicao--;

    if (!posicao_valida(posicao + 1))
        retorno = POSICAO_INVALIDA;
    else if (!existeEstrutura(posicao))
        retorno = SEM_ESTRUTURA_AUXILIAR;
    else {
        for (int i = 0; i < vetorPrincipal[posicao].qtd; i++) {
            vetorAux[i] = vetorPrincipal[posicao].aux[i];
        }
    }

    return retorno; 


/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    posicao--;
    if (!posicao_valida(posicao))
        return POSICAO_INVALIDA;
    if (!existeEstrutura(&vetorPrincipal[posicao]))
        return SEM_ESTRUTURA_AUXILIAR;

    for (int i = 0; i < vetorPrincipal[posicao].qtd; i++)
        vetorAux[i] = vetorPrincipal[posicao].aux[i];

    insertion_sort(vetorAux, vetorPrincipal[posicao].qtd);
    return SUCESSO;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int vazia = 1;
    int k = 0;

    for (int i = 0; i < TAM; i++)
    {
        if (existeEstrutura(i) && vetorPrincipal[i].qtd > 0)
        {
            vazia = 0;
            break;
        }
    }

    if (vazia)
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;

    // Copia os dados de todas as estruturas auxiliares para vetorAux
    for (int i = 0; i < TAM; i++)
    {
        if (existeEstrutura(i))
        {
            for (int j = 0; j < vetorPrincipal[i].qtd; j++)
            {
                vetorAux[k] = vetorPrincipal[i].aux[j];
                k++;
            }
        }
    }

    insertion_sort(vetorAux, k);

    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/

int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int vazia = 1;
    int k = 0;

    // Verifica se há pelo menos uma estrutura com dados
    for (int i = 0; i < TAM; i++) {
        if (existeEstrutura(&vetorPrincipal[i]) && vetorPrincipal[i].qtd > 0) {
            vazia = 0;
            break;
        }
    }

    if (vazia)
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;

    // Copia os dados de todas as estruturas auxiliares para vetorAux
    for (int i = 0; i < TAM; i++) {
        if (existeEstrutura(&vetorPrincipal[i])) {
            for (int j = 0; j < vetorPrincipal[i].qtd; j++) {
                vetorAux[k++] = vetorPrincipal[i].aux[j];
            }
        }
    }

    // Ordena os dados copiados
    insertion_sort(vetorAux, k);

    return SUCESSO;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
    posicao--;

    if (!posicao_valida(posicao))
        return POSICAO_INVALIDA;

    if (!existeEstrutura(posicao))
        return SEM_ESTRUTURA_AUXILIAR;

    int tamanhoResultante = vetorPrincipal[posicao].tam + novoTamanho;

    if (tamanhoResultante < 1)
        return NOVO_TAMANHO_INVALIDO;

    vetorPrincipal[posicao].aux = realloc(vetorPrincipal[posicao].aux, tamanhoResultante);
    if (vetorPrincipal[posicao].aux == NULL)
        return SEM_ESPACO_DE_MEMORIA;

    vetorPrincipal[posicao].tam = tamanhoResultante;

    if (vetorPrincipal[posicao].qtd > tamanhoResultante)
        vetorPrincipal[posicao].qtd = tamanhoResultante;

    return SUCESSO;
}



/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{
    posicao--;
    if (!posicao_valida(posicao))
        return POSICAO_INVALIDA;
    if (!existeEstrutura(&vetorPrincipal[posicao]))
        return SEM_ESTRUTURA_AUXILIAR;
    if (vetorPrincipal[posicao].qtd == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    return vetorPrincipal[posicao].qtd;
}


/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{
    No *inicio = malloc(sizeof(No));
    if (inicio == NULL)
        return NULL;

    inicio->prox = NULL;
    No *ultimo = inicio;

    for (int i = 0; i < TAM; i++)
    {
        if (existeEstrutura(i))
        {
            for (int j = 0; j < vetorPrincipal[i].qtd; j++)
            {
                No *novo = malloc(sizeof(No));
                if (novo == NULL) return NULL;

                novo->conteudo = vetorPrincipal[i].aux[j];
                novo->prox = NULL;
                ultimo->prox = novo;
                ultimo = novo;
            }
        }
    }

    if (inicio->prox == NULL)
    {
        free(inicio);
        return NULL;
    }

    return inicio;
}


/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
    int j = 0;

    for (No *atual = inicio->prox; atual != NULL; atual = atual->prox)
    {
        vetorAux[j] = atual->conteudo;
        j++;   
    }
}
/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
    No *atual = (*inicio);
    No *prox;

    while (atual != NULL){
        prox = atual->prox;
        free(atual);
        atual = prox;
    }

    *inicio = NULL;
}
/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar()
{
    for (int i = 0; i < TAM; i++)
    {
        vetorPrincipal[i].aux = NULL;
        vetorPrincipal[i].qtd = 0;
        vetorPrincipal[i].tam = 0;
    }
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar()
{
    for (int i = 0; i < TAM; i++)
    {
        if (vetorPrincipal[i].aux != NULL)
        {
            free(vetorPrincipal[i].aux);
            vetorPrincipal[i].aux = NULL;
            vetorPrincipal[i].tam = 0;
            vetorPrincipal[i].qtd = 0;
        }
    }
}
