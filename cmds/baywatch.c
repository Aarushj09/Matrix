#include "../utils/libraries.h"

int cmd_baywatch(int argc, char **argv)
{
    if(argc!=2 && argc!=4){
        fprintf(stderr,"Insufficient or wrong arguments for baywatch\n");
        return -1;
    }
    int interval = 1;
    char *command;
    char *inter;
    if(argc==2){
        command = argv[1];
    }
    if(argc==4){
        if(strcmp(argv[1],"-n")==0){
            inter = argv[2];
            command = argv[3];
        }
        else if(strcmp(argv[2],"-n")==0){
            inter = argv[3];
            command = argv[1];
        }
        else{
            fprintf(stderr,"Insufficient or wrong arguments for baywatch\n");
            return -1;
        }
    }
    if(strcmp(command,"interrupt")!=0 && strcmp(command,"newborn")!=0 && strcmp(command,"dirty")!=0){
        fprintf(stderr,"Invalid command for baywatch\n");
        return -1;
    }
    if(argc==4){
        int i = 0;
        while(inter[i]!=0){
            if(inter[i]<'0' || inter[i]>'9'){
                fprintf(stderr,"sig needs integer arguments\n");
                return 1;
            }
            i++;
        }
        interval = (int)atoi(inter);
    }
    int t = 0;
    int count = 0;
    while(keypressed()!='q'){
        if(t>interval){
            t=0;
            if(strcmp(command,"interrupt")==0)
                cmd_interrupt(count++);
            if(strcmp(command,"newborn")==0)
                cmd_newborn(count++);
            if(strcmp(command,"dirty")==0)
                cmd_dirty(count++);
        }
        else{
            sleep(1);
            t++;
        }
    }
    printf("\n");
}
void cmd_interrupt(int a)
{
    int fd = open("/proc/interrupts", O_RDONLY);
    if(fd<0){
        perror("Interrupt file");
        return;
    }
    char *string = calloc(5000,sizeof(char));
    read(fd,string,5000);
    char *first = strtok(string,"\n");
    if(a==0){
        printf("%s\n",first+5);
    }
    first = strtok(NULL,"\n");
    first = strtok(NULL,"\n");
    int i=0;
    while(first[i]!='I')
        i++;
    first[i] = '\0';
    printf("%s\n",first+5);
    close(fd);
}
void cmd_newborn(int a)
{
    int fd = open("/proc/loadavg", O_RDONLY);
    if(fd<0){
        perror("Loadavg file");
        return;
    }
    char *string = calloc(5000,sizeof(char));
    read(fd,string,5000);
    char *first = strtok(string," ");
    char *pid;
    while(first!=NULL){
        pid = first;
        first = strtok(NULL," ");
    }
    printf("%s", pid);
    close(fd);
}
void cmd_dirty(int a)
{
    int fd = open("/proc/meminfo", O_RDONLY);
    if(fd<0){
        perror("Meminfo file");
        return;
    }
    char *string = calloc(5000,sizeof(char));
    read(fd,string,5000);
    char *first = strtok(string,"\n");
    for(int x=0;x<16;x++)
        first = strtok(NULL,"\n");
    int i=6;
    while(first[i]==' ')
        i++;
    printf("%s\n", first+i);
    close(fd);
}
char keypressed()
{
    struct termios st;
    tcgetattr(0, &st);
    st.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &st);
    int count;
    ioctl(0, FIONREAD, &count);
    tcgetattr(0, &st);
    st.c_lflag |= ICANON | ECHO;
    tcsetattr(0, TCSANOW, &st);
    if(count == 0)
        return '\0';
    else
        return getchar();
}