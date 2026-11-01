#include <stdio.h>
#include <limits.h>

#define MAX 50

long long memo[MAX][MAX];
long long m_bu[MAX][MAX];

long long cadeia_rec(int *p, int i, int j) {
    if (i == j) return 0;
    long long melhor = LLONG_MAX;
    for (int k = i; k < j; k++) {
        long long q = cadeia_rec(p, i, k) + cadeia_rec(p, k + 1, j)
                      + (long long)p[i - 1] * p[k] * p[j];
        if (q < melhor) melhor = q;
    }
    return melhor;
}

long long cadeia_memo_aux(int *p, int i, int j) {
    if (i == j) return 0;
    if (memo[i][j] != -1) return memo[i][j];
    long long melhor = LLONG_MAX;
    for (int k = i; k < j; k++) {
        long long q = cadeia_memo_aux(p, i, k) + cadeia_memo_aux(p, k + 1, j)
                      + (long long)p[i - 1] * p[k] * p[j];
        if (q < melhor) melhor = q;
    }
    memo[i][j] = melhor;
    return melhor;
}

long long cadeia_topdown(int *p, int n) {
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            memo[i][j] = -1;
    return cadeia_memo_aux(p, 1, n);
}

long long cadeia_bottomup(int *p, int n) {
    for (int i = 1; i <= n; i++) m_bu[i][i] = 0;
    for (int l = 2; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            m_bu[i][j] = LLONG_MAX;
            for (int k = i; k < j; k++) {
                long long q = m_bu[i][k] + m_bu[k + 1][j]
                              + (long long)p[i - 1] * p[k] * p[j];
                if (q < m_bu[i][j]) m_bu[i][j] = q;
            }
        }
    }
    return m_bu[1][n];
}

int main(void) {
    int p[] = {200, 2, 30, 20, 5};
    int n = 4;

    printf("Recursivo: %lld\n", cadeia_rec(p, 1, n));
    printf("Top-down:  %lld\n", cadeia_topdown(p, n));
    printf("Bottom-up: %lld\n", cadeia_bottomup(p, n));

    return 0;
}