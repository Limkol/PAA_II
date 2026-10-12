#include <stdio.h>

int salto_sapo(int *p, int n, int delta, int *u) {

    int k = 0;
    u[k++] = p[0];
    if (n == 1)
        return k;

    int ultima_pos = p[0];
    for (int i = 1; i < n; i++) {
        if (p[i] - ultima_pos > delta) {
            if (p[i - 1] == ultima_pos)
                return -1;
            ultima_pos = p[i - 1];
            u[k++] = p[i - 1];
        }
    }
    u[k++] = p[n - 1];
    return k;
}

void testa(const char *nome, int *p, int n, int delta) {

    int u[100];
    int k = salto_sapo(p, n, delta, u);
    printf("%s: ", nome);
    if (k < 0) {
        printf("sem solucao\n");
        return;
    }
    printf("{");
    for (int i = 0; i < k; i++)
        printf("%d%s", u[i], i < k - 1 ? ", " : "");
    printf("} -> %d saltos\n", k - 1);
}

int main(void) {

    int p1[] = {1, 2, 3, 4};
    int p2[] = {1, 2, 3, 5, 6, 7};

    testa("Exemplo 1", p1, 4, 1);
    testa("Exemplo 2", p2, 6, 2);
    return 0;
}