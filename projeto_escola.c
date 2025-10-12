// Revisar CRUD matriculados + funcao main
// adicionar funcionalidades ao modulo da disciplina 
// verificar se o código intregou completamente (cpf barra a continuidade do código, então não consegui verificar)
// Corrgir a validação do cpf

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define ALUNO 1
#define PROFESSOR 2

#define MAX_PESSOAS 200
#define MAX_DISCI 100
#define MAX_ALUNOS_DISCI 50
#define NOME_SIZE 100
#define CPF_SIZE 15
#define MATRICULA_INICIAL 1000

// aliases / compatibilidade
#define TAM MAX_PESSOAS
#define TAM_DISCIPLINA MAX_DISCI

// códigos de retorno (adicionados os que faltavam)
#define LISTA_CHEIA 1
#define LISTA_VAZIA 0
#define CAD_SUCESSO 1
#define MATRICULA_INVALIDA -1
#define ATUALIZACAO_SUCESSO 2
#define EXCLUSAO_SUCESSO 3
#define MATRICULA_INEXISTENTE -3

#define CODIGO_INVALIDO -4
#define CAD_DISCIPLINA_SUCESSO 5
#define DISCIPLINA_INEXISTENTE -5
#define EXCLUSAO_DISCIPLINA_SUCESSO 6

// --- IMPLEMENTAÇÃO AUXILIAR DE FUNÇÃO NÃO-PADRÃO (para strcasestr) ---
char *strcasestr_custom(const char *haystack, const char *needle) {
    if (!*needle) return (char *)haystack;
    for (; *haystack; ++haystack) {
        if (toupper((unsigned char)*haystack) == toupper((unsigned char)*needle)) {
            const char *h, *n;
            for (h = haystack, n = needle; *h && *n && (toupper((unsigned char)*h) == toupper((unsigned char)*n)); ++h, ++n);
            if (!*n) return (char *)haystack;
        }
    }
    return NULL;
}

// --- estruturas ---
typedef struct {
    int dia, mes, ano;
} Data;

typedef struct {
    int matricula;
    char nome[NOME_SIZE];
    char sexo;
    Data dataNascimento;
    char cpf[CPF_SIZE];
    int ativo; // 1= ativo, 0 = excluido
    int tipo;  // 1 = aluno, 2 = professor
} Matriculado;

typedef struct {
    char nome[100];
    char codigo[10]; // ex: "INFO201"
    int semestre;
    char professor[50];
    int alunosMatriculados[MAX_ALUNOS_DISCI];
    int qtdAlunos;
    int ativo;
} Disciplina;

// --- variáveis globais ---
Matriculado vetor[MAX_PESSOAS];
Disciplina disciplinas[MAX_DISCI];
int proximaMatricula = MATRICULA_INICIAL;
int qtdMatriculados = 0;
int qtdDisciplinas = 0;

// --- protótipos ---
int menuGeral();
int menuListagens();
int menuMatriculados(char c[15]);
int menuDisciplina();

int cadastrarPessoa(Matriculado lista[], int *qtd, int tipo);
int excluirPessoa(Matriculado vetor[], int *qtdPessoas, int tipo);
int atualizarPessoa(Matriculado vetor[], int qtdPessoas, int tipo);

int cadastrarDisciplina(Disciplina listaDisciplina[], int *qtdDisciplina);
void listarDisciplina(Disciplina listaDisciplina[], int qtdDisciplina);
int excluirDisciplina(Disciplina listaDisciplina[], int *qtdDisciplina);
void listarDisciplinaCompleta(Disciplina disciplinas[], int qtdDisciplinas, Matriculado vetor[], int qtdPessoas);
int inserirAlunoDisciplina(Disciplina disciplinas[], int qtdDisciplinas, char codigo[], int matAluno);
int excluirAlunoDisciplina(Disciplina disciplinas[], int qtdDisciplinas, char codigo[], int matAluno);

int ehBissexto(int ano);
int validar_data_struct(Data d);
int validar_nome(char nome[]);
int validar_sexo(char sexo);
int validar_matricula_unica(int matricula);
int validar_CPF(const char cpf[]);
int validar_codigoDisciplina(const char codigo[]);

void listarPessoasPorSexo(Matriculado vetor[], int qtdPessoas, int tipo, char sexo);
void ordenarPessoasPorNome(Matriculado vetor[], int qtdPessoas, int tipo);
void ordenarPessoasPorDataNascimento(Matriculado vetor[], int qtdPessoas, int tipo);
void listarAniversariantesDoMes(Matriculado vetor[], int qtdPessoas);
void buscarPessoasPorString(Matriculado vetor[], int qtdPessoas, char busca[]);
void listarPessoas(Matriculado vetor[], int qtdPessoas, int tipo);
int buscarPessoa(Matriculado vetor[], int qtdPessoas, int matricula);
int ler_opcao(int min, int max);
int gerarMatricula();

// NOVAS FUNÇÕES PARA A LISTAGEM
int contarDisciplinasMatriculadas(int matricula); // retorna quantas disciplinas o aluno (matricula) está matriculado
int listarAlunosMenos3Disciplinas(); // lista e retorna quantidade encontrada

// --- implementações ---

int menuGeral() {
    int opcao;
    printf("\nMENU GERAL \n");
    printf("0 - Sair\n");
    printf("1 - Aluno\n");
    printf("2 - Professor\n");
    printf("3 - Disciplina\n");
    printf("4 - Listagens\n");
    printf("Escolha uma opção: ");
    if (scanf("%d", &opcao) != 1) {
        while (getchar() != '\n');
        return -1;
    }
    return opcao;
}

int menuMatriculados(char c[15]) {
    int opcao;
    printf("\nMENU %s\n", c);
    printf("0 - Voltar\n");
    printf("1 - Cadastrar %s\n", c);
    printf("2 - Listar %s\n", c);
    printf("3 - Atualizar %s\n", c);
    printf("4 - Excluir %s\n", c);
    printf("Escolha uma opção: ");
    if (scanf("%d", &opcao) != 1) {
        while (getchar() != '\n');
        return -1;
    }
    return opcao;
}

int menuDisciplina() {
    int opcao;
    printf("\nMENU DISCIPLINA \n");
    printf("0 - Voltar\n");
    printf("1 - Cadastrar Disciplina\n");
    printf("2 - Listar Disciplinas\n");
    printf("3 - Excluir Disciplina\n");
    printf("4 - Inserir aluno em disciplina\n");
    printf("5 - Remover aluno de disciplina\n");
    printf("Escolha uma opção: ");
    if (scanf("%d", &opcao) != 1) {
        while (getchar() != '\n');
        return -1;
    }
    return opcao;
}

int menuListagens() {
    int opcao;
    printf("\nMENU LISTAGENS \n");
    printf("0 - Voltar\n");
    printf("1 - Aniversariantes do mês\n");
    printf("2 - Disciplinas com mais de 40 alunos\n");
    printf("3 - Alunos matriculados em menos de 3 disciplinas\n");
    printf("4 - Listar por sexo\n");
    printf("Escolha uma opção: ");
    if (scanf("%d", &opcao) != 1) {
        while (getchar() != '\n');
        return -1;
    }
    return opcao;
}

// --- utilidades ---
int ehBissexto(int ano){
    if((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) return 1;
    else return 0;
}

int validar_data_struct(Data d){
    if(d.ano < 1900 || d.ano > 2100) return 0;
    if(d.mes < 1 || d.mes > 12) return 0;
    int diasPorMes[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if(d.mes == 2 && ehBissexto(d.ano)) diasPorMes[2] = 29;
    if(d.dia < 1 || d.dia > diasPorMes[d.mes]) return 0;
    return 1;
}

int validar_nome(char nome[]){
    if(strlen(nome) < 3) return 0;
    for(int i = 0; nome[i] != '\0'; i++){
        if(!isalpha((unsigned char)nome[i]) && nome[i] != ' ') return 0;
    }
    return 1;
}

int validar_sexo(char sexo){
    if(!(sexo == 'M' || sexo == 'F' || sexo == 'm' || sexo == 'f')) return 0;
    else return 1;
}

// Validar CPF (aceita com ou sem pontuação)
int validar_CPF(const char *cpf_raw) {
    if (cpf_raw == NULL) return 0;

    int tmp[20];
    int t = 0;

    for (size_t i = 0; cpf_raw[i] != '\0'; i++) {
        if (isdigit((unsigned char)cpf_raw[i])) {
            if (t < 20) tmp[t] = cpf_raw[i] - '0';
            t++;
        }
    }

    if (t != 11) return 0;

    int d[11];
    for (int i = 0; i < 11; i++) d[i] = tmp[i];

    int allsame = 1;
    for (int i = 1; i < 11; i++) {
        if (d[i] != d[0]) { allsame = 0; break; }
    }
    if (allsame) return 0;

    int soma = 0;
    for (int i = 0, peso = 10; i < 9; i++, peso--) soma += d[i] * peso;
    int resto = soma % 11;
    int dv1 = (resto < 2) ? 0 : 11 - resto;

    soma = 0;
    for (int i = 0, peso = 11; i < 10; i++, peso--) soma += d[i] * peso;
    resto = soma % 11;
    int dv2 = (resto < 2) ? 0 : 11 - resto;

    return (dv1 == d[9] && dv2 == d[10]) ? 1 : 0;
}

int validar_codigoDisciplina(const char codigo[]){
    if (codigo == NULL || strlen(codigo) < 3 || strlen(codigo) > 9) return 0;
    for (size_t i = 0; i < strlen(codigo); i++){
        if (!isalnum((unsigned char)codigo[i])) return 0;
    }
    return 1;
}

int tam_lista(int qtd) {
    if (qtd >= MAX_PESSOAS) return LISTA_CHEIA;
    if (qtd == 0) return LISTA_VAZIA;
    return 0;
}

int gerarMatricula() {
    int matriculaGerada = proximaMatricula;
    proximaMatricula++;
    return matriculaGerada;
}

int validar_matricula_unica(int matricula){
    for (int i = 0; i < qtdMatriculados; i++) {
        if (vetor[i].matricula == matricula) {
            return 0; // já existe
        }
    }
    return 1;
}

int buscarPessoa(Matriculado vetorLocal[], int qtdPessoas, int matricula) {
    for (int i = 0; i < qtdPessoas; i++) {
        if (vetorLocal[i].matricula == matricula) return i;
    }
    return -1;
}

// leitura segura de opção inteira entre min e max
int ler_opcao(int min, int max) {
    int opcao;
    if (scanf("%d", &opcao) != 1) {
        while (getchar() != '\n');
        return -1;
    }
    if (opcao < min || opcao > max) return -1;
    return opcao;
}

// --- CRUD Matriculados ---
int cadastrarPessoa(Matriculado vetor[], int *qtd, int tipo) {
    if (*qtd >= MAX_PESSOAS) {
        return LISTA_CHEIA;
    }

    Matriculado novaPessoa;
    char temp_nome[NOME_SIZE];
    char temp_cpf[CPF_SIZE];
    char temp_data_str[20];
    char temp_sexo;
    int data_valida = 0;

    novaPessoa.matricula = gerarMatricula();
    novaPessoa.tipo = tipo;
    novaPessoa.ativo = 1;

    printf("\n--- Cadastro de %s ---\n", tipo == ALUNO ? "Aluno" : "Professor");
    printf("Matrícula gerada: %d\n", novaPessoa.matricula);
    while (getchar() != '\n' && !feof(stdin)) break; // garantir limpar

    do {
        printf("Insira o nome: ");
        scanf(" %[^\n]", temp_nome);
        if (!validar_nome(temp_nome)) {
            printf("Nome inválido (mín. 3 letras, apenas letras e espaços).\n");
        }
    } while (!validar_nome(temp_nome));
    strcpy(novaPessoa.nome, temp_nome);

    do {
        printf("Insira o sexo (M/F): ");
        scanf(" %c", &temp_sexo);
        if (!validar_sexo(temp_sexo)) {
            printf("Sexo inválido. Digite M ou F.\n");
        }
    } while (!validar_sexo(temp_sexo));
    novaPessoa.sexo = toupper((unsigned char)temp_sexo);

    do {
        printf("Insira a data de nascimento (dd/mm/aaaa): ");
        scanf(" %19s", temp_data_str);
        int d, m, a;
        if (sscanf(temp_data_str, "%d/%d/%d", &d, &m, &a) != 3) {
            printf("Formato inválido. Use dd/mm/aaaa\n");
            data_valida = 0;
        } else {
            Data dd = {d, m, a};
            data_valida = validar_data_struct(dd);
            if (!data_valida) printf("Data inválida.\n");
            else novaPessoa.dataNascimento = dd;
        }
    } while (!data_valida);

    do {
        printf("Insira o CPF (XXX.XXX.XXX-XX ou 11 dígitos): ");
        scanf(" %14s", temp_cpf);
        if (!validar_CPF(temp_cpf)) {
            printf("CPF inválido.\n");
        }
    } while (!validar_CPF(temp_cpf));
    strcpy(novaPessoa.cpf, temp_cpf);

    vetor[*qtd] = novaPessoa;
    (*qtd)++;

    printf("%s cadastrado com sucesso! Matrícula: %d\n", tipo == ALUNO ? "Aluno" : "Professor", novaPessoa.matricula);
    return CAD_SUCESSO;
}

int excluirPessoa(Matriculado vetorLocal[], int *qtdPessoas, int tipo){
    int matricula_busca;

    printf("Exclusão de %s\n", tipo == ALUNO ? "Aluno" : "Professor");
    printf("Digite a matrícula a excluir: ");
    if (scanf("%d", &matricula_busca) != 1) {
        while (getchar() != '\n');
        printf("Entrada inválida.\n");
        return -1;
    }

    int indice = buscarPessoa(vetorLocal, *qtdPessoas, matricula_busca);
    if (indice == -1 || vetorLocal[indice].ativo == 0) {
        printf("Matrícula não encontrada ou já inativa.\n");
        return MATRICULA_INEXISTENTE;
    }

    if (vetorLocal[indice].tipo != tipo) {
        printf("Erro: Matrícula encontrada, mas não é um %s.\n", tipo == ALUNO ? "Aluno" : "Professor");
        return -1;
    }

    // exclusão lógica
    vetorLocal[indice].ativo = 0;
    printf("%s com matrícula %d excluído (logicamente) com sucesso.\n",
           tipo == ALUNO ? "Aluno" : "Professor",
           matricula_busca);
    return EXCLUSAO_SUCESSO;
}

int atualizarPessoa(Matriculado vetorLocal[], int qtdPessoas, int tipo){
    int matricula_busca;
    int indice;
    int opcao;

    printf("Atualização de cadastro de %s\n", tipo == ALUNO ? "Aluno" : "Professor");
    printf("Digite a matrícula do %s a ser atualizado: ", tipo == ALUNO ? "Aluno" : "Professor");
    if(scanf("%d", &matricula_busca) != 1){
        while(getchar() != '\n');
        printf("Entrada inválida.\n");
        return -1;
    }

    indice = buscarPessoa(vetorLocal, qtdPessoas, matricula_busca);
    if (indice == -1 || vetorLocal[indice].tipo != tipo || vetorLocal[indice].ativo == 0) {
        printf("Erro: Matrícula não encontrada, inativa ou tipo incorreto.\n");
        return MATRICULA_INEXISTENTE;
    }

    Matriculado *p = &vetorLocal[indice];
    printf("\n%s encontrado: %s\n", tipo == ALUNO ? "Aluno" : "Professor", p->nome);

    do {
        printf("\nQual campo deseja atualizar?\n");
        printf("1. Nome: %s\n", p->nome);
        printf("2. Sexo: %c\n", p->sexo);
        printf("3. Data de Nascimento: %02d/%02d/%d\n", p->dataNascimento.dia, p->dataNascimento.mes, p->dataNascimento.ano);
        printf("4. CPF: %s\n", p->cpf);
        printf("0. Finalizar Atualização\n");
        printf("Opção: ");

        opcao = ler_opcao(0, 4);
        if (opcao == -1) {
            printf("Opção inválida.\n");
            continue;
        }

        char temp_str[120];
        Data temp_data;
        int valida;

        switch (opcao) {
            case 1:
                do {
                    printf("Novo Nome: ");
                    scanf(" %[^\n]", temp_str);
                    valida = validar_nome(temp_str);
                    if (!valida) printf("Nome inválido.\n");
                } while (!valida);
                strcpy(p->nome, temp_str);
                printf("Nome atualizado.\n");
                break;
            case 2:
                do {
                    printf("Novo Sexo (M/F): ");
                    scanf(" %c", &temp_str[0]);
                    valida = validar_sexo(temp_str[0]);
                    if (!valida) printf("Sexo inválido.\n");
                } while (!valida);
                p->sexo = toupper((unsigned char)temp_str[0]);
                printf("Sexo atualizado.\n");
                break;
            case 3:
                do {
                    printf("Nova Data (DD/MM/AAAA): ");
                    scanf(" %19s", temp_str);
                    if (sscanf(temp_str, "%d/%d/%d", &temp_data.dia, &temp_data.mes, &temp_data.ano) != 3) {
                        printf("Formato inválido.\n");
                        valida = 0;
                    } else {
                        valida = validar_data_struct(temp_data);
                        if (!valida) printf("Data inválida.\n");
                    }
                } while (!valida);
                p->dataNascimento = temp_data;
                printf("Data atualizada.\n");
                break;
            case 4:
                do {
                    printf("Novo CPF (XXX.XXX.XXX-XX ou 11 dígitos): ");
                    scanf(" %14s", temp_str);
                    valida = validar_CPF(temp_str);
                    if (!valida) printf("CPF inválido.\n");
                } while (!valida);
                strcpy(p->cpf, temp_str);
                printf("CPF atualizado.\n");
                break;
            case 0:
                printf("Atualização finalizada.\n");
                return ATUALIZACAO_SUCESSO;
            default:
                printf("Opção inválida.\n");
        }
    } while (1);

    return ATUALIZACAO_SUCESSO;
}

// --- Disciplina ---
int cadastrarDisciplina(Disciplina listaDisciplina[], int *qtdDisciplina) {
    if (*qtdDisciplina >= MAX_DISCI) return LISTA_CHEIA;

    char codigo[10];
    char nomeDisc[100];
    int semestre;
    char professor[50];

    printf("Digite o código da disciplina (ex: INFO201): ");
    scanf(" %9s", codigo);
    if (!validar_codigoDisciplina(codigo)) {
        printf("Código inválido.\n");
        return CODIGO_INVALIDO;
    }
    // Verifica duplicidade
    for (int i = 0; i < *qtdDisciplina; i++) {
        if (strcmp(listaDisciplina[i].codigo, codigo) == 0 && listaDisciplina[i].ativo == 1)
            return CODIGO_INVALIDO;
    }

    printf("Digite o nome da disciplina: ");
    scanf(" %[^\n]", nomeDisc);
    printf("Digite o semestre (ex: 1, 2, 3...): ");
    if (scanf("%d", &semestre) != 1) {
        while (getchar() != '\n');
        printf("Semestre inválido.\n");
        return CODIGO_INVALIDO;
    }
    printf("Digite o nome do professor: ");
    scanf(" %[^\n]", professor);

    strcpy(listaDisciplina[*qtdDisciplina].codigo, codigo);
    strncpy(listaDisciplina[*qtdDisciplina].nome, nomeDisc, sizeof(listaDisciplina[*qtdDisciplina].nome)-1);
    listaDisciplina[*qtdDisciplina].semestre = semestre;
    strncpy(listaDisciplina[*qtdDisciplina].professor, professor, sizeof(listaDisciplina[*qtdDisciplina].professor)-1);
    listaDisciplina[*qtdDisciplina].qtdAlunos = 0;
    listaDisciplina[*qtdDisciplina].ativo = 1;
    for (int k = 0; k < MAX_ALUNOS_DISCI; k++) listaDisciplina[*qtdDisciplina].alunosMatriculados[k] = -1;

    (*qtdDisciplina)++;
    return CAD_DISCIPLINA_SUCESSO;
}

void listarDisciplina(Disciplina listaDisciplina[], int qtdDisciplina) {
    printf("\n--- Lista de Disciplinas ---\n");
    if (qtdDisciplina == 0) {
        printf("Nenhuma disciplina cadastrada.\n");
        return;
    }
    for (int i = 0; i < qtdDisciplina; i++) {
        if (listaDisciplina[i].ativo == 1) {
            printf("Código: %s | Nome: %s | Semestre: %d | Professor: %s | Alunos: %d\n",
                   listaDisciplina[i].codigo,
                   listaDisciplina[i].nome,
                   listaDisciplina[i].semestre,
                   listaDisciplina[i].professor,
                   listaDisciplina[i].qtdAlunos);
        }
    }
}

int excluirDisciplina(Disciplina listaDisciplina[], int *qtdDisciplina) {
    char codigo[10];
    printf("Digite o código da disciplina a excluir: ");
    scanf(" %9s", codigo);

    for (int i = 0; i < *qtdDisciplina; i++) {
        if (strcmp(listaDisciplina[i].codigo, codigo) == 0 && listaDisciplina[i].ativo == 1) {
            listaDisciplina[i].ativo = 0;
            for (int j = i; j < *qtdDisciplina - 1; j++) {
                listaDisciplina[j] = listaDisciplina[j + 1];
            }
            (*qtdDisciplina)--;
            return EXCLUSAO_DISCIPLINA_SUCESSO;
        }
    }
    return DISCIPLINA_INEXISTENTE;
}

int inserirAlunoDisciplina(Disciplina disciplinasLocal[], int qtdDisciplinasLocal, char codigo[], int matAluno) {
    int idxAluno = buscarPessoa(vetor, qtdMatriculados, matAluno);
    if (idxAluno == -1 || vetor[idxAluno].ativo == 0 || vetor[idxAluno].tipo != ALUNO) {
        return MATRICULA_INEXISTENTE; // Não é um aluno ativo
    }

    for (int i = 0; i < qtdDisciplinasLocal; i++) {
        if (disciplinasLocal[i].ativo == 1 && strcmp(disciplinasLocal[i].codigo, codigo) == 0) {
            if (disciplinasLocal[i].qtdAlunos >= MAX_ALUNOS_DISCI) return LISTA_CHEIA;
            for (int j = 0; j < disciplinasLocal[i].qtdAlunos; j++) {
                if (disciplinasLocal[i].alunosMatriculados[j] == matAluno) return 0; // já matriculado
            }
            disciplinasLocal[i].alunosMatriculados[disciplinasLocal[i].qtdAlunos++] = matAluno;
            return CAD_SUCESSO;
        }
    }
    return DISCIPLINA_INEXISTENTE;
}

int excluirAlunoDisciplina(Disciplina disciplinasLocal[], int qtdDisciplinasLocal, char codigo[], int matAluno) {
    for (int i = 0; i < qtdDisciplinasLocal; i++) {
        if (disciplinasLocal[i].ativo == 1 && strcmp(disciplinasLocal[i].codigo, codigo) == 0) {
            int found = -1;
            for (int j = 0; j < disciplinasLocal[i].qtdAlunos; j++) {
                if (disciplinasLocal[i].alunosMatriculados[j] == matAluno) { found = j; break; }
            }
            if (found == -1) return MATRICULA_INEXISTENTE;
            for (int k = found; k < disciplinasLocal[i].qtdAlunos - 1; k++) {
                disciplinasLocal[i].alunosMatriculados[k] = disciplinasLocal[i].alunosMatriculados[k+1];
            }
            disciplinasLocal[i].qtdAlunos--;
            disciplinasLocal[i].alunosMatriculados[disciplinasLocal[i].qtdAlunos] = -1;
            return EXCLUSAO_SUCESSO;
        }
    }
    return DISCIPLINA_INEXISTENTE;
}

void listarDisciplinaCompleta(Disciplina disciplinasLocal[], int qtdDisciplinasLocal, Matriculado vetorLocal[], int qtdPessoas) {
    printf("\n--- Disciplinas (detalhado) ---\n");
    for (int i = 0; i < qtdDisciplinasLocal; i++) {
        if (disciplinasLocal[i].ativo == 1) {
            printf("\nCódigo: %s | Nome: %s | Prof.: %s | Alunos (%d):\n",
                   disciplinasLocal[i].codigo,
                   disciplinasLocal[i].nome,
                   disciplinasLocal[i].professor,
                   disciplinasLocal[i].qtdAlunos);
            for (int j = 0; j < disciplinasLocal[i].qtdAlunos; j++) {
                int mat = disciplinasLocal[i].alunosMatriculados[j];
                int idx = buscarPessoa(vetorLocal, qtdPessoas, mat);
                if (idx != -1 && vetorLocal[idx].ativo == 1) {
                    printf("  - %s (mat %d)\n", vetorLocal[idx].nome, mat);
                } else {
                    printf("  - matrícula %d (não encontrada)\n", mat);
                }
            }
        }
    }
}

// --- Listagens simples / utilitárias ---
void listarPessoas(Matriculado vetorLocal[], int qtdPessoas, int tipo) {
    printf("\n--- Lista de %s(s) ---\n", tipo == ALUNO ? "Aluno" : "Professor");
    int achou = 0;
    for (int i = 0; i < qtdPessoas; i++) {
        if (vetorLocal[i].ativo == 1 && vetorLocal[i].tipo == tipo) {
            printf("Mat: %d | Nome: %s | Sexo: %c | Nasc: %02d/%02d/%04d | CPF: %s\n",
                   vetorLocal[i].matricula,
                   vetorLocal[i].nome,
                   vetorLocal[i].sexo,
                   vetorLocal[i].dataNascimento.dia,
                   vetorLocal[i].dataNascimento.mes,
                   vetorLocal[i].dataNascimento.ano,
                   vetorLocal[i].cpf);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhum registro.\n");
}

void listarAniversariantesDoMes(Matriculado vetorLocal[], int qtdPessoas) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int mes = tm.tm_mon + 1; // 1..12
    printf("\n--- Aniversariantes do mês (%02d) ---\n", mes);
    int achou = 0;
    for (int i = 0; i < qtdPessoas; i++) {
        if (vetorLocal[i].ativo == 1 && vetorLocal[i].dataNascimento.mes == mes) {
            printf("%s - %02d/%02d/%04d (mat %d)\n", vetorLocal[i].nome, vetorLocal[i].dataNascimento.dia, vetorLocal[i].dataNascimento.mes, vetorLocal[i].dataNascimento.ano, vetorLocal[i].matricula);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhum aniversariante no mês.\n");
}

void listarPessoasPorSexo(Matriculado vetorLocal[], int qtdPessoas, int tipo, char sexo) {
    printf("\n--- Lista por sexo: %c ---\n", sexo);
    int achou = 0;
    for (int i = 0; i < qtdPessoas; i++) {
        if (vetorLocal[i].ativo == 1 && vetorLocal[i].tipo == tipo && toupper((unsigned char)vetorLocal[i].sexo) == toupper((unsigned char)sexo)) {
            printf("Mat: %d | Nome: %s\n", vetorLocal[i].matricula, vetorLocal[i].nome);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhum registro.\n");
}

void buscarPessoasPorString(Matriculado vetorLocal[], int qtdPessoas, char busca[]) {
    printf("\n--- Busca: %s ---\n", busca);
    int achou = 0;
    for (int i = 0; i < qtdPessoas; i++) {
        if (vetorLocal[i].ativo == 1) {
            if (strcasestr_custom(vetorLocal[i].nome, busca) != NULL) {
                printf("Mat: %d | Nome: %s\n", vetorLocal[i].matricula, vetorLocal[i].nome);
                achou = 1;
            }
        }
    }
    if (!achou) printf("Nenhum registro encontrado.\n");
}

// placeholders para ordenação (simples bubble)
void ordenarPessoasPorNome(Matriculado vetorLocal[], int qtdPessoas, int tipo) {
    for (int i = 0; i < qtdPessoas - 1; i++) {
        for (int j = i + 1; j < qtdPessoas; j++) {
            if (vetorLocal[i].ativo && vetorLocal[j].ativo && vetorLocal[i].tipo == tipo && vetorLocal[j].tipo == tipo) {
                if (strcasecmp(vetorLocal[i].nome, vetorLocal[j].nome) > 0) {
                    Matriculado tmp = vetorLocal[i];
                    vetorLocal[i] = vetorLocal[j];
                    vetorLocal[j] = tmp;
                }
            }
        }
    }
    printf("Ordenação por nome realizada (in-place).\n");
}

void ordenarPessoasPorDataNascimento(Matriculado vetorLocal[], int qtdPessoas, int tipo) {
    for (int i = 0; i < qtdPessoas - 1; i++) {
        for (int j = i + 1; j < qtdPessoas; j++) {
            if (vetorLocal[i].ativo && vetorLocal[j].ativo && vetorLocal[i].tipo == tipo && vetorLocal[j].tipo == tipo) {
                Data a = vetorLocal[i].dataNascimento;
                Data b = vetorLocal[j].dataNascimento;
                if (a.ano > b.ano || (a.ano == b.ano && (a.mes > b.mes || (a.mes == b.mes && a.dia > b.dia)))) {
                    Matriculado tmp = vetorLocal[i];
                    vetorLocal[i] = vetorLocal[j];
                    vetorLocal[j] = tmp;
                }
            }
        }
    }
    printf("Ordenação por data de nascimento realizada (in-place).\n");
}

// --- NOVAS FUNÇÕES: contagem e listagem de alunos com menos de 3 disciplinas ---

// Retorna quantas disciplinas o aluno (matricula) está matriculado
int contarDisciplinasMatriculadas(int matricula) {
    int count = 0;
    for (int d = 0; d < qtdDisciplinas; d++) {
        if (!disciplinas[d].ativo) continue;
        for (int k = 0; k < disciplinas[d].qtdAlunos; k++) {
            if (disciplinas[d].alunosMatriculados[k] == matricula) {
                count++;
                break; // este aluno já conta para esta disciplina; ir para próxima disciplina
            }
        }
    }
    return count;
}

// Lista alunos ativos com menos de 3 disciplinas. Retorna quantos foram listados.
int listarAlunosMenos3Disciplinas() {
    int encontrados = 0;
    printf("\n--- Alunos matriculados em menos de 3 disciplinas ---\n");
    for (int i = 0; i < qtdMatriculados; i++) {
        if (vetor[i].ativo == 1 && vetor[i].tipo == ALUNO) {
            int qtd = contarDisciplinasMatriculadas(vetor[i].matricula);
            if (qtd < 3) {
                printf("Mat: %d | Nome: %s | Disciplinas: %d\n", vetor[i].matricula, vetor[i].nome, qtd);
                encontrados++;
            }
        }
    }
    if (encontrados == 0) {
        printf("Nenhum aluno encontrado com menos de 3 disciplinas.\n");
    }
    return encontrados;
}

// --- main ---
int main(void) {
    int opcao;
    int sair = 0;

    // inicializa arrays de disciplinas
    for (int i = 0; i < MAX_DISCI; i++) {
        disciplinas[i].ativo = 0;
        disciplinas[i].qtdAlunos = 0;
        for (int j = 0; j < MAX_ALUNOS_DISCI; j++) disciplinas[i].alunosMatriculados[j] = -1;
    }

    while (!sair) {
        opcao = menuGeral();
        if (opcao == -1) { printf("Opção inválida.\n"); continue; }

        switch (opcao) {
            case 0:
                sair = 1;
                break;
            case 1: { // ALUNO
                int sairAluno = 0;
                int opcaoAluno;
                while (!sairAluno) {
                    opcaoAluno = menuMatriculados("Aluno");
                    switch (opcaoAluno) {
                        case 0: sairAluno = 1; break;
                        case 1: {
                            int retorno = cadastrarPessoa(vetor, &qtdMatriculados, ALUNO);
                            if (retorno == LISTA_CHEIA) printf("Lista de alunos cheia!\n");
                            else if (retorno == CAD_SUCESSO) printf("Aluno cadastrado com sucesso!\n");
                            break;
                        }
                        case 2:
                            listarPessoas(vetor, qtdMatriculados, ALUNO);
                            break;
                        case 3: {
                            int retorno = atualizarPessoa(vetor, qtdMatriculados, ALUNO);
                            if (retorno == ATUALIZACAO_SUCESSO) printf("Aluno atualizado com sucesso!\n");
                            break;
                        }
                        case 4: {
                            int retorno = excluirPessoa(vetor, &qtdMatriculados, ALUNO);
                            if (retorno == EXCLUSAO_SUCESSO) printf("Aluno excluído com sucesso!\n");
                            break;
                        }
                        default: printf("Opção inválida!\n");
                    }
                }
                break;
            }
            case 2: { // PROFESSOR
                int sairProf = 0;
                int opcaoProf;
                while (!sairProf) {
                    opcaoProf = menuMatriculados("Professor");
                    switch (opcaoProf) {
                        case 0: sairProf = 1; break;
                        case 1: {
                            int r = cadastrarPessoa(vetor, &qtdMatriculados, PROFESSOR);
                            if (r == CAD_SUCESSO) printf("Professor cadastrado!\n");
                            else if (r == LISTA_CHEIA) printf("Lista cheia!\n");
                            break;
                        }
                        case 2: listarPessoas(vetor, qtdMatriculados, PROFESSOR); break;
                        case 3: atualizarPessoa(vetor, qtdMatriculados, PROFESSOR); break;
                        case 4: excluirPessoa(vetor, &qtdMatriculados, PROFESSOR); break;
                        default: printf("Opção inválida!\n");
                    }
                }
                break;
            }
            case 3: { // DISCIPLINA
                int sairDisciplina = 0, opcaoDisciplina;
                while (!sairDisciplina) {
                    opcaoDisciplina = menuDisciplina();
                    switch (opcaoDisciplina) {
                        case 0: sairDisciplina = 1; break;
                        case 1: {
                            int retorno = cadastrarDisciplina(disciplinas, &qtdDisciplinas);
                            if (retorno == LISTA_CHEIA) printf("Lista de disciplinas cheia!\n");
                            else if (retorno == CODIGO_INVALIDO) printf("Código de disciplina inválido ou já cadastrado!\n");
                            else if (retorno == CAD_DISCIPLINA_SUCESSO) printf("Disciplina cadastrada com sucesso!\n");
                            break;
                        }
                        case 2:
                            listarDisciplina(disciplinas, qtdDisciplinas);
                            break;
                        case 3: {
                            int retorno = excluirDisciplina(disciplinas, &qtdDisciplinas);
                            if (retorno == DISCIPLINA_INEXISTENTE) printf("Disciplina inexistente!\n");
                            else if (retorno == EXCLUSAO_DISCIPLINA_SUCESSO) printf("Disciplina excluída com sucesso!\n");
                            break;
                        }
                        case 4: {
                            char cod[10];
                            int mat;
                            printf("Código da disciplina: ");
                            scanf(" %9s", cod);
                            printf("Matrícula do aluno: ");
                            if (scanf("%d", &mat) != 1) { while(getchar()!='\n'); printf("Entrada inválida.\n"); break; }
                            int r = inserirAlunoDisciplina(disciplinas, qtdDisciplinas, cod, mat);
                            if (r == CAD_SUCESSO) printf("Aluno inserido na disciplina.\n");
                            else if (r == LISTA_CHEIA) printf("Disciplina cheia.\n");
                            else if (r == MATRICULA_INEXISTENTE) printf("Erro: Matrícula de aluno não encontrada/inativa.\n");
                            else printf("Erro (disciplina inexistente?).\n");
                            break;
                        }
                        case 5: {
                            char cod[10];
                            int mat;
                            printf("Código da disciplina: ");
                            scanf(" %9s", cod);
                            printf("Matrícula do aluno: ");
                            if (scanf("%d", &mat) != 1) { while(getchar()!='\n'); printf("Entrada inválida.\n"); break; }
                            int r = excluirAlunoDisciplina(disciplinas, qtdDisciplinas, cod, mat);
                            if (r == EXCLUSAO_SUCESSO) printf("Aluno removido da disciplina.\n");
                            else printf("Erro ao remover (não encontrado?).\n");
                            break;
                        }
                        default:
                            printf("Opção inválida!\n");
                    }
                }
                break;
            }
            case 4: { // Listagens
                int sairListagem = 0, opcaoListagem;
                while (!sairListagem) {
                    opcaoListagem = menuListagens();
                    switch(opcaoListagem) {
                        case 0: sairListagem = 1; break;
                        case 1: listarAniversariantesDoMes(vetor, qtdMatriculados); break;
                        case 2: {
                            printf("\n--- Disciplinas com mais de 40 alunos ---\n");
                            int achou = 0;
                            for (int i = 0; i < qtdDisciplinas; i++) {
                                if (disciplinas[i].ativo && disciplinas[i].qtdAlunos > 40) {
                                    printf("%s (%d alunos)\n", disciplinas[i].codigo, disciplinas[i].qtdAlunos);
                                    achou = 1;
                                }
                            }
                            if (!achou) printf("Nenhuma disciplina encontrada.\n");
                            break;
                        }
                        case 3: {
                            // chamada da implementação solicitada
                            listarAlunosMenos3Disciplinas();
                            break;
                        }
                        case 4: {
                            char sexo_busca;
                            int tipo_busca;
                            printf("Listar Aluno (1) ou Professor (2)? ");
                            if (scanf("%d", &tipo_busca) != 1 || (tipo_busca != ALUNO && tipo_busca != PROFESSOR)) {
                                while (getchar() != '\n');
                                printf("Opção de tipo inválida.\n");
                                break;
                            }
                            printf("Sexo (M/F): ");
                            scanf(" %c", &sexo_busca);
                            if (validar_sexo(sexo_busca)) {
                                listarPessoasPorSexo(vetor, qtdMatriculados, tipo_busca, sexo_busca);
                            } else {
                                printf("Sexo inválido.\n");
                            }
                            break;
                        }
                        default:
                            printf("Opção inválida!\n");
                    }
                }
                break;
            }
            default:
                printf("Opção inválida!\n");
        }
    }

    printf("\nSistema encerrado.\n");
    return 0;
}
