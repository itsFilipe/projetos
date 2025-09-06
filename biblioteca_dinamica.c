#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DISPONIVEL 1
#define EMPRESTADO 0

// Constantes para retornos das funções
#define SUCESSO 1
#define ERRO 0
#define SIM 1
#define NAO 0
#define CONFIRMADO 1
#define CANCELADO 0

static int proximo_id = 1;

typedef struct
{
    int id;
    char titulo[100];
    char autor[50];
    int ano;
    int disponivel; // 1 = disponivel, 0 = emprestado
} Livro;

typedef struct
{
    Livro *livros; 
    int capacidade;
    int total_livros;
} Biblioteca;

int inicializar_biblioteca(Biblioteca *b);
void imprimir_menu();
void adicionar_livro(Biblioteca *b);
void print_livro(Livro *livro);
int inicializar_biblioteca(Biblioteca *b);
int tem_livros_cadastrados(Biblioteca *b);
Livro* buscar_por_id(Biblioteca *b, int id);
int emprestar_livro(Biblioteca *b, int id);
int devolver_livro(Biblioteca *b, int id);
int digitar_id();
int remover_livro(Biblioteca *b, int id);
int confirmar_operacao();
void finalizar_biblioteca(Biblioteca *b);

int main()
{   
    Biblioteca minha_biblioteca;
    if(inicializar_biblioteca(&minha_biblioteca) == SUCESSO)
    {
        printf("Biblioteca inicializada!\n");
    }
    else
    {
        printf("Erro em alocar memoria.");
        return 1;
    }

    char buffer[100];
    int opcao = 0;

    while (opcao != 7)
    {
        imprimir_menu();

        printf("Digite a opcao:\n");
        fgets(buffer, sizeof(buffer), stdin);
        opcao = (int)strtol(buffer, NULL, 10);  // converte string -> int

        switch (opcao)
        {
        case 1: //add livro
            adicionar_livro(&minha_biblioteca);
            break;

        case 2: //listar livros
            if (!tem_livros_cadastrados(&minha_biblioteca))
                break;

            for (int i = 0; i < minha_biblioteca.total_livros; i++)
            {
                print_livro(&minha_biblioteca.livros[i]);
            }
            break;

        case 3: //buscar por id
            if (!tem_livros_cadastrados(&minha_biblioteca))
                break;

            Livro *livro_encontrado = buscar_por_id(&minha_biblioteca, digitar_id());

            if(livro_encontrado == NULL)
            {
                printf("Id nao encontrado.\n");
            }
            else
            {
                printf("Livro encontrado!\n");
                print_livro(livro_encontrado);
            }
            break;

        case 4: //emprestar livro
            if (!tem_livros_cadastrados(&minha_biblioteca))
                break;

            int id_emprestar = digitar_id();
            emprestar_livro(&minha_biblioteca, id_emprestar);
            break;

        case 5: //devolver livro
            if (!tem_livros_cadastrados(&minha_biblioteca))
                break;

            int id_devolver = digitar_id();
            devolver_livro(&minha_biblioteca, id_devolver);
            break;

        case 6: //remover livro
            if (!tem_livros_cadastrados(&minha_biblioteca))
                break;

            int id = digitar_id();

            if (remover_livro(&minha_biblioteca, id) == SUCESSO)
            {
                printf("Operacao realizada com sucesso!\n");
            }
            break;

        case 7: //sair do sistema
            printf("Saindo do sistema.\n");
            break;

        default:
            printf("Digite uma opcao valida.\n");
            break;
        }
    }

    printf("Total de livros: %d\n", minha_biblioteca.total_livros);

    finalizar_biblioteca(&minha_biblioteca);

    getchar();
    return 0;
}

int inicializar_biblioteca(Biblioteca *b)
{
    b->total_livros = 0;
    b->capacidade = 2;
    b->livros = malloc(2 * sizeof(Livro));

    if(b->livros == NULL)
    {
        printf("Erro em alocar memoria.");
        return ERRO;
    }

    return SUCESSO;
}

void imprimir_menu()
{
    printf("--------------------------------------------------\n");
    printf("-------------BIBLIOTECA DINAMICA------------------\n");
    printf("1- Adicionar livros\n");
    printf("2- Listar livros\n");
    printf("3- Buscar por Id\n");
    printf("4- Emprestar livro\n");
    printf("5- Devolver livro\n");
    printf("6- Remover livro\n");
    printf("7- Sair do sistema\n");
    printf("\n");
}

int digitar_id()
{
    int id;
    char buffer[50];
    char *endptr;

    do {
        printf("Digite o ID desejado: ");
        fgets(buffer, sizeof(buffer), stdin);
        id = (int)strtol(buffer, &endptr, 10);

        if (*endptr != '\n' && *endptr != '\0') {
            printf("ERRO: Digite apenas numeros!\n");
            id = -1;  //força repetir
        }
    } while (id <= 0);

    return id;
}

void adicionar_livro(Biblioteca *b)
{   
    if(b->total_livros >= b->capacidade)
    {
        Livro *temp = realloc(b->livros, 2 * b->capacidade * sizeof(Livro));
        if(temp == NULL)
        {
            printf("Erro em alocar memoria.\n");
            return;
        }
        b->livros = temp;
        b->capacidade *= 2;
    }

    int proximo_indice = b->total_livros;
    b->total_livros++;

    char buffer[50]; //para ler o ano como string
    char *endptr; //para verificar se ano é numero.

    b->livros[proximo_indice].id = proximo_id++;

    printf("Digite o titulo do livro: \n");
    fgets(b->livros[proximo_indice].titulo, sizeof(b->livros[proximo_indice].titulo), stdin);
    b->livros[proximo_indice].titulo[strcspn(b->livros[proximo_indice].titulo, "\n")] = '\0';  // remove o \n do final

    printf("Digite o autor do livro: \n");
    fgets(b->livros[proximo_indice].autor, sizeof(b->livros[proximo_indice].autor), stdin);
    b->livros[proximo_indice].autor[strcspn(b->livros[proximo_indice].autor, "\n")] = '\0';  

    do {
        printf("Digite o ano do livro: \n");
        fgets(buffer, sizeof(buffer), stdin);
        b->livros[proximo_indice].ano = (int)strtol(buffer, &endptr, 10);

        if (*endptr != '\n' && *endptr != '\0') {
            printf("ERRO: Digite apenas numeros!\n");
        }
    } while (*endptr != '\n' && *endptr != '\0');

    do {
        printf("Digite se o livro esta disponivel: (1 - sim, 0 - nao)\n");
        fgets(buffer, sizeof(buffer), stdin);
        b->livros[proximo_indice].disponivel = (int)strtol(buffer, &endptr, 10);

        if (*endptr != '\n' && *endptr != '\0') {
            printf("ERRO: Digite apenas numeros!\n");
            b->livros[proximo_indice].disponivel = -1;
        }
        else if(b->livros[proximo_indice].disponivel != 1 && b->livros[proximo_indice].disponivel != 0)
        {
            printf("ERRO: Digite apenas (1 - sim, 0 - nao)!\n");
            b->livros[proximo_indice].disponivel = -1;
        }
    } while (b->livros[proximo_indice].disponivel == -1);


    printf("Digite se o livro esta disponivel: (1 - sim, 0 - nao)\n");
    fgets(buffer, sizeof(buffer), stdin);
    b->livros[proximo_indice].disponivel = (int)strtol(buffer, NULL, 10);  

    printf("Livro adicionado com sucesso!\n");
}

void print_livro(Livro *livro)
{       
    printf("\nId: %d\n", livro->id);
    printf("Titulo: %s\n", livro->titulo);
    printf("Autor: %s\n", livro->autor);
    printf("Ano: %d\n", livro->ano);

    if(livro->disponivel == DISPONIVEL)
    {
        printf("Esta disponivel? Sim\n");
        printf("\n");
    }
    else if(livro->disponivel == EMPRESTADO)
    {
        printf("Esta disponivel? Nao, esta emprestado\n");
        printf("\n");
    }
}

int tem_livros_cadastrados(Biblioteca *b)
{
    if(b->total_livros == 0)
    {
        printf("Nao existem livros cadastrados\n");
        return NAO;
    }

    return SIM;
}

Livro *buscar_por_id(Biblioteca *b, int id)
{
    for (int i = 0; i < b->total_livros; i++)
    {
        if(id == b->livros[i].id)
        {
            return &b->livros[i];
        }
  }

    return NULL;
}

int emprestar_livro(Biblioteca *b, int id) 
{
    Livro *livro_encontrado = buscar_por_id(b, id);

    if(livro_encontrado == NULL)
    {
        printf("Livro com ID %d nao encontrado.\n", id);
        return ERRO;
    }

    if(livro_encontrado->disponivel != DISPONIVEL)
    {
        printf("Livro ja esta emprestado.\n");
        return ERRO;
    }

    print_livro(livro_encontrado);

    if(confirmar_operacao() == CONFIRMADO)
    {
        livro_encontrado->disponivel = EMPRESTADO;
        printf("\nLivro emprestado com sucesso.\n");
        return SUCESSO;
    }
    else
    {
        printf("Operacao cancelada.\n");
        return CANCELADO;
    }
}

int devolver_livro(Biblioteca *b, int id)
{
    Livro *livro_encontrado = buscar_por_id(b, id);

    if(livro_encontrado == NULL)
    {
        printf("Livro com ID %d nao encontrado.\n", id);
        return ERRO;
    }

    if(livro_encontrado->disponivel == DISPONIVEL)
    {
        printf("Livro ja estava disponivel.\n");
        return SUCESSO;
    }

    print_livro(livro_encontrado);

    if(confirmar_operacao() == CONFIRMADO)
    {
        livro_encontrado->disponivel = DISPONIVEL;
        printf("Livro devolvido com sucesso.\n");
        return SUCESSO;
    }
    else
    {
        printf("Operacao cancelada.\n");
        return CANCELADO;
    }
}

int remover_livro(Biblioteca *b, int id)
{
    Livro* livro_encontrado = buscar_por_id(b, id);

    if (livro_encontrado == NULL) {
        printf("Livro com ID %d nao encontrado!\n", id);
        return ERRO;
    }

    print_livro(livro_encontrado);

    if(livro_encontrado->disponivel == EMPRESTADO)
    {
        printf("ERRO: Nao e possivel remover livro emprestado!\n");
        printf("Devolva o livro antes de remove-lo.\n");
        return ERRO;
    }

    if(confirmar_operacao() == CONFIRMADO)
    {
        int indice = livro_encontrado - b->livros;

        for (int i = indice; i < b->total_livros - 1; i++)
        {
            b->livros[i] = b->livros[i + 1];
        }

        b->total_livros--;

        if(b->total_livros > 0 && b->capacidade > 2 && b->total_livros < b->capacidade / 4)
        {
            Livro *temp = realloc(b->livros, (b->capacidade / 2) * sizeof(Livro));
            
            if(temp != NULL)  
            {
                b->livros = temp;
                b->capacidade /= 2; 
                printf("Biblioteca otimizada! Nova capacidade: %d\n", b->capacidade);
            }
            else
            {
                // Se falhar, não é crítico - continua com a capacidade maior
                printf("Aviso: Nao foi possivel otimizar a memoria.\n");
            }
        }

        printf("Livro removido com sucesso!\n");
        return SUCESSO;
    }
    else
    {
        printf("Operacao cancelada.\n");
        return CANCELADO;
    } 
}

int confirmar_operacao()
{
    char resposta[10];
    printf("Tem certeza? (s/n): ");
    fgets(resposta, sizeof(resposta), stdin);

    if (resposta[0] == 's' || resposta[0] == 'S') {
        return CONFIRMADO;
    }
    return CANCELADO;
}

void finalizar_biblioteca(Biblioteca *b)
{
    free(b->livros);           
    b->livros = NULL;       
    b->total_livros = 0;       
    b->capacidade = 0;
}