#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int n;
    int **mat;
} Matrix;

Matrix* matrix_create(int n) {
    Matrix *m = (Matrix *)malloc(sizeof(Matrix));
    m->n = n;
    m->mat = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        m->mat[i] = (int *)calloc(n, sizeof(int));
    }
    return m;
}

void matrix_free(Matrix *m) {
    for (int i = 0; i < m->n; i++) {
        free(m->mat[i]);
    }
    free(m->mat);
    free(m);
}

Matrix* matrix_add(Matrix *A, Matrix *B) {
    Matrix *C = matrix_create(A->n);
    for (int i = 0; i < A->n; i++) {
        for (int j = 0; j < A->n; j++) {
            C->mat[i][j] = A->mat[i][j] + B->mat[i][j];
        }
    }
    return C;
}

Matrix* matrix_subtract(Matrix *A, Matrix *B) {
    Matrix *C = matrix_create(A->n);
    for (int i = 0; i < A->n; i++) {
        for (int j = 0; j < A->n; j++) {
            C->mat[i][j] = A->mat[i][j] - B->mat[i][j];
        }
    }
    return C;
}

Matrix* matrix_mult_naive(Matrix *A, Matrix *B) {
    Matrix *C = matrix_create(A->n);
    for (int i = 0; i < A->n; i++) {
        for (int j = 0; j < A->n; j++) {
            for (int k = 0; k < A->n; k++) {
                C->mat[i][j] += A->mat[i][k] * B->mat[k][j];
            }
        }
    }
    return C;
}

Matrix* matrix_mult_strassen(Matrix *A, Matrix *B) {
    int n = A->n;
    
    if (n <= 64) {
        return matrix_mult_naive(A, B);
    }
    
    int m = n / 2;
    
    Matrix *a = matrix_create(m);
    Matrix *b = matrix_create(m);
    Matrix *c = matrix_create(m);
    Matrix *d = matrix_create(m);
    Matrix *e = matrix_create(m);
    Matrix *f = matrix_create(m);
    Matrix *g = matrix_create(m);
    Matrix *h = matrix_create(m);
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            a->mat[i][j] = A->mat[i][j];
            b->mat[i][j] = A->mat[i][j + m];
            c->mat[i][j] = A->mat[i + m][j];
            d->mat[i][j] = A->mat[i + m][j + m];
        }
    }
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            e->mat[i][j] = B->mat[i][j];
            f->mat[i][j] = B->mat[i][j + m];
            g->mat[i][j] = B->mat[i + m][j];
            h->mat[i][j] = B->mat[i + m][j + m];
        }
    }
    
    Matrix *temp1, *temp2;
    
    temp1 = matrix_subtract(f, h);
    Matrix *P1 = matrix_mult_strassen(a, temp1);
    matrix_free(temp1);
    
    temp1 = matrix_add(a, b);
    Matrix *P2 = matrix_mult_strassen(temp1, h);
    matrix_free(temp1);
    
    temp1 = matrix_add(c, d);
    Matrix *P3 = matrix_mult_strassen(temp1, e);
    matrix_free(temp1);
    
    temp1 = matrix_subtract(g, e);
    Matrix *P4 = matrix_mult_strassen(d, temp1);
    matrix_free(temp1);
    
    temp1 = matrix_add(a, d);
    temp2 = matrix_add(e, h);
    Matrix *P5 = matrix_mult_strassen(temp1, temp2);
    matrix_free(temp1);
    matrix_free(temp2);
    
    temp1 = matrix_subtract(b, d);
    temp2 = matrix_add(g, h);
    Matrix *P6 = matrix_mult_strassen(temp1, temp2);
    matrix_free(temp1);
    matrix_free(temp2);
    
    temp1 = matrix_subtract(a, c);
    temp2 = matrix_add(e, f);
    Matrix *P7 = matrix_mult_strassen(temp1, temp2);
    matrix_free(temp1);
    matrix_free(temp2);
    
    temp1 = matrix_add(P5, P4);
    temp2 = matrix_subtract(temp1, P2);
    matrix_free(temp1);
    temp1 = matrix_add(temp2, P6);
    matrix_free(temp2);
    Matrix *r = temp1;
    
    Matrix *s = matrix_add(P1, P2);
    
    Matrix *t = matrix_add(P3, P4);
    
    temp1 = matrix_add(P5, P1);
    temp2 = matrix_subtract(temp1, P3);
    matrix_free(temp1);
    temp1 = matrix_subtract(temp2, P7);
    matrix_free(temp2);
    Matrix *u = temp1;
    
    Matrix *C = matrix_create(n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            C->mat[i][j] = r->mat[i][j];
            C->mat[i][j + m] = s->mat[i][j];
            C->mat[i + m][j] = t->mat[i][j];
            C->mat[i + m][j + m] = u->mat[i][j];
        }
    }
    
    matrix_free(a); matrix_free(b); matrix_free(c); matrix_free(d);
    matrix_free(e); matrix_free(f); matrix_free(g); matrix_free(h);
    matrix_free(P1); matrix_free(P2); matrix_free(P3); matrix_free(P4);
    matrix_free(P5); matrix_free(P6); matrix_free(P7);
    matrix_free(r); matrix_free(s); matrix_free(t); matrix_free(u);
    
    return C;
}

void print_matrix(Matrix *m, const char *name) {
    printf("\n%s (%dx%d):\n", name, m->n, m->n);
    for (int i = 0; i < m->n; i++) {
        for (int j = 0; j < m->n; j++) {
            printf("%6d ", m->mat[i][j]);
        }
        printf("\n");
    }
}

int main() {
    
    Matrix *A = matrix_create(4);
    Matrix *B = matrix_create(4);
    
    int val_a = 1;
    int val_b = 2;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            A->mat[i][j] = val_a++;
            B->mat[i][j] = val_b++;
        }
    }
    
    print_matrix(A, "Matriz A");
    print_matrix(B, "Matriz B");
    
    printf("\nProcessando com Strassen...\n");
    Matrix *C_strassen = matrix_mult_strassen(A, B);
    print_matrix(C_strassen, "Resultado (A × B) - Strassen");
    
    return 0;
}