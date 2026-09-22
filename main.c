#include <stdio.h>
#include <locale.h>

// !! CONSTANTES !!
#define MAXIMO_PRODUTOS 80
#define MAXIMO_NOME 50
#define ARQUIVO_ESTOQUE "storage.txt"

// !! STRUCT [molde do produto] !!
typedef struct {
    int codigo;
    int quantidade;
    float valor;
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
                &catalogo[totalLidos].valor,
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
    printf("\nSeja bem-vindo ao sistema de controle de estoque da XPTO!\n");

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

        // !! ESTRUTURA DE DECISÃO + EXIBIÇÃO DOS PRODUTOS ARMAZENADOS NO SISTEMA !!

        switch (opcao) 
        {
            case 1:
                printf("\n--- ESTOQUE ATUAL ---\n");
                printf("Total de itens cadastrados: %d\n\n", totalLidos);
                for (int i = 0; i < totalLidos; i++) 
                {
                    printf("Código: %d | Produto: %s | Qtd: %d | Preço: R$ %.2f\n", 
                           catalogo[i].codigo, catalogo[i].nome, catalogo[i].quantidade, catalogo[i].valor);
                }
                break;
                
            case 2:
                printf("\n--- ADICIONAR NOVO ITEM ---\n");
                if (totalLidos >= MAXIMO_PRODUTOS) 
                {
                    printf("ERRO: O estoque está cheio! Limite de %d atingido.\n", MAXIMO_PRODUTOS);
                } 
                else 
                {
                    printf("Digite o código do produto: ");
                    scanf("%d", &catalogo[totalLidos].codigo);
                    
                    printf("Digite a quantidade desejada: ");
                    scanf("%d", &catalogo[totalLidos].quantidade);
                    
                    printf("Digite o valor do produto (decimal, ex: 10.50): ");
                    scanf("%f", &catalogo[totalLidos].valor);
                    
                    printf("Digite o nome do produto (sem espaços, apenas com underline): ");
                    scanf("%s", catalogo[totalLidos].nome); 
                    
                    totalLidos++; // -> Contador de produtos cadastrados; adiciona mais um devido a inclusão do novo produto.
                    printf("== > Produto adicionado com sucesso!\n");
                }
                break;
                
            case 3:
                printf("\n--- REMOVER ITEM ---\n");
                int codigoRemover, i, j;
                int encontrado = 0; 
                
                printf("Digite o código/id do produto que deseja remover: ");
                scanf("%d", &codigoRemover);

                for (i = 0; i < totalLidos; i++) 
                {
                    if (catalogo[i].codigo == codigoRemover) 
                    {
                        encontrado = 1; // -> Valor booleano para true.
                        
                        for (j = i; j < totalLidos - 1; j++)  // -> Sistema de remoção do produto.
                        {
                            catalogo[j] = catalogo[j + 1];
                        }
                        
                        totalLidos--; // -> Redução de número de produtos.
                        printf("-> Produto removido com sucesso!\n");
                        break; 
                    }
                }
                
                if (encontrado == 0) // -> Valor booleano para false.
                {
                    printf("-> Produto com código %d não encontrado. Tente novamente.\n", codigoRemover);
                }
                break;
                
            case 0:
                printf("\nSalvando alterações no banco de dados...\n");
                
                FILE *arquivoSaida = fopen(ARQUIVO_ESTOQUE, "w"); // -> O "w" representa que o arquivo está sendo "sobrescrito"; para que as alterações realizadas sejam salvas.
                
                if (arquivoSaida != NULL) 
                {
                    for (int k = 0; k < totalLidos; k++) 
                    {
                        fprintf(arquivoSaida, "%d %d %.2f %s\n", 
                                catalogo[k].codigo, 
                                catalogo[k].quantidade, 
                                catalogo[k].valor, 
                                catalogo[k].nome);
                    }
                    fclose(arquivoSaida);
                    printf("== > Dados salvos com sucesso!\n");
                } 
                else 
                {
                    printf("ERRO: Não foi possivel salvar no arquivo.\n");
                }
                
                printf("Saindo do sistema.\n");
                break;
                
            default:
                printf("\nERRO: Opção inválida! Tente novamente.\n");
                break;
        }

    } while (opcao != 0); // Completa o loop, repetindo-o, até o usuário apertar no 0.

    return 0;
}

