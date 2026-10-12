#include <stdio.h>

int paradas(int *postos, int n, int destino, int C, int *s) {

    int k = 0;
    int ultima_parada = 0;

    for (int i = 0; i < n; i++) {
        int proximo = (i + 1 < n) ? postos[i + 1] : destino;
        if (proximo - ultima_parada > C) {
            if (postos[i] - ultima_parada > C || postos[i] == ultima_parada)
                return -1;
            ultima_parada = postos[i];
            s[k++] = postos[i];
        }
    }

    if (destino - ultima_parada > C)
        return -1;
    return k;
}

void testa(const char *nome, int *postos, int n, int destino, int C) {

    int s[100];
    int k = paradas(postos, n, destino, C, s);
    printf("%s: ", nome);
    if (k < 0) {
        printf("sem solucao\n");
        return;
    }
    printf("paradas nos km {");
    for (int i = 0; i < k; i++)
        printf("%d%s", s[i], i < k - 1 ? ", " : "");
    printf("} -> %d paradas\n", k);
}

int main(void) {

    int p1[] = {10, 25, 40, 55, 70, 90};
    int p4[] = {10, 60};

    testa("Teste 1", p1, 6, 100, 40);
    testa("Teste 4", p4, 2, 80, 30);
    return 0;
}