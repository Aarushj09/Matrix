#include "../cmds/jobs_sig_bg_fg.h"
#include "../cmds/pinfo.h"
#include "libraries.h"

void prompt()
{
    char* dir;
    dir = current_dir;
    int start=0;
    while(home_dir[start]!='\0' && current_dir[start]!='\0' && home_dir[start] == current_dir[start])
        start++;
    if(home_dir[start]=='\0' && (current_dir[start]=='\0' || current_dir[start]=='/'))
        dir = &current_dir[start];
    printf("%s~%s>",format,dir);
}

char **tokenise_input(char* input, char* del)
{
    char *string = malloc(MAX_INPUT_SIZE*(sizeof(char))), *token, *ptr1;
    char **commands = (char**)(malloc(MAX_ARGS*(sizeof(char*))));
    strcpy(string, input);
    token = strtok_r(string, del, &ptr1);
    int count = 0;
    while(token!=NULL)
    {
        commands[count] = token;
        count++;
        token = strtok_r(NULL,del,&ptr1);
    }
    commands[count] = NULL;
    return commands;
}

int break_input(char *input)
{
    char **semicoloncmds = tokenise_input(input,";\n");
    for(int x=0;semicoloncmds[x]!=NULL;x++){
        if(piping(semicoloncmds[x])==-1)
            return -1;
    }
    return 0;
}
int execute_commands(int argc, char **argv)
{
    int flag = 0;
    if(argc==0)
        return 0;
    if(strcmp(argv[0],"exit")==0)
        flag=-1;
    else if(strcmp(argv[0],"ls")==0)
        flag = cmd_ls(argc,argv);
    else if(strcmp(argv[0],"echo")==0)
        flag = cmd_echo(argc,argv);
    else if(strcmp(argv[0],"cd")==0)
        flag = cmd_cd(argc,argv);
    else if(strcmp(argv[0],"pwd")==0)
        flag = cmd_pwd(argc,argv);
    else if(strcmp(argv[0],"repeat")==0)
        flag = cmd_repeat(argc,argv);
    else if(strcmp(argv[0],"history")==0)
        flag = cmd_history(argc,argv);
    else if(strcmp(argv[0],"pinfo")==0)
        flag = cmd_pinfo(argc,argv);
    else if(strcmp(argv[0],"jobs")==0)
        flag = cmd_jobs(argc,argv);
    else if(strcmp(argv[0],"sig")==0)
        flag = cmd_sig(argc,argv);
    else if(strcmp(argv[0],"fg")==0)
        flag = cmd_fg(argc,argv);
    else if(strcmp(argv[0],"bg")==0)
        flag = cmd_bg(argc,argv);
    else if(strcmp(argv[0],"replay")==0)
        flag = cmd_replay(argc,argv);
    else if(strcmp(argv[0],"baywatch")==0)
        flag = cmd_baywatch(argc,argv);
    else
        flag = cmd_execvp(argc,argv);
    return flag;
}