#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int corte_haste_recursivo(int p[], int n) {
    if (n == 0) return 0;
    int q = INT_MIN;
    for (int i = 1; i <= n; i++) {
        q = max(q, p[i] + corte_haste_recursivo(p, n - i));
    }
    return q;
}

int corte_haste_topdown_aux(int p[], int n, int r[]) {
    if (r[n] >= 0) return r[n];
    if (n == 0) return 0;
    int q = INT_MIN;
    for (int i = 1; i <= n; i++) {
        q = max(q, p[i] + corte_haste_topdown_aux(p, n - i, r));
    }
    r[n] = q;
    return q;
}

int corte_haste_topdown(int p[], int n) {
    int *r = malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++) {
        r[i] = INT_MIN;
    }
    int resultado = corte_haste_topdown_aux(p, n, r);
    free(r);
    return resultado;
}

int corte_haste_bottomup(int p[], int n) {
    int *r = malloc((n + 1) * sizeof(int));
    r[0] = 0;
    for (int j = 1; j <= n; j++) {
        int q = INT_MIN;
        for (int i = 1; i <= j; i++) {
            q = max(q, p[i] + r[j - i]);
        }
        r[j] = q;
    }
    int resultado = r[n];
    free(r);
    return resultado;
}

int main() {
    int p[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

    int n1 = 4;
    printf("Recursivo  (n=%d): %d\n", n1, corte_haste_recursivo(p, n1));

    int n2 = 7;
    printf("Top-down   (n=%d): %d\n", n2, corte_haste_topdown(p, n2));

    int n3 = 9;
    printf("Bottom-up  (n=%d): %d\n", n3, corte_haste_bottomup(p, n3));

    return 0;
}