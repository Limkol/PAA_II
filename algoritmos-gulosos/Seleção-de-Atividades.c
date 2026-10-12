#include <stdio.h>

typedef struct {
    int id;
    int inicio;
    int termino;
} Atividade;

void ordena_por_termino(Atividade *a, int n) {

    for (int i = 1; i < n; i++) {
        Atividade chave = a[i];
        int j = i - 1;
        while (j >= 0 && a[j].termino > chave.termino) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = chave;
    }
}

int seleciona_atividades_guloso(int *s, int *t, int n, Atividade *A) {

    Atividade atv[100];
    for (int i = 0; i < n; i++) {
        atv[i].id = i + 1;
        atv[i].inicio = s[i];
        atv[i].termino = t[i];
    }

    ordena_por_termino(atv, n);

    int k = 0;
    A[k++] = atv[0];
    int j = 0;

    for (int i = 1; i < n; i++) {
        if (atv[i].inicio >= atv[j].termino) {
            A[k++] = atv[i];
            j = i;
        }
    }
    return k;
}

void testa(const char *nome, int *s, int *t, int n) {

    Atividade A[100];
    int k = seleciona_atividades_guloso(s, t, n, A);
    printf("%s:\n", nome);
    for (int i = 0; i < k; i++)
        printf("  atividade %d [%d, %d)\n", A[i].id, A[i].inicio, A[i].termino);
    printf("  total: %d\n", k);
}

int main(void) {

    int s1[] = {1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12};
    int t1[] = {4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16};

    testa("Teste 1 (11 atividades)", s1, t1, 11);
    return 0;
}