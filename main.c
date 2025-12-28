#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "stack.h"
#include "sorting.h"
#include <locale.h>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "ru_Ru.UTF-8");
    srand(time(NULL));

    char *input_file = NULL;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-file") == 0 && i + 1 < argc)
        {
            input_file = argv[i + 1];
            break;
        }
    }

    if (input_file != NULL)
    {
        void *previous_stack = load_stack_from_file(input_file);
        if (previous_stack != NULL && !is_empty_stack(previous_stack))
        {
            printf("предыдущий введённый ряд '%s'\n", input_file);
            print_stack(previous_stack);

            void *sorted_copy = create_stack();
            void *temp = create_stack();

            while (!is_empty_stack(previous_stack))
            {
                int val = top_stack(previous_stack);
                pop_back_stack(previous_stack);
                push_back_stack(temp, val);
            }

            while (!is_empty_stack(temp))
            {
                int val = top_stack(temp);
                pop_back_stack(temp);
                push_back_stack(previous_stack, val);
                push_back_stack(sorted_copy, val);
            }
            free_stack(temp);

            insertion_sort(sorted_copy);

            printf("\n отсортированный ряд (прямым включением) \n");
            print_stack(sorted_copy);

            free_stack(previous_stack);
            free_stack(sorted_copy);
        }
        else
        {
            printf("файл '%s' не найден или пуст\n", input_file);
        }
        printf("\n");
    }

    puts("введите ряд чисел:");

    void *stack = create_stack();
    char input[1000];

    if (fgets(input, sizeof(input), stdin) != NULL)
    {
        char *token = strtok(input, " \t\n");
        int count = 0;

        while (token != NULL)
        {
            int number = atoi(token);
            if (token[0] != '0' || number != 0 || strcmp(token, "0") == 0)
            {
                push_back_stack(stack, number);
                count++;
            }
            token = strtok(NULL, " \t\n");
        }

        if (count == 0)
        {
            printf("вы не ввели все числа. используем тестовый набор:\n");
            push_back_stack(stack, 34);
            push_back_stack(stack, 12);
            push_back_stack(stack, 78);
            push_back_stack(stack, 5);
            push_back_stack(stack, 91);
            push_back_stack(stack, 23);
        }
    }

    printf("\nновый ряд чисел:\n");
    print_stack(stack);

    save_stack_to_file(stack, "input.txt");

    void *insertion_stack = create_stack();
    void *merge_stack = create_stack();

    void *temp = create_stack();
    while (!is_empty_stack(stack))
    {
        int val = top_stack(stack);
        pop_back_stack(stack);
        push_back_stack(temp, val);
    }

    while (!is_empty_stack(temp))
    {
        int val = top_stack(temp);
        pop_back_stack(temp);
        push_back_stack(stack, val);
        push_back_stack(insertion_stack, val);
        push_back_stack(merge_stack, val);
    }
    free_stack(temp);

    printf("\nсортировка прямым включением\n");
    insertion_sort(insertion_stack);
    print_stack(insertion_stack);
    save_stack_to_file(insertion_stack, "sorted.txt");

    printf("\n");

    char answer;
    printf("запустить тест производительсти? (y/n): ");
    scanf(" %c", &answer);

    if (answer == 'y' || answer == 'Y')
    {
        benchmark_sorts(10000, 1000);
    }

    printf("создать файлы с тестовыми данными? (y/n): ");
    scanf(" %c", &answer);

    if (answer == 'y' || answer == 'Y')
    {
        for (int size = 100; size <= 1000; size += 100)
        {
            char filename[20];
            sprintf(filename, "test_%d.txt", size);

            FILE *file = fopen(filename, "w");
            if (file != NULL)
            {
                for (int i = 0; i < size; i++)
                {
                    fprintf(file, "%d ", rand() % 10000);
                }
                fprintf(file, "\n");
                fclose(file);
                printf("Создан файл: %s\n", filename);
            }
        }
        printf("\nвсе файлы созданы\n");
    }

    free_stack(stack);
    free_stack(insertion_stack);
    free_stack(merge_stack);
    return 0;
}