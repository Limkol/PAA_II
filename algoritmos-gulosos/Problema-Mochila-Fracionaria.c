#include <stdio.h>

#define MAX 100

typedef struct {
    int id;
    double valor;
    double peso;
} Item;

void ordena(Item itens[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            double r1 = itens[j].valor / itens[j].peso;
            double r2 = itens[j + 1].valor / itens[j + 1].peso;
            if (r1 < r2) {
                Item tmp = itens[j];
                itens[j] = itens[j + 1];
                itens[j + 1] = tmp;
            }
        }
    }
}

double mochila_fracionaria(Item itens[], int n, double W, double x[]) {
    double valor_total = 0.0;

    for (int i = 0; i < n; i++) {
        x[i] = 0.0;
    }

    ordena(itens, n);

    int i = 0;
    while (i < n && W > 0) {
        if (itens[i].peso <= W) {
            x[i] = 1.0;
            W -= itens[i].peso;
            valor_total += itens[i].valor;
            i++;
        } else {
            x[i] = W / itens[i].peso;
            valor_total += x[i] * itens[i].valor;
            W = 0;
        }
    }

    return valor_total;
}

void testa(Item itens[], int n, double W) {
    double x[MAX];

    printf("Capacidade: %.1f\n", W);
    double total = mochila_fracionaria(itens, n, W, x);

    for (int i = 0; i < n; i++) {
        if (x[i] > 0) {
            printf("  Item %d (valor %.0f, peso %.0f, valor/peso %.2f): fracao %.2f\n",
                   itens[i].id, itens[i].valor, itens[i].peso,
                   itens[i].valor / itens[i].peso, x[i]);
        }
    }
    printf("  Valor total: %.2f\n\n", total);
}

int main(void) {
    Item itens1[] = {
        {1, 60, 10},
        {2, 100, 20},
        {3, 120, 30}
    };
    testa(itens1, 3, 50);

    Item itens2[] = {
        {1, 120, 30},
        {2, 60, 10},
        {3, 100, 20},
        {4, 40, 40}
    };
    testa(itens2, 4, 70);

    return 0;
}