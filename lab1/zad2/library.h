#ifndef LIBRARY_H
#define LIBRARY_H
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>


struct table
{
    char **arr;
    uint32_t max_arr_len;
    uint32_t curr_arr_len;
};


struct table create_table(uint32_t max_array_len);

void count(struct table *t, char* filename);

char* get_block(struct table t, uint32_t index);

void remove_block(struct table *t, uint32_t index);

void free_table(struct table *t);

#endif