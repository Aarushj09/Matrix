#include "../utils/libraries.h"

int cmd_pinfo(int argc, char **argv)
{
    int pid=0;
    if(argc==1)
        pid = (int)(getpid());
    else if(argc==2){
        for(int x=0;x<strlen(argv[1]);x++){
            if(argv[1][x]<'0' || argv[1][x]>'9'){
                fprintf(stderr,"incorrect arguments\n");
                return 1;
            }
            pid = pid*10+(argv[1][x]-'0');
        }
    }
    else{
        fprintf(stderr,"pinfo: too many arguments\n");
        return 1;
    }


    char *path = malloc(MAX_PATH_SIZE* sizeof(char));
    sprintf(path,"/proc/%d/stat",pid);
    int fd = open(path,O_RDONLY);
    char *buf = malloc(MAX_PATH_SIZE*(sizeof(char)));
    if(read(fd,buf,MAX_PATH_SIZE)<0){
        perror("read");
        return 1;
    }
    strtok(buf," ");strtok(NULL," ");

    printf("pid -- %d\n",pid);
    printf("Process status -- %s",strtok(NULL," "));

    if(getpgid(pid)==shell_grpid)
        printf("+\n");
    else
        printf("\n");
    close(fd);

    sprintf(path,"/proc/%d/statm",pid);
    int fd1 = open(path,O_RDONLY);

    if(read(fd,buf,MAX_PATH_SIZE)<0){
        perror("read");
        return 1;
    }
    printf("memory -- %s\n",strtok(buf," "));
    close(fd1);

    char buf2[1000];
    char buf3[1000];
    sprintf(buf2,"/proc/%d/exe",pid);
    int len = readlink(buf2,buf3,sizeof(buf3));
    if(len<=0){
        perror("readlink");
        return 1;
    }
    buf3[len] = 0;
    printf("Executable Path -- %s\n",buf3);

    return 0;
}