#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "stack.h"

static void sorted_insertion(void *p_container, int element)
{
    if (is_empty_stack(p_container) || element <= top_stack(p_container)) 
    {
        push_back_stack(p_container, element);
        return;
    }

    int temp = top_stack(p_container); 
    pop_back_stack(p_container);

    sorted_insertion(p_container, element); 

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

    sorted_insertion(p_container, top); 
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


    int remaining = get_size_stack(temp); 
    for (int i = 0; i < remaining; i++) 
    {
        push_back_stack(right, top_stack(temp));
        pop_back_stack(temp);
    }

    free_stack(temp);
}
