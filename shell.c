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

char ** parse_cmds(char * input){
  char * newline = strchr(input, '\n'); //removing works, but warning.
  if(newline){
    *newline = NULL;
  }

  char ** cmds = calloc(6, sizeof(char *));
  int i = 0;
  while(i < 5){
    cmds[i] = strsep(&input, ";"); //didn't work as expected with delim " ; ", but at least spaces are not too detrimental for now.
    i++;
  }
  cmds[i] = NULL;
  return cmds;
}

char ** parse_args(char * line){ //needs to be modified for more args?
  //get rid of the possible \n
  char * s1 = line;

  char * newline = strchr(s1, '\n'); 
  if(newline){
    *newline = NULL;
  }

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
  char input[1000];
  char ** cmds;
  while(1){
    printf("type command: ");
    fgets(input, sizeof(input), stdin);
    //testing
    printf("input: %s \n", input);
    cmds = parse_cmds(input);
    //testing
    print_args(cmds);
  }

  
  
  //char ** args = parse_args(input);
  
  
  
  return 0;
}

int main(){
  shell();
  
  return 0;
}
