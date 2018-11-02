#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

void print_dir(char* dir){
  DIR* my_dir = opendir(dir);

  struct dirent* curr = readdir(my_dir);
  struct stat* file = malloc(sizeof(struct stat));

  size_t total_size = 0;

  while (curr){
    stat(curr->d_name, file);
    total_size += file->st_size;
    curr = readdir(my_dir);
  }

  printf("Statistics for directory: %s\n", dir);
  printf("Total Directory Size: %ld Bytes\n", total_size);

  my_dir = opendir(dir);
  curr = readdir(my_dir);

  while (curr){

    if (curr->d_type == DT_DIR){
      printf("directory\t%s\n", curr->d_name);
    } else
      printf("regular file\t%s\n", curr->d_name);

    curr = readdir(my_dir);
  }

  closedir(my_dir);
}

int main(){
  print_dir(".");
  return 0;
}
