void print_args(char ** arguments);

char ** parse_cmds(char * input);

char ** parse_args(char * line);

int exec_cmd(char ** args);

int exec_cmds(char ** cmds);

int shell();

