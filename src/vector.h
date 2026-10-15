#ifndef vector_h
#define vector_h
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void** data;
    int n;
    int maxN;
} Vector;

void initVector(Vector* vec);
void addVec(Vector* vec, void* data);
void resizeVector(Vector* v);
void freeVector(Vector* h);

#ifdef __cplusplus
}
#endif
#endif