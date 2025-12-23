#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"

void insertion_sort(void *p_container);
void merge_sort(void *p_container);

int main()
{
    srand(time(NULL));

    void *stack = create_stack();
    int test_data[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(test_data) / sizeof(test_data[0]);

    printf("Сортировка вставками\n");
    insertion_sort(stack);
    printf("Результат: ");
    print_stack(stack);

    free_stack(stack);
    stack = create_stack();
    for (int i = 0; i < size; i++)
    {
        push_back_stack(stack, test_data[i]);
    }

    printf("Сортировка слиянием\n");
    merge_sort(stack);
    printf("Результат: ");
    print_stack(stack);

    free_stack(stack);
    return 0;
}