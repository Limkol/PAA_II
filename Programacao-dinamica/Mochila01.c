#include <stdio.h>
#include <stdlib.h>

#define MAX_ITENS 11

typedef struct {
    int n;
    int W;
    int w[MAX_ITENS];
    int v[MAX_ITENS];
} Teste;

int maximo(int a, int b) {
    return a > b ? a : b;
}

int mochilaRecursiva(int n, int W, int w[], int v[]) {
    if (n <= 0 || W <= 0) {
        return 0;
    }
    if (w[n] > W) {
        return mochilaRecursiva(n - 1, W, w, v);
    }
    return maximo(mochilaRecursiva(n - 1, W, w, v),
                  mochilaRecursiva(n - 1, W - w[n], w, v) + v[n]);
}

int mochilaMemoizationAux(int n, int W, int w[], int v[], int **M) {
    if (n <= 0 || W <= 0) {
        return 0;
    }
    if (M[n][W] != -1) {
        return M[n][W];
    }
    if (w[n] > W) {
        M[n][W] = mochilaMemoizationAux(n - 1, W, w, v, M);
    } else {
        M[n][W] = maximo(mochilaMemoizationAux(n - 1, W, w, v, M),
                         mochilaMemoizationAux(n - 1, W - w[n], w, v, M) + v[n]);
    }
    return M[n][W];
}

int mochilaMemoization(int n, int W, int w[], int v[]) {
    int i, j, resultado;
    int **M = (int **)malloc((n + 1) * sizeof(int *));
    for (i = 0; i <= n; i++) {
        M[i] = (int *)malloc((W + 1) * sizeof(int));
        for (j = 0; j <= W; j++) {
            M[i][j] = -1;
        }
    }
    resultado = mochilaMemoizationAux(n, W, w, v, M);
    for (i = 0; i <= n; i++) {
        free(M[i]);
    }
    free(M);
    return resultado;
}

int mochilaTabulation(int n, int W, int w[], int v[], int m[]) {
    int i, j, resultado;
    int **M = (int **)malloc((n + 1) * sizeof(int *));
    for (i = 0; i <= n; i++) {
        M[i] = (int *)calloc(W + 1, sizeof(int));
    }
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= W; j++) {
            if (w[i] > j) {
                M[i][j] = M[i - 1][j];
            } else {
                M[i][j] = maximo(M[i - 1][j], M[i - 1][j - w[i]] + v[i]);
            }
        }
    }
    resultado = M[n][W];
    j = W;
    for (i = n; i >= 1; i--) {
        if (j == 0 || M[i][j] == M[i - 1][j]) {
            m[i] = 0;
        } else {
            m[i] = 1;
            j = j - w[i];
        }
    }
    for (i = 0; i <= n; i++) {
        free(M[i]);
    }
    free(M);
    return resultado;
}

void imprimirItens(int n, int m[]) {
    int i, primeiro = 1;
    printf("{");
    for (i = 1; i <= n; i++) {
        if (m[i]) {
            if (!primeiro) {
                printf(", ");
            }
            printf("%d", i);
            primeiro = 0;
        }
    }
    printf("}");
}

void executarTeste(int numero, Teste t) {
    int m[MAX_ITENS] = {0};
    int recursiva = mochilaRecursiva(t.n, t.W, t.w, t.v);
    int memoization = mochilaMemoization(t.n, t.W, t.w, t.v);
    int tabulation = mochilaTabulation(t.n, t.W, t.w, t.v, m);

    printf("Teste %d: n = %d, W = %d\n", numero, t.n, t.W);
    printf("  Recursiva:   %d\n", recursiva);
    printf("  Memoization: %d\n", memoization);
    printf("  Tabulation:  %d\n", tabulation);
    printf("  Itens escolhidos (tabulation): ");
    imprimirItens(t.n, m);
    printf("\n\n");
}

int main() {
    Teste teste = {4, 5, {0, 3, 2, 4, 1}, {0, 8, 3, 9, 6}};

    executarTeste(1, teste);

    return 0;
}