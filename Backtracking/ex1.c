#include <stdio.h>

void binario(char vetor[], int pos, int n){
    if (pos == n) {
        vetor[pos] = '\0';
        printf("%s\n", vetor);
        return;
    }

    vetor[pos] = '0';
    binario(vetor, pos + 1, n);

    vetor[pos] ='1';
    binario(vetor, pos + 1, n);
}

int main() {
    int n;

    printf("Digite o tamanho: ");
    scanf("%d", &n);

    char vetor[n + 1];
    
    binario(vetor, 0, n);
    
    return 0;
}