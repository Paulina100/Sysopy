#include "library.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>




struct table create_table(uint32_t max_array_len){
    struct table t;
    t.arr = calloc(max_array_len, sizeof(char*));
    t.max_arr_len = max_array_len;
    t.curr_arr_len = 0;


    return t;
}

long get_file_size(FILE* fp) {
    long size;
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	return size;
}

void count(struct table *t, char *filename){
    printf("inside count file name: %s\n", filename);
    printf("Access result: %d\n", access(filename, F_OK));
    char dir[200];
    getcwd(dir, sizeof(dir));
    printf("Current directory: %s\n", dir);
    printf("Strcm result: %d\n", strcmp(filename, "fajel"));
    if (access(filename, F_OK) != 0) {
        printf("File doesn't exist111gh1 %s\n", filename);
        return;
    }

    system("if ! [ -d 'tmp' ]; then mkdir tmp; fi");

    char outp[1000] = "wc ";

    strcat(outp, filename);
    printf("output: %s\n",outp);
    system(strcat(outp, " >> ./tmp/tmp"));

    FILE* tmp_file_ptr = fopen("tmp/tmp", "r");
    printf("jestem tu\n");
    long tmp_size = get_file_size(tmp_file_ptr);

    t->arr[t->curr_arr_len] = calloc(tmp_size, sizeof(char));

    fread(t->arr[t->curr_arr_len], sizeof(char), tmp_size, tmp_file_ptr);
    fclose(tmp_file_ptr);
    t->curr_arr_len++;
    printf("index %d\n", t->curr_arr_len);
    printf("zawartosc komorki %s\n", t->arr[t->curr_arr_len - 1]);
    printf("curr_arr_len %d\n", t->curr_arr_len);
    system("rm tmp/tmp");
}

char* get_block(struct table t, uint32_t index){
    printf("curr_arr_len %d\n", t.curr_arr_len);
    if (index >= t.curr_arr_len){
        printf("Invalid index %d\n", index);
        return "\0";
    }
    return t.arr[index];
}

void remove_block(struct table *t, uint32_t index){
    if (index >= t->curr_arr_len){
        printf("Invalid index %d\n", index);
        return;
    }

    free(t->arr[index]);
    t->curr_arr_len --;
}

void free_table(struct table *t){
    free(t->arr);
}