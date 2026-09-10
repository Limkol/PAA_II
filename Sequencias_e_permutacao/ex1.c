#include <stdio.h>

#define N 3

void mostra_sequencias(int s[], int i, int v[], int n) {
    if (i == n) {
        for (int k = 0; k < n; k++) {
            printf("%d", s[k]);
        }
        printf("\n");
    } else {
        for (int j = 0; j < n; j++) {
            s[i] = v[j];
            mostra_sequencias(s, i + 1, v, n);
        }
    }
}

int main() {
    int v[N] = {1, 2, 3};
    int s[N];

    mostra_sequencias(s, 0, v, N);

    return 0;
}