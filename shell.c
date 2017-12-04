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

  char ** cmds = calloc(11, sizeof(char *));
  int i = 0;
  while(i < 10){
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
  char ** args = calloc(11, sizeof(char *));;
  int i = 0;
  while(i<10){
    args[i] = strsep(&s1, " ");
    i++;
  }
  args[i] = NULL;
  return args;
}

//checks for element/string ">"... and later, another one will check for <
int has_redirect_stdout(char ** args){
  int i = 0;
  while(args[i]){ 
    if(strcmp(args[i], ">") == 0){
      return i + 1; //return index of path if redirecting
    }
    i++;
  }
  return 0;
}

//if ">" existent, rearrange files, execute, rearrange back to normal. 
//Assuming this will be in exec_cmd
int redirect_stdout(char * path){ //return value is the reference to stdout param filename?
  //gotta open file for fd?
  int fd_stdout = 1;
  int fd_stdout_new = dup(fd_stdout);
  int fd_file = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
  dup2(fd_file, fd_stdout);
  return fd_stdout_new;
}

void unredirect_stdout(int fd_stdout_new){
  dup2(fd_stdout_new, 1);
  close(fd_stdout_new); //and also close the other file?
}

int has_redirect_stdin(char ** args){
  int i = 0;
  while(args[i]){ 
    if(strcmp(args[i], "<") == 0){
      return i + 1; //return index of path if redirecting
    }
    i++;
  }
  return 0;
}

/*
int redirect_stdin(char * path){ //return value is the reference to stdin param filename?
  int fd_stdin = 0;
  int fd_stdin_new = dup(fd_stdin);
  int fd_file = open(path, O_RDONLY | O_TRUNC | O_CREAT, 0644); //what if file DNE?
  dup2(fd_file, fd_stdin);
  return fd_stdin_new;
}

void unredirect_stdin(int fd_stdin_new){
  dup2(fd_stdin_new, 0);
  close(fd_stdin_new); //and also close the other file?
}
*/

int exec_cmd(char ** args){ //if that cmd is supposed to result in an exit, return 0. Otherwise, return 1
  int child_pid;
  int has_redirect_out = has_redirect_stdout(args);
  int new_fd_stdout;
  int has_redirect_in = has_redirect_stdin(args);
  int new_fd_stdin;
  //int fd_file;
  if(has_redirect_out){ 
    //redirect & save the ref!
    new_fd_stdout = redirect_stdout(args[has_redirect_out]);
    args[has_redirect_out - 1] = NULL;
  }
  /*
  if(has_redirect_in){ 
    //printf("redirecting in using element %d as path\n", has_redirect_in);
    new_fd_stdin = redirect_stdin(args[has_redirect_in]);
    args[has_redirect_in - 1] = NULL;
  }
  */
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
  //un-redirect!
  if(has_redirect_out){
    unredirect_stdout(new_fd_stdout);
  }
  /*
  if(has_redirect_in){
    unredirect_stdin(new_fd_stdin);
  }
  */
  return 1;
}

int exec_cmds(char ** cmds){ //return 0 if exit. Otherwise, continue and return 1 when done
  int i = 0;
  char ** args;
  //int child_pid;
  while(cmds[i]){ //get & execute first full cmd
    args = parse_args(cmds[i]); 
    //testing
    //print_args(args);
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
    printf("type command(s): ");
    fgets(input, sizeof(input), stdin);
    //testing
    //printf("input: %s \n", input);
    cmds = parse_cmds(input);
    //testing
    //print_args(cmds);
    if(exec_cmds(cmds) == 0){ //if exec_cmds returns a 0, we end. Otherwise, continue.
      return 0;
    }
  }
  return 0;
}

int main(){
  return shell();
}
