#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertion_sort(int *A, int inicio, int fim) {
    for (int i = inicio + 1; i <= fim; i++) {
        int chave = A[i];
        int j = i - 1;
        while (j >= inicio && A[j] > chave) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = chave;
    }
}

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

int find_median_of_medians(int *A, int p, int r, int k) {
    if (r - p + 1 < 15) {
        insertion_sort(A, p, r);
        return A[p + k - 1];
    }
    
    int n = r - p + 1;
    int num_groups = (n + 4) / 5;
    
    int *medianas = (int *)malloc(num_groups * sizeof(int));
    
    for (int i = 0; i < num_groups; i++) {
        int inicio = p + i * 5;
        int fim = (inicio + 4 < r) ? inicio + 4 : r;
        
        insertion_sort(A, inicio, fim);
        
        int mediana_idx = inicio + (fim - inicio) / 2;
        medianas[i] = A[mediana_idx];
    }
    
    int med_das_meds = find_median_of_medians(medianas, 0, num_groups - 1, (num_groups + 1) / 2);
    free(medianas);
    
    int pos = -1;
    for (int i = p; i <= r; i++) {
        if (A[i] == med_das_meds) {
            pos = i;
            break;
        }
    }
    
    int temp = A[pos];
    A[pos] = A[r];
    A[r] = temp;
    
    int q = particiona(A, p, r);
    
    int m = q - p + 1;
    
    if (k == m) {
        return A[q];
    } else if (k < m) {
        return find_median_of_medians(A, p, q - 1, k);
    } else {
        return find_median_of_medians(A, q + 1, r, k - m);
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

    int arr1[] = {10, 8, 15, 9, 7, 20, 6, 1, 4, 19, 12, 11, 2, 5, 3, 18, 13, 14, 16, 17, 25, 30, 22, 27, 21};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    
    print_array(arr1, n1, "Array original");
    
    int *arr1_copia = (int *)malloc(n1 * sizeof(int));
    memcpy(arr1_copia, arr1, n1 * sizeof(int));
    
    printf("\nBuscando vários k-ésimos elementos:\n");
    for (int k = 1; k <= n1; k++) {
        int *temp = (int *)malloc(n1 * sizeof(int));
        memcpy(temp, arr1, n1 * sizeof(int));
        int resultado = find_median_of_medians(temp, 0, n1 - 1, k);
        printf("  k = %2d → %dº menor = %d\n", k, k, resultado);
        free(temp);
    }
    
    return 0;
}