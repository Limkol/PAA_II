#include <stdio.h>

#define N 4
#define M 3


void mostra_sequencias(int s[], int i, int v[], int n, int m) {
    if (i == m) {
        for (int k = 0; k < m; k++) {
            printf("%d", s[k]);
        }
        printf("\n");
    } else {
        for (int j = 0; j < n; j++) {
            s[i] = v[j];
            mostra_sequencias(s, i + 1, v, n, m);
        }
    }
}

int main() {
    int v[N] = {1, 2, 3, 4};
    int s[M];

    mostra_sequencias(s, 0, v, N, M);

    return 0;
}