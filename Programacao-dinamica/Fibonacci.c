#include <stdio.h>
#include <stdlib.h>

long long fib_recursivo(int n) {
    if (n == 0 || n == 1) {
        return n;
    }
    return fib_recursivo(n - 1) + fib_recursivo(n - 2);
}

long long fib_memo_aux(int n, long long *memo) {
    if (memo[n] != -1) {
        return memo[n];
    }
    if (n == 0 || n == 1) {
        memo[n] = n;
    } else {
        memo[n] = fib_memo_aux(n - 1, memo) + fib_memo_aux(n - 2, memo);
    }
    return memo[n];
}

long long fib_memoization(int n) {
    long long *memo = malloc((n + 2) * sizeof(long long));
    for (int i = 0; i < n + 2; i++) {
        memo[i] = -1;
    }
    long long resultado = fib_memo_aux(n, memo);
    free(memo);
    return resultado;
}

long long fib_tabulation(int n) {
    long long *f = malloc((n + 2) * sizeof(long long));
    f[0] = 0;
    f[1] = 1;
    for (int i = 2; i <= n; i++) {
        f[i] = f[i - 1] + f[i - 2];
    }
    long long resultado = f[n];
    free(f);
    return resultado;
}

int main(void) {
    int valores[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30};
    int total = sizeof(valores) / sizeof(valores[0]);

    printf("=== Fibonacci ===\n");
    for (int k = 0; k < total; k++) {
        int n = valores[k];
        printf("n = %d\n", n);
        printf("  recursivo   : %lld\n", fib_recursivo(n));
        printf("  memoization : %lld\n", fib_memoization(n));
        printf("  tabulation  : %lld\n", fib_tabulation(n));
    }
    return 0;
}