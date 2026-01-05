#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "stack.h"
#include "sorting.h"
#include <locale.h>

static void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "ru_Ru.UTF-8");
    srand(time(NULL));

    int continue_or_stop = (argc == 1);

    do {
        char* input_file = NULL;
        for (int i = 1; i < argc; i++)
            if (strcmp(argv[i], "-file") == 0 && i + 1 < argc) {
                input_file = argv[i + 1];
                break;
            }

        if (input_file != NULL) {
            void* previous = load_from_file(input_file);
            if (previous != NULL && !is_empty(previous)) {
                printf("предыдущий введённый ряд '%s'\n", input_file);
                print(previous);

                void* temp = create();
                full_move(previous, temp);

                void* sorted_copy = create();

                while (!is_empty(temp)) {
                    push_back(previous, top(temp));
                    push_back(sorted_copy, top(temp));
                    pop_back(temp);
                }
                free_stack(temp);

                insertion_sort(sorted_copy);

                printf("\n отсортированный ряд (прямым включением) \n");
                print(sorted_copy);

                free_stack(previous);
                free_stack(sorted_copy);
            } else {
                printf("файл '%s' не найден или пуст\n", input_file);
            }
            printf("\n");
        }

        puts("введите ряд чисел:");

        void* stack = create();
        char input[1000];

        if (fgets(input, sizeof(input), stdin) != NULL) {
            int count = 0;

            char* token = strtok(input, " \t\n");
            while (token != NULL) {
                int number = atoi(token);
                if (token[0] != '0' || number != 0 || strcmp(token, "0") == 0) {
                    push_back(stack, number);
                    count++;
                }
                token = strtok(NULL, " \t\n");
            }

            if (count == 0) {
                printf("вы не ввели все числа. используем тестовый набор:\n");
                push_back(stack, 34);
                push_back(stack, 12);
                push_back(stack, 78);
                push_back(stack, 5);
                push_back(stack, 91);
                push_back(stack, 23);
            }
        }

        printf("\nновый ряд чисел:\n");
        print(stack);

        save_to_file(stack, "input.txt");

        void* insertion_stack = create();
        void* merge_stack = create();

        void* temp = create();
        full_move(stack, temp);

        while (!is_empty(temp)) {
            int val = top(temp);
            pop_back(temp);
            push_back(stack, val);
            push_back(insertion_stack, val);
            push_back(merge_stack, val);
        }
        free_stack(temp);

        printf("\nсортировка прямым включением\n");
        insertion_sort(insertion_stack);
        print(insertion_stack);
        save_to_file(insertion_stack, "sorted.txt");

        printf("\n");

        char answer;
        printf("запустить тест производительсти? (y/n): ");
        scanf(" %c", &answer);
        clear_input_buffer();

        if (answer == 'y' || answer == 'Y') {
            benchmark_sorts(3000, 40000, 1000);
        }

        printf("создать файлы с тестовыми данными? (y/n): ");
        scanf(" %c", &answer);
        clear_input_buffer();

        if (answer == 'y' || answer == 'Y') {
            for (int size = 100; size <= 1000; size += 100) {
                char filename[20];
                sprintf(filename, "test_%d.txt", size);

                FILE* file = fopen(filename, "w");
                if (file != NULL) {
                    for (int i = 0; i < size; i++) {
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

        if (continue_or_stop) {
            printf("продолжить? (y/n): ");
            scanf(" %c", &answer);
            clear_input_buffer();

            if (answer != 'y' && answer != 'Y') {
                break;
            }
            printf("\n");
        } else {
            break;
        }

    } while (continue_or_stop);

    return 0;
}