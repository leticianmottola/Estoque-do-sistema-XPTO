#include <stdio.h>
#include <locale.h>

// !! CONSTANTES !!
#define MAXIMO_PRODUTOS 100
#define MAXIMO_NOME 50
#define ARQUIVO_ESTOQUE "storage.txt"

// !! STRUCT [molde do produto]!!
typedef struct {
    int codigo;
    int quantidade;
    float preco;
    char nome[MAXIMO_NOME];
} Produto; // -> Criação do apelido "Produto" para o tipo de dado "struct".


int main()
{
    setlocale(LC_ALL, "Portuguese_Brazil");

    FILE *estoque; //-> Aponta aonde o arquivo está guardado na memória.

    //!! ARRAY DE STRUCTS !!
    Produto catalogo[MAXIMO_PRODUTOS];
    int totalLidos = 0; // -> Contagem de quantos produtos existem no arquivo.
    int opcao; // -> Escolha do usuário no menu interativo.


    estoque = fopen(ARQUIVO_ESTOQUE, "r"); // -> Função chamada para abrir o arquivo "storage.txt". O "r" demonstra apenas a leitura deste arquivo.

    if (estoque == NULL)  // -> Trava de segurança.
    {
        printf("Erro ao abrir o arquivo %s.\n", ARQUIVO_ESTOQUE);
        return 1; // -> Encerra o programa.
    }

    // !! LEITURA DO ARQUIVO DIRETO PARA O STRUCT !!
    while(fscanf(estoque,"%d %d %f %s",
                &catalogo[totalLidos].codigo,
                &catalogo[totalLidos].quantidade,
                &catalogo[totalLidos].preco,
                catalogo[totalLidos].nome) == 4)

    {
        totalLidos++; // -> Leitura do produto com êxito.

        if (totalLidos >= MAXIMO_PRODUTOS) 
        { 
            printf("AVISO: Limite de produtos atingido!!\n");
            break;
        }
    }
    fclose(estoque);

    printf("======================================================================\n");
    printf("                          MEMBROS DO GRUPO                            \n");
    printf("======================================================================\n");
    printf("%-35s %-35s\n", "EVELYN PIO DA SILVA", "FELIPE FIUZA DO NASCIMENTO");
    printf("%-35s %-35s\n", "JEFFERSON DA SILVA SANTOS", "LETICIA NUNES MOTTOLA");
    printf("%-35s %-35s\n", "MARCO AGUILAR MANI", "MARCOS VINICIUS PEREIRA DA SILVA");
    printf("%-35s\n", "VITOR TAMARINDO DE SOUZA");
    printf("======================================================================\n");
    printf("\nBem vindo ao sistema de controle de estoque da XPTO!\n");

    // !! MENU INTERATIVO EM LOOP !!
    do 
    {
        printf("\n===================================\n");
        printf("Selecione uma operação:\n");
        printf("1 - Listar itens\n");
        printf("2 - Adicionar itens\n");
        printf("3 - Remover itens\n");
        printf("0 - Sair\n");
        printf("===================================\n");
        printf("Opção desejada: ");
        
        scanf("%d", &opcao);

        // !! ESTRUTURA DE DECISÃO + EXIBIÇÃO DOS PRODUTOS ARMAZENADOS!!

        switch (opcao) 
        {
            case 1:
                printf("\n--- ESTOQUE ATUAL ---\n");
                printf("Total de itens cadastrados: %d\n\n", totalLidos);
                for (int i = 0; i < totalLidos; i++) 
                {
                    printf("Código: %d | Produto: %s | Qtd: %d | Preco: R$ %.2f\n", 
                           catalogo[i].codigo, catalogo[i].nome, 
                           catalogo[i].quantidade, catalogo[i].preco);
                }
                break;
                
            case 2:
                // Aqui entrará a lógica de adicionar produtos no array no futuro
                printf("\n[Em construcao] Voce escolheu adicionar itens.\n");
                break;
                
            case 3:
                // Aqui entrará a lógica de remover produtos do array no futuro
                printf("\n[Em construcao] Voce escolheu remover itens.\n");
                break;
                
            case 0:
                printf("\nSaindo do sistema.\n");
                break;
                
            default:
                // Se o usuário digitar 4, 5, 99...
                printf("\nOpção inválida! Tente novamente.\n");
                break;
        }

    } while (opcao != 0); // O loop repete até o usuário digitar 0

    return 0;
}

