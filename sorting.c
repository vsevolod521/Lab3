#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "sorting.h"
#include "stack.h"

static void sorted_insert(void *p_container, int element)
{
 
    if (is_empty_stack(p_container) || element >= top_stack(p_container))
    {
        push_back_stack(p_container, element);
        return;
    }


    int temp = top_stack(p_container);
    pop_back_stack(p_container);

    sorted_insert(p_container, element);

    push_back_stack(p_container, temp);
}

void insertion_sort(void *p_container)
{
    if (p_container == NULL)
        return;

    if (get_size_stack(p_container) <= 1)
        return;

    int top = top_stack(p_container);
    pop_back_stack(p_container);

    insertion_sort(p_container);

    sorted_insert(p_container, top);
}

static void *merge_two_stacks(void *left, void *right)
{
    void *result = create_stack();
    void *temp = create_stack(); 

    while (!is_empty_stack(left) && !is_empty_stack(right))
    {
        if (top_stack(left) <= top_stack(right))
        {
            push_back_stack(temp, top_stack(left));
            pop_back_stack(left);
        }
        else
        {
            push_back_stack(temp, top_stack(right));
            pop_back_stack(right);
        }
    }

    while (!is_empty_stack(left))
    {
        push_back_stack(temp, top_stack(left));
        pop_back_stack(left);
    }

    while (!is_empty_stack(right))
    {
        push_back_stack(temp, top_stack(right));
        pop_back_stack(right);
    }

    while (!is_empty_stack(temp))
    {
        push_back_stack(result, top_stack(temp));
        pop_back_stack(temp);
    }

    free_stack(temp);
    return result;
}

static void split_stack(void *p_container, void *left, void *right)
{
    int size = get_size_stack(p_container);
    int half = size / 2;

    void *temp = create_stack();

    while (!is_empty_stack(p_container))
    {
        push_back_stack(temp, top_stack(p_container));
        pop_back_stack(p_container);
    }

    for (int i = 0; i < half; i++)
    {
        push_back_stack(left, top_stack(temp));
        pop_back_stack(temp);
    }

    while (!is_empty_stack(temp))
    {
        push_back_stack(right, top_stack(temp));
        pop_back_stack(temp);
    }

    free_stack(temp);
}

void merge_sort(void *p_container)
{
    if (p_container == NULL)
        return;

    int size = get_size_stack(p_container);
    if (size <= 1)
        return;

    void *left = create_stack();
    void *right = create_stack();

    split_stack(p_container, left, right);

    merge_sort(left);
    merge_sort(right);

    void *merged = merge_two_stacks(left, right);

    while (!is_empty_stack(merged))
    {
        push_back_stack(p_container, top_stack(merged));
        pop_back_stack(merged);
    }

    free_stack(left);
    free_stack(right);
    free_stack(merged);
}

void benchmark_sorts(int max_size, int step)
{
    srand(12345); 

    printf("Размер данных;Insertion Sort (мс);Merge Sort (мс)\n");

    for (int size = step; size <= max_size; size += step)
    {
     
        int *test_data = (int *)malloc(size * sizeof(int));
        for (int i = 0; i < size; i++)
        {
            test_data[i] = rand() % 10000;
        }

        
        void *stack1 = create_stack();
        for (int i = 0; i < size; i++)
        {
            push_back_stack(stack1, test_data[i]);
        }

        clock_t start = clock();
        insertion_sort(stack1);
        clock_t end = clock();
        double time_insertion = ((double)(end - start) * 1000) / CLOCKS_PER_SEC;
        free_stack(stack1);

        void *stack2 = create_stack();
        for (int i = 0; i < size; i++)
        {
            push_back_stack(stack2, test_data[i]);
        }

        start = clock();
        merge_sort(stack2);
        end = clock();
        double time_merge = ((double)(end - start) * 1000) / CLOCKS_PER_SEC;
        free_stack(stack2);

        printf("%d;%.3f;%.3f\n", size, time_insertion, time_merge);

        free(test_data);
    }
}