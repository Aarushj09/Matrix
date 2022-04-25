#ifndef MATRIX_LIBRARIES_H
#define MATRIX_LIBRARIES_H

#include <stdio.h>
#include <error.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "tokeniser.h"
#include "signals.h"
#include "pipeAndRedir.h"
#include "../cmds/ls.h"
#include "../cmds/cd.h"
#include "../cmds/pwd.h"
#include "../cmds/echo.h"
#include "../cmds/execvp.h"
#include "../cmds/repeat.h"
#include "../cmds/history.h"
#include "../cmds/pinfo.h"
#include "../cmds/jobs_sig_bg_fg.h"
#include "../cmds/replay.h"
#include "../cmds/baywatch.h"

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define MAX_VAR_NAME 100
#define MAX_FILE_SIZE 100
#define MAX_PATH_SIZE 1000
#define MAX_INPUT_SIZE 1000
#define MAX_ARGS 100
#define MAX_HISTORY 20
#define MIN_HISTORY 10

int shell_grpid;
struct proc fg_running;
char* home_dir;
char* prev_dir;
char* current_dir;
char* format;
char* system_name;
char **history;
char *history_path;
#endif//MATRIX_LIBRARIES_H
