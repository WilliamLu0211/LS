#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
  DIR* my_dir = opendir(".");

  struct dirent* curr = readdir(my_dir);
  struct stat* file = malloc(sizeof(struct stat));

  size_t total_size = 0;

  while (curr){
    stat(curr->d_name, file);
    total_size += file->st_size;
    curr = readdir(my_dir);
  }
  printf("Total Directory Size: %ld\n", total_size);

  
  curr = readdir(my_dir);
  while (curr){

    if (curr->d_type == DT_DIR)
      printf("directory\t");
    else
      printf("regular file\t");

    printf("name: %s size: %ld\n", curr->d_name, file->st_size);
    curr = readdir(my_dir);
  }

  closedir(my_dir);
}
