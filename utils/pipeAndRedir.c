#include "libraries.h"

int piping(char *input)
{
    char **commands = tokenise_input(input,"|");
    int length = 0;
    while(commands[length]!=NULL)
        length++;
    if(length==1)
        return redirect(commands[0]);
    int pipes[2][2];
    for(int x=0;x<length;x++)
    {
        if(pipe(pipes[(x+1)%2]) < 0){
            perror("pipe creation");
            return 1;
        }
        pid_t child = fork();
        if(child<0){
            perror("for pipeline");
            return 1;
        }
        else if(child==0){
            if(x>0){
                dup2(pipes[x%2][0],STDIN_FILENO);
            }
            if(x<length-1){
                dup2(pipes[(x+1)%2][1],STDOUT_FILENO);
            }
            if(redirect(commands[x])==-1)
                return -1;
            _exit(0);
        }
        else{
            wait(NULL);
            if(x>0)
                close(pipes[x%2][0]);
            if(x<length-1)
                close(pipes[(x+1)%2][1]);
        }
    }
    return 0;
}
int redirect(char *input)
{
    char **commands = tokenise_input(input," ");
    int length = 0;
    while(commands[length]!=NULL)
        length++;
    char **argv = (char**)(malloc(MAX_ARGS*(sizeof(char*))));
    int argc = 0;
    int mode = 0;   // 1 for input, 2 for output new,  3 for output append
    char *inputfile=NULL, *outputfile=NULL;
    int append = 0;
    for(int x=0;x<length;x++)
    {
        if(strcmp(commands[x],"<")==0){
            mode=1;
        }
        else if(strcmp(commands[x],">")==0){
            mode=2;
        }
        else if(strcmp(commands[x],">>")==0){
            mode=3;
            append=1;
        }
        if(mode==0){
            argv[argc] = commands[x];
            argc++;
        }
        else if(mode==1){
            inputfile = commands[x];
        }
        else if(mode==2 || mode==3){
            outputfile = commands[x];
        }
    }
    argv[argc] = NULL;
    int og_input = dup(STDIN_FILENO);
    int og_output = dup(STDOUT_FILENO);
    int inputfd,outputfd;
    if(inputfile!=NULL){
        inputfd = open(inputfile,O_RDONLY);
        if(inputfd<0){
            perror("open in redirection");
            return 1;
        }
        dup2(inputfd,STDIN_FILENO);
    }
    if(outputfile!=NULL){
        if(append)
            outputfd = open(outputfile,O_CREAT | O_WRONLY | O_APPEND, 0644);
        else
            outputfd = open(outputfile,O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if(outputfd<0){
            perror("open in redirection");
            return 1;
        }
        dup2(outputfd,STDOUT_FILENO);
    }
    if(execute_commands(argc,argv)==-1)
        return -1;
    if(inputfile!=NULL)
        close(inputfd);
    if(outputfile!=NULL)
        close(outputfd);
    dup2(og_input,STDIN_FILENO);
    dup2(og_output,STDOUT_FILENO);
    return 0;
}