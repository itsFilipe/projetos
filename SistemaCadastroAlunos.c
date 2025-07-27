#include <stdio.h>
#include <string.h>
#include <strings.h>

#define MAX 100

struct Aluno
{
    int matricula;
    char nome[50];
    int idade;
    char curso[50];
    float notaMedia;
};

int main()
{
    struct Aluno alunos[MAX];
    int opcao, sentinela, totalAlunos = 0, buscaMatricula, encontrado, proximaMatricula =1 ;
    char buscaNome[50], buscaCurso[50];

    do
    {
        printf("==========================================\n");
        printf("              SISTEMA ESCOLAR             \n");
        printf("==========================================\n");
        printf("1 - Adicionar aluno\n");
        printf("2 - Buscar pela matricula\n");
        printf("3 - Buscar pelo primeiro nome\n");
        printf("4 - Buscar por curso\n");
        printf("5 - Contagem dos alunos\n");
        printf("6 - Excluir aluno\n");
        printf("7 - Atualizar aluno\n");
        printf("8 - Sair\n");
        printf("==========================================\n");

        printf("Escolha uma opcao: ");
        scanf("%i", &opcao);
        getchar(); // limpa o \n do buffer
        
        switch (opcao)
        {
        case 1:
            do
            {
                if (totalAlunos>=MAX)
                {
                    printf("O valor maximo de contatos foi atingido (100)\n");
                    break;
                }

                alunos[totalAlunos].matricula = proximaMatricula;
                proximaMatricula++;

                printf("\nMatricula %i \n", alunos[totalAlunos].matricula);

                printf("Nome: ");
                fgets(alunos[totalAlunos].nome, sizeof(alunos[totalAlunos].nome), stdin);
                alunos[totalAlunos].nome[strcspn(alunos[totalAlunos].nome, "\n")] = 0;  // remove o \n

                if (strlen(alunos[totalAlunos].nome) == 0)
                {
                    printf("Nome nao pode ficar em branco. Tente novamente. \n");
                    break;
                }

                printf("Idade: ");
                scanf("%i", &alunos[totalAlunos].idade);

                if (alunos[totalAlunos].idade < 1 )
                {
                    printf("Idade deve ser maior que 1");
                    break;
                }

                getchar(); // limpa o \n após scanf
                
                printf("Curso: ");
                fgets(alunos[totalAlunos].curso, sizeof(alunos[totalAlunos].curso), stdin);
                alunos[totalAlunos].curso[strcspn(alunos[totalAlunos].curso, "\n")] = 0;  // remove o \n

                if (strlen(alunos[totalAlunos].curso) == 0)
                {
                    printf("Curso nao pode ficar em branco. Tente novamente. \n");
                    break;
                }

                printf("Nota media: ");
                scanf("%f", &alunos[totalAlunos].notaMedia);

                getchar(); // limpa o \n após scanf

                totalAlunos++;

                printf("\nDeseja continuar? SIM(1) / NAO(2)\n");
                scanf("%i", &sentinela);

                getchar(); // limpa o \n após scanf
            } while (sentinela == 1 );

            break;

        case 2:
            if (totalAlunos == 0)
            {
                printf("Nenhum aluno cadastrado ainda.\n");
                break;
            }

            printf("Digite o numero da matricula: ");
            scanf("%i", &buscaMatricula);

            getchar(); // limpa o \n do buffer

            encontrado = 0;

            for(int i = 0; i < totalAlunos; i++)
            {
                if (buscaMatricula == alunos[i].matricula)
                {
                    printf("Matricula: %i\n", alunos[i].matricula);
                    printf("Nome: %s\n", alunos[i].nome);
                    printf("Idade: %i\n", alunos[i].idade);
                    printf("Curso: %s\n", alunos[i].curso);
                    printf("Nota media: %f\n\n", alunos[i].notaMedia);
                    encontrado = 1;
                    break;
                }
            }
            
            if (!encontrado)
                {
                    printf("\nNenhum nome foi encontrado");
                }

            break;

        case 3:
            if (totalAlunos == 0)
            {
                printf("Nenhum aluno cadastrado ainda.\n");
                break;
            }    

            printf("\nBusque por um nome: ");
            fgets(buscaNome, sizeof(buscaNome), stdin);
            buscaNome[strcspn(buscaNome, "\n")] = 0;

            encontrado = 0;

            for (int i = 0; i < totalAlunos; i++)
            {
                if (strncasecmp(alunos[i].nome, buscaNome, strlen(buscaNome)) == 0)
                {   
                    printf("Matricula: %i\n", alunos[i].matricula);
                    printf("Nome: %s\n", alunos[i].nome);
                    printf("Idade: %i\n", alunos[i].idade);
                    printf("Curso: %s\n\n", alunos[i].curso);
                    printf("Nota media: %f\n\n", alunos[i].notaMedia);
                    encontrado = 1;
                    // Se quiser encontrar todos os que começam com esse nome, tire o break:
                    // break;
                 }
            }
                if (!encontrado)
                {
                    printf("\nNenhum nome foi encontrado\n");
                }

            break;

        case 4:
            if (totalAlunos == 0)
            {
                printf("Nenhum aluno cadastrado ainda.\n");
                break;
            }

            printf("\nBusque por um curso: ");
            fgets(buscaCurso, sizeof(buscaCurso), stdin);
            buscaCurso[strcspn(buscaCurso, "\n")] = 0;

            encontrado = 0;

            for (int i = 0; i < totalAlunos; i++)
            {
                if (strncasecmp(alunos[i].curso, buscaCurso, strlen(buscaCurso)) == 0)
                {   
                    printf("Matricula: %i\n", alunos[i].matricula);
                    printf("Nome: %s\n", alunos[i].nome);
                    printf("Idade: %i\n", alunos[i].idade);
                    printf("Curso: %s\n\n", alunos[i].curso);
                    printf("Nota media: %f\n\n", alunos[i].notaMedia);
                    encontrado = 1;
                    // Se quiser encontrar todos os que estao nesse curso, tire o break:
                    // break;
                 }
            }
                if (!encontrado)
                {
                    printf("\nNenhum nome foi encontrado\n");
                }

            break;

        case 5:
            if (totalAlunos == 0)
            {
                printf("Nenhum aluno cadastrado ainda.\n");
                break;
            }

            printf("O sistema possui %i alunos cadastrados.\n", totalAlunos);

            break;

        case 6:
            printf("Digite a matricula do aluno que deseja excluir: ");
            scanf("%i", &buscaMatricula);
            
            getchar(); // limpa o \n do buffer

            for (int i = 0; i < totalAlunos; i++)
            {
                if (alunos[i].matricula == buscaMatricula)
                {
                // Desloca os elementos à esquerda
                for (int j = i; j < totalAlunos - 1; j++) {
                    alunos[j] = alunos[j + 1];
                }
                totalAlunos--;  // reduz o total de registros
                printf("Aluno removido com sucesso!\n");
                encontrado = 1;
                break;
                }
            }

            if (!encontrado)
            {
                printf("Aluno com essa matricula nao foi encontrado.\n");
            }

            break;

        case 7:
            encontrado = 0;

            printf("Digite a matricula do aluno a ser atualizado: ");
            scanf("%i", &buscaMatricula);

            for (int i = 0; i < totalAlunos; i++)
            {
                if (alunos[i].matricula == buscaMatricula)
                {
                printf("Nome atual: %s\n", alunos[i].nome);
                printf("Digite o novo nome: ");

                getchar(); // Limpa o buffer

                fgets(alunos[i].nome, sizeof(alunos[i].nome), stdin);
                alunos[i].nome[strcspn(alunos[i].nome, "\n")] = 0;

                printf("Digite a nova idade: ");
                scanf("%d", &alunos[i].idade);

                printf("Digite o novo curso: ");

                getchar(); // limpa

                fgets(alunos[i].curso, sizeof(alunos[i].curso), stdin);
                alunos[i].curso[strcspn(alunos[i].curso, "\n")] = 0;

                printf("Digite a nova nota media: ");
                scanf("%f", &alunos[i].notaMedia);

                getchar(); // limpa

                printf("Aluno atualizado com sucesso!\n");
                encontrado = 1;
                break;
                }
            }

            if (!encontrado)
            {
                printf("Aluno com essa matricula nao foi encontrado.\n");
            }

            break;

        case 8:
            printf("\nSaindo do sistema...\n");

            break;
        
        default:
            printf("Nenhuma opcao valida foi escolhida.");
            break;
        }
    } while (opcao!=8);
    
    return 0;
}