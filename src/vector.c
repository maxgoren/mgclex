#include "vector.h"

void initVector(Vector* v) {
    v->n = 0;
    v->maxN = 25;
    v->data = malloc(sizeof(void*)*v->maxN);
}

Vector* allocVector() {
    Vector* v = (Vector*)malloc(sizeof(Vector));
    initVector(v);
    return v;
}

void pushVector(Vector* v, void* data) {
    if (v->n + 1 >= v->maxN) {
        resizeVector(v);
    }
    v->data[v->n++] = data;
}

void resizeVector(Vector* v) {
    void** tmp = v->data;
    int nm = 2*v->maxN;
    v->data = malloc(sizeof(void*)*(2*nm));
    for (int i = 0; i < v->n; i++)
        v->data[i] = tmp[i];
    free(tmp);
    v->maxN = nm;
}

void freeVector(Vector* v) {
    if (v) {
        free(v->data);
        free(v);
    }
}