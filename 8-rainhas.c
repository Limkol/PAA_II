#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define N 8

void mostra_matriz(char tabuleiro[][N]) {
    static int silucao = 1;
    printf("Solução %d\n", solucao++);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", tabuleiro[i][j]);
        }

        printf("\n");
    }

    printf("\n");
}

bool esta_salva(char tabuleiro[][N], int linha, int coluna) {
    int i, j;
    for (i = 0; i < coluna; i++)
        if (tabuleiro[linha][i] == 'Q') return false;

    for (i = linha, j = coluna; i >= 0 && j >= 0; i--, j--)
        if (tabuleiro[i][j] == 'Q')
            return false;

    for (i = linha, j = coluna; i < N && j >= 0; i++, j--)
        if (tabuleiro[i][j] == 'Q') return false;

    return true;
}

void posiciona_rainha(char tabuleiro[][N], int coluna) {
    if (coluna == N) mostra_matriz(tabuleiro);
    else {
        for (int i = 0; i < N; i++) {
            if (esta_salva(tabuleiro, i, coluna)) {
                tabuleiro[i][coluna] = 'Q';
                posiciona_rainha(tabuleiro, coluna + 1);
                tabuleiro[i][coluna] = '-';
            }
        }
    }
}

int main(int argc, char *argv[]) {
    char tabuleiro[N][N];
    memset(tabuleiro, '-', sizeof(tabuleiro));
    posiciona_rainha(tabuleiro, 0);
    return 0;
}
