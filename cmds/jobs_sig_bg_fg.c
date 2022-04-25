#include "../utils/libraries.h"

int cmd_jobs(int argc, char **argv)
{
    // t = stopped
    // r/s = running
    int flag_r=0, flag_s=0;
    int option=0;
    optind=1;
    while((option = getopt(argc,argv,"-rs"))!=-1)
    {
        switch (option) {
            case 'r': flag_r=1;
                break;
            case 's': flag_s=1;
                break;
            case '?':
                fprintf(stderr,"invalid flags for jobs\n");
                return 1;
        }
    }
    struct sort_proc sort_processlist[MAX_ARGS];
    for(int x=0;x<proc_count;x++){
        sort_processlist[x].proc_name = process_list[x].proc_name;
        sort_processlist[x].pid = process_list[x].pid;
        sort_processlist[x].proc_num = x+1;
    }
    for(int x=0;x<proc_count;x++)
    {
        for(int y=0;y<proc_count-1-x;y++)
        {
            if(strcmp(sort_processlist[y].proc_name,sort_processlist[y+1].proc_name)>0)
            {
                // swap strings
                struct sort_proc temp;
                temp=sort_processlist[y];
                sort_processlist[y]=sort_processlist[y+1];
                sort_processlist[y+1]=temp;
            }
        }
    }
    for(int x=0;x<proc_count;x++){
        char *path = malloc(MAX_PATH_SIZE* sizeof(char));
        sprintf(path,"/proc/%d/stat",sort_processlist[x].pid);
        int fd = open(path,O_RDONLY);
        char *buf = malloc(MAX_PATH_SIZE*(sizeof(char)));
        if(read(fd,buf,MAX_PATH_SIZE)<0){
            perror("read");
            return 1;
        }
        strtok(buf," ");strtok(NULL," ");
        char *status = strtok(NULL," ");
        close(fd);
        char *final;
        if(status[0] == 'S' || status[0] == 'R')
            final = "Running";
        else
            final = "Stopped";
        if((flag_s==0 && flag_r==0) || (flag_s==1 && flag_r==1))
            printf("[%d] %s %s [%d]\n",sort_processlist[x].proc_num, final,sort_processlist[x].proc_name, sort_processlist[x].pid);
        else if(flag_s==1 && strcmp(final,"Stopped")==0)
            printf("[%d] %s %s [%d]\n",sort_processlist[x].proc_num, final,sort_processlist[x].proc_name, sort_processlist[x].pid);
        else if(flag_r==1 && strcmp(final,"Running")==0)
            printf("[%d] %s %s [%d]\n",sort_processlist[x].proc_num, final,sort_processlist[x].proc_name, sort_processlist[x].pid);
    }
}
int cmd_sig(int argc, char **argv)
{
    if(argc!=3){
        fprintf(stderr,"sig needs 2 arguments\n");
        return 1;
    }
    int job_no, signal;
    int i = 0;
    while(argv[1][i]!=0){
        if(argv[1][i]<'0' || argv[1][i]>'9'){
            fprintf(stderr,"sig needs integer arguments\n");
            return 1;
        }
        i++;
    }
    i=0;
    while(argv[2][i]!=0){
        if(argv[2][i]<'0' || argv[2][i]>'9'){
            fprintf(stderr,"sig needs integer arguments\n");
            return 1;
        }
        i++;
    }
    job_no = (int)atoi(argv[1]);
    signal = (int)atoi(argv[2]);
    if(job_no < 1 || job_no> proc_count){
        fprintf(stderr,"Invalid job number\n");
        return 1;
    }
    kill(process_list[job_no-1].pid,signal);
}
int cmd_fg(int argc, char **argv)
{
    if(argc!=2){
        fprintf(stderr,"fg needs 1 arguments\n");
        return 1;
    }
    int job_no;
    int i = 0;
    while(argv[1][i]!=0){
        if(argv[1][i]<'0' || argv[1][i]>'9'){
            fprintf(stderr,"fg needs integer arguments\n");
            return 1;
        }
        i++;
    }

    job_no = (int)atoi(argv[1]);
    if(job_no < 1 || job_no> proc_count){
        fprintf(stderr,"Invalid job number\n");
        return 1;
    }

    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    struct proc pid = process_list[job_no-1];
    if(tcsetpgrp(0,pid.pid)==-1){
        perror("fg");
        return 1;
    }
    kill(pid.pid, SIGCONT);
    fg_running.pid = process_list[job_no-1].pid;
    fg_running.proc_name = process_list[job_no-1].proc_name;
    remove_proc(pid.pid);
    int status;
    waitpid(pid.pid,&status,WUNTRACED);
    if(WIFSTOPPED(status)){
        add_proc(pid.pid,pid.proc_name);
    }
    tcsetpgrp(0, getpgrp());
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
}
int cmd_bg(int argc, char **argv)
{
    if(argc!=2){
        fprintf(stderr,"bg needs 1 arguments\n");
        return 1;
    }
    int job_no;
    int i = 0;
    while(argv[1][i]!=0){
        if(argv[1][i]<'0' || argv[1][i]>'9'){
            fprintf(stderr,"bg needs integer arguments\n");
            return 1;
        }
        i++;
    }
    job_no = (int)atoi(argv[1]);
    if(job_no < 1 || job_no> proc_count){
        fprintf(stderr,"Invalid job number\n");
        return 1;
    }
    kill(process_list[job_no-1].pid,SIGCONT);
}
