#include "../utils/libraries.h"

int cmd_repeat(int argc, char **argv)
{
    if(argc<3){
        fprintf(stderr,"insufficient arguments\n");
        return 1;
    }
    int times=0;
    for(int x=0;x<strlen(argv[1]);x++){
        if(argv[1][x]<'0' || argv[1][x]>'9'){
            fprintf(stderr,"incorrect arguments\n");
            return 1;
        }
        times = times*10+(argv[1][x]-'0');
    }
    for(int x=0;x<times;x++){
        int flag = execute_commands(argc-2,&argv[2]);
        if(flag==-1)
            return -1;
    }
    return 0;
}