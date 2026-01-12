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

Stack* check_parameter_file(int , char** );
Stack* get_sorted_copy(Stack* );
int input_int(int, int);
int show_menu();    
void save(Stack*);

Parameters create_test_files();

Stack* input_stack();
void clear_input_buffer(void);