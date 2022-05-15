# Matrix

## Division of Code:

The entire code is divided into modular files. The "utils" directory has helper functions and "cmds" has all the codes to run different commands.
The code starts from the main.c from where other functions are called.

* `libraries.h` contains all the libraries and .h files used with macros and global variables.
* `tokeniser` contains functions to display the prompt, divide the input by '|' , '>' , '<' , '>>' , ';' and space and call the function to execute the command.
* `signals` handles the the termination of background process, and manages the SIGINT and SIGTSTP signal sent by pressing ctrl+c and ctrl+z and outputs appropriately.
* `pipeAndRedir` contains code to break the input and open and close pipes,files and redirect the input and output.
* `cmds` folder contain the .c and .h files to execute all the various commands.


## Assumption:
* The history will display at max 20 commands.
* Maximum length of command that can be entered at one time is 1000.
* Maximum length of path for a file or directory is 1000.
* Maximum number of arguments for a command can be 100.
* Maximum length of a variable name can be 100.
* The file for saving history will be created in the same directory from which shell was invoked.
* The baywatch command has a default interval of 1 second after which it prints again.

## Features:
* `baywatch`: A modified version of the bash command watch, that works for three specific commands: <br>

1. <b>interrupt:</b> Prints the number of times the CPUs have been interrupted by the keyboard controller (i8042 with IRQ 1)

2. <b>newborn:</b> Prints the PID of the most recently created process.

3. <b>dirty:</b> Prints the size of the part of memory that is dirty.
```bash
baywatch -n <interval> interrupt
baywatch -n <interval> newborn
baywatch -n <interval> dirty
```

Press <kbd>Q</kbd> to terminate the command.

* `bg`: Changes the state of a stopped background job to running.
```bash
bg <job_number>
```

* `cd`: Changes the working directory of the shell.
```bash
cd
cd - # To go to the previous working directory
cd ~
cd ../..
cd dir_1/dir_2/dir_3
```

* `echo`: Prints the text following "echo" on the terminal.
```bash
echo "Hello World"
echo Welcome to ASH
```

* `fg`: Brings the running/stopped background job to the foreground.
```bash
fg <job_number>
```

* `history`: Displays a list of the commands previously used (at most the 20 latest commands).
```bash
history
history <n> # To display last n commands used
```

* `jobs`: Prints a list of all currently running background processes spawned by the shell in alphabetical order of the command name, along with
the job number, process ID and the state.
```bash
jobs
jobs -s
jobs -r
jobs -rs
jobs -s -r
```

* `ls`: Lists the contents of a particular directory.
```bash
ls
ls -a
ls -l
ls -al
ls -la
ls -a -l
ls -l -a
ls ../../dir_1/dir_2
ls ~
ls dir_1/file_name
```

* `pinfo`: Displays information about a particular process.
```bash
pinfo # Displays information about the shell process itself
pinfo <pid>
```

* `pwd`: Prints the absolute path of the current working directory.
```bash
pwd
```

* `repeat`: Executes a given command n times.
```bash
repeat <n> <command>
```

* `replay`: Executes a particular command in fixed time interval for a certain period.
```bash
replay -command <command> -interval <interval> -period <period>
```

* `sig`: Sends the signal corresponding to signal number​ to the process with the particular job number.
```
sig <job_number> <signal_number>
```

* <b>System Commands: </b>ASH should run many of the processes that bash can, including `gedit`, `vim`, `clear`, etc.
```bash
gedit
vim
clear
ps
```

* <b>Background Processes: </b>Add `&` at the end of the command to run it as a background process. This however only works for system commands, and not shell built-ins.
```bash
gedit &
```
## To run the shell:
Run ```make``` and then ```./Matrix```. This will run the shell directly.