#include "../utils/libraries.h"

int cmd_execvp(int argc, char **argv)
{
    argv[argc] = NULL;
    int bg_flag=0;
    char *command;
    char *arglist[1000];
    int count=0;
    for(int x=0;x<argc;x++)
    {
        if(strcmp(argv[x],"&")==0)
        {
            bg_flag=1;
            command = argv[0];
            for(int y=0;y<x;y++)
            {
                arglist[count] = argv[y];
                count++;
            }
            arglist[count] = NULL;
            break;
        }
        else
        {
            int s=0;
            while(argv[x][s]!='\0')
                s++;
            if(argv[x][s-1]=='&')
            {
                bg_flag=1;
                for(int y=0;y<=x;y++)
                {
                    arglist[count] = argv[y];
                    if(y==x)
                    {
                        arglist[count][s-1]='\0';
                        if(x>0)
                            command = argv[0];
                        else
                            command = arglist[count];
                    }
                    count++;
                }
                arglist[count] = NULL;
                break;
            }
        }
    }


    pid_t child_pid = fork();
    int status;
    if(bg_flag && child_pid>0)
        printf("%d\n",child_pid);
    if(child_pid<0){
        fprintf(stderr,"cannot create child process\n");
        return 1;
    }
    else if(child_pid>0)
    {
        if(!bg_flag){
            fg_running.pid=child_pid;
            fg_running.proc_name = argv[0];
            waitpid(child_pid, &status, WUNTRACED);
        }
        else{
            add_proc(child_pid,command);
            setpgid(child_pid, 0);
            tcsetpgrp(0,getpgrp());
        }
    }
    else if(child_pid==0)
    {
        setpgid(0,0);
        if(bg_flag){
            if(execvp(command,arglist)<0){
                perror("execvp");
                exit(1);
            }
        }
        else{
            if(execvp(argv[0],argv)<0){
                perror("execvp");
                exit(1);
            }
        }
        exit(0);
    }
    return 0;
}