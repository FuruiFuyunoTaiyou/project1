void print_args(char ** arguments);

char ** parse_cmds(char * input);

char ** parse_args(char * line);

int has_redirect_stdout(char ** args);

int redirect_stdout(char * path);

void unredirect_stdout(int fd_stdout_new);

int exec_cmd(char ** args);

int exec_cmds(char ** cmds);

int shell();

