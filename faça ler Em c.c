#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINHA 256
#define MAX_ALUNOS 500

typedef struct {
    char materia[50];
    char nome[50];
    char ra[20];
    char turma[20];
    float nota1;
    float nota2;
    float media;
} Aluno;

Aluno alunos[MAX_ALUNOS];
int totalAlunos = 0;

void carregarCSV() {
    FILE *file = fopen("alunos.csv", "r");
    if (file == NULL) {
        printf("Erro: não foi possi­vel abrir o arquivo alunos.csv.\n");
        return;
    }

    char linha[MAX_LINHA];
    fgets(linha, sizeof(linha), file); // pula o cabeÃ§alho

    while (fgets(linha, sizeof(linha), file)) {
        Aluno a;
        if (sscanf(linha, "%49[^,],%49[^,],%19[^,],%19[^,],%f,%f,%f",
                   a.materia, a.nome, a.ra, a.turma,
                   &a.nota1, &a.nota2, &a.media) == 7) {
            alunos[totalAlunos++] = a;
        }
    }

    fclose(file);
    printf("\n%d alunos carregados com sucesso!\n", totalAlunos);
}

void listarAlunos() {
    printf("\n=== LISTA DE TODOS OS ALUNOS ===\n");
    for (int i = 0; i < totalAlunos; i++) {
        printf("%s | %s | %s | %s | %.1f | %.1f | Media: %.2f\n",
               alunos[i].materia, alunos[i].nome, alunos[i].ra,
               alunos[i].turma, alunos[i].nota1, alunos[i].nota2, alunos[i].media);
    }
}

void buscarPorRA() {
    char raBusca[20];
    printf("Digite o RA do aluno: ");
    scanf("%s", raBusca);

    int encontrado = 0;
    for (int i = 0; i < totalAlunos; i++) {
        if (strcmp(alunos[i].ra, raBusca) == 0) {
            printf("\nAluno encontrado:\n");
            printf("Materia: %s\nNome: %s\nRA: %s\nTurma: %s\nNotas: %.1f, %.1f\nMedia: %.2f\n",
                   alunos[i].materia, alunos[i].nome, alunos[i].ra, alunos[i].turma,
                   alunos[i].nota1, alunos[i].nota2, alunos[i].media);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Aluno com RA %s Não encontrado.\n", raBusca);
    }
}

void relatorioMediasPorMateria() {
    printf("\n=== RELATORIO DE MEDIAS POR DISCIPLINA ===\n");

    char materias[50][50];
    float soma[50] = {0};
    int contagem[50] = {0};
    int numMaterias = 0;

    for (int i = 0; i < totalAlunos; i++) {
        int idx = -1;
        for (int j = 0; j < numMaterias; j++) {
            if (strcmp(alunos[i].materia, materias[j]) == 0) {
                idx = j;
                break;
            }
        }
        if (idx == -1) {
            strcpy(materias[numMaterias], alunos[i].materia);
            soma[numMaterias] = alunos[i].media;
            contagem[numMaterias] = 1;
            numMaterias++;
        } else {
            soma[idx] += alunos[i].media;
            contagem[idx]++;
        }
    }

    for (int i = 0; i < numMaterias; i++) {
        printf("%s: media geral = %.2f\n", materias[i], soma[i] / contagem[i]);
    }
}

int main() {
    int opcao;

    carregarCSV();

    do {
        printf("\n========= MENU =========\n");
        printf("1 - Listar todos os alunos\n");
        printf("2 - Buscar aluno por RA\n");
        printf("3 - Relatorio de medias por disciplina\n");
        printf("0 - Sair\n");
        printf("========================\n");
        printf("Escolha uma opcoes: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listarAlunos();
                break;
            case 2:
                buscarPorRA();
                break;
            case 3:
                relatorioMediasPorMateria();
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}