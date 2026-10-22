#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int lis_recursivo_aux(int *num, int i) {
    if (i == 0) {
        return 1;
    }
    int maior = 1;
    for (int j = 0; j < i; j++) {
        if (num[j] < num[i]) {
            maior = max(maior, lis_recursivo_aux(num, j) + 1);
        }
    }
    return maior;
}

int lis_recursivo(int *num, int n) {
    if (n == 0) {
        return 0;
    }
    int maior = 1;
    for (int i = 1; i < n; i++) {
        maior = max(maior, lis_recursivo_aux(num, i));
    }
    return maior;
}

int lis_memo_aux(int *num, int i, int *L) {
    if (L[i] != -1) {
        return L[i];
    }
    if (i == 0) {
        L[i] = 1;
        return L[i];
    }
    int maior = 1;
    for (int j = 0; j < i; j++) {
        if (num[j] < num[i]) {
            maior = max(maior, lis_memo_aux(num, j, L) + 1);
        }
    }
    L[i] = maior;
    return L[i];
}

int lis_memoization(int *num, int n) {
    if (n == 0) {
        return 0;
    }
    int *L = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        L[i] = -1;
    }
    int maior = 1;
    for (int i = 1; i < n; i++) {
        maior = max(maior, lis_memo_aux(num, i, L));
    }
    free(L);
    return maior;
}

int lis_tabulation(int *num, int n) {
    if (n == 0) {
        return 0;
    }
    int *L = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        L[i] = 1;
    }
    int maior = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (num[j] < num[i]) {
                L[i] = max(L[i], L[j] + 1);
            }
        }
        maior = max(maior, L[i]);
    }
    free(L);
    return maior;
}

void imprimir_vetor(int *num, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf(i == 0 ? "%d" : ", %d", num[i]);
    }
    printf("]");
}

int main(void) {
    int s1[] = {8, 7, 11, 4, 5, 1, 9, 10, 6, 3};
    int s2[] = {3, 10, 2, 11};
    int s3[] = {5};
    int s5[] = {1, 2, 3, 4, 5};
    int s6[] = {5, 4, 3, 2, 1};
    int s7[] = {7, 7, 7, 7};
    int s8[] = {10, 22, 9, 33, 21, 50, 41, 60, 80};

    int *sequencias[] = {s1, s2, s3, NULL, s5, s6, s7, s8};
    int tamanhos[] = {10, 4, 1, 0, 5, 5, 4, 9};
    int total = sizeof(tamanhos) / sizeof(tamanhos[0]);

    printf("=== LIS ===\n");
    for (int k = 0; k < total; k++) {
        printf("num = ");
        imprimir_vetor(sequencias[k], tamanhos[k]);
        printf("\n");
        printf("  recursivo   : %d\n", lis_recursivo(sequencias[k], tamanhos[k]));
        printf("  memoization : %d\n", lis_memoization(sequencias[k], tamanhos[k]));
        printf("  tabulation  : %d\n", lis_tabulation(sequencias[k], tamanhos[k]));
    }
    return 0;
}