#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "sorting.h"
#include "stack.h"

void insertion_sort(void* stack) {
    void* temp = create();
    void* sorted = create();

    while (!is_empty(stack)) {
        fflush(stdout);
        int current_element = top(stack);
        pop_back(stack);

        while (!is_empty(sorted) && top(sorted) > current_element)
            move_single(sorted, temp);

        push_back(sorted, current_element);

        while (!is_empty(temp))
            move_single(temp, sorted);
    }

    full_move(sorted, stack);

    free_stack(temp);
    free_stack(sorted);
}

static void* merge_sorted_stacks(void* stack1, void* stack2) {
    void* temp = create();

    while (!is_empty(stack1) && !is_empty(stack2)) {
        if (top(stack1) <= top(stack2))
            move_single(stack1, temp);
        else
            move_single(stack2, temp);
    }

    full_move(stack1, temp);
    full_move(stack2, temp);

    void* result = create();
    full_move(temp, result);
    
    free_stack(temp);

    return result;
}

void merge_sort(void* stack) {
    int size = get_size(stack);
    if (size <= 1) 
        return;

    void* right_stack = create();

    int mid = size / 2;
    for (int i = 0; i < mid; i++)
        move_single(stack, right_stack);

    merge_sort(right_stack);
    merge_sort(stack);

    void* merged = merge_sorted_stacks(right_stack, stack);
    
    void* temp = create();
    full_move(merged, temp);
    full_move(temp, stack);

    free_stack(right_stack);
    free_stack(merged);
    free_stack(temp);
}

void benchmark_sorts(int start_size, int max_size, int step) {
    srand(12345);

    printf("Размер данных\tВремя сортировки вставками (мс)\tВремя сортировки слиянием (мс)\n");

    for (int size = start_size; size <= max_size; size += step) {

        void* stack = create();
        if (stack == NULL) {
            fprintf(stderr, "Ошибка создания стека для размера %d (вставками)\n", size);
            continue;
        }

        for (int i = 0; i < size; i++)
            push_back(stack, rand() % 10000);

        clock_t start_ins = clock();
        insertion_sort(stack);
        clock_t end_ins = clock();

        double time_ins = ((double)(end_ins - start_ins) * 1000) / CLOCKS_PER_SEC;

        clear(stack);

        for (int i = 0; i < size; i++)
            push_back(stack, rand() % 10000);

        clock_t start_mer = clock();
        merge_sort(stack);
        clock_t end_mer = clock();

        double time_mer = ((double)(end_mer - start_mer) * 1000) / CLOCKS_PER_SEC;

        free_stack(stack);

        printf("%d\t%f\t%f\n", size, time_ins, time_mer);
    }
}
