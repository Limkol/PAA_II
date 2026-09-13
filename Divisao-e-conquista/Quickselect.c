#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int particiona(int *A, int p, int r) {
    int x = A[r];
    int i = p - 1;
    
    for (int j = p; j < r; j++) {
        if (A[j] <= x) {
            i++;
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    
    int temp = A[i + 1];
    A[i + 1] = A[r];
    A[r] = temp;
    
    return i + 1;
}

int select_quickselect(int *A, int p, int r, int k) {
    if (p == r) {
        return A[p];
    }
    
    int q = particiona(A, p, r);
    
    int m = q - p + 1;
    
    if (k == m) {
        return A[q];
    } else if (k < m) {
        return select_quickselect(A, p, q - 1, k);
    } else {
        return select_quickselect(A, q + 1, r, k - m);
    }
}

void print_array(int *A, int n, const char *name) {
    printf("%s: ", name);
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main() {
    
    int arr1[] = {22, 33, 55, 77, 99, 11, 44, 66, 88, 7, 15, 3};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    
    print_array(arr1, n1, "Array original");
    
    int *arr1_copia = (int *)malloc(n1 * sizeof(int));
    memcpy(arr1_copia, arr1, n1 * sizeof(int));
    
    printf("\nBuscando diferentes k-ésimos elementos:\n");
    for (int k = 1; k <= n1; k++) {
        int *temp = (int *)malloc(n1 * sizeof(int));
        memcpy(temp, arr1, n1 * sizeof(int));
        int resultado = select_quickselect(temp, 0, n1 - 1, k);
        printf("  k = %2d → %dº menor = %d\n", k, k, resultado);
        free(temp);
    }

    return 0;
}