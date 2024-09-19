#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // Para usar strcasecmp

struct Livro //cria uma struct para armazenar informações de livros
{
    char titulo[100];
    char autor[100];
    char genero[50];
    char isbn[14];
    int quantidade;
    float preco;
};

struct Funcionario //cria uma struct para armazenar informações dos funcionários
{
    int id;
    char nome[100];
    char cargo[50];
    float salario;
    int idade;
    int senha;
};

int carregar_livros_txt(struct Livro livros[]) 
{
    FILE *arquivo = fopen("livros.txt", "r");
    if (arquivo == NULL) 
        {
            printf("Erro ao abrir o arquivo para leitura.\n");
            return 0;
        }
    int QuantidadeLivros = 0;

    while (fscanf(arquivo, "%99[^;];%99[^;];%49[^;];%19[^;];%d;%f\n",
            livros[QuantidadeLivros].titulo, livros[QuantidadeLivros].autor, livros[QuantidadeLivros].genero,
            livros[QuantidadeLivros].isbn, &livros[QuantidadeLivros].quantidade, &livros[QuantidadeLivros].preco) != EOF) 
        {
            QuantidadeLivros++;
        }
    fclose(arquivo);
    return QuantidadeLivros;
}

void pesquisarLivro(struct Livro livros[], int QuantidadeLivros, char parametro[], char tipoBusca[]) //função de pesquisa de livro no sistema
{
    int encontrado = 0; //já é atribuído o valor de 0 como se o livro não existisse no sistema

    for (int i = 0; i < QuantidadeLivros; i++) //a repetição passa de livro por livro cadastrado
    {
        if ((strcmp(tipoBusca, "titulo") == 0 && strcasecmp(livros[i].titulo, parametro) == 0) ||
            (strcmp(tipoBusca, "autor") == 0 && strcasecmp(livros[i].autor, parametro) == 0) ||
            (strcmp(tipoBusca, "genero") == 0 && strcasecmp(livros[i].genero, parametro) == 0) ||
            (strcmp(tipoBusca, "isbn") == 0 && strcasecmp(livros[i].isbn, parametro) == 0)) //a condição verifica se o parametro e o tipo de busca são iguais
        {
            
            printf("\n\nLivro encontrado:\n");
            printf("Titulo: %s\n", livros[i].titulo);
            printf("Autor: %s\n", livros[i].autor);
            printf("Genero: %s\n", livros[i].genero);
            printf("ISBN: %s\n", livros[i].isbn);
            printf("Quantidade em estoque: %d\n", livros[i].quantidade);
            printf("Preco: R$ %.2f\n\n", livros[i].preco);
            
            encontrado = 1;
            break;  // Encerra o loop ao encontrar o livro
        }
    }

    if (!encontrado)  // Se Encontrado=0, quer dizer que o sistema não encontrou o livro
    { 
        printf("\nLivro não encontrado.\n");
    }
}

void removerLivro(struct Livro livros[], int *QuantidadeLivros, char parametro[], char tipoBusca[]) // Função de remover livro no sistema
{
    int encontrado = 0;

    // Procura o livro para remover
    for (int i = 0; i < *QuantidadeLivros; i++) 
    {
        if ((strcmp(tipoBusca, "titulo") == 0 && strcasecmp(livros[i].titulo, parametro) == 0) ||
            (strcmp(tipoBusca, "isbn") == 0 && strcasecmp(livros[i].isbn, parametro) == 0)) 
        {
            printf("\n\nRemovendo livro '%s' do sistema\n...\n...\n...\nLivro removido com sucesso.\n", livros[i].titulo);

            // Desloca os livros subsequentes para preencher o espaço do livro removido
            for (int j = i; j < *QuantidadeLivros - 1; j++) 
            {
                livros[j] = livros[j + 1];
            }

            (*QuantidadeLivros)--; // Diminui o contador total de livros
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) // Se Encontrado=0, quer dizer que o sistema não encontrou o livro
    { 
        printf("\nLivro não encontrado.\n");
    }

    // Atualiza o arquivo com a lista de livros modificada
    FILE *arquivo = fopen("livros.txt", "w"); // Abre o arquivo para escrita binária
    if (arquivo == NULL) 
    {
        printf("Erro ao abrir o arquivo para atualização.\n");
        return; // Encerra a função se não conseguir abrir o arquivo
    }

    fwrite(livros, sizeof(struct Livro), *QuantidadeLivros, arquivo); // Escreve a lista de livros no arquivo

    fclose(arquivo); // Fecha o arquivo após a escrita
}

void disponibilidade(struct Livro livros[], int QuantidadeLivros, char parametro[], char tipoBusca[]) //função de quantidade de exemplares de um livro no sistema
{
    int encontrado = 0; //já é atribuído o valor de 0 como se o livro não existisse no sistema

    for (int i = 0; i < QuantidadeLivros; i++) //a repetição passa de livro por livro cadastrado
    {
        if ((strcmp(tipoBusca, "titulo") == 0 && strcasecmp(livros[i].titulo, parametro) == 0) ||
            (strcmp(tipoBusca, "isbn") == 0 && strcasecmp(livros[i].isbn, parametro) == 0)) //a condição verifica se o parametro e o tipo de busca são iguais
        {
            
            printf("\n\nA livraria possui %d exemplares do livro %s\n", livros[i].quantidade, parametro);
            
            encontrado = 1;
            break;  // Encerra o loop ao encontrar o livro
        }
    }

    if (!encontrado)  // Se Encontrado=0, quer dizer que o sistema não encontrou o livro
    { 
        printf("\nLivro não encontrado.\n");
    }
}

void reabastecer(struct Livro livros[], int QuantidadeLivros, char parametro[], char tipoBusca[]) //função de reabastecer exemplares de livros no sistema
{
    int encontrado = 0; //já é atribuído o valor de 0 como se o livro não existisse no sistema

    for (int i = 0; i < QuantidadeLivros; i++) //a repetição passa de livro por livro cadastrado
    {
        if ((strcmp(tipoBusca, "titulo") == 0 && strcasecmp(livros[i].titulo, parametro) == 0) ||
            (strcmp(tipoBusca, "isbn") == 0 && strcasecmp(livros[i].isbn, parametro) == 0)) //a condição verifica se o parametro e o tipo de busca são iguais
        {
            
            printf("\n\nA livraria possui %d exemplares do livro %s\n", livros[i].quantidade, parametro);
            printf("Deseja colocar quantos exemplares a mais? ");
            int exemplares;
            scanf("%d", &exemplares);
            printf("Adicionando exemplares no sistema\n...\n...\n...\nAgora o livro %s possui %d exemplares", parametro, livros[i].quantidade+exemplares);
            
            encontrado = 1;
            break;  // Encerra o loop ao encontrar o livro
        }
    }

    if (!encontrado)  // Se Encontrado=0, quer dizer que o sistema não encontrou o livro
    { 
        printf("\nLivro não encontrado.\n");
    }
}

void venda(struct Livro livros[], int QuantidadeLivros, char parametro[], char tipoBusca[]) //função de registrar venda no sistema e atualizar estoque
{
    int encontrado = 0; //já é atribuído o valor de 0 como se o livro não existisse no sistema

    for (int i = 0; i < QuantidadeLivros; i++) //a repetição passa de livro por livro cadastrado
    {
        if ((strcmp(tipoBusca, "titulo") == 0 && strcasecmp(livros[i].titulo, parametro) == 0) ||
            (strcmp(tipoBusca, "isbn") == 0 && strcasecmp(livros[i].isbn, parametro) == 0)) //a condição verifica se o parametro e o tipo de busca são iguais
        {
            
            printf("\n\nA livraria possui %d exemplares do livro %s\n", livros[i].quantidade, parametro);
            printf("Quantos livros serao vendidos? ");
            int exemplares;
            scanf("%d", &exemplares);
            printf("Venda sendo registrada\n...\n...\n...\nAgora o livro %s possui %d exemplares", parametro, livros[i].quantidade-exemplares);
            
            encontrado = 1;
            break;  // Encerra o loop ao encontrar o livro
        }
    }

    if (!encontrado)  // Se Encontrado=0, quer dizer que o sistema não encontrou o livro
    { 
        printf("\nLivro não encontrado.\n");
    }
}

float receita(struct Livro livros[], int QuantidadeLivros) 
{
    int op;
    float receitaTotal = 0;

    printf("\nDeseja calcular a receita de qual tipo?\n1 - Um livro\n2 - Varios livros\nDigite: ");
    scanf("%d", &op);

    if(op == 1) 
    {
        char tipoBusca[10], parametro[100];
        int encontrado = 0;
        int exemplares;

        printf("\nEscreva o tipo de busca (titulo ou isbn): "); 
        scanf("%s", tipoBusca); //define qual método de busca o usuário deseja
        
        if (strcmp(tipoBusca, "titulo") != 0 && strcmp(tipoBusca, "isbn") != 0) // Verifique se o tipo de busca é válido
        {
            printf("Tipo de busca invalido.\n");
            return receitaTotal;
        }

        printf("Escreva o %s: ", tipoBusca);
        scanf(" %[^\n]", parametro); //define qual parametro o usuario deseja(título do livro em questão ou seu isbn)

        for (int i = 0; i < QuantidadeLivros; i++) 
        {
            if ((strcmp(tipoBusca, "titulo") == 0 && strcasecmp(livros[i].titulo, parametro) == 0) ||
                (strcmp(tipoBusca, "isbn") == 0 && strcasecmp(livros[i].isbn, parametro) == 0)) //compara o que o usuário digitou no sistema com oque está armazenado
            {
                printf("Quantos livros serao vendidos? ");
                if (scanf("%d", &exemplares) != 1 || exemplares < 0) //define quantos exemplares serão contados e compara se é válido(aior que 0)
                {
                    printf("Quantidade invalida. Por favor, insira um numero inteiro positivo.\n");
                    return receitaTotal;
                }

                if (exemplares <= livros[i].quantidade) //se os exemplares digitados for menor que  a quantidade presente no sistema, o computador efetua faz a conta
                {
                    receitaTotal = exemplares * livros[i].preco;
                    printf("Receita para %d exemplares do livro %s: R$ %.2f\n", exemplares, parametro, receitaTotal);
                } 
                else 
                {
                    printf("Quantidade de exemplares insuficiente.\n");
                }
                
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) // Se Encontrado=0, quer dizer que o sistema não encontrou o livro
        { 
            printf("Livro nao encontrado.\n");
        }
    }
    else if(op == 2) 
    {
        int exemplares;
        char parametro[100];
        float receitaParcial;
        int encontrado;

        printf("Para calcular a receita de varios livros, insira as seguintes informacoes para cada livro:\n");
        
        do
        {
            printf("\nEscreva o titulo ou ISBN do livro (ou digite 'fim' para terminar): ");
            scanf(" %[^\n]", parametro);

            if (strcasecmp(parametro, "fim") == 0) //se o usuário digitar fim, a repetição se encerra
            {
                break;
            }

            encontrado = 0;

            for (int i = 0; i < QuantidadeLivros; i++) 
            {
                if ((strcasecmp(livros[i].titulo, parametro) == 0) ||
                    (strcasecmp(livros[i].isbn, parametro) == 0)) 
                {
                    printf("Quantos livros serao vendidos? ");
                    if (scanf("%d", &exemplares) != 1 || exemplares < 0) 
                    {
                        printf("Quantidade invalida. Por favor, insira um número inteiro positivo.\n");
                        return receitaTotal;
                    }

                    if (exemplares <= livros[i].quantidade) 
                    {
                        receitaParcial = exemplares * livros[i].preco;
                        receitaTotal += receitaParcial;
                        printf("Receita para %d exemplares do livro %s: R$ %.2f\n", exemplares, parametro, receitaParcial);
                    } 

                    else 
                    {
                        printf("Quantidade de exemplares insuficiente para o livro %s.\n", parametro);
                    }

                    encontrado = 1;
                    break;
                }
            }

            if (!encontrado) // Se Encontrado=0, quer dizer que o sistema não encontrou o livro
            { 
                printf("Livro nao encontrado: %s.\n", parametro);
            }
        }
        while (1); // Continue até o usuário digitar "fim"
    }
    else 
    {
        printf("Opcao invalida.\n");
    }

    return receitaTotal;
}

void listarLivros(struct Livro livros[], int QuantidadeLivros, char parametro[], char tipoBusca[]) //função de listar livro por autor ou gênero
{
    int encontrado = 0; //já é atribuído o valor de 0 como se o livro não existisse no sistema
    int numero = 1;

    printf("Livros de %s...\n", parametro);

    for (int i = 0; i < QuantidadeLivros; i++) //a repetição passa de livro por livro cadastrado
    {
        if ((strcmp(tipoBusca, "genero") == 0 && strcasecmp(livros[i].genero, parametro) == 0) ||
            (strcmp(tipoBusca, "gênero") == 0 && strcasecmp(livros[i].genero, parametro) == 0) ||
            (strcmp(tipoBusca, "autor") == 0 && strcasecmp(livros[i].autor, parametro) == 0)) //a condição verifica se o parametro e o tipo de busca são iguais
        {
            
            printf("%d - %s\n", numero, livros[i].titulo);
            numero++;
            encontrado = 1;
        }
    }

    if (!encontrado)  // Se Encontrado=0, quer dizer que o sistema não encontrou os livros
    { 
        printf("\nLivros de %s não encontrado.\n", parametro);
    }
}

void cadastrarLivro(struct Livro livros[], int *QuantidadeLivros) // Função para cadastrar um novo livro
{
    struct Livro novoLivro;  // Mudança em "struct Livro" para adicionar o novo livro

    printf("\nDigite o titulo do livro: "); // Solicitar informações ao usuário
    fgets(novoLivro.titulo, sizeof(novoLivro.titulo), stdin);
    novoLivro.titulo[strcspn(novoLivro.titulo, "\n")] = 0;

    printf("Digite o autor do livro: "); 
    fgets(novoLivro.autor, sizeof(novoLivro.autor), stdin); //fgets lê o título do livro digitado e o armazena em novoLivro
    novoLivro.autor[strcspn(novoLivro.autor, "\n")] = 0; //substitui o \n por \0, removendo a nova linha da string, garantindo que esteja formatado corretamente.

    printf("Digite o ISBN do livro: ");
    fgets(novoLivro.isbn, sizeof(novoLivro.isbn), stdin);
    novoLivro.isbn[strcspn(novoLivro.isbn, "\n")] = 0;

    printf("Digite o genero do livro: ");
    fgets(novoLivro.genero, sizeof(novoLivro.genero), stdin);
    novoLivro.genero[strcspn(novoLivro.genero, "\n")] = 0;

    printf("Digite o preco do livro: ");
    scanf("%f", &novoLivro.preco);

    printf("Digite a quantidade inicial do livro: ");
    scanf("%d", &novoLivro.quantidade);

    getchar(); // Consumir o caractere de nova linha residual

    livros[*QuantidadeLivros] = novoLivro; //cadastra os novos dados do livro cadastrado no vetor Livros
    (*QuantidadeLivros)++; //incrementa a quantidade total de livros

    printf("Livro cadastrado com sucesso!\n");
}

void atualizarLivro(struct Livro livros[], int QuantidadeLivros, char parametro[], char tipoBusca[]) // Função para atualizar as informações de um livro
{
    int encontrado = 0;

    for (int i = 0; i < QuantidadeLivros; i++) {
        if ((strcmp(tipoBusca, "titulo") == 0 && strcmp(livros[i].titulo, parametro) == 0) ||
            (strcmp(tipoBusca, "isbn") == 0 && strcmp(livros[i].isbn, parametro) == 0)) {
            encontrado = 1;

            printf("Livro encontrado! O que voce gostaria de atualizar?\n");
            printf("[1] - Titulo\n[2] - Autor\n[3] - Genero\n[4] - Preco\n[5] - Quantidade\nDigite: ");
            
            int opcao;
            scanf("%d", &opcao);

            if (opcao == 1) 
            {
                printf("Digite o novo titulo: ");
                scanf(" %[^\n]", livros[i].titulo); //armazena nova informação
            } 

            else if (opcao == 2) 
            {
                printf("Digite o novo autor: ");
                scanf(" %[^\n]", livros[i].autor); //armazena nova informação
            } 

            else if (opcao == 3) 
            {
                printf("Digite o novo genero: ");
                scanf(" %[^\n]", livros[i].genero); //armazena nova informação
            } 

            else if (opcao == 4) 
            {
                printf("Digite o novo preco: ");
                scanf("%f", &livros[i].preco); //armazena nova informação
            } 

            else if (opcao == 5) 
            {
                printf("Digite a nova quantidade: ");
                scanf("%d", &livros[i].quantidade); //armazena nova informação
            } 

            else 
            {
                printf("Opcao invalida.\n");
                return;
            }

            printf("Informacoes atualizadas com sucesso!\n");
            return;
        }
    }

    if (!encontrado) // Se Encontrado=0, quer dizer que o sistema não encontrou o livro
    {
        printf("Livro nao encontrado.\n");
    }
}

void lerLivrosDoArquivo(struct Livro livros[], int *QuantidadeLivros) // Função para ler livros do arquivo
{
    FILE *file = fopen("livros.txt", "r");

    if (file == NULL) 
    {
        puts("Erro ao abrir o arquivo livros.txt para leitura.");
        *QuantidadeLivros = 0;
        return;
    }

    char linha[256]; // Buffer para armazenar cada linha do arquivo
    *QuantidadeLivros = 0;

    while (fgets(linha, sizeof(linha), file)) 
    {
        linha[strcspn(linha, "\n")] = '\0';

        if (sscanf(linha, "%49[^;];%49[^;];%29[^;];%19[^;];%d;%f",
                livros[*QuantidadeLivros].titulo,
                livros[*QuantidadeLivros].autor,
                livros[*QuantidadeLivros].genero,
                livros[*QuantidadeLivros].isbn,
                &livros[*QuantidadeLivros].quantidade,
                &livros[*QuantidadeLivros].preco) == 6) 
            {
                (*QuantidadeLivros)++;
            } 

        else 
            {
                printf("Erro ao processar a linha: %s\n", linha);
            }
    }
    fclose(file);
}

void mostrarLivros(struct Livro livros[], int QuantidadeLivros) // Função para mostrar os livros
{
    if (QuantidadeLivros == 0) 
    {
        printf("Nenhum livro disponivel para exibicao.\n");
        return;
    }

    for (int i = 0; i < QuantidadeLivros; i++) 
    {
        printf("Livro %d:\n", i + 1);
        printf("  Titulo: %s\n", livros[i].titulo);
        printf("  Autor: %s\n", livros[i].autor);
        printf("  Genero: %s\n", livros[i].genero);
        printf("  ISBN: %s\n", livros[i].isbn);
        printf("  Quantidade: %d\n", livros[i].quantidade);
        printf("  Preco: R$%.2f\n\n", livros[i].preco);
    }
}

void lerFuncionariosDoArquivo(struct Funcionario funcionarios[], int *QuantidadeFuncionarios) 
{
    FILE *file = fopen("funcionarios.txt", "r");

    if (file == NULL) 
    {
        puts("Erro ao abrir o arquivo funcionarios.txt para leitura.");
        *QuantidadeFuncionarios = 0;
        return;
    }

    char linha[256]; // Buffer para armazenar cada linha do arquivo
    *QuantidadeFuncionarios = 0;

    while (fgets(linha, sizeof(linha), file)) 
    {
        linha[strcspn(linha, "\n")] = '\0';

        if (sscanf(linha, "%d;%50[^;];%50[^;];%f;%d;%d",
                   &funcionarios[*QuantidadeFuncionarios].id,
                   funcionarios[*QuantidadeFuncionarios].nome,
                   funcionarios[*QuantidadeFuncionarios].cargo,
                   &funcionarios[*QuantidadeFuncionarios].salario,
                   &funcionarios[*QuantidadeFuncionarios].idade,
                   &funcionarios[*QuantidadeFuncionarios].senha) == 6) 
        {
            (*QuantidadeFuncionarios)++;
        } 

        else 
        {
            printf("Erro ao processar a linha: %s\n", linha);
        }
    }

    fclose(file);
}

void mostrarFuncionarios(struct Funcionario funcionarios[], int QuantidadeFuncionarios) 
{
    if (QuantidadeFuncionarios == 0) 
    {
        printf("Nenhum funcionário cadastrado.\n");
        return;
    }

    for (int i = 0; i < QuantidadeFuncionarios; i++)
    {
        printf("ID: %d\n", funcionarios[i].id);
        printf("Nome: %s\n", funcionarios[i].nome);
        printf("Cargo: %s\n", funcionarios[i].cargo);
        printf("Salario: R$%.2f\n", funcionarios[i].salario);
        printf("Idade: %d anos\n", funcionarios[i].idade);
        printf("\n");
    }
}

void senha(int ID, struct Funcionario funcionarios[], int QuantidadeFuncionarios) 
{
    int senhaID;

    for (int i = 0; i < QuantidadeFuncionarios; i++)
    {
        if(funcionarios[i].id ==ID)
        {
            printf("Digite sua senha: ");
            scanf("%d", &senhaID);

            while(funcionarios[i].senha != senhaID)
            {
                printf("Senha incorreta, digite novamente: ");
                scanf("%d", &senhaID);
            }

            return;
        }
    }
}

int main() 
{
    struct Livro livros[100];
    struct Funcionario funcionarios[100];
    int QuantidadeLivros = 0;
    int QuantidadeFuncionarios = 0;

    lerLivrosDoArquivo( livros, &QuantidadeLivros); // Chama a função para ler os livros do arquivo
    lerFuncionariosDoArquivo( funcionarios, &QuantidadeFuncionarios); // Chama a função para ler os funcionários do arquivo

    char nome[100], repetir; 

    printf("\tLIVRARIA CEFA'S\n\n");
    printf("Ola, qual eh o seu nome? ");
    scanf(" %[^\n]", nome);
    printf("\nOla, %s\n", nome);

    int op, ID;

    printf("\nAntes de prosseguirmos, precisamos saber se voce eh funcionario ou cliente...");
    printf("\n[1] - Funcionario\n[2] - Cliente\nDigite a opcao: ");
    scanf("%d", &op);

    while(op>2 || op<1)
        {
            printf("\nOpção invalida, tente novamente: ");
            scanf("%d", &op);
        }

    if(op == 1) 
    {
        printf("\nDigite seu ID de funcionario: ");
        scanf("%d", &ID);

        senha(ID, funcionarios, &QuantidadeFuncionarios);

        system("cls");
        
        int setor;
        printf("Qual o seu setor?\n[1] - Vendedor\n[2] - Administracao\n[3] - Estoque\nDigite: ");
        scanf("%d", &setor); //usuário digita qual setor ele pertence

        while(setor>3 || setor<1)
        {
            printf("Opção invalida, tente novamente: ");
            scanf("%d", &setor);
        }

        if(setor == 1) //opção de vendedor
        {
            do
            {
                int opp;
                printf("\n\n\tMENU\n\n[1] - Pesquisar dados de livro\n[2] - Remover livro do sistema\n[3] - Disponibilidade de exemplar\n");
                printf("[4] - Registro de venda\n[5] - Listar livros por autor ou genero");
                printf("\nDigite: "); //usuário escolhe oque ele quer fazer no sistema
                scanf("%d", &opp);

                while(opp>5 || opp<1)
                {
                    printf("\nOpção invalida, tente novamente: ");
                    scanf("%d", &opp);
                }

                if(opp == 1) //opção de pesquisar o livro no sistema
                {
                    char tipoBusca[10], parametro[100];
                    printf("\nEscreva o tipo de busca (titulo, autor, genero, isbn): ");
                    scanf("%s", tipoBusca); //usuário escolhe o tipo de busca
                    printf("Escreva o %s: ", tipoBusca);
                    scanf(" %[^\n]", parametro); //usuário 

                    pesquisarLivro(livros, QuantidadeLivros, parametro, tipoBusca); //chama a função de pesquisa de livro no sistema
                }

                else if(opp == 2) //opção de remover livro do sistema
                {
                    char tipoBusca[10], parametro[100];
                    printf("\nEscreva o tipo de busca (titulo ou isbn): ");
                    scanf("%s", tipoBusca); //usuário escolhe o tipo de busca
                    printf("Escreva o %s: ", tipoBusca);
                    scanf(" %[^\n]", parametro); //usuário digita o titulo ou isbn do livro

                    removerLivro(livros, &QuantidadeLivros, parametro, tipoBusca); //chama a função de pesquisa de livro no sistema
                }

                else if(opp == 3) //opção de quantidade de exemplares de um livro a loja possui
                {
                    char tipoBusca[10], parametro[100];
                    printf("\nEscreva o tipo de busca (titulo ou isbn): ");
                    scanf("%s", tipoBusca); //usuário escolhe o tipo de busca
                    printf("Escreva o %s: ", tipoBusca);
                    scanf(" %[^\n]", parametro); //usuário digita o titulo ou isbn do livro

                    disponibilidade(livros, QuantidadeLivros, parametro, tipoBusca); //chama a função de disponibilidade de livro no sistema
                }

                else if(opp == 4) //opção de registro de venda
                {
                    char tipoBusca[10], parametro[100];
                    printf("\nEscreva o tipo de busca (titulo ou isbn): ");
                    scanf("%s", tipoBusca); //usuário escolhe o tipo de busca
                    printf("Escreva o %s: ", tipoBusca);
                    scanf(" %[^\n]", parametro); //usuário digita o titulo ou isbn do livro

                    venda(livros, QuantidadeLivros, parametro, tipoBusca); //chama a função de resgistrar venda
                }

                else if(opp == 5)
                {
                    char tipoBusca[10], parametro[100];
                    printf("\nEscreva o tipo de busca (genero ou autor): ");
                    scanf("%s", tipoBusca); //usuário escolhe o tipo de busca
                    printf("Escreva o %s: ", tipoBusca);
                    scanf(" %[^\n]", parametro); //usuário digita o titulo ou isbn do livro

                    listarLivros(livros, QuantidadeLivros, parametro, tipoBusca); //chama a função de listar livros por genero ou autor
                }

                printf("\nDeseja algo mais?(s/n) ");
                scanf("%s", &repetir);

                system("cls");

            }while (repetir == 's');
            
        }

        else if(setor == 2) // opção de administração
        {
            do
            {
                int opp;
                printf("\n\n\tMENU\n\n[1] - Calcular Receita\n[2] - Cadastrar novo livro\n[3] - Atualizar informacao de livro\n");
                printf("[4] - Mostrar Todos os Livros no Sistema\n[5] - Mostrar todos os Funcinarios no Sistema");
                printf("\nDigite: "); //usuário escolhe oque ele quer fazer no sistema
                scanf("%d", &opp);

                while(opp>5 || opp<1)
                {
                    printf("\nOpção invalida, tente novamente: ");
                    scanf("%d", &opp);
                }

                if(opp == 1) //opção de calcular receita 
                {
                    float total = receita(livros, QuantidadeLivros); //armazena o retorno da função 'receita' em 'total'
                    printf("A livraria teve uma receita de R$ %.2f no período escolhido\n", total);
                }

                else if(opp == 2) //opção de cadastrar novo livro
                {
                    getchar(); // Limpa o buffer de entrada
                    cadastrarLivro(livros, &QuantidadeLivros); // chama a função para cadastrar um novo livro

                    // Para verificar se o livro foi cadastrado corretamente
                    printf("\nTitulo cadastrado: %s\n", livros[QuantidadeLivros - 1].titulo);
                    printf("Autor cadastrado: %s\n", livros[QuantidadeLivros - 1].autor);
                    printf("ISBN cadastrado: %s\n", livros[QuantidadeLivros - 1].isbn);
                    printf("Genero cadastrado: %s\n", livros[QuantidadeLivros - 1].genero);
                    printf("Preco cadastrado: %.2f\n", livros[QuantidadeLivros - 1].preco);
                    printf("Quantidade cadastrada: %d\n", livros[QuantidadeLivros - 1].quantidade);
                }

                else if(opp == 3) //opção de atualizar certa informação de um livro
                {
                    char tipoBusca[10], parametro[100];
                    printf("\nEscreva o tipo de busca (titulo ou isbn): ");
                    scanf("%s", tipoBusca); //usuário escolhe o tipo de busca
                    printf("Escreva o %s: ", tipoBusca);
                    scanf(" %[^\n]", parametro); //usuário digita o titulo ou isbn do livro

                    atualizarLivro(livros, QuantidadeLivros, parametro, tipoBusca); //chama a função de listar livros por genero ou autor
                }

                else if(opp == 4)
                {
                    mostrarLivros(livros, QuantidadeLivros);
                }

                else if(opp == 5)
                {
                    mostrarFuncionarios(funcionarios, QuantidadeFuncionarios);
                }

                printf("\nDeseja algo mais?(s/n) ");
                scanf("%s", &repetir);

                system("cls");

            }while (repetir == 's');
        }

        else if(setor == 3) //opção de estoque
        {
            do
            {
                int opp;
                printf("\n\n\tMENU\n\n[1] - Pesquisar dados de livro\n[2] - Reabastecer estoque");
                printf("\nDigite: "); //usuário escolhe oque ele quer fazer no sistema
                scanf("%d", &opp);

                while(opp>2 || opp<1)
                {
                    printf("\nOpção invalida, tente novamente: ");
                    scanf("%d", &opp);
                }

                if(opp == 1) //opção de pesquisar o livro no sistema
                {
                    char tipoBusca[10], parametro[100];
                    printf("\nEscreva o tipo de busca (titulo, autor, genero, isbn): ");
                    scanf("%s", tipoBusca); //usuário escolhe o tipo de busca
                    printf("Escreva o %s: ", tipoBusca);
                    scanf(" %[^\n]", parametro); //usuário 

                    pesquisarLivro(livros, QuantidadeLivros, parametro, tipoBusca); //chama a função de pesquisa de livro no sistema
                }

                if(opp == 2) //opção de reabastecer o estoque
                {
                    char tipoBusca[10], parametro[100];
                    printf("\nEscreva o tipo de busca (titulo ou isbn): ");
                    scanf("%s", tipoBusca); //usuário escolhe o tipo de busca
                    printf("Escreva o %s: ", tipoBusca);
                    scanf(" %[^\n]", parametro); //usuário 

                    reabastecer(livros, QuantidadeLivros, parametro, tipoBusca); //chama a função de reabastecer estoque
                }


                printf("\nDeseja algo mais?(s/n) ");
                scanf("%s", &repetir);

                system("cls");

            }while (repetir == 's');

        }
    } 
    
    else if(op == 2) //opção cliente
    {
        do
        {
            int opp;
            printf("\nQuerido cliente, o que deseja fazer?");
            printf("\n\n\tMENU\n\n[1] - Pesquisar dados de livro\n[2] - Listar livros por autor ou genero");
            printf("\nDigite: ");
            scanf("%d", &opp); //usuário escolhe oque ele quer fazer no sistema

            while(opp>2 || opp<1)
            {
                printf("\nOpção invalida, tente novamente: ");
                scanf("%d", &opp);
            }

            if(opp == 1) //opção de pesquisar o livro no sistema
            {
                char tipoBusca[10], parametro[100];
                printf("\nEscreva o tipo de busca (titulo, autor, genero, isbn): ");
                scanf("%s", tipoBusca); //usuário escolhe o tipo de busca
                printf("Escreva o %s: ", tipoBusca);
                scanf(" %[^\n]", parametro); //usuário digita o titulo ou autor ou genero ou isbn do livro

                pesquisarLivro(livros, QuantidadeLivros, parametro, tipoBusca); //chama a função de pesquisa de livro no sistema
            }

            else if(opp == 2)
            {
                char tipoBusca[10], parametro[100];
                printf("\nEscreva o tipo de busca (genero ou autor): ");
                scanf("%s", tipoBusca); //usuário escolhe o tipo de busca
                printf("Escreva o %s: ", tipoBusca);
                 scanf(" %[^\n]", parametro); //usuário digita o titulo ou isbn do livro

                listarLivros(livros, QuantidadeLivros, parametro, tipoBusca); //chama a função de listar livros por genero ou autor
            }

            printf("\nDeseja algo mais?(s/n) ");
            scanf("%s", &repetir);

            system("cls");

        }while (repetir == 's');
    } 

    return 0;
}