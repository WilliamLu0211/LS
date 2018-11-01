#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

void print_dir(char* dir, int tab){
  DIR* my_dir = opendir(dir);

  struct dirent* curr = readdir(my_dir);
  struct stat* file = malloc(sizeof(struct stat));

  size_t total_size = 0;

  while (curr){
    stat(curr->d_name, file);
    total_size += file->st_size;
    curr = readdir(my_dir);
  }

  char str[128] = "";
  for (int i = 0; i < tab; i ++)
    strcat(str, "\t");

  printf("%sStatistics for directory: %s\n", str, dir);
  printf("%sTotal Directory Size: %ld Bytes\n", str, total_size);

  my_dir = opendir(dir);
  curr = readdir(my_dir);

  while (curr){

    if (curr->d_type == DT_DIR){
      printf("%sdirectory\t%s\n", str, curr->d_name);
      if (strcmp(curr->d_name, ".") && strcmp(curr->d_name, ".."))
        print_dir(curr->d_name, tab + 1);
    } else
      printf("%sregular file\t%s\n", str, curr->d_name);

    curr = readdir(my_dir);
  }

  closedir(my_dir);
}

int main(){
  print_dir(".", 0);
  return 0;
}
