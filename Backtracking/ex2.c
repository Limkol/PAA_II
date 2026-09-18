#include <stdio.h>

void sequencias(char vetor[], int pos, int golsA, int golsB) {
    if (golsA == 0 && golsB == 0) {
        vetor[pos] ='\0';
        printf("%s\n", vetor);
        return;
    }

    if (golsA > 0) {
        vetor[pos] = 'A';
        sequencias(vetor, pos + 1, golsA - 1, golsB);
    }

    if (golsB > 0) {
        vetor[pos] = 'B';
        sequencias(vetor, pos + 1, golsA, golsB - 1);
    }
}

int main() {
    int m, n;

    printf("Digite o placar de A: ");
    scanf("%d", &m);
    
    printf("Digite o placar de B: ");
    scanf("%d", &n);
    
    char vetor[m + n + 1];

    sequencias(vetor, 0, m, n);
    return 0;
}