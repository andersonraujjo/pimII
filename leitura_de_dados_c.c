#include <stdio.h> // padrão para entrada e saída de dados
#include <stdlib.h>
#include <string.h> // para comparação de strings
#include <ctype.h> // para conversão em upper

#define MAX_LINHA 256
#define MAX_ALUNOS 500

//struct de todos os dados do csv
typedef struct {
    char materia[50];
    char nome[50];
    char ra[20];
    char turma[20];
    float nota1;
    float nota2;
    float media;
} Aluno;

Aluno alunos[MAX_ALUNOS]; // vetor principal com todos os dados de todos os alunos
int totalRegistros = 0; // contabiliza o total de registros que foram encontrados no csv


//função para carregar os dados do arquivo csv
void carregarCSV() {
    FILE *file = fopen("alunos.csv", "r");//abre no modo leitura
    if (file == NULL) {
        printf("Erro: nao foi possivel abrir o arquivo.\n");
        return;
    }

    char linha[MAX_LINHA];// armazena o texto bruto de cada linha armazenando no vetor (linha)
    fgets(linha, sizeof(linha), file); // pula o cabeçalho

    while (fgets(linha, sizeof(linha), file)) {
        Aluno a;
        if (sscanf(linha, "%49[^,],%49[^,],%19[^,],%19[^,],%f,%f,%f",
                   a.materia, a.nome, a.ra, a.turma,
                   &a.nota1, &a.nota2, &a.media) == 7) {
            alunos[totalRegistros++] = a; //salva os dados lidos no vetor global alunos
        }
    }
    //fecha o arquivo
    fclose(file);
    printf("\n%d registros carregados com sucesso!\n", totalRegistros);
}


// vetor para mapear a escolha numérica para o nome da matéria no CSV
char* materias_mapa[] = {
    "ENGENHARIA DE SOFT AGIL", // 0
    "PYTHON",                 // 1
    "C",                      // 2
    "ANALISE DE PROJETOS" // 3
};
#define NUM_OPCOES_MATERIA 4



//função para definir escolhas por materia
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
            while (getchar() != '\n' && !feof(stdin)); //limpa buffer do teclado
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



//função para converter os caracteres do buscaRA em maiusculo
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
    
    for (int i = 0; i < totalRegistros; i++) {
        // Compara o nome da matéria do aluno com a matéria buscada
        const char *status;
        if (strcmp(alunos[i].materia, materia_buscada) == 0) {
     
            //outro if para verificar se o status do aluno esta aprovado ou nao
             if (alunos[i].media >= 7.0) {
            status = "APROVADO";
            } else {
            status = "REPROVADO";
            }
            
            // Imprime os detalhes do aluno/materia
            printf("%s | %s | %s | %s | %.1f | %.1f | Media: %.2f | %s\n",
                   alunos[i].materia, alunos[i].nome, alunos[i].ra,
                   alunos[i].turma, alunos[i].nota1, alunos[i].nota2, alunos[i].media, status);
            
            encontrado = 1;
        }
    }
    
    if (!encontrado) {
        printf("Nenhum registro encontrado para a materia '%s'.\n", materia_buscada);
    }
}




//função para listar os alunos
void listarAlunos() {
    printf("\n=== LISTA DE TODOS OS ALUNOS ===\n");
    printf("MATERIA | NOME | RA | TURMA | N1 | N2 | MEDIA | STATUS\n");
    printf("-----------------------------------------------------------------\n"); 


    // Roda um loop no vetor alunos para calcular e imprimir
    for (int i = 0; i < totalRegistros; i++) {
        const char *status;
        
        // Determina o status
        if (alunos[i].media >= 7.0) {
            status = "APROVADO";
        } else {
            status = "REPROVADO";
        }

        // Imprime os detalhes do aluno atual, incluindo o status 
        printf("%s | %s | %s | %s | %.1f | %.1f | Media: %.2f | %s\n",
               alunos[i].materia, alunos[i].nome, alunos[i].ra,
               alunos[i].turma, alunos[i].nota1, alunos[i].nota2, alunos[i].media, status);
    }
    printf("----------------------------------------------------------------\n"); 
}

//função da busca por ra
void buscarPorRA() {
    char raBusca[20];//limita em 20
    printf("Digite o RA do aluno: ");
    scanf("%s", raBusca);
    converter_para_upper(raBusca); // chama a função que converte os caracteres digitados em maiusculo

    int encontrado = 0;
    for (int i = 0; i < totalRegistros; i++) {
        if (strcmp(alunos[i].ra, raBusca) == 0) {
            printf("\n-----------------\nAluno encontrado:\n");
            printf("Materia: %s\nNome: %s\nRA: %s\nTurma: %s\nNotas: %.1f, %.1f\nMedia: %.2f\n",
                   alunos[i].materia, alunos[i].nome, alunos[i].ra, alunos[i].turma,
                   alunos[i].nota1, alunos[i].nota2, alunos[i].media);
            encontrado = 1; //roda o for no vetor alunos e printa os dados em sequencia
        }
    }
    //se não encontrar cai aqui
    if (!encontrado) {
        printf("Aluno com RA %s nao encontrado.\n", raBusca);
    }
}

// Função para lsitar a qtd de aprovados e reprovados (geral, todas as materias)
void relatorioAprovacao() {
    printf("\nRELACAO DE APROVADOS / REPROVADOS (GERAL) \n");
    printf("----------------------------------------\n");

    //contadores para incrementar +1 a cada loop
    int aprovados_cont = 0;
    int reprovados_cont = 0;

    for (int i = 0; i < totalRegistros; i++) {
        const char *status;
        
        // Verifica a condição de aprovação
        if (alunos[i].media >= 7.0) {
            aprovados_cont++;} 
            else {
            reprovados_cont++;}
    }
    
    printf("Total de Aprovados: %d\n", aprovados_cont);
    printf("Total de Reprovados: %d\n", reprovados_cont);
}

//função principal
int main() {
    int opcao;

    carregarCSV();
    //força o menu 1 vez
    do {
        printf("\n========= MENU =========\n");
        printf("1 - Listar todos os dados de alunos e materias\n");
        printf("2 - Buscar aluno por RA\n");
        printf("3 - Relacao de aprovados e reprovados\n");
        printf("4 - Selecionar materia para relatorio\n");
        printf("0 - Sair\n");
        printf("========================\n");
        printf("Escolha uma opcao: ");
    

        //inserção de um pequeno loop para verificar se a entrada do usuário é um numero, limpa buffer
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n' && !feof(stdin));
            opcao = -1; // define um valor invalido para forçar o default

        }

        //switch case pra validar as opções (cada case aciona uma função, exceto 0 e default)
        switch (opcao) {
            case 1:
                listarAlunos();

                break;
            case 2:
                buscarPorRA();

                break;
            case 3:
                relatorioAprovacao();
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