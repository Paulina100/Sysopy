#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifdef LIB_DYNAMIC
	#include <dlfcn.h>
    struct table
    {
        char **arr;
        uint32_t max_arr_len;
        uint32_t curr_arr_len;
    };
#else
	#include "../zad1/library.h"
#endif

#include <sys/times.h>
#include <unistd.h>
clock_t start_time, end_time;
struct tms start_buffer, end_buffer;

void start_timer(){
	start_time = times(&start_buffer);
}

void stop_timer(){
	end_time = times(&end_buffer);
}

double calc_time(clock_t start, clock_t end) {
    return ((double) (end - start) / sysconf(_SC_CLK_TCK));
}

void print_times(){
	printf("TIMES: real %.3fs user %.3fs sys %.3fs\n",
        calc_time(start_time, end_time),
        calc_time(start_buffer.tms_cutime, end_buffer.tms_cutime),
        calc_time(start_buffer.tms_cstime, end_buffer.tms_cstime));
}

int main()
{
    // commands
    char *INIT_SIZE = "init";
    char *COUNT_FILE = "count";
    char *SHOW_INDEX = "show";
    char *DELETE_INDEX_INDEX = "delete";
    char *DESTROY = "destroy";
    char *EXIT = "exit";

    #ifdef LIB_DYNAMIC
        void *handle = dlopen("../zad1/liblibrary.so", RTLD_LAZY);
        if(!handle){
            printf("Cannot load library liblibrary.so");
            return 0;
        }

        struct table (*create_table)(uint32_t) = (struct table (*)(uint32_t)) dlsym(handle, "create_table");
        void (*count)(struct table*, char*) = (void (*)(struct table*, char*)) dlsym(handle, "count");
        char* (*get_block)(struct table, uint32_t) = (char* (*)(struct table, uint32_t)) dlsym(handle, "get_block");
        void (*remove_block)(struct table*, uint32_t) = (void (*)(struct table*, uint32_t)) dlsym(handle, "remove_block");
        void (*free_table)(struct table*) = (void (*)(struct table*)) dlsym(handle, "free_table");

        if (dlerror()) {
            fprintf(stderr, "Cannot load functions from library.so\n");
            exit(1);
        }

    #endif

    int table_initialized = 0;
    struct table TABLE;

    char *cmd = calloc(4096, sizeof(char));
    // infinite loop, reads command line
	for (;;) {
		fgets(cmd, 4096, stdin);

        uint32_t index;
        if (table_initialized == 0){
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

            start_timer();
            TABLE = create_table(size);
            stop_timer();
            table_initialized = 1;
            printf("INITIALIZED TABLE OF SIZE: %d\n", size);
            print_times();
            }
            else if(strncmp(cmd, EXIT, strlen(EXIT)) == 0){
                return 0;
            }
            else{
                printf("You need to initialized table first.\n");
            }
        }
        else{
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

                printf("Table is already initialized.\n");
            }
            else if (strncmp(cmd, COUNT_FILE, strlen(COUNT_FILE)) == 0){
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
                start_timer();
                count(&TABLE, filename);
                stop_timer();
                print_times();
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

                start_timer();
                char* block = get_block(TABLE, table_index);
                stop_timer();
                printf("INDEX %d:%s\n", table_index, block);
                print_times();

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

                start_timer();
                remove_block(&TABLE, table_index);
                stop_timer();
                printf("DELETED INDEX: %d\n", table_index);
                print_times();

            }
            else if (strncmp(cmd, DESTROY, strlen(DESTROY)) == 0){
                index = strlen(DESTROY);

                if (cmd[index + 1] != '\0'){
                    printf("Invalid argument: %s\n", cmd);
                    continue;
                }
                start_timer();
                free_table(&TABLE);
                stop_timer();
                table_initialized = 0;
                printf("TABLE DESTROYED\n");
                print_times();
            }
            else if(strncmp(cmd, EXIT, strlen(EXIT)) == 0){
                return 0;
            }
            else{
                printf("Invalid argument: %s\n", cmd);
            }
        }

        strcpy(cmd, "");

    }
    #ifdef LIB_DYNAMIC
	    dlclose(handle);
	#endif
}