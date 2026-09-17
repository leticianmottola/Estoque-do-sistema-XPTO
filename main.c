#include <stdio.h>

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
    FILE *estoque; //-> Aponta aonde o arquivo está guardado na memória.

    //!! ARRAY DE STRUCTS !!
    Produto catalogo[MAXIMO_PRODUTOS];
    int totalLidos = 0; // -> Contagem de quantos produtos existem no arquivo.

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
                &catalogo[totalLidos].nome) == 4)

    {
        totalLidos++; // -> Leitura do produto com êxito.

        if (totalLidos >= MAXIMO_PRODUTOS) 
        { 
            printf("AVISO: Limite de produtos atingido!!\n");
            break;
        }
    }
    fclose(estoque);

    // !! EXIBIÇÃO DOS PRODUTOS ARMAZENADOS !!
    printf("=========== ESTOQUE DA XPTO TECNOLOGIA ===========\n");
    printf("Total de itens cadastrados: %d\n\n", totalLidos);

    for (int i = 0; i < totalLidos; i++) 
    {
        printf("Codigo: %d | Produto: %s | Qtd: %d | Preco: R$ %.2f\n", 
               catalogo[i].codigo, 
               catalogo[i].nome, 
               catalogo[i].quantidade, 
               catalogo[i].preco);
    }

    return 0;
    
}