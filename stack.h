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

void *create_stack();
void free_stack(void *);

bool is_empty_stack(void *);
void clear_stack(void *);
int get_size_stack(void *);

void push_back_stack(void *, int ); 
void pop_back_stack(void *);
int top_stack(void *); 

void *begin_stack(void *);
void *next_stack(void *, void *);

void save_stack_to_file(void *, const char *);
void *load_stack_from_file(const char *);
void print_stack(void *);