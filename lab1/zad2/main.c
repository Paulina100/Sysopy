#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// #include "../zad1/library.h"
#include "library.h"

int main()
{
    // commands
    char *INIT_SIZE = "init";
    char *COUNT_FILE = "count";
    char *SHOW_INDEX = "show";
    char *DELETE_INDEX_INDEX = "delete";
    char *DESTROY = "destroy";

    struct table TABLE;

    char *cmd = calloc(4096, sizeof(char));
    // infinite loop, reads command line
	for (;;) {
		fgets(cmd, 4096, stdin);

        uint32_t index;
        if (strncmp(cmd, INIT_SIZE, strlen(INIT_SIZE)) == 0){
            index = strlen(INIT_SIZE) - 1;
            if (cmd[index + 1] != ' '){
                printf("Invalid argument: %s\n", cmd); 
                continue;
            }

            int size = atoi(&cmd[index + 2]);
            if (size <= 0){
                printf("Invalid size: %s\n", cmd);
                continue;
            }

            TABLE = create_table(size);
            printf("INITIALIZED TABLE OF SIZE: %d\n", size);
        }
        else if (strncmp(cmd, COUNT_FILE, strlen(COUNT_FILE)) == 0){
            printf("size of table %ld\n", sizeof(TABLE));
            if (sizeof(TABLE) == 0){
                printf("Table is not initialized\n");
                continue;
            }

            index = strlen(COUNT_FILE) - 1;

            if (cmd[index + 1] != ' '){
                printf("Invalid argument: %s\n", cmd);
                continue;
            }

            char *filename = &cmd[index + 2];
            for (int i = 0; ; i++) {
                if (filename[i] < 11) {
                    filename[i] = 0;
                    break;
                }
            }
            count(&TABLE, filename);
        }
        else if (strncmp(cmd, SHOW_INDEX, strlen(SHOW_INDEX)) == 0){
            index = strlen(SHOW_INDEX) - 1;
            if (cmd[index + 1] != ' '){
                printf("Invalid argument: %s\n", cmd);
                continue;
            }

            int table_index = atoi(&cmd[index + 2]);
            if (table_index <= 0 && cmd[index + 2] != 48){
                printf("Invalid index: %s\n", cmd);
                continue;
            }

            char* block = get_block(TABLE, table_index);
            printf("INDEX %d:%s\n", table_index, block);

        }
        else if (strncmp(cmd, DELETE_INDEX_INDEX, strlen(DELETE_INDEX_INDEX)) == 0){
            index = strlen(DELETE_INDEX_INDEX) - 1;

            if (cmd[index + 1] != ' '){
                printf("Invalid argument: %s\n", cmd);
                continue;
            }

            int table_index = atoi(&cmd[index + 2]);
            if (table_index <= 0 && cmd[index + 2] != 48){
                printf("Invalid index: %s\n", cmd);
                continue;
            }

            remove_block(&TABLE, table_index);
            printf("DELETED INDEX: %d\n", table_index);

        }
        else if (strncmp(cmd, DESTROY, strlen(DESTROY)) == 0){
            index = strlen(DESTROY);

            if (cmd[index + 1] != '\0'){
                printf("Invalid argument: %s\n", cmd);
                continue;
            }
            free_table(&TABLE);
            printf("TABLE DESTROYED\n");
        }
        else{
            printf("Invalid argument: %s\n", cmd);
        }

        strcpy(cmd, "");

    }

}