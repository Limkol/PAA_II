#include <stdio.h>

#define N 3

void mostra_permutacoes(int s[], int i, int v[], int n, int usado[]) {
    if (i == n) {
        for (int k = 0; k < n; k++) {
            printf("%d", s[k]);
        }
        printf("\n");
    } else {
        for (int j = 0; j < n; j++) {
            if (!usado[j]) {
                s[i] = v[j];
                usado[j] = 1;
                mostra_permutacoes(s, i + 1, v, n, usado);
                usado[j] = 0;
            }
        }
    }
}

int main() {
    int v[N] = {1, 2, 3};
    int s[N];
    int usado[N] = {0};
    
    mostra_permutacoes(s, 0, v, N, usado);

    return 0;
}