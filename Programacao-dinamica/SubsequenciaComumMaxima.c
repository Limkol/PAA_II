#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int tamanho;
    char *sequencia;
} ResultadoSCM;

static int **alocar_int(int linhas, int colunas) {
    int **mat = malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++)
        mat[i] = calloc(colunas, sizeof(int));
    return mat;
}

static char **alocar_char(int linhas, int colunas) {
    char **mat = malloc(linhas * sizeof(char *));
    for (int i = 0; i < linhas; i++)
        mat[i] = calloc(colunas, sizeof(char));
    return mat;
}

static void liberar_int(int **mat, int linhas) {
    for (int i = 0; i < linhas; i++)
        free(mat[i]);
    free(mat);
}

static void liberar_char(char **mat, int linhas) {
    for (int i = 0; i < linhas; i++)
        free(mat[i]);
    free(mat);
}

static void recupera_scm(char **b, const char *X, int i, int j, char *saida, int *pos) {
    if (i <= 0 || j <= 0)
        return;
    if (b[i][j] == 'D') {
        recupera_scm(b, X, i - 1, j - 1, saida, pos);
        saida[(*pos)++] = X[i - 1];
    } else if (b[i][j] == 'C') {
        recupera_scm(b, X, i - 1, j, saida, pos);
    } else {
        recupera_scm(b, X, i, j - 1, saida, pos);
    }
}

ResultadoSCM scm(const char *X, const char *Y) {
    int m = (int)strlen(X);
    int n = (int)strlen(Y);

    int **c = alocar_int(m + 1, n + 1);
    char **b = alocar_char(m + 1, n + 1);

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 'D';
            } else if (c[i][j - 1] > c[i - 1][j]) {
                c[i][j] = c[i][j - 1];
                b[i][j] = 'E';
            } else {
                c[i][j] = c[i - 1][j];
                b[i][j] = 'C';
            }
        }
    }

    ResultadoSCM res;
    res.tamanho = c[m][n];
    res.sequencia = calloc(res.tamanho + 1, sizeof(char));

    int pos = 0;
    recupera_scm(b, X, m, n, res.sequencia, &pos);
    res.sequencia[pos] = '\0';

    liberar_int(c, m + 1);
    liberar_char(b, m + 1);
    return res;
}

int scm_tamanho_otimizado(const char *X, const char *Y) {
    int m = (int)strlen(X);
    int n = (int)strlen(Y);
    const char *A = X;
    const char *B = Y;
    if (n > m) {
        A = Y;
        B = X;
        int t = m;
        m = n;
        n = t;
    }

    int *anterior = calloc(n + 1, sizeof(int));
    int *atual = calloc(n + 1, sizeof(int));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (A[i - 1] == B[j - 1])
                atual[j] = anterior[j - 1] + 1;
            else
                atual[j] = atual[j - 1] > anterior[j] ? atual[j - 1] : anterior[j];
        }
        int *tmp = anterior;
        anterior = atual;
        atual = tmp;
    }

    int resultado = anterior[n];
    free(anterior);
    free(atual);
    return resultado;
}

int main(void) {
    const char *X = "ATCTGAT";
    const char *Y = "TGCATTA";

    ResultadoSCM r = scm(X, Y);

    printf("X = \"%s\"\n", X);
    printf("Y = \"%s\"\n", Y);
    printf("Tamanho da SCM: %d\n", r.tamanho);
    printf("SCM: \"%s\"\n", r.sequencia);
    printf("Tamanho (versao otimizada): %d\n", scm_tamanho_otimizado(X, Y));

    free(r.sequencia);
    return 0;
}