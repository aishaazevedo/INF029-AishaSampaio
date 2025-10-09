#include <stdio.h>
#include <string.h>

#define TAM_ALUNO 3
#define TAM_DISCIPLINA 4

// Códigos de retorno
#define CAD_ALUNO_SUCESSO -1
#define MATRICULA_INVALIDA -2
#define LISTA_CHEIA -3
#define ATUALIZACAO_ALUNO_SUCESSO -4
#define MATRICULA_INEXISTENTE -5
#define EXCLUSAO_ALUNO_SUCESSO -6
#define CAD_DISCIPLINA_SUCESSO -7
#define CODIGO_INVALIDO -8
#define DISCIPLINA_INEXISTENTE -9
#define EXCLUSAO_DISCIPLINA_SUCESSO -10

// Estruturas
typedef struct alu {
    int matricula;
    char sexo;
    int ativo;
} Aluno;

typedef struct dis {
    char codigo[10];     // Ex: "INFO201"
    int semestre;
    char professor[50];
    int ativo;
} Disciplina;

// Protótipos
int menuGeral();
int menuAluno();
int cadastrarAluno(Aluno listaAluno[], int qtdAluno);
void listarAluno(Aluno listaAluno[], int qtdAluno);
int atualizarAluno(Aluno listaAluno[], int qtdAluno);
int excluirAluno(Aluno listaAluno[], int qtdAluno);

int menuDisciplina();
int cadastrarDisciplina(Disciplina listaDisciplina[], int qtdDisciplina);
void listarDisciplina(Disciplina listaDisciplina[], int qtdDisciplina);
int excluirDisciplina(Disciplina listaDisciplina[], int qtdDisciplina);

// FUNÇÕES AUXILIARES 

int menuGeral() {
    int opcao;
    printf("\nMENU GERAL \n");
    printf("0 - Sair\n");
    printf("1 - Aluno\n");
    printf("2 - Professor\n");
    printf("3 - Disciplina\n");
    printf("4 - Listagens\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    return opcao;
}

// ===== MÓDULO ALUNO =====

int menuAluno() {
    int opcao;
    printf("\nMENU ALUNO \n");
    printf("0 - Voltar\n");
    printf("1 - Cadastrar Aluno\n");
    printf("2 - Listar Aluno\n");
    printf("3 - Atualizar Aluno\n");
    printf("4 - Excluir Aluno\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    return opcao;
}

int cadastrarAluno(Aluno listaAluno[], int qtdAluno) {
    if (qtdAluno == TAM_ALUNO) {
        return LISTA_CHEIA;
    }

    int matricula;
    char sexo;

    printf("Digite a matrícula: ");
    scanf("%d", &matricula);

    if (matricula < 0) {
        return MATRICULA_INVALIDA;
    }

    printf("Digite o sexo (M/F): ");
    scanf(" %c", &sexo);

    listaAluno[qtdAluno].matricula = matricula;
    listaAluno[qtdAluno].sexo = sexo;
    listaAluno[qtdAluno].ativo = 1;

    return CAD_ALUNO_SUCESSO;
}

void listarAluno(Aluno listaAluno[], int qtdAluno) {
    printf("\n--- Lista de Alunos ---\n");
    if (qtdAluno == 0) {
        printf("Nenhum aluno cadastrado.\n");
    } else {
        for (int i = 0; i < qtdAluno; i++) {
            if (listaAluno[i].ativo == 1)
                printf("Matrícula: %d | Sexo: %c\n",
                       listaAluno[i].matricula,
                       listaAluno[i].sexo);
        }
    }
}

int atualizarAluno(Aluno listaAluno[], int qtdAluno) {
    int matricula;
    printf("Digite a matrícula do aluno a atualizar: ");
    scanf("%d", &matricula);

    if (matricula < 0)
        return MATRICULA_INVALIDA;

    for (int i = 0; i < qtdAluno; i++) {
        if (listaAluno[i].matricula == matricula && listaAluno[i].ativo == 1) {
            printf("Digite o novo sexo (M/F): ");
            scanf(" %c", &listaAluno[i].sexo);
            return ATUALIZACAO_ALUNO_SUCESSO;
        }
    }

    return MATRICULA_INEXISTENTE;
}

int excluirAluno(Aluno listaAluno[], int qtdAluno) {
    int matricula;
    printf("Digite a matrícula do aluno a excluir: ");
    scanf("%d", &matricula);

    if (matricula < 0)
        return MATRICULA_INVALIDA;

    for (int i = 0; i < qtdAluno; i++) {
        if (listaAluno[i].matricula == matricula && listaAluno[i].ativo == 1) {
            listaAluno[i].ativo = -1;

            for (int j = i; j < qtdAluno - 1; j++) {
                listaAluno[j] = listaAluno[j + 1];
            }

            return EXCLUSAO_ALUNO_SUCESSO;
        }
    }

    return MATRICULA_INEXISTENTE;
}

//  MÓDULO DISCIPLINA 

int menuDisciplina() {
    int opcao;
    printf("\nMENU DISCIPLINA \n");
    printf("0 - Voltar\n");
    printf("1 - Cadastrar Disciplina\n");
    printf("2 - Listar Disciplinas\n");
    printf("3 - Excluir Disciplina\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    return opcao;
}

int cadastrarDisciplina(Disciplina listaDisciplina[], int qtdDisciplina) {
    if (qtdDisciplina == TAM_DISCIPLINA) {
        return LISTA_CHEIA;
    }

    char codigo[10];
    int semestre;
    char professor[50];

    printf("Digite o código da disciplina (ex: INFO201): ");
    scanf("%s", codigo);

    // Verifica duplicidade
    for (int i = 0; i < qtdDisciplina; i++) {
        if (strcmp(listaDisciplina[i].codigo, codigo) == 0 && listaDisciplina[i].ativo == 1)
            return CODIGO_INVALIDO;
    }

    printf("Digite o semestre (ex: 1, 2, 3...): ");
    scanf("%d", &semestre);

    printf("Digite o nome do professor: ");
    scanf(" %[^\n]", professor);

    strcpy(listaDisciplina[qtdDisciplina].codigo, codigo);
    listaDisciplina[qtdDisciplina].semestre = semestre;
    strcpy(listaDisciplina[qtdDisciplina].professor, professor);
    listaDisciplina[qtdDisciplina].ativo = 1;

    return CAD_DISCIPLINA_SUCESSO;
}

void listarDisciplina(Disciplina listaDisciplina[], int qtdDisciplina) {
    printf("\n--- Lista de Disciplinas ---\n");
    if (qtdDisciplina == 0) {
        printf("Nenhuma disciplina cadastrada.\n");
    } else {
        for (int i = 0; i < qtdDisciplina; i++) {
            if (listaDisciplina[i].ativo == 1)
                printf("Código: %s | Semestre: %d | Professor: %s\n",
                       listaDisciplina[i].codigo,
                       listaDisciplina[i].semestre,
                       listaDisciplina[i].professor);
        }
    }
}

int excluirDisciplina(Disciplina listaDisciplina[], int qtdDisciplina) {
    char codigo[10];
    printf("Digite o código da disciplina a excluir: ");
    scanf("%s", codigo);

    for (int i = 0; i < qtdDisciplina; i++) {
        if (strcmp(listaDisciplina[i].codigo, codigo) == 0 && listaDisciplina[i].ativo == 1) {
            listaDisciplina[i].ativo = -1;

            for (int j = i; j < qtdDisciplina - 1; j++) {
                listaDisciplina[j] = listaDisciplina[j + 1];
            }

            return EXCLUSAO_DISCIPLINA_SUCESSO;
        }
    }

    return DISCIPLINA_INEXISTENTE;
}
//menu listagens
int menuListagens() {
    int opcao;
    printf("\nMENU LISTAGENS \n");
    printf("0 - Voltar\n");
    printf("1 - Aniversariantes do mês\n");
    printf("2 - Disciplinas com mais de 40 alunos\n");
    printf("3 - Alunos matriculados em menos de 3 disciplinas\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    return opcao;
}

// ===== FUNÇÃO PRINCIPAL =====

int main(void) {
    Aluno listaAluno[TAM_ALUNO];
    Disciplina listaDisciplina[TAM_DISCIPLINA];

    int opcao, qtdAluno = 0, qtdDisciplina = 0, sair = 0;

    while (!sair) {
        opcao = menuGeral();

        switch (opcao) {
            case 0:
                sair = 1;
                break;

            case 1: { 
                int sairAluno = 0, opcaoAluno;
                while (!sairAluno) {
                    opcaoAluno = menuAluno();
                    switch (opcaoAluno) {
                        case 0: sairAluno = 1; break;
                        case 1: {
                            int retorno = cadastrarAluno(listaAluno, qtdAluno);
                            if (retorno == LISTA_CHEIA)
                                printf("Lista de alunos cheia!\n");
                            else if (retorno == MATRICULA_INVALIDA)
                                printf("Matrícula inválida!\n");
                            else if (retorno == CAD_ALUNO_SUCESSO) {
                                printf("Aluno cadastrado com sucesso!\n");
                                qtdAluno++;
                            }
                            break;
                        }
                        case 2: listarAluno(listaAluno, qtdAluno); break;
                        case 3: {
                            int retorno = atualizarAluno(listaAluno, qtdAluno);
                            if (retorno == ATUALIZACAO_ALUNO_SUCESSO)
                                printf("Aluno atualizado com sucesso!\n");
                            else if (retorno == MATRICULA_INEXISTENTE)
                                printf("Matrícula inexistente!\n");
                            else
                                printf("Matrícula inválida!\n");
                            break;
                        }
                        case 4: {
                            int retorno = excluirAluno(listaAluno, qtdAluno);
                            if (retorno == EXCLUSAO_ALUNO_SUCESSO) {
                                printf("Aluno excluído com sucesso!\n");
                                qtdAluno--;
                            } else if (retorno == MATRICULA_INEXISTENTE)
                                printf("Matrícula inexistente!\n");
                            else
                                printf("Matrícula inválida!\n");
                            break;
                        }
                        default: printf("Opção inválida!\n");
                    }
                }
                break;
            }

            case 2:
                printf("Módulo Professor (em desenvolvimento)\n");
                break;

            case 3: { 
                int sairDisciplina = 0, opcaoDisciplina;
                while (!sairDisciplina) {
                    opcaoDisciplina = menuDisciplina();
                    switch (opcaoDisciplina) {
                        case 0:
                            sairDisciplina = 1;
                            break;
                        case 1: {
                            int retorno = cadastrarDisciplina(listaDisciplina, qtdDisciplina);
                            if (retorno == LISTA_CHEIA)
                                printf("Lista de disciplinas cheia!\n");
                            else if (retorno == CODIGO_INVALIDO)
                                printf("Código de disciplina inválido ou já cadastrado!\n");
                            else if (retorno == CAD_DISCIPLINA_SUCESSO) {
                                printf("Disciplina cadastrada com sucesso!\n");
                                qtdDisciplina++;
                            }
                            break;
                        }
                        case 2:
                            listarDisciplina(listaDisciplina, qtdDisciplina);
                            break;
                        case 3: {
                            int retorno = excluirDisciplina(listaDisciplina, qtdDisciplina);
                            if (retorno == DISCIPLINA_INEXISTENTE)
                                printf("Disciplina inexistente!\n");
                            else if (retorno == EXCLUSAO_DISCIPLINA_SUCESSO) {
                                printf("Disciplina excluída com sucesso!\n");
                                qtdDisciplina--;
                            }
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
            case 0:
                sairListagem = 1;
                break;
            case 1:
           // fazer     listarAniversariantesDoMes
                break;
            case 2:
             //   listarDisciplinasVagasExcedidas(listaDisciplina, qtdDisciplina, listaAluno, qtdAluno);
                break;
            case 3:
          //      listarAlunosMenos3Disciplinas(listaAluno, qtdAluno, listaDisciplina, qtdDisciplina);
                break;
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

    printf("\nConsulta finalizada.\n");
    return 0;
}
