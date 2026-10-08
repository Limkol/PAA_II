#include <stdio.h>

#define MAX_SOLUCAO 100

int troco(int moedas[], int n, int valor, int S[], int *tam) {
    int soma = 0;
    int i = 0;
    *tam = 0;

    while (i < n && soma < valor) {
        int m = moedas[i];
        if (soma + m <= valor) {
            soma += m;
            S[(*tam)++] = m;
        } else {
            i++;
        }
    }

    return soma == valor;
}

void testa(int moedas[], int n, int valor) {
    int S[MAX_SOLUCAO];
    int tam;

    printf("Moedas: {");
    for (int i = n - 1; i >= 0; i--) {
        printf("%d%s", moedas[i], i > 0 ? ", " : "");
    }
    printf("} | Troco: %d\n", valor);

    if (troco(moedas, n, valor, S, &tam)) {
        printf("  Solucao (%d moedas): ", tam);
        for (int i = 0; i < tam; i++) {
            printf("%d ", S[i]);
        }
        printf("\n");
    } else {
        printf("  Nao encontrei a solucao\n");
    }
    printf("\n");
}

int main(void) {
    int moedas1[] = {5, 2, 1};
    testa(moedas1, 3, 12);

    int moedas2[] = {6, 4, 1};
    testa(moedas2, 3, 8);

    int moedas3[] = {5, 3};
    testa(moedas3, 2, 4);

    return 0;
}