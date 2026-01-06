#pragma once
#include <stdbool.h>

typedef struct Node
{
    int data;   
    struct Node *prev;
} Node;


typedef struct Stack
{
    int size;
    Node *top;
} Stack;

void *create();
void free_stack(void *);

bool is_empty(void *);
void clear(void *);
int get_size(void *);

void push_back(void *, int ); 
void pop_back(void *);

void *begin(void *);
void *next(void *, void *);

int save_to_file(void *, const char *);
void *load_from_file(const char *);
void print(void *);

void full_move(void*, void*);
void move_single(void*, void*);
int top(void*);

void* copy(void*);