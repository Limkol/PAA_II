#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define ALFABETO 256

typedef struct No {
    unsigned char simbolo;
    uint64_t freq;
    uint32_t ordem;
    struct No *esq;
    struct No *dir;
} No;

typedef struct {
    No **v;
    int tam;
} Fila;

static unsigned char codigos[ALFABETO][ALFABETO];
static int tamCodigos[ALFABETO];

static No *novoNo(unsigned char s, uint64_t f, uint32_t ordem, No *esq, No *dir) {
    No *n = malloc(sizeof(No));
    n->simbolo = s;
    n->freq = f;
    n->ordem = ordem;
    n->esq = esq;
    n->dir = dir;
    return n;
}

static int menor(No *a, No *b) {
    if (a->freq != b->freq) return a->freq < b->freq;
    return a->ordem < b->ordem;
}

static void troca(No **a, No **b) {
    No *t = *a;
    *a = *b;
    *b = t;
}

static void sobe(Fila *q, int i) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (!menor(q->v[i], q->v[p])) break;
        troca(&q->v[i], &q->v[p]);
        i = p;
    }
}

static void desce(Fila *q, int i) {
    for (;;) {
        int e = 2 * i + 1, d = 2 * i + 2, m = i;
        if (e < q->tam && menor(q->v[e], q->v[m])) m = e;
        if (d < q->tam && menor(q->v[d], q->v[m])) m = d;
        if (m == i) break;
        troca(&q->v[i], &q->v[m]);
        i = m;
    }
}

static void insere(Fila *q, No *n) {
    q->v[q->tam] = n;
    sobe(q, q->tam);
    q->tam++;
}

static No *extraiMin(Fila *q) {
    No *min = q->v[0];
    q->tam--;
    q->v[0] = q->v[q->tam];
    desce(q, 0);
    return min;
}

static No *constroiArvore(const uint64_t *freq) {
    Fila q;
    uint32_t ordem = 0;
    q.v = malloc(ALFABETO * sizeof(No *));
    q.tam = 0;
    for (int i = 0; i < ALFABETO; i++)
        if (freq[i] > 0) insere(&q, novoNo((unsigned char)i, freq[i], ordem++, NULL, NULL));
    if (q.tam == 0) {
        free(q.v);
        return NULL;
    }
    if (q.tam == 1) {
        No *x = extraiMin(&q);
        free(q.v);
        return novoNo(x->simbolo, x->freq, ordem++, x, NULL);
    }
    while (q.tam > 1) {
        No *x = extraiMin(&q);
        No *y = extraiMin(&q);
        insere(&q, novoNo(0, x->freq + y->freq, ordem++, x, y));
    }
    No *raiz = extraiMin(&q);
    free(q.v);
    return raiz;
}

static void liberaArvore(No *n) {
    if (!n) return;
    liberaArvore(n->esq);
    liberaArvore(n->dir);
    free(n);
}

static void geraCodigos(No *n, unsigned char *buf, int prof) {
    if (!n) return;
    if (!n->esq && !n->dir) {
        memcpy(codigos[n->simbolo], buf, prof);
        tamCodigos[n->simbolo] = prof;
        return;
    }
    buf[prof] = 0;
    geraCodigos(n->esq, buf, prof + 1);
    buf[prof] = 1;
    geraCodigos(n->dir, buf, prof + 1);
}

static void escreve64(FILE *f, uint64_t v) {
    for (int i = 0; i < 8; i++) fputc((int)((v >> (8 * i)) & 0xFF), f);
}

static int le64(FILE *f, uint64_t *v) {
    *v = 0;
    for (int i = 0; i < 8; i++) {
        int c = fgetc(f);
        if (c == EOF) return 0;
        *v |= ((uint64_t)c) << (8 * i);
    }
    return 1;
}

int compactar(const char *entrada, const char *saida) {
    FILE *in = fopen(entrada, "rb");
    if (!in) return 0;
    uint64_t freq[ALFABETO] = {0};
    uint64_t total = 0;
    int c;
    while ((c = fgetc(in)) != EOF) {
        freq[c]++;
        total++;
    }
    rewind(in);

    FILE *out = fopen(saida, "wb");
    if (!out) {
        fclose(in);
        return 0;
    }

    int distintos = 0;
    for (int i = 0; i < ALFABETO; i++)
        if (freq[i] > 0) distintos++;

    fwrite("HUF1", 1, 4, out);
    escreve64(out, total);
    fputc(distintos & 0xFF, out);
    fputc((distintos >> 8) & 0xFF, out);
    for (int i = 0; i < ALFABETO; i++) {
        if (freq[i] > 0) {
            fputc(i, out);
            escreve64(out, freq[i]);
        }
    }

    No *raiz = constroiArvore(freq);
    if (raiz) {
        unsigned char buf[ALFABETO];
        memset(tamCodigos, 0, sizeof(tamCodigos));
        geraCodigos(raiz, buf, 0);

        unsigned char acc = 0;
        int nbits = 0;
        while ((c = fgetc(in)) != EOF) {
            for (int i = 0; i < tamCodigos[c]; i++) {
                acc = (unsigned char)((acc << 1) | codigos[c][i]);
                nbits++;
                if (nbits == 8) {
                    fputc(acc, out);
                    acc = 0;
                    nbits = 0;
                }
            }
        }
        if (nbits > 0) {
            acc = (unsigned char)(acc << (8 - nbits));
            fputc(acc, out);
        }
        liberaArvore(raiz);
    }

    fclose(in);
    fclose(out);
    return 1;
}

int descompactar(const char *entrada, const char *saida) {
    FILE *in = fopen(entrada, "rb");
    if (!in) return 0;

    char magico[4];
    if (fread(magico, 1, 4, in) != 4 || memcmp(magico, "HUF1", 4) != 0) {
        fclose(in);
        return 0;
    }

    uint64_t total;
    if (!le64(in, &total)) {
        fclose(in);
        return 0;
    }
    int lo = fgetc(in);
    int hi = fgetc(in);
    if (lo == EOF || hi == EOF) {
        fclose(in);
        return 0;
    }
    int distintos = lo | (hi << 8);

    uint64_t freq[ALFABETO] = {0};
    for (int i = 0; i < distintos; i++) {
        int s = fgetc(in);
        uint64_t f;
        if (s == EOF || !le64(in, &f)) {
            fclose(in);
            return 0;
        }
        freq[s] = f;
    }

    FILE *out = fopen(saida, "wb");
    if (!out) {
        fclose(in);
        return 0;
    }

    No *raiz = constroiArvore(freq);
    uint64_t escritos = 0;
    No *atual = raiz;
    int c;
    while (escritos < total && (c = fgetc(in)) != EOF) {
        for (int b = 7; b >= 0 && escritos < total; b--) {
            int bit = (c >> b) & 1;
            atual = bit ? atual->dir : atual->esq;
            if (!atual) {
                liberaArvore(raiz);
                fclose(in);
                fclose(out);
                return 0;
            }
            if (!atual->esq && !atual->dir) {
                fputc(atual->simbolo, out);
                escritos++;
                atual = raiz;
            }
        }
    }

    liberaArvore(raiz);
    fclose(in);
    fclose(out);
    return escritos == total;
}

static long tamanhoArquivo(const char *nome) {
    FILE *f = fopen(nome, "rb");
    if (!f) return -1;
    fseek(f, 0, SEEK_END);
    long t = ftell(f);
    fclose(f);
    return t;
}

static int arquivosIguais(const char *a, const char *b) {
    FILE *fa = fopen(a, "rb");
    FILE *fb = fopen(b, "rb");
    if (!fa || !fb) {
        if (fa) fclose(fa);
        if (fb) fclose(fb);
        return 0;
    }
    int iguais = 1;
    for (;;) {
        int ca = fgetc(fa);
        int cb = fgetc(fb);
        if (ca != cb) {
            iguais = 0;
            break;
        }
        if (ca == EOF) break;
    }
    fclose(fa);
    fclose(fb);
    return iguais;
}

static int executaTeste(const char *original) {
    const char *comp = "compactado.huff";
    const char *rest = "restaurado.txt";

    if (tamanhoArquivo(original) < 0) {
        printf("Arquivo '%s' nao encontrado na pasta.\n", original);
        return 1;
    }

    if (!compactar(original, comp)) {
        printf("Falha ao compactar.\n");
        return 1;
    }
    if (!descompactar(comp, rest)) {
        printf("Falha ao descompactar.\n");
        return 1;
    }

    long to = tamanhoArquivo(original);
    long tc = tamanhoArquivo(comp);
    int iguais = arquivosIguais(original, rest);

    printf("Original:     %s (%ld bytes)\n", original, to);
    printf("Compactado:   %s (%ld bytes)", comp, tc);
    if (to > 0) printf(" - %.1f%% do original", 100.0 * (double)tc / (double)to);
    printf("\nRestaurado:   %s (%ld bytes)\n", rest, tamanhoArquivo(rest));
    printf("Resultado:    %s\n", iguais ? "PASSOU (arquivo restaurado identico ao original)" : "FALHOU");
    return iguais ? 0 : 1;
}

int main(int argc, char **argv) {
    if (argc == 4 && strcmp(argv[1], "c") == 0)
        return compactar(argv[2], argv[3]) ? 0 : 1;
    if (argc == 4 && strcmp(argv[1], "d") == 0)
        return descompactar(argv[2], argv[3]) ? 0 : 1;
    if (argc == 1)
        return executaTeste("entrada.txt");
    if (argc == 2)
        return executaTeste(argv[1]);
    fprintf(stderr, "uso: %s [arquivo] | %s c|d entrada saida\n", argv[0], argv[0]);
    return 1;
}