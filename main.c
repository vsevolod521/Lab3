#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "stack.h"
#include "sorting.h"
#include "functions.h"
#include <locale.h>

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "ru_Ru.UTF-8");
    srand(time(NULL));

    Stack* stack = check_parameter_file(argc, argv);
    Stack* sorted = NULL;
    
    if (stack != NULL) {
        sorted = get_sorted_copy(stack);

        printf("Ряд чисел из файла: ");
        print(stack);

        printf("После сортировки: ");
        print(sorted);
    }

    Parameters parameters;
    parameters.start_size = -1;
    
    int answer = show_menu();
    
    while (answer != n_cmds) {
        if (answer == 1) {
            if (stack != NULL) {
                free_stack(stack);
            }
            stack = input_stack();
            print(stack);
            printf("Введён новый ряд чисел!\n");

        } else if (answer == 2) {
            if (sorted != NULL) {
                free_stack(sorted);
                sorted = NULL;
            }
            
            if (stack == NULL) {
                printf("Нет исходного ряда для сортировки!\n");
            } else {
                sorted = get_sorted_copy(stack);
                printf("Ряд чисел после сортировки: ");
                print(sorted);
            }

        } else if (answer == 3) {
            save(stack);

        } else if (answer == 4) {
            save(sorted);

        } else if (answer == 5) {
            Parameters params;
            params.start_size = 3000;
            params.max_size = 10000;
            params.step = 1000;
            benchmark_sorts(params, false);

        } else if (answer == 6) {
            if (parameters.start_size == -1)
                printf("Нет тестовых файлов.\n");
            else 
                benchmark_sorts(parameters, true);

        } else if (answer == 7) {
            parameters = create_test_files();
        }
        answer = show_menu();
    }

    if (stack != NULL)
        free_stack(stack);
    
    if (sorted != NULL)
        free_stack(sorted);
   
    return 0;
}