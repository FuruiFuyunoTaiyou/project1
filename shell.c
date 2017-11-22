#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void print_args(char ** arguments){
  int i = 0;
  printf("printing args: [ \n");
  while(arguments[i]){ 
    printf("\t %s \n", arguments[i]);
    i++;
  }
  printf("] \n");
}

char ** parse_args(char * line){ //needs to be modified
  char * s1 = line;
  char ** args = calloc(6, sizeof(char *));;
  int i = 0;
  while(i<5){
    args[i] = strsep(&s1, " ");
    i++;
  }
  args[i] = NULL;
  return args;
}

int shell(){
  
  return 0;
}

int main(){
  shell();
  
  return 0;
}
