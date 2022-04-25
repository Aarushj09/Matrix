#include "../utils/libraries.h"

void load_history()
{
    if(file_exists(history_path)){
        FILE *f = fopen(history_path,"r");
        char *cmd = NULL;
        size_t sz = MAX_INPUT_SIZE;
        int i = 0;
        while (getline(&cmd,&sz,f)!=-1){
            char *temp = malloc(MAX_INPUT_SIZE*sizeof(char));
            strcpy(temp,cmd);
            history[i] = temp;
            i++;
        }
        for(int x=i;x<MAX_HISTORY;x++)
            history[x] = NULL;
        fclose(f);
    }
    else{
        for(int x=0;x<MAX_HISTORY;x++)
            history[x] = NULL;
    }
}

void save_history()
{
    FILE *f = fopen(history_path,"w");
    for(int x=0;x<MAX_HISTORY;x++){
        if(history[x]!=NULL)
        {
            fprintf(f,"%s",history[x]);
        }
    }
    fclose(f);
}
void add_to_history(char *input)
{
    if(history[0]!=NULL && strcmp(history[0],input)==0)
        return;
    if(history[MAX_HISTORY-1]!=NULL)
        free(history[MAX_HISTORY-1]);
    for(int x = MAX_HISTORY-1;x>0;x--){
        history[x] = history[x-1];
    }
    char *temp = malloc(MAX_INPUT_SIZE*sizeof(char));
    strcpy(temp,input);
    history[0] = temp;
}

int cmd_history(int argc, char **argv)
{
    if(argc==1)
    {
        for(int x=0;x<10;x++)
            if(history[9-x]!=NULL)
                printf("%s", history[9-x]);
    }
    else if(argc==2)
    {
        int times=0;
        for(int x=0;x<strlen(argv[1]);x++){
            if(argv[1][x]<'0' || argv[1][x]>'9'){
                fprintf(stderr,"incorrect arguments\n");
                return 1;
            }
            times = times*10+(argv[1][x]-'0');
        }
        for(int x=0;x<times;x++)
            if(history[times-x]!=NULL)
                printf("%s", history[times-x]);
        return 0;
    }
    else{
        fprintf(stderr,"history: too many arguments\n");
        return 1;
    }
    return 0;
}