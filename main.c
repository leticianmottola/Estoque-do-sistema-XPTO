#include <stdio.h>

int main()
{
    FILE *estoque; // Aponta aonde o arquivo está guardado na memória.

    estoque = fopen("storage.txt", "r"); /* Função chamada para abrir o arquivo "storage.txt", o arquivo do estoque.
    O "r" demonstra apenas a leitura deste arquivo. */
    if (estoque == NULL)  // Trava de segurança.
    {
        printf("Erro ao abrir o arquivo. \n");
    }
    else 
    {
        printf("Abriu o arquivo.");
        while(feof(estoque) == 0) 
        {
            fscanf(arquivo, "%d%d", &a, &b);
        }
        fclose(estoque);
    }

}