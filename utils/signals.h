#ifndef MATRIX_SIGNALS_H
#define MATRIX_SIGNALS_H

struct proc{
    int pid;
    char *proc_name;
};

void init_process_list();
void process_signal(int sig);
void add_proc(int pid, char* name);
void remove_proc(int pid);
char* proc_name(int pid);
void ctrlc();
void ctrlz();
struct proc *process_list;
int proc_count;

#endif//MATRIX_SIGNALS_H
