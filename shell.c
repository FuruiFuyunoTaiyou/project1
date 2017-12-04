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
/*
char * strsep_mod(char ** original_stringp, const char * delim){
  char ** old_stringp = original_stringp;
  char * delim_location = strstr(*original_stringp, delim);
  if(delim_location){
    *delim_location = NULL;
    *original_stringp = delim_location + strlen(delim);
  }else{
    *original_stringp = NULL;
  }
  return *old_stringp;
}
*/
char ** parse_cmds(char * input){
  char * newline = strchr(input, '\n'); //removing works, but warning.
  if(newline){
    *newline = NULL;
  }

  char ** cmds = calloc(6, sizeof(char *));
  int i = 0;
  while(i < 5){
    //cmds[i] = strsep_mod(&input, ";"); //didn't work as expected with delim " ; "
    //testing
    //printf("cmds[%d]: %s", i, cmds[i]);
    cmds[i] = strsep(&input, ";");
    i++;
  }
  cmds[i] = NULL;
  return cmds;
}

char ** parse_args(char * line){ //needs to be modified for more args?
  char * s1 = line;
  //cutting off possible spaces on ends
  if(*s1 == ' '){
    s1++;
  }
  if(s1[strlen(s1) - 1] == ' '){
    s1[strlen(s1) - 1] = NULL;
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

int exec_cmd(char ** args){ //if that cmd is supposed to result in an exit, return 0. Otherwise, return 1
  int child_pid;
  if(strcmp(args[0], "cd") == 0){
    chdir(args[1]);
  }else if(strcmp(args[0], "exit") == 0){
    return 0;
  }else{
    child_pid = fork();
    if(child_pid){ //parent
      wait();
    }else{ //child
      execvp(args[0], args);
      return 0; //in case
    }
  }
  return 1;
}

int exec_cmds(char ** cmds){ //return 0 if exit. Otherwise, continue and return 1 when done
  int i = 0;
  char ** args;
  //int child_pid;
  while(cmds[i]){ //get & execute first full cmd
    args = parse_args(cmds[i]); //be careful, some of the commands will start a/o  with a space, so strsep may make the first arg an empty string and have an empty string as the last arg
    //testing
    print_args(args);
    if(exec_cmd(args) == 0){ //if that cmd is supposed to result in an exit (0), then exit. Otherwise, continue
      return 0;
    }
    i++;
  }
  free(cmds);
  return 1;
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
    if(exec_cmds(cmds) == 0){ //if exec_cmds returns a 0, we end. Otherwise, continue.
      return 0;
    }
  }
  return 0;
}

int main(){
  shell();
  
  return 0;
}
