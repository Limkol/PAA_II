#include <stdio.h>

#define N 4

int tabuleiro[N][N] = {
    {0, 2, 0, 4},
    {3, 0, 1, 0},
    {0, 1, 0, 3},
    {4, 0, 2, 0}
};

int promissor(int linha, int coluna, int valor) {
    for (int k = 0; k < N; k++) {
        if (tabuleiro[linha][k] == valor) return 0;
        if (tabuleiro[k][coluna] == valor) return 0;
    }
    return 1;
}

int proxima_vazia(int *linha, int *coluna) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (tabuleiro[i][j] == 0) {
                *linha = i;
                *coluna = j;
                return 1;
            }
        }
    }
    return 0;
}

void imprime_tabuleiro() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int resolve_sudoku() {
    int linha, coluna;

    if (!proxima_vazia(&linha, &coluna)) {
        return 1;
    }

    for (int valor = 1; valor <= N; valor++) {
        if (promissor(linha, coluna, valor)) {
            tabuleiro[linha][coluna] = valor;
            if (resolve_sudoku()) {
                return 1;
            }
            tabuleiro[linha][coluna] = 0;
        }
    }

    return 0;
}

int main() {
    if (resolve_sudoku()) {
        printf("Solucao encontrada:\n");
        imprime_tabuleiro();
    } else {
        printf("Nao existe solucao.\n");
    }

    return 0;
}