#include "libraries.h"


void init_process_list()
{
    process_list = malloc(sizeof(struct proc)*MAX_ARGS);
    for(int x=0;x<MAX_ARGS;x++)
        process_list[x].proc_name = NULL, process_list[x].pid = 0;
    proc_count=0;
}

void add_proc(int pid, char* name)
{
    process_list[proc_count].pid = pid;
    process_list[proc_count].proc_name = name;
    proc_count++;
}
void remove_proc(int pid)
{
    int i=0;
    while(process_list[i].pid!=pid)
        i++;
    for(int x=i;x<MAX_ARGS;x++)
        process_list[x] = process_list[x+1];
    proc_count--;
}
char* proc_name(int pid)
{
    int i=0;
    while(process_list[i].pid!=pid)
        i++;
    return process_list[i].proc_name;
}
void process_signal(int sig)
{
    int wstatus;
    pid_t child_pid = waitpid(-1, &wstatus, WNOHANG);;
    if(child_pid<=0){
        return;
    }
    for(int x=0;x<MAX_ARGS;x++){
        if(child_pid == process_list[x].pid){
            if(WIFEXITED(wstatus)){
                fprintf(stderr,"\n%s with pid %d exited normally\n",proc_name(child_pid),child_pid);
                prompt();
            }
            else{
                fprintf(stderr,"\n%s with pid %d exited abnormally\n",proc_name(child_pid),child_pid);
                prompt();
            }
            remove_proc(child_pid);
        }
        fflush(stdout);
    }
}
void ctrlc()
{
    printf("\n");
    prompt();
    fflush(stdout);
    if(fg_running.pid!=-1){
        kill(fg_running.pid,SIGINT);
    }
}
void ctrlz()
{
    printf("\n");
    prompt();
    fflush(stdout);
    if(fg_running.pid!=-1){
        add_proc(fg_running.pid,fg_running.proc_name);
        kill(fg_running.pid,SIGTSTP);
    }
}