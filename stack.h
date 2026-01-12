#pragma once
#include <stdbool.h>

typedef struct Node
{
    int data;   
    struct Node *prev;
} Node;


typedef struct Stack
{
    Node *top;
} Stack;

Stack *create();
void free_stack(Stack *);

bool is_empty(Stack *);
void clear(Stack *);
int get_size(Stack *);

void push_back(Stack *, int ); 
void pop_back(Stack *);

int save_to_file(Stack *, const char *);
Stack* load_from_file(const char *);
void print(Stack *);

void full_move(Stack*, Stack*);
void move_single(Stack*, Stack*);
int top(Stack*);

Stack* copy(Stack*);