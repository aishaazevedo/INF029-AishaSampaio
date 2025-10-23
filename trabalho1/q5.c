//** 5) Faça uma função que permita inverter um número inteiro N.

#include <stdio.h>

int inverterN(int N) {
    int invertido = 0, resto;

    while (N != 0) {
        resto = N % 10;              
        invertido = invertido * 10 + resto; 
        N = N / 10;                  
    }

    return invertido;
}

int main() {
    int N, invertido, resto; 
    printf("Digite um número inteiro: \n");
    scanf("%d", &N);

    invertido = inverterN(N);  

    printf("Esse número invertido é %d \n", invertido);

    return 0;
}
