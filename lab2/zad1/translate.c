#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef SYS
  #include <fcntl.h>
  #include <unistd.h>
  #include <sys/types.h>
  #include <sys/stat.h>
#endif

long get_file_size(FILE* fp) {
    long size;
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	return size;
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
  #endif

  #ifdef LIB
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

  #endif

  return 0;
} 