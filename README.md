Project1
by Winnie Chen

Implemented:
    Forks and executes commands.
    Reads and separates multiple commands on one line with ;.
    Can do simple redirection using >. 
    
Unsuccessful:
    Simple redirection using < does not work as intended.
    Did not implement simple pipes.
    
Known Bugs:
    Does not work if there is more than one whitespace character 
    next to an argument.
    Redirecting stdin does not do anything but empty the file.
    
Function Headers:
    /*********************************
    NAME: void print_args(char ** arguments)

    INPUTS: char ** arguments

    RETURNS: N/A

    Prints the strings stored in the string array arguments.
    *********************************/

    /*********************************
    NAME: char ** parse_cmds(char * input)

    INPUTS: char * input

    RETURNS: Array of strings where each element is a command 
    line command

    Removes the \n from input, then creates and returns an array 
    of string commands by separating the string input by “;”.

    NOTES: Assumes there are 10 or less commands.
    *********************************/

    /*********************************
    NAME: char ** parse_args(char * line)

    INPUTS: char * line

    RETURNS: Array of strings where each element is an argument 
    of a command line command

    Cuts off possible extra space at the beginning and/or end of 
    the string line, then creates and returns an array of string 
    arguments by separating the string input by “ ”.

    NOTES: Assumes there are 10 or less arguments.
    *********************************/

    /*********************************
    NAME: int has_redirect_stdout(char ** args)

    INPUTS: char ** args

    RETURNS: Int index of the string array args at which the 
    filepath for where stdout is to be redirected to is located
            Int 0 if there is no redirection 

    Loops through the string array args to check for signs of 
    simple redirection of stdout (an element of “>”). Returns 
    the index of string array args for where the path for 
    redirection is if there is to be redirection. Returns 0 
    otherwise.
    *********************************/

    /*********************************
    NAME: int redirect_stdout(char * path)

    INPUTS: char * path

    RETURNS: Int file descriptor for the duplicate of stdout

    Duplicates the stdout entry, opens the file at path and 
    redirects stdout to it. Returns the int file descriptor 
    for the duplicate stdout entry.
    *********************************/

    /*********************************
    NAME: void unredirect_stdout(int fd_stdout_new)

    INPUTS: int fd_stdout_new

    RETURNS: N/A

    Duplicates the behavior of the duplicate stdout entry whose 
    file descriptor is stored in int fd_stdout_new at the file 
    with a file descriptor of 1, then closes the duplicate stdout 
    entry.
    *********************************/
    
    /*********************************
    NAME: int has_redirect_stdin(char ** args)

    INPUTS: char ** args

    RETURNS: Int index of the string array args at which the 
    filepath from where stdin is to be redirected to is located
            Int 0 if there is no redirection 

    Loops through the string array args to check for signs of 
    simple redirection of stdin (an element of “<”). Returns the 
    index of string array args for where the path for redirection 
    is if there is to be redirection. Returns 0 otherwise.
    *********************************/

    /*********************************
    NAME: int exec_cmd(char ** args)

    INPUTS: char ** args

    RETURNS: int 0 if the executed command should result in the 
    program being exited
            int 1 if otherwise

    Executes the command line command specified by the string 
    array args. Forks a child for commands other than cd and exit. 
    Returns a 0 if the specified command is “exit” and a 1 otherwise. 
    *********************************/

    /*********************************
    NAME: int exec_cmds(char ** cmds)

    INPUTS: char ** cmds

    RETURNS: int 0 if it encounters an executed command that should 
    result in the program being exited
            int 1 if otherwise

    Executes the line of command line command(s) one by one, in the 
    order specified by the string array cmds. Frees cmds, assuming 
    cmds was calloc’d when parse_cmds() was used. Returns a 0 if 
    it encounters the command “exit” and a 1 otherwise.
    *********************************/

    /*********************************
    NAME: int shell()

    INPUTS: N/A

    RETURNS: Int 0 when exited

    Takes in a line of input, parses the input into a string array 
    cmds, and executes the commands specified in string array cmds. 
    Returns 0 if exec_cmds() encounters the command “exit”.
    *********************************/
