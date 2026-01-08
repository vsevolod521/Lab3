#pragma once
#include "stack.h"

struct Parameters {
    int start_size;
    int max_size;
    int step;
};

typedef struct Parameters Parameters;

extern const int n_cmds;
extern const char* cmds[];

void* check_parameter_file(int , char** );
void* get_sorted_copy(void* );
int input_int(int, int);
int show_menu();    
void save(void*);

Parameters create_test_files();

void* input_stack();
void clear_input_buffer(void);