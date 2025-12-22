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

void *create_stack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (stack == NULL)
        return NULL;
    stack->size = 0;
    stack->top = NULL;
    return (void *)stack;
}

void free_stack(void *p_container)
{
    if (p_container == NULL)
        return;
    Stack *stack = (Stack *)p_container;
    free(stack);
}

bool is_empty_stack(void *p_container)
{
    if (p_container == NULL)
        return true;
    Stack *stack = (Stack *)p_container;
    return stack->size == 0;
}

void clear_stack(void *p_container)
{
    if (p_container == NULL)
        return;
    Stack *stack = (Stack *)p_container;
    while (stack->top != NULL)
    { 
        pop_back_stack(p_container);
    }
}

int get_size_stack(void *p_container)
{
    if (p_container == NULL)
        return 0;
    Stack *stack = (Stack *)p_container;
    return stack->size;
}

void push_back_stack(void *p_container, int element)
{
    if (p_container == NULL)
        return;
    Stack *stack = (Stack *)p_container;

    Node *new_node = create_node(element);
    if (new_node == NULL)
        return;

    new_node->prev = stack->top;
    stack->top = new_node;
    stack->size++;
}

void pop_back_stack(void *p_container)
{
    if (p_container == NULL)
        return;
    Stack *stack = (Stack *)p_container;

    Node *old_top = stack->top;
    stack->top = old_top->prev;

    free_node(old_top);
    stack->size--;
}

int top_stack(void *p_container)
{
    if (p_container == NULL)
        return 0;
    Stack *stack = (Stack *)p_container;

    if (is_empty_stack(p_container))
        return 0;
    return stack->top->data;
}

void save_stack_to_file(void *p_container, const char *filename)
{
    if (p_container == NULL || filename == NULL)
        return;

    FILE *file = fopen(filename, "w");
    if (file == NULL)
        return;

    Stack *stack = (Stack *)p_container;
    Node *current = stack->top;

    while (current != NULL)
    {
        fprintf(file, "%d ", current->data);
        current = current->prev;
    }

    fclose(file);
}

void *load_stack_from_file(const char *filename)
{
    if (filename == NULL)
        return NULL;

    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return NULL;

    void *stack = create_stack();
    int value;

    while (fscanf(file, "%d", &value) == 1)
    {
        push_back_stack(stack, value);
    }

    fclose(file);
    return stack;
}

void print_stack(void *p_container)
{
    if (p_container == NULL)
    {
        printf("Стек не существует\n");
        return;
    }

    Stack *stack = (Stack *)p_container;
    if (is_empty_stack(p_container))
    {
        printf("Стек пуст\n");
        return;
    }

    printf("Стек (%d элементов): ", stack->size);

    void *temp = create_stack();
    Node *current = stack->top;

    while (current != NULL)
    {
        push_back_stack(temp, current->data);
        current = current->prev;
    }

    current = ((Stack *)temp)->top;
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->prev;
    }

    free_stack(temp);
    printf("\n");
}

int *stack_to_array(void *p_container, int *size)
{
    if (p_container == NULL)
    {
        if (size != NULL)
            *size = 0;
        return NULL;
    }

    Stack *stack = (Stack *)p_container;
    if (size != NULL)
        *size = stack->size;

    int *array = (int *)malloc(sizeof(int) * stack->size);
    if (array == NULL)
        return NULL;

    void *temp = create_stack();
    Node *current = stack->top;

    while (current != NULL)
    {
        push_back_stack(temp, current->data);
        current = current->prev;
    }

    current = ((Stack *)temp)->top;
    for (int i = 0; i < stack->size && current != NULL; i++)
    {
        array[i] = current->data;
        current = current->prev;
    }

    free_stack(temp);
    return array;
}

void *array_to_stack(int *array, int size)
{
    if (array == NULL || size <= 0)
        return create_stack();

    void *stack = create_stack();
    for (int i = 0; i < size; i++)
    {
        push_back_stack(stack, array[i]);
    }
    return stack;
}