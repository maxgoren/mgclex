#include "vector.h"

void initVector(Vector* v) {
    v->n = 0;
    v->maxN = 25;
    v->data = malloc(sizeof(void*)*v->maxN);
}

void addVec(Vector* v, void* data) {
    if (v->n + 1 >= v->maxN) {
        resizeVector(v);
    }
    v->data[v->n++] = data;
}

void resizeVector(Vector* v) {
    void** tmp = v->data;
    v->data = malloc(sizeof(void*)*(2*v->maxN));
    for (int i = 0; i < v->n; i++)
        v->data[i] = tmp[i];
    free(tmp);
    v->maxN = 2*v->maxN;
}

void freeVector(Vector* v) {
    if (v) {
        free(v->data);
        free(v);
    }
}