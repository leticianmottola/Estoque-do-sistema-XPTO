/*
 =============== SISTEMA DE ESTOQUE || XPTO =================

 * | DISCIPLINA: Projeto de Desenvolvimento de Software
 * | LINGUAGEM: C
 * --------------------------------------------------------
 * | MEMBROS DA EQUIPE:
 * - EVELYN PIO DA SILVA
 * - FELIPE FIUZA DO NASCIMENTO
 * - JEFFERSON DA SILVA SANTOS
 * - LETICIA NUNES MOTTOLA
 * - MARCO AGUILAR MANI
 * - MARCOS VINICIUS PEREIRA DA SILVA
 * - VITOR TAMARINDO DE SOUZA 
 * -------------------------------------------------------
 * | SOBRE:
 * Sistema com controle de estoque de produtos cadastrados XPTO.
 * Constitui-se em um menu interativo, o qual o usuário é capaz 
 * de listar os produtos armazenados no estoque, adicionar e 
 * remover produtos; controle realizado por meio de structs.

=============================================================
*/

#include <stdio.h>
#include <locale.h>

//===================== || CONSTANTES || ==========================
#define MAXIMO_PRODUTOS 80
#define MAXIMO_NOME 50
#define ARQUIVO_ESTOQUE "storage.txt"

// =================== || STRUCT [MOLDE] || =======================
typedef struct {
    int codigo;
    int quantidade;
    float valor;
    char nome[MAXIMO_NOME];
} Produto; // -> Criação do apelido "Produto" para o tipo de dado "struct".

// =================== || FUNÇÃO PRINCIPAL || =====================
int main()
{
    setlocale(LC_ALL, "Portuguese_Brazil");

    FILE *estoque;

    //!! ARRAY DE STRUCTS !!
    Produto catalogo[MAXIMO_PRODUTOS];
    int totalLidos = 0; 
    int opcao; 


    estoque = fopen(ARQUIVO_ESTOQUE, "r"); 

    if (estoque == NULL) 
    {
        printf("Erro ao abrir o arquivo %s.\n", ARQUIVO_ESTOQUE);
        return 1;
    }

// =================== || LEITURA DO ARQUIVO || =====================
    while(fscanf(estoque,"%d %d %f %s",
                &catalogo[totalLidos].codigo,
                &catalogo[totalLidos].quantidade,
                &catalogo[totalLidos].valor,
                catalogo[totalLidos].nome) == 4)

    {
        totalLidos++;

        if (totalLidos >= MAXIMO_PRODUTOS) 
        { 
            printf("AVISO: Limite de produtos atingido!!\n");
            break;
        }
    }
    fclose(estoque);

// ================== || SISTEMA XPTO || =========================
    printf("\n================================================\n");
    printf("                XPTO TECNOLOGIAS                \n");
    printf("================================================\n");
    printf("\n  SEJA BEM-VINDO AO SISTEMA DE ESTOQUE XPTO!\n\n");
    printf("    QUAL OPERAÇÃO DEVEMOS REALIZAR HOJE? \n\n"); 

// =================== || MENU INTERATIVO || =====================
    do 
    {
        printf("\n=========================================\n");
        printf("Selecione uma operação:\n");
        printf("[1] - LISTAR ITENS\n");
        printf("[2] - ADICIONAR ITENS\n");
        printf("[3] - REMOVER ITENS\n");
        printf("[0] - SAIR\n");
        printf("===========================================\n");
        printf("OPÇÃO ESCOLHIDA: ");
        
        scanf("%d", &opcao);

// ========== || ESTRUTURA DE DECISÃO + EXIBIÇÃO || ==============

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
                    printf("[ERRO]: O estoque está cheio! Limite de %d atingido.\n", MAXIMO_PRODUTOS);
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
                    printf("[SUCESSO]: Produto adicionado com sucesso!\n");
                }
                break;
                
            case 3:
                printf("\n--- REMOVER ITEM ---\n");
                int codigoRemover, i, j;
                int encontrado = 0; 
                
                printf("Digite o código do produto que deseja remover: ");
                scanf("%d", &codigoRemover);

                for (i = 0; i < totalLidos; i++) 
                {
                    if (catalogo[i].codigo == codigoRemover) 
                    {
                        encontrado = 1;
                        
                        for (j = i; j < totalLidos - 1; j++) 
                        {
                            catalogo[j] = catalogo[j + 1];
                        }
                        
                        totalLidos--; 
                        printf("[SUCESSO]: Produto removido com sucesso!\n");
                        break; 
                    }
                }
                
                if (encontrado == 0) // 
                {
                    printf("[ERRO]: Produto com código %d não encontrado. Tente novamente.\n", codigoRemover);
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
                    printf("[SUCESSO]: Dados salvos com sucesso!\n");
                } 
                else 
                {
                    printf("[ERRO]: Não foi possivel salvar no arquivo.\n");
                }
                
                printf("Saindo do sistema.\n");
                break;
                
            default:
                printf("\n[ERRO]: Opção inválida! Tente novamente.\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}

