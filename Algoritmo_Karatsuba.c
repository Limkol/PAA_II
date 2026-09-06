#include <stdio.h>

#include <stdio.h>

int numeroDigitos(int n) {
    if (n == 0) {
        return 1;
    }

    int quantidade = 0;

    while (n != 0) {
        quantidade++;
        n /= 10;
    }

    return quantidade;
}

// Algoritmo de Karatsuba
int karatsuba(int x, int y) {

    if (x < 10 || y < 10) {
        return x * y;
    }

    int nx = numeroDigitos(x);
    int ny = numeroDigitos(y);

    int n;

    if (nx > ny) {
        n = nx;
    } else {
        n = ny;
    }

    int m = n / 2;

    int p = 1;

    for (int i = 0; i < m; i++) {
        p *= 10;
    }

    int a = x / p;
    int b = x % p;

    int c = y / p;
    int d = y % p;

    int ac = karatsuba(a, c);
    int bd = karatsuba(b, d);
    int u = karatsuba(a + b, c + d);

    int ad_bc = u - ac - bd;

    int p2 = p * p;

    return ac * p2
         + ad_bc * p
         + bd;
}

int main() {
    int x, y;

    printf("Digite o primeiro número: ");
    scanf("%d", &x);

    printf("Digite o segundo número: ");
    scanf("%d", &y);

    int resultado = karatsuba(x, y);

    printf("O resultado da multiplicação %d * %d = %d\n", x, y, resultado);

    return  0;
}