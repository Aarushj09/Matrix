#ifndef MATRIX_JOBS_SIG_BG_FG_H
#define MATRIX_JOBS_SIG_BG_FG_H

struct sort_proc{
    int proc_num;
    int pid;
    char *proc_name;
};

int cmd_jobs(int argc, char **argv);
int cmd_sig(int argc, char **argv);
int cmd_fg(int argc, char **argv);
int cmd_bg(int argc, char **argv);

#endif//MATRIX_JOBS_SIG_BG_FG_H
