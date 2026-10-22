#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

int min(int a, int b) {
    return a < b ? a : b;
}

int troco_recursivo(int T, int *M, int n) {
    if (T == 0) {
        return 0;
    }
    if (T < 0) {
        return INF;
    }
    int menor = INF;
    for (int i = 0; i < n; i++) {
        int parcial = troco_recursivo(T - M[i], M, n);
        if (parcial != INF) {
            menor = min(menor, parcial + 1);
        }
    }
    return menor;
}

int troco_memo_aux(int T, int *M, int n, int *memo) {
    if (T == 0) {
        return 0;
    }
    if (T < 0) {
        return INF;
    }
    if (memo[T] != -1) {
        return memo[T];
    }
    int menor = INF;
    for (int i = 0; i < n; i++) {
        int parcial = troco_memo_aux(T - M[i], M, n, memo);
        if (parcial != INF) {
            menor = min(menor, parcial + 1);
        }
    }
    memo[T] = menor;
    return memo[T];
}

int troco_memoization(int T, int *M, int n) {
    if (T < 0) {
        return INF;
    }
    int *memo = malloc((T + 1) * sizeof(int));
    for (int i = 0; i <= T; i++) {
        memo[i] = -1;
    }
    int resultado = troco_memo_aux(T, M, n, memo);
    free(memo);
    return resultado;
}

int troco_tabulation(int T, int *M, int n) {
    if (T < 0) {
        return INF;
    }
    int *troco = malloc((T + 1) * sizeof(int));
    for (int i = 1; i <= T; i++) {
        troco[i] = INF;
    }
    troco[0] = 0;
    for (int i = 1; i <= T; i++) {
        for (int j = 0; j < n; j++) {
            if (i >= M[j] && troco[i - M[j]] != INF) {
                troco[i] = min(troco[i], troco[i - M[j]] + 1);
            }
        }
    }
    int resultado = troco[T];
    free(troco);
    return resultado;
}

void imprimir_moedas(int *M, int n) {
    printf("{");
    for (int i = 0; i < n; i++) {
        printf(i == 0 ? "%d" : ", %d", M[i]);
    }
    printf("}");
}

void imprimir_resultado(const char *nome, int resultado) {
    if (resultado == INF) {
        printf("  %s: impossivel\n", nome);
    } else {
        printf("  %s: %d\n", nome, resultado);
    }
}

int main(void) {
    int m1[] = {1, 4, 6};
    int m2[] = {1, 3, 4};
    int m3[] = {1, 2, 5};
    int m4[] = {2};
    int m5[] = {5, 7};
    int m6[] = {1, 5, 10, 25};

    int *moedas[] = {m1, m1, m1, m2, m3, m4, m5, m6};
    int quantidades[] = {3, 3, 3, 3, 3, 1, 2, 4};
    int trocos[] = {8, 0, 13, 6, 11, 3, 1, 30};
    int total = sizeof(trocos) / sizeof(trocos[0]);

    printf("=== Problema do troco ===\n");
    for (int k = 0; k < total; k++) {
        printf("M = ");
        imprimir_moedas(moedas[k], quantidades[k]);
        printf(", T = %d\n", trocos[k]);
        imprimir_resultado("recursivo  ", troco_recursivo(trocos[k], moedas[k], quantidades[k]));
        imprimir_resultado("memoization", troco_memoization(trocos[k], moedas[k], quantidades[k]));
        imprimir_resultado("tabulation ", troco_tabulation(trocos[k], moedas[k], quantidades[k]));
    }
    return 0;
}