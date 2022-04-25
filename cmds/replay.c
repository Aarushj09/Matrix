#include "../utils/libraries.h"

int cmd_replay(int argc, char **argv)
{
    int command_length = 0;
    char **commands = (char**)(malloc(MAX_ARGS*(sizeof(char*))));
    char *interval, *period;
    int flag_c=0,flag_i=0,flag_p=0;
    for(int x=0;x<argc;x++){
        if(strcmp(argv[x],"-command")==0){
            flag_c=1;flag_i=0;flag_p=0;
        }
        else if(strcmp(argv[x],"-interval")==0){
            flag_c=0;flag_i=1;flag_p=0;
        }
        else if(strcmp(argv[x],"-period")==0){
            flag_c=0;flag_i=0;flag_p=1;
        }
        else if(flag_c==1){
            commands[command_length] = argv[x];
            command_length++;
        }
        else if(flag_i==1){
            interval = argv[x];
        }
        else if(flag_p==1){
            period = argv[x];
        }
    }
    int i = 0;
    while(interval[i]!=0){
        if(interval[i]<'0' || interval[i]>'9'){
            fprintf(stderr,"sig needs integer arguments\n");
            return 1;
        }
        i++;
    }
    i=0;
    while(period[i]!=0){
        if(period[i]<'0' || period[i]>'9'){
            fprintf(stderr,"sig needs integer arguments\n");
            return 1;
        }
        i++;
    }
    int per = (int)atoi(period);
    int inter = (int)atoi(interval);
    int time = 0;
    while(time+inter<=per){
        sleep(inter);
        execute_commands(command_length,commands);
        time+=inter;
    }
    if(per-time>0){
        sleep(per-time);
    }
}