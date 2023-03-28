#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef SYS
  #include <fcntl.h>
  #include <unistd.h>
  #include <sys/types.h>
  #include <sys/stat.h>
#endif

#include <sys/times.h>
#include <unistd.h>
clock_t start_time, end_time;
struct tms start_buffer, end_buffer;
double mean_time;
double mean_time_utime;
double mean_time_stime;
int TEST_NUMBER = 100;

void start_timer(){
	start_time = times(&start_buffer);
}

void stop_timer(){
	end_time = times(&end_buffer);
}

double calc_time(clock_t start, clock_t end) {
    return ((double) (end - start) / sysconf(_SC_CLK_TCK));
}

void add_mean_times(){
  mean_time += calc_time(start_time, end_time);
  mean_time_utime += calc_time(start_buffer.tms_utime, end_buffer.tms_utime);
  mean_time_stime += calc_time(start_buffer.tms_stime, end_buffer.tms_stime);
}

void print_times(){
	printf("TIMES: real %.3fs user %.3fs sys %.3fs\n",
        mean_time/TEST_NUMBER, mean_time_utime/TEST_NUMBER, mean_time_stime/TEST_NUMBER);
}

int main (int argc, char* argv[])
{
  if (argc <= 4){
    printf("Not enough arguments!\n");
    return 0;
  }

  if (strlen(argv[1]) != 1){
    printf("Argument %s should be a single sign!\n", argv[1]);
    return 0;
  }
  if (strlen(argv[2]) != 1){
    printf("Argument %s should be a single sign!\n", argv[2]);
    return 0;
  }
  char *old_ascii = argv[1];
  char *new_ascii = argv[2];
  char *in_file_name = argv[3];
  char *out_file_name = argv[4];

  #ifdef SYS
    for(int i = 0; i < TEST_NUMBER; i++){
      start_timer();
      int in_file = open(in_file_name, O_RDONLY);
      int out_file = open(out_file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);

      char* buff = calloc(1, sizeof(char));
        while (read(in_file, buff, sizeof(char)) == 1){
            if(*buff != old_ascii[0]){
              write(out_file, buff, sizeof(char));
            }
            else{
              write(out_file, new_ascii, sizeof(char));
            }
        }
        
      free(buff);
      close(in_file);
      close(out_file);
      stop_timer();
      add_mean_times();
    }
    print_times();
  #endif

  #ifdef LIB
    for(int i = 0; i < TEST_NUMBER; i++){
      start_timer();
      FILE* in_file = fopen (in_file_name, "r");
      FILE* out_file = fopen(out_file_name, "w+");

      char* buff = calloc(1, sizeof(char));
        while (fread(buff, sizeof(char), 1, in_file) == 1){
            if(*buff != old_ascii[0]){
              fwrite(buff, sizeof(char), 1, out_file);
            }
            else{
              fwrite(new_ascii, sizeof(char), 1, out_file);
            }
        }
        
      free(buff);
      fclose(in_file);
      fclose(out_file);
      stop_timer();
      add_mean_times();
    }
    print_times();
  #endif

  return 0;
} 