#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// #include "../zad1/library.h"
#include "library.h"

int main()
{
    // commands
    char *INIT_SIZE = "init size";
    char *COUNT_FILE = "count file";
    char *SHOW_INDEX = "show index";
    char *DELETE_INDEX_INDEX = "delete index index";
    char *DESTROY = "destroy";

    struct table TABLE;


    // nieskonczona petla zczytujemy linia po linii polecenia i je wykonujemy
    // char cmd[4096];
    char *cmd = calloc(4096, sizeof(char));

	for (;;) {
		fgets(cmd, 4096, stdin);


        uint32_t index;
        if (strncmp(cmd, INIT_SIZE, strlen(INIT_SIZE)) == 0){
            index = strlen(INIT_SIZE) - 1;
            printf("init_size");

            if (cmd[index + 1] != ' '){
                printf("Invalid argument %s\n", cmd);
            }

            int size = atoi(&cmd[index + 2]);
            if (size == 0){
                printf("Invalid size %s\n", cmd);
            }

            TABLE = create_table(size);
            printf("INITIALIZED TABLE OF SIZE: %d\n", size);
        }
        else if (strncmp(cmd, COUNT_FILE, strlen(COUNT_FILE)) == 0){
            index = strlen(COUNT_FILE) - 1;
            printf("count_file");

            if (cmd[index + 1] != ' '){
                printf("Invalid argument %s\n", cmd);
            }

            char *filename = &cmd[index + 2];
            for (int i = 0; ; i++) {
                if (filename[i] < 11) {
                    filename[i] = 0;
                    break;
                }
            }
            printf("filename: %s\n", filename);
            count(&TABLE, filename);
            printf("tutaj");
            printf("zawartosc komorki %s\n", TABLE.arr[TABLE.curr_arr_len]);
            printf("curr_arr_len %d\n", TABLE.curr_arr_len);
        }
        else if (strncmp(cmd, SHOW_INDEX, strlen(SHOW_INDEX)) == 0){
            index = strlen(SHOW_INDEX) - 1;
            printf("show_index");

            if (cmd[index + 1] != ' '){
                printf("Invalid argument %s\n", cmd);
            }

            int table_index = atoi(&cmd[index + 2]);
            if (table_index == 0){
                printf("Invalid index %s\n", cmd);
            }

            char* block = get_block(TABLE, table_index);
            printf("%s\n", block);

        }
        else if (strncmp(cmd, DELETE_INDEX_INDEX, strlen(DELETE_INDEX_INDEX)) == 0){
            index = strlen(DELETE_INDEX_INDEX) - 1;
            printf("delete_index");

            if (cmd[index + 1] != ' '){
                printf("Invalid argument %s\n", cmd);
            }

            int table_index = atoi(&cmd[index + 2]);
            if (table_index == 0){
                printf("Invalid index %s\n", cmd);
            }

            remove_block(&TABLE, table_index);

        }
        else if (strncmp(cmd, DESTROY, strlen(DESTROY)) == 0){
            index = strlen(DESTROY) - 1;
            printf("destroy");

            if (cmd[index + 1] != '\0'){
                printf("Invalid argument %s\n", cmd);
            }
            free_table(&TABLE);
        }
        else{
            printf("Invalid argument: %s\n", cmd);
        }

        strcpy(cmd, "");

    }

}