#ifndef statequeue_h
#define statequeue_h
#include "dfastate.h"

typedef struct qnode_ {
    DFAState* state;
    struct qnode_* next;
} qnode;

typedef struct {
    qnode* head;
    qnode* tail;
    int count;
} StateQueue;

qnode* makeQueueNode(DFAState* state);
void initQueue(StateQueue* q);
bool emptyQueue(StateQueue* q);
void enQueue(StateQueue* q, DFAState* state);
DFAState* deQueue(StateQueue* q);
DFAState* peekQueue(StateQueue* q);

#endif