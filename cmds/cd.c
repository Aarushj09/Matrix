#include "../utils/libraries.h"
int cmd_cd(int argc, char **argv)
{

    if(argc==1){
        prev_dir = current_dir;

        if(home_dir == NULL){
            chdir(getenv("HOME"));
            current_dir = getenv("HOME");
        }
        else{
            chdir(home_dir);
            current_dir = home_dir;
        }
    }
    else if(argc==2){
        if(strcmp(argv[1],"-")==0){
            if(prev_dir == NULL){
                fprintf(stderr,"cd: OLDPWD not set\n");
                return 0;
            }
            else{
                printf("%s\n",prev_dir);
                chdir(prev_dir);
                char *temp = prev_dir;
                prev_dir = current_dir;
                current_dir = temp;
            }
            return 1;
        }
        char *newpath;
        if(argv[1][0]=='~'){
            char *home = getenv("HOME");
            if(home_dir != NULL){
                home = home_dir;
            }
            newpath = (char *)(malloc(MAX_PATH_SIZE* sizeof(char)));
            int start=0;
            while(home[start]!='\0'){
                newpath[start] = home[start];
                start++;
            }
            int s2=1;
            while(argv[1][s2]!='\0'){
                newpath[start] = argv[1][s2];
                start++;s2++;
            }
            newpath[start]='\0';
            argv[1] = newpath;
        }
        if(chdir(argv[1])==-1){
            perror("cd");
            return 0;
        }
        prev_dir = current_dir;
        current_dir = getcwd(NULL,0);
    }
    else
    {
        fprintf(stderr,"cd: too many arguments\n");
        return 0;
    }

    return 1;
}

