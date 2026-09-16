#include <stdio.h>

int main()
{
    FILE *pointer;

    pointer = fopen("storage.txt", "r");

    if (pointer == NULL) 
    {
        printf("Erro ao abrir o arquivo. \n");
    }
    else 
    {
        printf("Abriu o arquivo.");
        fclose(pointer);
    }

}