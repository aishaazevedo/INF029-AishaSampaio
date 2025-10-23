/******************************************************************************
3) Faça um programa que o usuário informa um texto de até 250 caracteres, 
e uma letra. O programa deve informar quantas vezes essa letra aparece no texto.
*******************************************************************************/

#include <stdio.h>

int main()
{
    int n = 0, i = 0;       
    char letra, texto[251];
    
    printf("Escreva um pequeno texto de até 250 caracteres:\n");
    fgets(texto, sizeof(texto), stdin);
    
    printf("Digite uma letra:\n");
    scanf(" %c", &letra);  
    
    while (texto[i] != '\0') {
        if (texto[i] == letra || texto[i] == letra + 32 || texto[i] == letra - 32) {
            n++;
        }
        i++;
    }

    if (n > 0) {
        printf("A letra %c aparece %d vezes nesse texto.\n", letra, n);
    } else {
        printf("A letra %c não aparece no texto.\n", letra);
    }
    
    return 0;
}
