#<u>*Matrix*</u> - Shell for OS Assignment
##Division of Code:
The entire code is divided into modular files. The "utils" directory has helper functions and "cmds" has all the codes to run different commands.
The code starts from the main.c from where other functions are called.

* "libraries.h" contains all the libraries and .h files used with macros and global variables.
* "tokeniser" contains functions to display the prompt, divide the input by '|' , '>' , '<' , '>>' , ';' and space and call the function to execute the command.
* "signals" handles the the termination of background process, and manages the SIGINT and SIGTSTP signal sent by pressing ctrl+c and ctrl+z and outputs appropriately.
* "pipeAndRedir" contains code to break the input and open and close pipes,files and redirect the input and output.
* cmds folder contain the .c and .h files to execute all the various commands.


##Assumption:
* The history will display at max 20 commands.
* Maximum length of command that can be entered at one time is 1000.
* Maximum length of path for a file or directory is 1000.
* Maximum number of arguments for a command can be 100.
* Maximum length of a variable name can be 100.
* The file for saving history will be created in the same directory from which shell was invoked.
* The baywatch command has a default interval of 1 second after which it prints again.

##Features:
For features, refer the Assignment 2 & 3 document present in the same as this directory.

##To run the shell:
Run ```make``` and then ```./Matrix```. This will run the shell directly.