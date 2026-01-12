#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"

Node *create_node(int element)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL)
        return NULL;
    node->data = element;
    node->prev = NULL;
    return node;
}

void free_node(Node *node)
{
    free(node);
}

Stack* create() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));

    if (stack == NULL)
        return NULL;

    stack->top = NULL;

    return stack;
}

void free_stack(Stack* stack) {
    if (stack == NULL)
        return;

    clear(stack);

    free(stack);
}

bool is_empty(Stack* stack) {
    if (stack == NULL)
        return true;

    return stack->top == 0;
}

void clear(Stack* stack) {
    if (stack == NULL)
        return;
    while (stack->top != NULL)
        pop_back(stack);
}

int get_size(Stack* stack) {
    if (stack == NULL)
        return 0;

    int size = 0;

    Node* node = stack->top;
    while (node != NULL) {
        size++;
        node = node->prev;
    }
    
    return size;
}

void push_back(Stack* stack, int element) {
    if (stack == NULL)
        return;

    Node* new_node = create_node(element);

    if (new_node == NULL)
        return;

    new_node->prev = stack->top;
    stack->top = new_node;
}

void pop_back(Stack* stack) {
    if (stack == NULL)
        return;

    if (is_empty(stack))
        return;

    Node* old_top = stack->top;
    stack->top = old_top->prev;

    free(old_top);
}

int save_to_file(Stack* stack, const char* filename) {
    if (stack == NULL || filename == NULL)
        return 0;

    FILE* file = fopen(filename, "w");

    if (file == NULL)
        return 0;

    Node* current = stack->top;

    while (current != NULL) {
        fprintf(file, "%d ", current->data);
        current = current->prev;
    }

    fclose(file);
    return 1;
}

Stack* load_from_file(const char* filename) {
    if (filename == NULL)
        return NULL;

    FILE* file = fopen(filename, "r");

    if (file == NULL)
        return NULL;

    Stack* stack = create();

    int value;
    while (fscanf(file, "%d", &value) == 1) {
        push_back(stack, value);
    }

    fclose(file);
    return stack;
}


void print(Stack* stack) {
    if (stack == NULL) {
        printf("Стек не существует\n");
        return;
    }

    if (is_empty(stack)) {
        printf("Стек пуст\n");
        return;
    }

    printf("Стек (%d элементов): ", get_size(stack));

    Node* current = stack->top;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->prev;
    }
    printf("\n");
}

void full_move(Stack* source, Stack* destination) {
    if (source == NULL || destination == NULL)
        return;

    while (!is_empty(source)) {
        push_back(destination, top(source));
        pop_back(source);
    }
}

void move_single(Stack* source, Stack* destination) {
    if (source == NULL || destination == NULL)
        return;

    push_back(destination, top(source));
    pop_back(source);
}

int top(Stack* stack) {
    if (stack == NULL || is_empty(stack))
        return 0;

    return stack->top->data;
}

Stack* copy(Stack* source) {
    if (source == NULL)
        return NULL;

    Stack* temp = create();
    full_move(source, temp);
    
    Stack* destination = create();

    while (!is_empty(temp)) {
        push_back(source, top(temp));
        push_back(destination, top(temp));
        pop_back(temp);
    }
    free_stack(temp);

    return destination;
}