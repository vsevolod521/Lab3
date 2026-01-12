#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"
#include "sorting.h"

const int n_cmds = 8;

const char* cmds[] = {
    "Ввести ряд с клавиатуры",
    "Отсортировать ряд",
    "Сохранить исходный ряд в файл",
    "Сохранить отсортированный ряд в файл",
    "Запустить тест производительности",
    "Запустить тест производительности на основе тестовых данных",
    "Создать файлы с тестовыми данными",
    "Выход"
};


int input_int(int min, int max) {
    int answer;
    printf("\n(%d - %d) > ", min, max);
    while (scanf("%d", &answer) != 1 || answer < min || answer > max) {
        clear_input_buffer();
        printf("(%d - %d) > ", min, max);
    }
    return answer;
}

int show_menu() {
    printf("\n");
    for (int i = 0; i < n_cmds; i++)
        printf("%d. %s\n", i + 1, cmds[i]);
    
    return input_int(1, n_cmds);
}

void save(Stack* stack) {
    if (stack == NULL) {
        printf("Нет ряда чисел для вывода в файл!\n");
        return;
    }

    char filename[20];

    printf("Введите имя файла: ");
    scanf("%s", filename);
    
    if (save_to_file(stack, filename))
        printf("Данные сохранены!\n");
    else
        printf("Попытка записи в файл провалена!\n");
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Parameters create_test_files() {

    Parameters parameters;

    printf("Введите минимальный объём данных: ");
    parameters.start_size = input_int(1, 10000);

    printf("Введите максимальный объём данных: ");
    parameters.max_size = input_int(parameters.start_size, 100000);

    printf("Введите шаг изменения объёма данных: ");
    parameters.step = input_int(1, 10000);

    char filename[20];

    for (int size = parameters.start_size; size <= parameters.max_size; size += parameters.step) {
        sprintf(filename, "test_%d.txt", size);

        FILE* file = fopen(filename, "w");
        if (file != NULL) {
            for (int i = 0; i < size; i++) {
                fprintf(file, "%d ", rand() % 10000);
            }
            fclose(file);
            printf("Создан файл: %s\n", filename);
        }
    }
    printf("\nВсе файлы созданы\n");

    return parameters;
}

Stack* check_parameter_file(int argc, char* argv[]) {
    char* input_file = NULL;
    for (int i = 1; i < argc; i++)
        if (strcmp(argv[i], "-file") == 0 && i + 1 < argc) {
            input_file = argv[i + 1];
            break;
        }

    if (input_file == NULL)
        return NULL;
    
    return load_from_file(input_file);
}

Stack* get_sorted_copy(Stack* stack) {
    if (stack == NULL)
        return NULL;

    Stack* sorted_copy = copy(stack);

    insertion_sort(sorted_copy);

    return sorted_copy;
}

Stack* input_stack() {
    puts("Введите ряд чисел в одну строку через пробел: ");

    getc(stdin);

    Stack* temp = create();

    char input[1000];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        free_stack(temp);
        return NULL;
    }

    char* token = strtok(input, " \t\n");

    while (token != NULL) {
        int number = atoi(token);
        if (number != 0 || strcmp(token, "0") == 0)
            push_back(temp, number);
        
        token = strtok(NULL, " \t\n");
    }

    Stack* stack = create();
    full_move(temp, stack);

    return stack;
}