#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "sorting.h"
#include "stack.h"

static void sorted_insert_node(void *sorted_stack_void, Node *node_to_insert)
{
    Stack *sorted_stack = (Stack*)sorted_stack_void;

    if (sorted_stack->top == NULL || node_to_insert->data <= sorted_stack->top->data)
    {
        node_to_insert->prev = sorted_stack->top;
        sorted_stack->top = node_to_insert;
        sorted_stack->size++;
        return;
    }

    Node *current = sorted_stack->top;
    Node *prev_node = NULL;

    while (current != NULL && node_to_insert->data > current->data)
    {
        prev_node = current;
        current = current->prev;
    }

    node_to_insert->prev = current;
    if (prev_node != NULL) {
        prev_node->prev = node_to_insert;
    }
    sorted_stack->size++;
}

void insertion_sort(void *p_container)
{
    Stack *stack = (Stack*)p_container;
    if (stack->size <= 1) return;

    void *sorted_stack_void = create_stack();
    if (!sorted_stack_void) return;
    Stack *sorted_stack = (Stack*)sorted_stack_void;

    while (stack->top != NULL)
    {
        Node *current_node = stack->top;
        stack->top = current_node->prev;
        stack->size--;
        current_node->prev = NULL;

        sorted_insert_node(sorted_stack_void, current_node);
    }

    stack->top = sorted_stack->top;
    stack->size = sorted_stack->size;

    free_stack(sorted_stack_void);
}

static void split_list(Node *head, Node **left, Node **right) {
    if (head == NULL || head->prev == NULL) {
        *left = head;
        *right = NULL;
        return;
    }

    Node *slow = head;
    Node *fast = head->prev;

    while (fast != NULL && fast->prev != NULL) {
        slow = slow->prev;
        fast = fast->prev->prev;
    }

    *left = head;
    *right = slow->prev;
    slow->prev = NULL;
}

static Node* merge_lists(Node *left, Node *right) {
    if (left == NULL) return right;
    if (right == NULL) return left;

    Node dummy;
    Node *tail = &dummy;

    while (left != NULL && right != NULL) {
        if (left->data <= right->data) {
            tail->prev = left;
            left = left->prev;
        } else {
            tail->prev = right;
            right = right->prev;
        }
        tail = tail->prev;
    }

    if (left != NULL) {
        tail->prev = left;
    } else {
        tail->prev = right;
    }

    return dummy.prev;
}

void merge_sort(void *p_container)
{
    Stack *stack = (Stack*)p_container;
    if (stack->size <= 1) return;

    Node *left_head = NULL;
    Node *right_head = NULL;
    split_list(stack->top, &left_head, &right_head);

    void *left_stack_void = create_stack();
    void *right_stack_void = create_stack();
    if (!left_stack_void || !right_stack_void) {
        if (left_stack_void) free_stack(left_stack_void);
        if (right_stack_void) free_stack(right_stack_void);
        return;
    }
    Stack *left_stack = (Stack*)left_stack_void;
    Stack *right_stack = (Stack*)right_stack_void;

    int left_size = 0;
    Node *temp = left_head;
    while(temp) { left_size++; temp = temp->prev; }
    int right_size = 0;
    temp = right_head;
    while(temp) { right_size++; temp = temp->prev; }
    left_stack->size = left_size;
    right_stack->size = right_size;

    left_stack->top = left_head;
    right_stack->top = right_head;

    merge_sort(left_stack_void);
    merge_sort(right_stack_void);

    Node *merged_list = merge_lists(left_stack->top, right_stack->top);

    stack->top = merged_list;
    stack->size = left_size + right_size;

    free_stack(left_stack_void);
    free_stack(right_stack_void);
}

void benchmark_sorts(int max_size, int step)
{
    int start_size = 3000;
    step = 1000;
    max_size = 40000; 

    srand(12345);

    printf("Размер данных\tВремя сортировки вставками (мс)\tВремя сортировки слиянием (мс)\n");

    for (int size = start_size; size <= max_size; size += step)
    {
        int *test_data = (int *)malloc(size * sizeof(int));
        if (!test_data) {
            fprintf(stderr, "Ошибка выделения памяти для размера %d\n", size);
            continue;
        }
        for (int j = 0; j < size; j++)
        {
            test_data[j] = rand() % 10000;
        }

        void *stack_ins = create_stack();
        if (!stack_ins) {
            fprintf(stderr, "Ошибка создания стека для размера %d (вставками)\n", size);
            free(test_data);
            continue;
        }
        for (int j = 0; j < size; j++)
        {
            push_back_stack(stack_ins, test_data[j]);
        }

        clock_t start_ins = clock();
        insertion_sort(stack_ins);
        clock_t end_ins = clock();
        double time_ins = ((double)(end_ins - start_ins) * 1000) / CLOCKS_PER_SEC;
        free_stack(stack_ins);

        void *stack_mer = create_stack();
        if (!stack_mer) {
            fprintf(stderr, "Ошибка создания стека для размера %d (слиянием)\n", size);
            free(test_data);
            continue;
        }
        for (int j = 0; j < size; j++)
        {
            push_back_stack(stack_mer, test_data[j]);
        }

        clock_t start_mer = clock();
        merge_sort(stack_mer);
        clock_t end_mer = clock();
        double time_mer = ((double)(end_mer - start_mer) * 1000) / CLOCKS_PER_SEC;
        free_stack(stack_mer);

        printf("%d\t%f\t%f\n", size, time_ins, time_mer);

        free(test_data);
    }
}