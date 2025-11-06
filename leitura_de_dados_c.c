#include <stdio.h> // padrão para entrada e saída de dados
#include <stdlib.h>
#include <string.h> // para comparação de strings
#include <ctype.h> // para conversão em upper

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

// vetor para mapear a escolha numérica para o nome da matéria no CSV
char* materias_mapa[] = {
    "ENGENHARIA DE SOFT AGIL", // 0
    "PYTHON",                 // 1
    "C",                      // 2
    "ANALISE DE PROJETOS" // 3
};
#define NUM_OPCOES_MATERIA 4


int selecao_materias(){
     int selecao_materia;
    
    while (1) { 
        printf("\nSelecione a materia a ser mostrada: \n");
        printf("\n0 - %s\n", materias_mapa[0]);
        printf("1 - %s\n", materias_mapa[1]);
        printf("2 - %s\n", materias_mapa[2]);
        printf("3 - %s\n", materias_mapa[3]);
        printf("99 - Voltar ao menu principal");
        printf("\n>>>> ");

        if (scanf("%d", &selecao_materia) != 1) {
            while (getchar() != '\n' && !feof(stdin));
            selecao_materia = -1;
        }

        if (selecao_materia >= 0 && selecao_materia < NUM_OPCOES_MATERIA) {
            return selecao_materia;
        }
        else if (selecao_materia == 99) {
            return 99;
        }
        else {
            printf("\nOpcao invalida. Por favor, tente novamente.\n");
        }
    }
}



//função para converter os caracteres em maiusculo
void converter_para_upper(char* s){
    int i = 0;
    while (s[i] != '\0')
    {
        s[i] = toupper((unsigned char) s[i]);
        i++;
    }
}


void listarPorMateria(char* materia_buscada) {
    printf("\n=== LISTA DE ALUNOS NA MATERIA: %s ===\n", materia_buscada);
    
    int encontrado = 0;
    
    for (int i = 0; i < totalAlunos; i++) {
        // Compara o nome da matéria do aluno com a matéria buscada
        if (strcmp(alunos[i].materia, materia_buscada) == 0) {
            
            // Imprime os detalhes do aluno/materia
            printf("%s | %s | %s | %s | %.1f | %.1f | Media: %.2f\n",
                   alunos[i].materia, alunos[i].nome, alunos[i].ra,
                   alunos[i].turma, alunos[i].nota1, alunos[i].nota2, alunos[i].media);
            
            encontrado = 1;
        }
    }
    
    if (!encontrado) {
        printf("Nenhum registro encontrado para a materia '%s'.\n", materia_buscada);
    }
}




//função para carregar os dados do arquivo csv
void carregarCSV() {
    FILE *file = fopen("alunos.csv", "r");
    if (file == NULL) {
        printf("Erro: nao foi possivel abrir o arquivo.\n");
        return;
    }

    char linha[MAX_LINHA];
    fgets(linha, sizeof(linha), file); // pula o cabeçalho

    while (fgets(linha, sizeof(linha), file)) {
        Aluno a;
        if (sscanf(linha, "%49[^,],%49[^,],%19[^,],%19[^,],%f,%f,%f",
                   a.materia, a.nome, a.ra, a.turma,
                   &a.nota1, &a.nota2, &a.media) == 7) {
            alunos[totalAlunos++] = a;
        }
    }
    //fecha o arquivo
    fclose(file);
    printf("\n%d registros carregados com sucesso!\n", totalAlunos);
}

//função para listar os alunos
void listarAlunos() {
    printf("\n=== LISTA DE TODOS OS ALUNOS ===\n");
    //roda um loop no vetor alunos printando em sequencia
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
    converter_para_upper(raBusca); // chama a função que converte os caracteres digitados em maiusculo

    int encontrado = 0;
    for (int i = 0; i < totalAlunos; i++) {
        if (strcmp(alunos[i].ra, raBusca) == 0) {
            printf("\n-----------------\nAluno encontrado:\n");
            printf("Materia: %s\nNome: %s\nRA: %s\nTurma: %s\nNotas: %.1f, %.1f\nMedia: %.2f\n",
                   alunos[i].materia, alunos[i].nome, alunos[i].ra, alunos[i].turma,
                   alunos[i].nota1, alunos[i].nota2, alunos[i].media);
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("Aluno com RA %s nao encontrado.\n", raBusca);
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
        printf("1 - Listar todos os dados de alunos e materias\n");
        printf("2 - Buscar aluno por RA\n");
        printf("3 - Relatorio de medias por disciplina\n");
        printf("4 - Selecionar materia para relatorio\n");
        printf("0 - Sair\n");
        printf("========================\n");
        printf("Escolha uma opcao: ");
    

        //inserção de um pequeno loop para verificar se a entrada do usuário é um numero, limpa buffer
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n' && !feof(stdin));
            opcao = -1; // define um valor invalido para forçar o default

        }

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

            case 4:
            {int selecao = selecao_materias();            
            if (selecao >= 0 && selecao < NUM_OPCOES_MATERIA) 
            {listarPorMateria(materias_mapa[selecao]);} 
            else if (selecao == 99) 
            {printf("Retornando ao menu principal.\n");}
            }
            break;

            case 0:
                printf("Programa encerrado.\n");
                break;

            default:
                printf("Escolha invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}